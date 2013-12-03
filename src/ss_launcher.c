

#define SS_IS_LAUNCHER 1

#include "ss_main.h"


#undef main
int main( int argc, char* argv[] )
{
	int ret;
	
	ret = ss_Initialize( argc, argv );
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

