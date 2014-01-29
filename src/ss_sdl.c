
#include <math.h>

#include <SDL2/SDL_syswm.h>

#include "ss_main.h"


#define FN( f ) { "SS_" #f, SS_##f }
#define IC( i ) { #i, i }
#define IC_SDL( i ) { "SDL_" #i, i }
#define ICX( n, i ) { #n, i }
#define _WARN( err ) { sgs_Printf( C, SGS_WARNING, err ); return 0; }



extern SS_RenderInterface GRI_GL;
#ifdef SS_USED3D
extern SS_RenderInterface GRI_D3D9;
#endif

static SS_RenderInterface* ri_pick( int id )
{
	if( id == SS_RENDERER_OPENGL ) return &GRI_GL;
#ifdef SS_USED3D
	if( id == SS_RENDERER_DIRECT3D9 ) return &GRI_D3D9;
#endif
	return NULL;
}

static void ri_init()
{
	GRI_GL.init();
#ifdef SS_USED3D
	GRI_D3D9.init();
#endif
}

static void ri_free()
{
	GRI_GL.free();
#ifdef SS_USED3D
	GRI_D3D9.free();
#endif
}



int SS_GetPlatformInfo( SGS_CTX )
{
	SGSFN( "SS_GetPlatformInfo" );
	sgs_SetStackSize( C, 0 );
	sgs_PushString( C, "name" ); sgs_PushString( C, SDL_GetPlatform() );
	sgs_PushString( C, "cpu_cache_line_size" ); sgs_PushInt( C, SDL_GetCPUCacheLineSize() );
	sgs_PushString( C, "cpu_count" ); sgs_PushInt( C, SDL_GetCPUCount() );
	sgs_PushString( C, "ram_size" ); sgs_PushInt( C, SDL_GetSystemRAM() );
	sgs_PushString( C, "has_3dnow" ); sgs_PushBool( C, SDL_Has3DNow() );
	sgs_PushString( C, "has_altivec" ); sgs_PushBool( C, SDL_HasAltiVec() );
	sgs_PushString( C, "has_mmx" ); sgs_PushBool( C, SDL_HasMMX() );
	sgs_PushString( C, "has_rdtsc" ); sgs_PushBool( C, SDL_HasRDTSC() );
	sgs_PushString( C, "has_sse" ); sgs_PushBool( C, SDL_HasSSE() );
	sgs_PushString( C, "has_sse2" ); sgs_PushBool( C, SDL_HasSSE2() );
	sgs_PushString( C, "has_sse3" ); sgs_PushBool( C, SDL_HasSSE3() );
	sgs_PushString( C, "has_sse41" ); sgs_PushBool( C, SDL_HasSSE41() );
	sgs_PushString( C, "has_sse42" ); sgs_PushBool( C, SDL_HasSSE42() );
	sgs_PushDict( C, sgs_StackSize( C ) );
	return 1;
}

int SS_GetPowerInfo( SGS_CTX )
{
	int secs, pct;
	SGSFN( "SS_GetPowerInfo" );
	sgs_SetStackSize( C, 0 );
	sgs_PushString( C, "state" ); sgs_PushInt( C, SDL_GetPowerInfo( &secs, &pct ) );
	sgs_PushString( C, "seconds" ); sgs_PushInt( C, secs );
	sgs_PushString( C, "percentage" ); sgs_PushInt( C, pct );
	sgs_PushDict( C, sgs_StackSize( C ) );
	return 1;
}


int SS_HasClipboardText( SGS_CTX )
{
	SGSFN( "SS_HasClipboardText" );
	sgs_PushBool( C, SDL_HasClipboardText() );
	return 1;
}

int SS_GetClipboardText( SGS_CTX )
{
	char* text;
	SGSFN( "SS_GetClipboardText" );
	text = SDL_GetClipboardText();
	if( !text )
		return sgs_Printf( C, SGS_WARNING, "failed to read from the clipboard: %s", SDL_GetError() );
	sgs_PushString( C, text );
	SDL_free( text );
	return 1;
}

int SS_SetClipboardText( SGS_CTX )
{
	int ret;
	char* text;
	SGSFN( "SS_SetClipboardText" );
	if( !sgs_LoadArgs( C, "s", &text ) )
		return 0;
	ret = SDL_SetClipboardText( text ) >= 0;
	if( !ret )
		sgs_Printf( C, SGS_WARNING, "failed to write to the clipboard: %s", SDL_GetError() );
	sgs_PushBool( C, ret );
	return 1;
}


int SS_Sleep( SGS_CTX )
{
	sgs_Integer time;
	SGSFN( "SS_Sleep" );
	if( sgs_StackSize( C ) != 1 ||
		!sgs_ParseInt( C, 0, &time ) )
		_WARN( "function expects 1 argument: int" )
	
	SDL_Delay( time );
	return 0;
}

int SS_EnableScreenSaver( SGS_CTX ){ SGSFN( "SS_EnableScreenSaver" ); SDL_EnableScreenSaver(); return 0; }
int SS_DisableScreenSaver( SGS_CTX ){ SGSFN( "SS_DisableScreenSaver" ); SDL_DisableScreenSaver(); return 0; }
int SS_IsScreenSaverEnabled( SGS_CTX ){ SGSFN( "SS_IsScreenSaverEnabled" ); sgs_PushBool( C, SDL_IsScreenSaverEnabled() ); return 1; }

int SS_GetVideoDrivers( SGS_CTX )
{
	int i, num;
	SGSFN( "SS_GetVideoDrivers" );
	num = SDL_GetNumVideoDrivers();
	for( i = 0; i < num; ++i )
		sgs_PushString( C, SDL_GetVideoDriver( i ) );
	sgs_PushArray( C, num );
	return 1;
}



#define DM_HDR SDL_DisplayMode* DM = (SDL_DisplayMode*) data->data

static int ss_displaymode_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* str;
	DM_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseString( C, 0, &str, NULL ) )
	{
		if( !strcmp( str, "format" ) ){ sgs_PushInt( C, DM->format ); return SGS_SUCCESS; }
		if( !strcmp( str, "w" ) ){ sgs_PushInt( C, DM->w ); return SGS_SUCCESS; }
		if( !strcmp( str, "h" ) ){ sgs_PushInt( C, DM->h ); return SGS_SUCCESS; }
		if( !strcmp( str, "refresh_rate" ) ){ sgs_PushInt( C, DM->refresh_rate ); return SGS_SUCCESS; }
		if( !strcmp( str, "driverdata" ) ){ sgs_PushPtr( C, DM->driverdata ); return SGS_SUCCESS; }
	}
	
	return SGS_ENOTFND;
}

