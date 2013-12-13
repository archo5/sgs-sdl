
#include <math.h>

#include "ss_main.h"


#define ssGetProcAddress SDL_GL_GetProcAddress


#ifndef SS_USED3D
PFNGLBLENDEQUATIONPROC ss_glBlendEquation;
#endif


#define FN( f ) { #f, ss_##f }
#define IC( i ) { #i, i }
#define ICX( n, i ) { #n, i }
#define _WARN( err ) { sgs_Printf( C, SGS_WARNING, err ); return 0; }



int g_width = 0;
int g_height = 0;


#ifdef SS_USED3D
IDirect3D9* GD3D = NULL;
IDirect3DDevice9* GD3DDev = NULL;
D3DPRESENT_PARAMETERS GD3DPP;

void _ss_reset_states()
{
	IDirect3DDevice9_SetTextureStageState( GD3DDev, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	IDirect3DDevice9_SetTextureStageState( GD3DDev, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	IDirect3DDevice9_SetTextureStageState( GD3DDev, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	IDirect3DDevice9_SetTextureStageState( GD3DDev, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_LIGHTING, 0 );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_CULLMODE, D3DCULL_NONE );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_ZENABLE, 0 );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_ALPHABLENDENABLE, 1 );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	{
		float wm[ 16 ] = { 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1 };
		float vm[ 16 ] = { 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 100,  0, 0, 0, 1 };
		float pm[ 16 ] = { 2.0f/1024.0f, 0, 0, 0,  0, 2.0f/576.0f, 0, 0,  0, 0, 1.0f/999.0f, 1.0f/-999.0f,  0, 0, 0, 1 };
		IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_WORLD, (D3DMATRIX*) wm );
		IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_VIEW, (D3DMATRIX*) vm );
		IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_PROJECTION, (D3DMATRIX*) pm );
	}
}

int _ss_reset_device( SGS_CTX )
{
	D3DPRESENT_PARAMETERS npp;
	SDL_Event event;
	
	npp = GD3DPP;
	
	event.type = SDL_VIDEO_DEVICELOST;
	sgs_CreateSDLEvent( C, &event );
	sgs_GlobalCall( C, "on_event", 1, 0 );
	
	IDirect3DDevice9_Reset( GD3DDev, &npp );
	
	_ss_reset_states();
	
	event.type = SDL_VIDEO_DEVICERESET;
	sgs_CreateSDLEvent( C, &event );
	sgs_GlobalCall( C, "on_event", 1, 0 );
	
	return 1;
}

#else
void* GD3D = NULL;
void* GD3DDev = NULL;
#endif


int ss_sleep( SGS_CTX )
{
	sgs_Integer time;
	SGSFN( "sleep" );
	if( sgs_StackSize( C ) != 1 ||
		!sgs_ParseInt( C, 0, &time ) )
		_WARN( "function expects 1 argument: int" )
	
	SDL_Delay( time );
	return 0;
}

int ss_set_gl_attrib( SGS_CTX )
{
	sgs_Integer attr, val;
	SGSFN( "set_gl_attrib" );
	
	if( !sgs_ParseInt( C, 0, &attr ) || !sgs_ParseInt( C, 1, &val ) )
		_WARN( "function expects 2 arguments: int, int" )
	
	sgs_PushBool( C, SDL_GL_SetAttribute( attr, val ) == 0 );
	return 1;
}

#define SDL_VSYNC 0x10000

flag_string_item_t setvideomode_flags[] =
{
	{ "fullscreen", SDL_FULLSCREEN },
	{ "resizable", SDL_RESIZABLE },
	{ "noframe", SDL_NOFRAME },
	{ "vsync", SDL_VSYNC },
	FSI_LAST
};
int ss_set_video_mode( SGS_CTX )
{
	char* ts;
	int suc = 0, vsync;
	sgs_Integer w, h, b, f;
	sgs_SizeVal tss;
	
	UNUSED( vsync );
	
	SGSFN( "set_video_mode" );
	
	if( sgs_StackSize( C ) != 4 ||
		!sgs_ParseInt( C, 0, &w ) ||
		!sgs_ParseInt( C, 1, &h ) ||
		!sgs_ParseInt( C, 2, &b ) ||
		!sgs_ParseString( C, 3, &ts, &tss ) )
		_WARN( "function expects 4 arguments: int, int, int, string" )
	
	f = sgs_GetFlagString( C, 3, setvideomode_flags );
	vsync = ( f & SDL_VSYNC ) != 0;
	f &= ~SDL_VSYNC;
	
#ifdef SS_USED3D
	ZeroMemory( &GD3DPP, sizeof(GD3DPP) );
	GD3DPP.Windowed = 1;
	GD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	GD3DPP.EnableAutoDepthStencil = 1;
	GD3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	GD3DPP.hDeviceWindow = GetActiveWindow();
	GD3DPP.BackBufferWidth = w;
	GD3DPP.BackBufferHeight = h;
	GD3DPP.BackBufferFormat = b == 32 ? D3DFMT_X8R8G8B8 : D3DFMT_R5G6B5;
	GD3DPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	GD3DPP.PresentationInterval = vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
#else
	f |= SDL_OPENGL;
	SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, vsync ? 1 : 0 );
