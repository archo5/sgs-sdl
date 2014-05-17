

#define SS_IS_LAUNCHER 1

#if defined _WIN32 && defined SS_RELEASE
#include <windows.h>
#endif

#include "ss_main.h"


#undef main
#if defined _WIN32 && defined SS_RELEASE
#  define SS_ARG_DEBUG 0
int CALLBACK WinMain( HINSTANCE hinst, HINSTANCE hprevinst, LPSTR cmdline, int ncmdshow )
#else
#  if defined SS_RELEASE
#    define SS_ARG_DEBUG 0
#  else
#    define SS_ARG_DEBUG 1
#  endif
int main( int argc, char* argv[] )
#endif
{
	int ret;
	
#if defined _WIN32 && defined SS_RELEASE
	int i, argc, totalsize = 0;
	char** argv = NULL, *p;
	LPWSTR *argv_w;
	
	argv_w = CommandLineToArgvW( GetCommandLineW(), &argc );
	if( !argv_w )
		return -201;
	
	for( i = 0; i < argc; ++i )
		totalsize += WideCharToMultiByte( CP_UTF8, 0, argv_w[i], lstrlenW( argv_w[i] ) + 1, NULL, 0, NULL, NULL );
	
	argv = (char**) malloc( sizeof(*argv) * argc + totalsize );
	p = (char*)( argv + argc );
	
	for( i = 0; i < argc; ++i )
	{
		int size = WideCharToMultiByte( CP_UTF8, 0, argv_w[i], lstrlenW( argv_w[i] ) + 1, p, totalsize, NULL, NULL );
		totalsize -= size;
		argv[ i ] = p;
		p += size;
	}
	
	LocalFree( argv_w );
#endif
	
	ret = ss_Initialize( argc, argv, SS_ARG_DEBUG );
	
#if defined _WIN32 && defined SS_RELEASE
	free( argv );
#endif
	
	if( ret < 0 )
		return ret; /* error */
	if( ret == 0 )
		return 0; /* premature exit */
	
	for(;;)
	{
		ret = ss_Frame();
		if( ret < 0 )
			return -101; /* error */
		if( ret > 0 )
			break;
	}
	
	ret = ss_Free();
	
	return ret;
}

