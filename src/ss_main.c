
#include "ss_main.h"

#include "../sgscript/ext/sgs_idbg.h"
#include "../sgscript/ext/sgs_prof.h"


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
;


sgs_MemBuf g_tmpbuf;



SGS_CTX;
sgs_IDbg D;
sgs_Prof P;


sgs_Context* ss_GetContext(){ return C; }


int g_enabledProfiler = 0;

int SS_EnableProfiler( SGS_CTX )
{
	SGSFN( "SS_EnableProfiler" );
	if( sgs_StackSize( C ) > 0 )
		g_enabledProfiler = sgs_GetInt( C, 0 );
	else
		g_enabledProfiler = 1;
	return 0;
}

int ss_InitDebug( SGS_CTX )
{
	sgs_PushCFunction( C, SS_EnableProfiler );
	sgs_StoreGlobal( C, "SS_EnableProfiler" );
	return SGS_SUCCESS;
}


void* ss_request_memory( size_t numbytes )
{
	sgs_membuf_resize( &g_tmpbuf, C, g_tmpbuf.size + numbytes );
	return g_tmpbuf.ptr + g_tmpbuf.size - numbytes;
}
void ss_reset_buffer()
{
	sgs_membuf_resize( &g_tmpbuf, C, 0 );
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
	sgs_GlobalCall( C, "loadtypeflags", 0, 0 );

	ss_InitDebug( C );
	ss_InitExtSys( C );
	ss_InitExtMath( C );
	ss_InitImage( C );
	
	/* preinit tmp buffer */
	g_tmpbuf = sgs_membuf_create();
	sgs_membuf_reserve( &g_tmpbuf, C, 1024 );
	
	/* load command line arguments */
	{
		int i;
		for( i = 1; i < argc; ++i )
		{
			sgs_PushString( C, argv[ i ] );
		}
		sgs_PushArray( C, argc - 1 );
		sgs_StoreGlobal( C, "sys_args" );
	}
	
	/* push some system info */
	sgs_PushPtr( C, C );
	sgs_StoreGlobal( C, "sys_scripting_engine" );
	
	/* run the preconfig script */
	sgs_ExecString( C, scr_preconfig );

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
	
	/* configure the framework (optional) */
	sgs_GlobalCall( C, "configure", 0, 0 );

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
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE ) < 0 )
	{
		fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
		return -5;
	}
	
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	
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
	if( ss_GlobalInt( C, "sys_exit" ) )
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
		
		if( ss_GlobalInt( C, "sys_exit" ) )
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

	if( g_enabledProfiler )
	{
		sgs_ProfDump( &P );
		sgs_ProfClose( &P );
	}

	sgs_CloseIDbg( C, &D );
	sgs_DestroyEngine( C );
	
	ss_FreeGraphics( C );
	
	return 0;
}

