

/* SS3D Rendering Engine */


#include <sgscript.h>
#include <sgs_util.h>
#include <sgsxgmath.h>



typedef float VEC3[3];
typedef float VEC4[4];
typedef VEC3 MAT3[3];
typedef VEC4 MAT4[4];

#define DEG2RAD( x ) ((x)/180.0f*M_PI)

#define VEC3_Set( V, x, y, z ) V[0] = x; V[1] = y; V[2] = z;
#define VEC3_Add( V, A, B ) V[0]=A[0]+B[0]; V[1]=A[1]+B[1]; V[2]=A[2]+B[2];
#define VEC3_Sub( V, A, B ) V[0]=A[0]-B[0]; V[1]=A[1]-B[1]; V[2]=A[2]-B[2];
#define VEC3_Mul( V, A, B ) V[0]=A[0]*B[0]; V[1]=A[1]*B[1]; V[2]=A[2]*B[2];
#define VEC3_Div( V, A, B ) V[0]=A[0]/B[0]; V[1]=A[1]/B[1]; V[2]=A[2]/B[2];
#define VEC3_Dot( A, B ) (A[0]*B[0]+A[1]*B[1]+A[2]*B[2])
#define VEC3_Length( X ) sqrt( VEC3_Dot( X, X ) );
#define VEC3_Cross( V, A, B ) V[0]=A[1]*B[2]-A[2]*B[1]; V[1]=A[2]*B[0]-A[0]*B[2]; V[2]=A[0]*B[1]-A[1]*B[0];
#define VEC3_Normalized( V, X ) { float len = VEC3_Length( X ); if( len > 0 ){ V[0]=X[0]/len; V[1]=X[1]/len; V[2]=X[2]/len; } }

#define VEC4_Set( V, x, y, z, w ) V[0] = x; V[1] = y; V[2] = z; V[3] = w;
#define VEC4_Copy( V, src ) V[0] = src[0]; V[1] = src[1]; V[2] = src[2]; V[3] = src[3];

void SS3D_Mtx_Identity( MAT4 out );
void SS3D_Mtx_Transpose( MAT4 mtx );
void SS3D_Mtx_Multiply( MAT4 out, MAT4 A, MAT4 B );
void SS3D_Mtx_Transform( VEC4 out, VEC4 v, MAT4 mtx );
void SS3D_Mtx_TransformPos( VEC3 out, VEC3 pos, MAT4 mtx );
void SS3D_Mtx_Dump( MAT4 mtx );
void SS3D_Mtx_LookAt( MAT4 out, VEC3 pos, VEC3 dir, VEC3 up );
void SS3D_Mtx_Perspective( MAT4 out, float angle, float aspect, float aamix, float znear, float zfar );


#define SS3DTEXTURE_2D     1 /* 1 side, width x height */
#define SS3DTEXTURE_CUBE   2 /* 6 sides, width x width */
#define SS3DTEXTURE_VOLUME 3 /* 1 side, width x height x depth */

#define SS3DTEXFLAGS_SRGB    0x01
#define SS3DTEXFLAGS_HASMIPS 0x02
#define SS3DTEXFLAGS_LERP_X  0x04
#define SS3DTEXFLAGS_LERP_Y  0x08
#define SS3DTEXFLAGS_CLAMP_X 0x10
#define SS3DTEXFLAGS_CLAMP_Y 0x20

#define SS3DFORMAT_UNKNOWN 0
#define SS3DFORMAT_RGBA8  1
#define SS3DFORMAT_BGRA8  2
#define SS3DFORMAT_R5G6B5 5
#define SS3DFORMAT_DXT1   11
#define SS3DFORMAT_DXT3   13
#define SS3DFORMAT_DXT5   15
#define SS3DFORMAT_ISBLOCK4FORMAT( x ) ((x)==SS3DFORMAT_DXT1||(x)==SS3DFORMAT_DXT3||(x)==SS3DFORMAT_DXT5)

#define SS3DLIGHT_POINT  1
#define SS3DLIGHT_SPOT   2
#define SS3DLIGHT_DIRECT 3

#define SS3DINDEX_16 0
#define SS3DINDEX_32 1

