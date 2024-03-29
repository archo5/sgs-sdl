

/* SS3D Rendering Engine */


#include <sgscript.h>
#include <sgs_util.h>
#include <sgsxgmath.h>



typedef float VEC3[3];
typedef float VEC4[4];
typedef VEC3 MAT3[3];
typedef VEC4 MAT4[4];
typedef VEC4 PLANE;

typedef uint32_t bitfield_t;

#define DEG2RAD( x ) ((x)/180.0f*M_PI)
#define LERP( a, b, t ) ((a)*(1-(t))+(b)*(t))
#define MIN( a, b ) ((a)<(b)?(a):(b))
#define MAX( a, b ) ((a)>(b)?(a):(b))

#define VEC3_Set( V, x, y, z ) V[0] = x; V[1] = y; V[2] = z;
#define VEC3_Copy( V, X ) V[0] = X[0]; V[1] = X[1]; V[2] = X[2];
#define VEC3_Min( V, A, B ) V[0]=MIN(A[0],B[0]); V[1]=MIN(A[1],B[1]); V[2]=MIN(A[2],B[2]);
#define VEC3_Max( V, A, B ) V[0]=MAX(A[0],B[0]); V[1]=MAX(A[1],B[1]); V[2]=MAX(A[2],B[2]);
#define VEC3_Add( V, A, B ) V[0]=A[0]+B[0]; V[1]=A[1]+B[1]; V[2]=A[2]+B[2];
#define VEC3_Sub( V, A, B ) V[0]=A[0]-B[0]; V[1]=A[1]-B[1]; V[2]=A[2]-B[2];
#define VEC3_Mul( V, A, B ) V[0]=A[0]*B[0]; V[1]=A[1]*B[1]; V[2]=A[2]*B[2];
#define VEC3_Div( V, A, B ) V[0]=A[0]/B[0]; V[1]=A[1]/B[1]; V[2]=A[2]/B[2];
#define VEC3_Dot( A, B ) (A[0]*B[0]+A[1]*B[1]+A[2]*B[2])
#define VEC3_Scale( V, A, S ) V[0]=A[0]*S; V[1]=A[1]*S; V[2]=A[2]*S;
#define VEC3_Length( X ) sqrt( VEC3_Dot( X, X ) );
#define VEC3_Cross( V, A, B ) V[0]=A[1]*B[2]-A[2]*B[1]; V[1]=A[2]*B[0]-A[0]*B[2]; V[2]=A[0]*B[1]-A[1]*B[0];
#define VEC3_Normalized( V, X ) { float len = VEC3_Length( X ); if( len > 0 ){ V[0]=X[0]/len; V[1]=X[1]/len; V[2]=X[2]/len; }else{ VEC3_Set( V, 0, 0, 0 ); } }
#define VEC3_Dump( V ) printf("(%f;%f;%f)\n",V[0],V[1],V[2])

#define VEC4_Set( V, x, y, z, w ) V[0] = x; V[1] = y; V[2] = z; V[3] = w;
#define VEC4_Copy( V, src ) V[0] = src[0]; V[1] = src[1]; V[2] = src[2]; V[3] = src[3];
#define VEC4_Dump( V ) printf("(%f;%f;%f;%f)\n",V[0],V[1],V[2],V[3])

void SS3D_Mtx_Identity( MAT4 out );
void SS3D_Mtx_Transpose( MAT4 mtx );
void SS3D_Mtx_Multiply( MAT4 out, MAT4 A, MAT4 B );
int SS3D_Mtx_Invert( MAT4 out, MAT4 M );
void SS3D_Mtx_Transform( VEC4 out, VEC4 v, MAT4 mtx );
void SS3D_Mtx_TransformPos( VEC3 out, VEC3 pos, MAT4 mtx );
void SS3D_Mtx_TransformNormal( VEC3 out, VEC3 pos, MAT4 mtx );
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

#define SS3DTEXTURE_USAGE_MISC   0
#define SS3DTEXTURE_USAGE_NORMAL 1
#define SS3DTEXTURE_USAGE_ALBEDO 2
#define SS3DTEXTURE_USAGE_FULLSCREEN 3

