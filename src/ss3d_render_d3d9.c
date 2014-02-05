
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#include "../d3dx/d3dx9.h"

#include "ss3d_engine.h"


#define D3DCALL( x, m ) (x)->lpVtbl->m( (x) )
#define D3DCALL_( x, m, ... ) (x)->lpVtbl->m( (x), __VA_ARGS__ )
#define SAFE_RELEASE( x ) if( x ){ D3DCALL( x, Release ); x = NULL; }


typedef struct _SS3D_Shader_D3D9
{
	IDirect3DPixelShader9* PS;
	IDirect3DVertexShader9* VS;
	ID3DXConstantTable* PSCT;
	ID3DXConstantTable* VSCT;
}
SS3D_Shader_D3D9;

typedef struct _SS3D_Texture_D3D9
{
	SS3D_Texture inh;
	
	union
	{
		IDirect3DBaseTexture9* base;
		IDirect3DTexture9* tex2d;
		IDirect3DCubeTexture9* cube;
		IDirect3DVolumeTexture9* vol;
	}
	ptr;
}
SS3D_Texture_D3D9;

typedef struct _DeferredRenderingData
{
	IDirect3DTexture9* RTT1; /* dR, dG, dB, depth, RGBA16F */
	IDirect3DTexture9* RTT2; /* vnX, vnY, vnZ, spec, RGBA8 */
	IDirect3DSurface9* RTS1; /* surface of RTT1 */
	IDirect3DSurface9* RTS2; /* surface of RTT2 */
	IDirect3DSurface9* RTSD; /* depth/stencil surface, D24S8 */
	int width, height;
}
DeferredRenderingData;

typedef struct _SS3D_RD3D9
{
	SS3D_Renderer inh;
	
	IDirect3DDevice9* device;
	IDirect3DSurface9* bb_color;
	IDirect3DSurface9* bb_depth;
	DeferredRenderingData drd;
}
SS3D_RD3D9;


//
//  D E F E R R E D   R E N D E R I N G
//

static void drd_init( SS3D_RD3D9* R, DeferredRenderingData* D, int w, int h )
{
	HRESULT hr;
	memset( D, 0, sizeof(*D) );
	
	D->width = w;
	D->height = h;
	
	hr = D3DCALL_( R->device, CreateTexture, w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &D->RTT1, NULL );
	sgs_BreakIf( FAILED( hr ) || !D->RTT1 || !"failed to create rgba16f render target texture" );
	
	hr = D3DCALL_( R->device, CreateTexture, w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &D->RTT2, NULL );
	sgs_BreakIf( FAILED( hr ) || !D->RTT2 || !"failed to create bgra8 render target texture" );
	
	hr = D3DCALL_( R->device, CreateDepthStencilSurface, w, h, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &D->RTSD, NULL );
	sgs_BreakIf( FAILED( hr ) || !D->RTSD || !"failed to create d24s8 depth+stencil surface" );
	
	D3DCALL_( D->RTT1, GetSurfaceLevel, 0, &D->RTS1 );
	D3DCALL_( D->RTT2, GetSurfaceLevel, 0, &D->RTS2 );
}

static void drd_free( SS3D_RD3D9* R, DeferredRenderingData* D )
{
	SAFE_RELEASE( D->RTS1 );
	SAFE_RELEASE( D->RTS2 );
	SAFE_RELEASE( D->RTSD );
	SAFE_RELEASE( D->RTT1 );
	SAFE_RELEASE( D->RTT2 );
	D->width = 0;
	D->height = 0;
}


//
//  S H A D E R S
//

static void use_shader( SS3D_RD3D9* R, SS3D_Shader_D3D9* S )
{
	D3DCALL_( R->device, SetPixelShader, S ? S->PS : NULL );
	D3DCALL_( R->device, SetVertexShader, S ? S->VS : NULL );
}

static void vshc_set_mat4( SS3D_RD3D9* R, int pos, MAT4 mtx ){ D3DCALL_( R->device, SetVertexShaderConstantF, pos, mtx[0], 4 ); }

