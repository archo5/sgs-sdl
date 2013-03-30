
#include "ss_main.h"


#define FN( f ) { #f, ss_##f }
#define IC( i ) { #i, i }
#define _WARN( err ) { sgs_Printf( C, SGS_ERROR, -1, err ); return 0; }


int ss_sleep( SGS_CTX )
{
	sgs_Integer time;
	if( sgs_StackSize( C ) != 1 ||
		!stdlib_toint( C, 0, &time ) )
		_WARN( "sleep() - unexpected arguments; function expects 1 argument: int" )
	
	SDL_Delay( time );
	return 0;
}

flag_string_item_t setvideomode_flags[] =
{
	{ "fullscreen", SDL_FULLSCREEN },
	{ "resizable", SDL_RESIZABLE },
	{ "noframe", SDL_NOFRAME },
	FSI_LAST
};
int ss_set_video_mode( SGS_CTX )
{
	char* ts;
	SDL_Surface* scr;
	sgs_Integer w, h, b, f, tss;
	
	if( sgs_StackSize( C ) != 4 ||
		!stdlib_toint( C, 0, &w ) ||
		!stdlib_toint( C, 1, &h ) ||
		!stdlib_toint( C, 2, &b ) ||
		!stdlib_tostring( C, 3, &ts, &tss ) )
		_WARN( "set_video_mode() - unexpected arguments; function expects 4 arguments: int, int, int, string" )
	
	f = sgs_GetFlagString( C, 3, setvideomode_flags );
	f |= SDL_OPENGL;
	
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	scr = SDL_SetVideoMode( w, h, b, f );
	glDisable( GL_DEPTH_TEST );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( 0, 0, -100 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, w, h, 0, 1, 1000 );
	
	sgs_PushBool( C, !!scr );
	return 1;
}

int ss_set_caption( SGS_CTX )
{
	char* str;
	sgs_Integer size;
	
	if( !stdlib_tostring( C, 0, &str, &size ) )
		_WARN( "set_caption() - unexpected arguments; function expects 1 argument: string" );
	
	SDL_WM_SetCaption( str, NULL );
}

/*
	the buffer control functions
*/
int ss_clear( SGS_CTX )
{
	sgs_Real col[ 4 ];
	if( sgs_StackSize( C ) != 1 ||
		!stdlib_tocolor4( C, 0, col ) )
		_WARN( "clear(): function expects 1 argument: array of 1-4 real values" )
	
	glClearColor( col[0], col[1], col[2], col[3] );
	glClear( GL_COLOR_BUFFER_BIT );
	return 0;
}
int ss_present( SGS_CTX )
{
	SDL_GL_SwapBuffers();
	return 0;
}

/*
	the "draw" function
	- draws
	>> usage examples
	draw({ shape = 'box', position = create_pos2d( 10, 10 ) }); // draws a white 1x1 box at position 10,10
	>> available parameters (by category):
	- geometry: type (enum), shape (enum), vertices (array), verts3d (array), vcolors (array), vtexcoords (array)
	- instances: position, positions, angle, angles, transform, transforms, color, colors
	- misc.: texture
	>> defaults (by category):
	- geometry: 1x1 box shape
	- instancing: !must have at least one position item known in advance
	- misc.: the "white" 1x1 texture (only preserves color data) or disabled texturing
	>> order of operations:
	- validate
	- set texture
	- for each instance
		- set instance data
		- draw call
	>> evaluation of passed arguments
	GEOMETRY:
	- first look for verts3d, then vertices; if found - check for type (if not found, ERROR), vcolors, colors, color and vtexcoords too
	- if none found, check for shape; if found - check for colors, then color
	- if none found, ERROR
	INSTANCE-TRANSFORM:
	- first check for transforms, then transform; if found - EXIT EARLY
	- if none found, check for positions, then position; if found - check for angles, then angle, then EXIT EARLY
	MISC:
	- check for texture
	>> data objects
	- texture is an OpenGL texture + some metadata // TODO
	>> tech
	- vertex arrays // TODO, currently get it out there with immediate mode
	>> intermediate storages
	- data loading functions will return additional values to specify if a buffer was created in the call
*/
int ss_draw( SGS_CTX )
{
	glBegin( GL_QUADS );
	glVertex2d( 100, 100 );
	glVertex2d( 200, 100 );
	glVertex2d( 200, 200 );
	glVertex2d( 100, 200 );
	glEnd();
}


