

#include "ss3d_engine.h"

#define FN( x ) { "SS3D_" #x, SS3D_##x }


void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX )
{
	R->C = C;
	R->destroying = 0;
	sgs_vht_init( &R->resources, C, 128, 128 );
	sgs_vht_init( &R->shaders, C, 128, 128 );
	sgs_vht_init( &R->materials, C, 128, 128 );
	R->currentScene = NULL;
}

void SS3D_Renderer_Destruct( SS3D_Renderer* R )
{
	R->destroying = 1;
	sgs_vht_free( &R->resources, R->C );
	sgs_vht_free( &R->shaders, R->C );
	sgs_vht_free( &R->materials, R->C );
	if( R->currentScene )
		sgs_ObjRelease( R->C, R->currentScene );
}

void SS3D_Renderer_Update( SS3D_Renderer* R, float dt )
{
}

void SS3D_Renderer_Resize( SS3D_Renderer* R, int w, int h )
{
	R->width = w;
	R->height = h;
}


static int SS3D_CreateRenderer( SGS_CTX )
{
	char* rendererType;
	sgs_Int version = 0;
	void* device = NULL;
	
	SGSFN( "SS3D_CreateRenderer" );
	if( !sgs_LoadArgs( C, "s|i&", &rendererType, &version, &device ) )
		return 0;
	
	if( !strcmp( rendererType, "D3D9" ) && !device )
		return sgs_Printf( C, SGS_WARNING, "Direct3D requires a device pointer (argument 3)" );
	
	if( !strcmp( rendererType, "D3D9" ) )
		return SS3D_PushRenderer_D3D9( C, device );
	else if( !strcmp( rendererType, "GL" ) )
		return SS3D_PushRenderer_GL( C, version );
	else
		return sgs_Printf( C, SGS_WARNING, "unsupported renderer type" );
}


static sgs_RegFuncConst ss3d_fconsts[] =
{
	FN( CreateRenderer ),
};


SGS_APIFUNC int sgscript_main( SGS_CTX )
{
	sgs_RegFuncConsts( C, ss3d_fconsts, sizeof(ss3d_fconsts) / sizeof(ss3d_fconsts[0]) );
	if( !sgs_Include( C, "ss3d/engine" ) )
		return SGS_EINPROC;
	return SGS_SUCCESS;
}