static void pshc_set_float( SS3D_RD3D9* R, int pos, float f ){ VEC4 v = { f, f, f, f }; D3DCALL_( R->device, SetPixelShaderConstantF, pos, v, 1 ); }
static void pshc_set_vec4array( SS3D_RD3D9* R, int pos, VEC4 data, int count ){ D3DCALL_( R->device, SetPixelShaderConstantF, pos, data, count ); }
// static void pshc_set_int( SS3D_RD3D9* R, int pos, int i ){ VEC4 v = { i, i, i, i }; D3DCALL_( R->device, SetPixelShaderConstantF, pos, v, 1 ); }

static void shd3d9_free( SS3D_Shader_D3D9* S )
{
	SAFE_RELEASE( S->PSCT );
	SAFE_RELEASE( S->VSCT );
	SAFE_RELEASE( S->PS );
	SAFE_RELEASE( S->VS );
}

static int shd3d9_init_source( SS3D_RD3D9* R, SS3D_Shader_D3D9* S, const char* code, int codelen )
{
	SGS_CTX = R->inh.C;
	HRESULT hr;
	ID3DXBuffer *outbuf = NULL, *outerr = NULL;
	
	memset( S, 0, sizeof(*S) );
	
	static const D3DXMACRO vsmacros[] = { { "VS", "1" }, { NULL, NULL } };
	static const D3DXMACRO psmacros[] = { { "PS", "1" }, { NULL, NULL } };
	
	hr = D3DXCompileShader( code, codelen, vsmacros, NULL, "main", "vs_3_0", D3DXSHADER_OPTIMIZATION_LEVEL3, &outbuf, &outerr, &S->VSCT );
	if( FAILED( hr ) )
	{
		if( outerr )
			sgs_Printf( C, SGS_WARNING, "Errors in vertex shader compilation:\n%s", (const char*) D3DCALL( outerr, GetBufferPointer ) );
		else
			sgs_Printf( C, SGS_WARNING, "Unknown error in vertex shader compilation" );
		if( outbuf ) SAFE_RELEASE( outbuf );
		if( outerr ) SAFE_RELEASE( outerr );
		goto cleanup;
	}
	hr = IDirect3DDevice9_CreateVertexShader( R->device, (const DWORD*) D3DCALL( outbuf, GetBufferPointer ), &S->VS );
	SAFE_RELEASE( outbuf );
	if( outerr ) SAFE_RELEASE( outerr );
	if( FAILED( hr ) )
	{
		sgs_Printf( C, SGS_WARNING, "Unknown error while loading vertex shader" );
		goto cleanup;
	}
	
	hr = D3DXCompileShader( code, codelen, psmacros, NULL, "main", "ps_3_0", D3DXSHADER_OPTIMIZATION_LEVEL3, &outbuf, &outerr, &S->PSCT );
	if( FAILED( hr ) )
	{
		if( outerr )
			sgs_Printf( C, SGS_WARNING, "Errors in pixel shader compilation:\n%s", (const char*) D3DCALL( outerr, GetBufferPointer ) );
		else
			sgs_Printf( C, SGS_WARNING, "Unknown error in pixel shader compilation" );
		if( outbuf ) SAFE_RELEASE( outbuf );
		if( outerr ) SAFE_RELEASE( outerr );
		goto cleanup;
	}
	hr = IDirect3DDevice9_CreatePixelShader( R->device, (const DWORD*) D3DCALL( outbuf, GetBufferPointer ), &S->PS );
	SAFE_RELEASE( outbuf );
	if( outerr ) SAFE_RELEASE( outerr );
	if( FAILED( hr ) )
	{
		sgs_Printf( C, SGS_WARNING, "Unknown error while loading pixel shader" );
		goto cleanup;
	}
	
	return 1;
	
cleanup:
	shd3d9_free( S );
	return 0;
}

#define SH_HDR SS3D_Shader_D3D9* S = (SS3D_Shader_D3D9*) data->data;

static int shd3d9_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_VT_STRING || type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "SS3D_Shader_D3D9" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int shd3d9_destruct( SGS_CTX, sgs_VarObj* data, int unused )
{
	SH_HDR;
	UNUSED( unused );
	shd3d9_free( S );
	return SGS_SUCCESS;
}

static sgs_ObjCallback SS3D_Shader_D3D9_iface[] =
{
	SGS_OP_DESTRUCT, shd3d9_destruct,
	SGS_OP_CONVERT, shd3d9_convert,
	SGS_OP_END
};

