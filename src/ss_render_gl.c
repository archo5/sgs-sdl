

#define GL_GLEXT_PROTOTYPES
#include "SDL2/SDL_opengl.h"
#include "glext.h"

#include <GL/gl.h>

#define SS_TEXTURE_HANDLE_DATA void* __dummy; GLuint id;

#include "ss_main.h"


struct _SS_Renderer
{
	SDL_Window* window;
	SDL_GLContext* ctx;
	PFNGLBLENDEQUATIONPROC glBlendEquation;
	int height;
};


static void ss_ri_gl_init();
static void ss_ri_gl_free();
static int ss_ri_gl_available();
static SS_Renderer* ss_ri_gl_create( SDL_Window* window, uint32_t version, uint32_t flags );
static void ss_ri_gl_destroy( SS_Renderer* R );
static void ss_ri_gl_modify( SS_Renderer* R, int* modlist );
static void ss_ri_gl_set_current( SS_Renderer* R );
static void ss_ri_gl_swap( SS_Renderer* R, SGS_CTX );
static void ss_ri_gl_clear( SS_Renderer* R, float* col4f );
static void ss_ri_gl_set_render_state( SS_Renderer* R, int which, int arg0, int arg1, int arg2, int arg3 );

static int ss_ri_gl_create_texture_argb8( SS_Renderer* R, SGS_CTX, SS_Texture* T, SS_Image* I, uint32_t flags );
static int ss_ri_gl_create_texture_a8( SS_Renderer* R, SS_Texture* T, uint8_t* data, int width, int height, int pitch );
static int ss_ri_gl_destroy_texture( SS_Renderer* R, SS_Texture* T );
static int ss_ri_gl_apply_texture( SS_Renderer* R, SS_Texture* T );


SS_RenderInterface GRI_GL =
{
	ss_ri_gl_init,
	ss_ri_gl_free,
	ss_ri_gl_available,
	ss_ri_gl_create,
	ss_ri_gl_destroy,
	ss_ri_gl_modify,
	ss_ri_gl_set_current,
	ss_ri_gl_swap,
	ss_ri_gl_clear,
	ss_ri_gl_set_render_state,
	
	ss_ri_gl_create_texture_argb8,
	ss_ri_gl_create_texture_a8,
	ss_ri_gl_destroy_texture,
	ss_ri_gl_apply_texture,
	
	0,
	
	"no error",
};


static void ss_ri_gl_init()
{
}

static void ss_ri_gl_free()
{
}

static int ss_ri_gl_available()
{
	return 1;
}

static SS_Renderer* ss_ri_gl_create( SDL_Window* window, uint32_t version, uint32_t flags )
{
	int w, h;
	SDL_GLContext* ctx, *origctx;
	SDL_Window* origwin;
	SS_Renderer* R;
	
	origctx = SDL_GL_GetCurrentContext();
	origwin = SDL_GL_GetCurrentWindow();
	
	SDL_GetWindowSize( window, &w, &h );
	ctx = SDL_GL_CreateContext( window );
	if( !ctx )
	{
		GRI_GL.last_error = SDL_GetError();
		return NULL;
	}
	
	R = (SS_Renderer*) malloc( sizeof(*R) );
	R->window = window;
	R->ctx = ctx;
	R->glBlendEquation = (PFNGLBLENDEQUATIONPROC) SDL_GL_GetProcAddress( "glBlendEquation" );
	R->height = h;
	
	glDisable( GL_DEPTH_TEST );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( 0, 0, -100 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, w, h, 0, 1, 1000 );
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0 );
	
	SDL_GL_MakeCurrent( origwin, origctx );
	
	if( flags & SS_RENDERER_VSYNC )
	{
		if( 0 != SDL_GL_SetSwapInterval( -1 ) )
			SDL_GL_SetSwapInterval( 1 );
	}
	
	return R;
}

static void ss_ri_gl_destroy( SS_Renderer* R )
{
	if( GCurRr == R )
	{
		GCurRr = NULL;
		GCurRI = NULL;
	}
	SDL_GL_DeleteContext( R->ctx );
	free( R );
}

static void ss_ri_gl_modify( SS_Renderer* R, int* modlist )
{
	int w, h;
	int resize = 0;
	SDL_GetWindowSize( window, &w, &h );
	
	while( *modlist )
	{
		if( *modlist == SS_RMOD_WIDTH ){ if( w != modlist[1] ){ resize = 1; w = modlist[1]; } }
		else if( *modlist == SS_RMOD_HEIGHT ){ if( h != modlist[1] ){ resize = 1; h = modlist[1]; R->height = h; } }
		
		modlist += 2;
	}
	
	if( resize )
		glViewport( 0, 0, w, h );
}

static void ss_ri_gl_set_current( SS_Renderer* R )
{
	SDL_GL_MakeCurrent( R->window, R->ctx );
}

static void ss_ri_gl_swap( SS_Renderer* R )
{
	SDL_GL_SwapWindow( R->window );
}