#endif
	
	suc = !!SDL_SetVideoMode( w, h, b, f );
	
#ifdef SS_USED3D
	if( !GD3D )
		GD3D = Direct3DCreate9( D3D_SDK_VERSION );
	
	if( !GD3DDev )
	{
		suc = !FAILED( IDirect3D9_CreateDevice( GD3D,
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetActiveWindow(),
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE, &GD3DPP, &GD3DDev ) );
		
		_ss_reset_states();
	}
	else
	{
		_ss_reset_device( C );
	}
	
	IDirect3DDevice9_BeginScene( GD3DDev );
	
#else
	ss_glBlendEquation = (PFNGLBLENDEQUATIONPROC) ssGetProcAddress( "glBlendEquation" );
	
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
	
#endif
	
	sgs_PushBool( C, suc );
	return 1;
}

int ss_list_video_modes( SGS_CTX )
{
	int i;
	char* ts;
	sgs_SizeVal tss;
	sgs_Integer f;
	SDL_Rect** modes;
	
	SGSFN( "list_video_modes" );
	
	if( !sgs_ParseString( C, 0, &ts, &tss ) )
		_WARN( "function expects 1 argument: string" )
	
	f = sgs_GetFlagString( C, 3, setvideomode_flags );
	f |= SDL_OPENGL;
	
	modes = SDL_ListModes( NULL, f );
	if( modes == (SDL_Rect**)0 )
	{
		sgs_PushBool( C, 0 );
		return 1;
	}
	if( modes == (SDL_Rect**)-1 )
	{
		sgs_PushBool( C, 1 );
		return 1;
	}
	for( i = 0; modes[ i ]; ++i )
	{
		sgs_PushInt( C, modes[ i ]->w );
		sgs_PushInt( C, modes[ i ]->h );
		sgs_PushArray( C, 2 );
	}
	sgs_PushArray( C, i );
	return 1;
}

int ss_set_caption( SGS_CTX )
{
	char* str;
	sgs_SizeVal size;
	
	SGSFN( "set_caption" );
	
	if( !sgs_ParseString( C, 0, &str, &size ) )
		_WARN( "function expects 1 argument: string" );
	
	SDL_WM_SetCaption( str, NULL );
	return 0;
}

int ss_show_cursor( SGS_CTX )
{
	int shc;
	SGSFN( "show_cursor" );
	if( !sgs_ParseBool( C, 0, &shc ) )
		_WARN( "function expects 1 argument: bool" )
	SDL_ShowCursor( shc ? SDL_ENABLE : SDL_DISABLE );
	return 0;
}

int ss_grab_input( SGS_CTX )
{
	SGSFN( "grab_input" );
	if( !sgs_StackSize( C ) )
	{
		sgs_PushBool( C, SDL_WM_GrabInput( SDL_GRAB_QUERY ) == SDL_GRAB_ON );
		return 1;
	}
	else
	{
		int grab;
		if( sgs_StackSize( C ) != 1 || !sgs_ParseBool( C, 0, &grab ) )
			_WARN( "function expects 1 argument: bool" )
		
		SDL_WM_GrabInput( grab ? SDL_GRAB_ON : SDL_GRAB_OFF );
		return 0;
	}
}

int ss_warp_mouse( SGS_CTX )
{
	sgs_Integer x, y;
	SGSFN( "warp_mouse" );
	if( !sgs_ParseInt( C, 0, &x ) ||
		!sgs_ParseInt( C, 1, &y ) )
		_WARN( "function expects 2 argument: int, int" )
	SDL_WarpMouse( (Uint16) x, (Uint16) y );
	return 0;
}

