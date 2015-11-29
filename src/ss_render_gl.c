

#define GL_GLEXT_PROTOTYPES
// #include "SDL2/SDL_opengl.h"
#if defined(__APPLE__) && (__MACH__)
#  include <OpenGL/gl.h>
#  undef __glext_h_
#  undef GL_GLEXT_VERSION
#  undef GL_VERSION_1_2
#else
#  include <GL/gl.h>
#endif
#include "glext.h"


#define SS_TEXTURE_HANDLE_DATA void* __dummy; GLuint id;
#define SS_TEXRSURF_HANDLE_DATA void* __dummy; GLuint id;
#define SS_TEXDSURF_HANDLE_DATA void* __dummy; GLuint id;
#define SS_RENDERER_OVERRIDE

#include "ss_main.h"


static void* mglGetProcAddress( const char* procnames )
{
	while( *procnames )
	{
		void* proc = SDL_GL_GetProcAddress( procnames );
		if( proc )
			return proc;
		while( *procnames )
			procnames++;
		procnames++;
	}
	return NULL;
}

#define SSGL_FBO_SUPPORT 0x0001


struct _SS_Renderer
{
	SS_RENDERER_DATA
	SDL_GLContext* ctx;
	PFNGLBLENDEQUATIONPROC glBlendEquation;
	PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
	PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
	PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
	PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
	PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
	PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
	PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
	PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
	int width;
	int height;
	float world_matrix[16];
	float view_matrix[16];
	SS_Texture* cur_rtt;
	int flags;
	int bbwidth, bbheight, bbscale;
};


static void ss_ri_gl__resetviewport( SS_Renderer* R )
{
	if( R->bbscale != SS_POSMODE_NONE )
		glViewport( 0, 0, SGS_MIN( R->bbwidth, R->width ), SGS_MIN( R->bbheight, R->height ) );
	else
		glViewport( 0, 0, R->width, R->height );
}


static void ss_ri_gl_init();
static void ss_ri_gl_free();
static int ss_ri_gl_available();
static SS_Renderer* ss_ri_gl_create( SDL_Window* window, uint32_t flags );
static void ss_ri_gl_destroy( SS_Renderer* R );
static void* ss_ri_gl_get_pointer( SS_Renderer* R, int which );
static void ss_ri_gl_modify( SS_Renderer* R, int* modlist );
static void ss_ri_gl_set_buffer_scale( SS_Renderer* R, int enable, int width, int height, int scalemode );
static void ss_ri_gl_set_current( SS_Renderer* R );
static void ss_ri_gl_poke_resource( SS_Renderer* R, sgs_VarObj* obj, int add );
static void ss_ri_gl_swap( SS_Renderer* R );
static void ss_ri_gl_clear( SS_Renderer* R, float* col4f );
static void ss_ri_gl_set_render_state( SS_Renderer* R, int which, int arg0, int arg1, int arg2, int arg3 );
static void ss_ri_gl_set_matrix( SS_Renderer* R, int which, float* data );
static void ss_ri_gl_set_rt( SS_Renderer* R, SS_Texture* T );

static int ss_ri_gl_create_texture_argb8( SS_Renderer* R, SS_Texture* T, SS_Image* I, uint32_t flags );
static int ss_ri_gl_create_texture_a8( SS_Renderer* R, SS_Texture* T, uint8_t* data, int width, int height, int pitch );
static int ss_ri_gl_create_texture_rnd( SS_Renderer* R, SS_Texture* T, int width, int height, uint32_t flags );
static int ss_ri_gl_destroy_texture( SS_Renderer* R, SS_Texture* T );
static int ss_ri_gl_apply_texture( SS_Renderer* R, SS_Texture* T );

static int ss_ri_gl_init_vertex_format( SS_Renderer* R, SS_VertexFormat* F );
static int ss_ri_gl_free_vertex_format( SS_Renderer* R, SS_VertexFormat* F );
static int ss_ri_gl_draw_basic_vertices( SS_Renderer* R, void* data, uint32_t count, int ptype );
static int ss_ri_gl_draw_ext( SS_Renderer* R, SS_VertexFormat* F, void* vdata, uint32_t vdsize, void* idata, uint32_t idsize, int i32, uint32_t start, uint32_t count, int ptype );


