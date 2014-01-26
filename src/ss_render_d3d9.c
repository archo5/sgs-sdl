

#include <d3d9.h>

#include <SDL2/SDL_syswm.h>


#define SS_TEXTURE_HANDLE_DATA IDirect3DBaseTexture9* base; IDirect3DTexture9* tex2d;
#define SS_VERTEXFORMAT_HANDLE_DATA IDirect3DVertexDeclaration9* vdecl;

#include "ss_main.h"


typedef IDirect3D9* WINAPI (*pfnDirect3DCreate9) (UINT SDKVersion); 


static void* GD3D9_DLL = NULL;
static IDirect3D9* GD3D = NULL;


static void _ss_reset_states( IDirect3DDevice9* dev, int w, int h )
{
	IDirect3DDevice9_SetTextureStageState( dev, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	IDirect3DDevice9_SetTextureStageState( dev, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	IDirect3DDevice9_SetTextureStageState( dev, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	IDirect3DDevice9_SetTextureStageState( dev, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	IDirect3DDevice9_SetRenderState( dev, D3DRS_LIGHTING, 0 );
	IDirect3DDevice9_SetRenderState( dev, D3DRS_CULLMODE, D3DCULL_NONE );
	IDirect3DDevice9_SetRenderState( dev, D3DRS_ZENABLE, 0 );
	IDirect3DDevice9_SetRenderState( dev, D3DRS_ALPHABLENDENABLE, 1 );
	IDirect3DDevice9_SetRenderState( dev, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	IDirect3DDevice9_SetRenderState( dev, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	{
		float wm[ 16 ] = { 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1 };
		float vm[ 16 ] = { 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 100,  0, 0, 0, 1 };
		float pm[ 16 ] = { 2.0f/(float)w, 0, 0, 0,  0, 2.0f/(float)h, 0, 0,  0, 0, 1.0f/999.0f, 1.0f/-999.0f,  0, 0, 0, 1 };
		IDirect3DDevice9_SetTransform( dev, D3DTS_WORLD, (D3DMATRIX*) wm );
		IDirect3DDevice9_SetTransform( dev, D3DTS_VIEW, (D3DMATRIX*) vm );
		IDirect3DDevice9_SetTransform( dev, D3DTS_PROJECTION, (D3DMATRIX*) pm );
	}
}

static void _ss_reset_device( IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* pd3dpp )
{
	SGS_CTX = ss_GetContext();
	D3DPRESENT_PARAMETERS npp;
	SDL_Event event;
	
	npp = *pd3dpp;
	
	event.type = SDL_VIDEODEVICELOST;
	ss_CreateSDLEvent( C, &event );
	sgs_GlobalCall( C, "on_event", 1, 0 );
	
	IDirect3DDevice9_Reset( dev, &npp );
	
	_ss_reset_states( dev, pd3dpp->BackBufferWidth, pd3dpp->BackBufferHeight );
	
	event.type = SDL_VIDEODEVICERESET;
	ss_CreateSDLEvent( C, &event );
	sgs_GlobalCall( C, "on_event", 1, 0 );
}


struct _SS_Renderer
{
	SDL_Window* window;
	IDirect3DDevice9* d3ddev;
	D3DPRESENT_PARAMETERS d3dpp;
	sgs_VHTable rsrc_table;
	int destructing;
};


static void ss_ri_d3d9_init();
static void ss_ri_d3d9_free();
static int ss_ri_d3d9_available();
static SS_Renderer* ss_ri_d3d9_create( SDL_Window* window, uint32_t version, uint32_t flags );
static void ss_ri_d3d9_destroy( SS_Renderer* R );
static void ss_ri_d3d9_modify( SS_Renderer* R, int* modlist );
static void ss_ri_d3d9_set_current( SS_Renderer* R );
static void ss_ri_d3d9_poke_resource( SS_Renderer* R, sgs_VarObj* obj, int add );
static void ss_ri_d3d9_swap( SS_Renderer* R );
static void ss_ri_d3d9_clear( SS_Renderer* R, float* col4f );
static void ss_ri_d3d9_set_render_state( SS_Renderer* R, int which, int arg0, int arg1, int arg2, int arg3 );
static void ss_ri_d3d9_set_matrix( SS_Renderer* R, int which, float* data );

static int ss_ri_d3d9_create_texture_argb8( SS_Renderer* R, SS_Texture* T, SS_Image* I, uint32_t flags );
static int ss_ri_d3d9_create_texture_a8( SS_Renderer* R, SS_Texture* T, uint8_t* data, int width, int height, int pitch );
static int ss_ri_d3d9_destroy_texture( SS_Renderer* R, SS_Texture* T );
static int ss_ri_d3d9_apply_texture( SS_Renderer* R, SS_Texture* T );

static int ss_ri_d3d9_init_vertex_format( SS_Renderer* R, SS_VertexFormat* F );
static int ss_ri_d3d9_free_vertex_format( SS_Renderer* R, SS_VertexFormat* F );
static int ss_ri_d3d9_draw_basic_vertices( SS_Renderer* R, void* data, uint32_t count, int ptype );
static int ss_ri_d3d9_draw_ext( SS_Renderer* R, SS_VertexFormat* F, void* vdata, uint32_t vdsize, void* idata, uint32_t idsize, int i32, uint32_t start, uint32_t count, int ptype );


SS_RenderInterface GRI_D3D9 =
{
	ss_ri_d3d9_init,
	ss_ri_d3d9_free,
	ss_ri_d3d9_available,
	ss_ri_d3d9_create,
	ss_ri_d3d9_destroy,
	ss_ri_d3d9_modify,
	ss_ri_d3d9_set_current,
	ss_ri_d3d9_poke_resource,
	ss_ri_d3d9_swap,
	ss_ri_d3d9_clear,
	ss_ri_d3d9_set_render_state,
	ss_ri_d3d9_set_matrix,
	
	ss_ri_d3d9_create_texture_argb8,
	ss_ri_d3d9_create_texture_a8,
	ss_ri_d3d9_destroy_texture,
	ss_ri_d3d9_apply_texture,
	
	ss_ri_d3d9_init_vertex_format,
	ss_ri_d3d9_free_vertex_format,
	ss_ri_d3d9_draw_basic_vertices,
	ss_ri_d3d9_draw_ext,
	
	/* flags */
	SS_RI_HALFPIXELOFFSET | SS_RI_COLOR_BGRA,
	
	/* last error */
	"no error",
};


static void ss_ri_d3d9_init()
{
	GD3D9_DLL = SDL_LoadObject( "d3d9.dll" );
	if( GD3D9_DLL )
	{
		pfnDirect3DCreate9 func = (pfnDirect3DCreate9) SDL_LoadFunction( GD3D9_DLL, "Direct3DCreate9" );
		if( func )
			GD3D = func( D3D_SDK_VERSION );
	}
}

static void ss_ri_d3d9_free()
{
	if( GD3D )
		IDirect3DResource9_Release( GD3D );
	if( GD3D9_DLL )
		SDL_UnloadObject( GD3D9_DLL );
}

static int ss_ri_d3d9_available()
{
	return !!GD3D;
}

static SS_Renderer* ss_ri_d3d9_create( SDL_Window* window, uint32_t version, uint32_t flags )
{
	int w, h, suc;
	SDL_SysWMinfo sysinfo;
	D3DPRESENT_PARAMETERS d3dpp;
	IDirect3DDevice9* d3ddev;
	SS_Renderer* R;
	
	SDL_GetWindowSize( window, &w, &h );
	
	SDL_VERSION( &sysinfo.version );
	if( SDL_GetWindowWMInfo( window, &sysinfo ) <= 0 )
	{
		GRI_D3D9.last_error = SDL_GetError();
		return NULL;
	}
	
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow = sysinfo.info.win.window;
	d3dpp.BackBufferWidth = w;
	d3dpp.BackBufferHeight = h;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.PresentationInterval = ( flags & SS_RENDERER_VSYNC ) ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
	
	suc = !FAILED( IDirect3D9_CreateDevice( GD3D,
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, sysinfo.info.win.window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE, &d3dpp, &d3ddev ) );
	if( !suc )
	{
		GRI_D3D9.last_error = "failed to create the device";
		return NULL;
	}
	
	_ss_reset_states( d3ddev, w, h );
	
	R = (SS_Renderer*) malloc( sizeof(*R) );
	R->window = window;
	R->d3ddev = d3ddev;
	R->d3dpp = d3dpp;
	
	sgs_vht_init( &R->rsrc_table, ss_GetContext(), 64, 64 );
	R->destructing = 0;
	
	return R;
}

static void ss_ri_d3d9_destroy( SS_Renderer* R )
{
	int i;
	SGS_CTX = ss_GetContext();
	R->destructing = 1;
	for( i = 0; i < R->rsrc_table.size; ++i )
	{
		sgs_VarObj* obj = (sgs_VarObj*) R->rsrc_table.vars[ i ].val.data.P;
		ss_CallDtor( C, obj );
	}
	sgs_vht_free( &R->rsrc_table, C );
	
	if( GCurRr == R )
	{
		GCurRr = NULL;
		GCurRI = NULL;
	}
	IDirect3DResource9_Release( R->d3ddev );
	free( R );
}

static void ss_ri_d3d9_modify( SS_Renderer* R, int* modlist )
{
	int w, h;
	int resize = 0;
	SDL_GetWindowSize( R->window, &w, &h );
	
	while( *modlist )
	{
		if( *modlist == SS_RMOD_WIDTH ){ resize = 1; w = modlist[1]; }
		else if( *modlist == SS_RMOD_HEIGHT ){ resize = 1; h = modlist[1]; }
		
		modlist += 2;
	}
	
	if( resize )
	{
		R->d3dpp.BackBufferWidth = w;
		R->d3dpp.BackBufferHeight = h;
		_ss_reset_device( R->d3ddev, &R->d3dpp );
	}
}

static void ss_ri_d3d9_set_current( SS_Renderer* R )
{
	UNUSED( R );
}

static void ss_ri_d3d9_poke_resource( SS_Renderer* R, sgs_VarObj* obj, int add )
{
	SGS_CTX = ss_GetContext();
	sgs_Variable K;
	
	if( R->destructing )
		return;
	
	K.type = SGS_VT_PTR;
	K.data.P = obj;
	
	if( add )
		sgs_vht_set( &R->rsrc_table, C, &K, &K );
	else
		sgs_vht_unset( &R->rsrc_table, C, &K );
}

static void ss_ri_d3d9_swap( SS_Renderer* R )
{
	IDirect3DDevice9_EndScene( R->d3ddev );
	if( IDirect3DDevice9_Present( R->d3ddev, NULL, NULL, NULL, NULL ) == D3DERR_DEVICELOST )
	{
		if( IDirect3DDevice9_TestCooperativeLevel( R->d3ddev ) == D3DERR_DEVICENOTRESET )
		{
			_ss_reset_device( R->d3ddev, &R->d3dpp );
		}
	}
	IDirect3DDevice9_BeginScene( R->d3ddev );
}

static void ss_ri_d3d9_clear( SS_Renderer* R, float* col4f )
{
	uint32_t cc = (((uint8_t)(col4f[3]*255))<<24) | (((uint8_t)(col4f[0]*255))<<16) |
		(((uint8_t)(col4f[1]*255))<<8) | (((uint8_t)(col4f[2]*255)));
	IDirect3DDevice9_Clear( R->d3ddev, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, cc, 1.0f, 0 );
}

static void ss_ri_d3d9_set_render_state( SS_Renderer* R, int which, int arg0, int arg1, int arg2, int arg3 )
{
	if( which == SS_RS_BLENDFACTORS )
	{
		static const int blendfactors[] =
		{
			D3DBLEND_ZERO,
			D3DBLEND_ONE,
			D3DBLEND_SRCCOLOR,
			D3DBLEND_INVSRCCOLOR,
			D3DBLEND_SRCALPHA,
			D3DBLEND_INVSRCALPHA,
			D3DBLEND_DESTCOLOR,
			D3DBLEND_INVDESTCOLOR,
			D3DBLEND_DESTALPHA,
			D3DBLEND_INVDESTALPHA,
			D3DBLEND_SRCALPHASAT,
		};
		if( arg0 < 0 || arg0 >= SS_BLEND__COUNT ) arg0 = SS_BLEND_SRCALPHA;
		if( arg1 < 0 || arg1 >= SS_BLEND__COUNT ) arg1 = SS_BLEND_INVSRCALPHA;
		IDirect3DDevice9_SetRenderState( R->d3ddev, D3DRS_SRCBLEND, blendfactors[ arg0 ] );
		IDirect3DDevice9_SetRenderState( R->d3ddev, D3DRS_DESTBLEND, blendfactors[ arg1 ] );
	}
	else if( which == SS_RS_BLENDOP )
	{
		static const int blendfuncs[] =
		{
			D3DBLENDOP_ADD, D3DBLENDOP_SUBTRACT, D3DBLENDOP_REVSUBTRACT, D3DBLENDOP_MIN, D3DBLENDOP_MAX,
		};
		if( arg0 < 0 || arg0 >= SS_BLENDOP__COUNT ) arg0 = SS_BLENDOP_ADD;
		IDirect3DDevice9_SetRenderState( R->d3ddev, D3DRS_BLENDOP, blendfuncs[ arg0 ] );
	}
	else if( which == SS_RS_CLIPENABLE )
	{
		IDirect3DDevice9_SetRenderState( R->d3ddev, D3DRS_SCISSORTESTENABLE, arg0 ? 1 : 0 );
	}
	else if( which == SS_RS_CLIPRECT )
	{
		/* x0 = arg0, y0 = arg1, x1 = arg2, y1 = arg3 */
		RECT rect = { arg0, arg1, arg2, arg3 };
		IDirect3DDevice9_SetScissorRect( R->d3ddev, &rect );
	}
	else if( which == SS_RS_CULLING )
	{
		IDirect3DDevice9_SetRenderState( R->d3ddev, D3DRS_CULLMODE, arg0 ? ( arg0 > 0 ? D3DCULL_CCW : D3DCULL_CW ) : D3DCULL_NONE );
	}
	else if( which == SS_RS_ZENABLE )
	{
		IDirect3DDevice9_SetRenderState( R->d3ddev, D3DRS_ZENABLE, arg0 );
	}
}

static void ss_ri_d3d9_set_matrix( SS_Renderer* R, int which, float* mtx )
{
	if( which == SS_RMAT_WORLD )
		IDirect3DDevice9_SetTransform( R->d3ddev, D3DTS_WORLD, (D3DMATRIX*) mtx );
	else if( which == SS_RMAT_VIEW )
		IDirect3DDevice9_SetTransform( R->d3ddev, D3DTS_VIEW, (D3DMATRIX*) mtx );
	else if( which == SS_RMAT_PROJ )
		IDirect3DDevice9_SetTransform( R->d3ddev, D3DTS_PROJECTION, (D3DMATRIX*) mtx );
}


static int ss_ri_d3d9_create_texture_argb8( SS_Renderer* R, SS_Texture* T, SS_Image* I, uint32_t flags )
{
	HRESULT hr;
	SGS_CTX = ss_GetContext();
	int miplev = 1, i, y;
	SS_Image* pdI = I, *pI;
	IDirect3DTexture9* tex = NULL;
	
	if( flags & SS_TEXTURE_MIPMAPS )
	{
		int sz = I->width > I->height ? I->width : I->height;
		while( sz > 1 )
		{
			sz /= 2;
			miplev++;
		}
	}
	
	hr = IDirect3DDevice9_CreateTexture( R->d3ddev, I->width, I->height,
		miplev, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, NULL );
	if( tex == NULL || FAILED(hr) )
		return 0;
	
	for( i = 0; i < miplev; ++i )
	{
		pI = pdI;
		D3DLOCKED_RECT lr;
		IDirect3DTexture9_LockRect( tex, i, &lr, NULL, D3DLOCK_DISCARD );
		for( y = 0; y < pdI->height; ++y )
			memcpy( ((uint8_t*)lr.pBits) + lr.Pitch * y, pdI->data + pdI->width * 4 * y, pdI->width * 4 );
		IDirect3DTexture9_UnlockRect( tex, i );
		if( i < miplev-1 )
			pdI = ss_ImageDS2X( pdI, C );
		if( pI != I )
			ss_DeleteImage( pI, C );
	}
	
	T->riface = &GRI_D3D9;
	T->renderer = R;
	T->width = I->width;
	T->height = I->height;
	T->flags = flags;
	T->handle.tex2d = tex;
	return 1;
}

static int ss_ri_d3d9_create_texture_a8( SS_Renderer* R, SS_Texture* T, uint8_t* data, int width, int height, int pitch )
{
	int x, y;
	HRESULT hr;
	D3DLOCKED_RECT lr;
	IDirect3DTexture9* tex = NULL;
	
	hr = IDirect3DDevice9_CreateTexture( R->d3ddev, width,
		height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, NULL );
	if( tex == NULL || FAILED(hr) )
		return 0;
	
	IDirect3DTexture9_LockRect( tex, 0, &lr, NULL, D3DLOCK_DISCARD );
	for( y = 0; y < height; ++y )
	{
		for( x = 0; x < width; ++x )
		{
			int off = y * lr.Pitch + x * 4;
			((uint8_t*)lr.pBits)[ off ] = 0xff;
			((uint8_t*)lr.pBits)[ off + 1 ] = 0xff;
			((uint8_t*)lr.pBits)[ off + 2 ] = 0xff;
			((uint8_t*)lr.pBits)[ off + 3 ] = data[ x ];
		}
		data += pitch;
	}
	IDirect3DTexture9_UnlockRect( tex, 0 );
	
	T->riface = &GRI_D3D9;
	T->renderer = R;
	T->width = width;
	T->height = height;
	T->flags = 0;
	T->handle.tex2d = tex;
	return 1;
}

static int ss_ri_d3d9_destroy_texture( SS_Renderer* R, SS_Texture* T )
{
	IDirect3DResource9_Release( T->handle.base );
	return 1;
}

static int ss_ri_d3d9_apply_texture( SS_Renderer* R, SS_Texture* T )
{
	IDirect3DDevice9_SetTexture( R->d3ddev, 0, T ? T->handle.base : NULL );
	if( T )
	{
		int lin = !( T->flags & SS_TEXTURE_NOLERP );
		int mip = ( T->flags & SS_TEXTURE_MIPMAPS );
		int hr = ( T->flags & SS_TEXTURE_HREPEAT );
		int vr = ( T->flags & SS_TEXTURE_VREPEAT );
		IDirect3DDevice9_SetSamplerState( R->d3ddev, 0, D3DSAMP_MINFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( R->d3ddev, 0, D3DSAMP_MAGFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( R->d3ddev, 0, D3DSAMP_MIPFILTER, mip ? ( lin ? D3DTEXF_LINEAR : D3DTEXF_POINT ) : D3DTEXF_NONE );
		IDirect3DDevice9_SetSamplerState( R->d3ddev, 0, D3DSAMP_ADDRESSU, hr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
		IDirect3DDevice9_SetSamplerState( R->d3ddev, 0, D3DSAMP_ADDRESSV, vr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
	}
	
	return 1;
}


static int vd_make_typecount( int type, int count )
{
	if( type == SS_RSET_FLOAT && count == 1 ) return D3DDECLTYPE_FLOAT1;
	if( type == SS_RSET_FLOAT && count == 2 ) return D3DDECLTYPE_FLOAT2;
	if( type == SS_RSET_FLOAT && count == 3 ) return D3DDECLTYPE_FLOAT3;
	if( type == SS_RSET_FLOAT && count == 4 ) return D3DDECLTYPE_FLOAT4;
	if( type == SS_RSET_BYTE && count == 4 ) return D3DDECLTYPE_D3DCOLOR;
	return 0;
}

static int ss_ri_d3d9_init_vertex_format( SS_Renderer* R, SS_VertexFormat* F )
{
	HRESULT hr;
	D3DVERTEXELEMENT9 els[ 5 ] = { D3DDECL_END(), D3DDECL_END(),
		D3DDECL_END(), D3DDECL_END(), D3DDECL_END() };
	
	int i = 0;
	if( F->P[0] )
	{
		D3DVERTEXELEMENT9 el = { 0, F->P[1], vd_make_typecount( F->P[2], F->P[3] ),
			D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 };
		memcpy( els + i++, &el, sizeof(D3DVERTEXELEMENT9) );
	}
	if( F->T[0] )
	{
		D3DVERTEXELEMENT9 el = { 0, F->T[1], vd_make_typecount( F->T[2], F->T[3] ),
			D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };
		memcpy( els + i++, &el, sizeof(D3DVERTEXELEMENT9) );
	}
	if( F->C[0] )
	{
		D3DVERTEXELEMENT9 el = { 0, F->C[1], vd_make_typecount( F->C[2], F->C[3] ),
			D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 };
		memcpy( els + i++, &el, sizeof(D3DVERTEXELEMENT9) );
	}
	if( F->N[0] )
	{
		D3DVERTEXELEMENT9 el = { 0, F->N[1], vd_make_typecount( F->N[2], F->N[3] ),
			D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 };
		memcpy( els + i++, &el, sizeof(D3DVERTEXELEMENT9) );
	}
	
	F->handle.vdecl = NULL;
	hr = IDirect3DDevice9_CreateVertexDeclaration( R->d3ddev, els, &F->handle.vdecl );
	if( FAILED( hr ) || !F->handle.vdecl )
	{
		GRI_D3D9.last_error = "vertex declaration creation failed";
		return 0;
	}
	
	return 1;
}

static int ss_ri_d3d9_free_vertex_format( SS_Renderer* R, SS_VertexFormat* F )
{
	IDirect3DVertexDeclaration9_Release( F->handle.vdecl );
	return 1;
}

static const int primtypes[] =
{
	D3DPT_POINTLIST,
	D3DPT_LINELIST,
	D3DPT_LINESTRIP,
	D3DPT_TRIANGLELIST,
	D3DPT_TRIANGLEFAN,
	D3DPT_TRIANGLESTRIP,
	-10,
};

static int getprimitivecount( int mode, uint32_t vcount )
{
	switch( mode )
	{
	case SS_PT_POINTS: return vcount;
	case SS_PT_LINES: return vcount / 2;
	case SS_PT_LINE_STRIP: return vcount - 1;
	case SS_PT_TRIANGLES: return vcount / 3;
	case SS_PT_TRIANGLE_FAN: return vcount - 2;
	case SS_PT_TRIANGLE_STRIP: return vcount - 2;
	case SS_PT_QUADS: return vcount / 4;
	}
	return 0;
}

static int ss_ri_d3d9_draw_basic_vertices( SS_Renderer* R, void* data, uint32_t count, int ptype )
{
	int mode;
	char* Bptr = (char*) data;
	
	if( ptype < 0 || ptype >= SS_PT__COUNT )
		return 0;
	mode = primtypes[ ptype ];
	
	IDirect3DDevice9_SetFVF( R->d3ddev, D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE );
	if( ptype == SS_PT_QUADS )
	{
		int i, cnt = count - 3;
		for( i = 0; i < cnt; i += 4 )
		{
			IDirect3DDevice9_DrawPrimitiveUP( R->d3ddev, D3DPT_TRIANGLEFAN,
				2, Bptr + sizeof(SS_BasicVertex) * i, sizeof(SS_BasicVertex) );
		}
	}
	else
	{
		IDirect3DDevice9_DrawPrimitiveUP( R->d3ddev, mode,
			getprimitivecount( ptype, count ),
			Bptr, sizeof(SS_BasicVertex) );
	}
	
	return 1;
}

static int ss_ri_d3d9_draw_ext( SS_Renderer* R, SS_VertexFormat* F, void* vdata, uint32_t vdsize, void* idata, uint32_t idsize, int i32, uint32_t start, uint32_t count, int ptype )
{
	int mode;
	char* BVptr = (char*) vdata;
	char* idcs = (char*) idata;
	
	if( ptype < 0 || ptype >= SS_PT__COUNT )
		return 0;
	mode = primtypes[ ptype ];
	
	IDirect3DDevice9_SetVertexDeclaration( R->d3ddev, F->handle.vdecl );
	if( idcs )
		IDirect3DDevice9_DrawIndexedPrimitiveUP( R->d3ddev, mode, 0, count,
			getprimitivecount( ptype, count ), idcs + start * 2, D3DFMT_INDEX16,
			BVptr, F->size );
	else
	{
		if( ptype == SS_PT_QUADS )
		{
			int i, cnt = count - 3;
			for( i = 0; i < cnt; i += 4 )
			{
				IDirect3DDevice9_DrawPrimitiveUP( R->d3ddev, D3DPT_TRIANGLEFAN,
					2, BVptr + F->size * i, F->size );
			}
		}
		else
		{
			IDirect3DDevice9_DrawPrimitiveUP( R->d3ddev, mode,
				getprimitivecount( ptype, count ),
				BVptr, F->size );
		}
	}
	IDirect3DDevice9_SetVertexDeclaration( R->d3ddev, NULL );
	
	return 1;
}

