
#include <SDL/SDL_syswm.h>

#include "ss_main.h"

#include "../sgscript/ext/sgs_idbg.h"
#include "../sgscript/ext/sgs_prof.h"


const char* scr_globalvars = "global \
sys_exit = false;\
";


SGS_CTX;
sgs_IDbg D;
sgs_Prof P;

int g_enabledProfiler = 0;

int ss_enable_profiler( SGS_CTX )
{
	g_enabledProfiler = 1;
	return 0;
}

int ss_enable_profiler2( SGS_CTX )
{
	g_enabledProfiler = 2;
	return 0;
}

int sgs_InitDebug( SGS_CTX )
{
	sgs_PushCFunction( C, ss_enable_profiler );
	sgs_StoreGlobal( C, "enable_profiler" );
	sgs_PushCFunction( C, ss_enable_profiler2 );
	sgs_StoreGlobal( C, "enable_profiler2" );
	return SGS_SUCCESS;
}


int ss_Initialize( int argc, char* argv[] )
{
	int ret;
	
	C = sgs_CreateEngine();
	sgs_InitIDbg( C, &D );
	
	/* preinit first-use libs */
	sgs_LoadLib_Fmt( C );
	sgs_LoadLib_IO( C );
	sgs_LoadLib_Math( C );
	sgs_LoadLib_OS( C );
	sgs_LoadLib_RE( C );
	sgs_LoadLib_String( C );
	if( sgs_GlobalCall( C, "loadtypeflags", 0, 0 ) != SGS_SUCCESS )
	{
		fprintf( stderr, "Failed to initialize the scripting engine\n" );
		return -1;
	}

	sgs_InitDebug( C );
	sgs_InitExtSys( C );
	sgs_InitExtMath( C );
	sgs_InitImage( C );
	sgs_InitAPI( C );

	/* run the config file */
	ret = sgs_Include( C, "engine/all" );
	if( !ret )
	{
		fprintf( stderr, "Could not set up engine scripts.\n" );
		return -2;
	}
	
	/* run the main file */
	ret = sgs_Include( C, "main" );
	if( !ret )
	{
		fprintf( stderr, "Could not execute 'main'.\n" );
		return -3;
	}
	
	/* create some variables */
	sgs_ExecString( C, scr_globalvars );
	{
		int i;
		
		sgs_PushString( C, argv[ 0 ] );
		sgs_StoreGlobal( C, "sys_execname" );
		
		for( i = 1; i < argc; ++i )
		{
			sgs_PushString( C, argv[ i ] );
		}
		sgs_PushArray( C, argc - 1 );
		sgs_StoreGlobal( C, "sys_args" );
	}
	
	/* configure the framework (optional) */
	if( sgs_GlobalCall( C, "configure", 0, 0 ) )
	{
		fprintf( stderr, "Failed to configure the framework.\n" );
		return -4;
	}

	if( g_enabledProfiler )
		sgs_ProfInit( C, &P, g_enabledProfiler );
	
	/* check if already required to exit */
	{
		int b;
		sgs_PushGlobal( C, "sys_exit" );
		b = sgs_GetBool( C, -1 );
		if( b )
			return 0;
		sgs_Pop( C, 1 );
	}
	
	/* initialize SDL */
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
		return -5;
	}
	SDL_EnableUNICODE( 1 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	
	/* initialize script-space SDL API */
	if( sgs_InitSDL( C ) )
	{
		fprintf( stderr, "Couldn't initialize SDL API\n" );
		return -6;
	}
	
	/* initialize script-space rendering API */
	if( sgs_InitGL( C ) )
	{
		fprintf( stderr, "Couldn't initialize rendering API\n" );
		return -7;
	}
	
	/* initialize the application */
	if( sgs_GlobalCall( C, "initialize", 0, 0 ) )
	{
		fprintf( stderr, "Failed to initialize the application.\n" );
		return -8;
	}
	
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
			if( sgs_CreateSDLEvent( C, &event ) || sgs_GlobalCall( C, "on_event", 1, 0 ) )
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

	if( g_enabledProfiler )
	{
		sgs_ProfDump( &P );
		sgs_ProfClose( &P );
	}

	sgs_CloseIDbg( C, &D );
	sgs_DestroyEngine( C );
	
	sgs_FreeGraphics( C );
	
	return 0;
}

void* ss_GetPtr( int pid )
{
	switch( pid )
	{
	case SS_PTR_SGSCTX: return C;
	case SS_PTR_WINDOW:
		{
			SDL_SysWMinfo sysinfo;
			SDL_VERSION( &sysinfo.version );
			if( SDL_GetWMInfo( &sysinfo ) <= 0 )
				return NULL;
			return (void*) sysinfo.window;
		}
	case SS_PTR_D3DDEV: return GD3DDev;
	}
	return NULL;
}

