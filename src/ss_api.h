
#ifndef SS_API_H_INCLUDED
#define SS_API_H_INCLUDED


/*
	This file must be included after sgscript.h
*/

#define CT_HREPEAT 1
#define CT_VREPEAT 2
#define CT_NOLERP 4
#define CT_MIPMAPS 8

typedef struct _sgs_Texture
{
	/* GLuint */ uint32_t id;
#if defined(SS_USED3D) && ( defined(BUILDING_SGS_SDL) || defined(SS_USE_TYPES) )
	IDirect3DBaseTexture9*
#else
	void*
#endif
	/* lptex */	obj;
	int32_t flags;
	int16_t width;
	int16_t height;
}
sgs_Texture;


#define SSI_D3D 1
#define SSI_D3D_DEVICE 2
#define SSI_TEX_IFACE 3


/* functions transferred via the SGScript hash table */
/* calling them would most probably crash the engine or corrupt the memory,
	so the identifier-unfriendly symbols try to prevent that from happening */

#define SS_PARSE_TEXTURE_KEY "$__parse_texture"
#define SS_PARSE_TEXTURE pfn_ss_parse_texture ss_parse_texture
typedef int (*pfn_ss_parse_texture) ( sgs_Context*, int /* item */, sgs_Texture** /* tex */ );


#define SS_GET_IFACE_KEY "$__get_iface"
#define SS_GET_IFACE pfn_ss_get_iface ss_get_iface
typedef void* (*pfn_ss_get_iface) ( int which );


#ifndef BUILDING_SGS_SDL

static void* ss_get_apifunc( SGS_CTX, const char* key )
{
	if( sgs_PushGlobal( C, key ) == SGS_SUCCESS )
	{
		void* data;
		if( sgs_ItemType( C, -1 ) != SGS_VT_OBJECT )
			return NULL;
		data = sgs_GetObjectData( C, -1 )->data;
		sgs_Pop( C, 1 );
		return data;
	}
	return NULL;
}

#endif


#endif
