
#ifdef _WIN32
#  include <rpc.h>
#else
#  include <uuid/uuid.h>
#endif

#include "ss_main.h"

#include <sgs_idbg.h>
#include <sgs_prof.h>


static const char* scr_preconfig =
	"global sys_exit = false;\n"
	"global sys_wait_events = false;\n"
	"global sys_initial_dir = io_getcwd();\n"
	"io_setcwd( sys_curprocdir() );\n"
;


static sgs_MemBuf g_tmpbuf;



static sgs_Context* g_C;
static sgs_IDbg D;
static sgs_Prof P;


sgs_Context* ss_GetContext(){ return g_C; }


/* #define SS_STARTUP_PROFILING 1 */


static int GEnabledProfiler = 0;
static int GEnabledDebugging = 0;

static int SS_EnableProfiler( SGS_CTX )
{
	SGSFN( "SS_EnableProfiler" );
	if( sgs_StackSize( C ) > 0 )
		GEnabledProfiler = sgs_GetInt( C, 0 );
	else
		GEnabledProfiler = 1;
	return 0;
}

static int SS_GenerateGUID( SGS_CTX )
{
	SGSFN( "SS_GenerateGUID" );
	static const char* hex = "0123456789abcdef";
	char bfr[ 36 ], *p, sep = '-';
	uint8_t out[ 16 ], *bp;
#ifdef _WIN32
	UUID uuid;
	UuidCreate( &uuid );
	memcpy( out, &uuid, sizeof(out) );
#else
	uuid_t uuid;
	uuid_generate( uuid );
	memcpy( out, uuid, sizeof(out) );
#endif
	
	p = bfr;
	bp = out;
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = sep;
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = sep;
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = sep;
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = sep;
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	*p++ = hex[ *bp >> 4 ]; *p++ = hex[ *bp++ & 0xf ];
	
	sgs_PushStringBuf( C, bfr, 36 );
	return 1;
}

static const sgs_RegFuncConst rfc_helpers[] =
{
	{ "SS_EnableProfiler", SS_EnableProfiler },
	{ "SS_GenerateGUID", SS_GenerateGUID },
	{ NULL, NULL },
};

static int ss_InitHelpers( SGS_CTX )
{
	sgs_RegFuncConsts( C, rfc_helpers, -1 );
	return SGS_SUCCESS;
}


char* ss_GetBufferPtr()
{
	return g_tmpbuf.ptr;
}
char* ss_RequestMemory( size_t numbytes )
{
	sgs_membuf_resize( &g_tmpbuf, g_C, g_tmpbuf.size + numbytes );
	return g_tmpbuf.ptr + g_tmpbuf.size - numbytes;
}
void ss_ResetBuffer()
{
	sgs_membuf_resize( &g_tmpbuf, g_C, 0 );
}


static void ss_MsgFunc( void* unused, SGS_CTX, int type, const char* message )
{
	if( type >= SGS_ERROR )
	{
		sgs_PushErrorInfo( C, SGS_ERRORINFO_FULL, type, message );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Script error", sgs_GetStringPtr( C, -1 ), NULL );
		exit( -1 );
	}
}