#define SS3DFORMAT_UNKNOWN 0
#define SS3DFORMAT_RGBA8  1
#define SS3DFORMAT_BGRA8  2
#define SS3DFORMAT_BGRX8  3
#define SS3DFORMAT_R5G6B5 5
#define SS3DFORMAT_DXT1   11
#define SS3DFORMAT_DXT3   13
#define SS3DFORMAT_DXT5   15
#define SS3DFORMAT_ISBLOCK4FORMAT( x ) ((x)==SS3DFORMAT_DXT1||(x)==SS3DFORMAT_DXT3||(x)==SS3DFORMAT_DXT5)

#define SS3DRT_FORMAT_BACKBUFFER 0
#define SS3DRT_FORMAT_DEPTH      1

#define SS3DLIGHT_POINT  1
#define SS3DLIGHT_SPOT   2

#define SS3DINDEX_16 0
#define SS3DINDEX_32 1

#define SS3D_NUM_MATERIAL_TEXTURES 8
#define SS3D_MAX_MESH_PARTS 16
#define SS3D_MAX_MESH_BONES 32
#define SS3D_VDECL_MAX_ITEMS 10

#define SS3D_VDECLTYPE_FLOAT1 0
#define SS3D_VDECLTYPE_FLOAT2 1
#define SS3D_VDECLTYPE_FLOAT3 2
#define SS3D_VDECLTYPE_FLOAT4 3
#define SS3D_VDECLTYPE_BCOL4 4

/* usage type | expected data type */
#define SS3D_VDECLUSAGE_POSITION 0 /* float3 */
#define SS3D_VDECLUSAGE_COLOR    1 /* float3/float4/bcol4 */
#define SS3D_VDECLUSAGE_NORMAL   2 /* float3 */
#define SS3D_VDECLUSAGE_TANGENT  3 /* float4 */
#define SS3D_VDECLUSAGE_BLENDWT  4 /* preferably bcol4 */
#define SS3D_VDECLUSAGE_BLENDIDX 5 /* preferably bcol4 (will be passed as ubyte4, not float4) */
#define SS3D_VDECLUSAGE_TEXTURE0 6 /* any .. */
#define SS3D_VDECLUSAGE_TEXTURE1 7
#define SS3D_VDECLUSAGE_TEXTURE2 8
#define SS3D_VDECLUSAGE_TEXTURE3 9

/* mesh data flags */
#define SS3D_MDF_INDEX_32      0x01
#define SS3D_MDF_TRIANGLESTRIP 0x02
#define SS3D_MDF_DYNAMIC       0x04 /* dynamic buffer updating */
#define SS3D_MDF_TRANSPARENT   0x10 /* mesh is required to be rendered transparent */
#define SS3D_MDF_UNLIT         0x20 /* mesh doesn't require the lighting passes to be applied */
#define SS3D_MDF_NOCULL        0x40 /* mesh has culling disabled */
#define SS3D_MDF_SKINNED       0x80 /* mesh has bone data (name, offset, parent id) */

#define SS3D_MDF__PUBFLAGMASK (0x01|0x02|0x10|0x20|0x40|0x80)
#define SS3D_MDF__PUBFLAGBASE  0

/* render pass constants */
#define SS3D_RPT_OBJECT     1
#define SS3D_RPT_SCREEN     2
#define SS3D_RPT_SHADOWS    3

#define SS3D_RPF_OBJ_STATIC      0x01
#define SS3D_RPF_OBJ_DYNAMIC     0x02
#define SS3D_RPF_OBJ_ALL        (SS3D_RPF_OBJ_STATIC|SS3D_RPF_OBJ_DYNAMIC)
#define SS3D_RPF_MTL_SOLID       0x04
#define SS3D_RPF_MTL_TRANSPARENT 0x08
#define SS3D_RPF_MTL_ALL        (SS3D_RPF_MTL_SOLID|SS3D_RPF_MTL_TRANSPARENT)
#define SS3D_RPF_CALC_DIRAMB     0x10
#define SS3D_RPF_LIGHTOVERLAY    0x20
#define SS3D_RPF_ENABLED         0x80

#define SS3D_SHADER_NAME_LENGTH 64
#define SS3D_MAX_NUM_PASSES     16
#define SS3D_MAX_MI_TEXTURES    4
#define SS3D_MAX_MI_CONSTANTS   16

#define SS3D_CF_ENABLE_CAM_MESH 0x01
#define SS3D_CF_ENABLE_CAM_PLT  0x02
#define SS3D_CF_ENABLE_CAM_SLT  0x04
#define SS3D_CF_ENABLE_MESH_PLT 0x08
#define SS3D_CF_ENABLE_MESH_SLT 0x10
#define SS3D_CF_ENABLE_SLT_MESH 0x20
#define SS3D_CF_ENABLE_ALL      0xff
#define SS3D_CF_SUBST_SLT       0x100


