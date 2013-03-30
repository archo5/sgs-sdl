
#include "ss_main.h"


static const char* util_parseargs_str = "\
global sys_args, sys_parsedargs = {};\
for( var a, i = 1; i < sys_args.size; ++i )\
	if( string_part( a = sys_args[ i ], 0, 1 ) == '-' )\
		sys_parsedargs[ string_part( a, 1 ) ] = sys_args[ ++i ];\
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
	
	/* run the main file */
	ret = sgs_ExecFile( C, "main.sgs" );
	if( ret != SGS_SUCCESS )
	{
		fprintf( stderr, "Could not execute 'main.sgs', error %d.", ret );
		return 1;
	}
	
	/* pass some variables */
	sgs_PushBool( C, 0 ); sgs_SetGlobal( C, "sys_exit" );
	{
		int i;
		sgs_GetGlobal( C, "array" );
		for( i = 0; i < argc; ++i )
		{
			sgs_PushString( C, argv[ i ] );
		}
		sgs_Call( C, argc, 1 );
		sgs_SetGlobal( C, "sys_args" );
		
		/* parse the arguments to a dictionary */
		sgs_EvalString( C, util_parseargs_str, NULL );
	}
	
	/* configure the framework */
	if( sgs_GetGlobal( C, "sys_configure" ) || !sgs_Call( C, 0, 0 ) )
	{
		fprintf( stderr, "Failed to configure the framework." );
		return 1;
	}
	
	return 0;
}