static int get_shader_( SS3D_RD3D9* R, sgs_Variable* key )
{
	SGS_CTX = R->inh.C;
	sgs_VHTVar* found = sgs_vht_get( &R->inh.shaders, key );
	if( found )
	{
		sgs_PushVariable( C, &found->val );
		return 1;
	}
	
	// load shader
	{
		char* buf;
		sgs_SizeVal size;
		sgs_Variable val;
		SS3D_Shader_D3D9 shader, *S;
		
		// load code
		sgs_PushString( C, "d3d9" );
		sgs_PushItem( C, 1 );
		sgs_GlobalCall( C, "_SS3D_Shader_LoadCode", 2, 1 );
		if( !sgs_ParseString( C, -1, &buf, &size ) )
			return sgs_Printf( C, SGS_WARNING, "failed to load shader code" );
		
		// compile code
		if( !shd3d9_init_source( R, &shader, buf, size ) )
			return 0;
		
		S = (SS3D_Shader_D3D9*) sgs_PushObjectIPA( C, sizeof(*S), SS3D_Shader_D3D9_iface );
		memcpy( S, &shader, sizeof(*S) );
		sgs_GetStackItem( C, -1, &val );
		
		sgs_vht_set( &R->inh.shaders, C, key, &val );
		return 1;
	}
}

static SS3D_Shader_D3D9* get_shader( SS3D_RD3D9* R, const char* name )
{
	sgs_Variable key;
	SGS_CTX = R->inh.C;
	sgs_SizeVal ssz = sgs_StackSize( C );
	SS3D_Shader_D3D9* out = NULL;
	
	sgs_PushString( C, name );
	sgs_GetStackItem( C, -1, &key );
	
	if( get_shader_( R, &key ) )
		out = (SS3D_Shader_D3D9*) sgs_GetObjectData( C, -1 );
	sgs_SetStackSize( C, ssz );
	return out;
}


//
//  T E X T U R E S
//

static D3DFORMAT texfmt2d3d( int fmt )
{
	switch( fmt )
	{
	case SS3DFORMAT_RGBA8: return D3DFMT_A8B8G8R8;
	case SS3DFORMAT_R5G6B5: return D3DFMT_R5G6B5;
	
	case SS3DFORMAT_DXT1: return D3DFMT_DXT1;
	case SS3DFORMAT_DXT3: return D3DFMT_DXT3;
	case SS3DFORMAT_DXT5: return D3DFMT_DXT5;
	}
	return 0;
}

static void texd3d9_free( SS3D_Texture_D3D9* T )
{
	SAFE_RELEASE( T->ptr.base );
}

static void texdatacopy( D3DLOCKED_RECT* plr, SS3D_TextureData* TD, int side, int mip )
{
	int ret;
	uint8_t *src, *dst;
	size_t i, off, copyrowsize = 0, copyrowcount = 0;
	SS3D_TextureInfo mipTI;
	
	off = SS3D_TextureData_GetMipDataOffset( TD, side, mip );
	ret = SS3D_TextureInfo_GetMipInfo( &TD->info, mip, &mipTI );
	sgs_BreakIf( !ret );
	
	src = ((uint8_t*)TD->data) + off;
	dst = (uint8_t*)plr->pBits;
	SS3D_TextureInfo_GetCopyDims( &mipTI, &copyrowsize, &copyrowcount );
	for( i = 0; i < copyrowcount; ++i )
	{
		memcpy( dst, src, copyrowsize );
		src += copyrowsize;
		dst += plr->Pitch;
	}
}