SS_RenderInterface GRI_GL =
{
	ss_ri_gl_init,
	ss_ri_gl_free,
	ss_ri_gl_available,
	ss_ri_gl_create,
	ss_ri_gl_destroy,
	ss_ri_gl_get_pointer,
	ss_ri_gl_modify,
	ss_ri_gl_set_buffer_scale,
	ss_ri_gl_set_current,
	ss_ri_gl_poke_resource,
	ss_ri_gl_swap,
	ss_ri_gl_clear,
	ss_ri_gl_set_render_state,
	ss_ri_gl_set_matrix,
	ss_ri_gl_set_rt,
	
	ss_ri_gl_create_texture_argb8,
	ss_ri_gl_create_texture_a8,
	ss_ri_gl_create_texture_rnd,
	ss_ri_gl_destroy_texture,
	ss_ri_gl_apply_texture,
	
	ss_ri_gl_init_vertex_format,
	ss_ri_gl_free_vertex_format,
	ss_ri_gl_draw_basic_vertices,
	ss_ri_gl_draw_ext,
	
	/* flags */
	SS_RI_COLOR_RGBA,
	/* API */
	"GL",
	
	/* last error */
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

static SS_Renderer* ss_ri_gl_create( SDL_Window* window, uint32_t flags )
{
	int w, h, x, y;
	SDL_GLContext* ctx, *origctx;
	SDL_Window* origwin;
	SS_Renderer* R;
	SGS_CTX = ss_GetContext();
	
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
	R->iface = &GRI_GL;
	R->window = window;
	R->ctx = ctx;
	R->glBlendEquation = (PFNGLBLENDEQUATIONPROC) SDL_GL_GetProcAddress( "glBlendEquation" );
	R->glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) SDL_GL_GetProcAddress( "glBlendFuncSeparate" );
	R->glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) mglGetProcAddress( "glGenRenderbuffersEXT\0glGenRenderbuffers\0" );
	R->glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) mglGetProcAddress( "glBindRenderbufferEXT\0glBindRenderbuffer\0" );
	R->glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) mglGetProcAddress( "glRenderbufferStorageEXT\0glRenderbufferStorage\0" );
	R->glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) mglGetProcAddress( "glDeleteRenderbuffersEXT\0glDeleteRenderbuffers\0" );
	R->glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) mglGetProcAddress( "glGenFramebuffersEXT\0glGenFramebuffers\0" );
	R->glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) mglGetProcAddress( "glBindFramebufferEXT\0glBindFramebuffer\0" );
	R->glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) mglGetProcAddress( "glDeleteFramebuffersEXT\0glDeleteFramebuffers\0" );
	R->glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) mglGetProcAddress( "glFramebufferTextureEXT\0glFramebufferTexture\0" );
	R->glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) mglGetProcAddress( "glFramebufferRenderbufferEXT\0glFramebufferRenderbuffer\0" );
	R->glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) mglGetProcAddress( "glCheckFramebufferStatusEXT\0glCheckFramebufferStatus\0" );
	
	R->width = w;
	R->height = h;
	
	R->flags = 0;
	if( R->glGenRenderbuffers && R->glBindRenderbuffer && R->glRenderbufferStorage && R->glDeleteRenderbuffers &&
		R->glGenFramebuffers && R->glBindFramebuffer && R->glDeleteFramebuffers && R->glFramebufferTexture &&
		R->glFramebufferRenderbuffer && R->glCheckFramebufferStatus )
		R->flags |= SSGL_FBO_SUPPORT;
	
	R->bbwidth = 0;
	R->bbheight = 0;
	R->bbscale = 0;
	
	for( y = 0; y < 4; ++y )
	{
		for( x = 0; x < 4; ++x )
		{
			R->world_matrix[ x + 4 * y ] =
			R->view_matrix[ x + 4 * y ] =
				x == y ? 1 : 0;
		}
	}
	R->view_matrix[ 11 ] = -100;
	glDisable( GL_DEPTH_TEST );
	glMatrixMode( GL_MODELVIEW );
	glLoadMatrixf( R->view_matrix );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, w, h, 0, 1, 1000 );
	R->cur_rtt = NULL;
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0 );
	
	if( flags & SS_RENDERER_VSYNC )
	{
		if( 0 != SDL_GL_SetSwapInterval( -1 ) )
			SDL_GL_SetSwapInterval( 1 );
	}
	
	SDL_GL_MakeCurrent( origwin, origctx );
	
	sgs_vht_init( &R->rsrc_table, C, 64, 64 );
	R->destructing = 0;
	
	sgs_CreateDict( C, &R->textures, 0 );
	sgs_CreateDict( C, &R->fonts, 0 );
	sgs_CreateDict( C, &R->rsdict, 0 );
	
	sgs_PushString( C, "textures" );
	sgs_SetIndex( C, R->rsdict, sgs_StackItem( C, -1 ), R->textures, 0 );
	sgs_Pop( C, 1 );
	sgs_PushString( C, "fonts" );
	sgs_SetIndex( C, R->rsdict, sgs_StackItem( C, -1 ), R->fonts, 0 );
	sgs_Pop( C, 1 );
	
	return R;
}

