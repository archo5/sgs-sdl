
#ifndef SS_MAIN_H_INCLUDED
#define SS_MAIN_H_INCLUDED


#ifndef SS_IS_LAUNCHER
#  define SS_API __declspec(dllexport)
#else
#  define SS_API
#endif

#include "ss_cfg.h"

#include <stdio.h>
#include <SDL2/SDL.h>

#define SDL_VIDEODEVICELOST SDL_USEREVENT + 1
#define SDL_VIDEODEVICERESET SDL_USEREVENT + 2


#include "../sgscript/src/sgscript.h"
#include "../sgscript/src/sgs_util.h"
#include "../sgscript/ext/sgsxgmath.h"


#define ARRAY_SIZE( x ) (sizeof(x)/sizeof(x[0]))


/* SGScript helpers */
sgs_Context* ss_GetContext();

typedef struct flag_string_item_s
{
	const char* name;
	int value;
}
flag_string_item_t;

#define FSI_LAST { NULL, 0 }

typedef struct dict_unpack_item_s
{
	const char* name;
	sgs_Variable* var;
}
dict_unpack_item_t;

#define DUI_LAST { NULL, NULL }

void ss_CallDtor( SGS_CTX, sgs_VarObj* O );
sgs_Integer ss_GlobalInt( SGS_CTX, const char* name );
uint32_t ss_GetFlagString( SGS_CTX, int pos, flag_string_item_t* items );
uint32_t ss_GlobalFlagString( SGS_CTX, const char* name, flag_string_item_t* items );
int ss_UnpackDict( SGS_CTX, int pos, dict_unpack_item_t* items );
void ss_UnpackFree( SGS_CTX, dict_unpack_item_t* items );

int ss_ParseVec2( SGS_CTX, int pos, float* v2f, int strict );
int ss_ParseColor( SGS_CTX, int pos, float* v4f );
int ss_InitExtMath( SGS_CTX );
int ss_InitExtSys( SGS_CTX );


/* SGScript - Images */
typedef struct _SS_Image
{
	void* data; /* 32 bit RGBA */
	int16_t width;
	int16_t height;
}
SS_Image;
int ss_InitImage( SGS_CTX );
int ss_IsImageVar( sgs_Variable* var );
int ss_ParseImage( SGS_CTX, int pos, SS_Image** out );
int ss_CreateImageHelper( SGS_CTX, int16_t w, int16_t h, const void* bits );
int ss_LoadImageHelper( SGS_CTX, char* str, int size );
SS_Image* ss_ImageDS2X( SS_Image* src, SGS_CTX );
void ss_DeleteImage( SS_Image* img, SGS_CTX );


/* SGScript - SDL */
int ss_InitSDL( SGS_CTX );
int ss_CreateSDLEvent( SGS_CTX, SDL_Event* event );
void ss_FreeGraphics( SGS_CTX );


/* SGScript - Graphics */
int ss_InitGraphics( SGS_CTX );


/*  RENDERING INTERFACE  */
#define SS_RI_HALFPIXELOFFSET 0x0001
#define SS_RI_COLOR_BGRA      0x0002
#define SS_RI_COLOR_RGBA      0x0004

#define SS_RENDERER_DONTCARE  0
#define SS_RENDERER_OPENGL    1
#define SS_RENDERER_DIRECT3D9 2

#define SS_RENDERER_VSYNC 0x00000001
#define SS_RENDERER_DEBUG 0x00000002

#define SS_RMOD_WIDTH  1
#define SS_RMOD_HEIGHT 2

#define SS_RS_BLENDFACTORS 1
#define SS_RS_BLENDOP      2
#define SS_RS_CLIPENABLE   3
#define SS_RS_CLIPRECT     4
#define SS_RS_CULLING      5
#define SS_RS_ZENABLE      6

#define SS_RMAT_WORLD 0
#define SS_RMAT_VIEW  1
#define SS_RMAT_PROJ  2

