

/* SS3D Rendering Engine */


#include <sgscript.h>
#include <sgs_util.h>
#include <sgsxgmath.h>


SGSRESULT sgs_ParseObjectPtr( SGS_CTX, sgs_StkIdx item, sgs_ObjCallback* iface, sgs_VarObj** out, int strict );


typedef float VEC3[3];
typedef float VEC4[4];
typedef VEC3 MAT3[3];
typedef VEC4 MAT4[4];

#define DEG2RAD( x ) ((x)/180.0f*M_PI)

#define VEC3_Set( V, x, y, z ) V[0] = x; V[1] = y; V[2] = z;
#define VEC3_Add( V, A, B ) v[0]=A[0]+B[0]; v[1]=A[1]+B[1]; v[2]=A[2]+B[2];
#define VEC3_Sub( V, A, B ) v[0]=A[0]-B[0]; v[1]=A[1]-B[1]; v[2]=A[2]-B[2];
#define VEC3_Mul( V, A, B ) v[0]=A[0]*B[0]; v[1]=A[1]*B[1]; v[2]=A[2]*B[2];
#define VEC3_Div( V, A, B ) v[0]=A[0]/B[0]; v[1]=A[1]/B[1]; v[2]=A[2]/B[2];
#define VEC3_Dot( A, B ) (A[0]*B[0]+A[1]*B[1]+A[2]*B[2])
#define VEC3_Length( X ) sqrt( VEC3_Dot( X, X ) );
#define VEC3_Cross( V, A, B ) V[0]=A[1]*B[2]-A[2]*B[1]; V[1]=A[2]*B[0]-A[0]*B[2]; V[2]=A[0]*B[1]-A[1]*B[0];
#define VEC3_Normalized( V, X ) { float len = VEC3_Length( X ); if( len > 0 ){ V[0]=X[0]/len; V[1]=X[1]/len; V[2]=X[2]/len; } }

void SS3D_Mtx_Transpose( MAT4 mtx );
void SS3D_Mtx_Multiply( MAT4 out, MAT4 A, MAT4 B );
void SS3D_Mtx_Transform( VEC4 out, VEC4 v, MAT4 mtx );
void SS3D_Mtx_TransformPos( VEC3 out, VEC3 pos, MAT4 mtx );
void SS3D_Mtx_Dump( MAT4 mtx );
void SS3D_Mtx_LookAt( MAT4 out, VEC3 pos, VEC3 dir, VEC3 up );
void SS3D_Mtx_Perspective( MAT4 out, float angle, float aspect, float aamix, float znear, float zfar );


#define SS3DLIGHT_POINT  1
#define SS3DLIGHT_SPOT   2
#define SS3DLIGHT_DIRECT 3

#define SS3DINDEX_16 0
#define SS3DINDEX_32 1


sgs_ObjCallback SS3D_Camera_iface[9];
sgs_ObjCallback SS3D_Light_iface[13];
sgs_ObjCallback SS3D_Scene_iface[9];

typedef struct _SS3D_Scene SS3D_Scene;
typedef struct _SS3D_Renderer SS3D_Renderer;


typedef struct _SS3D_Camera
{
	VEC3 position;
	VEC3 direction;
	VEC3 up;
	float angle;
	float aspect;
	float aamix;
	float znear;
	float zfar;
	
	MAT4 mView;
	MAT4 mProj;
}
SS3D_Camera;

typedef struct _SS3D_Light
{
	SS3D_Scene* scene;
	
	int type;
	int isEnabled;
	VEC3 position;
	VEC3 direction;
	VEC3 color;
	float range;
	float power;
	float minangle;
	float maxangle;
	sgs_VarObj* cookieTexture;
	MAT4 projMatrix;
	int hasShadows;
}
SS3D_Light;

typedef struct _SS3D_MeshInstance
{
	SS3D_Scene* scene;
	
	sgs_VarObj* mesh;
	MAT4 matrix;
	VEC3 color;
}
SS3D_MeshInstance;

typedef void (*fpSS3D_CullScene_SetCamera) ( void* /* data */, SS3D_Camera* );
typedef int (*fpSS3D_CullScene_AABB)       ( void* /* data */, VEC3 /* from */, VEC3 /* to */ );
typedef int (*fpSS3D_CullScene_OBB)        ( void* /* data */, VEC3 /* center */, VEC3 /* extents */, MAT3 /* rotation */ );
typedef int (*fpSS3D_CullScene_Sphere)     ( void* /* data */, VEC3 /* center */, float /* radius */ );
typedef int (*fpSS3D_CullScene_Spotlight)  ( void* /* data */, VEC3 /* origin */, float /* radius */, VEC3 /* direction */, float /* halfAngle */ );

typedef struct _SS3D_CullScene
{
	fpSS3D_CullScene_SetCamera setCameraFunc;
	fpSS3D_CullScene_AABB      AABBFunc;
	fpSS3D_CullScene_OBB       OBBFunc;
	fpSS3D_CullScene_Sphere    sphereFunc;
	fpSS3D_CullScene_Spotlight spotlightFunc;
	void* dataStruct;
}
SS3D_CullScene;

struct _SS3D_Scene
{
	SS3D_Renderer* renderer;
	int destroying;
	
	sgs_VHTable meshInstances;
	sgs_VHTable lights;
	
	sgs_VarObj* camera;
	sgs_VarObj* cullScene;
};

struct _SS3D_Renderer
{
	SGS_CTX;
	int destroying;
	sgs_VHTable resources;
	sgs_VHTable shaders;
	sgs_VHTable materials;
	sgs_VarObj* currentScene;
	sgs_Bool enableDeferredShading;
	
	/* to be initialized by derived class */
	int width, height;
	const char* API;
	sgs_ObjCallback* ifMesh;
	sgs_ObjCallback* ifTexture;
};


void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX );
void SS3D_Renderer_Destruct( SS3D_Renderer* R );
void SS3D_Renderer_Update( SS3D_Renderer* R, float dt );
void SS3D_Renderer_Resize( SS3D_Renderer* R, int w, int h );
void SS3D_Renderer_PokeResource( SS3D_Renderer* R, sgs_VarObj* obj, int add );
void SS3D_Renderer_PushScene( SS3D_Renderer* R );

int SS3D_PushRenderer_D3D9( SGS_CTX, void* device );
int SS3D_PushRenderer_GL( SGS_CTX, uint32_t version );