static void ss_ri_gl_destroy( SS_Renderer* R )
{
	int i;
	SGS_CTX = ss_GetContext();
	
	sgs_Release( C, &R->rsdict );
	
	R->destructing = 1;
	for( i = 0; i < R->rsrc_table.size; ++i )
	{
		sgs_VarObj* obj = (sgs_VarObj*) R->rsrc_table.vars[ i ].val.data.P;
		sgs_ObjCallDtor( C, obj );
	}
	sgs_vht_free( &R->rsrc_table, C );
	
	if( GCurRr == R )
	{
		GCurRr = NULL;
		GCurRI = NULL;
	}
	SDL_GL_DeleteContext( R->ctx );
	free( R );
}

static void* ss_ri_gl_get_pointer( SS_Renderer* R, int which )
{
	SGS_UNUSED( which );
	return NULL;
}

static void ss_ri_gl_modify( SS_Renderer* R, int* modlist )
{
	int w, h;
	int resize = 0;
	SDL_GetWindowSize( R->window, &w, &h );
	
	while( *modlist )
	{
		if( *modlist == SS_RMOD_WIDTH ){ resize = 1; w = modlist[1]; R->width = w; }
		else if( *modlist == SS_RMOD_HEIGHT ){ resize = 1; h = modlist[1]; R->height = h; }
		
		modlist += 2;
	}
	
	if( resize )
		ss_ri_gl__resetviewport( R );
}

static void ss_ri_gl_set_buffer_scale( SS_Renderer* R, int enable, int width, int height, int scalemode )
{
	R->bbwidth = enable ? width : 0;
	R->bbheight = enable ? height : 0;
	R->bbscale = enable ? scalemode : 0;
}

static void ss_ri_gl_set_current( SS_Renderer* R )
{
	SGS_CTX = ss_GetContext();
	sgs_SetGlobalByName( C, "_RND", R->rsdict );
	
	SDL_GL_MakeCurrent( R->window, R->ctx );
}

static void ss_ri_gl_poke_resource( SS_Renderer* R, sgs_VarObj* obj, int add )
{
	SGS_CTX = ss_GetContext();
	sgs_Variable K = sgs_MakePtr( obj );
	
	if( R->destructing )
		return;
	
	if( add )
		sgs_vht_set( &R->rsrc_table, C, &K, &K );
	else
		sgs_vht_unset( &R->rsrc_table, C, &K );
}