#define SS_TEXTURE_HREPEAT 0x0001
#define SS_TEXTURE_VREPEAT 0x0002
#define SS_TEXTURE_NOLERP  0x0004
#define SS_TEXTURE_MIPMAPS 0x0008

#define SS_PT_POINTS         0
#define SS_PT_LINES          1
#define SS_PT_LINE_STRIP     2
#define SS_PT_TRIANGLES      3
#define SS_PT_TRIANGLE_FAN   4
#define SS_PT_TRIANGLE_STRIP 5
#define SS_PT_QUADS          6
#define SS_PT__COUNT         7

#define SS_RSET_FLOAT 1
#define SS_RSET_BYTE  2

#define SS_BLENDOP_ADD              0
#define SS_BLENDOP_SUBTRACT         1
#define SS_BLENDOP_REVERSE_SUBTRACT 2
#define SS_BLENDOP_MIN              3
#define SS_BLENDOP_MAX              4
#define SS_BLENDOP__COUNT           5

#define SS_BLEND_ZERO         0
#define SS_BLEND_ONE          1
#define SS_BLEND_SRCCOLOR     2
#define SS_BLEND_INVSRCCOLOR  3
#define SS_BLEND_SRCALPHA     4
#define SS_BLEND_INVSRCALPHA  5
#define SS_BLEND_DESTCOLOR    6
#define SS_BLEND_INVDESTCOLOR 7
#define SS_BLEND_DESTALPHA    8
#define SS_BLEND_INVDESTALPHA 9
#define SS_BLEND_SRCALPHASAT 10
#define SS_BLEND__COUNT      11

#ifndef SS_TEXTURE_HANDLE_DATA
#define SS_TEXTURE_HANDLE_DATA void* ptr; uint32_t u32;
#endif

typedef struct _SS_RenderInterface SS_RenderInterface;
typedef struct _SS_Renderer SS_Renderer;

typedef struct _SS_Texture
{
	SS_RenderInterface* riface;
	SS_Renderer* renderer;
	
	union { SS_TEXTURE_HANDLE_DATA } handle;
	
	int16_t width;
	int16_t height;
	uint16_t flags;
}
SS_Texture;


#ifndef SS_VERTEXFORMAT_HANDLE_DATA
#define SS_VERTEXFORMAT_HANDLE_DATA void* ptr; uint32_t u32;
#endif

typedef struct _SS_VertexFormat
{
	SS_RenderInterface* riface;
	SS_Renderer* renderer;
	
	union { SS_VERTEXFORMAT_HANDLE_DATA } handle;
	
	uint16_t size;
	/* use / offset / type / count / size / order */
	uint16_t P[ 6 ];
	uint16_t T[ 6 ];
	uint16_t C[ 6 ];
	uint16_t N[ 6 ];
}
SS_VertexFormat;

typedef struct _SS_BasicVertex
{
	float pos[ 3 ];   /* 4 * 3 => 12b */
	uint32_t col;     /*           4b */
	float tex[ 2 ];   /* 4 * 2 =>  8b */
	float padding[2]; /* 4 * 2 =>  8b */
	/* total: 32 bytes */
}
SS_BasicVertex;

typedef void (*ss_ri_init) ();
typedef void (*ss_ri_free) ();
typedef int (*ss_ri_available) ();
typedef SS_Renderer* (*ss_ri_create) ( SDL_Window*, uint32_t, uint32_t ); /* version, flags */
typedef void (*ss_ri_destroy) ( SS_Renderer* );
typedef void (*ss_ri_modify) ( SS_Renderer*, int* );
typedef void (*ss_ri_set_current) ( SS_Renderer* );
typedef void (*ss_ri_poke_resource) ( SS_Renderer*, sgs_VarObj*, int ); /* !=0 => add, otherwise remove */
typedef void (*ss_ri_swap) ( SS_Renderer* );
typedef void (*ss_ri_clear) ( SS_Renderer*, float* );
typedef void (*ss_ri_set_render_state) ( SS_Renderer*, int, int, int, int, int ); /* type, arg0, arg1, arg2, arg3 */
typedef void (*ss_ri_set_matrix) ( SS_Renderer*, int, float* ); /* type, float[16] */