#define SS3D_NUM_MATERIAL_TEXTURES 6
#define SS3D_MAX_MESH_PARTS 8
#define SS3D_VDECL_MAX_ITEMS 8

#define SS3D_VDECLTYPE_FLOAT1 0
#define SS3D_VDECLTYPE_FLOAT2 1
#define SS3D_VDECLTYPE_FLOAT3 2
#define SS3D_VDECLTYPE_FLOAT4 3
#define SS3D_VDECLTYPE_BCOL4 4

/* usage type | expected data type */
#define SS3D_VDECLUSAGE_POSITION 0 /* float3 */
#define SS3D_VDECLUSAGE_COLOR    1 /* float3/float4/ubyte4 */
#define SS3D_VDECLUSAGE_NORMAL   2 /* float3 */
#define SS3D_VDECLUSAGE_TANGENT  3 /* float4 */
#define SS3D_VDECLUSAGE_TEXTURE0 4 /* any .. */
#define SS3D_VDECLUSAGE_TEXTURE1 5
#define SS3D_VDECLUSAGE_TEXTURE2 6
#define SS3D_VDECLUSAGE_TEXTURE3 7

/* mesh data flags */
#define SS3D_MDF_INDEX_32      0x01
#define SS3D_MDF_TRIANGLESTRIP 0x02
#define SS3D_MDF_DYNAMIC       0x04


sgs_ObjInterface SS3D_Camera_iface[1];
sgs_ObjInterface SS3D_Light_iface[1];
sgs_ObjInterface SS3D_Scene_iface[1];

typedef struct _SS3D_Light SS3D_Light;
typedef struct _SS3D_Material SS3D_Material;
typedef struct _SS3D_MeshPart SS3D_MeshPart;
typedef struct _SS3D_Mesh SS3D_Mesh;
typedef struct _SS3D_MeshInstance SS3D_MeshInstance;
typedef struct _SS3D_CullScene SS3D_CullScene;
typedef struct _SS3D_Camera SS3D_Camera;
typedef struct _SS3D_Viewport SS3D_Viewport;
typedef struct _SS3D_Scene SS3D_Scene;
typedef struct _SS3D_Renderer SS3D_Renderer;


typedef struct _SS3D_TextureInfo
{
	int type;
	int width;
	int height;
	int depth;
	int format; /* SS3DFORMAT */
	int flags; /* SS3DTEXFLAGS */
	int mipcount;
}
SS3D_TextureInfo;

size_t SS3D_TextureInfo_GetTextureSideSize( SS3D_TextureInfo* TI );
void SS3D_TextureInfo_GetCopyDims( SS3D_TextureInfo* TI, size_t* outcopyrowsize, size_t* outcopyrowcount );
SGSBOOL SS3D_TextureInfo_GetMipInfo( SS3D_TextureInfo* TI, int mip, SS3D_TextureInfo* outinfo );


/* sorting order of pixel/block data:
	- mip level
	- side
	- depth
	- height
	- width
*/
typedef struct _SS3D_TextureData
{
	SS3D_TextureInfo info;
	void* data;
}
SS3D_TextureData;

SGSRESULT SS3D_TextureData_LoadFromFile( SS3D_TextureData* TD, const char* file );
void SS3D_TextureData_Free( SS3D_TextureData* TD );
size_t SS3D_TextureData_GetMipDataOffset( SS3D_TextureData* TD, int side, int mip );
size_t SS3D_TextureData_GetMipDataSize( SS3D_TextureData* TD, int mip );


typedef struct _SS3D_Texture
{
	SS3D_Renderer* renderer;
	SS3D_TextureInfo info;
}
SS3D_Texture;

struct _SS3D_Light
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
};

struct _SS3D_Material
{
	SS3D_Renderer* renderer;
	
	int transparent;
	sgs_VarObj* shader;
	sgs_VarObj* textures[ SS3D_NUM_MATERIAL_TEXTURES ];
};

extern sgs_ObjInterface SS3D_Material_iface[1];

int SS3D_Material_Create( SS3D_Renderer* R );

