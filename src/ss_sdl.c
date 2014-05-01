
#include <math.h>

#include <SDL2/SDL_syswm.h>

#include "ss_main.h"


#define FN( f ) { "SS_" #f, SS_##f }
#define IC( i ) { #i, i }
#define IC_SDL( i ) { "SDL_" #i, i }
#define ICX( n, i ) { #n, i }
#define _WARN( err ) { sgs_Msg( C, SGS_WARNING, err ); return 0; }



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



static int SS_SetError( SGS_CTX )
{
	char* str = NULL;
	SGSFN( "SS_SetError" );
	if( !sgs_LoadArgs( C, "|s", &str ) )
		return 0;
	if( str )
		SDL_SetError( "%s", str );
	else
		SDL_ClearError();
	return 0;
}

static int SS_GetError( SGS_CTX )
{
	SGSFN( "SS_GetError" );
	sgs_PushString( C, SDL_GetError() );
	return 1;
}


static int SS_EventState( SGS_CTX )
{
	uint32_t type;
	int8_t state = -1;
	SGSFN( "SS_EventState" );
	if( !sgs_LoadArgs( C, "+l|-c", &type, &state ) )
		return 0;
	sgs_PushBool( C, SDL_EventState( type, state ) );
	return 1;
}

static int SS_GetNumTouchDevices( SGS_CTX )
{
	SGSFN( "SS_GetNumTouchDevices" );
	sgs_PushInt( C, SDL_GetNumTouchDevices() );
	return 1;
}

static int SS_GetTouchDevice( SGS_CTX )
{
	sgs_Int index;
	SGSFN( "SS_GetTouchDevice" );
	if( !sgs_LoadArgs( C, "i", &index ) )
		return 0;
	sgs_PushInt( C, SDL_GetTouchDevice( index ) );
	return 1;
}

static int SS_GetTouchDevices( SGS_CTX )
{
	int i, numdevs;
	SGSFN( "SS_GetTouchDevices" );
	numdevs = SDL_GetNumTouchDevices();
	for( i = 0; i < numdevs; ++i )
		sgs_PushInt( C, SDL_GetTouchDevice( i ) );
	sgs_PushArray( C, numdevs );
	return 1;
}

static int SS_GetNumTouchFingers( SGS_CTX )
{
	sgs_Int touchID;
	SGSFN( "SS_GetNumTouchFingers" );
	if( !sgs_LoadArgs( C, "i", &touchID ) )
		return 0;
	sgs_PushInt( C, SDL_GetNumTouchFingers( touchID ) );
	return 1;
}

static void _SS_PushFinger( SGS_CTX, SDL_Finger* finger )
{
	if( !finger )
	{
		sgs_PushNull( C );
		return;
	}
	sgs_PushString( C, "id" );
	sgs_PushInt( C, finger->id );
	sgs_PushString( C, "x" );
	sgs_PushReal( C, finger->x );
	sgs_PushString( C, "y" );
	sgs_PushReal( C, finger->y );
	sgs_PushString( C, "pressure" );
	sgs_PushReal( C, finger->pressure );
	sgs_PushDict( C, 8 );
}

static int SS_GetTouchFinger( SGS_CTX )
{
	sgs_Int touchID, index;
	SGSFN( "SS_GetTouchFinger" );
	if( !sgs_LoadArgs( C, "ii", &touchID, &index ) )
		return 0;
	_SS_PushFinger( C, SDL_GetTouchFinger( touchID, index ) );
	return 1;
}

static int SS_GetTouchFingers( SGS_CTX )
{
	int i, count;
	sgs_Int touchID;
	SGSFN( "SS_GetTouchFingers" );
	if( !sgs_LoadArgs( C, "i", &touchID ) )
		return 0;
	count = SDL_GetNumTouchFingers( touchID );
	for( i = 0; i < count; ++i )
		_SS_PushFinger( C, SDL_GetTouchFinger( touchID, i ) );
	sgs_PushArray( C, count );
	return 1;
}

static int SS_RecordGesture( SGS_CTX )
{
	sgs_Int touchID;
	SGSFN( "SS_RecordGesture" );
	if( !sgs_LoadArgs( C, "i", &touchID ) )
		return 0;
	sgs_PushInt( C, SDL_RecordGesture( touchID ) );
	return 1;
}

static int SS_FlushEvents( SGS_CTX )
{
	Uint32 mintype, maxtype;
	SGSFN( "SS_FlushEvents" );
	if( !sgs_LoadArgs( C, "+l|l", &mintype, &maxtype ) )
		return 0;
	if( sgs_StackSize( C ) >= 2 )
		SDL_FlushEvents( mintype, maxtype );
	else
		SDL_FlushEvent( mintype );
	return 0;
}

static int SS_HasEvents( SGS_CTX )
{
	Uint32 mintype, maxtype;
	SGSFN( "SS_HasEvents" );
	if( !sgs_LoadArgs( C, "+l|l", &mintype, &maxtype ) )
		return 0;
	sgs_PushBool( C, sgs_StackSize( C ) >= 2 ? SDL_HasEvents( mintype, maxtype ) : SDL_HasEvent( mintype ) );
	return 1;
}

static int SS_PollEvent( SGS_CTX )
{
	SDL_Event ev;
	SGSFN( "SS_PollEvent" );
	return ( SDL_PollEvent( &ev ) && SGS_SUCCEEDED( ss_CreateSDLEvent( C, &ev ) ) ) ? 1 : 0;
}

static int SS_WaitEvent( SGS_CTX )
{
	int ret;
	sgs_Int timeout = -1;
	SDL_Event ev;
	SGSFN( "SS_WaitEvent" );
	if( sgs_LoadArgs( C, "|i", &timeout ) )
		return 0;
	if( timeout >= 0 )
		ret = SDL_WaitEventTimeout( &ev, timeout );
	else
		ret = SDL_WaitEvent( &ev );
	return ( ret && SGS_SUCCEEDED( ss_CreateSDLEvent( C, &ev ) ) ) ? 1 : 0;
}

static int _SS_PeepEvents_PG( SGS_CTX, int get )
{
	int i, outevents;
	Uint32 eventcount, mintype, maxtype;
	SDL_Event* events;
	if( !sgs_LoadArgs( C, "+lll", &eventcount, &mintype, &maxtype ) )
		return 0;
	if( eventcount > 65535 )
		_WARN( "too many events requested" )
	events = sgs_Alloc_n( SDL_Event, eventcount );
	outevents = SDL_PeepEvents( events, eventcount, get ? SDL_GETEVENT : SDL_PEEKEVENT, mintype, maxtype );
	if( outevents < 0 )
	{
		sgs_PushNull( C );
		sgs_PushString( C, SDL_GetError() );
		return 2;
	}
	else
	{
		for( i = 0; i < outevents; ++i )
		{
			if( SGS_FAILED( ss_CreateSDLEvent( C, &events[ i ] ) ) )
				sgs_PushNull( C );
		}
		sgs_PushArray( C, outevents );
		return 1;
	}
}

static int SS_PeekEvents( SGS_CTX )
{
	SGSFN( "SS_PeekEvents" );
	return _SS_PeepEvents_PG( C, 0 );
}

static int SS_GetEvents( SGS_CTX )
{
	SGSFN( "SS_GetEvents" );
	return _SS_PeepEvents_PG( C, 1 );
}