static int ss_displaymode_setindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* str;
	DM_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseString( C, 0, &str, NULL ) )
	{
		if( !strcmp( str, "format" ) ){ sgs_Int val; if( sgs_ParseInt( C, 1, &val ) ){ DM->format = val; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "w" ) ){ sgs_Int val; if( sgs_ParseInt( C, 1, &val ) ){ DM->w = val; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "h" ) ){ sgs_Int val; if( sgs_ParseInt( C, 1, &val ) ){ DM->h = val; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "refresh_rate" ) ){ sgs_Int val; if( sgs_ParseInt( C, 1, &val ) ){ DM->refresh_rate = val; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "driverdata" ) ){ void* val; if( sgs_ParsePtr( C, 1, &val ) ){ DM->driverdata = val; return SGS_SUCCESS; } return SGS_EINVAL; }
	}
	
	return SGS_ENOTFND;
}

static int ss_displaymode_dump( SGS_CTX, sgs_VarObj* data, int maxdepth )
{
	char bfr[ 256 ];
	DM_HDR;
	UNUSED( maxdepth );
	
	sprintf( bfr, "SDL_DisplayMode(format=%u, w=%d, h=%d, refresh_rate=%d, driverdata=%p)", (unsigned) DM->format, DM->w, DM->h, DM->refresh_rate, DM->driverdata );
	sgs_PushString( C, bfr );
	return SGS_SUCCESS;
}