static void ss_ri_gl_swap( SS_Renderer* R )
{
	if( R->bbscale != SS_POSMODE_NONE )
	{
		GLuint texID;
		
		int w = SGS_MIN( R->bbwidth, R->width );
		int h = SGS_MIN( R->bbheight, R->height );
		void* data = malloc( w * h * 4 );
		if( data )
		{
			/* width factors */
			float wf = 1, hf = 1, xoff, yoff;
			float aspect = ( (float) w / (float) h ) / ( (float) R->width / (float) R->height );
			switch( R->bbscale )
			{
			case SS_POSMODE_CROP:
				if( aspect > 1 )
					wf = aspect;
				else
					hf = 1 / aspect;
				break;
			case SS_POSMODE_FIT:
				if( aspect > 1 )
					hf = 1 / aspect;
				else
					wf = aspect;
				break;
			case SS_POSMODE_FITRND:
				{
					int wc = (int) floor( (float) R->width / (float) w );
					int hc = (int) floor( (float) R->height / (float) h );
					int cnt = SGS_MAX( 1, SGS_MIN( wc, hc ) );
					wf = (float) w * cnt / (float) R->width;
					hf = (float) h * cnt / (float) R->height;
				}
				break;
			case SS_POSMODE_CENTER:
				wf = (float) w / (float) R->width;
				hf = (float) h / (float) R->height;
				break;
			default:
				break;
			}
			xoff = ( 1 - wf ) / 2;
			yoff = ( 1 - hf ) / 2;
			
			glReadPixels( 0, 0, w, h, GL_BGRA, GL_UNSIGNED_BYTE, data );
			
			glClearColor( 0, 0, 0, 0 );
			glClear( GL_COLOR_BUFFER_BIT );
			glViewport( 0, 0, R->width, R->height );
			
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( 0, 1, 1, 0, -1, 1 );
			
			glGenTextures( 1, &texID );
			glBindTexture( GL_TEXTURE_2D, texID );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glBegin( GL_QUADS );
			glTexCoord2f( 0, 1 );
			glVertex2f( xoff, yoff );
			glTexCoord2f( 1, 1 );
			glVertex2f( 1 - xoff, yoff );
			glTexCoord2f( 1, 0 );
			glVertex2f( 1 - xoff, 1 - yoff );
			glTexCoord2f( 0, 0 );
			glVertex2f( xoff, 1 - yoff );
			glEnd();
			glDeleteTextures( 1, &texID );
			
			free( data );
		}
	}
	SDL_GL_SwapWindow( R->window );
	ss_ri_gl__resetviewport( R );
}

