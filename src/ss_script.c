
#include <math.h>
#include <assert.h>

#define SGS_INTERNAL

#include "ss_main.h"

#undef ARRAY_SIZE
#include "../sgscript/ext/sgs_idbg.c"
#include "../sgscript/ext/sgs_prof.c"
#undef ARRAY_SIZE
#define ARRAY_SIZE( x ) (sizeof(x)/sizeof(x[0]))


#define _WARN( err ) { sgs_Printf( C, SGS_WARNING, err ); return 0; }

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
	sgs_Variable obj, idx;
	
	if( !sgs_GetStackItem( C, pos, &obj ) || obj.type != SVT_OBJECT )
		return ret;
	
	while( items->name )
	{
		sgs_PushString( C, items->name );
		sgs_GetStackItem( C, -1, &idx );
		sgs_Acquire( C, &idx );
		sgs_Pop( C, 1 );
		
		assert( items->var != NULL );
		if( sgs_GetIndex( C, items->var, &obj, &idx ) != SGS_SUCCESS )
			items->var = NULL;
		else
			ret++;
		
		sgs_Release( C, &idx );
		items++;
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


/* extended math utilities */
/*
	A note on atan2 usage:
	I know it's 'wrong' and I don't care. This is easier.
	This is the 'tau' of 'tau vs pi', this is how the clock works, this is real life.
	Consider that.
*/

#define SUC SGS_SUCCESS
#define FN( f ) { #f, sem_##f }

/*
	2 D   V E C T O R
*/
#define V2DHDR sgs_Real* hdr = (sgs_Real*) data->data;
static void* vec2d_iface[];

static int _make_v2d( SGS_CTX, sgs_Real x, sgs_Real y ){ sgs_Real* nv = sgs_Alloc_n( sgs_Real, 2 ); nv[ 0 ] = x; nv[ 1 ] = y; sgs_PushObject( C, nv, vec2d_iface ); return SUC; }

int stdlib_tovec2d( SGS_CTX, int pos, sgs_Real* v2f, int strict )
{
	sgs_VarObj* data;
	int ty = sgs_ItemType( C, pos );
	if( !strict && ( ty == SVT_INT || ty == SVT_REAL ) )
	{
		v2f[0] = v2f[1] = sgs_GetReal( C, pos );
		return 1;
	}
	if( sgs_ItemType( C, pos ) != SVT_OBJECT )
		return 0;
	data = sgs_GetObjectData( C, pos );
	if( data->iface != vec2d_iface )
		return 0;
	{
		sgs_Real* hdr = (sgs_Real*) data->data;
		v2f[0] = hdr[0]; v2f[1] = hdr[1];
	}
	return 1;
}

static int sem_v2d_destruct( SGS_CTX, sgs_VarObj* data, int dco ){ sgs_Dealloc( data->data ); return SUC; }

static int sem_v2d_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	V2DHDR;
	if( type == SGS_CONVOP_CLONE )
	{
		return _make_v2d( C, hdr[0], hdr[1] );
	}
	else if( type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "vec2d" );
		return SUC;
	}
	else if( type == SVT_STRING )
	{
		char buf[ 48 ];
		sprintf( buf, "vec2d(%g;%g)", hdr[0], hdr[1] );
		sgs_PushString( C, buf );
		return SUC;
	}
	return SGS_ENOTSUP;
}

static int sem_v2d_getindex( SGS_CTX, sgs_VarObj* data, int prop )
{
	char* str;
	sgs_SizeVal size;
	V2DHDR;
	
	if( !sgs_ParseString( C, 0, &str, &size ) )
		return SGS_EINVAL;
	if( !strcmp( str, "x" ) ){ sgs_PushReal( C, hdr[ 0 ] ); return SUC; }
	if( !strcmp( str, "y" ) ){ sgs_PushReal( C, hdr[ 1 ] ); return SUC; }
	if( !strcmp( str, "length" ) ){ sgs_PushReal( C, sqrt( hdr[0] * hdr[0] + hdr[1] * hdr[1] ) ); return SUC; }
	if( !strcmp( str, "length_squared" ) ){ sgs_PushReal( C, hdr[0] * hdr[0] + hdr[1] * hdr[1] ); return SUC; }
	if( !strcmp( str, "normalized" ) )
	{
		sgs_Real lensq = hdr[0] * hdr[0] + hdr[1] * hdr[1];
		if( lensq )
		{
			lensq = 1.0 / sqrt( lensq );
			return _make_v2d( C, hdr[0] * lensq, hdr[1] * lensq );
		}
		return _make_v2d( C, 0, 0 );
	}
	if( !strcmp( str, "angle" ) ){ sgs_PushReal( C, atan2( hdr[0], hdr[1] ) ); return SUC; }
	if( !strcmp( str, "perp" ) ) return _make_v2d( C, -hdr[1], hdr[0] );
	if( !strcmp( str, "perp2" ) ) return _make_v2d( C, hdr[1], -hdr[0] );
	return SGS_ENOTFND;
}
static int sem_v2d_setindex( SGS_CTX, sgs_VarObj* data, int prop )
{
	char* str;
	sgs_SizeVal size;
	sgs_Real val;
	V2DHDR;
	
	if( !sgs_ParseString( C, 0, &str, &size ) )
		return SGS_EINVAL;
	if( !sgs_ParseReal( C, 1, &val ) )
		return SGS_EINVAL;
	if( !strcmp( str, "x" ) ){ hdr[ 0 ] = val; return SUC; }
	if( !strcmp( str, "y" ) ){ hdr[ 1 ] = val; return SUC; }
	return SGS_ENOTFND;
}