static int SS_PumpEvents( SGS_CTX )
{
	SGSFN( "SS_PumpEvents" );
	SDL_PumpEvents();
	return 0;
}

static int SS_QuitRequested( SGS_CTX )
{
	SGSFN( "SS_QuitRequested" );
	sgs_PushBool( C, SDL_QuitRequested() );
	return 1;
}


static int SS_GetPlatformInfo( SGS_CTX )
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

static int SS_GetPowerInfo( SGS_CTX )
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


static int SS_HasClipboardText( SGS_CTX )
{
	SGSFN( "SS_HasClipboardText" );
	sgs_PushBool( C, SDL_HasClipboardText() );
	return 1;
}

static int SS_GetClipboardText( SGS_CTX )
{
	char* text;
	SGSFN( "SS_GetClipboardText" );
	text = SDL_GetClipboardText();
	if( !text )
		return sgs_Msg( C, SGS_WARNING, "failed to read from the clipboard: %s", SDL_GetError() );
	sgs_PushString( C, text );
	SDL_free( text );
	return 1;
}

static int SS_SetClipboardText( SGS_CTX )
{
	int ret;
	char* text;
	SGSFN( "SS_SetClipboardText" );
	if( !sgs_LoadArgs( C, "s", &text ) )
		return 0;
	ret = SDL_SetClipboardText( text ) >= 0;
	if( !ret )
		sgs_Msg( C, SGS_WARNING, "failed to write to the clipboard: %s", SDL_GetError() );
	sgs_PushBool( C, ret );
	return 1;
}


static int SS_Sleep( SGS_CTX )
{
	sgs_Integer time;
	SGSFN( "SS_Sleep" );
	if( sgs_StackSize( C ) != 1 ||
		!sgs_ParseInt( C, 0, &time ) )
		_WARN( "function expects 1 argument: int" )
	
	SDL_Delay( time );
	return 0;
}

static int SS_EnableScreenSaver( SGS_CTX ){ SGSFN( "SS_EnableScreenSaver" ); SDL_EnableScreenSaver(); return 0; }
static int SS_DisableScreenSaver( SGS_CTX ){ SGSFN( "SS_DisableScreenSaver" ); SDL_DisableScreenSaver(); return 0; }
static int SS_IsScreenSaverEnabled( SGS_CTX ){ SGSFN( "SS_IsScreenSaverEnabled" ); sgs_PushBool( C, SDL_IsScreenSaverEnabled() ); return 1; }

static int SS_GetVideoDrivers( SGS_CTX )
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

static int ss_displaymode_getindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, int isprop )
{
	char* str;
	DM_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseStringP( C, key, &str, NULL ) )
	{
		if( !strcmp( str, "format" ) ){ sgs_PushInt( C, DM->format ); return SGS_SUCCESS; }
		if( !strcmp( str, "w" ) ){ sgs_PushInt( C, DM->w ); return SGS_SUCCESS; }
		if( !strcmp( str, "h" ) ){ sgs_PushInt( C, DM->h ); return SGS_SUCCESS; }
		if( !strcmp( str, "refresh_rate" ) ){ sgs_PushInt( C, DM->refresh_rate ); return SGS_SUCCESS; }
		if( !strcmp( str, "driverdata" ) ){ sgs_PushPtr( C, DM->driverdata ); return SGS_SUCCESS; }
	}
	
	return SGS_ENOTFND;
}

static int ss_displaymode_setindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, sgs_Variable* val, int isprop )
{
	char* str;
	DM_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseStringP( C, key, &str, NULL ) )
	{
		if( !strcmp( str, "format" ) ){ sgs_Int V; if( sgs_ParseIntP( C, val, &V ) ){ DM->format = V; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "w" ) ){ sgs_Int V; if( sgs_ParseIntP( C, val, &V ) ){ DM->w = V; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "h" ) ){ sgs_Int V; if( sgs_ParseIntP( C, val, &V ) ){ DM->h = V; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "refresh_rate" ) ){ sgs_Int V; if( sgs_ParseIntP( C, val, &V ) ){ DM->refresh_rate = V; return SGS_SUCCESS; } return SGS_EINVAL; }
		if( !strcmp( str, "driverdata" ) ){ void* V; if( sgs_ParsePtrP( C, val, &V ) ){ DM->driverdata = V; return SGS_SUCCESS; } return SGS_EINVAL; }
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
	return SGS_ENOTSUP;
}

static sgs_ObjInterface ss_displaymode_iface[1] =
{{
	"SDL_DisplayMode",
	NULL, NULL,
	ss_displaymode_getindex, ss_displaymode_setindex,
	ss_displaymode_convert, NULL, ss_displaymode_dump, NULL,
	NULL, NULL
}};

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
		if( flags & SGS_LOADARG_WRITE )
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
		return sgs_Msg( C, SGS_WARNING, "failed to get number of display modes for display #%d: %s", (int) i, SDL_GetError() );
	
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
		return sgs_Msg( C, SGS_WARNING, "failed to get display mode #%d for display #%d: %s", (int) mid, (int) i, SDL_GetError() );
	
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
		return sgs_Msg( C, SGS_WARNING, "failed to get number of display modes for display #%d: %s", (int) did, SDL_GetError() );
	
	for( i = 0; i < num; ++i )
	{
		if( 0 != SDL_GetDisplayMode( did, i, &mode ) )
			return sgs_Msg( C, SGS_WARNING, "failed to get display mode #%d for display #%d: %s", i, (int) did, SDL_GetError() );
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
		return sgs_Msg( C, SGS_WARNING, "failed to get display #%d bounds: %s", (int) i, SDL_GetError() );
	
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
		return sgs_Msg( C, SGS_WARNING, "failed to get current display mode for display #%d: %s", (int) i, SDL_GetError() );
	
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
		return sgs_Msg( C, SGS_WARNING, "failed to get desktop display mode for display #%d: %s", (int) i, SDL_GetError() );
	
	ss_PushDisplayMode( C, &mode );
	return 1;
}



#define WND_HDR SS_Window* W = (SS_Window*) data->data;
#define WND_IHDR( funcname ) SS_Window* W; \
	if( !SGS_PARSE_METHOD( C, SS_Window_iface, W, SS_Window, funcname ) ) return 0;

SGS_DECLARE sgs_ObjInterface SS_Window_iface[1];