static void ss_ri_gl_clear( SS_Renderer* R, float* col4f )
{
	int flags = GL_DEPTH_BUFFER_BIT;
	glClearDepth( 1.0f );
	if( col4f )
	{
		glClearColor( col4f[0], col4f[1], col4f[2], col4f[3] );
		flags |= GL_COLOR_BUFFER_BIT;
	}
	glClear( flags );
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
		if( arg2 < 0 || arg2 >= SS_BLEND__COUNT ) arg2 = SS_BLEND_ONE;
		if( arg3 < 0 || arg3 >= SS_BLEND__COUNT ) arg3 = SS_BLEND_ZERO;
		if( !R->glBlendFuncSeparate )
			glBlendFunc( blendfactors[ arg0 ], blendfactors[ arg1 ] );
		else
			R->glBlendFuncSeparate( blendfactors[ arg0 ], blendfactors[ arg1 ], blendfactors[ arg2 ], blendfactors[ arg3 ] );
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
	else if( which == SS_RS_VIEWPORT )
	{
		/* x0 = arg0, y0 = arg1, x1 = arg2, y1 = arg3 */
		glViewport( arg0, R->height - arg3, arg2 - arg0, arg3 - arg1 );
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

static void ss_ri_gl_set_matrix( SS_Renderer* R, int which, float* mtx )
{
	if( which == SS_RMAT_PROJ )
	{
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( mtx );
	}
	else
	{
		memcpy( which == SS_RMAT_VIEW ? R->view_matrix : R->world_matrix, mtx, sizeof(R->view_matrix) );
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( R->view_matrix );
		glMultMatrixf( R->world_matrix );
	}
	glMatrixMode( which == SS_RMAT_PROJ ? GL_PROJECTION : GL_MODELVIEW );
}

static void ss_ri_gl_set_rt( SS_Renderer* R, SS_Texture* T )
{
	if( !( R->flags & SSGL_FBO_SUPPORT ) )
		return;
	R->cur_rtt = T;
	R->glBindFramebuffer( GL_FRAMEBUFFER, T ? T->rsh.id : 0 );
	if( !T )
		ss_ri_gl__resetviewport( R );
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
	
	T->renderer = R;
	T->width = I->width;
	T->height = I->height;
	T->flags = flags;
	T->handle.id = id;
	T->rsh.id = 0;
	T->dsh.id = 0;
	return 1;
}

static int ss_ri_gl_create_texture_a8( SS_Renderer* R, SS_Texture* T, uint8_t* data, int width, int height, int pitch )
{
	int x, y;
	uint8_t* imgdata;
	GLuint tex = 0;
	SGS_CTX = ss_GetContext();
	
	glGenTextures( 1, &tex );
	glBindTexture( GL_TEXTURE_2D, tex );
	
	imgdata = sgs_Alloc_n( uint8_t, width * height * 4 );
	for( y = 0; y < height; ++y )
	{
		for( x = 0; x < width; ++x )
		{
			int off = y * width * 4 + x * 4;
			imgdata[ off ] = 0xff;
			imgdata[ off + 1 ] = 0xff;
			imgdata[ off + 2 ] = 0xff;
			imgdata[ off + 3 ] = data[ x ];
		}
		data += pitch;
	}
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, imgdata );
	sgs_Dealloc( imgdata );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	
	T->renderer = R;
	T->width = width;
	T->height = height;
	T->flags = 0;
	T->handle.id = tex;
	T->rsh.id = 0;
	T->dsh.id = 0;
	return 1;
}

static int ss_ri_gl_create_texture_rnd( SS_Renderer* R, SS_Texture* T, int width, int height, uint32_t flags )
{
	GLuint fb = 0, tex = 0, ds_rb = 0;
	
	if( !( R->flags & SSGL_FBO_SUPPORT ) )
	{
		GRI_GL.last_error = "renderable textures are not supported";
		return 0;
	}
	
	glGenTextures( 1, &tex );
	glBindTexture( GL_TEXTURE_2D, tex );
	
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
	
	if( flags & SS_TEXTURE_HREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	if( flags & SS_TEXTURE_VREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flags & SS_TEXTURE_NOLERP ? GL_NEAREST : GL_LINEAR );
	{
		GLuint minf = flags & SS_TEXTURE_MIPMAPS ?
			( flags & SS_TEXTURE_NOLERP ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR ) :
			( flags & SS_TEXTURE_NOLERP ? GL_NEAREST : GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minf );
	}
	
	R->glGenRenderbuffers( 1, &ds_rb );
	R->glBindRenderbuffer( GL_RENDERBUFFER, ds_rb );
	R->glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height );
	R->glBindRenderbuffer( GL_RENDERBUFFER, 0 );
	
	R->glGenFramebuffers( 1, &fb );
	R->glBindFramebuffer( GL_FRAMEBUFFER, fb );
	R->glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0 );
	R->glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ds_rb );
	
	GLenum e = R->glCheckFramebufferStatus( GL_FRAMEBUFFER );
	if( e != GL_FRAMEBUFFER_COMPLETE )
	{
		GRI_GL.last_error = "failed to validate framebuffer (incompatible format / driver issue)";
		return 0;
	}
	
	R->glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	T->renderer = R;
	T->width = width;
	T->height = height;
	T->flags = flags | SS_TEXTURE_RENDER;
	T->handle.id = tex;
	T->rsh.id = fb;
	T->dsh.id = ds_rb;
	return 1;
}

