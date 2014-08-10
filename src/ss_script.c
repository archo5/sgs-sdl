
#include <math.h>
#include <assert.h>

#include "ss_main.h"

#include "../sgscript/ext/sgs_prof.c"
#include "../sgscript/ext/sgs_idbg.c"
#define ARRAY_SIZE( x ) (sizeof(x)/sizeof(x[0]))


#define _WARN( err ) return sgs_Msg( C, SGS_WARNING, err );

uint32_t ss_GetFlagString( SGS_CTX, int pos, flag_string_item_t* items )
{
	char* str;
	uint32_t flags = 0;
	str = sgs_ToString( C, pos );
	if( !str )
		return 0;
	
	while( items->name )
	{
		char* p = strstr( str, items->name );
		if( p )
		{
			int len = strlen( items->name );
			if( p[ len ] == ',' || p[ len ] == 0 )
				flags |= items->value;
		}
		items++;
	}
	return flags;
}

uint32_t ss_GlobalFlagString( SGS_CTX, const char* name, flag_string_item_t* items )
{
	uint32_t flags = 0;
	if( sgs_PushGlobal( C, name ) != SGS_SUCCESS )
		return 0;
	flags = ss_GetFlagString( C, -1, items );
	sgs_Pop( C, 1 );
	return flags;
}

int ss_UnpackDict( SGS_CTX, int pos, dict_unpack_item_t* items )
{
	int ret = 0;
	
	if( sgs_ItemType( C, pos ) != SGS_VT_OBJECT )
		return ret;
	
	while( items->name )
	{
		sgs_SizeVal sz = sgs_StackSize( C );
		sgs_PushString( C, items->name );
		
		assert( items->var != NULL );
		if( sgs_PushIndexII( C, pos, -1, 0 ) || !sgs_GetStackItem( C, -1, items->var ) )
			items->var = NULL;
		else
			ret++;
		
		items++;
		sgs_SetStackSize( C, sz );
	}
	return ret;
}

void ss_UnpackFree( SGS_CTX, dict_unpack_item_t* items )
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
int ss_ParseColor( SGS_CTX, int pos, float* v4f )
{
	int32_t size = sgs_ArraySize( C, pos );
	if( size >= 0 )
	{
		int i;
		if( size < 1 || size > 4 )
			return 0;
		for( i = 0; i < size; ++i )
		{
			sgs_Real tmp;
			if( sgs_PushNumIndex( C, pos, i ) )
				return 0;
			if( !sgs_ParseReal( C, -1, &tmp ) )
			{
				sgs_Pop( C, 1 );
				return 0;
			}
			v4f[ i ] = tmp;
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
	else if( sgs_ParseColor( C, pos, v4f, 0 ) )
		return 1;
	return 0;
}


int ss_InitExtMath( SGS_CTX )
{
	return xgm_module_entry_point( C );
}

