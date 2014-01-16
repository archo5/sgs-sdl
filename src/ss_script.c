
#include <math.h>
#include <assert.h>

#define SGS_INTERNAL

#include "ss_main.h"

#undef ARRAY_SIZE
#include "../sgscript/ext/sgs_prof.c"
#include "../sgscript/ext/sgs_idbg.c"
#undef ARRAY_SIZE
#define ARRAY_SIZE( x ) (sizeof(x)/sizeof(x[0]))


#define _WARN( err ) return sgs_Printf( C, SGS_WARNING, err );

sgs_Integer sgs_GlobalInt( SGS_CTX, const char* name )
{
	sgs_Integer v;
	if( sgs_PushGlobal( C, name ) != SGS_SUCCESS )
		return 0;
	v = sgs_GetInt( C, -1 );
	sgs_Pop( C, 1 );
	return v;
}

uint32_t sgs_GetFlagString( SGS_CTX, int pos, flag_string_item_t* items )
{
	char* str;
	uint32_t flags = 0;
	str = sgs_ToString( C, pos );
	if( !str )
		return 0;
	
	while( items->name )
	{
		char* pos = strstr( str, items->name );
		if( pos )
		{
			int len = strlen( items->name );
			if( pos[ len ] == ',' || pos[ len ] == 0 )
				flags |= items->value;
		}
		items++;
	}
	return flags;
}

uint32_t sgs_GlobalFlagString( SGS_CTX, const char* name, flag_string_item_t* items )
{
	uint32_t flags = 0;
	if( sgs_PushGlobal( C, name ) != SGS_SUCCESS )
		return 0;
	flags = sgs_GetFlagString( C, -1, items );
	sgs_Pop( C, 1 );
	return flags;
}

int sgs_UnpackDict( SGS_CTX, int pos, dict_unpack_item_t* items )
{
	int ret = 0;
	sgs_String32 S;
	
	if( sgs_ItemType( C, pos ) != SVT_OBJECT )
		return ret;
	
	while( items->name )
	{
		sgs_SizeVal sz = sgs_StackSize( C );
		sgs_PushString32( C, &S, items->name );
		
		assert( items->var != NULL );
		if( sgs_PushIndex( C, pos, -1 ) || !sgs_GetStackItem( C, -1, items->var ) )
			items->var = NULL;
		else
		{
			sgs_Acquire( C, items->var );
			ret++;
		}
		
		items++;
		sgs_SetStackSize( C, sz );
		sgs_CheckString32( &S );
	}
	return ret;
}

void sgs_UnpackFree( SGS_CTX, dict_unpack_item_t* items )
{
	while( items->name )
	{
		if( items->var )
			sgs_Release( C, items->var );
		items++;
	}
}

/*
	C O L O R
*/
int stdlib_tocolor4( SGS_CTX, int pos, sgs_Real* v4f )
{
	float tmp[4];
	if( sgs_ItemTypeExt( C, pos ) == VTC_ARRAY )
	{
		int i;
		int size = sgs_ArraySize( C, pos );
		if( size < 1 || size > 4 )
			return 0;
		for( i = 0; i < size; ++i )
		{
			if( sgs_PushNumIndex( C, pos, i ) )
				return 0;
			if( !sgs_ParseReal( C, -1, v4f + i ) )
			{
				sgs_Pop( C, 1 );
				return 0;
			}
			sgs_Pop( C, 1 );
		}
		switch( size )
		{
		case 1: v4f[1] = v4f[2] = v4f[3] = v4f[0]; break;
		case 2: v4f[3] = v4f[1]; v4f[1] = v4f[2] = v4f[0]; break;
		case 3: v4f[3] = 1.0; break;
		}
		return 1;
	}
	if( sgs_ParseColor( C, pos, tmp, 0 ) )
	{
		v4f[0] = tmp[0];
		v4f[1] = tmp[1];
		v4f[2] = tmp[2];
		v4f[3] = tmp[3];
		return 1;
	}
	return 0;
}


int sgs_InitExtMath( SGS_CTX )
{
	return xgm_module_entry_point( C );
}



#undef FN
#define FN( f ) { #f, ses_##f }

int ses_sgs_objcount( SGS_CTX )
{
	sgs_PushInt( C, sgs_Stat( C, SGS_STAT_OBJCOUNT ) );
	return 1;
}

sgs_RegFuncConst es_fconsts[] =
{
	FN( sgs_objcount ),
};

int sgs_InitExtSys( SGS_CTX )
{
	int ret;
	ret = sgs_RegFuncConsts( C, es_fconsts, ARRAY_SIZE( es_fconsts ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	return SGS_SUCCESS;
}





/*
	API
*/

extern sgs_ObjCallback tex_iface[];

int ss_parse_texture( SGS_CTX, int item, sgs_Texture** tex )
{
	if( !sgs_IsObject( C, item, tex_iface ) )
		return 0;
	if( tex )
		*tex = (sgs_Texture*) sgs_GetObjectData( C, item );
	return 1;
}

void* ss_get_iface( int which )
{
	switch( which )
	{
#ifdef SS_USED3D
	case SSI_D3D: return GD3D;
	case SSI_D3D_DEVICE: return GD3DDev;
#endif
	case SSI_TEX_IFACE: return tex_iface;
	}
	return NULL;
}

int sgs_InitAPI( SGS_CTX )
{
	int ret;
	
	sgs_RegisterType( C, "texture", tex_iface );
	
	sgs_PushPtr( C, ss_parse_texture );
	ret = sgs_StoreGlobal( C, SS_PARSE_TEXTURE_KEY );
	if( ret != SGS_SUCCESS ) return ret;
	
	sgs_PushPtr( C, ss_get_iface );
	ret = sgs_StoreGlobal( C, SS_GET_IFACE_KEY );
	if( ret != SGS_SUCCESS ) return ret;
	
#ifdef SS_USED3D
	sgs_PushInt( C, 1 );
	sgs_PushInt( C, 1 );
#else
	sgs_PushInt( C, -1 );
	sgs_PushInt( C, 0 );
#endif
	sgs_StoreGlobal( C, "sys_using_d3d" );
	sgs_StoreGlobal( C, "sys_using_d3d_signed" );
	
	return SGS_SUCCESS;
}