static int ss_displaymode_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_VT_STRING )
	{
		return ss_displaymode_dump( C, data, 1 );
	}
	if( type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "SDL_DisplayMode" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static sgs_ObjCallback ss_displaymode_iface[] =
{
	SGS_OP_GETINDEX, ss_displaymode_getindex,
	SGS_OP_SETINDEX, ss_displaymode_setindex,
	SGS_OP_CONVERT, ss_displaymode_convert,
	SGS_OP_DUMP, ss_displaymode_dump,
	SGS_OP_END
};

static void ss_PushDisplayMode( SGS_CTX, SDL_DisplayMode* dm )
{
	SDL_DisplayMode* mode = (SDL_DisplayMode*) sgs_PushObjectIPA( C, sizeof(SDL_DisplayMode), ss_displaymode_iface );
	memcpy( mode, dm, sizeof(SDL_DisplayMode) );
}
/* UNUSED
static int ss_ParseDisplayMode( SGS_CTX, sgs_StkIdx item, SDL_DisplayMode** dm )
{
	if( sgs_IsObject( C, item, ss_displaymode_iface ) )
	{
		if( dm )
			*dm = (SDL_DisplayMode*) sgs_GetObjectData( C, item );
		return 1;
	}
	return 0;
}
*/
static int ss_acf_DisplayMode( SGS_CTX, int item, sgs_VAList* args, int flags )
{
	if( sgs_IsObject( C, item, ss_displaymode_iface ) )
	{
		if( !( flags & SGS_LOADARG_NOWRITE ) )
			*va_arg( args->args, SDL_DisplayMode** ) = (SDL_DisplayMode*) sgs_GetObjectData( C, item );
		return 1;
	}
	return 0;
}

static int SS_DisplayMode( SGS_CTX )
{
	SDL_DisplayMode dm;
	SGSFN( "SS_DisplayMode" );
	memset( &dm, 0, sizeof(dm) );
	ss_PushDisplayMode( C, &dm );
	return 1;
}



static int SS_GetNumDisplays( SGS_CTX ){ SGSFN( "SS_GetNumDisplays" ); sgs_PushInt( C, SDL_GetNumVideoDisplays() ); return 1; }
static int SS_GetDisplayName( SGS_CTX )
{
	sgs_Int i;
	SGSFN( "SS_GetDisplayName" );
	if( !sgs_LoadArgs( C, "i", &i ) )
		return 0;
	sgs_PushString( C, SDL_GetDisplayName( i ) );
	return 1;
}
static int SS_GetNumDisplayModes( SGS_CTX )
{
	int num;
	sgs_Int i;
	SGSFN( "SS_GetNumDisplayModes" );
	if( !sgs_LoadArgs( C, "i", &i ) )
		return 0;
	
	if( 0 > ( num = SDL_GetNumDisplayModes( i ) ) )
		return sgs_Printf( C, SGS_WARNING, "failed to get number of display modes for display #%d: %s", (int) i, SDL_GetError() );
	
	sgs_PushInt( C, num );
	return 1;
}
static int SS_GetDisplayMode( SGS_CTX )
{
	sgs_Int i, mid;
	SDL_DisplayMode mode;
	SGSFN( "SS_GetDisplayMode" );
	if( !sgs_LoadArgs( C, "ii", &i, &mid ) )
		return 0;
	
	if( 0 != SDL_GetDisplayMode( i, mid, &mode ) )
		return sgs_Printf( C, SGS_WARNING, "failed to get display mode #%d for display #%d: %s", (int) mid, (int) i, SDL_GetError() );
	
	ss_PushDisplayMode( C, &mode );
	return 1;
}
static int SS_GetDisplayModes( SGS_CTX )
{
	int i, num;
	sgs_Int did;
	SDL_DisplayMode mode;
	SGSFN( "SS_GetDisplayModes" );
	if( !sgs_LoadArgs( C, "i", &did ) )
		return 0;
	
	if( 0 > ( num = SDL_GetNumDisplayModes( did ) ) )
		return sgs_Printf( C, SGS_WARNING, "failed to get number of display modes for display #%d: %s", (int) did, SDL_GetError() );
	
	for( i = 0; i < num; ++i )
	{
		if( 0 != SDL_GetDisplayMode( did, i, &mode ) )
			return sgs_Printf( C, SGS_WARNING, "failed to get display mode #%d for display #%d: %s", i, (int) did, SDL_GetError() );
		ss_PushDisplayMode( C, &mode );
	}
	sgs_PushArray( C, num );
	return 1;
}
static int SS_GetDisplayBounds( SGS_CTX )
{
	sgs_Int i;
	SDL_Rect rect;
	SGSFN( "SS_GetDisplayBounds" );
	if( !sgs_LoadArgs( C, "i", &i ) )
		return 0;
	
	if( 0 != SDL_GetDisplayBounds( i, &rect ) )
		return sgs_Printf( C, SGS_WARNING, "failed to get display #%d bounds: %s", (int) i, SDL_GetError() );
	
	sgs_PushString( C, "x" );
	sgs_PushInt( C, rect.x );
	sgs_PushString( C, "y" );
	sgs_PushInt( C, rect.y );
	sgs_PushString( C, "w" );
	sgs_PushInt( C, rect.w );
	sgs_PushString( C, "h" );
	sgs_PushInt( C, rect.h );
	sgs_PushDict( C, 8 );
	return 1;
}
static int SS_GetClosestDisplayMode( SGS_CTX )
{
	sgs_Int i;
	SDL_DisplayMode mode, *modeIn;
	SGSFN( "SS_GetClosestDisplayMode" );
	if( !sgs_LoadArgs( C, "ix", &i, ss_acf_DisplayMode, &modeIn ) )
		return 0;
	
	if( !SDL_GetClosestDisplayMode( i, modeIn, &mode ) )
		return 0;
	
	ss_PushDisplayMode( C, &mode );
	return 1;
}
static int SS_GetCurrentDisplayMode( SGS_CTX )
{
	sgs_Int i;
	SDL_DisplayMode mode;
	SGSFN( "SS_GetCurrentDisplayMode" );
	if( !sgs_LoadArgs( C, "i", &i ) )
		return 0;
	
	if( 0 != SDL_GetCurrentDisplayMode( i, &mode ) )
		return sgs_Printf( C, SGS_WARNING, "failed to get current display mode for display #%d: %s", (int) i, SDL_GetError() );
	
	ss_PushDisplayMode( C, &mode );
	return 1;
}
static int SS_GetDesktopDisplayMode( SGS_CTX )
{
	sgs_Int i;
	SDL_DisplayMode mode;
	SGSFN( "SS_GetDesktopDisplayMode" );
	if( !sgs_LoadArgs( C, "i", &i ) )
		return 0;
	
	if( 0 != SDL_GetDesktopDisplayMode( i, &mode ) )
		return sgs_Printf( C, SGS_WARNING, "failed to get desktop display mode for display #%d: %s", (int) i, SDL_GetError() );
	
	ss_PushDisplayMode( C, &mode );
	return 1;
}



typedef struct _ss_window
{
	SDL_Window* window;
	SS_RenderInterface* riface;
	SS_Renderer* renderer;
}
ss_window;

#define WND_HDR ss_window* W = (ss_window*) data->data;
#define WND_IHDR( funcname ) \
	int method_call = sgs_Method( C ); \
	sgs_FuncName( C, method_call ? "window." #funcname : "window_" #funcname ); \
	if( !sgs_IsObject( C, 0, ss_window_iface ) ) \
		return sgs_ArgErrorExt( C, 0, method_call, "window", "" ); \
	ss_window* W = (ss_window*) sgs_GetObjectData( C, 0 );

SGS_DECLARE sgs_ObjCallback ss_window_iface[];

static int ss_windowI_show( SGS_CTX )
{
	WND_IHDR( show );
	SDL_ShowWindow( W->window );
	return 0;
}

static int ss_windowI_hide( SGS_CTX )
{
	WND_IHDR( hide );
	SDL_HideWindow( W->window );
	return 0;
}

static int ss_windowI_minimize( SGS_CTX )
{
	WND_IHDR( minimize );
	SDL_MinimizeWindow( W->window );
	return 0;
}

static int ss_windowI_maximize( SGS_CTX )
{
	WND_IHDR( maximize );
	SDL_MaximizeWindow( W->window );
	return 0;
}

static int ss_windowI_restore( SGS_CTX )
{
	WND_IHDR( restore );
	SDL_RestoreWindow( W->window );
	return 0;
}

static int ss_windowI_raise( SGS_CTX )
{
	WND_IHDR( raise );
	SDL_RaiseWindow( W->window );
	return 0;
}

static int ss_windowI_setPosition( SGS_CTX )
{
	sgs_Int x, y;
	WND_IHDR( setPosition );
	if( !sgs_LoadArgs( C, "@>ii", &x, &y ) )
		return 0;
	SDL_SetWindowPosition( W->window, x, y );
	return 0;
}

static int ss_windowI_setSize( SGS_CTX )
{
	sgs_Int w, h;
	WND_IHDR( setSize );
	if( !sgs_LoadArgs( C, "@>ii", &w, &h ) )
		return 0;
	SDL_SetWindowSize( W->window, w, h );
	return 0;
}

static int ss_windowI_setMaxSize( SGS_CTX )
{
	sgs_Int w, h;
	WND_IHDR( setMaxSize );
	if( !sgs_LoadArgs( C, "@>ii", &w, &h ) )
		return 0;
	SDL_SetWindowMaximumSize( W->window, w, h );
	return 0;
}

static int ss_windowI_setMinSize( SGS_CTX )
{
	sgs_Int w, h;
	WND_IHDR( setMinSize );
	if( !sgs_LoadArgs( C, "@>ii", &w, &h ) )
		return 0;
	SDL_SetWindowMinimumSize( W->window, w, h );
	return 0;
}

static int ss_windowI_warpMouse( SGS_CTX )
{
	sgs_Int x, y;
	WND_IHDR( warpMouse );
	if( !sgs_LoadArgs( C, "@>ii", &x, &y ) )
		return 0;
	SDL_WarpMouseInWindow( W->window, x, y );
	return 0;
}

static int ss_windowI_initRenderer( SGS_CTX )
{
	sgs_Int renderer = SS_RENDERER_DONTCARE, version = SS_RENDERER_DONTCARE, flags = 0;
	SS_RenderInterface* riface;
	SS_Renderer* R;
	WND_IHDR( initRenderer );
	
	if( !sgs_LoadArgs( C, "@>|iii", &renderer, &version, &flags ) )
		return 0;
	
	if( W->riface )
		return sgs_Printf( C, SGS_WARNING, "free the current renderer to initialize a new one" );
	
	if( renderer != SS_RENDERER_DONTCARE &&
		renderer != SS_RENDERER_OPENGL &&
		renderer != SS_RENDERER_DIRECT3D9 )
		return sgs_Printf( C, SGS_WARNING, "invalid renderer specified" );
	
	if( renderer == SS_RENDERER_DONTCARE )
#ifdef SS_USED3D
		renderer = SS_RENDERER_DIRECT3D9;
#else
		renderer = SS_RENDERER_OPENGL;
#endif
	
	riface = ri_pick( renderer );
	if( !riface )
		return sgs_Printf( C, SGS_WARNING, "specified renderer is unavailable" );
	
	R = riface->create( W->window, version, flags );
	if( !R )
		return sgs_Printf( C, SGS_WARNING, "failed to create the renderer: %s", riface->last_error );
	
	W->riface = riface;
	W->renderer = R;
	
	ss_MakeCurrent( riface, R );
	
	sgs_PushBool( C, 1 );
	return 1;
}

static int ss_windowI_makeCurrent( SGS_CTX )
{
	WND_IHDR( makeCurrent );
	if( W->riface && W->renderer )
		ss_MakeCurrent( W->riface, W->renderer );
	
	sgs_PushBool( C, W->riface && W->renderer );
	return 1;
}


static int ss_window_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* str;
	WND_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseString( C, 0, &str, NULL ) )
	{
		/* function properties */
		if( !strcmp( str, "show" ) ){ sgs_PushCFunction( C, ss_windowI_show ); return SGS_SUCCESS; }
		if( !strcmp( str, "hide" ) ){ sgs_PushCFunction( C, ss_windowI_hide ); return SGS_SUCCESS; }
		if( !strcmp( str, "minimize" ) ){ sgs_PushCFunction( C, ss_windowI_minimize ); return SGS_SUCCESS; }
		if( !strcmp( str, "maximize" ) ){ sgs_PushCFunction( C, ss_windowI_maximize ); return SGS_SUCCESS; }
		if( !strcmp( str, "restore" ) ){ sgs_PushCFunction( C, ss_windowI_restore ); return SGS_SUCCESS; }
		if( !strcmp( str, "raise" ) ){ sgs_PushCFunction( C, ss_windowI_raise ); return SGS_SUCCESS; }
		if( !strcmp( str, "setPosition" ) ){ sgs_PushCFunction( C, ss_windowI_setPosition ); return SGS_SUCCESS; }
		if( !strcmp( str, "setSize" ) ){ sgs_PushCFunction( C, ss_windowI_setSize ); return SGS_SUCCESS; }
		if( !strcmp( str, "setMaxSize" ) ){ sgs_PushCFunction( C, ss_windowI_setMaxSize ); return SGS_SUCCESS; }
		if( !strcmp( str, "setMinSize" ) ){ sgs_PushCFunction( C, ss_windowI_setMinSize ); return SGS_SUCCESS; }
		if( !strcmp( str, "warpMouse" ) ){ sgs_PushCFunction( C, ss_windowI_warpMouse ); return SGS_SUCCESS; }
		if( !strcmp( str, "initRenderer" ) ){ sgs_PushCFunction( C, ss_windowI_initRenderer ); return SGS_SUCCESS; }
		if( !strcmp( str, "makeCurrent" ) ){ sgs_PushCFunction( C, ss_windowI_makeCurrent ); return SGS_SUCCESS; }
		
		/* data properties */
		if( !strcmp( str, "brightness" ) ){ sgs_PushReal( C, SDL_GetWindowBrightness( W->window ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "displayIndex" ) ){ sgs_PushInt( C, SDL_GetWindowDisplayIndex( W->window ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "displayMode" ) )
		{
			SDL_DisplayMode mode;
			memset( &mode, 0, sizeof(mode) );
			if( 0 == SDL_GetWindowDisplayMode( W->window, &mode ) )
			{
				ss_PushDisplayMode( C, &mode );
			}
			else
			{
				sgs_PushNull( C );
				sgs_Printf( C, SGS_WARNING, "failed to get display mode: %s", SDL_GetError() );
			}
			return SGS_SUCCESS;
		}
		if( !strcmp( str, "flags" ) ){ sgs_PushInt( C, SDL_GetWindowFlags( W->window ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "grab" ) ){ sgs_PushBool( C, SDL_GetWindowGrab( W->window ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "id" ) ){ sgs_PushInt( C, SDL_GetWindowID( W->window ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "maxSize" ) )
		{
			int w, h;
			SDL_GetWindowMaximumSize( W->window, &w, &h );
			sgs_PushInt( C, w );
			sgs_PushInt( C, h );
			sgs_PushArray( C, 2 );
			return SGS_SUCCESS;
		}
		if( !strcmp( str, "maxWidth" ) ){ int w, h; SDL_GetWindowMaximumSize( W->window, &w, &h ); sgs_PushInt( C, w ); return SGS_SUCCESS; }
		if( !strcmp( str, "maxHeight" ) ){ int w, h; SDL_GetWindowMaximumSize( W->window, &w, &h ); sgs_PushInt( C, h ); return SGS_SUCCESS; }
		if( !strcmp( str, "minSize" ) )
		{
			int w, h;
			SDL_GetWindowMinimumSize( W->window, &w, &h );
			sgs_PushInt( C, w );
			sgs_PushInt( C, h );
			sgs_PushArray( C, 2 );
			return SGS_SUCCESS;
		}
		if( !strcmp( str, "minWidth" ) ){ int w, h; SDL_GetWindowMinimumSize( W->window, &w, &h ); sgs_PushInt( C, w ); return SGS_SUCCESS; }
		if( !strcmp( str, "minHeight" ) ){ int w, h; SDL_GetWindowMinimumSize( W->window, &w, &h ); sgs_PushInt( C, h ); return SGS_SUCCESS; }
		if( !strcmp( str, "pixelFormat" ) ){ sgs_PushInt( C, SDL_GetWindowPixelFormat( W->window ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "position" ) )
		{
			int x, y;
			SDL_GetWindowPosition( W->window, &x, &y );
			sgs_PushInt( C, x );
			sgs_PushInt( C, y );
			sgs_PushArray( C, 2 );
			return SGS_SUCCESS;
		}
		if( !strcmp( str, "x" ) ){ int x, y; SDL_GetWindowPosition( W->window, &x, &y ); sgs_PushInt( C, x ); return SGS_SUCCESS; }
		if( !strcmp( str, "y" ) ){ int x, y; SDL_GetWindowPosition( W->window, &x, &y ); sgs_PushInt( C, y ); return SGS_SUCCESS; }
		if( !strcmp( str, "size" ) )
		{
			int w, h;
			SDL_GetWindowSize( W->window, &w, &h );
			sgs_PushInt( C, w );
			sgs_PushInt( C, h );
			sgs_PushArray( C, 2 );
			return SGS_SUCCESS;
		}
		if( !strcmp( str, "width" ) ){ int w, h; SDL_GetWindowSize( W->window, &w, &h ); sgs_PushInt( C, w ); return SGS_SUCCESS; }
		if( !strcmp( str, "height" ) ){ int w, h; SDL_GetWindowSize( W->window, &w, &h ); sgs_PushInt( C, h ); return SGS_SUCCESS; }
		if( !strcmp( str, "title" ) ){ sgs_PushString( C, SDL_GetWindowTitle( W->window ) ); return SGS_SUCCESS; }
		
		/* special properties */
		if( !strcmp( str, "nativeWindow" ) )
		{
			SDL_SysWMinfo sysinfo;
			SDL_VERSION( &sysinfo.version );
			if( SDL_GetWindowWMInfo( W->window, &sysinfo ) <= 0 )
				return SGS_EINPROC;
			
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
			sgs_PushPtr( C, (void*) sysinfo.info.win.window );
#elif defined(SDL_VIDEO_DRIVER_X11)
			sgs_PushPtr( C, (void*) sysinfo.info.x11.window );
#elif defined(SDL_VIDEO_DRIVER_DIRECTFB)
			sgs_PushPtr( C, (void*) sysinfo.info.dfb.window );
#elif defined(SDL_VIDEO_DRIVER_COCOA)
			sgs_PushPtr( C, (void*) sysinfo.info.cocoa.window );
#elif defined(SDL_VIDEO_DRIVER_UIKIT)
			sgs_PushPtr( C, (void*) sysinfo.info.uikit.window );
#else
			sgs_PushNull( C );
#endif
			return SGS_SUCCESS;
		}
		if( !strcmp( str, "rendererPtr" ) ){ sgs_PushPtr( C, W->riface->get_pointer( W->renderer, 0 ) ); return SGS_SUCCESS; }
	}
	
	return SGS_ENOTFND;
}

static int ss_window_setindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* str;
	WND_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseString( C, 0, &str, NULL ) )
	{
		if( !strcmp( str, "bordered" ) )
		{
			sgs_Bool val;
			if( sgs_ParseBool( C, 1, &val ) )
			{
				SDL_SetWindowBordered( W->window, val );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "brightness" ) )
		{
			sgs_Real val;
			if( sgs_ParseReal( C, 1, &val ) )
			{
				if( 0 != SDL_SetWindowBrightness( W->window, val ) )
					sgs_Printf( C, SGS_WARNING, "failed to set brightness: %s\n", SDL_GetError() );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "fullscreen" ) )
		{
			sgs_Int val;
			if( sgs_ParseInt( C, 1, &val ) )
			{
				if( 0 != SDL_SetWindowFullscreen( W->window, val ) )
					sgs_Printf( C, SGS_WARNING, "failed to set fullscreen: %s\n", SDL_GetError() );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "grab" ) )
		{
			sgs_Bool val;
			if( sgs_ParseBool( C, 1, &val ) )
			{
				SDL_SetWindowGrab( W->window, val );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "title" ) )
		{
			char* val;
			if( sgs_ParseString( C, 1, &val, NULL ) )
			{
				SDL_SetWindowTitle( W->window, val );
				return SGS_SUCCESS;
			}
		}
	}
	
	return SGS_ENOTFND;
}

static int ss_window_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_CONVOP_TOTYPE || type == SGS_VT_STRING )
	{
		UNUSED( data );
		sgs_PushString( C, "window" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int ss_window_destruct( SGS_CTX, sgs_VarObj* data, int unused )
{
	WND_HDR;
	UNUSED( unused );
	if( W->renderer )
	{
		SS_TmpCtx ctx = ss_TmpMakeCurrent( W->riface, W->renderer );
		W->riface->destroy( W->renderer );
		ss_TmpRestoreCurrent( &ctx );
	}
	SDL_DestroyWindow( W->window );
	return SGS_SUCCESS;
}

static sgs_ObjCallback ss_window_iface[] =
{
	SGS_OP_GETINDEX, ss_window_getindex,
	SGS_OP_SETINDEX, ss_window_setindex,
	SGS_OP_CONVERT, ss_window_convert,
	SGS_OP_DESTRUCT, ss_window_destruct,
	SGS_OP_END
};

static int SS_CreateWindow( SGS_CTX )
{
	ss_window* W;
	char* str;
	sgs_Int x, y, w, h, f = 0;
	SGSFN( "SS_CreateWindow" );
	if( !sgs_LoadArgs( C, "siiii|i", &str, &x, &y, &w, &h, &f ) )
		return 0;
	
	f |= SDL_WINDOW_OPENGL;
	W = (ss_window*) sgs_PushObjectIPA( C, sizeof(ss_window), ss_window_iface );
	W->window = SDL_CreateWindow( str, x, y, w, h, f );
	W->renderer = NULL;
	W->riface = NULL;
	if( !W->window )
		return sgs_Printf( C, SGS_WARNING, "failed to create a window" );
	SDL_SetWindowData( W->window, "sgsobj", sgs_GetObjectStruct( C, -1 ) );
	
	return 1;
}

static int SS_GetWindowFromID( SGS_CTX )
{
	sgs_VarObj* obj;
	SDL_Window* win;
	sgs_Int id;
	SGSFN( "SS_GetWindowFromID" );
	if( !sgs_LoadArgs( C, "i", &id ) )
		return 0;
	win = SDL_GetWindowFromID( id );
	if( !win )
		return 0;
	obj = (sgs_VarObj*) SDL_GetWindowData( win, "sgsobj" );
	if( !obj )
		sgs_PushPtr( C, win );
	else
		sgs_PushObjectPtr( C, obj );
	return 1;
}

static ss_window* ss_window_from_id( Uint32 id )
{
	sgs_VarObj* obj;
	SDL_Window* win;
	win = SDL_GetWindowFromID( id );
	if( !win )
		return NULL;
	obj = (sgs_VarObj*) SDL_GetWindowData( win, "sgsobj" );
	if( !obj )
		return NULL;
	return (ss_window*) obj->data;
}



int SS_ShowCursor( SGS_CTX )
{
	int shc;
	SGSFN( "SS_ShowCursor" );
	if( !sgs_ParseBool( C, 0, &shc ) )
		_WARN( "function expects 1 argument: bool" )
	SDL_ShowCursor( shc ? SDL_ENABLE : SDL_DISABLE );
	return 0;
}

int SS_WarpMouse( SGS_CTX )
{
	sgs_Integer x, y;
	SGSFN( "SS_WarpMouse" );
	if( !sgs_LoadArgs( C, "ii", &x, &y ) )
		return 0;
	SDL_WarpMouseInWindow( NULL, (Uint16) x, (Uint16) y );
	return 0;
}

int SS_GetMouseState( SGS_CTX )
{
	int x, y, btnmask;
	SGSFN( "SS_GetMouseState" );
	btnmask = SDL_GetMouseState( &x, &y );
	sgs_PushInt( C, x );
	sgs_PushInt( C, y );
	sgs_PushInt( C, btnmask );
	sgs_PushArray( C, 3 );
	return 1;
}

int SS_GetRelativeMouseState( SGS_CTX )
{
	int x, y, btnmask;
	SGSFN( "SS_GetRelativeMouseState" );
	btnmask = SDL_GetRelativeMouseState( &x, &y );
	sgs_PushInt( C, x );
	sgs_PushInt( C, y );
	sgs_PushInt( C, btnmask );
	sgs_PushArray( C, 3 );
	return 1;
}


int SS_SetGLAttrib( SGS_CTX )
{
	sgs_Integer attr, val;
	SGSFN( "SS_SetGLAttrib" );
	
	if( !sgs_ParseInt( C, 0, &attr ) || !sgs_ParseInt( C, 1, &val ) )
		_WARN( "function expects 2 arguments: int, int" )
	
	sgs_PushBool( C, SDL_GL_SetAttribute( attr, val ) == 0 );
	return 1;
}

int SS_Clear( SGS_CTX )
{
	float col[ 4 ];
	SGSFN( "SS_Clear" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( sgs_StackSize( C ) != 1 ||
		!ss_ParseColor( C, 0, col ) )
		_WARN( "function expects 1 argument: array of 1-4 real values" )
	
	GCurRI->clear( GCurRr, col );
	return 0;
}

int SS_Present( SGS_CTX )
{
	SGSFN( "SS_Present" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	GCurRI->swap( GCurRr );
	return 0;
}


sgs_RegIntConst sdl_ints[] =
{
	/*  EVENTS  */
	IC( SDL_QUIT ),
	
	IC( SDL_WINDOWEVENT ),
	IC( SDL_SYSWMEVENT ),
	
	IC( SDL_KEYDOWN ),
	IC( SDL_KEYUP ),
	IC( SDL_TEXTEDITING ),
	IC( SDL_TEXTINPUT ),
	
	IC( SDL_MOUSEMOTION ),
	IC( SDL_MOUSEBUTTONDOWN ),
	IC( SDL_MOUSEBUTTONUP ),
	IC( SDL_MOUSEWHEEL ),
	
	IC( SDL_JOYAXISMOTION ),
	IC( SDL_JOYBALLMOTION ),
	IC( SDL_JOYHATMOTION ),
	IC( SDL_JOYBUTTONDOWN ),
	IC( SDL_JOYBUTTONUP ),
	IC( SDL_JOYDEVICEADDED ),
	IC( SDL_JOYDEVICEREMOVED ),
	
	IC( SDL_CONTROLLERAXISMOTION ),
	IC( SDL_CONTROLLERBUTTONDOWN ),
	IC( SDL_CONTROLLERBUTTONUP ),
	IC( SDL_CONTROLLERDEVICEADDED ),
	IC( SDL_CONTROLLERDEVICEREMOVED ),
	IC( SDL_CONTROLLERDEVICEREMAPPED),
	
	IC( SDL_FINGERDOWN ),
	IC( SDL_FINGERUP ),
	IC( SDL_FINGERMOTION ),
	
	IC( SDL_DOLLARGESTURE ),
	IC( SDL_DOLLARRECORD ),
	IC( SDL_MULTIGESTURE ),
	
	IC( SDL_CLIPBOARDUPDATE ),
	
	IC( SDL_DROPFILE ),
	
	IC( SDL_USEREVENT ),
	
	IC( SDL_WINDOWEVENT_SHOWN ),
	IC( SDL_WINDOWEVENT_HIDDEN ),
	IC( SDL_WINDOWEVENT_EXPOSED ),
	IC( SDL_WINDOWEVENT_MOVED ),
	IC( SDL_WINDOWEVENT_RESIZED ),
	IC( SDL_WINDOWEVENT_SIZE_CHANGED ),
	IC( SDL_WINDOWEVENT_MINIMIZED ),
	IC( SDL_WINDOWEVENT_MAXIMIZED ),
	IC( SDL_WINDOWEVENT_RESTORED ),
	IC( SDL_WINDOWEVENT_ENTER ),
	IC( SDL_WINDOWEVENT_LEAVE ),
	IC( SDL_WINDOWEVENT_FOCUS_GAINED ),
	IC( SDL_WINDOWEVENT_FOCUS_LOST ),
	IC( SDL_WINDOWEVENT_CLOSE ),
	
	/* D3D9 - specific */
	IC( SDL_VIDEODEVICELOST ),
	IC( SDL_VIDEODEVICERESET ),
	
	/*  KEYCODES  */
	IC( SDLK_UNKNOWN ),

	IC( SDLK_RETURN ),
	IC( SDLK_ESCAPE ),
	IC( SDLK_BACKSPACE ),
	IC( SDLK_TAB ),
	IC( SDLK_SPACE ),
	IC( SDLK_EXCLAIM ),
	IC( SDLK_QUOTEDBL ),
	IC( SDLK_HASH ),
	IC( SDLK_PERCENT ),
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

	IC( SDLK_CAPSLOCK ),

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

	IC( SDLK_PRINTSCREEN ),
	IC( SDLK_SCROLLLOCK ),
	IC( SDLK_PAUSE ),
	IC( SDLK_INSERT ),
	IC( SDLK_HOME ),
	IC( SDLK_PAGEUP ),
	IC( SDLK_DELETE ),
	IC( SDLK_END ),
	IC( SDLK_PAGEDOWN ),
	IC( SDLK_RIGHT ),
	IC( SDLK_LEFT ),
	IC( SDLK_DOWN ),
	IC( SDLK_UP ),

	IC( SDLK_NUMLOCKCLEAR ),
	IC( SDLK_KP_DIVIDE ),
	IC( SDLK_KP_MULTIPLY ),
	IC( SDLK_KP_MINUS ),
	IC( SDLK_KP_PLUS ),
	IC( SDLK_KP_ENTER ),
	IC( SDLK_KP_1 ),
	IC( SDLK_KP_2 ),
	IC( SDLK_KP_3 ),
	IC( SDLK_KP_4 ),
	IC( SDLK_KP_5 ),
	IC( SDLK_KP_6 ),
	IC( SDLK_KP_7 ),
	IC( SDLK_KP_8 ),
	IC( SDLK_KP_9 ),
	IC( SDLK_KP_0 ),
	IC( SDLK_KP_PERIOD ),

	IC( SDLK_APPLICATION ),
	IC( SDLK_POWER ),
	IC( SDLK_KP_EQUALS ),
	IC( SDLK_F13 ),
	IC( SDLK_F14 ),
	IC( SDLK_F15 ),
	IC( SDLK_F16 ),
	IC( SDLK_F17 ),
	IC( SDLK_F18 ),
	IC( SDLK_F19 ),
	IC( SDLK_F20 ),
	IC( SDLK_F21 ),
	IC( SDLK_F22 ),
	IC( SDLK_F23 ),
	IC( SDLK_F24 ),
	IC( SDLK_EXECUTE ),
	IC( SDLK_HELP ),
	IC( SDLK_MENU ),
	IC( SDLK_SELECT ),
	IC( SDLK_STOP ),
	IC( SDLK_AGAIN ),
	IC( SDLK_UNDO ),
	IC( SDLK_CUT ),
	IC( SDLK_COPY ),
	IC( SDLK_PASTE ),
	IC( SDLK_FIND ),
	IC( SDLK_MUTE ),
	IC( SDLK_VOLUMEUP ),
	IC( SDLK_VOLUMEDOWN ),
	IC( SDLK_KP_COMMA ),
	IC( SDLK_KP_EQUALSAS400 ),

	IC( SDLK_ALTERASE ),
	IC( SDLK_SYSREQ ),
	IC( SDLK_CANCEL ),
	IC( SDLK_CLEAR ),
	IC( SDLK_PRIOR ),
	IC( SDLK_RETURN2 ),
	IC( SDLK_SEPARATOR ),
	IC( SDLK_OUT ),
	IC( SDLK_OPER ),
	IC( SDLK_CLEARAGAIN ),
	IC( SDLK_CRSEL ),
	IC( SDLK_EXSEL ),

	IC( SDLK_KP_00 ),
	IC( SDLK_KP_000 ),
	IC( SDLK_THOUSANDSSEPARATOR ),
	IC( SDLK_DECIMALSEPARATOR ),
	IC( SDLK_CURRENCYUNIT ),
	IC( SDLK_CURRENCYSUBUNIT ),
	IC( SDLK_KP_LEFTPAREN ),
	IC( SDLK_KP_RIGHTPAREN ),
	IC( SDLK_KP_LEFTBRACE ),
	IC( SDLK_KP_RIGHTBRACE ),
	IC( SDLK_KP_TAB ),
	IC( SDLK_KP_BACKSPACE ),
	IC( SDLK_KP_A ),
	IC( SDLK_KP_B ),
	IC( SDLK_KP_C ),
	IC( SDLK_KP_D ),
	IC( SDLK_KP_E ),
	IC( SDLK_KP_F ),
	IC( SDLK_KP_XOR ),
	IC( SDLK_KP_POWER ),
	IC( SDLK_KP_PERCENT ),
	IC( SDLK_KP_LESS ),
	IC( SDLK_KP_GREATER ),
	IC( SDLK_KP_AMPERSAND ),
	IC( SDLK_KP_DBLAMPERSAND ),
	IC( SDLK_KP_VERTICALBAR ),
	IC( SDLK_KP_DBLVERTICALBAR ),
	IC( SDLK_KP_COLON ),
	IC( SDLK_KP_HASH ),
	IC( SDLK_KP_SPACE ),
	IC( SDLK_KP_AT ),
	IC( SDLK_KP_EXCLAM ),
	IC( SDLK_KP_MEMSTORE ),
	IC( SDLK_KP_MEMRECALL ),
	IC( SDLK_KP_MEMCLEAR ),
	IC( SDLK_KP_MEMADD ),
	IC( SDLK_KP_MEMSUBTRACT ),
	IC( SDLK_KP_MEMMULTIPLY ),
	IC( SDLK_KP_MEMDIVIDE ),
	IC( SDLK_KP_PLUSMINUS ),
	IC( SDLK_KP_CLEAR ),
	IC( SDLK_KP_CLEARENTRY ),
	IC( SDLK_KP_BINARY ),
	IC( SDLK_KP_OCTAL ),
	IC( SDLK_KP_DECIMAL ),
	IC( SDLK_KP_HEXADECIMAL ),

	IC( SDLK_LCTRL ),
	IC( SDLK_LSHIFT ),
	IC( SDLK_LALT ),
	IC( SDLK_LGUI ),
	IC( SDLK_RCTRL ),
	IC( SDLK_RSHIFT ),
	IC( SDLK_RALT ),
	IC( SDLK_RGUI ),

	IC( SDLK_MODE ),

	IC( SDLK_AUDIONEXT ),
	IC( SDLK_AUDIOPREV ),
	IC( SDLK_AUDIOSTOP ),
	IC( SDLK_AUDIOPLAY ),
	IC( SDLK_AUDIOMUTE ),
	IC( SDLK_MEDIASELECT ),
	IC( SDLK_WWW ),
	IC( SDLK_MAIL ),
	IC( SDLK_CALCULATOR ),
	IC( SDLK_COMPUTER ),
	IC( SDLK_AC_SEARCH ),
	IC( SDLK_AC_HOME ),
	IC( SDLK_AC_BACK ),
	IC( SDLK_AC_FORWARD ),
	IC( SDLK_AC_STOP ),
	IC( SDLK_AC_REFRESH ),
	IC( SDLK_AC_BOOKMARKS ),

	IC( SDLK_BRIGHTNESSDOWN ),
	IC( SDLK_BRIGHTNESSUP ),
	IC( SDLK_DISPLAYSWITCH ),
	IC( SDLK_KBDILLUMTOGGLE ),
	IC( SDLK_KBDILLUMDOWN ),
	IC( SDLK_KBDILLUMUP ),
	IC( SDLK_EJECT ),
	IC( SDLK_SLEEP ),
	
	/* SECOND KEY MAPPING, for consistency */
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
	
	/*  KEY MODIFIER FLAGS  */
	IC_SDL( KMOD_NONE ),
	IC_SDL( KMOD_NUM ),
	IC_SDL( KMOD_CAPS ),
	IC_SDL( KMOD_LCTRL ),
	IC_SDL( KMOD_RCTRL ),
	IC_SDL( KMOD_RSHIFT ),
	IC_SDL( KMOD_LSHIFT ),
	IC_SDL( KMOD_RALT ),
	IC_SDL( KMOD_LALT ),
	IC_SDL( KMOD_CTRL ),
	IC_SDL( KMOD_SHIFT ),
	IC_SDL( KMOD_ALT ),
	
	/*  BUTTON MASKS & IDS  */
	IC( SDL_BUTTON_LMASK ),
	IC( SDL_BUTTON_MMASK ),
	IC( SDL_BUTTON_RMASK ),
	IC( SDL_BUTTON_X1MASK ),
	IC( SDL_BUTTON_X2MASK ),
	
	IC( SDL_BUTTON_LEFT ),
	IC( SDL_BUTTON_MIDDLE ),
	IC( SDL_BUTTON_RIGHT ),
	IC( SDL_BUTTON_X1 ),
	IC( SDL_BUTTON_X2 ),
	
	IC( SDL_TOUCH_MOUSEID ),
	
	/*  WINDOW/RENDERER FLAGS & ATTRIBUTES  */
	IC( SDL_WINDOWPOS_UNDEFINED ),
	IC( SDL_WINDOWPOS_CENTERED ),
	
	IC( SDL_WINDOW_FULLSCREEN ),
	IC( SDL_WINDOW_FULLSCREEN_DESKTOP ),
	IC( SDL_WINDOW_OPENGL ),
	IC( SDL_WINDOW_HIDDEN ),
	IC( SDL_WINDOW_BORDERLESS ),
	IC( SDL_WINDOW_RESIZABLE ),
	IC( SDL_WINDOW_MINIMIZED ),
	IC( SDL_WINDOW_MAXIMIZED ),
	IC( SDL_WINDOW_INPUT_GRABBED ),
	IC( SDL_WINDOW_ALLOW_HIGHDPI ),
	
	IC( SDL_RENDERER_SOFTWARE ),
	IC( SDL_RENDERER_ACCELERATED ),
	IC( SDL_RENDERER_PRESENTVSYNC ),
	IC( SDL_RENDERER_TARGETTEXTURE ),
	
	IC( SDL_MESSAGEBOX_ERROR ),
	IC( SDL_MESSAGEBOX_WARNING ),
	IC( SDL_MESSAGEBOX_INFORMATION ),
	
	/*  POWER STATES  */
	IC( SDL_POWERSTATE_UNKNOWN ),
	IC( SDL_POWERSTATE_ON_BATTERY ),
	IC( SDL_POWERSTATE_NO_BATTERY ),
	IC( SDL_POWERSTATE_CHARGING ),
	IC( SDL_POWERSTATE_CHARGED ),
	
	/*  G-L- ATTRIBUTES  */
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
	IC( SDL_GL_CONTEXT_MAJOR_VERSION ),
	IC( SDL_GL_CONTEXT_MINOR_VERSION ),
	IC( SDL_GL_CONTEXT_FLAGS ),
	IC( SDL_GL_CONTEXT_PROFILE_MASK ),
	IC( SDL_GL_SHARE_WITH_CURRENT_CONTEXT ),
	IC( SDL_GL_FRAMEBUFFER_SRGB_CAPABLE ),
	
	/*  CUSTOM CONSTANTS  */
	IC( SS_RENDERER_DONTCARE ),
	IC( SS_RENDERER_OPENGL ),
	IC( SS_RENDERER_DIRECT3D9 ),
	IC( SS_RENDERER_VSYNC ),
	IC( SS_RENDERER_DEBUG ),
};

int SS_SDL_WINDOWPOS_UNDEFINED_DISPLAY( SGS_CTX )
{
	sgs_PushInt( C, SDL_WINDOWPOS_UNDEFINED_DISPLAY( sgs_GetInt( C, 0 ) ) );
	return 1;
}

int SS_SDL_WINDOWPOS_CENTERED_DISPLAY( SGS_CTX )
{
	sgs_PushInt( C, SDL_WINDOWPOS_CENTERED_DISPLAY( sgs_GetInt( C, 0 ) ) );
	return 1;
}

sgs_RegFuncConst sdl_funcs[] =
{
	FN( GetPlatformInfo ),
	FN( GetPowerInfo ),
	FN( Sleep ),
	
	FN( HasClipboardText ),
	FN( GetClipboardText ),
	FN( SetClipboardText ),
	
	FN( EnableScreenSaver ),
	FN( DisableScreenSaver ),
	FN( IsScreenSaverEnabled ),
	
	FN( GetVideoDrivers ),
	FN( DisplayMode ),
	FN( GetNumDisplays ),
	FN( GetDisplayName ),
	FN( GetNumDisplayModes ),
	FN( GetDisplayMode ),
	FN( GetDisplayModes ),
	FN( GetDisplayBounds ),
	FN( GetClosestDisplayMode ),
	FN( GetCurrentDisplayMode ),
	FN( GetDesktopDisplayMode ),
	
	{ "SDL_WINDOWPOS_UNDEFINED_DISPLAY", SS_SDL_WINDOWPOS_UNDEFINED_DISPLAY },
	{ "SDL_WINDOWPOS_CENTERED_DISPLAY", SS_SDL_WINDOWPOS_CENTERED_DISPLAY },
	
	FN( CreateWindow ), FN( GetWindowFromID ),
	
	FN( ShowCursor ),
	FN( WarpMouse ),
	FN( GetMouseState ), FN( GetRelativeMouseState ),
	
	FN( SetGLAttrib ),
	FN( Clear ), FN( Present ),
};

int ss_InitSDL( SGS_CTX )
{
	int ret;
	ret = sgs_RegIntConsts( C, sdl_ints, ARRAY_SIZE( sdl_ints ) );
	if( ret != SGS_SUCCESS ) return ret;
	ret = sgs_RegFuncConsts( C, sdl_funcs, ARRAY_SIZE( sdl_funcs ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	ri_init();
	
	return SGS_SUCCESS;
}


void ss_FreeGraphics( SGS_CTX )
{
	ri_free();
}


int ss_CreateSDLEvent( SGS_CTX, SDL_Event* event )
{
	int osz, ret;
	
	osz = sgs_StackSize( C );
	
	sgs_PushString( C, "type" );
	sgs_PushInt( C, event->type );
	sgs_PushString( C, "timestamp" );
	sgs_PushInt( C, event->common.timestamp );
	
	switch( event->type )
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->key.windowID );
		sgs_PushString( C, "state" );
		sgs_PushBool( C, event->key.state == SDL_PRESSED );
		sgs_PushString( C, "repeat" );
		sgs_PushInt( C, event->key.repeat );
		sgs_PushString( C, "hwcode" );
		sgs_PushInt( C, event->key.keysym.scancode );
		sgs_PushString( C, "keycode" );
		sgs_PushInt( C, event->key.keysym.sym );
		sgs_PushString( C, "mod" );
		sgs_PushInt( C, event->key.keysym.mod );
		break;
	
	case SDL_MOUSEMOTION:
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->motion.windowID );
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->motion.which );
		sgs_PushString( C, "buttons" );
		sgs_PushInt( C, event->motion.state );
		sgs_PushString( C, "lbutton" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON_LMASK );
		sgs_PushString( C, "mbutton" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON_MMASK );
		sgs_PushString( C, "rbutton" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON_RMASK );
		sgs_PushString( C, "x1button" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON_X1MASK );
		sgs_PushString( C, "x2button" );
		sgs_PushBool( C, event->motion.state & SDL_BUTTON_X2MASK );
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
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->button.windowID );
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->button.which );
		sgs_PushString( C, "button" );
		sgs_PushInt( C, event->button.button );
		sgs_PushString( C, "state" );
		sgs_PushBool( C, event->button.state == SDL_PRESSED );
		/* TODO: SDL 2.0.2
		sgs_PushString( C, "clicks" );
		sgs_PushInt( C, event->button.clicks ); */
		sgs_PushString( C, "x" );
		sgs_PushInt( C, event->button.x );
		sgs_PushString( C, "y" );
		sgs_PushInt( C, event->button.y );
		break;
	
	case SDL_WINDOWEVENT:
		if( event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
		{
			int modlist[] = { SS_RMOD_WIDTH, event->window.data1, SS_RMOD_HEIGHT, event->window.data2, 0 };
			ss_window* W = ss_window_from_id( event->window.windowID );
			if( W )
			{
				SS_TmpCtx ctx = ss_TmpMakeCurrent( W->riface, W->renderer );
				W->riface->modify( W->renderer, modlist );
				ss_TmpRestoreCurrent( &ctx );
			}
		}
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->window.windowID );
		sgs_PushString( C, "event" );
		sgs_PushInt( C, event->window.event );
		sgs_PushString( C, "data1" );
		sgs_PushInt( C, event->window.data1 );
		sgs_PushString( C, "data2" );
		sgs_PushInt( C, event->window.data2 );
		break;
	
	/* no more data for...
		SDL_QUIT
	*/
	}
	
	ret = sgs_PushDict( C, sgs_StackSize( C ) - osz );
	if( ret != SGS_SUCCESS )
		sgs_Pop( C, sgs_StackSize( C ) - osz );
	return ret;
}