int ss_Initialize( int argc, char* argv[], int debug )
{
	int ret;
	SGS_CTX;
	
	GEnabledDebugging = debug;
	
#if SS_STARTUP_PROFILING
	printf( "ss_Initialize called: %f\n", sgs_GetTime() );
#endif
	
	C = g_C = sgs_CreateEngine();
	
#if SS_STARTUP_PROFILING
	printf( "SGS engine created: %f\n", sgs_GetTime() );
#endif
	
	if( GEnabledDebugging )
		sgs_InitIDbg( C, &D );
	else
		sgs_SetMsgFunc( C, ss_MsgFunc, NULL );
	
#if SS_STARTUP_PROFILING
	printf( "debug printing initialized: %f\n", sgs_GetTime() );
#endif
	
	/* preinit first-use libs */
	sgs_LoadLib_Fmt( C );
	sgs_LoadLib_IO( C );
	sgs_LoadLib_Math( C );
	sgs_LoadLib_OS( C );
	sgs_LoadLib_RE( C );
	sgs_LoadLib_String( C );
	
#if SS_STARTUP_PROFILING
	printf( "SGS libraries loaded: %f\n", sgs_GetTime() );
#endif
	
	ss_InitHelpers( C );
	ss_InitExtMath( C );
	ss_InitImage( C );
	
#if SS_STARTUP_PROFILING
	printf( "SS libraries loaded: %f\n", sgs_GetTime() );
#endif
	
	/* preinit tmp buffer */
	g_tmpbuf = sgs_membuf_create();
	sgs_membuf_reserve( &g_tmpbuf, C, 1024 );
	
	/* load command line arguments */
	{
		int i;
		for( i = 0; i < argc; ++i )
		{
			sgs_PushString( C, argv[ i ] );
		}
		sgs_CreateArray( C, NULL, argc );
		sgs_SetGlobalByName( C, "sys_args", sgs_StackItem( C, -1 ) );
		sgs_Pop( C, 1 );
	}
	
	/* push some system info */
	sgs_SetGlobalByName( C, "sys_scripting_engine", sgs_MakePtr( C ) );
	
#if SS_STARTUP_PROFILING
	printf( "system info pushed: %f\n", sgs_GetTime() );
#endif
	
	/* run the preconfig script */
	sgs_ExecString( C, scr_preconfig );
	
#if SS_STARTUP_PROFILING
	printf( "preconfig done: %f\n", sgs_GetTime() );
#endif
	
	/* run the config file */
	ret = sgs_Include( C, "core/config" );
	if( !ret )
	{
		sgs_Msg( C, SGS_ERROR, "Could not run core/config (configuration script)." );
		return -2;
	}
	/* run the primary extensions */
	ret = sgs_Include( C, "core/ext" );
	if( !ret )
	{
		sgs_Msg( C, SGS_ERROR, "Could not run core/ext." );
		return -2;
	}
	
#if SS_STARTUP_PROFILING
	printf( "configured engine scripts: %f\n", sgs_GetTime() );
#endif
	
	/* run the main file */
	ret = sgs_Include( C, "main" );
	if( !ret )
	{
		sgs_Msg( C, SGS_ERROR, "Could not execute 'main'." );
		return -3;
	}
	
#if SS_STARTUP_PROFILING
	printf( "ran main script: %f\n", sgs_GetTime() );
#endif
	
	/* configure the framework (optional) */
	sgs_GlobalCall( C, "configure", 0, 0 );
	
#if SS_STARTUP_PROFILING
	printf( "called 'configure': %f\n", sgs_GetTime() );
#endif
	
	/* check if already required to exit */
	if( sgs_GlobalBool( C, "sys_exit" ) )
		return 0;
	
	if( GEnabledProfiler )
		sgs_ProfInit( C, &P, GEnabledProfiler );
	
#if SS_STARTUP_PROFILING
	printf( "pre-SDL init: %f\n", sgs_GetTime() );
#endif
	
	/* initialize SDL */
	if( SDL_Init(
		SDL_INIT_TIMER | SDL_INIT_VIDEO |
		SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC |
		SDL_INIT_GAMECONTROLLER |
		SDL_INIT_EVENTS | SDL_INIT_NOPARACHUTE
	) < 0 )
	{
		sgs_Msg( C, SGS_ERROR, "Couldn't initialize SDL: %s", SDL_GetError() );
		return -5;
	}
	
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	
#if SS_STARTUP_PROFILING
	printf( "post-SDL init: %f\n", sgs_GetTime() );
#endif
	
	/* initialize script-space SDL API */
	ss_InitSDL( C );
	
	/* initialize script-space rendering API */
	ss_InitGraphics( C );
	
#if SS_STARTUP_PROFILING
	printf( "initialized SDL/Graphics subsystems: %f\n", sgs_GetTime() );
#endif
	
	/* initialize the application */
	if( SGS_FAILED( sgs_GlobalCall( C, "initialize", 0, 0 ) ) )
	{
		sgs_Msg( C, SGS_ERROR, "Failed to initialize the application." );
		return -8;
	}
	
#if SS_STARTUP_PROFILING
	printf( "called 'initialize': %f\n", sgs_GetTime() );
#endif
	
	return 1;
}

int ss_Frame()
{
	SGS_CTX = g_C;
	if( sgs_GlobalInt( C, "sys_exit" ) )
		return 1;
	
	{
		int wait = sgs_GlobalBool( C, "sys_wait_events" );
		SDL_Event event;
		while( wait ? SDL_WaitEvent( &event ) : SDL_PollEvent( &event ) )
		{
			int ssz = sgs_StackSize( C );
			if( event.type == SDL_KEYDOWN && event.key.state == SDL_PRESSED &&
				event.key.keysym.sym == SDLK_F4 && ( event.key.keysym.mod & KMOD_ALT ) )
			{
				sgs_ExecString( C, "global sys_exit = true;" );
				break;
			}
			ss_CreateSDLEvent( C, &event );
			if( SGS_FAILED( sgs_GlobalCall( C, "on_event", 1, 0 ) ) )
			{
				sgs_Msg( C, SGS_ERROR, "error in event creation" );
				sgs_Pop( C, sgs_StackSize( C ) - ssz );
				
				// provide default handler
				if( event.type == SDL_QUIT )
				{
					sgs_ExecString( C, "global sys_exit = true;" );
					return 1;
				}
			}
		}
		
		if( sgs_GlobalInt( C, "sys_exit" ) )
			return 1;
		
		/* advance the application exactly one frame */
		if( SGS_FAILED( sgs_GlobalCall( C, "update", 0, 0 ) ) )
		{
			sgs_Msg( C, SGS_ERROR, "Failed to update the application." );
			return -1;
		}
	}
	
	return 0;
}

int ss_Free()
{
	SGS_CTX = g_C;
	/* clean the application */
	if( SGS_FAILED( sgs_GlobalCall( C, "cleanup", 0, 0 ) ) )
	{
		sgs_Msg( C, SGS_ERROR, "Failed to clean the application." );
		return -1;
	}
	
	sgs_membuf_destroy( &g_tmpbuf, C );
	
	if( GEnabledProfiler )
	{
		sgs_ProfDump( C, &P );
		sgs_ProfClose( C, &P );
	}
	
	if( GEnabledDebugging )
		sgs_CloseIDbg( C, &D );
	sgs_DestroyEngine( C );
	
	ss_FreeGraphics( C );
	
	return 0;
}

