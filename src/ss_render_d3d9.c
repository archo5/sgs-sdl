

#include <d3d9.h>

#define D3DCALL( x, m ) (x)->lpVtbl->m( (x) )
#define D3DCALL_( x, m, ... ) (x)->lpVtbl->m( (x), __VA_ARGS__ )
#define SAFE_RELEASE( x ) if( x ){ D3DCALL( x, Release ); x = NULL; }


#include <SDL2/SDL_syswm.h>


#define SS_TEXTURE_HANDLE_DATA IDirect3DBaseTexture9* base; IDirect3DTexture9* tex2d;
#define SS_TEXRSURF_HANDLE_DATA IDirect3DSurface9* surf;
#define SS_VERTEXFORMAT_HANDLE_DATA IDirect3DVertexDeclaration9* vdecl;
#define SS_RENDERER_OVERRIDE

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


struct _SS_Renderer
{
	SS_RENDERER_DATA
	IDirect3DDevice9* d3ddev;
	D3DPRESENT_PARAMETERS d3dpp;
	IDirect3DSurface9* backbuf;
	IDirect3DSurface9* dssurf;
	SS_Texture* cur_rtt;
	int width;
	int height;
	int bbwidth, bbheight, bbscale;
};


static void ss_ri_d3d9__resetviewport( SS_Renderer* R )
{
	D3DVIEWPORT9 vp = { 0, 0, -1, -1, 0.0, 1.0 };
	if( R->bbscale != SS_POSMODE_NONE )
	{
		vp.Width = sgs_MIN( R->bbwidth, R->width );
		vp.Height = sgs_MIN( R->bbheight, R->height );
	}
	else
	{
		vp.Width = R->width;
		vp.Height = R->height;
	}
	IDirect3DDevice9_SetViewport( R->d3ddev, &vp );
}


static void ss_ri_d3d9_init();
static void ss_ri_d3d9_free();
static int ss_ri_d3d9_available();
static SS_Renderer* ss_ri_d3d9_create( SDL_Window* window, uint32_t version, uint32_t flags );
static void ss_ri_d3d9_destroy( SS_Renderer* R );
static void* ss_ri_d3d9_get_pointer( SS_Renderer* R, int which );
static void ss_ri_d3d9_modify( SS_Renderer* R, int* modlist );
static void ss_ri_d3d9_set_buffer_scale( SS_Renderer* R, int enable, int width, int height, int scalemode );
static void ss_ri_d3d9_set_current( SS_Renderer* R );
static void ss_ri_d3d9_poke_resource( SS_Renderer* R, sgs_VarObj* obj, int add );
static void ss_ri_d3d9_swap( SS_Renderer* R );
static void ss_ri_d3d9_clear( SS_Renderer* R, float* col4f );
static void ss_ri_d3d9_set_render_state( SS_Renderer* R, int which, int arg0, int arg1, int arg2, int arg3 );
static void ss_ri_d3d9_set_matrix( SS_Renderer* R, int which, float* data );
static void ss_ri_d3d9_set_rt( SS_Renderer* R, SS_Texture* T );

static int ss_ri_d3d9_create_texture_argb8( SS_Renderer* R, SS_Texture* T, SS_Image* I, uint32_t flags );
static int ss_ri_d3d9_create_texture_a8( SS_Renderer* R, SS_Texture* T, uint8_t* data, int width, int height, int pitch );
static int ss_ri_d3d9_create_texture_rnd( SS_Renderer* R, SS_Texture* T, int width, int height, uint32_t flags );
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
	ss_ri_d3d9_get_pointer,
	ss_ri_d3d9_modify,
	ss_ri_d3d9_set_buffer_scale,
	ss_ri_d3d9_set_current,
	ss_ri_d3d9_poke_resource,
	ss_ri_d3d9_swap,
	ss_ri_d3d9_clear,
	ss_ri_d3d9_set_render_state,
	ss_ri_d3d9_set_matrix,
	ss_ri_d3d9_set_rt,
	
	ss_ri_d3d9_create_texture_argb8,
	ss_ri_d3d9_create_texture_a8,
	ss_ri_d3d9_create_texture_rnd,
	ss_ri_d3d9_destroy_texture,
	ss_ri_d3d9_apply_texture,
	
	ss_ri_d3d9_init_vertex_format,
	ss_ri_d3d9_free_vertex_format,
	ss_ri_d3d9_draw_basic_vertices,
	ss_ri_d3d9_draw_ext,
	
	/* flags */
	SS_RI_HALFPIXELOFFSET | SS_RI_COLOR_BGRA,
	/* API */
	"D3D9",
	
	/* last error */
	"no error",
};


