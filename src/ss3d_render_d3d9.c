
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

typedef struct _SS3D_RD3D9
{
	SS3D_Renderer inh;
	
	IDirect3DDevice9* device;
}
SS3D_RD3D9;


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
};

static int rd3d9i_render( SGS_CTX )
{
	R_IHDR( render );
	if( !R->inh.currentScene )
		return 0;
	
	IDirect3DDevice9_Clear( R->device, 0, NULL, D3DCLEAR_TARGET, 0xc0c0c0c0, 1.0f, 0 );
	D3DCALL_( R->device, SetRenderState, D3DRS_ZENABLE, 1 );
	
	SS3D_Scene* scene = (SS3D_Scene*) R->inh.currentScene->data;
	if( scene->camera )
	{
		SS3D_Camera* cam = (SS3D_Camera*) scene->camera->data;
		D3DCALL_( R->device, SetTransform, D3DTS_VIEW, (D3DMATRIX*) *cam->mView );
		D3DCALL_( R->device, SetTransform, D3DTS_PROJECTION, (D3DMATRIX*) *cam->mProj );
	}
	D3DCALL_( R->device, SetFVF, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE );
	D3DCALL_( R->device, DrawIndexedPrimitiveUP, D3DPT_TRIANGLELIST, 0, 8, 12, testIndices, D3DFMT_INDEX16, testVertices, sizeof(*testVertices) );
	
	D3DCALL_( R->device, SetRenderState, D3DRS_ZENABLE, 0 );
	
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
	sgs_Variable key, val;
	sgs_VHTVar* found;
	
	R_IHDR( getShader );
	if( !sgs_LoadArgs( C, "@>?s<v", &key ) )
		return 0;
	
	found = sgs_vht_get( &R->inh.shaders, &key );
	if( found )
	{
		sgs_PushVariable( C, &found->val );
		return 1;
	}
	
	// load shader
	{
		char* buf;
		sgs_SizeVal size;
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
		
		sgs_vht_set( &R->inh.shaders, C, &key, &val );
		return 1;
	}
}

static int rd3d9i_createScene( SGS_CTX )
{
	R_IHDR( createScene );
	SS3D_Renderer_PushScene( &R->inh );
	return 1;
}

static int rd3d9_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* name;
	R_HDR;
	if( sgs_ParseString( C, 0, &name, NULL ) )
	{
		// methods
		if( !strcmp( name, "update" ) ){ sgs_PushCFunction( C, rd3d9i_update ); return SGS_SUCCESS; }
		if( !strcmp( name, "render" ) ){ sgs_PushCFunction( C, rd3d9i_render ); return SGS_SUCCESS; }
		if( !strcmp( name, "resize" ) ){ sgs_PushCFunction( C, rd3d9i_resize ); return SGS_SUCCESS; }
		if( !strcmp( name, "onDeviceLost" ) ){ sgs_PushCFunction( C, rd3d9i_onDeviceLost ); return SGS_SUCCESS; }
		if( !strcmp( name, "onDeviceReset" ) ){ sgs_PushCFunction( C, rd3d9i_onDeviceReset ); return SGS_SUCCESS; }
		
		if( !strcmp( name, "getShader" ) ){ sgs_PushCFunction( C, rd3d9i_getShader ); return SGS_SUCCESS; }
		if( !strcmp( name, "createScene" ) ){ sgs_PushCFunction( C, rd3d9i_createScene ); return SGS_SUCCESS; }
		
		// properties
		if( !strcmp( name, "currentScene" ) ){ sgs_PushObjectPtr( C, R->inh.currentScene ); return SGS_SUCCESS; }
		if( !strcmp( name, "enableDeferredShading" ) ){ sgs_PushBool( C, R->inh.enableDeferredShading ); return SGS_SUCCESS; }
	}
	return SGS_ENOTFND;
}

static int rd3d9_setindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* name;
	R_HDR;
	if( sgs_ParseString( C, 0, &name, NULL ) )
	{
		if( !strcmp( name, "currentScene" ) )
		{
			if( sgs_ItemType( C, 1 ) == SGS_VT_NULL )
			{
				if( R->inh.currentScene )
					sgs_ObjRelease( C, R->inh.currentScene );
				R->inh.currentScene = NULL;
			}
			if( sgs_IsObject( C, 1, SS3D_Scene_iface ) )
			{
				sgs_VarObj* ns = sgs_GetObjectStruct( C, 1 );
				if( ((SS3D_Scene*)ns->data)->renderer == &R->inh )
				{
					if( R->inh.currentScene )
						sgs_ObjRelease( C, R->inh.currentScene );
					R->inh.currentScene = ns;
					sgs_ObjAcquire( C, ns );
					return SGS_SUCCESS;
				}
			}
			return SGS_EINVAL;
		}
		if( !strcmp( name, "enableDeferredShading" ) )
			return sgs_ParseBool( C, 1, &R->inh.enableDeferredShading ) ? SGS_SUCCESS : SGS_EINVAL;
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
	IDirect3DDevice9_AddRef( R->device );
	return 1;
}