static int SS_WindowI_show( SGS_CTX )
{
	WND_IHDR( show );
	SDL_ShowWindow( W->window );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_hide( SGS_CTX )
{
	WND_IHDR( hide );
	SDL_HideWindow( W->window );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_minimize( SGS_CTX )
{
	WND_IHDR( minimize );
	SDL_MinimizeWindow( W->window );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_maximize( SGS_CTX )
{
	WND_IHDR( maximize );
	SDL_MaximizeWindow( W->window );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_restore( SGS_CTX )
{
	WND_IHDR( restore );
	SDL_RestoreWindow( W->window );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_raise( SGS_CTX )
{
	WND_IHDR( raise );
	SDL_RaiseWindow( W->window );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_setPosition( SGS_CTX )
{
	sgs_Int x, y;
	WND_IHDR( setPosition );
	if( !sgs_LoadArgs( C, "ii", &x, &y ) )
		return 0;
	SDL_SetWindowPosition( W->window, x, y );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_setSize( SGS_CTX )
{
	sgs_Int w, h;
	WND_IHDR( setSize );
	if( !sgs_LoadArgs( C, "ii", &w, &h ) )
		return 0;
	SDL_SetWindowSize( W->window, w, h );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_setMaxSize( SGS_CTX )
{
	sgs_Int w, h;
	WND_IHDR( setMaxSize );
	if( !sgs_LoadArgs( C, "ii", &w, &h ) )
		return 0;
	SDL_SetWindowMaximumSize( W->window, w, h );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_setMinSize( SGS_CTX )
{
	sgs_Int w, h;
	WND_IHDR( setMinSize );
	if( !sgs_LoadArgs( C, "ii", &w, &h ) )
		return 0;
	SDL_SetWindowMinimumSize( W->window, w, h );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_warpMouse( SGS_CTX )
{
	sgs_Int x, y;
	WND_IHDR( warpMouse );
	if( !sgs_LoadArgs( C, "ii", &x, &y ) )
		return 0;
	SDL_WarpMouseInWindow( W->window, x, y );
	SGS_RETURN_THIS( C );
}

static int SS_WindowI_initRenderer( SGS_CTX )
{
	sgs_Int renderer = SS_RENDERER_DONTCARE, version = SS_RENDERER_DONTCARE, flags = 0;
	SS_RenderInterface* riface;
	SS_Renderer* R;
	WND_IHDR( initRenderer );
	
	if( !sgs_LoadArgs( C, "|iii", &renderer, &version, &flags ) )
		return 0;
	
	if( W->riface )
		return sgs_Msg( C, SGS_WARNING, "free the current renderer to initialize a new one" );
	
	if( renderer != SS_RENDERER_DONTCARE &&
		renderer != SS_RENDERER_OPENGL &&
		renderer != SS_RENDERER_DIRECT3D9 )
		return sgs_Msg( C, SGS_WARNING, "invalid renderer specified" );
	
	if( renderer == SS_RENDERER_DONTCARE )
#ifdef SS_USED3D
		renderer = SS_RENDERER_DIRECT3D9;
#else
		renderer = SS_RENDERER_OPENGL;
#endif
	
	riface = ri_pick( renderer );
	if( !riface )
		return sgs_Msg( C, SGS_WARNING, "specified renderer is unavailable" );
	
	R = riface->create( W->window, version, flags );
	if( !R )
		return sgs_Msg( C, SGS_WARNING, "failed to create the renderer: %s", riface->last_error );
	
	W->riface = riface;
	W->renderer = R;
	
	ss_MakeCurrent( riface, R );
	
	sgs_PushBool( C, 1 );
	return 1;
}

static int SS_WindowI_makeCurrent( SGS_CTX )
{
	WND_IHDR( makeCurrent );
	if( W->riface && W->renderer )
		ss_MakeCurrent( W->riface, W->renderer );
	
	sgs_PushBool( C, W->riface && W->renderer );
	return 1;
}


static int SS_Window_getindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, int isprop )
{
	char* str;
	WND_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseStringP( C, key, &str, NULL ) )
	{
		/* function properties */
		if( !strcmp( str, "show" ) ){ sgs_PushCFunction( C, SS_WindowI_show ); return SGS_SUCCESS; }
		if( !strcmp( str, "hide" ) ){ sgs_PushCFunction( C, SS_WindowI_hide ); return SGS_SUCCESS; }
		if( !strcmp( str, "minimize" ) ){ sgs_PushCFunction( C, SS_WindowI_minimize ); return SGS_SUCCESS; }
		if( !strcmp( str, "maximize" ) ){ sgs_PushCFunction( C, SS_WindowI_maximize ); return SGS_SUCCESS; }
		if( !strcmp( str, "restore" ) ){ sgs_PushCFunction( C, SS_WindowI_restore ); return SGS_SUCCESS; }
		if( !strcmp( str, "raise" ) ){ sgs_PushCFunction( C, SS_WindowI_raise ); return SGS_SUCCESS; }
		if( !strcmp( str, "setPosition" ) ){ sgs_PushCFunction( C, SS_WindowI_setPosition ); return SGS_SUCCESS; }
		if( !strcmp( str, "setSize" ) ){ sgs_PushCFunction( C, SS_WindowI_setSize ); return SGS_SUCCESS; }
		if( !strcmp( str, "setMaxSize" ) ){ sgs_PushCFunction( C, SS_WindowI_setMaxSize ); return SGS_SUCCESS; }
		if( !strcmp( str, "setMinSize" ) ){ sgs_PushCFunction( C, SS_WindowI_setMinSize ); return SGS_SUCCESS; }
		if( !strcmp( str, "warpMouse" ) ){ sgs_PushCFunction( C, SS_WindowI_warpMouse ); return SGS_SUCCESS; }
		if( !strcmp( str, "initRenderer" ) ){ sgs_PushCFunction( C, SS_WindowI_initRenderer ); return SGS_SUCCESS; }
		if( !strcmp( str, "makeCurrent" ) ){ sgs_PushCFunction( C, SS_WindowI_makeCurrent ); return SGS_SUCCESS; }
		
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
				sgs_Msg( C, SGS_WARNING, "failed to get display mode: %s", SDL_GetError() );
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
		
		if( !strcmp( str, "hasKeyboardFocus" ) ){ sgs_PushBool( C, SDL_GetKeyboardFocus() == W->window ); return SGS_SUCCESS; }
		if( !strcmp( str, "hasMouseFocus" ) ){ sgs_PushBool( C, SDL_GetMouseFocus() == W->window ); return SGS_SUCCESS; }
		if( !strcmp( str, "isScreenKeyboardShown" ) ){ sgs_PushBool( C, SDL_IsScreenKeyboardShown( W->window ) ); return SGS_SUCCESS; }
		
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
		if( !strcmp( str, "renderingAPI" ) ){ sgs_PushString( C, W->riface->API ); return SGS_SUCCESS; }
		if( !strcmp( str, "rendererPtr" ) ){ sgs_PushPtr( C, W->riface->get_pointer( W->renderer, 0 ) ); return SGS_SUCCESS; }
	}
	
	return SGS_ENOTFND;
}

static int SS_Window_setindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, sgs_Variable* val, int isprop )
{
	char* str;
	WND_HDR;
	UNUSED( isprop );
	
	if( sgs_ParseStringP( C, key, &str, NULL ) )
	{
		if( !strcmp( str, "bordered" ) )
		{
			sgs_Bool V;
			if( sgs_ParseBoolP( C, val, &V ) )
			{
				SDL_SetWindowBordered( W->window, V );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "brightness" ) )
		{
			sgs_Real V;
			if( sgs_ParseRealP( C, val, &V ) )
			{
				if( 0 != SDL_SetWindowBrightness( W->window, V ) )
					sgs_Msg( C, SGS_WARNING, "failed to set brightness: %s\n", SDL_GetError() );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "fullscreen" ) )
		{
			sgs_Int V;
			if( sgs_ParseIntP( C, val, &V ) )
			{
				if( 0 != SDL_SetWindowFullscreen( W->window, V ) )
					sgs_Msg( C, SGS_WARNING, "failed to set fullscreen: %s\n", SDL_GetError() );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "grab" ) )
		{
			sgs_Bool V;
			if( sgs_ParseBoolP( C, val, &V ) )
			{
				SDL_SetWindowGrab( W->window, V );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "title" ) )
		{
			char* V;
			if( sgs_ParseStringP( C, val, &V, NULL ) )
			{
				SDL_SetWindowTitle( W->window, V );
				return SGS_SUCCESS;
			}
		}
	}
	
	return SGS_ENOTFND;
}

static int SS_Window_destruct( SGS_CTX, sgs_VarObj* data )
{
	WND_HDR;
	if( W->renderer )
	{
		SS_TmpCtx ctx = ss_TmpMakeCurrent( W->riface, W->renderer );
		W->riface->destroy( W->renderer );
		if( ctx.renderer == W->renderer )
		{
			// destroyed current
			ss_MakeCurrent( NULL, NULL );
			sgs_PushNull( C );
			sgs_StoreGlobal( C, "_R" );
		}
		else
		{
			// destroyed some other
			ss_TmpRestoreCurrent( &ctx );
		}
	}
	SDL_DestroyWindow( W->window );
	return SGS_SUCCESS;
}

static sgs_ObjInterface SS_Window_iface[1] =
{{
	"SS_Window",
	SS_Window_destruct, NULL,
	SS_Window_getindex, SS_Window_setindex,
	NULL, NULL, NULL, NULL,
	NULL, NULL
}};

static int SS_CreateWindow( SGS_CTX )
{
	SS_Window* W;
	char* str;
	sgs_Int x, y, w, h, f = 0;
	SGSFN( "SS_CreateWindow" );
	if( !sgs_LoadArgs( C, "siiii|i", &str, &x, &y, &w, &h, &f ) )
		return 0;
	
//	f |= SDL_WINDOW_OPENGL;
	W = (SS_Window*) sgs_PushObjectIPA( C, sizeof(SS_Window), SS_Window_iface );
	W->window = SDL_CreateWindow( str, x, y, w, h, f );
	W->renderer = NULL;
	W->riface = NULL;
	if( !W->window )
		return sgs_Msg( C, SGS_WARNING, "failed to create a window" );
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

static SS_Window* SS_Window_from_id( Uint32 id )
{
	sgs_VarObj* obj;
	SDL_Window* win;
	win = SDL_GetWindowFromID( id );
	if( !win )
		return NULL;
	obj = (sgs_VarObj*) SDL_GetWindowData( win, "sgsobj" );
	if( !obj )
		return NULL;
	return (SS_Window*) obj->data;
}



static int SS_GetKeyFromName( SGS_CTX )
{
	char* str;
	SGSFN( "SS_GetKeyFromName" );
	if( !sgs_LoadArgs( C, "s", &str ) )
		return 0;
	sgs_PushInt( C, SDL_GetKeyFromName( str ) );
	return 1;
}

static int SS_GetScancodeFromName( SGS_CTX )
{
	char* str;
	SGSFN( "SS_GetScancodeFromName" );
	if( !sgs_LoadArgs( C, "s", &str ) )
		return 0;
	sgs_PushInt( C, SDL_GetScancodeFromName( str ) );
	return 1;
}

static int SS_GetKeyFromScancode( SGS_CTX )
{
	sgs_Int sc;
	SGSFN( "SS_GetKeyFromScancode" );
	if( !sgs_LoadArgs( C, "i", &sc ) )
		return 0;
	sgs_PushInt( C, SDL_GetKeyFromScancode( sc ) );
	return 1;
}

static int SS_GetScancodeFromKey( SGS_CTX )
{
	sgs_Int key;
	SGSFN( "SS_GetScancodeFromKey" );
	if( !sgs_LoadArgs( C, "i", &key ) )
		return 0;
	sgs_PushInt( C, SDL_GetScancodeFromKey( key ) );
	return 1;
}

static int SS_GetKeyName( SGS_CTX )
{
	sgs_Int key;
	SGSFN( "SS_GetKeyName" );
	if( !sgs_LoadArgs( C, "i", &key ) )
		return 0;
	sgs_PushString( C, SDL_GetKeyName( key ) );
	return 1;
}

static int SS_GetScancodeName( SGS_CTX )
{
	sgs_Int key;
	SGSFN( "SS_GetScancodeName" );
	if( !sgs_LoadArgs( C, "i", &key ) )
		return 0;
	sgs_PushString( C, SDL_GetScancodeName( key ) );
	return 1;
}

static int SS_GetKeyboardFocus( SGS_CTX )
{
	sgs_VarObj* obj;
	SDL_Window* win;
	SGSFN( "SS_GetKeyboardFocus" );
	win = SDL_GetKeyboardFocus();
	if( win )
	{
		if( ( obj = (sgs_VarObj*) SDL_GetWindowData( win, "sgsobj" ) ) != NULL )
			sgs_PushObjectPtr( C, obj );
		else
			sgs_PushPtr( C, win );
		return 1;
	}
	return 0;
}

static int SS_GetMouseFocus( SGS_CTX )
{
	sgs_VarObj* obj;
	SDL_Window* win;
	SGSFN( "SS_GetMouseFocus" );
	win = SDL_GetMouseFocus();
	if( win )
	{
		if( ( obj = (sgs_VarObj*) SDL_GetWindowData( win, "sgsobj" ) ) != NULL )
			sgs_PushObjectPtr( C, obj );
		else
			sgs_PushPtr( C, win );
		return 1;
	}
	return 0;
}

static int SS_GetModState( SGS_CTX )
{
	SGSFN( "SS_GetModState" );
	sgs_PushInt( C, SDL_GetModState() );
	return 1;
}

static int SS_SetModState( SGS_CTX )
{
	sgs_Int state;
	SGSFN( "SS_SetModState" );
	if( !sgs_LoadArgs( C, "i", &state ) )
		return 0;
	SDL_SetModState( state );
	return 0;
}

static int SS_HasScreenKeyboardSupport( SGS_CTX )
{
	SGSFN( "SS_HasScreenKeyboardSupport" );
	sgs_PushBool( C, SDL_HasScreenKeyboardSupport() );
	return 1;
}

static int SS_IsTextInputActive( SGS_CTX )
{
	SGSFN( "SS_IsTextInputActive" );
	sgs_PushBool( C, SDL_IsTextInputActive() );
	return 1;
}


static int SS_ShowCursor( SGS_CTX )
{
	sgs_Bool shc;
	SGSFN( "SS_ShowCursor" );
	if( !sgs_LoadArgs( C, "b", &shc ) )
		return 0;
	SDL_ShowCursor( shc ? SDL_ENABLE : SDL_DISABLE );
	return 0;
}

static int SS_SetSystemCursor( SGS_CTX )
{
	sgs_Int type;
	SDL_Cursor* cursor;
	SGSFN( "SS_SetSystemCursor" );
	if( !sgs_LoadArgs( C, "i", &type ) )
		return 0;
	cursor = SDL_CreateSystemCursor( type );
	if( !cursor )
	{
		sgs_PushBool( C, 0 );
		return 1;
	}
	SDL_SetCursor( cursor );
	SDL_FreeCursor( cursor );
	sgs_PushBool( C, 1 );
	return 1;
}

static int SS_WarpMouse( SGS_CTX )
{
	sgs_Integer x, y;
	SGSFN( "SS_WarpMouse" );
	if( !sgs_LoadArgs( C, "ii", &x, &y ) )
		return 0;
	SDL_WarpMouseInWindow( NULL, (Uint16) x, (Uint16) y );
	return 0;
}

static int SS_GetMouseState( SGS_CTX )
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

static int SS_GetRelativeMouseState( SGS_CTX )
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

static int SS_GetRelativeMouseMode( SGS_CTX )
{
	SGSFN( "SS_GetRelativeMouseMode" );
	sgs_PushBool( C, SDL_GetRelativeMouseMode() );
	return 1;
}

static int SS_SetRelativeMouseMode( SGS_CTX )
{
	sgs_Bool mode;
	SGSFN( "SS_SetRelativeMouseMode" );
	if( !sgs_LoadArgs( C, "b", &mode ) )
		return 0;
	if( SDL_SetRelativeMouseMode( mode ) == 0 )
	{
		sgs_PushBool( C, 1 );
		return 1;
	}
	else
	{
		sgs_PushBool( C, 0 );
		sgs_PushString( C, SDL_GetError() );
		return 2;
	}
}


static int SS_StartTextInput( SGS_CTX )
{
	SGSFN( "SS_StartTextInput" );
	SDL_StartTextInput();
	return 0;
}

static int SS_StopTextInput( SGS_CTX )
{
	SGSFN( "SS_StopTextInput" );
	SDL_StopTextInput();
	return 0;
}

static int SS_SetTextInputRect( SGS_CTX )
{
	sgs_Int l, t, r, b;
	SGSFN( "SS_SetTextInputRect" );
	if( !sgs_LoadArgs( C, "iiii", &l, &t, &r, &b ) )
		return 0;
	{
		SDL_Rect rect = { l, t, r, b };
		SDL_SetTextInputRect( &rect );
	}
	return 0;
}


static int SS_SetGLAttrib( SGS_CTX )
{
	sgs_Integer attr, val;
	SGSFN( "SS_SetGLAttrib" );
	
	if( !sgs_ParseInt( C, 0, &attr ) || !sgs_ParseInt( C, 1, &val ) )
		_WARN( "function expects 2 arguments: int, int" )
	
	sgs_PushBool( C, SDL_GL_SetAttribute( attr, val ) == 0 );
	return 1;
}

static int SS_Clear( SGS_CTX )
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

static int SS_Present( SGS_CTX )
{
	SGSFN( "SS_Present" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	GCurRI->swap( GCurRr );
	return 0;
}


#ifdef SS_USED3D
#  define SDL_WINDOW_OPENGLMAYBE 0
#else
#  define SDL_WINDOW_OPENGLMAYBE SDL_WINDOW_OPENGL
#endif


static sgs_RegIntConst sdl_ints[] =
{
	/*  EVENTS  */
	IC( SDL_QUIT ),
	
	IC( SDL_FIRSTEVENT ),
	IC( SDL_LASTEVENT ),
	
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
	
	/* System cursors */
	IC( SDL_SYSTEM_CURSOR_ARROW ),
	IC( SDL_SYSTEM_CURSOR_IBEAM ),
	IC( SDL_SYSTEM_CURSOR_WAIT ),
	IC( SDL_SYSTEM_CURSOR_CROSSHAIR ),
	IC( SDL_SYSTEM_CURSOR_WAITARROW ),
	IC( SDL_SYSTEM_CURSOR_SIZENWSE ),
	IC( SDL_SYSTEM_CURSOR_SIZENESW ),
	IC( SDL_SYSTEM_CURSOR_SIZEWE ),
	IC( SDL_SYSTEM_CURSOR_SIZENS ),
	IC( SDL_SYSTEM_CURSOR_SIZEALL ),
	IC( SDL_SYSTEM_CURSOR_NO ),
	IC( SDL_SYSTEM_CURSOR_HAND ),
	/* - shorter */
	ICX( SDL_CURSOR_ARROW, SDL_SYSTEM_CURSOR_ARROW ),
	ICX( SDL_CURSOR_IBEAM, SDL_SYSTEM_CURSOR_IBEAM ),
	ICX( SDL_CURSOR_WAIT, SDL_SYSTEM_CURSOR_WAIT ),
	ICX( SDL_CURSOR_CROSSHAIR, SDL_SYSTEM_CURSOR_CROSSHAIR ),
	ICX( SDL_CURSOR_WAITARROW, SDL_SYSTEM_CURSOR_WAITARROW ),
	ICX( SDL_CURSOR_SIZENWSE, SDL_SYSTEM_CURSOR_SIZENWSE ),
	ICX( SDL_CURSOR_SIZENESW, SDL_SYSTEM_CURSOR_SIZENESW ),
	ICX( SDL_CURSOR_SIZEWE, SDL_SYSTEM_CURSOR_SIZEWE ),
	ICX( SDL_CURSOR_SIZENS, SDL_SYSTEM_CURSOR_SIZENS ),
	ICX( SDL_CURSOR_SIZEALL, SDL_SYSTEM_CURSOR_SIZEALL ),
	ICX( SDL_CURSOR_NO, SDL_SYSTEM_CURSOR_NO ),
	ICX( SDL_CURSOR_HAND, SDL_SYSTEM_CURSOR_HAND ),
	
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
	
	/*  SCANCODES  */
	IC( SDL_SCANCODE_UNKNOWN ),
	IC( SDL_SCANCODE_A ),
	IC( SDL_SCANCODE_B ),
	IC( SDL_SCANCODE_C ),
	IC( SDL_SCANCODE_D ),
	IC( SDL_SCANCODE_E ),
	IC( SDL_SCANCODE_F ),
	IC( SDL_SCANCODE_G ),
	IC( SDL_SCANCODE_H ),
	IC( SDL_SCANCODE_I ),
	IC( SDL_SCANCODE_J ),
	IC( SDL_SCANCODE_K ),
	IC( SDL_SCANCODE_L ),
	IC( SDL_SCANCODE_M ),
	IC( SDL_SCANCODE_N ),
	IC( SDL_SCANCODE_O ),
	IC( SDL_SCANCODE_P ),
	IC( SDL_SCANCODE_Q ),
	IC( SDL_SCANCODE_R ),
	IC( SDL_SCANCODE_S ),
	IC( SDL_SCANCODE_T ),
	IC( SDL_SCANCODE_U ),
	IC( SDL_SCANCODE_V ),
	IC( SDL_SCANCODE_W ),
	IC( SDL_SCANCODE_X ),
	IC( SDL_SCANCODE_Y ),
	IC( SDL_SCANCODE_Z ),
	
	IC( SDL_SCANCODE_1 ),
	IC( SDL_SCANCODE_2 ),
	IC( SDL_SCANCODE_3 ),
	IC( SDL_SCANCODE_4 ),
	IC( SDL_SCANCODE_5 ),
	IC( SDL_SCANCODE_6 ),
	IC( SDL_SCANCODE_7 ),
	IC( SDL_SCANCODE_8 ),
	IC( SDL_SCANCODE_9 ),
	IC( SDL_SCANCODE_0 ),
	
	IC( SDL_SCANCODE_RETURN ),
	IC( SDL_SCANCODE_ESCAPE ),
	IC( SDL_SCANCODE_BACKSPACE ),
	IC( SDL_SCANCODE_TAB ),
	IC( SDL_SCANCODE_SPACE ),
	
	IC( SDL_SCANCODE_MINUS ),
	IC( SDL_SCANCODE_EQUALS ),
	IC( SDL_SCANCODE_LEFTBRACKET ),
	IC( SDL_SCANCODE_RIGHTBRACKET ),
	IC( SDL_SCANCODE_BACKSLASH ),
	IC( SDL_SCANCODE_NONUSHASH ),
	IC( SDL_SCANCODE_SEMICOLON ),
	IC( SDL_SCANCODE_APOSTROPHE ),
	IC( SDL_SCANCODE_GRAVE ),
	IC( SDL_SCANCODE_COMMA ),
	IC( SDL_SCANCODE_PERIOD ),
	IC( SDL_SCANCODE_SLASH ),
	
	IC( SDL_SCANCODE_CAPSLOCK ),
	
	IC( SDL_SCANCODE_F1 ),
	IC( SDL_SCANCODE_F2 ),
	IC( SDL_SCANCODE_F3 ),
	IC( SDL_SCANCODE_F4 ),
	IC( SDL_SCANCODE_F5 ),
	IC( SDL_SCANCODE_F6 ),
	IC( SDL_SCANCODE_F7 ),
	IC( SDL_SCANCODE_F8 ),
	IC( SDL_SCANCODE_F9 ),
	IC( SDL_SCANCODE_F10 ),
	IC( SDL_SCANCODE_F11 ),
	IC( SDL_SCANCODE_F12 ),
	
	IC( SDL_SCANCODE_PRINTSCREEN ),
	IC( SDL_SCANCODE_SCROLLLOCK ),
	IC( SDL_SCANCODE_PAUSE ),
	IC( SDL_SCANCODE_INSERT ),
	IC( SDL_SCANCODE_HOME ),
	IC( SDL_SCANCODE_PAGEUP ),
	IC( SDL_SCANCODE_DELETE ),
	IC( SDL_SCANCODE_END ),
	IC( SDL_SCANCODE_PAGEDOWN ),
	IC( SDL_SCANCODE_RIGHT ),
	IC( SDL_SCANCODE_LEFT ),
	IC( SDL_SCANCODE_DOWN ),
	IC( SDL_SCANCODE_UP ),
	
	IC( SDL_SCANCODE_NUMLOCKCLEAR ),
	IC( SDL_SCANCODE_KP_DIVIDE ),
	IC( SDL_SCANCODE_KP_MULTIPLY ),
	IC( SDL_SCANCODE_KP_MINUS ),
	IC( SDL_SCANCODE_KP_PLUS ),
	IC( SDL_SCANCODE_KP_ENTER ),
	IC( SDL_SCANCODE_KP_1 ),
	IC( SDL_SCANCODE_KP_2 ),
	IC( SDL_SCANCODE_KP_3 ),
	IC( SDL_SCANCODE_KP_4 ),
	IC( SDL_SCANCODE_KP_5 ),
	IC( SDL_SCANCODE_KP_6 ),
	IC( SDL_SCANCODE_KP_7 ),
	IC( SDL_SCANCODE_KP_8 ),
	IC( SDL_SCANCODE_KP_9 ),
	IC( SDL_SCANCODE_KP_0 ),
	IC( SDL_SCANCODE_KP_PERIOD ),
	
	IC( SDL_SCANCODE_NONUSBACKSLASH ),
	IC( SDL_SCANCODE_APPLICATION ),
	IC( SDL_SCANCODE_POWER ),
	IC( SDL_SCANCODE_KP_EQUALS ),
	IC( SDL_SCANCODE_F13 ),
	IC( SDL_SCANCODE_F14 ),
	IC( SDL_SCANCODE_F15 ),
	IC( SDL_SCANCODE_F16 ),
	IC( SDL_SCANCODE_F17 ),
	IC( SDL_SCANCODE_F18 ),
	IC( SDL_SCANCODE_F19 ),
	IC( SDL_SCANCODE_F20 ),
	IC( SDL_SCANCODE_F21 ),
	IC( SDL_SCANCODE_F22 ),
	IC( SDL_SCANCODE_F23 ),
	IC( SDL_SCANCODE_F24 ),
	IC( SDL_SCANCODE_EXECUTE ),
	IC( SDL_SCANCODE_HELP ),
	IC( SDL_SCANCODE_MENU ),
	IC( SDL_SCANCODE_SELECT ),
	IC( SDL_SCANCODE_STOP ),
	IC( SDL_SCANCODE_AGAIN ),
	IC( SDL_SCANCODE_UNDO ),
	IC( SDL_SCANCODE_CUT ),
	IC( SDL_SCANCODE_COPY ),
	IC( SDL_SCANCODE_PASTE ),
	IC( SDL_SCANCODE_FIND ),
	IC( SDL_SCANCODE_MUTE ),
	IC( SDL_SCANCODE_VOLUMEUP ),
	IC( SDL_SCANCODE_VOLUMEDOWN ),
	IC( SDL_SCANCODE_KP_COMMA ),
	IC( SDL_SCANCODE_KP_EQUALSAS400 ),
	
	IC( SDL_SCANCODE_INTERNATIONAL1 ),
	IC( SDL_SCANCODE_INTERNATIONAL2 ),
	IC( SDL_SCANCODE_INTERNATIONAL3 ),
	IC( SDL_SCANCODE_INTERNATIONAL4 ),
	IC( SDL_SCANCODE_INTERNATIONAL5 ),
	IC( SDL_SCANCODE_INTERNATIONAL6 ),
	IC( SDL_SCANCODE_INTERNATIONAL7 ),
	IC( SDL_SCANCODE_INTERNATIONAL8 ),
	IC( SDL_SCANCODE_INTERNATIONAL9 ),
	IC( SDL_SCANCODE_LANG1 ),
	IC( SDL_SCANCODE_LANG2 ),
	IC( SDL_SCANCODE_LANG3 ),
	IC( SDL_SCANCODE_LANG4 ),
	IC( SDL_SCANCODE_LANG5 ),
	IC( SDL_SCANCODE_LANG6 ),
	IC( SDL_SCANCODE_LANG7 ),
	IC( SDL_SCANCODE_LANG8 ),
	IC( SDL_SCANCODE_LANG9 ),
	
	IC( SDL_SCANCODE_ALTERASE ),
	IC( SDL_SCANCODE_SYSREQ ),
	IC( SDL_SCANCODE_CANCEL ),
	IC( SDL_SCANCODE_CLEAR ),
	IC( SDL_SCANCODE_PRIOR ),
	IC( SDL_SCANCODE_RETURN2 ),
	IC( SDL_SCANCODE_SEPARATOR ),
	IC( SDL_SCANCODE_OUT ),
	IC( SDL_SCANCODE_OPER ),
	IC( SDL_SCANCODE_CLEARAGAIN ),
	IC( SDL_SCANCODE_CRSEL ),
	IC( SDL_SCANCODE_EXSEL ),
	
	IC( SDL_SCANCODE_KP_00 ),
	IC( SDL_SCANCODE_KP_000 ),
	IC( SDL_SCANCODE_THOUSANDSSEPARATOR ),
	IC( SDL_SCANCODE_DECIMALSEPARATOR ),
	IC( SDL_SCANCODE_CURRENCYUNIT ),
	IC( SDL_SCANCODE_CURRENCYSUBUNIT ),
	IC( SDL_SCANCODE_KP_LEFTPAREN ),
	IC( SDL_SCANCODE_KP_RIGHTPAREN ),
	IC( SDL_SCANCODE_KP_LEFTBRACE ),
	IC( SDL_SCANCODE_KP_RIGHTBRACE ),
	IC( SDL_SCANCODE_KP_TAB ),
	IC( SDL_SCANCODE_KP_BACKSPACE ),
	IC( SDL_SCANCODE_KP_A ),
	IC( SDL_SCANCODE_KP_B ),
	IC( SDL_SCANCODE_KP_C ),
	IC( SDL_SCANCODE_KP_D ),
	IC( SDL_SCANCODE_KP_E ),
	IC( SDL_SCANCODE_KP_F ),
	IC( SDL_SCANCODE_KP_XOR ),
	IC( SDL_SCANCODE_KP_POWER ),
	IC( SDL_SCANCODE_KP_PERCENT ),
	IC( SDL_SCANCODE_KP_LESS ),
	IC( SDL_SCANCODE_KP_GREATER ),
	IC( SDL_SCANCODE_KP_AMPERSAND ),
	IC( SDL_SCANCODE_KP_DBLAMPERSAND ),
	IC( SDL_SCANCODE_KP_VERTICALBAR ),
	IC( SDL_SCANCODE_KP_DBLVERTICALBAR ),
	IC( SDL_SCANCODE_KP_COLON ),
	IC( SDL_SCANCODE_KP_HASH ),
	IC( SDL_SCANCODE_KP_SPACE ),
	IC( SDL_SCANCODE_KP_AT ),
	IC( SDL_SCANCODE_KP_EXCLAM ),
	IC( SDL_SCANCODE_KP_MEMSTORE ),
	IC( SDL_SCANCODE_KP_MEMRECALL ),
	IC( SDL_SCANCODE_KP_MEMCLEAR ),
	IC( SDL_SCANCODE_KP_MEMADD ),
	IC( SDL_SCANCODE_KP_MEMSUBTRACT ),
	IC( SDL_SCANCODE_KP_MEMMULTIPLY ),
	IC( SDL_SCANCODE_KP_MEMDIVIDE ),
	IC( SDL_SCANCODE_KP_PLUSMINUS ),
	IC( SDL_SCANCODE_KP_CLEAR ),
	IC( SDL_SCANCODE_KP_CLEARENTRY ),
	IC( SDL_SCANCODE_KP_BINARY ),
	IC( SDL_SCANCODE_KP_OCTAL ),
	IC( SDL_SCANCODE_KP_DECIMAL ),
	IC( SDL_SCANCODE_KP_HEXADECIMAL ),
	
	IC( SDL_SCANCODE_LCTRL ),
	IC( SDL_SCANCODE_LSHIFT ),
	IC( SDL_SCANCODE_LALT ),
	IC( SDL_SCANCODE_LGUI ),
	IC( SDL_SCANCODE_RCTRL ),
	IC( SDL_SCANCODE_RSHIFT ),
	IC( SDL_SCANCODE_RALT ),
	IC( SDL_SCANCODE_RGUI ),
	
	IC( SDL_SCANCODE_MODE ),
	
	IC( SDL_SCANCODE_AUDIONEXT ),
	IC( SDL_SCANCODE_AUDIOPREV ),
	IC( SDL_SCANCODE_AUDIOSTOP ),
	IC( SDL_SCANCODE_AUDIOPLAY ),
	IC( SDL_SCANCODE_AUDIOMUTE ),
	IC( SDL_SCANCODE_MEDIASELECT ),
	IC( SDL_SCANCODE_WWW ),
	IC( SDL_SCANCODE_MAIL ),
	IC( SDL_SCANCODE_CALCULATOR ),
	IC( SDL_SCANCODE_COMPUTER ),
	IC( SDL_SCANCODE_AC_SEARCH ),
	IC( SDL_SCANCODE_AC_HOME ),
	IC( SDL_SCANCODE_AC_BACK ),
	IC( SDL_SCANCODE_AC_FORWARD ),
	IC( SDL_SCANCODE_AC_STOP ),
	IC( SDL_SCANCODE_AC_REFRESH ),
	IC( SDL_SCANCODE_AC_BOOKMARKS ),
	
	IC( SDL_SCANCODE_BRIGHTNESSDOWN ),
	IC( SDL_SCANCODE_BRIGHTNESSUP ),
	IC( SDL_SCANCODE_DISPLAYSWITCH ),
	IC( SDL_SCANCODE_KBDILLUMTOGGLE ),
	IC( SDL_SCANCODE_KBDILLUMDOWN ),
	IC( SDL_SCANCODE_KBDILLUMUP ),
	IC( SDL_SCANCODE_EJECT ),
	IC( SDL_SCANCODE_SLEEP ),
	
	IC( SDL_SCANCODE_APP1 ),
	IC( SDL_SCANCODE_APP2 ),
	
	IC( SDL_NUM_SCANCODES ),
	
	/*  KEY MODIFIER FLAGS  */
	IC_SDL( KMOD_NONE ),
	IC_SDL( KMOD_NUM ),
	IC_SDL( KMOD_CAPS ),
	IC_SDL( KMOD_MODE ),
	IC_SDL( KMOD_LCTRL ),
	IC_SDL( KMOD_RCTRL ),
	IC_SDL( KMOD_RSHIFT ),
	IC_SDL( KMOD_LSHIFT ),
	IC_SDL( KMOD_RALT ),
	IC_SDL( KMOD_LALT ),
	IC_SDL( KMOD_RGUI ),
	IC_SDL( KMOD_LGUI ),
	IC_SDL( KMOD_CTRL ),
	IC_SDL( KMOD_SHIFT ),
	IC_SDL( KMOD_ALT ),
	IC_SDL( KMOD_GUI ),
	
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
	IC( SDL_WINDOW_OPENGLMAYBE ),
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

static int SS_SDL_WINDOWPOS_UNDEFINED_DISPLAY( SGS_CTX )
{
	sgs_PushInt( C, SDL_WINDOWPOS_UNDEFINED_DISPLAY( sgs_GetInt( C, 0 ) ) );
	return 1;
}

static int SS_SDL_WINDOWPOS_CENTERED_DISPLAY( SGS_CTX )
{
	sgs_PushInt( C, SDL_WINDOWPOS_CENTERED_DISPLAY( sgs_GetInt( C, 0 ) ) );
	return 1;
}

static sgs_RegFuncConst sdl_funcs[] =
{
	FN( SetError ), FN( GetError ),
	FN( EventState ),
	FN( GetNumTouchDevices ), FN( GetTouchDevice ), FN( GetTouchDevices ),
	FN( GetNumTouchFingers ), FN( GetTouchFinger ), FN( GetTouchFingers ),
	FN( RecordGesture ),
	FN( FlushEvents ), FN( HasEvents ),
	FN( PollEvent ), FN( WaitEvent ),
	FN( PeekEvents ), FN( GetEvents ),
	FN( PumpEvents ),
	FN( QuitRequested ),
	
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
	
	FN( GetKeyFromName ), FN( GetScancodeFromName ),
	FN( GetKeyFromScancode ), FN( GetScancodeFromKey ),
	FN( GetKeyName ), FN( GetScancodeName ),
	FN( GetKeyboardFocus ), FN( GetMouseFocus ),
	FN( GetModState ), FN( SetModState ),
	FN( HasScreenKeyboardSupport ),
	FN( IsTextInputActive ),
	FN( ShowCursor ), FN( SetSystemCursor ),
	FN( WarpMouse ),
	FN( GetMouseState ), FN( GetRelativeMouseState ),
	FN( GetRelativeMouseMode ), FN( SetRelativeMouseMode ),
	FN( StartTextInput ), FN( StopTextInput ), FN( SetTextInputRect ),
	
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
	case SDL_CONTROLLERAXISMOTION:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->caxis.which );
		sgs_PushString( C, "axis" );
		sgs_PushInt( C, event->caxis.axis );
		sgs_PushString( C, "value" );
		sgs_PushInt( C, event->caxis.value );
		break;
		
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->cbutton.which );
		sgs_PushString( C, "button" );
		sgs_PushInt( C, event->cbutton.button );
		sgs_PushString( C, "state" );
		sgs_PushInt( C, event->cbutton.state );
		break;
		
	case SDL_CONTROLLERDEVICEADDED:
	case SDL_CONTROLLERDEVICEREMOVED:
	case SDL_CONTROLLERDEVICEREMAPPED:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->cdevice.which );
		break;
		
	case SDL_DOLLARGESTURE:
		sgs_PushString( C, "touchID" );
		sgs_PushInt( C, event->dgesture.touchId );
		sgs_PushString( C, "gestureID" );
		sgs_PushInt( C, event->dgesture.gestureId );
		sgs_PushString( C, "numFingers" );
		sgs_PushInt( C, event->dgesture.numFingers );
		sgs_PushString( C, "error" );
		sgs_PushReal( C, event->dgesture.error );
		sgs_PushString( C, "x" );
		sgs_PushReal( C, event->dgesture.x );
		sgs_PushString( C, "y" );
		sgs_PushReal( C, event->dgesture.y );
		break;
		
	case SDL_DROPFILE:
		sgs_PushString( C, "file" );
		sgs_PushString( C, event->drop.file );
		break;
		
	case SDL_FINGERMOTION:
	case SDL_FINGERDOWN:
	case SDL_FINGERUP:
		sgs_PushString( C, "touchID" );
		sgs_PushInt( C, event->tfinger.touchId );
		sgs_PushString( C, "fingerID" );
		sgs_PushInt( C, event->tfinger.fingerId );
		sgs_PushString( C, "x" );
		sgs_PushReal( C, event->tfinger.x );
		sgs_PushString( C, "y" );
		sgs_PushReal( C, event->tfinger.y );
		sgs_PushString( C, "dx" );
		sgs_PushReal( C, event->tfinger.dx );
		sgs_PushString( C, "dy" );
		sgs_PushReal( C, event->tfinger.dy );
		sgs_PushString( C, "pressure" );
		sgs_PushReal( C, event->tfinger.pressure );
		break;
		
	case SDL_JOYAXISMOTION:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->jaxis.which );
		sgs_PushString( C, "axis" );
		sgs_PushInt( C, event->jaxis.axis );
		sgs_PushString( C, "value" );
		sgs_PushInt( C, event->jaxis.value );
		break;
		
	case SDL_JOYBALLMOTION:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->jball.which );
		sgs_PushString( C, "ball" );
		sgs_PushInt( C, event->jball.ball );
		sgs_PushString( C, "xrel" );
		sgs_PushInt( C, event->jball.xrel );
		sgs_PushString( C, "yrel" );
		sgs_PushInt( C, event->jball.yrel );
		break;
		
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->jbutton.which );
		sgs_PushString( C, "button" );
		sgs_PushInt( C, event->jbutton.button );
		sgs_PushString( C, "state" );
		sgs_PushInt( C, event->jbutton.state );
		break;
		
	case SDL_JOYDEVICEADDED:
	case SDL_JOYDEVICEREMOVED:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->jdevice.which );
		break;
		
	case SDL_JOYHATMOTION:
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->jhat.which );
		sgs_PushString( C, "hat" );
		sgs_PushInt( C, event->jhat.hat );
		sgs_PushString( C, "value" );
		sgs_PushInt( C, event->jhat.value );
		break;
		
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
		sgs_PushString( C, "clicks" );
		sgs_PushInt( C, event->button.clicks );
		sgs_PushString( C, "x" );
		sgs_PushInt( C, event->button.x );
		sgs_PushString( C, "y" );
		sgs_PushInt( C, event->button.y );
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
		
	case SDL_MOUSEWHEEL:
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->wheel.windowID );
		sgs_PushString( C, "which" );
		sgs_PushInt( C, event->wheel.which );
		sgs_PushString( C, "x" );
		sgs_PushInt( C, event->wheel.x );
		sgs_PushString( C, "y" );
		sgs_PushInt( C, event->wheel.y );
		break;
		
	case SDL_MULTIGESTURE:
		sgs_PushString( C, "touchID" );
		sgs_PushInt( C, event->mgesture.touchId );
		sgs_PushString( C, "dTheta" );
		sgs_PushReal( C, event->mgesture.dTheta );
		sgs_PushString( C, "dDist" );
		sgs_PushReal( C, event->mgesture.dDist );
		sgs_PushString( C, "x" );
		sgs_PushReal( C, event->mgesture.x );
		sgs_PushString( C, "y" );
		sgs_PushReal( C, event->mgesture.y );
		sgs_PushString( C, "numFingers" );
		sgs_PushInt( C, event->mgesture.numFingers );
		break;
		
	case SDL_QUIT: break;
	case SDL_SYSWMEVENT: /* TODO */ break;
		
	case SDL_TEXTEDITING:
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->edit.windowID );
		sgs_PushString( C, "text" );
		sgs_PushString( C, event->edit.text );
		sgs_PushString( C, "start" );
		sgs_PushInt( C, event->edit.start );
		sgs_PushString( C, "length" );
		sgs_PushInt( C, event->edit.length );
		break;
		
	case SDL_TEXTINPUT:
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->text.windowID );
		sgs_PushString( C, "text" );
		sgs_PushString( C, event->text.text );
		break;
		
	case SDL_WINDOWEVENT:
		if( event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
		{
			int modlist[] = { SS_RMOD_WIDTH, event->window.data1, SS_RMOD_HEIGHT, event->window.data2, 0 };
			SS_Window* W = SS_Window_from_id( event->window.windowID );
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
		
	default:
		sgs_PushString( C, "windowID" );
		sgs_PushInt( C, event->user.windowID );
		sgs_PushString( C, "code" );
		sgs_PushInt( C, event->user.code );
		sgs_PushString( C, "data1" );
		sgs_PushPtr( C, event->user.data1 );
		sgs_PushString( C, "data2" );
		sgs_PushPtr( C, event->user.data2 );
		break;
		
	}
	
	ret = sgs_PushDict( C, sgs_StackSize( C ) - osz );
	if( ret != SGS_SUCCESS )
		sgs_Pop( C, sgs_StackSize( C ) - osz );
	return ret;
}