static int _ssr_reset_device( SS_Renderer* R )
{
	SGS_CTX = ss_GetContext();
	D3DPRESENT_PARAMETERS npp;
	SDL_Event event;
	int i;
	
	event.type = SDL_VIDEODEVICELOST;
	ss_CreateSDLEvent( C, &event );
	sgs_GlobalCall( C, "on_event", 1, 0 );
	
	SAFE_RELEASE( R->backbuf );
	SAFE_RELEASE( R->dssurf );
	/* free all renderable textures */
	for( i = 0; i < R->rsrc_table.size; ++i )
	{
		sgs_VarObj* obj = (sgs_VarObj*) R->rsrc_table.vars[ i ].val.data.P;
		if( obj->iface == SS_Texture_iface )
		{
			SS_Texture* T = (SS_Texture*) obj->data;
			if( T->flags & SS_TEXTURE_RENDER )
			{
				SAFE_RELEASE( T->rsh.surf );
				SAFE_RELEASE( T->handle.tex2d );
			}
		}
	}
	
	/* reset */
	npp = R->d3dpp;
	
	IDirect3DDevice9_Reset( R->d3ddev, &npp );
	
	_ss_reset_states( R->d3ddev, R->d3dpp.BackBufferWidth, R->d3dpp.BackBufferHeight );
	R->cur_rtt = NULL;
	/* --- */
	
	if( FAILED( D3DCALL_( R->d3ddev, GetRenderTarget, 0, &R->backbuf ) ) )
	{
		GRI_D3D9.last_error = "failed to retrieve original backbuffer";
		return 0;
	}
	if( FAILED( D3DCALL_( R->d3ddev, GetDepthStencilSurface, &R->dssurf ) ) )
	{
		GRI_D3D9.last_error = "failed to retrieve original depth stencil surface";
		return 0;
	}
	/* recreate all renderable textures */
	for( i = 0; i < R->rsrc_table.size; ++i )
	{
		sgs_VarObj* obj = (sgs_VarObj*) R->rsrc_table.vars[ i ].val.data.P;
		if( obj->iface == SS_Texture_iface )
		{
			SS_Texture* T = (SS_Texture*) obj->data;
			if( T->flags & SS_TEXTURE_RENDER )
			{
				HRESULT hr = IDirect3DDevice9_CreateTexture( R->d3ddev, T->width, T->height, 1,
					D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &T->handle.tex2d, NULL );
				if( T->handle.tex2d == NULL || FAILED(hr) )
				{
					R->iface->last_error = "could not create renderable texture";
					return 0;
				}
				
				hr = D3DCALL_( T->handle.tex2d, GetSurfaceLevel, 0, &T->rsh.surf );
				if( T->rsh.surf == NULL || FAILED(hr) )
				{
					R->iface->last_error = "failed to retrieve render surface";
					return 0;
				}
			}
		}
	}
	
	event.type = SDL_VIDEODEVICERESET;
	ss_CreateSDLEvent( C, &event );
	sgs_GlobalCall( C, "on_event", 1, 0 );
	
	return 1;
}


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
	SGS_CTX = ss_GetContext();
	
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
	R->iface = &GRI_D3D9;
	R->window = window;
	R->d3ddev = d3ddev;
	R->d3dpp = d3dpp;
	if( FAILED( D3DCALL_( R->d3ddev, GetRenderTarget, 0, &R->backbuf ) ) )
	{
		GRI_D3D9.last_error = "failed to retrieve original backbuffer";
		return NULL;
	}
	if( FAILED( D3DCALL_( R->d3ddev, GetDepthStencilSurface, &R->dssurf ) ) )
	{
		GRI_D3D9.last_error = "failed to retrieve original depth stencil surface";
		return NULL;
	}
	
	R->width = w;
	R->height = h;

	R->bbwidth = 0;
	R->bbheight = 0;
	R->bbscale = 0;
	
	sgs_vht_init( &R->rsrc_table, C, 64, 64 );
	R->destructing = 0;
	
	sgs_InitDict( C, &R->textures, 0 );
	sgs_InitDict( C, &R->fonts, 0 );
	sgs_InitDict( C, &R->rsdict, 0 );
	
	sgs_PushString( C, "textures" );
	sgs_SetIndexPIP( C, &R->rsdict, -1, &R->textures, 0 );
	sgs_Pop( C, 1 );
	sgs_PushString( C, "fonts" );
	sgs_SetIndexPIP( C, &R->rsdict, -1, &R->fonts, 0 );
	sgs_Pop( C, 1 );
	
	return R;
}