sgs_ObjInterface SS3D_Camera_iface[1];
sgs_ObjInterface SS3D_Light_iface[1];
sgs_ObjInterface SS3D_Viewport_iface[1];
sgs_ObjInterface SS3D_MeshInstance_iface[1];
sgs_ObjInterface SS3D_Scene_iface[1];

typedef struct _SS3D_Light SS3D_Light;
typedef struct _SS3D_Material SS3D_Material;
typedef struct _SS3D_MeshPart SS3D_MeshPart;
typedef struct _SS3D_MeshBone SS3D_MeshBone;
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
	int usage;
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
	- side
	- mip level
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

SGSRESULT SS3D_TextureData_LoadFromFile( SGS_CTX, SS3D_TextureData* TD, sgs_Variable* vFile );
void SS3D_TextureData_Free( SS3D_TextureData* TD );
size_t SS3D_TextureData_GetMipDataOffset( SS3D_TextureData* TD, int side, int mip );
size_t SS3D_TextureData_GetMipDataSize( SS3D_TextureData* TD, int mip );


typedef struct _SS3D_MeshFilePartData
{
	uint32_t vertexOffset;
	uint32_t vertexCount;
	uint32_t indexOffset;
	uint32_t indexCount;
	
	uint8_t materialTextureCount; /* 0 - 8 */
	uint8_t materialStringSizes[ SS3D_NUM_MATERIAL_TEXTURES + 1 ];
	char* materialStrings[ SS3D_NUM_MATERIAL_TEXTURES + 1 ];
	/* size w/o padding = 28+[36/72] = 64/100 */
}
SS3D_MeshFilePartData;

typedef struct _SS3D_MeshFileBoneData
{
	char* boneName;
	uint8_t boneNameSize;
	uint8_t parent_id;
	MAT4 boneOffset;
	/* size w/o padding = 66+[4/8] = 70/74 */
}
SS3D_MeshFileBoneData;

typedef struct _SS3D_MeshFileData
{
	uint32_t dataFlags;
	uint32_t vertexDataSize;
	uint32_t indexDataSize;
	char* vertexData;
	char* indexData;
	char* formatData;
	
	VEC3 boundsMin;
	VEC3 boundsMax;
	
	uint8_t numParts;
	uint8_t numBones;
	uint8_t formatSize;
	/* size w/o padding = 39+[12/24] = 51/63 */
	
	SS3D_MeshFilePartData parts[ SS3D_MAX_MESH_PARTS ];
	/* size w/o padding = 51/63 + 64/100 x16 = 1075/1663 */
	SS3D_MeshFileBoneData bones[ SS3D_MAX_MESH_BONES ];
	/* size w/o padding = 1075/1663 + 70/74 x32 = 3315/4031 */
}
SS3D_MeshFileData;

const char* SS3D_MeshData_Parse( char* buf, size_t size, SS3D_MeshFileData* out );


typedef struct _SS3D_Texture
{
	SS3D_Renderer* renderer;
	SS3D_TextureInfo info;
}
SS3D_Texture;

typedef struct _SS3D_MeshInstLight
{
	SS3D_MeshInstance* MI;
	SS3D_Light* L;
}
SS3D_MeshInstLight;

struct _SS3D_Light
{
	SS3D_Scene* scene;
	
	int type;
	int enabled;
	VEC3 position;
	VEC3 direction;
	VEC3 updir;
	VEC3 color;
	float range;
	float power;
	float angle;
	float aspect;
	sgs_VarObj* cookieTexture;
	sgs_VarObj* shadowTexture;
	MAT4 viewMatrix;
	MAT4 projMatrix;
	MAT4 viewProjMatrix;
	int hasShadows;
	
	/* frame cache */
	SS3D_MeshInstLight* mibuf_begin;
	SS3D_MeshInstLight* mibuf_end;
};


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
int SS3D_GetAABBFromVertexData( SS3D_VDeclInfo* info, const char* vdata, size_t vdsize, VEC3 outMin, VEC3 outMax );

struct _SS3D_MeshPart
{
	uint32_t vertexOffset;
	uint32_t vertexCount;
	uint32_t indexOffset;
	uint32_t indexCount;
	