static int texd3d9_init( SS3D_RD3D9* R, SS3D_Texture_D3D9* T, SS3D_TextureData* TD )
{
	int mip;
	HRESULT hr;
	// TODO: filter unsupported formats / dimensions
	// TODO: generate mipmaps for mipmap-unaware sources if required
	
	if( TD->info.type == SS3DTEXTURE_2D )
	{
		IDirect3DTexture9* d3dtex;
		
		hr = D3DCALL_( R->device, CreateTexture, TD->info.width, TD->info.height, TD->info.mipcount, 0, texfmt2d3d( TD->info.format ), D3DPOOL_MANAGED, &d3dtex, NULL );
		if( FAILED( hr ) )
			return sgs_Printf( R->inh.C, SGS_WARNING, "failed to load texture - error while creating d3d9 texture" );
		
		// load all mip levels into it
		for( mip = 0; mip < TD->info.mipcount; ++mip )
		{
			D3DLOCKED_RECT lr;
			hr = D3DCALL_( d3dtex, LockRect, mip, &lr, NULL, D3DLOCK_DISCARD );
			if( FAILED( hr ) )
				return sgs_Printf( R->inh.C, SGS_WARNING, "failed to load texture - error while locking d3d9 texture" );
			
			texdatacopy( &lr, TD, 0, mip );
			
			hr = D3DCALL_( d3dtex, UnlockRect, mip );
			if( FAILED( hr ) )
				return sgs_Printf( R->inh.C, SGS_WARNING, "failed to load texture - error while unlocking d3d9 texture" );
		}
		
		T->inh.renderer = &R->inh;
		T->inh.info = TD->info;
		T->ptr.tex2d = d3dtex;
		return 1;
	}
	
	return sgs_Printf( R->inh.C, SGS_ERROR, "TODO [reached a part of not-yet-defined behavior]" );
}

#define TEX_HDR SS3D_Texture_D3D9* T = (SS3D_Texture_D3D9*) data->data;

static int texd3d9_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_VT_STRING || type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "SS3D_Texture_D3D9" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int texd3d9_destruct( SGS_CTX, sgs_VarObj* data, int unused )
{
	TEX_HDR;
	UNUSED( unused );
	texd3d9_free( T );
	return SGS_SUCCESS;
}

static sgs_ObjCallback SS3D_Texture_D3D9_iface[] =
{
	SGS_OP_DESTRUCT, texd3d9_destruct,
	SGS_OP_CONVERT, texd3d9_convert,
	SGS_OP_END
};

static int get_texture_( SS3D_RD3D9* R, sgs_Variable* key )
{
	int err;
	SGS_CTX = R->inh.C;
	sgs_VHTVar* found;
	
	sgs_BreakIf( key->type != SGS_VT_STRING );
	
	found = sgs_vht_get( &R->inh.textures, key );
	if( found )
	{
		sgs_PushVariable( C, &found->val );
		return 1;
	}
	
	// load texture
	{
		sgs_Variable val;
		SS3D_TextureData texdata;
		SS3D_Texture_D3D9 texture, *T;
		
		err = SS3D_TextureData_LoadFromFile( &texdata, sgs_var_cstr( key ) );
		if( err != SGS_SUCCESS )
			return 0;
		
		err = !texd3d9_init( R, &texture, &texdata );
		SS3D_TextureData_Free( &texdata );
		if( err )
			return 0;
		
		T = (SS3D_Texture_D3D9*) sgs_PushObjectIPA( C, sizeof(*T), SS3D_Texture_D3D9_iface );
		memcpy( T, &texture, sizeof(*T) );
		sgs_GetStackItem( C, -1, &val );
		
		sgs_vht_set( &R->inh.textures, C, key, &val );
		return 1;
	}
}

static SS3D_Texture_D3D9* get_texture( SS3D_RD3D9* R, const char* name )
{
	sgs_Variable key;
	SGS_CTX = R->inh.C;
	sgs_SizeVal ssz = sgs_StackSize( C );
	SS3D_Texture_D3D9* out = NULL;
	
	sgs_PushString( C, name );
	sgs_GetStackItem( C, -1, &key );
	
	if( get_texture_( R, &key ) )
		out = (SS3D_Texture_D3D9*) sgs_GetObjectData( C, -1 );
	sgs_SetStackSize( C, ssz );
	return out;
}


//
//  R E N D E R E R
//

SGS_DECLARE sgs_ObjCallback SS3D_Renderer_D3D9_iface[];