static int ss_ri_gl_destroy_texture( SS_Renderer* R, SS_Texture* T )
{
	if( R->cur_rtt == T )
		ss_ri_gl_set_rt( R, NULL );
	if( T->rsh.id )
	{
		R->glDeleteFramebuffers( 1, &T->rsh.id );
	}
	if( T->dsh.id )
	{
		R->glDeleteRenderbuffers( 1, &T->dsh.id );
	}
	glDeleteTextures( 1, &T->handle.id );
	return 1;
}

static int ss_ri_gl_apply_texture( SS_Renderer* R, SS_Texture* T )
{
	if( T )
	{
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, T->handle.id );
		glMatrixMode( GL_TEXTURE );
		float flip = T->rsh.id ? 1 : 0;
		float m[16] =
		{
			1, 0, 0, 0,
			0, 1 - flip * 2, 0, 0,
			0, 0, 1, 0,
			0, flip, 0, 1
		};
		glLoadMatrixf( m );
	}
	else
		glDisable( GL_TEXTURE_2D );
	return 1;
}


static int ss_ri_gl_init_vertex_format( SS_Renderer* R, SS_VertexFormat* F )
{
	return 1;
}

static int ss_ri_gl_free_vertex_format( SS_Renderer* R, SS_VertexFormat* F )
{
	return 1;
}

static const int primtypes[] =
{
	GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_TRIANGLES,
	GL_TRIANGLE_FAN,
	GL_TRIANGLE_STRIP,
	GL_QUADS,
};

static int ss_ri_gl_draw_basic_vertices( SS_Renderer* R, void* data, uint32_t count, int ptype )
{
	int mode;
	char* Bptr = (char*) data;
	
	if( ptype < 0 || ptype >= SS_PT__COUNT )
		return 0;
	mode = primtypes[ ptype ];
	
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	
	glVertexPointer( 3, GL_FLOAT, sizeof(SS_BasicVertex), Bptr );
	glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(SS_BasicVertex), Bptr + 12 );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(SS_BasicVertex), Bptr + 16 );
	
	glDrawArrays( mode, 0, count );
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	
	return 1;
}

static int datatype( int setype )
{
	if( setype == SS_RSET_FLOAT ) return GL_FLOAT;
	if( setype == SS_RSET_BYTE ) return GL_UNSIGNED_BYTE;
	return 0;
}

static int ss_ri_gl_draw_ext( SS_Renderer* R, SS_VertexFormat* F, void* vdata, uint32_t vdsize, void* idata, uint32_t idsize, int i32, uint32_t start, uint32_t count, int ptype )
{
	int mode;
	char* BVptr = (char*) vdata;
	char* idcs = (char*) idata;
	
	if( ptype < 0 || ptype >= SS_PT__COUNT )
		return 0;
	mode = primtypes[ ptype ];
	
	if( F->P[0] ) glVertexPointer( F->P[3], datatype( F->P[2] ), F->size, BVptr + F->P[1] );
	if( F->T[0] ) glTexCoordPointer( F->T[3], datatype( F->T[2] ), F->size, BVptr + F->T[1] );
	if( F->C[0] ) glColorPointer( F->C[3], datatype( F->C[2] ), F->size, BVptr + F->C[1] );
	if( F->N[0] ) glNormalPointer( F->N[2], F->size, BVptr + F->N[1] );
	
	if( F->P[0] ) glEnableClientState( GL_VERTEX_ARRAY );
	if( F->T[0] ) glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	if( F->C[0] ) glEnableClientState( GL_COLOR_ARRAY );
	if( F->N[0] ) glEnableClientState( GL_NORMAL_ARRAY );
	
	glColor4f( 1, 1, 1, 1 );
	if( idcs )
		glDrawElements( mode, count, GL_UNSIGNED_SHORT, idcs + start * 2 );
	else
		glDrawArrays( mode, start, count );
	
	if( F->P[0] ) glDisableClientState( GL_VERTEX_ARRAY );
	if( F->T[0] ) glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	if( F->C[0] ) glDisableClientState( GL_COLOR_ARRAY );
	if( F->N[0] ) glDisableClientState( GL_NORMAL_ARRAY );
	
	return 1;
}