	sgs_VarObj* shaders[ SS3D_MAX_NUM_PASSES ];
	sgs_VarObj* shaders_skin[ SS3D_MAX_NUM_PASSES ];
	sgs_VarObj* textures[ SS3D_NUM_MATERIAL_TEXTURES ];
	char shader_name[ SS3D_SHADER_NAME_LENGTH ];
};

struct _SS3D_MeshBone
{
	sgs_iStr* name;
	MAT4 boneOffset;
	MAT4 invSkinOffset;
	int parent_id;
};

struct _SS3D_Mesh
{
	SS3D_Renderer* renderer;
	
	/* rendering info */
	uint32_t dataFlags;
	sgs_VarObj* vertexDecl;
	uint32_t vertexCount;
	uint32_t vertexDataSize;
	uint32_t indexCount;
	uint32_t indexDataSize;
	SS3D_MeshPart parts[ SS3D_MAX_MESH_PARTS ];
	SS3D_MeshBone bones[ SS3D_MAX_MESH_BONES ];
	int numParts;
	int numBones;
	
	/* collision detection */
	VEC3 boundsMin;
	VEC3 boundsMax;
};

void SS3D_Mesh_Init( SS3D_Mesh* mesh );

struct _SS3D_MeshInstance
{
	SS3D_Scene* scene;
	
	sgs_VarObj* mesh;
	MAT4 matrix;
	VEC4 color;
	bitfield_t enabled : 1;
	bitfield_t cpuskin : 1; /* TODO */
	
	sgs_VarObj* textures[ SS3D_MAX_MI_TEXTURES ];
	VEC4 constants[ SS3D_MAX_MI_CONSTANTS ];
	
	MAT4* skin_matrices;
	int skin_matrix_count;
	
	/* frame cache */
	SS3D_MeshInstLight* lightbuf_begin;
	SS3D_MeshInstLight* lightbuf_end;
};


typedef struct _SS3D_CullSceneFrustum
{
	VEC3 position;
	VEC3 direction;
	VEC3 up;
	float hangle;
	float vangle;
	float znear;
	float zfar;
}
SS3D_CullSceneFrustum;
typedef struct _SS3D_CullSceneCamera
{
	SS3D_CullSceneFrustum frustum;
	MAT4 viewProjMatrix;
	MAT4 invViewProjMatrix;
}
SS3D_CullSceneCamera;
typedef struct _SS3D_CullScenePointLight
{
	VEC3 position;
	float radius;
}
SS3D_CullScenePointLight;
typedef struct _SS3D_CullSceneMesh
{
	MAT4 transform;
	VEC3 min, max;
}
SS3D_CullSceneMesh;

typedef void (*fpSS3D_CullScene_Camera_Prepare) ( void* /* data */, SS3D_CullSceneCamera* /* camera */ );
typedef int (*fpSS3D_CullScene_Camera_MeshList) ( void* /* data */, uint32_t /* count */, SS3D_CullSceneCamera* /* camera */, SS3D_CullSceneMesh* /* meshes */, uint32_t* /* outbitfield */ );
typedef int (*fpSS3D_CullScene_Camera_PointLightList) ( void* /* data */, uint32_t /* count */, SS3D_CullSceneCamera* /* camera */, SS3D_CullScenePointLight* /* lights */, uint32_t* /* outbitfield */ );
typedef int (*fpSS3D_CullScene_Camera_SpotLightList) ( void* /* data */, uint32_t /* count */, SS3D_CullSceneCamera* /* camera */, SS3D_CullSceneFrustum* /* frusta */, MAT4* /* inv_matrices */, uint32_t* /* outbitfield */ );
typedef int (*fpSS3D_CullScene_Mesh_PointLightList) ( void* /* data */, uint32_t /* count */, SS3D_CullSceneMesh* /* mesh */, SS3D_CullScenePointLight* /* lights */, uint32_t* /* outbitfield */ );
typedef int (*fpSS3D_CullScene_Mesh_SpotLightList) ( void* /* data */, uint32_t /* count */, SS3D_CullSceneMesh* /* mesh */, SS3D_CullSceneFrustum* /* frusta */, MAT4* /* inv_matrices */, uint32_t* /* outbitfield */ );