int ss_get_mouse_state( SGS_CTX )
{
	int x, y, btnmask;
	SGSFN( "get_mouse_state" );
	btnmask = SDL_GetMouseState( &x, &y );
	sgs_PushInt( C, x );
	sgs_PushInt( C, y );
	sgs_PushInt( C, btnmask );
	sgs_PushArray( C, 3 );
	return 1;
}

int ss_get_relative_mouse_state( SGS_CTX )
{
	int x, y, btnmask;
	SGSFN( "get_relative_mouse_state" );
	btnmask = SDL_GetRelativeMouseState( &x, &y );
	sgs_PushInt( C, x );
	sgs_PushInt( C, y );
	sgs_PushInt( C, btnmask );
	sgs_PushArray( C, 3 );
	return 1;
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
	
#ifndef SS_USED3D
	glClearDepth( 1.0f );
	glClearColor( col[0], col[1], col[2], col[3] );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
#else
	if( GD3DDev )
	{
		uint32_t cc = (((uint8_t)(col[3]*255))<<24) | (((uint8_t)(col[0]*255))<<16) |
			(((uint8_t)(col[1]*255))<<8) | (((uint8_t)(col[2]*255)));
		IDirect3DDevice9_Clear( GD3DDev, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, cc, 1.0f, 0 );
	}
#endif
	return 0;
}
int ss_present( SGS_CTX )
{
#ifndef SS_USED3D
	SDL_GL_SwapBuffers();
#else
	IDirect3DDevice9_EndScene( GD3DDev );
	if( IDirect3DDevice9_Present( GD3DDev, NULL, NULL, NULL, NULL ) == D3DERR_DEVICELOST )
	{
		if( IDirect3DDevice9_TestCooperativeLevel( GD3DDev ) == D3DERR_DEVICENOTRESET )
		{
			_ss_reset_device( C );
		}
	}
	IDirect3DDevice9_BeginScene( GD3DDev );
#endif
	return 0;
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
	
	IC( SDL_VIDEO_DEVICELOST ),
	IC( SDL_VIDEO_DEVICERESET ),

	/* keycodes */
	IC( SDLK_UNKNOWN ),
	IC( SDLK_FIRST ),
	IC( SDLK_BACKSPACE ),
	IC( SDLK_TAB ),
	IC( SDLK_CLEAR ),
	IC( SDLK_RETURN ),
	IC( SDLK_PAUSE ),
	IC( SDLK_ESCAPE ),
	IC( SDLK_SPACE ),
	IC( SDLK_EXCLAIM ),
	IC( SDLK_QUOTEDBL ),
	IC( SDLK_HASH ),
	IC( SDLK_DOLLAR ),
	IC( SDLK_AMPERSAND ),
	IC( SDLK_QUOTE ),
	IC( SDLK_LEFTPAREN ),
	IC( SDLK_RIGHTPAREN ),
	IC( SDLK_ASTERISK ),
	IC( SDLK_PLUS ),
	IC( SDLK_COMMA ),
	IC( SDLK_MINUS ),
	IC( SDLK_PERIOD ),
	IC( SDLK_SLASH ),
	IC( SDLK_0 ),
	IC( SDLK_1 ),
	IC( SDLK_2 ),
	IC( SDLK_3 ),
	IC( SDLK_4 ),
	IC( SDLK_5 ),
	IC( SDLK_6 ),
	IC( SDLK_7 ),
	IC( SDLK_8 ),
	IC( SDLK_9 ),
	IC( SDLK_COLON ),
	IC( SDLK_SEMICOLON ),
	IC( SDLK_LESS ),
	IC( SDLK_EQUALS ),
	IC( SDLK_GREATER ),
	IC( SDLK_QUESTION ),
	IC( SDLK_AT ),
	/*
	   Skip uppercase letters
	 */
	IC( SDLK_LEFTBRACKET ),
	IC( SDLK_BACKSLASH ),
	IC( SDLK_RIGHTBRACKET ),
	IC( SDLK_CARET ),
	IC( SDLK_UNDERSCORE ),
	IC( SDLK_BACKQUOTE ),
	IC( SDLK_a ),
	IC( SDLK_b ),
	IC( SDLK_c ),
	IC( SDLK_d ),
	IC( SDLK_e ),
	IC( SDLK_f ),
	IC( SDLK_g ),
	IC( SDLK_h ),
	IC( SDLK_i ),
	IC( SDLK_j ),
	IC( SDLK_k ),
	IC( SDLK_l ),
	IC( SDLK_m ),
	IC( SDLK_n ),
	IC( SDLK_o ),
	IC( SDLK_p ),
	IC( SDLK_q ),
	IC( SDLK_r ),
	IC( SDLK_s ),
	IC( SDLK_t ),
	IC( SDLK_u ),
	IC( SDLK_v ),
	IC( SDLK_w ),
	IC( SDLK_x ),
	IC( SDLK_y ),
	IC( SDLK_z ),
	/* second mapping, for consistency */
	ICX( SDLK_A, SDLK_a ),
	ICX( SDLK_B, SDLK_b ),
	ICX( SDLK_C, SDLK_c ),
	ICX( SDLK_D, SDLK_d ),
	ICX( SDLK_E, SDLK_e ),
	ICX( SDLK_F, SDLK_f ),
	ICX( SDLK_G, SDLK_g ),
	ICX( SDLK_H, SDLK_h ),
	ICX( SDLK_I, SDLK_i ),
	ICX( SDLK_J, SDLK_j ),
	ICX( SDLK_K, SDLK_k ),
	ICX( SDLK_L, SDLK_l ),
	ICX( SDLK_M, SDLK_m ),
	ICX( SDLK_N, SDLK_n ),
	ICX( SDLK_O, SDLK_o ),
	ICX( SDLK_P, SDLK_p ),
	ICX( SDLK_Q, SDLK_q ),
	ICX( SDLK_R, SDLK_r ),
	ICX( SDLK_S, SDLK_s ),
	ICX( SDLK_T, SDLK_t ),
	ICX( SDLK_U, SDLK_u ),
	ICX( SDLK_V, SDLK_v ),
	ICX( SDLK_W, SDLK_w ),
	ICX( SDLK_X, SDLK_x ),
	ICX( SDLK_Y, SDLK_y ),
	ICX( SDLK_Z, SDLK_z ),
	IC( SDLK_DELETE ),
	/* End of ASCII mapped keysyms */

	/* International keyboard syms */
	IC( SDLK_WORLD_0 ),		/* 0xA0 */
	IC( SDLK_WORLD_1 ),
	IC( SDLK_WORLD_2 ),
	IC( SDLK_WORLD_3 ),
	IC( SDLK_WORLD_4 ),
	IC( SDLK_WORLD_5 ),
	IC( SDLK_WORLD_6 ),
	IC( SDLK_WORLD_7 ),
	IC( SDLK_WORLD_8 ),
	IC( SDLK_WORLD_9 ),
	IC( SDLK_WORLD_10 ),
	IC( SDLK_WORLD_11 ),
	IC( SDLK_WORLD_12 ),
	IC( SDLK_WORLD_13 ),
	IC( SDLK_WORLD_14 ),
	IC( SDLK_WORLD_15 ),
	IC( SDLK_WORLD_16 ),
	IC( SDLK_WORLD_17 ),
	IC( SDLK_WORLD_18 ),
	IC( SDLK_WORLD_19 ),
	IC( SDLK_WORLD_20 ),
	IC( SDLK_WORLD_21 ),
	IC( SDLK_WORLD_22 ),
	IC( SDLK_WORLD_23 ),
	IC( SDLK_WORLD_24 ),
	IC( SDLK_WORLD_25 ),
	IC( SDLK_WORLD_26 ),
	IC( SDLK_WORLD_27 ),
	IC( SDLK_WORLD_28 ),
	IC( SDLK_WORLD_29 ),
	IC( SDLK_WORLD_30 ),
	IC( SDLK_WORLD_31 ),
	IC( SDLK_WORLD_32 ),
	IC( SDLK_WORLD_33 ),
	IC( SDLK_WORLD_34 ),
	IC( SDLK_WORLD_35 ),
	IC( SDLK_WORLD_36 ),
	IC( SDLK_WORLD_37 ),
	IC( SDLK_WORLD_38 ),
	IC( SDLK_WORLD_39 ),
	IC( SDLK_WORLD_40 ),
	IC( SDLK_WORLD_41 ),
	IC( SDLK_WORLD_42 ),
	IC( SDLK_WORLD_43 ),
	IC( SDLK_WORLD_44 ),
	IC( SDLK_WORLD_45 ),
	IC( SDLK_WORLD_46 ),
	IC( SDLK_WORLD_47 ),
	IC( SDLK_WORLD_48 ),
	IC( SDLK_WORLD_49 ),
	IC( SDLK_WORLD_50 ),
	IC( SDLK_WORLD_51 ),
	IC( SDLK_WORLD_52 ),
	IC( SDLK_WORLD_53 ),
	IC( SDLK_WORLD_54 ),
	IC( SDLK_WORLD_55 ),
	IC( SDLK_WORLD_56 ),
	IC( SDLK_WORLD_57 ),
	IC( SDLK_WORLD_58 ),
	IC( SDLK_WORLD_59 ),
	IC( SDLK_WORLD_60 ),
	IC( SDLK_WORLD_61 ),
	IC( SDLK_WORLD_62 ),
	IC( SDLK_WORLD_63 ),
	IC( SDLK_WORLD_64 ),
	IC( SDLK_WORLD_65 ),
	IC( SDLK_WORLD_66 ),
	IC( SDLK_WORLD_67 ),
	IC( SDLK_WORLD_68 ),
	IC( SDLK_WORLD_69 ),
	IC( SDLK_WORLD_70 ),
	IC( SDLK_WORLD_71 ),
	IC( SDLK_WORLD_72 ),
	IC( SDLK_WORLD_73 ),
	IC( SDLK_WORLD_74 ),
	IC( SDLK_WORLD_75 ),
	IC( SDLK_WORLD_76 ),
	IC( SDLK_WORLD_77 ),
	IC( SDLK_WORLD_78 ),
	IC( SDLK_WORLD_79 ),
	IC( SDLK_WORLD_80 ),
	IC( SDLK_WORLD_81 ),
	IC( SDLK_WORLD_82 ),
	IC( SDLK_WORLD_83 ),
	IC( SDLK_WORLD_84 ),
	IC( SDLK_WORLD_85 ),
	IC( SDLK_WORLD_86 ),
	IC( SDLK_WORLD_87 ),
	IC( SDLK_WORLD_88 ),
	IC( SDLK_WORLD_89 ),
	IC( SDLK_WORLD_90 ),
	IC( SDLK_WORLD_91 ),
	IC( SDLK_WORLD_92 ),
	IC( SDLK_WORLD_93 ),
	IC( SDLK_WORLD_94 ),
	IC( SDLK_WORLD_95 ),		/* 0xFF */

	/* Numeric keypad */
	IC( SDLK_KP0 ),
	IC( SDLK_KP1 ),
	IC( SDLK_KP2 ),
	IC( SDLK_KP3 ),
	IC( SDLK_KP4 ),
	IC( SDLK_KP5 ),
	IC( SDLK_KP6 ),
	IC( SDLK_KP7 ),
	IC( SDLK_KP8 ),
	IC( SDLK_KP9 ),
	IC( SDLK_KP_PERIOD ),
	IC( SDLK_KP_DIVIDE ),
	IC( SDLK_KP_MULTIPLY ),
	IC( SDLK_KP_MINUS ),
	IC( SDLK_KP_PLUS ),
	IC( SDLK_KP_ENTER ),
	IC( SDLK_KP_EQUALS ),

	/* Arrows + Home/End pad */
	IC( SDLK_UP ),
	IC( SDLK_DOWN ),
	IC( SDLK_RIGHT ),
	IC( SDLK_LEFT ),
	IC( SDLK_INSERT ),
	IC( SDLK_HOME ),
	IC( SDLK_END ),
	IC( SDLK_PAGEUP ),
	IC( SDLK_PAGEDOWN ),

	/* Function keys */
	IC( SDLK_F1 ),
	IC( SDLK_F2 ),
	IC( SDLK_F3 ),
	IC( SDLK_F4 ),
	IC( SDLK_F5 ),
	IC( SDLK_F6 ),
	IC( SDLK_F7 ),
	IC( SDLK_F8 ),
	IC( SDLK_F9 ),
	IC( SDLK_F10 ),
	IC( SDLK_F11 ),
	IC( SDLK_F12 ),
	IC( SDLK_F13 ),
	IC( SDLK_F14 ),
	IC( SDLK_F15 ),

	/* Key state modifier keys */
	IC( SDLK_NUMLOCK ),
	IC( SDLK_CAPSLOCK ),
	IC( SDLK_SCROLLOCK ),
	IC( SDLK_RSHIFT ),
	IC( SDLK_LSHIFT ),
	IC( SDLK_RCTRL ),
	IC( SDLK_LCTRL ),
	IC( SDLK_RALT ),
	IC( SDLK_LALT ),
	IC( SDLK_RMETA ),
	IC( SDLK_LMETA ),
	IC( SDLK_LSUPER ),		/* Left "Windows" key */
	IC( SDLK_RSUPER ),		/* Right "Windows" key */
	IC( SDLK_MODE ),		/* "Alt Gr" key */
	IC( SDLK_COMPOSE ),		/* Multi-key compose key */

	/* Miscellaneous function keys */
	IC( SDLK_HELP ),
	IC( SDLK_PRINT ),
	IC( SDLK_SYSREQ ),
	IC( SDLK_BREAK ),
	IC( SDLK_MENU ),
	IC( SDLK_POWER ),		/* Power Macintosh power key */
	IC( SDLK_EURO ),		/* Some european keyboards */
	IC( SDLK_UNDO ),		/* Atari keyboard has Undo */

	/* Add any other keys here */

	IC( SDLK_LAST ),

	/* key modifier flags */
	IC( KMOD_NONE ),
	IC( KMOD_NUM ),
	IC( KMOD_CAPS ),
	IC( KMOD_LCTRL ),
	IC( KMOD_RCTRL ),
	IC( KMOD_RSHIFT ),
	IC( KMOD_LSHIFT ),
	IC( KMOD_RALT ),
	IC( KMOD_LALT ),
	IC( KMOD_CTRL ),
	IC( KMOD_SHIFT ),
	IC( KMOD_ALT ),
	
	/* GL attributes */
	IC( SDL_GL_RED_SIZE ),
	IC( SDL_GL_GREEN_SIZE ),
	IC( SDL_GL_BLUE_SIZE ),
	IC( SDL_GL_ALPHA_SIZE ),
	IC( SDL_GL_BUFFER_SIZE ),
	IC( SDL_GL_DOUBLEBUFFER ),
	IC( SDL_GL_DEPTH_SIZE ),
	IC( SDL_GL_STENCIL_SIZE ),
	IC( SDL_GL_ACCUM_RED_SIZE ),
	IC( SDL_GL_ACCUM_GREEN_SIZE ),
	IC( SDL_GL_ACCUM_BLUE_SIZE ),
	IC( SDL_GL_ACCUM_ALPHA_SIZE ),
	IC( SDL_GL_STEREO ),
	IC( SDL_GL_MULTISAMPLEBUFFERS ),
	IC( SDL_GL_MULTISAMPLESAMPLES ),
	IC( SDL_GL_ACCELERATED_VISUAL ),
	/* SDL 1.3?
	IC( SDL_GL_CONTEXT_MAJOR_VERSION ),
	IC( SDL_GL_CONTEXT_MINOR_VERSION ),
	*/
};