typedef struct _SS3D_VDeclInfo
{
	uint8_t offsets[ SS3D_VDECL_MAX_ITEMS ];
	uint8_t types  [ SS3D_VDECL_MAX_ITEMS ];
	uint8_t usages [ SS3D_VDECL_MAX_ITEMS ];
	uint8_t count;
	uint8_t size;
}
SS3D_VDeclInfo;

const char* SS3D_VDeclInfo_Parse( SS3D_VDeclInfo* info, const char* text );

struct _SS3D_MeshPart
{
	sgs_VarObj* material;
	uint32_t vertexOffset;
	uint32_t vertexCount;
	uint32_t indexOffset;
	uint32_t indexCount;
};

struct _SS3D_Mesh
{
	SS3D_Renderer* renderer;
	
	/* rendering info */
	int dataFlags;
	sgs_VarObj* vertexDecl;
	uint32_t vertexCount;
	uint32_t vertexDataSize;
	uint32_t indexCount;
	uint32_t indexDataSize;
	SS3D_MeshPart parts[ SS3D_MAX_MESH_PARTS ];
	int numParts;
	
	/* collision detection */
	VEC3 boundsMin;
	VEC3 boundsMax;
	VEC3 center;
	float radius;
};

void SS3D_Mesh_Init( SS3D_Mesh* mesh );

struct _SS3D_MeshInstance
{
	SS3D_Scene* scene;
	
	sgs_VarObj* mesh;
	MAT4 matrix;
	VEC4 color;
	int enabled;
};

typedef void (*fpSS3D_CullScene_SetCamera) ( void* /* data */, SS3D_Camera* );
typedef int (*fpSS3D_CullScene_AABB)       ( void* /* data */, VEC3 /* from */, VEC3 /* to */ );
typedef int (*fpSS3D_CullScene_OBB)        ( void* /* data */, VEC3 /* center */, VEC3 /* extents */, MAT3 /* rotation */ );
typedef int (*fpSS3D_CullScene_Sphere)     ( void* /* data */, VEC3 /* center */, float /* radius */ );
typedef int (*fpSS3D_CullScene_Spotlight)  ( void* /* data */, VEC3 /* origin */, float /* radius */, VEC3 /* direction */, float /* halfAngle */ );

struct _SS3D_CullScene
{
	fpSS3D_CullScene_SetCamera setCameraFunc;
	fpSS3D_CullScene_AABB      AABBFunc;
	fpSS3D_CullScene_OBB       OBBFunc;
	fpSS3D_CullScene_Sphere    sphereFunc;
	fpSS3D_CullScene_Spotlight spotlightFunc;
	void* dataStruct;
};

struct _SS3D_Camera
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
	MAT4 mInvView;
};

struct _SS3D_Viewport
{
	int x1, y1, x2, y2;
};

struct _SS3D_Scene
{
	SS3D_Renderer* renderer;
	int destroying;
	
	sgs_VHTable meshInstances;
	sgs_VHTable lights;
	
	sgs_VarObj* cullScene;
	sgs_VarObj* camera;
	sgs_VarObj* viewport;
};

struct _SS3D_Renderer
{
	SGS_CTX;
	int destroying;
	sgs_VHTable resources;
	sgs_VHTable shaders;
	sgs_VHTable textures;
	sgs_VHTable materials;
	sgs_VarObj* currentScene;
	sgs_VarObj* store;
	
	/* to be initialized by derived class */
	int width, height;
	const char* API;
	sgs_ObjInterface* ifMesh;
	sgs_ObjInterface* ifTexture;
	sgs_ObjInterface* ifShader;
};


void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX );
void SS3D_Renderer_Destruct( SS3D_Renderer* R );
void SS3D_Renderer_Update( SS3D_Renderer* R, float dt );
void SS3D_Renderer_Resize( SS3D_Renderer* R, int w, int h );
void SS3D_Renderer_PokeResource( SS3D_Renderer* R, sgs_VarObj* obj, int add );
void SS3D_Renderer_PushScene( SS3D_Renderer* R );

int SS3D_PushRenderer_D3D9( SGS_CTX, void* device );
int SS3D_PushRenderer_GL( SGS_CTX, uint32_t version );