static int sem_v2d_expr( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_EOP_ADD || type == SGS_EOP_SUB || type == SGS_EOP_MUL
		|| type == SGS_EOP_DIV || type == SGS_EOP_MOD )
	{
		sgs_Real r[ 2 ], v1[ 2 ], v2[ 2 ];
		if( !stdlib_tovec2d( C, 0, v1, 0 ) || !stdlib_tovec2d( C, 1, v2, 0 ) )
			return SGS_EINVAL;
		
		if( ( type == SGS_EOP_DIV || type == SGS_EOP_MOD ) &&
			( v2[0] == 0 || v2[1] == 0 ) )
		{
			const char* errstr = type == SGS_EOP_DIV ?
				"vec2d operator '/' - division by zero" :
				"vec2d operator '%' - modulo by zero";
			sgs_Printf( C, SGS_ERROR, errstr );
			return SGS_EINPROC;
		}
		
		if( type == SGS_EOP_ADD )
			{ r[0] = v1[0] + v2[0]; r[1] = v1[1] + v2[1]; }
		else if( type == SGS_EOP_SUB )
			{ r[0] = v1[0] - v2[0]; r[1] = v1[1] - v2[1]; }
		else if( type == SGS_EOP_MUL )
			{ r[0] = v1[0] * v2[0]; r[1] = v1[1] * v2[1]; }
		else if( type == SGS_EOP_DIV )
			{ r[0] = v1[0] / v2[0]; r[1] = v1[1] / v2[1]; }
		else
			{ r[0] = fmod( v1[0], v2[0] ); r[1] = fmod( v1[1], v2[1] ); }
		
		return _make_v2d( C, r[0], r[1] );
	}
	else if( type == SGS_EOP_COMPARE )
	{
		sgs_Real *v1, *v2;
		if( sgs_ItemType( C, 0 ) != SVT_OBJECT || sgs_ItemType( C, 1 ) != SVT_OBJECT ||
			sgs_GetObjectData( C, 0 )->iface != vec2d_iface ||
			sgs_GetObjectData( C, 1 )->iface != vec2d_iface )
			return SGS_EINVAL;
		
		v1 = (sgs_Real*) sgs_GetObjectData( C, 0 )->data;
		v2 = (sgs_Real*) sgs_GetObjectData( C, 1 )->data;
		
		return v1[0] - v2[0] + v1[1] - v2[1];
	}
	else if( type == SGS_EOP_NEGATE )
	{
		V2DHDR;
		return _make_v2d( C, -hdr[0], -hdr[1] );
	}
	return SGS_ENOTSUP;
}

static void* vec2d_iface[] =
{
	SOP_GETINDEX, sem_v2d_getindex,
	SOP_SETINDEX, sem_v2d_setindex,
	SOP_EXPR, sem_v2d_expr,
	
	SOP_CONVERT, sem_v2d_convert,
	SOP_DESTRUCT, sem_v2d_destruct,
	
	SOP_END
};

#define V2DARGERR "vec2d() - unexpected arguments; function expects [real[, real]]"
static int sem_vec2d( SGS_CTX )
{
	sgs_Real v[ 2 ] = { 0, 0 };
	int argc = sgs_StackSize( C );
	
	if( argc > 2 ) _WARN( V2DARGERR )
	if( argc >= 1 )
	{
		if( !sgs_ParseReal( C, 0, v ) )
			_WARN( V2DARGERR )
		if( argc > 1 )
		{
			if( !sgs_ParseReal( C, 1, v + 1 ) )
				_WARN( V2DARGERR )
		}
		else
			v[ 1 ] = v[ 0 ];
	}
	
	return _make_v2d( C, v[ 0 ], v[ 1 ] ) == SUC ? 1 : 0;
}
#undef V2DARGERR

static int sem_vec2d_dot( SGS_CTX )
{
	sgs_Real v1[2], v2[2];
	
	if( !stdlib_tovec2d( C, 0, v1, 1 ) || !stdlib_tovec2d( C, 1, v2, 1 ) )
		_WARN( "vec2d_dot(): unexpected arguments; function expects vec2d, vec2d" )
	
	sgs_PushReal( C, v1[0] * v2[0] + v1[1] * v2[1] );
	return 1;
}

/*
	C O L O R
*/
int stdlib_tocolor4( SGS_CTX, int pos, sgs_Real* v4f )
{
	sgs_Variable var;
	if( sgs_GetStackItem( C, pos, &var ) && sgs_IsArray( C, &var ) )
	{
		int i;
		int size = sgs_ArraySize( C, &var );
		if( size < 1 || size > 4 )
			return 0;
		for( i = 0; i < size; ++i )
		{
			sgs_Variable item;
			if( !sgs_ArrayGet( C, &var, i, &item ) )
				return 0;
			sgs_PushVariable( C, &item );
			sgs_Release( C, &item );
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
	return 0;
}


int sem_randf( SGS_CTX )
{
	sgs_PushReal( C, (sgs_Real) rand() / (sgs_Real) RAND_MAX );
	return 1;
}

sgs_RegFuncConst em_fconsts[] =
{
	FN( vec2d ), FN( vec2d_dot ),
	FN( randf ),
};

int sgs_InitExtMath( SGS_CTX )
{
	int ret;
	ret = sgs_RegFuncConsts( C, em_fconsts, ARRAY_SIZE( em_fconsts ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	return SGS_SUCCESS;
}



#undef FN
#define FN( f ) { #f, ses_##f }

int ses_sgs_objcount( SGS_CTX )
{
	sgs_PushInt( C, sgs_Stat( C, SGS_STAT_VARCOUNT ) );
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