#define R_HDR SS3D_RD3D9* R = (SS3D_RD3D9*) data->data;
#define R_IHDR( funcname ) \
	int method_call = sgs_Method( C ); \
	sgs_FuncName( C, method_call ? "SS3D_Renderer_D3D9." #funcname : "SS3D_Renderer_D3D9_" #funcname ); \
	if( !sgs_IsObject( C, 0, SS3D_Renderer_D3D9_iface ) ) \
		return sgs_ArgErrorExt( C, 0, method_call, "SS3D_Renderer_D3D9", "" ); \
	SS3D_RD3D9* R = (SS3D_RD3D9*) sgs_GetObjectData( C, 0 );

static int rd3d9i_update( SGS_CTX )
{
	float dt;
	R_IHDR( update );
	if( !sgs_LoadArgs( C, "@>f", &dt ) )
		return 0;
	SS3D_Renderer_Update( &R->inh, dt );
	return 0;
}

typedef struct _testVtx
{
	float x, y, z;
	float nx, ny, nz;
	uint32_t col;
}
testVtx;

static testVtx testVertices[] =
{
	{ -5, -5, -5, -1, -1, -1, D3DCOLOR_XRGB( 233, 222, 211 ) },
	{ +5, -5, -5, +1, -1, -1, D3DCOLOR_XRGB( 233, 211, 222 ) },
	{ +5, +5, -5, +1, +1, -1, D3DCOLOR_XRGB( 222, 211, 222 ) },
	{ -5, +5, -5, -1, +1, -1, D3DCOLOR_XRGB( 222, 222, 211 ) },
	{ -5, -5, +5, -1, -1, +1, D3DCOLOR_XRGB( 211, 222, 233 ) },
	{ +5, -5, +5, +1, -1, +1, D3DCOLOR_XRGB( 222, 211, 233 ) },
	{ +5, +5, +5, +1, +1, +1, D3DCOLOR_XRGB( 222, 211, 233 ) },
	{ -5, +5, +5, -1, +1, +1, D3DCOLOR_XRGB( 211, 222, 233 ) },
	
	{ -50, -50, 0, 0, 0, +1, D3DCOLOR_XRGB( 233, 222, 211 ) },
	{ +50, -50, 0, 0, 0, +1, D3DCOLOR_XRGB( 233, 211, 222 ) },
	{ +50, +50, 0, 0, 0, +1, D3DCOLOR_XRGB( 222, 211, 222 ) },
	{ -50, +50, 0, 0, 0, +1, D3DCOLOR_XRGB( 222, 222, 211 ) },
};
static uint16_t testIndices[] =
{
    // front
    0, 1, 2,
    2, 3, 0,
    // top
    3, 2, 6,
    6, 7, 3,
    // back
    7, 6, 5,
    5, 4, 7,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // left
    4, 0, 3,
    3, 7, 4,
    // right
    1, 5, 6,
    6, 2, 1,
    // plane
    8,9,10,
    10,11,8,
};

typedef struct _ssvtx
{
	float x, y, z;
	float u0, v0;
	float u1, v1;
}
ssvtx;

static int rd3d9i_render( SGS_CTX )
{
	R_IHDR( render );
	if( !R->inh.currentScene )
		return 0;
	SS3D_Scene* scene = (SS3D_Scene*) R->inh.currentScene->data;
	if( !scene->camera )
		return 0;
	SS3D_Camera* cam = (SS3D_Camera*) scene->camera->data;
	
	int w = R->inh.width, h = R->inh.height;
	
	D3DCALL_( R->device, Clear, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xc0c0c0c0, 1.0f, 0 );
	
	D3DCALL_( R->device, SetRenderTarget, 0, R->drd.RTS1 );
	D3DCALL_( R->device, SetRenderTarget, 1, R->drd.RTS2 );
	D3DCALL_( R->device, SetDepthStencilSurface, R->drd.RTSD );
	
	D3DCALL_( R->device, SetRenderState, D3DRS_ZENABLE, 1 );
	D3DCALL_( R->device, SetRenderState, D3DRS_SRCBLEND, D3DBLEND_ONE );
	D3DCALL_( R->device, SetRenderState, D3DRS_DESTBLEND, D3DBLEND_ZERO );
	
	D3DCALL_( R->device, Clear, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0 );
	
	SS3D_Shader_D3D9* sh = get_shader( R, "testDR" );
	use_shader( R, sh );
	
	D3DCALL_( R->device, SetTransform, D3DTS_VIEW, (D3DMATRIX*) *cam->mView );
	D3DCALL_( R->device, SetTransform, D3DTS_PROJECTION, (D3DMATRIX*) *cam->mProj );
	
	vshc_set_mat4( R, 4, cam->mView );
	vshc_set_mat4( R, 12, cam->mProj );
	pshc_set_float( R, 0, cam->zfar );
	
	D3DCALL_( R->device, SetFVF, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE );
	D3DCALL_( R->device, DrawIndexedPrimitiveUP, D3DPT_TRIANGLELIST, 0, 12, 14, testIndices, D3DFMT_INDEX16, testVertices, sizeof(*testVertices) );
	
	D3DCALL_( R->device, SetRenderTarget, 0, R->bb_color );
	D3DCALL_( R->device, SetRenderTarget, 1, NULL );
	D3DCALL_( R->device, SetDepthStencilSurface, R->bb_depth );
	
	D3DCALL_( R->device, SetRenderState, D3DRS_ZENABLE, 0 );
	D3DCALL_( R->device, SetRenderState, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	D3DCALL_( R->device, SetRenderState, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	
	SS3D_Shader_D3D9* sh2 = get_shader( R, "testDRmix" );
	use_shader( R, sh2 );
	
	VEC4 pointlightdata[ 2 * 32 ]; /* px, py, pz, radius, cr, cg, cb, power */
	int i, plc = 0;
	for( i = 0; i < scene->lights.size && plc < 32; ++i )
	{
		SS3D_Light* light = (SS3D_Light*) scene->lights.vars[i].val.data.O->data;
		if( light->type == SS3DLIGHT_POINT )
		{
			VEC3 viewpos;
			SS3D_Mtx_TransformPos( viewpos, light->position, cam->mView );
			VEC4 newdata[2] =
			{
				{ viewpos[0], viewpos[1], viewpos[2], light->range },
				{ light->color[0], light->color[1], light->color[2], light->power }
			};
			memcpy( pointlightdata[ plc * 2 ], newdata, sizeof(VEC4)*2 );
			plc++;
		}
	}
	if( plc )
		pshc_set_vec4array( R, 32, *pointlightdata, 2 * plc );
	pshc_set_float( R, 28, plc ); /* point light count */
	
	float hpox = 0.5f / w;
	float hpoy = 0.5f / h;
	float fsx = 1/cam->mProj[0][0];
	float fsy = 1/cam->mProj[1][1];
	ssvtx ssVertices[] =
	{
		{ -1, -1, 0, 0+hpox, 1+hpoy, -fsx, -fsy },
		{ +1, -1, 0, 1+hpox, 1+hpoy, +fsx, -fsy },
		{ +1, +1, 0, 1+hpox, 0+hpoy, +fsx, +fsy },
		{ -1, +1, 0, 0+hpox, 0+hpoy, -fsx, +fsy },
	};
	
	D3DCALL_( R->device, SetTexture, 0, (IDirect3DBaseTexture9*) R->drd.RTT1 );
	D3DCALL_( R->device, SetTexture, 1, (IDirect3DBaseTexture9*) R->drd.RTT2 );
	D3DCALL_( R->device, SetFVF, D3DFVF_XYZ | D3DFVF_TEX2 );
	D3DCALL_( R->device, DrawPrimitiveUP, D3DPT_TRIANGLEFAN, 2, ssVertices, sizeof(*ssVertices) );
	D3DCALL_( R->device, SetTexture, 0, NULL );
	D3DCALL_( R->device, SetTexture, 0, NULL );
	
	use_shader( R, NULL );
	
	RECT srcRect = { 0, 0, w, h };
	RECT dstRect1 = { 0, 0, w/4, h/4 };
	RECT dstRect2 = { w/4, 0, w/2, h/4 };
	D3DCALL_( R->device, StretchRect, R->drd.RTS1, &srcRect, R->bb_color, &dstRect1, D3DTEXF_POINT );
	D3DCALL_( R->device, StretchRect, R->drd.RTS2, &srcRect, R->bb_color, &dstRect2, D3DTEXF_POINT );
	
	return 0;
}

static int rd3d9i_resize( SGS_CTX )
{
	sgs_Int w, h;
	R_IHDR( resize );
	if( !sgs_LoadArgs( C, "@>ii", &w, &h ) )
		return 0;
	SS3D_Renderer_Resize( &R->inh, w, h );
	return 0;
}

static int rd3d9i_onDeviceLost( SGS_CTX )
{
	R_IHDR( onDeviceLost );
	UNUSED( R );
	return 0;
}

static int rd3d9i_onDeviceReset( SGS_CTX )
{
	R_IHDR( onDeviceReset );
	UNUSED( R );
	return 0;
}

static int rd3d9i_getShader( SGS_CTX )
{
	sgs_Variable key;
	R_IHDR( getShader );
	if( !sgs_LoadArgs( C, "@>?s<v", &key ) )
		return 0;
	return get_shader_( R, &key );
}

static int rd3d9i_createScene( SGS_CTX )
{
	R_IHDR( createScene );
	SS3D_Renderer_PushScene( &R->inh );
	return 1;
}

static int rd3d9_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	R_HDR;
	SGS_BEGIN_INDEXFUNC
		// methods
		SGS_CASE( "update" )        SGS_RETURN_CFUNC( rd3d9i_update )
		SGS_CASE( "render" )        SGS_RETURN_CFUNC( rd3d9i_render )
		SGS_CASE( "resize" )        SGS_RETURN_CFUNC( rd3d9i_resize )
		SGS_CASE( "onDeviceLost" )  SGS_RETURN_CFUNC( rd3d9i_onDeviceLost )
		SGS_CASE( "onDeviceReset" ) SGS_RETURN_CFUNC( rd3d9i_onDeviceReset )
		
		SGS_CASE( "getShader" )     SGS_RETURN_CFUNC( rd3d9i_getShader )
		SGS_CASE( "createScene" )   SGS_RETURN_CFUNC( rd3d9i_createScene )
		
		// properties
		SGS_CASE( "currentScene" )          SGS_RETURN_OBJECT( R->inh.currentScene )
		SGS_CASE( "enableDeferredShading" ) SGS_RETURN_BOOL( R->inh.enableDeferredShading )
	SGS_END_INDEXFUNC;
}

static int rd3d9_setindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	R_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "currentScene" ) SGS_PARSE_OBJECT_IF( SS3D_Scene_iface, R->inh.currentScene, 0, ((SS3D_Scene*)sgs_GetObjectData( C, 1 ))->renderer == &R->inh )
		SGS_CASE( "enableDeferredShading" ) SGS_PARSE_BOOL( R->inh.enableDeferredShading )
	}
	return SGS_ENOTFND;
}