typedef int (*ss_ri_create_texture_argb8) ( SS_Renderer*, SS_Texture*, SS_Image*, uint32_t );
typedef int (*ss_ri_create_texture_a8) ( SS_Renderer*, SS_Texture*, uint8_t*, int, int, int ); /* data, width, height, pitch */
typedef int (*ss_ri_destroy_texture) ( SS_Renderer*, SS_Texture* );
typedef int (*ss_ri_apply_texture) ( SS_Renderer*, SS_Texture* );

typedef int (*ss_ri_init_vertex_format) ( SS_Renderer*, SS_VertexFormat* );
typedef int (*ss_ri_free_vertex_format) ( SS_Renderer*, SS_VertexFormat* );
typedef int (*ss_ri_draw_basic_vertices) ( SS_Renderer*, void*, uint32_t, int ); /* SS_BasicVertex*, count, ptype */
typedef int (*ss_ri_draw_ext) ( SS_Renderer*, SS_VertexFormat*, void*, uint32_t, void*, uint32_t, int, uint32_t, uint32_t, int );
	/* vertex_data, vertex_data_size, index_data, index_data_size, bool i32, start, count, ptype */

struct _SS_RenderInterface
{
	ss_ri_init init;
	ss_ri_free free;
	ss_ri_available available;
	ss_ri_create create;
	ss_ri_destroy destroy;
	ss_ri_modify modify;
	ss_ri_set_current set_current;
	ss_ri_poke_resource poke_resource;
	ss_ri_swap swap;
	ss_ri_clear clear;
	ss_ri_set_render_state set_render_state;
	ss_ri_set_matrix set_matrix;
	
	ss_ri_create_texture_argb8 create_texture_argb8;
	ss_ri_create_texture_a8 create_texture_a8;
	ss_ri_destroy_texture destroy_texture;
	ss_ri_apply_texture apply_texture;
	
	ss_ri_init_vertex_format init_vertex_format;
	ss_ri_free_vertex_format free_vertex_format;
	ss_ri_draw_basic_vertices draw_basic_vertices;
	ss_ri_draw_ext draw_ext;
	
	uint32_t flags;
	
	const char* last_error;
};


extern SS_RenderInterface* GCurRI;
extern SS_Renderer* GCurRr;

#define SCRFN_NEEDS_RENDER_CONTEXT if( !GCurRI || !GCurRr ) _WARN( "must have rendering context set to use this function" );
#define SCRFN_NEEDS_SPECIFIC_RENDER_CONTEXT( riface, rend ) if( GCurRI != riface || GCurRr != rend ) _WARN( "must have object's owning rendering context set to use this function" );

void ss_MakeCurrent( SS_RenderInterface* ri, SS_Renderer* rr );

typedef struct _SS_TmpCtx
{
	SS_RenderInterface* riface;
	SS_Renderer* renderer;
}
SS_TmpCtx;
SS_TmpCtx ss_TmpMakeCurrent( SS_RenderInterface* ri, SS_Renderer* rr );
void ss_TmpRestoreCurrent( SS_TmpCtx* ctx );


/* utility */
char* ss_get_buffer_ptr();
char* ss_request_memory( size_t numbytes );
void ss_reset_buffer();
#define ss_request_memory_idx( numbytes ) (ss_request_memory( numbytes ) - ss_get_buffer_ptr())


/* API */
int ss_ParseTexture( SGS_CTX, int item, SS_Texture** out );


/* Core interface */
int ss_Initialize( int argc, char* argv[], int debug );
int ss_Frame();
int ss_Free();


#endif /* SS_MAIN_H_INCLUDED */