sgs_RegFuncConst sdl_funcs[] =
{
	FN( sleep ),
	FN( set_gl_attrib ), FN( set_video_mode ), FN( list_video_modes ),
	FN( set_caption ), FN( show_cursor ),
	FN( grab_input ), FN( warp_mouse ),
	FN( get_mouse_state ), FN( get_relative_mouse_state ),
	FN( clear ), FN( present ),
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


void sgs_FreeGraphics( SGS_CTX )
{
#ifdef SS_USED3D
	IDirect3DDevice9_Release( GD3DDev );
	IDirect3D9_Release( GD3D );
#endif
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
#ifdef SS_USED3D
		if( GD3DPP.BackBufferWidth != event->resize.w || GD3DPP.BackBufferHeight != event->resize.h )
		{
			GD3DPP.BackBufferWidth = event->resize.w;
			GD3DPP.BackBufferHeight = event->resize.h;
			_ss_reset_device( C );
		}
#else
		glViewport( 0, 0, event->resize.w, event->resize.h );
#endif
		g_width = event->resize.w;
		g_height = event->resize.h;
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
	
	ret = sgs_PushDict( C, sgs_StackSize( C ) - osz );
	if( ret != SGS_SUCCESS )
		sgs_Pop( C, sgs_StackSize( C ) - osz );
	return ret;
}