static void ss_ri_d3d9_destroy( SS_Renderer* R )
{
	int i;
	SGS_CTX = ss_GetContext();
	
	sgs_Release( C, &R->rsdict );
	
	R->destructing = 1;
	for( i = 0; i < R->rsrc_table.size; ++i )
	{
		sgs_VarObj* obj = (sgs_VarObj*) R->rsrc_table.vars[ i ].val.data.P;
		sgs_ObjCallDtor( C, obj );
	}
	sgs_vht_free( &R->rsrc_table, C );
	
	if( GCurRr == R )
	{
		GCurRr = NULL;
		GCurRI = NULL;
	}
	SAFE_RELEASE( R->backbuf );
	SAFE_RELEASE( R->dssurf );
	IDirect3DResource9_Release( R->d3ddev );
	free( R );
}

static void* ss_ri_d3d9_get_pointer( SS_Renderer* R, int which )
{
	if( which == 0 ) return R->d3ddev;
	return NULL;
}

static void ss_ri_d3d9_modify( SS_Renderer* R, int* modlist )
{
	int w, h;
	int resize = 0;
	SDL_GetWindowSize( R->window, &w, &h );
	
	while( *modlist )
	{
		if( *modlist == SS_RMOD_WIDTH ){ resize = 1; w = modlist[1]; R->width = w; }
		else if( *modlist == SS_RMOD_HEIGHT ){ resize = 1; h = modlist[1]; R->height = h; }
		
		modlist += 2;
	}
	
	if( resize )
	{
		R->d3dpp.BackBufferWidth = w;
		R->d3dpp.BackBufferHeight = h;
		_ssr_reset_device( R );
		ss_ri_d3d9__resetviewport( R );
	}
}

static void ss_ri_d3d9_set_buffer_scale( SS_Renderer* R, int enable, int width, int height, int scalemode )
{
	R->bbwidth = enable ? width : 0;
	R->bbheight = enable ? height : 0;
	R->bbscale = enable ? scalemode : 0;
}

static void ss_ri_d3d9_set_current( SS_Renderer* R )
{
	SGS_CTX = ss_GetContext();
	sgs_PushVariable( C, &R->rsdict );
	sgs_StoreGlobal( C, "_R" );
	
	UNUSED( R );
}

static void ss_ri_d3d9_poke_resource( SS_Renderer* R, sgs_VarObj* obj, int add )
{
	SGS_CTX = ss_GetContext();
	sgs_Variable K;
	
	if( R->destructing )
		return;
	
	sgs_InitPtr( &K, obj );
	if( add )
		sgs_vht_set( &R->rsrc_table, C, &K, &K );
	else
		sgs_vht_unset( &R->rsrc_table, C, &K );
}

