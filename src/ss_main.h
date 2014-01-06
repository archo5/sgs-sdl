
#ifndef SS_MAIN_H_INCLUDED
#define SS_MAIN_H_INCLUDED


#ifndef SS_IS_LAUNCHER
#  define SS_API __declspec(dllexport)
#else
#  define SS_API
#endif


#include "ss_cfg.h"

#ifdef SS_USED3D
#  undef VT_NULL
#  undef VT_BOOL
#  undef VT_INT
#  include <d3d9.h>
extern IDirect3D9* GD3D;
extern IDirect3DDevice9* GD3DDev;
#else
#  include <GL/gl.h>
extern void* GD3D;
extern void* GD3DDev;
#endif

#undef TRUE
#undef FALSE
#undef MIN
#undef MAX

#include <SDL/SDL.h>

#define SDL_VIDEO_DEVICELOST SDL_USEREVENT + 1
#define SDL_VIDEO_DEVICERESET SDL_USEREVENT + 2
#ifndef SS_USED3D
#  define GL_GLEXT_PROTOTYPES
#  include "SDL/SDL_opengl.h"
#  include "glext.h"
extern PFNGLBLENDEQUATIONPROC ss_glBlendEquation;
#endif

#include "../sgscript/src/sgscript.h"
#include "../sgscript/ext/sgsxgmath.h"

#include "ss_api.h"


#define ARRAY_SIZE( x ) (sizeof(x)/sizeof(x[0]))


/* globals */
extern int g_width;
extern int g_height;


/* SGScript helpers */

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

sgs_Integer sgs_GlobalInt( SGS_CTX, const char* name );
uint32_t sgs_GetFlagString( SGS_CTX, int pos, flag_string_item_t* items );
uint32_t sgs_GlobalFlagString( SGS_CTX, const char* name, flag_string_item_t* items );
int sgs_UnpackDict( SGS_CTX, int pos, dict_unpack_item_t* items );
void sgs_UnpackFree( SGS_CTX, dict_unpack_item_t* items );

int stdlib_tovec2d( SGS_CTX, int pos, sgs_Real* v2f, int strict );
int stdlib_tocolor4( SGS_CTX, int pos, sgs_Real* v4f );
int sgs_InitExtMath( SGS_CTX );
int sgs_InitExtSys( SGS_CTX );


/* SGScript - Images */
typedef struct _sgs_Image
{
	void* data; /* 32 bit RGBA */
	int16_t width;
	int16_t height;
}
sgs_Image;
int sgs_InitImage( SGS_CTX );
int sgs_IsImageVar( sgs_Variable* var );
int stdlib_toimage( SGS_CTX, int pos, sgs_Image** out );
int sgs_CreateImageHelper( SGS_CTX, int16_t w, int16_t h, const void* bits );
int sgs_LoadImageHelper( SGS_CTX, char* str, int size );
sgs_Image* sgs_ImageDS2X( sgs_Image* src, SGS_CTX );
void sgs_DeleteImage( sgs_Image* img, SGS_CTX );


/* SGScript - SDL */
int sgs_InitSDL( SGS_CTX );
int sgs_CreateSDLEvent( SGS_CTX, SDL_Event* event );
void sgs_FreeGraphics( SGS_CTX );


/* SGScript - OpenGL */
int sgs_InitGL( SGS_CTX );


/* utility */
void* ss_request_memory( size_t numbytes );
void ss_reset_buffer();


/* API */
int ss_parse_texture( SGS_CTX, int item, sgs_Texture** out );
void* ss_get_iface( int which );

int sgs_InitAPI( SGS_CTX );


/* Core interface */
#define SS_PTR_SGSCTX 1
#define SS_PTR_WINDOW 2
#define SS_PTR_D3DDEV 3
int ss_Initialize( int argc, char* argv[] );
int ss_Frame();
int ss_Free();
void* ss_GetPtr( int pid );


#endif /* SS_MAIN_H_INCLUDED */
