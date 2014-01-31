

/* SS3D Rendering Engine */


#include <sgscript.h>
#include <sgs_util.h>
#include <sgsxgmath.h>


#define SS3DCULL_AABB   1
#define SS3DCULL_OBB    2
#define SS3DCULL_SPHERE 3
#define SS3DCULL_CONE   4

#define S3DLIGHT_POINT  1
#define S3DLIGHT_SPOT   2
#define S3DLIGHT_DIRECT 3

#define S3DINDEX_16 1
#define S3DINDEX_32 2


typedef struct _SS3D_Renderer
{
	SGS_CTX;
	int destroying;
	int width, height;
	sgs_VHTable resources;
	sgs_VHTable shaders;
	sgs_VHTable materials;
	sgs_VarObj* currentScene;
	sgs_Bool enableDeferredShading;
}
SS3D_Renderer;


void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX );
void SS3D_Renderer_Destruct( SS3D_Renderer* R );
void SS3D_Renderer_Update( SS3D_Renderer* R, float dt );
void SS3D_Renderer_Resize( SS3D_Renderer* R, int w, int h );


int SS3D_PushRenderer_D3D9( SGS_CTX, void* device );
int SS3D_PushRenderer_GL( SGS_CTX, uint32_t version );