static void ss_ri_gl_clear( SS_Renderer* R, float* col4f )
{
	glClearDepth( 1.0f );
	glClearColor( col4f[0], col4f[1], col4f[2], col4f[3] );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

static void ss_ri_gl_set_render_state( SS_Renderer* R, int which, int arg0, int arg1, int arg2, int arg3 )
{
	if( which == SS_RS_BLENDFACTORS )
	{
		static const int blendfactors[] =
		{
			GL_ZERO,
			GL_ONE,
			GL_SRC_COLOR,
			GL_ONE_MINUS_SRC_COLOR,
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA,
			GL_DST_COLOR,
			GL_ONE_MINUS_DST_COLOR,
			GL_DST_ALPHA,
			GL_ONE_MINUS_DST_ALPHA,
			GL_SRC_ALPHA_SATURATE,
		};
		if( arg0 < 0 || arg0 >= SS_BLEND__COUNT ) arg0 = SS_BLEND_SRCALPHA;
		if( arg1 < 0 || arg1 >= SS_BLEND__COUNT ) arg1 = SS_BLEND_INVSRCALPHA;
		glBlendFunc( blendfactors[ src ], blendfactors[ dst ] );
	}
	else if( which == SS_RS_BLENDOP )
	{
		static const int blendfuncs[] =
		{
			GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX,
		};
		if( arg0 < 0 || arg0 >= SS_BLENDOP__COUNT ) arg0 = SS_BLENDOP_ADD;
		R->glBlendEquation( blendfuncs[ arg0 ] );
	}
	else if( which == SS_RS_CLIPENABLE )
	{
		if( arg0 )
			glEnable( GL_SCISSOR_TEST );
		else
			glDisable( GL_SCISSOR_TEST );
	}
	else if( which == SS_RS_CLIPRECT )
	{
		/* x0 = arg0, y0 = arg1, x1 = arg2, y1 = arg3 */
		glScissor( arg0, R->height - arg3, arg2 - arg0, arg3 - arg1 );
	}
	else if( which == SS_RS_CULLING )
	{
		if( arg0 )
		{
			glCullFace( arg0 < 0 ? GL_FRONT : GL_BACK );
			glEnable( GL_CULL_FACE );
		}
		else
			glDisable( GL_CULL_FACE );
	}
	else if( which == SS_RS_ZENABLE )
	{
		if( arg0 )
			glEnable( GL_DEPTH_TEST );
		else
			glDisable( GL_DEPTH_TEST );
	}
}


static int ss_ri_gl_create_texture_argb8( SS_Renderer* R, SS_Texture* T, SS_Image* I, uint32_t flags )
{
	GLuint id;
	SGS_CTX = ss_GetContext();
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );
	
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
#ifndef GL_BGRA
#  define GL_BGRA 0x80E1
#endif
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, I->width, I->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, I->data );
	if( flags & SS_TEXTURE_MIPMAPS )
	{
		int miplev = 0;
		int more = I->width > 1 || I->height > 1;
		SS_Image* pdI = I;
		while( more )
		{
			SS_Image* dI = ss_ImageDS2X( pdI, C );
			if( pdI != I )
				ss_DeleteImage( pdI, C );
			pdI = dI;
			more = dI->width > 1 || dI->height > 1;
			glTexImage2D( GL_TEXTURE_2D, ++miplev, GL_RGBA, dI->width,
				dI->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, dI->data );
		}
		if( pdI != I )
			ss_DeleteImage( pdI, C );
	}
	
	if( flags & SS_TEXTURE_HREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	if( flags & SS_TEXTURE_VREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flags & SS_TEXTURE_NOLERP ? GL_NEAREST : GL_LINEAR );
	{
		GLuint minf = flags & SS_TEXTURE_MIPMAPS ?
			( flags & SS_TEXTURE_NOLERP ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR ) :
			( flags & SS_TEXTURE_NOLERP ? GL_NEAREST : GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minf );
	}
	
	T->riface = &GRI_GL;
	T->renderer = R;
	T->width = ii->width;
	T->height = ii->height;
	T->flags = flags;
	T->handle.id = id;
	return 1;
}

static int ss_ri_gl_create_texture_a8( SS_Renderer* R, SS_Texture* T, uint8_t* data, int width, int height, int pitch )
{
	SGS_CTX = ss_GetContext();
	GLuint tex = 0;
	
	glGenTextures( 1, &tex );
	glBindTexture( GL_TEXTURE_2D, tex );
	
	imgdata = sgs_Alloc_n( uint8_t, glyph->bitmap.width * glyph->bitmap.rows * 4 );
	pp = glyph->bitmap.buffer;
	for( y = 0; y < glyph->bitmap.rows; ++y )
	{
		for( x = 0; x < glyph->bitmap.width; ++x )
		{
			int off = y * glyph->bitmap.width * 4;
			imgdata[ off + x * 4 ] = 0xff;
			imgdata[ off + x * 4 + 1 ] = 0xff;
			imgdata[ off + x * 4 + 2 ] = 0xff;
			imgdata[ off + x * 4 + 3 ] = pp[ x ];
		}
		pp += glyph->bitmap.pitch;
	}
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, glyph->bitmap.width, glyph->bitmap.rows,
		0, GL_RGBA, GL_UNSIGNED_BYTE, imgdata );
	sgs_Dealloc( imgdata );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	
	T->riface = &GRI_GL;
	T->renderer = R;
	T->width = width;
	T->height = height;
	T->flags = 0;
	T->handle.id = id;
	return 1;
}

static int ss_ri_gl_destroy_texture( SS_Renderer* R, SS_Texture* T )
{
	glDeleteTextures( 1, &T->handle.id );
	return 1;
}

static int ss_ri_gl_apply_texture( SS_Renderer* R, SS_Texture* T )
{
	if( T )
	{
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, T->handle.id );
	}
	else
		glDisable( GL_TEXTURE_2D );
	return 1;
}

