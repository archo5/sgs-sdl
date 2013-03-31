
#include "ss_main.h"


const char* scr_globalvars = "global \
sys_exit = false;\
";


int main( int argc, char* argv[] )
{
	int ret;
	sgs_Context* C;
	
	C = sgs_CreateEngine();
	
	/* preinit first-use libs */
	sgs_LoadLib_Math( C );
	sgs_LoadLib_String( C );
	sgs_LoadLib_Type( C );
	sgs_InitExtSys( C );
	sgs_InitExtMath( C );
	
	/* run the main file */
	ret = sgs_ExecFile( C, "main.sgs" );
	if( ret != SGS_SUCCESS )
	{
		fprintf( stderr, "Could not execute 'main.sgs', error %d.\n", ret );
		return 1;
	}
	
	/* create some variables */
	sgs_ExecString( C, scr_globalvars );
	{
		int i;
		
		sgs_PushString( C, argv[ 0 ] );
		sgs_SetGlobal( C, "sys_execname" );
		
		for( i = 1; i < argc; ++i )
		{
			sgs_PushString( C, argv[ i ] );
		}
		sgs_GlobalCall( C, "array", argc - 1, 1 );
		sgs_SetGlobal( C, "sys_args" );
	}
	
	/* configure the framework (optional) */
	if( sgs_GlobalCall( C, "configure", 0, 0 ) )
	{
		fprintf( stderr, "Failed to configure the framework.\n" );
		return 1;
	}
	
	/* check if already required to exit */
	{
		int b;
		sgs_GetGlobal( C, "sys_exit" );
		b = sgs_GetBool( C, -1 );
		if( b )
			return 0;
		sgs_Pop( C, 1 );
	}
	
	printf( "\n\n-- sgs-sdl framework --\n\n" );
	
	/* initialize SDL */
	SDL_EnableUNICODE( 1 );
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
		return 1;
	}
	printf( "\ninitialized...\n" );
	
	/* initialize script-space SDL API */
	if( sgs_InitSDL( C ) != SGS_SUCCESS )
	{
		fprintf( stderr, "Couldn't initialize SDL API\n" );
		return 1;
	}
	printf( "SDL API initialized...\n" );
	
	/* initialize the application */
	if( sgs_GlobalCall( C, "initialize", 0, 0 ) )
	{
		fprintf( stderr, "Failed to initialize the application.\n" );
		return 1;
	}
	
	while( !sgs_GlobalInt( C, "sys_exit" ) )
	{
		SDL_Event event;
		while( SDL_PollEvent( &event ) )
		{
			int ssz = sgs_StackSize( C );
			if( sgs_CreateSDLEvent( C, &event ) || sgs_GlobalCall( C, "on_event", 1, 0 ) )
			{
				fprintf( stderr, "error in event creation\n" );
				sgs_Pop( C, sgs_StackSize( C ) - ssz );
				
				// provide default handler
				if( event.type == SDL_QUIT )
				{
					sgs_ExecString( C, "global sys_exit = true;" );
					break;
				}
			}
		}
		
		if( sgs_GlobalInt( C, "sys_exit" ) )
			break;
	
		/* advance the application exactly one frame */
		if( sgs_GlobalCall( C, "update", 0, 0 ) )
		{
			fprintf( stderr, "Failed to clean the application.\n" );
			return 1;
		}
	}
	
	/* clean the application */
	if( sgs_GlobalCall( C, "cleanup", 0, 0 ) )
	{
		fprintf( stderr, "Failed to clean the application.\n" );
		return 1;
	}
	sgs_DestroyEngine( C );
	
	return 0;
}