struct _SS3D_CullScene
{
	fpSS3D_CullScene_Camera_Prepare        camera_prepare;
	fpSS3D_CullScene_Camera_MeshList       camera_meshlist;
	fpSS3D_CullScene_Camera_PointLightList camera_pointlightlist;
	fpSS3D_CullScene_Camera_SpotLightList  camera_spotlightlist;
	fpSS3D_CullScene_Mesh_PointLightList   mesh_pointlightlist;
	fpSS3D_CullScene_Mesh_SpotLightList    mesh_spotlightlist;
	fpSS3D_CullScene_Camera_Prepare        spotlight_prepare;
	fpSS3D_CullScene_Camera_MeshList       spotlight_meshlist;
	void* data;
	uint32_t flags;
	sgs_Variable store;
};

SS3D_CullScene* SS3D_PushCullScene( SGS_CTX );

void SS3D_Scene_Cull_Camera_Prepare( SGS_CTX, SS3D_Scene* S );
uint32_t SS3D_Scene_Cull_Camera_MeshList( SGS_CTX, sgs_MemBuf* MB, SS3D_Scene* S );
uint32_t SS3D_Scene_Cull_Camera_PointLightList( SGS_CTX, sgs_MemBuf* MB, SS3D_Scene* S );
uint32_t SS3D_Scene_Cull_Camera_SpotLightList( SGS_CTX, sgs_MemBuf* MB, SS3D_Scene* S );
void SS3D_Scene_Cull_Spotlight_Prepare( SGS_CTX, SS3D_Scene* S, SS3D_Light* L );
uint32_t SS3D_Scene_Cull_Spotlight_MeshList( SGS_CTX, sgs_MemBuf* MB, SS3D_Scene* S, SS3D_Light* L );


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
	
	sgs_VarObj* cullScenes;
	sgs_VarObj* camera;
	
	VEC3 fogColor;
	float fogHeightFactor;
	float fogDensity;
	float fogHeightDensity;
	float fogStartHeight;
	float fogMinDist;
	
	VEC3 ambientLightColor;
	VEC3 dirLightColor;
	VEC3 dirLightDir;
	
	sgs_VarObj* skyTexture;
};

typedef struct _SS3D_RenderPass
{
	uint8_t type;
	uint8_t flags;
	int16_t maxruns;
	uint16_t pointlight_count;
	uint8_t spotlight_count;
	uint8_t num_inst_textures;
	char shname[ SS3D_SHADER_NAME_LENGTH ];
}
SS3D_RenderPass;

struct _SS3D_Renderer
{
	SGS_CTX;
	int destroying;
	sgs_VHTable resources;
	sgs_VHTable shaders;
	sgs_VHTable textures;
	sgs_VHTable materials;
	sgs_VarObj* _myobj;
	sgs_VarObj* currentScene;
	sgs_VarObj* store;
	sgs_VarObj* currentRT;
	sgs_VarObj* viewport;
	
	sgs_Variable debugDraw;
	VEC4 debugDrawColor;
	
	bitfield_t disablePostProcessing : 1;
	bitfield_t dbg_rt : 1;
	
	bitfield_t inDebugDraw : 1;
	bitfield_t debugDrawClipWorld : 1;
	
	/* common rendering stats */
	uint32_t stat_numVisMeshes;
	uint32_t stat_numVisPLights;
	uint32_t stat_numVisSLights;
	uint32_t stat_numDrawCalls;
	uint32_t stat_numSDrawCalls;
	uint32_t stat_numMDrawCalls;
	uint32_t stat_numPDrawCalls;
	
	/* to be initialized by derived class */
	int width, height;
	const char* API;
	sgs_ObjInterface* ifMesh;
	sgs_ObjInterface* ifTexture;
	sgs_ObjInterface* ifShader;
	sgs_ObjInterface* ifRT;
	
	SS3D_RenderPass passes[ SS3D_MAX_NUM_PASSES ];
	int numPasses;
};


void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX );
void SS3D_Renderer_Destruct( SS3D_Renderer* R );
void SS3D_Renderer_Update( SS3D_Renderer* R, float dt );
void SS3D_Renderer_Resize( SS3D_Renderer* R, int w, int h );
void SS3D_Renderer_PokeResource( SS3D_Renderer* R, sgs_VarObj* obj, int add );
void SS3D_Renderer_PushScene( SS3D_Renderer* R );

int SS3D_PushRenderer_D3D9( SGS_CTX, void* device );
int SS3D_PushRenderer_GL( SGS_CTX );