static void ss_ri_d3d9_swap( SS_Renderer* R )
{
	ss_ri_d3d9_set_rt( R, NULL );
	IDirect3DDevice9_EndScene( R->d3ddev );
	
	if( R->bbscale != SS_POSMODE_NONE )
	{
		int w = sgs_MIN( R->bbwidth, R->width );
		int h = sgs_MIN( R->bbheight, R->height );
		
		IDirect3DSurface9 *plain = NULL, *target = NULL;
		if( !FAILED( IDirect3DDevice9_CreateOffscreenPlainSurface( R->d3ddev, R->width, R->height, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &plain, NULL ) ) && plain &&
			!FAILED( IDirect3DDevice9_CreateRenderTarget( R->d3ddev, w, h, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, 0, &target, NULL ) ) && target )
		{
			RECT srcrect = { 0, 0, w, h };
			if( !FAILED( IDirect3DDevice9_GetRenderTargetData( R->d3ddev, R->backbuf, plain ) ) &&
				!FAILED( IDirect3DDevice9_UpdateSurface( R->d3ddev, plain, &srcrect, target, NULL ) ) )
			{
				/* width factors */
				float wf = 1, hf = 1, xoff, yoff;
				float aspect = ( (float) w / (float) h ) / ( (float) R->width / (float) R->height );
				switch( R->bbscale )
				{
				case SS_POSMODE_CROP:
					if( aspect > 1 )
						wf = aspect;
					else
						hf = 1 / aspect;
					break;
				case SS_POSMODE_FIT:
					if( aspect > 1 )
						hf = 1 / aspect;
					else
						wf = aspect;
					break;
				case SS_POSMODE_FITRND:
					{
						int wc = (int) floor( (float) R->width / (float) w );
						int hc = (int) floor( (float) R->height / (float) h );
						int cnt = sgs_MAX( 1, sgs_MIN( wc, hc ) );
						wf = (float) w * cnt / (float) R->width;
						hf = (float) h * cnt / (float) R->height;
					}
					break;
				case SS_POSMODE_CENTER:
					wf = (float) w / (float) R->width;
					hf = (float) h / (float) R->height;
					break;
				default:
					break;
				}
				xoff = ( 1 - wf ) / 2;
				yoff = ( 1 - hf ) / 2;
				
				{
					D3DVIEWPORT9 fullvp = { 0, 0, R->width, R->height, -1, 1 };
					RECT dstrect = { xoff * R->width, yoff * R->height, (xoff+wf) * R->width, (yoff+hf) * R->height };
					IDirect3DDevice9_SetViewport( R->d3ddev, &fullvp );
					IDirect3DDevice9_Clear( R->d3ddev, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0 );
					IDirect3DDevice9_StretchRect( R->d3ddev, target, &srcrect, R->backbuf, &dstrect, D3DTEXF_POINT );
				}
			}
		}
		
		SAFE_RELEASE( plain );
		SAFE_RELEASE( target );
	}
	
	if( IDirect3DDevice9_Present( R->d3ddev, NULL, NULL, NULL, NULL ) == D3DERR_DEVICELOST )
	{
		if( IDirect3DDevice9_TestCooperativeLevel( R->d3ddev ) == D3DERR_DEVICENOTRESET )
		{
			_ssr_reset_device( R );
		}
	}
	IDirect3DDevice9_BeginScene( R->d3ddev );
	ss_ri_d3d9_set_rt( R, NULL );
}

