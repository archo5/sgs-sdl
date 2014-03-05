
#include "ss_main.h"

#include <sgs_idbg.h>
#include <sgs_prof.h>


static const char* scr_preconfig =
	"_dirname = function(s){p=string_find_rev(s,'/');\n"
	"	if(p===null){ p=string_find(s,':'); if(p===null){ return ''; } p++; }\n"
	"	return string_part(s,0,p);};\n"
	"\n"
	"global sys_exit = false;\n"
	"global sys_initial_dir = io_getcwd();\n"
	"global sys_executable_path = string_replace( io_getexecpath(), '\\\\', '/' );\n"
	"global sys_executable_dir = _dirname( sys_executable_path );\n"
	"io_setcwd( sys_executable_dir );\n"
	"\n"
	"function min( a, b ){ return if( a < b, a, b ); }\n"
	"function max( a, b ){ return if( a > b, a, b ); }\n"
;


static sgs_MemBuf g_tmpbuf;



static SGS_CTX;
static sgs_IDbg D;
static sgs_Prof P;


sgs_Context* ss_GetContext(){ return C; }


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

static int ss_InitDebug( SGS_CTX )
{
	sgs_PushCFunction( C, SS_EnableProfiler );
	sgs_StoreGlobal( C, "SS_EnableProfiler" );
	return SGS_SUCCESS;
}


char* ss_GetBufferPtr()
{
	return g_tmpbuf.ptr;
}
char* ss_RequestMemory( size_t numbytes )
{
	sgs_membuf_resize( &g_tmpbuf, C, g_tmpbuf.size + numbytes );
	return g_tmpbuf.ptr + g_tmpbuf.size - numbytes;
}
void ss_ResetBuffer()
{
	sgs_membuf_resize( &g_tmpbuf, C, 0 );
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
	
	GEnabledDebugging = debug;
	
#if SS_STARTUP_PROFILING
	printf( "ss_Initialize called: %f\n", sgs_GetTime() );
#endif
	
	C = sgs_CreateEngine();
	
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
	
	ss_InitDebug( C );
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
		sgs_PushArray( C, argc );
		sgs_StoreGlobal( C, "sys_args" );
	}
	
	/* push some system info */
	sgs_PushPtr( C, C );
	sgs_StoreGlobal( C, "sys_scripting_engine" );
	
#if SS_STARTUP_PROFILING
	printf( "system info pushed: %f\n", sgs_GetTime() );
#endif
	
	/* run the preconfig script */
	sgs_ExecString( C, scr_preconfig );
	
#if SS_STARTUP_PROFILING
	printf( "preconfig done: %f\n", sgs_GetTime() );
#endif
	
	/* run the config file */
	ret = sgs_Include( C, "engine/all" );
	if( !ret )
	{
		fprintf( stderr, "Could not set up engine scripts.\n" );
		return -2;
	}
	
#if SS_STARTUP_PROFILING
	printf( "configured engine scripts: %f\n", sgs_GetTime() );
#endif
	
	/* run the main file */
	ret = sgs_Include( C, "main" );
	if( !ret )
	{
		fprintf( stderr, "Could not execute 'main'.\n" );
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
	
	if( GEnabledProfiler )
		sgs_ProfInit( C, &P, GEnabledProfiler );
	
	/* check if already required to exit */
	{
		int b;
		sgs_PushGlobal( C, "sys_exit" );
		b = sgs_GetBool( C, -1 );
		if( b )
			return 0;
		sgs_Pop( C, 1 );
	}
	
#if SS_STARTUP_PROFILING
	printf( "pre-SDL init: %f\n", sgs_GetTime() );
#endif
	
	/* initialize SDL */
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE ) < 0 )
	{
		fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
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
	if( ss_InitSDL( C ) )
	{
		fprintf( stderr, "Couldn't initialize SDL API\n" );
		return -6;
	}
	
	/* initialize script-space rendering API */
	if( ss_InitGraphics( C ) )
	{
		fprintf( stderr, "Couldn't initialize rendering API\n" );
		return -7;
	}
	
#if SS_STARTUP_PROFILING
	printf( "initialized SDL/Graphics subsystems: %f\n", sgs_GetTime() );
#endif
	
	/* initialize the application */
	if( sgs_GlobalCall( C, "initialize", 0, 0 ) )
	{
		fprintf( stderr, "Failed to initialize the application.\n" );
		return -8;
	}
	
#if SS_STARTUP_PROFILING
	printf( "called 'initialize': %f\n", sgs_GetTime() );
#endif
	
	return 1;
}

int ss_Frame()
{
	if( sgs_GlobalInt( C, "sys_exit" ) )
		return 1;
	
	{
		SDL_Event event;
		while( SDL_PollEvent( &event ) )
		{
			int ssz = sgs_StackSize( C );
			if( event.type == SDL_KEYDOWN && event.key.state == SDL_PRESSED &&
				event.key.keysym.sym == SDLK_F4 && ( event.key.keysym.mod & KMOD_ALT ) )
			{
				sgs_ExecString( C, "global sys_exit = true;" );
				break;
			}
			if( ss_CreateSDLEvent( C, &event ) || sgs_GlobalCall( C, "on_event", 1, 0 ) )
			{
				fprintf( stderr, "error in event creation\n" );
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
		if( sgs_GlobalCall( C, "update", 0, 0 ) )
		{
			fprintf( stderr, "Failed to update the application.\n" );
			return -1;
		}
	}
	
	return 0;
}

int ss_Free()
{
	/* clean the application */
	if( sgs_GlobalCall( C, "cleanup", 0, 0 ) )
	{
		fprintf( stderr, "Failed to clean the application.\n" );
		return -1;
	}
	
	sgs_membuf_destroy( &g_tmpbuf, C );
	
	if( GEnabledProfiler )
	{
		sgs_ProfDump( &P );
		sgs_ProfClose( &P );
	}
	
	if( GEnabledDebugging )
		sgs_CloseIDbg( C, &D );
	sgs_DestroyEngine( C );
	
	ss_FreeGraphics( C );
	
	return 0;
}

