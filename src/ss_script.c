
#include "ss_main.h"


sgs_Integer sgs_GlobalInt( SGS_CTX, const char* name )
{
	sgs_Integer v;
	if( sgs_GetGlobal( C, name ) != SGS_SUCCESS )
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
	char* str;
	uint32_t flags = 0;
	if( sgs_GetGlobal( C, name ) != SGS_SUCCESS )
		return 0;
	flags = sgs_GetFlagString( C, -1, items );
	sgs_Pop( C, 1 );
	return flags;
}