static void ss_ri_d3d9_clear( SS_Renderer* R, float* col4f )
{
	uint32_t cc = (((uint8_t)(col4f[3]*255))<<24) | (((uint8_t)(col4f[0]*255))<<16) |
		(((uint8_t)(col4f[1]*255))<<8) | (((uint8_t)(col4f[2]*255)));
	uint32_t flags = D3DCLEAR_TARGET;
	if( !R->cur_rtt )
		flags |= D3DCLEAR_ZBUFFER;
	IDirect3DDevice9_Clear( R->d3ddev, 0, NULL, flags, cc, 1.0f, 0 );
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
	else if( which == SS_RS_VIEWPORT )
	{
		/* x0 = arg0, y0 = arg1, x1 = arg2, y1 = arg3 */
		D3DVIEWPORT9 vp = { arg0, arg1, arg2 - arg0, arg3 - arg1, 0.0, 1.0 };
		IDirect3DDevice9_SetViewport( R->d3ddev, &vp );
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
	{
		/* this solves the d3d9 texel->pixel mapping issue */
		float w = R->bbwidth ? R->bbwidth : R->width;
		float h = R->bbheight ? R->bbheight : R->height;
		float mox[ 16 ];
		if( w || h )
		{
			float mfx[ 16 ] = { 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  w ? -1.0f / w : 0, h ? 1.0f / h : 0, 0, 1 };
			SS_Mat4Multiply( (float(*)[4])mtx, (float(*)[4])mfx, (float(*)[4])mox );
		}
		else
			memcpy( mox, mtx, sizeof(mox) );
		IDirect3DDevice9_SetTransform( R->d3ddev, D3DTS_PROJECTION, (D3DMATRIX*) mox );
	}
}

static void ss_ri_d3d9_set_rt( SS_Renderer* R, SS_Texture* T )
{
	IDirect3DSurface9* surf = T ? T->rsh.surf : R->backbuf;
	IDirect3DSurface9* dssurf = T ? NULL : R->dssurf;
	R->cur_rtt = T;
	D3DCALL_( R->d3ddev, SetRenderTarget, 0, surf );
	D3DCALL_( R->d3ddev, SetDepthStencilSurface, dssurf );
	if( !T )
		ss_ri_d3d9__resetviewport( R );
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
	
	T->renderer = R;
	T->width = width;
	T->height = height;
	T->flags = 0;
	T->handle.tex2d = tex;
	return 1;
}

static int ss_ri_d3d9_create_texture_rnd( SS_Renderer* R, SS_Texture* T, int width, int height, uint32_t flags )
{
	HRESULT hr;
	IDirect3DTexture9* tex = NULL;
	
	hr = IDirect3DDevice9_CreateTexture( R->d3ddev, width,
		height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &tex, NULL );
	if( tex == NULL || FAILED(hr) )
	{
		R->iface->last_error = "could not create renderable texture";
		return 0;
	}
	
	hr = D3DCALL_( tex, GetSurfaceLevel, 0, &T->rsh.surf );
	if( T->rsh.surf == NULL || FAILED(hr) )
	{
		R->iface->last_error = "failed to retrieve render surface";
		return 0;
	}
	T->renderer = R;
	T->width = width;
	T->height = height;
	T->flags = flags | SS_TEXTURE_RENDER;
	T->handle.tex2d = tex;
	return 1;
}

static int ss_ri_d3d9_destroy_texture( SS_Renderer* R, SS_Texture* T )
{
	if( R->cur_rtt == T )
		ss_ri_d3d9_set_rt( R, NULL );
	SAFE_RELEASE( T->rsh.surf );
	SAFE_RELEASE( T->handle.base );
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
	IDirect3DDevice9_DrawPrimitiveUP( R->d3ddev, mode,
		getprimitivecount( ptype, count ),
		Bptr, sizeof(SS_BasicVertex) );
	
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
		IDirect3DDevice9_DrawPrimitiveUP( R->d3ddev, mode,
			getprimitivecount( ptype, count ),
			BVptr, F->size );
	}
	IDirect3DDevice9_SetVertexDeclaration( R->d3ddev, NULL );
	
	return 1;
}