static int rd3d9_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_VT_STRING || type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "SS3D_Renderer_D3D9" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int rd3d9_destruct( SGS_CTX, sgs_VarObj* data, int unused )
{
	R_HDR;
	UNUSED( unused );
	
	drd_free( R, &R->drd );
	SAFE_RELEASE( R->bb_color );
	SAFE_RELEASE( R->bb_depth );
	SAFE_RELEASE( R->device );
	
	SS3D_Renderer_Destruct( &R->inh );
	
	return SGS_SUCCESS;
}

static sgs_ObjCallback SS3D_Renderer_D3D9_iface[] =
{
	SGS_OP_GETINDEX, rd3d9_getindex,
	SGS_OP_SETINDEX, rd3d9_setindex,
	SGS_OP_DESTRUCT, rd3d9_destruct,
	SGS_OP_CONVERT, rd3d9_convert,
	SGS_OP_END
};


int SS3D_PushRenderer_D3D9( SGS_CTX, void* device )
{
	sgs_BreakIf( !device );
	SS3D_RD3D9* R = (SS3D_RD3D9*) sgs_PushObjectIPA( C, sizeof(*R), SS3D_Renderer_D3D9_iface );
	
	SS3D_Renderer_Construct( &R->inh, C );
	
	R->inh.API = "D3D9";
	R->device = (IDirect3DDevice9*) device;
	D3DCALL( R->device, AddRef );
	D3DCALL_( R->device, GetRenderTarget, 0, &R->bb_color );
	D3DCALL_( R->device, GetDepthStencilSurface, &R->bb_depth );
	{
		D3DSURFACE_DESC desc;
		HRESULT hr = D3DCALL_( R->bb_color, GetDesc, &desc );
		sgs_BreakIf( FAILED( hr ) );
		R->inh.width = desc.Width;
		R->inh.height = desc.Height;
	}
	
	drd_init( R, &R->drd, R->inh.width, R->inh.height );
	
	return 1;
}