sgs_RegIntConst sdl_ints[] =
{
	/* events */
	IC( SDL_ACTIVEEVENT ),
	IC( SDL_KEYDOWN ),
	IC( SDL_KEYUP ),
	IC( SDL_MOUSEMOTION ),
	IC( SDL_MOUSEBUTTONDOWN ),
	IC( SDL_MOUSEBUTTONUP ),
	IC( SDL_QUIT ),
	IC( SDL_VIDEORESIZE ),
	IC( SDL_VIDEOEXPOSE ),
};

sgs_RegFuncConst sdl_funcs[] =
{
	FN( sleep ),
	FN( set_video_mode ), FN( set_caption ),
	FN( clear ), FN( present ),
	FN( draw ),
};

int sgs_InitSDL( SGS_CTX )
{
	int ret;
	ret = sgs_RegIntConsts( C, sdl_ints, ARRAY_SIZE( sdl_ints ) );
	if( ret != SGS_SUCCESS ) return ret;
	ret = sgs_RegFuncConsts( C, sdl_funcs, ARRAY_SIZE( sdl_funcs ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	return SGS_SUCCESS;
}


int sgs_CreateSDLEvent( SGS_CTX, SDL_Event* event )
{
	int osz, ret;
	
	osz = sgs_StackSize( C );
	
	sgs_PushString( C, "type" );
	sgs_PushInt( C, event->type );
	
	switch( event->type )
	{
	case SDL_ACTIVEEVENT:
		sgs_PushString( C, "gain" );
		sgs_PushBool( C, event->active.gain );
		sgs_PushString( C, "state" );
		sgs_PushInt( C, event->active.state );
		break;
	
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		sgs_PushString( C, "state" );
		sgs_PushBool( C, event->key.state == SDL_PRESSED );
		sgs_PushString( C, "hwcode" );
		sgs_PushInt( C, event->key.keysym.scancode );
		sgs_PushString( C, "keycode" );
		sgs_PushInt( C, event->key.keysym.sym );
		sgs_PushString( C, "mod" );
		sgs_PushInt( C, event->key.keysym.mod );
		sgs_PushString( C, "unicode" );
		sgs_PushInt( C, event->key.keysym.unicode );
		break;
	
	case SDL_MOUSEMOTION:
		sgs_PushString( C, "buttons" );
		sgs_PushInt( C, event->motion.state );
		sgs_PushString( C, "button0" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON(1) );
		sgs_PushString( C, "button1" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON(2) );
		sgs_PushString( C, "button2" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON(3) );
		sgs_PushString( C, "x" );
		sgs_PushInt( C, event->motion.x );
		sgs_PushString( C, "y" );
		sgs_PushInt( C, event->motion.y );
		sgs_PushString( C, "xrel" );
		sgs_PushInt( C, event->motion.xrel );
		sgs_PushString( C, "yrel" );
		sgs_PushInt( C, event->motion.yrel );
		break;
	
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		sgs_PushString( C, "button" );
		sgs_PushInt( C, event->button.button );
		sgs_PushString( C, "state" );
		sgs_PushBool( C, event->button.state == SDL_PRESSED );
		sgs_PushString( C, "x" );
		sgs_PushInt( C, event->button.x );
		sgs_PushString( C, "y" );
		sgs_PushInt( C, event->button.y );
		break;
	
	case SDL_VIDEORESIZE:
		sgs_PushString( C, "w" );
		sgs_PushInt( C, event->resize.w );
		sgs_PushString( C, "h" );
		sgs_PushInt( C, event->resize.h );
		break;
	
	/* no more data for...
		SDL_QUIT
		SDL_VIDEOEXPOSE
	*/
	}
	
	ret = sgs_GlobalCall( C, "dict", sgs_StackSize( C ) - osz, 1 );
	if( ret != SGS_SUCCESS )
		sgs_Pop( C, sgs_StackSize( C ) - osz );
	return ret;
}
