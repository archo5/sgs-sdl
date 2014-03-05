
#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define SGS_INTERNAL

#include "../sgscript/src/sgs_util.h"
#undef ARRAY_SIZE

#include "ss_main.h"

#define FN( f ) { "SS_" #f, SS_##f }
#define IC( i ) { #i, i }
#define _WARN( err ) return sgs_Msg( C, SGS_WARNING, err );


SS_RenderInterface* GCurRI = NULL;
SS_Renderer* GCurRr = NULL;

void ss_MakeCurrent( SS_RenderInterface* ri, SS_Renderer* rr )
{
	SGS_CTX = ss_GetContext();
	
	if( GCurRI == ri && GCurRr == rr )
		return;
	
	if( ri && rr )
		ri->set_current( rr );
	GCurRI = ri;
	GCurRr = rr;
	
	sgs_PushBool( C, ri->flags & SS_RI_COLOR_BGRA );
	sgs_StoreGlobal( C, "sys_rctx_flip_colors" );
}

SS_TmpCtx ss_TmpMakeCurrent( SS_RenderInterface* ri, SS_Renderer* rr )
{
	SS_TmpCtx ctx = { GCurRI, GCurRr };
	ss_MakeCurrent( ri, rr );
	return ctx;
}

void ss_TmpRestoreCurrent( SS_TmpCtx* ctx )
{
	ss_MakeCurrent( ctx->riface, ctx->renderer );
}


#define SS_MATRIX_STACK_SIZE 8

typedef float mat4x4[4][4];

static mat4x4 GRWorldMatrices[ SS_MATRIX_STACK_SIZE ];
static int GRCurMatrix = 0;


static FT_Library g_ftlib;


static void _mtx_transpose( float* m )
{
	float tmp;
#define MSWAP( a, b ) tmp = m[a]; m[a] = m[b]; m[b] = tmp
	MSWAP( 1, 4 );
	MSWAP( 2, 8 );
	MSWAP( 3, 12 );
	MSWAP( 6, 9 );
	MSWAP( 7, 13 );
	MSWAP( 11, 14 );
#undef MSWAP
}

static void _mtx_identity( float* m )
{
	m[1] = m[2] = m[3] = 0.0f;
	m[4] = m[6] = m[7] = 0.0f;
	m[8] = m[9] = m[11] = 0.0f;
	m[12] = m[13] = m[14] = 0.0f;
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}


#define TEXHDR SS_Texture* T = (SS_Texture*) data->data

static int sstex_destruct( SGS_CTX, sgs_VarObj* data )
{
	TEXHDR;
	if( T->renderer )
	{
		SS_RenderInterface* RI = T->renderer->iface;
		SS_TmpCtx ctx = ss_TmpMakeCurrent( RI, T->renderer );
		RI->destroy_texture( T->renderer, T );
		T->renderer = NULL;
		GCurRI->poke_resource( GCurRr, data, 0 );
		ss_TmpRestoreCurrent( &ctx );
	}
	return SGS_SUCCESS;
}

static int sstex_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SVT_STRING )
	{
		char buf[ 48 ];
		TEXHDR;
		sprintf( buf, "Texture (%d x %d, type %d)", (int) T->width, (int) T->height, (int) T->flags );
		sgs_PushString( C, buf );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int sstex_getindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, int isprop )
{
	char* str;
	sgs_SizeVal size;
	TEXHDR;
	UNUSED( isprop );
	if( sgs_ParseStringP( C, key, &str, &size ) )
	{
		if( !strcmp( str, "width" ) ){ sgs_PushInt( C, T->width ); return SGS_SUCCESS; }
		if( !strcmp( str, "height" ) ){ sgs_PushInt( C, T->height ); return SGS_SUCCESS; }
		
		if( !strcmp( str, "is_hrepeat" ) ){ sgs_PushBool( C, sgs_HAS_FLAG( T->flags, SS_TEXTURE_HREPEAT ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "is_vrepeat" ) ){ sgs_PushBool( C, sgs_HAS_FLAG( T->flags, SS_TEXTURE_VREPEAT ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "is_nolerp" ) ){ sgs_PushBool( C, sgs_HAS_FLAG( T->flags, SS_TEXTURE_NOLERP ) ); return SGS_SUCCESS; }
		if( !strcmp( str, "is_mipmaps" ) ){ sgs_PushBool( C, sgs_HAS_FLAG( T->flags, SS_TEXTURE_MIPMAPS ) ); return SGS_SUCCESS; }
	}
	return SGS_ENOTFND;
}

static sgs_ObjInterface tex_iface[1] =
{{
	"SS_Texture",
	sstex_destruct, NULL,
	sstex_getindex, NULL,
	sstex_convert, NULL, NULL, NULL,
	NULL, NULL
}};

/*
	the "create_texture" function
	- creates a texture
	>> usage examples
	create_texture( 'blurp.png', 'hrepeat,vrepeat,nolerp,mipmaps' );
	craete_texture( some_image, 'bilerp' ); // image object
	create_texture( 'wall.png' ); // clamped & filtered texture
	>> flags
	- hrepeat - horizontal (X) repeating
	- vrepeat - vertical (Y) repeating
	- nolerp - disable bilinear interpolation
	- mipmaps - generate mipmaps for it
	>> additional info
	- returns a texture object
	- saves the object in _Gtex dict for later reference
	- supports image objects and filenames as image sources
	- filenames will be converted to images first by taking the extension, lowercasing it and calling "ss_load_image_from_file_<ext>"
		- if function doesn't exist or it simply returns null, texture creation fails
*/

static int SS_CreateTexture( SGS_CTX )
{
	uint32_t flags;
	SS_Image* ii;
	int argc = sgs_StackSize( C ), bystr = 0;
	
	SGSFN( "SS_CreateTexture" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	static flag_string_item_t flagitems[] =
	{
		{ "hrepeat", SS_TEXTURE_HREPEAT },
		{ "vrepeat", SS_TEXTURE_VREPEAT },
		{ "nolerp", SS_TEXTURE_NOLERP },
		{ "mipmaps", SS_TEXTURE_MIPMAPS },
		FSI_LAST
	};
	
	if( argc < 1 || argc > 2 )
		_WARN( "unexpected arguments; function expects 1-2 arguments: (image|string)[, string]" )
	
	flags = ss_GetFlagString( C, 1, flagitems );
	
	if( sgs_ItemType( C, 0 ) == SVT_STRING )
	{
		bystr = 1;
		
		/* check if image already loaded */
		sgs_PushItem( C, 0 ); /* NAME [FLAGS...] NAME */
		sgs_PushString( C, "|" ); /* NAME [FLAGS...] NAME "|" */
		sgs_PushInt( C, flags ); /* NAME [FLAGS...] NAME "|" INT_FLAGS */
		sgs_StringConcat( C, 3 ); /* NAME [FLAGS...] KEY */
		
		if( sgs_PushIndexPI( C, &GCurRr->textures, -1, 0 ) == SGS_SUCCESS )
		{
			/* found it! */
			return 1;
		}
		
		/* convert string to image */
		if( !ss_LoadImageHelper( C, sgs_GetStringPtr( C, 0 ), sgs_GetStringSize( C, 0 ) ) )
			return 0; /* error printed by LIH */
		
		/* NAME [FLAGS...] KEY IMAGE */
		
		/* insert return value as argument #0 */
		sgs_StoreItem( C, 0 );
		/* IMAGE [FLAGS...] KEY */
		
		/* texture key must stay at position -1 */
	}
	
	/* IMAGE [FLAGS...] [KEY](if bystr) */
	
	if( !ss_ParseImage( C, 0, &ii ) )
		_WARN( "unexpected arguments; function expects 1-2 arguments: (image|string)[, string]" )
	
	{
		SS_Texture* T = (SS_Texture*) sgs_PushObjectIPA( C, sizeof(SS_Texture), tex_iface );
		memset( T, 0, sizeof(*T) );
		
		if( !GCurRI->create_texture_argb8( GCurRr, T, ii, flags ) )
			return sgs_Msg( C, SGS_WARNING, "failed to create texture: %s", GCurRI->last_error );
		
		GCurRI->poke_resource( GCurRr, sgs_GetObjectStruct( C, -1 ), 1 );
	}
	
	/* IMAGE [FLAGS...] [KEY](if bystr) TEXTURE */
	
	/* texture key at position -2 */
	if( bystr )
	{
		/* save texture in cache */
		sgs_SetIndexPII( C, &GCurRr->textures, -2, -1, 0 );
	}
	
	return 1;
}


int ss_ParseTexture( SGS_CTX, int item, SS_Texture** T )
{
	if( !sgs_IsObject( C, item, tex_iface ) )
		return 0;
	if( T )
		*T = (SS_Texture*) sgs_GetObjectData( C, item );
	return 1;
}

int ss_ApplyTexture( sgs_Variable* texvar, float* tox, float* toy )
{
	SS_Texture* T = NULL;
	
	sgs_BreakIf( !GCurRI || !GCurRr );
	
	if( tox ) *tox = 0;
	if( toy ) *toy = 0;
	if( texvar && texvar->type != SGS_VT_NULL )
	{
		if( texvar->type != SGS_VT_OBJECT || texvar->data.O->iface != tex_iface )
			return 0;
		T = (SS_Texture*) texvar->data.O->data;
		if( T->renderer != GCurRr )
			return 0;
		if( GCurRI->flags & SS_RI_HALFPIXELOFFSET && !( T->flags & SS_TEXTURE_NOLERP ) )
		{
			if( tox ) *tox = 0.5f / T->width;
			if( toy ) *toy = 0.5f / T->height;
		}
	}
	return GCurRI->apply_texture( GCurRr, T );
}


/*
	the "draw" function
	- draws
	>> usage examples
	draw({ shape = 'box', position = create_pos2d( 10, 10 ) }); // draws a white 1x1 box at position 10,10
	>> available parameters (by category):
	- geometry: type (enum), shape (enum), vertices (array), verts3d (array), vcolors (array), vtexcoords (array)
	- instances: position, positions, angle, angles, transform, transforms, color, colors
	- misc.: texture
	>> defaults (by category):
	- geometry: 1x1 box shape
	- instancing: !must have at least one position item known in advance
	- misc.: the "white" 1x1 texture (only preserves color data) or disabled texturing
	>> order of operations:
	- validate
	- set texture
	- for each instance
		- set instance data
		- draw call
	>> evaluation of passed arguments
	GEOMETRY:
	- first look for verts3d, then vertices; if found - check for type (if not found, ERROR), vcolors, colors, color and vtexcoords too
	- if none found, check for shape; if found - check for colors, then color
	- if none found, ERROR
	INSTANCE-TRANSFORM:
	- first check for transforms, then transform; if found - EXIT EARLY
	- if none found, check for positions, then position; if found - check for angles, then angle, then EXIT EARLY
	MISC:
	- check for texture
	>> data objects
	- texture is an OpenGL texture + some metadata // TODO
	>> intermediate storages
	- data loading functions will return additional values to specify if a buffer was created in the call
	
	>> CHANGES
	- renamed "shape" to "preset"
*/
#define BUFIDX_NONE -1
typedef struct floatbuf_s
{
	float* data_static;
	ptrdiff_t data_off;
	int32_t size;
	int32_t cnt;
}
floatbuf;
static float* floatbuf_get_ptr( floatbuf* buf )
{
	return buf->data_off != BUFIDX_NONE ? ((float*)(ss_GetBufferPtr() + buf->data_off)) : buf->data_static;
}
#define NFB { NULL, BUFIDX_NONE, 0, 0 }
/*
	the floating point buffer parser
	supports:
	- array of float-ish* => size = numcomp, ncp = numcomp, cnt = 0
	- array of array of float-ish => size => array-size * numcomp, ncp = numcomp, cnt = array-size
	- array of vec2d => ^^
	function returns NULL on success, error on failure
	///
	(*int, real, numstring -- use strings at your own risk, performance can easily suck)
	///
	parameters:
	- C - the script engine context
	- var - the entry point variable
	- out - the output floatbuf
	- numcomp - max. number of components to read
	- defcomp - a numcomp-sized array that contains the default values for shorter-than-numcomp components
	- arr - whether to expect an array of multivalue items (true) or an array of float-ish items (false)
*/
	
static const char* _parse_floatvec( SGS_CTX, int stkitem, float* out, int numcomp )
{
	int pnp = -1;
	if( sgs_ParseVec2( C, stkitem, out, 0 ) ) pnp = 2;
	else if( sgs_ParseVec3( C, stkitem, out, 0 ) ) pnp = 3;
	else if( sgs_ParseVec4( C, stkitem, out, 0 ) ) pnp = 4;
	else if( sgs_ParseColor( C, stkitem, out, 0 ) ) pnp = 4;
	else if( sgs_ParseMat4( C, stkitem, out ) ) pnp = 16;
	else if( sgs_ArraySize( C, stkitem ) >= 0 )
	{
		int32_t i, asz = sgs_ArraySize( C, stkitem );
		if( asz > numcomp )
			asz = numcomp;
		
		for( i = 0; i < asz; ++i )
		{
			sgs_Real real;
			if( sgs_PushNumIndex( C, stkitem, i ) )
			{
				return "could not read from array";
			}
			
			if( !sgs_ParseReal( C, -1, &real ) )
			{
				sgs_Pop( C, 1 );
				return "non-number value found";
			}
			sgs_Pop( C, 1 );
			
			out[ i ] = real;
		}
		
		pnp = asz;
	}
	
	if( pnp >= 0 )
		return NULL;
	
	return "item was not a vector or array of floats";
}

static const char* _parse_floatbuf( SGS_CTX, sgs_Variable* var, floatbuf* out, int numcomp, float* defcomp, int arr )
{
	float* off;
	int32_t i, asz;
	
	sgs_SizeVal ssz = sgs_StackSize( C );
	sgs_PushVariable( C, var );
	if( !arr )
	{
		const char* res;
		out->cnt = 1;
		out->size = numcomp;
		out->data_off = ss_RequestMemory_idx( out->size * sizeof(float) );
		out->data_static = NULL;
		memcpy( ss_GetBufferPtr() + out->data_off, defcomp, numcomp * sizeof(float) );
		res = _parse_floatvec( C, -1, (float*)( ss_GetBufferPtr() + out->data_off ), numcomp );
		sgs_Pop( C, 1 );
		return res;
	}
	
	asz = sgs_ArraySize( C, -1 );
	if( asz < 0 )
	{
		sgs_Pop( C, 1 );
		return "array expected";
	}
	
	out->cnt = asz;
	out->size = asz * numcomp;
	out->data_off = ss_RequestMemory_idx( out->size * sizeof(float) );
	out->data_static = NULL;
	
	off = (float*)( ss_GetBufferPtr() + out->data_off );
	for( i = 0; i < asz; ++i )
	{
		const char* subres;
		if( sgs_PushNumIndex( C, -1, i ) || sgs_ItemType( C, -1 ) != SVT_OBJECT )
		{
			sgs_Pop( C, sgs_StackSize( C ) - ssz );
			return "element was not an object";
		}
		
		memcpy( off, defcomp, numcomp * sizeof(float) );
		
		subres = _parse_floatvec( C, -1, off, numcomp );
		sgs_Pop( C, 1 );
		
		if( subres )
		{
			sgs_Pop( C, 1 );
			return subres;
		}
		
		off += numcomp;
	}
	
	sgs_Pop( C, 1 );
	return NULL;
}

static int _draw_load_geom( SGS_CTX, int* outmode, floatbuf* vert, floatbuf* vcol, floatbuf* vtex )
{
	sgs_Variable preset, mode, vertices, vcolors, vtexcoords;
	dict_unpack_item_t gi[] =
	{
		{ "preset", &preset }, { "mode", &mode },
		{ "vertices", &vertices },
		{ "vcolors", &vcolors },
		{ "vtexcoords", &vtexcoords },
		DUI_LAST,
	};
	
	if( !ss_UnpackDict( C, 0, gi ) )
		_WARN( "no geometry data found" )
	
	if( gi[0].var && ( gi[1].var || gi[2].var ) )
	{
		ss_UnpackFree( C, gi );
		_WARN( "'preset' doesn't work together with 'mode' or 'vertices'" )
	}
	
	if( gi[0].var )
	{
		static float boxbuf[] =
		{
			-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
			0, 0, 1, 0, 1, 1, 0, 1,
		};
		
		int ret = 0;
		char* str;
		sgs_SizeVal size;
		sgs_PushVariable( C, gi[0].var );
		if( !sgs_ParseString( C, -1, &str, &size ) )
		{
			sgs_Pop( C, 1 );
			ss_UnpackFree( C, gi );
			_WARN( "'preset' must be a string" )
		}
		sgs_Pop( C, 1 );
		
		if( !strcmp( str, "box" ) )
		{
			*outmode = SS_PT_QUADS;
			vert->cnt = 4;
			vert->size = 8;
			vert->data_static = boxbuf;
			vert->data_off = BUFIDX_NONE;
			vtex->cnt = 4;
			vtex->size = 8;
			vtex->data_static = boxbuf + 8;
			vtex->data_off = BUFIDX_NONE;
			ret = 1;
		}
		if( !strcmp( str, "tile" ) )
		{
			*outmode = SS_PT_QUADS;
			vert->cnt = 4;
			vert->size = 8;
			vert->data_static = boxbuf + 8;
			vert->data_off = BUFIDX_NONE;
			vtex->cnt = 4;
			vtex->size = 8;
			vtex->data_static = boxbuf + 8;
			vtex->data_off = BUFIDX_NONE;
			ret = 1;
		}
		
		ss_UnpackFree( C, gi );
		if( !ret )
			_WARN( "preset not found" )
		return ret;
	}
	else if( gi[2].var )
	{
		sgs_Integer imode;
		float defcomp[] = { 0, 0, 0, 0, 1, 1, 1, 1, 0.5f, 0.5f, 0.5f, 0.5f };
		floatbuf pdata = NFB, cdata = NFB, tdata = NFB;
		const char* res = _parse_floatbuf( C, gi[2].var, &pdata, 2, defcomp, 1 );
		if( res )
		{
			sgs_Msg( C, SGS_WARNING, "failed to load vertices - %s", res );
			goto cleanup;
		}
		
		if( !gi[1].var )
		{
			sgs_Msg( C, SGS_WARNING, "'mode' not found" );
			goto cleanup;
		}
		
		sgs_PushVariable( C, gi[1].var );
		if( !sgs_ParseInt( C, -1, &imode ) )
		{
			sgs_Pop( C, 1 );
			goto cleanup;
		}
		sgs_Pop( C, 1 );
		*outmode = imode;
		
		if( gi[3].var )
		{
			res = _parse_floatbuf( C, gi[3].var, &cdata, 4, defcomp+4, 1 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load vertex colors - %s", res );
				goto cleanup;
			}
		}
		
		if( gi[4].var )
		{
			res = _parse_floatbuf( C, gi[4].var, &tdata, 2, defcomp+8, 1 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load vertex texcoords - %s", res );
				goto cleanup;
			}
		}
		
		ss_UnpackFree( C, gi );
		if( pdata.data_off != BUFIDX_NONE ) *vert = pdata;
		if( cdata.data_off != BUFIDX_NONE ) *vcol = cdata;
		if( tdata.data_off != BUFIDX_NONE ) *vtex = tdata;
		return 1;
		
cleanup:
		ss_UnpackFree( C, gi );
		return 0;
	}
	
	ss_UnpackFree( C, gi );
	_WARN( "no geometry data found" )
}

static int _draw_load_inst( SGS_CTX, floatbuf* xform, floatbuf* icol )
{
	sgs_Variable transform, transforms, position, positions,
		angle, angles, scale, scales, color, colors;
	dict_unpack_item_t tfi[] =
	{
		{ "transform", &transform }, { "transforms", &transforms },
		{ "position", &position }, { "positions", &positions },
		{ "angle", &angle }, { "angles", &angles },
		{ "scale", &scale }, { "scales", &scales },
		{ "color", &color }, { "colors", &colors },
		DUI_LAST,
	};
	
	if( !ss_UnpackDict( C, 0, tfi ) )
		_WARN( "no instancing data found" )
	
	if( tfi[1].var ) /* found 'transforms', array of matrices */
	{
		ss_UnpackFree( C, tfi );
		_WARN( "MATRICES ARE NOT YET IMPLEMENTED" )
	}
	
	else if( tfi[0].var ) /* found 'transform', one matrix */
	{
		ss_UnpackFree( C, tfi );
		_WARN( "MATRICES ARE NOT YET IMPLEMENTED" )
	}
	
	else
	{
		float *pdata, *adata, *sdata, *xdata;
		int ret = 1;
		int32_t i;
		float defcomp[] = { 0, 0, 0, 0, 1, 1, 1, 1 };
		float tmpfloats[ 5 ];
		floatbuf posdata = NFB, angdata = NFB, scaledata = NFB;
		posdata.data_static = tmpfloats;
		angdata.data_static = tmpfloats + 2;
		scaledata.data_static = tmpfloats + 3;
		if( tfi[3].var ) /* found 'positions', array of vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[3].var, &posdata, 2, defcomp, 1 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load positions - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[2].var ) /* found 'position', one vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[2].var, &posdata, 2, defcomp, 0 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load position - %s", res );
				goto cleanup;
			}
		}
		else
		{
			sgs_Msg( C, SGS_WARNING, "no instance position data found" );
		}
		
		if( tfi[5].var ) /* found 'angles', array of real */
		{
			const char* res = _parse_floatbuf( C, tfi[5].var, &angdata, 1, defcomp, 1 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load angles - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[4].var ) /* found 'angle', one real */
		{
			const char* res = _parse_floatbuf( C, tfi[4].var, &angdata, 1, defcomp, 0 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load angle - %s", res );
				goto cleanup;
			}
		}
		
		if( tfi[7].var ) /* found 'scales', array of vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[7].var, &scaledata, 2, defcomp+4, 1 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load scales - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[6].var ) /* found 'scale', one vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[6].var, &scaledata, 2, defcomp+4, 0 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load scale - %s", res );
				goto cleanup;
			}
		}
		
		/* mix-and-match */
		xform->data_static = NULL;
		xform->data_off = ss_RequestMemory_idx( sizeof(float) * 16 * posdata.cnt );
		xform->size = 16 * posdata.cnt;
		xform->cnt = posdata.cnt;
		
		pdata = floatbuf_get_ptr( &posdata );
		adata = floatbuf_get_ptr( &angdata );
		sdata = floatbuf_get_ptr( &scaledata );
		xdata = floatbuf_get_ptr( xform );
		
		for( i = 0; i < posdata.cnt; ++i )
		{
			float* mtx = xdata + i * 16;
			float posx = pdata[ i * 2 ];
			float posy = pdata[ i * 2 + 1 ];
			float angle = 0;
			float sclx = 1;
			float scly = 1;
			if( angdata.size )
				angle = adata[ i % angdata.cnt ];
			if( scaledata.size )
			{
				int32_t off = i % scaledata.cnt;
				sclx = sdata[ off * 2 ];
				scly = sdata[ off * 2 + 1 ];
			}
			
			/* generate matrix from tf2d
				- clockwise rotation
			*/
			{
				float ca = cosf( angle ), sa = sinf( angle );
				
				/*
					cos * sx, -sin * sx, 0, posx
					sin * sy, cos * sy,  0, posy
					0,        0,         1, 0
					0,        0,         0, 1
				*/
				mtx[ 0 ] = ca * sclx; mtx[ 1 ] = -sa * scly; mtx[ 3 ] = posx;
				mtx[ 4 ] = sa * sclx; mtx[ 5 ] = ca * scly; mtx[ 7 ] = posy;
				mtx[ 10 ] = mtx[ 15 ] = 1;
				mtx[ 2 ] = mtx[ 6 ] = mtx[ 8 ] = mtx[ 9 ] =
					mtx[ 11 ] = mtx[ 12 ] = mtx[ 13 ] = mtx[ 14 ] = 0;
				
				_mtx_transpose( mtx );
			}
		}
		
end:
		if( !ret )
		{
			ss_UnpackFree( C, tfi );
			return 0;
		}
		goto colors;
		
cleanup:
		ret = 0;
		goto end;
	}
	
colors:
	{
		float defcomp[] = { 1, 1, 1, 1 };
		if( tfi[9].var ) /* found 'colors', array of real4 */
		{
			const char* res = _parse_floatbuf( C, tfi[9].var, icol, 4, defcomp, 1 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load colors - %s", res );
				ss_UnpackFree( C, tfi );
				return 0;
			}
		}
		else if( tfi[8].var ) /* found 'colors', array of real4 */
		{
			const char* res = _parse_floatbuf( C, tfi[8].var, icol, 4, defcomp, 0 );
			if( res )
			{
				sgs_Msg( C, SGS_WARNING, "failed to load color - %s", res );
				ss_UnpackFree( C, tfi );
				return 0;
			}
		}
	}
	
	ss_UnpackFree( C, tfi );
	return 1;
}

static uint32_t col4f_pack_native( float* col )
{
#define MAX( a, b ) ((a)>(b)?(a):(b))
#define MIN( a, b ) ((a)<(b)?(a):(b))
	float r = col[0], g = col[1], b = col[2], a = col[3];
	uint32_t ir = r * 255, ig = g * 255, ib = b * 255, ia = a * 255;
	ir = MAX( 0, MIN( 255, ir ) ); ig = MAX( 0, MIN( 255, ig ) );
	ib = MAX( 0, MIN( 255, ib ) ); ia = MAX( 0, MIN( 255, ia ) );
	if( GCurRI->flags & SS_RI_COLOR_BGRA )
	{
		uint32_t tmp = ir;
		ir = ib;
		ib = tmp;
	}
	return ir | (ig<<8) | (ib<<16) | (ia<<24);
#undef MIN
#undef MAX
}

static int SS_Draw( SGS_CTX )
{
	char* Bptr;
	sgs_SizeVal Bsize;
	SS_BasicVertex tmp = { { 0, 0, 0 }, 0xffffffff, { 0, 0 }, {0,0} };
	
	float *tf, *tfend, *cc, *ccend, *vp, *vpstart, *vpend, *vt, *vtstart, *vtend, *vc, *vcstart, *vcend, tox = 0, toy = 0;
	int mode = SS_PT_TRIANGLES, ret = 1;
	
	floatbuf vert = NFB, vcol = NFB, vtex = NFB, xform = NFB, icol = NFB;
	sgs_Variable texture;
	dict_unpack_item_t mi[] =
	{
		{ "texture", &texture },
		DUI_LAST,
	};
	
	SGSFN( "SS_Draw" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	ss_ResetBuffer();
	
	if( sgs_StackSize( C ) != 1 ||
		sgs_ItemType( C, 0 ) != SVT_OBJECT )
		_WARN( "expected one dictionary argument" )
	
	ss_UnpackDict( C, 0, mi );
	
	if( !_draw_load_geom( C, &mode, &vert, &vcol, &vtex ) )
		goto cleanup;
	if( !_draw_load_inst( C, &xform, &icol ) )
		goto cleanup;
	
	if( !ss_ApplyTexture( mi[0].var, &tox, &toy ) )
		sgs_Msg( C, SGS_WARNING, "could not use texture" );
	
	Bsize = vert.size / 2 * sizeof(tmp);
	Bptr = (char*) ss_RequestMemory( Bsize );
	
	cc = floatbuf_get_ptr( &icol );
	ccend = cc + icol.size;
	tf = floatbuf_get_ptr( &xform );
	tfend = tf + xform.size;
	vpstart = floatbuf_get_ptr( &vert );
	vpend = vpstart + vert.size;
	vtstart = floatbuf_get_ptr( &vtex );
	vtend = vtstart + vtex.size;
	vcstart = floatbuf_get_ptr( &vcol );
	vcend = vcstart + vcol.size;
	for( ; tf < tfend; tf += 16 )
	{
		char* Biter = Bptr;
		
		GCurRI->set_matrix( GCurRr, SS_RMAT_WORLD, tf );
		
		if( cc < ccend )
		{
			/* TODO: color multiplication */
			tmp.col = col4f_pack_native( cc );
			cc += 4;
		}
		
		vt = vtstart;
		vc = vcstart;
		for( vp = vpstart; vp < vpend; vp += 2 )
		{
			if( vt < vtend )
			{
				tmp.tex[0] = vt[0] + tox;
				tmp.tex[1] = vt[1] + toy;
				vt += 2;
			}
			if( vc < vcend )
			{
				tmp.col = col4f_pack_native( vc );
				vc += 4;
			}
			tmp.pos[0] = vp[0];
			tmp.pos[1] = vp[1];
			
			memcpy( Biter, &tmp, sizeof(tmp) );
			Biter += sizeof(tmp);
		}
		
		GCurRI->draw_basic_vertices( GCurRr, Bptr, Bsize / sizeof(SS_BasicVertex), mode );
	}
	
	GCurRI->set_matrix( GCurRr, SS_RMAT_WORLD, (float*) GRWorldMatrices[ GRCurMatrix ] );
	
end:
	ss_UnpackFree( C, mi );
	
	sgs_PushBool( C, ret );
	return 1;

cleanup:
	ret = 0;
	goto end;
}



#define VFMT_HDR SS_VertexFormat* F = (SS_VertexFormat*) data->data;

static int ss_vertex_format_destruct( SGS_CTX, sgs_VarObj* data )
{
	VFMT_HDR;
	if( F->renderer )
	{
		SS_RenderInterface* RI = F->renderer->iface;
		SS_TmpCtx ctx = ss_TmpMakeCurrent( RI, F->renderer );
		RI->free_vertex_format( F->renderer, F );
		F->renderer = NULL;
		GCurRI->poke_resource( GCurRr, data, 0 );
		ss_TmpRestoreCurrent( &ctx );
	}
	return SGS_SUCCESS;
}

static int ss_vertex_format_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	VFMT_HDR;
	if( type == SVT_STRING )
	{
		sgs_PushString( C, F->renderer ? "SS_VertexFormat" : "SS_VertexFormat (unloaded)" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static sgs_ObjInterface vertex_format_iface[1] =
{{
	"SS_VertexFormat",
	ss_vertex_format_destruct, NULL,
	NULL, NULL,
	ss_vertex_format_convert, NULL, NULL, NULL,
	NULL, NULL
}};

static int SS_MakeVertexFormat( SGS_CTX )
{
	char *fmt;
	sgs_SizeVal fmtsize;
	
	SGSFN( "SS_MakeVertexFormat" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( sgs_StackSize( C ) != 1 ||
		!sgs_ParseString( C, 0, &fmt, &fmtsize ) )
		_WARN( "unexpected arguments; "
			"function expects 1 argument: string" )
	
	{
		SS_VertexFormat* ef;
		SS_VertexFormat F = {0};
		char* fmtend = fmt + fmtsize;
		int order = 0;
		
		int aligned = fmt < fmtend && *fmt == '|';
		if( aligned )
			fmt++;
		
		while( fmt < fmtend - 2 )
		{
			int isz = 0;
			uint16_t* dst;
			
			int ch = fmt[0], type = fmt[1], cnt = fmt[2];
			if( ch != 'p' && ch != 't' && ch != 'c' && ch != 'n' )
				_WARN( "wrong channel specifier (not p/t/c/n)" )
			if( type != 'f'  && type != 'b' )
				_WARN( "wrong type specifier (not f/b)" )
			if( cnt != '1' && cnt != '2' && cnt != '3' && cnt != '4' )
				_WARN( "wrong count specifier (not 1/2/3/4)" )
			
			if( ch == 'p' ) dst = F.P;
			else if( ch == 't' ) dst = F.T;
			else if( ch == 'c' ) dst = F.C;
			else if( ch == 'n' ) dst = F.N;
			else dst = NULL;
			
			if( dst[0] )
				_WARN( "a channel cannot appear twice in a format" )
			
			dst[0] = 1;
			dst[1] = F.size;
			if( type == 'f' ){ isz = 4; dst[2] = SS_RSET_FLOAT; }
			else if( type == 'b' ){ isz = 1; dst[2] = SS_RSET_BYTE; }
			
			if( cnt == '1' ) dst[3] = 1;
			else if( cnt == '2' ) dst[3] = 2;
			else if( cnt == '3' ) dst[3] = 3;
			else if( cnt == '4' ) dst[3] = 4;
			
			if( ch == 'n' && cnt != '3' )
				_WARN( "normals must have 3 components" )
			if( ch == 'c' && type == 'b' && cnt != '4' )
				_WARN( "colors with byte components must have exactly 4 bytes" )
			
			F.size += dst[4] = isz * dst[3];
			dst[5] = ++order;
			
			fmt += 3;
		}
		
		if( !F.size )
			_WARN( "empty vertex format" )
		
		if( aligned )
			F.size = ( ( F.size - 1 ) / 32 + 1 ) * 32;
		
		ef = (SS_VertexFormat*) sgs_PushObjectIPA( C, sizeof(F), vertex_format_iface );
		memcpy( ef, &F, sizeof(F) );
		ef->renderer = GCurRr;
		if( GCurRI->init_vertex_format( GCurRr, ef ) )
		{
			GCurRI->poke_resource( GCurRr, sgs_GetObjectStruct( C, -1 ), 1 );
			return 1;
		}
		return 0;
	}
}

/*
	- texture
	- format
	- data
*/
static int SS_DrawPacked( SGS_CTX )
{
	sgs_Variable texvar;
	sgs_Integer start, count, type;
	SS_VertexFormat* F;
	char *data, *idcs = NULL;
	sgs_SizeVal datasize, idcsize = 0;
	int ssz = sgs_StackSize( C );
	
	SGSFN( "SS_DrawPacked" );
	
	if( !( ssz == 6 || ssz == 7 ) ||
		!( sgs_ItemType( C, 0 ) == SVT_NULL || sgs_IsObject( C, 0, tex_iface ) ) ||
		!sgs_IsObject( C, 1, vertex_format_iface ) ||
		!sgs_ParseString( C, 2, &data, &datasize ) ||
		!sgs_ParseInt( C, 3, &start ) ||
		!sgs_ParseInt( C, 4, &count ) ||
		!sgs_ParseInt( C, 5, &type ) ||
		( ssz >=7 && !sgs_ParseString( C, 6, &idcs, &idcsize ) )
		)
		_WARN( "unexpected arguments; function expects 6-7 arguments: "
			"texture|null, format, vertex_data, int, int, int[, index_data]" )
	
	F = (SS_VertexFormat*) sgs_GetObjectData( C, 1 );
	
	if( idcs )
	{
		if( 2 * (start+count) > idcsize )
			_WARN( "not enough data to draw with given start/count values" )
	}
	else
	{
		if( F->size * (start+count) > datasize )
			_WARN( "not enough data to draw with given start/count values" )
	}
	
	sgs_PeekStackItem( C, 0, &texvar );
	if( !ss_ApplyTexture( &texvar, NULL, NULL ) )
		sgs_Msg( C, SGS_WARNING, "could not use texture" );
	
	if( F->renderer != GCurRr )
		_WARN( "vertex format was created with another renderer" );
	
	GCurRI->draw_ext( GCurRr, F, data, datasize, idcs, idcsize, 0, start, count, type );
	
	return 0;
}



/*
	-------------------
	RENDERING SYSTEM v2
	-------------------
	
	- renderbuffer
*/

typedef
struct _ss_renderbuf
{
	MemBuf B;
}
ss_renderbuf;

static sgs_ObjInterface renderbuf_iface[1];


#define RB_IHDR( funcname ) ss_renderbuf* rb; \
	if( !SGS_PARSE_METHOD( C, renderbuf_iface, rb, SS_RenderBuffer, funcname ) ) return 0;

/* .begin() */
static int ss_renderbuf_begin( SGS_CTX )
{
	RB_IHDR( begin );
	
	membuf_resize( &rb->B, C, 0 );
	
	SGS_RETURN_THIS( C );
}

/* .reserve( int bytes ) */
static int ss_renderbuf_reserve( SGS_CTX )
{
	sgs_SizeVal numbytes;
	
	RB_IHDR( reserve );
	if( !sgs_LoadArgs( C, "l", &numbytes ) )
		return 0;
	
	membuf_reserve( &rb->B, C, numbytes );
	
	SGS_RETURN_THIS( C );
}

/* .f( real{1,64} ) - floats */
static int ss_renderbuf_f( SGS_CTX )
{
	int argc, i;
	float f[64];
	
	RB_IHDR( f );
	argc = sgs_StackSize( C );
	if( argc > 0 )
	{
		if( argc > 64 )
			argc = 64;
		for( i = 0; i < argc; ++i )
			f[ i ] = sgs_ToReal( C, i );
		
		membuf_appbuf( &rb->B, C, f, sizeof(*f)*argc );
	}
	
	SGS_RETURN_THIS( C );
}

/* .b( int{1,64} ) - bytes */
static int ss_renderbuf_b( SGS_CTX )
{
	int argc, i;
	uint8_t b[64];
	
	RB_IHDR( b );
	argc = sgs_StackSize( C );
	if( argc > 0 )
	{
		if( argc > 64 )
			argc = 64;
		for( i = 0; i < argc; ++i )
			b[ i ] = (uint8_t) sgs_ToInt( C, i );
		
		membuf_appbuf( &rb->B, C, b, sizeof(*b)*argc );
	}
	
	SGS_RETURN_THIS( C );
}

/* .dw( int{1,64} ) - DoubleWord (4 bytes) */
static int ss_renderbuf_dw( SGS_CTX )
{
	int argc, i;
	uint32_t dw[64];
	
	RB_IHDR( dw );
	argc = sgs_StackSize( C );
	if( argc > 0 )
	{
		if( argc > 64 )
			argc = 64;
		for( i = 0; i < argc; ++i )
			dw[ i ] = (uint32_t) sgs_ToInt( C, i );
		
		membuf_appbuf( &rb->B, C, dw, sizeof(*dw)*argc );
	}
	
	SGS_RETURN_THIS( C );
}

/* .cf2b( real{1,64} ) - clamped float to byte */
static int ss_renderbuf_cf2b( SGS_CTX )
{
	int argc, i;
	uint8_t b[64];
	
	RB_IHDR( cf2b );
	argc = sgs_StackSize( C );
	if( argc > 0 )
	{
		if( argc > 64 )
			argc = 64;
		for( i = 0; i < argc; ++i )
		{
			float f = sgs_ToReal( C, i );
			if( f < 0 ) f = 0;
			if( f > 1 ) f = 1;
			b[ i ] = f * 255;
		}
		
		membuf_appbuf( &rb->B, C, b, sizeof(*b)*argc );
	}
	
	SGS_RETURN_THIS( C );
}

/* .pad( int ) - padding */
static int ss_renderbuf_pad( SGS_CTX )
{
	sgs_SizeVal numbytes;
	
	RB_IHDR( pad );
	if( !sgs_LoadArgs( C, "l", &numbytes ) )
		return 0;
	
	if( rb->B.size + numbytes < 0 )
		return sgs_Msg( C, SGS_WARNING, "padding so big that it's negative (overflow)" );
	
	membuf_resize( &rb->B, C, rb->B.size + numbytes );
	
	SGS_RETURN_THIS( C );
}

/* .draw( texture|null, vertex_format, int start, int count, int type ) */
static int ss_renderbuf_draw( SGS_CTX )
{
	sgs_Variable texvar;
	SS_VertexFormat* F = NULL;
	sgs_SizeVal start, count, type;
	char* data;
	
	RB_IHDR( draw );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( !sgs_LoadArgs( C, ">olll", vertex_format_iface, &F, &start, &count, &type ) )
		return 0;
	if( sgs_ItemType( C, 0 ) != SVT_NULL )
	{
		if( !sgs_IsObject( C, 0, tex_iface ) )
			return sgs_ArgErrorExt( C, 0, 0, "texture or null", "" );
	}
	sgs_PeekStackItem( C, 0, &texvar );
	data = rb->B.ptr;
	
	if( F->size * (start+count) > rb->B.size )
		_WARN( "not enough data to draw with given start/count values" )
	
	if( !ss_ApplyTexture( &texvar, NULL, NULL ) )
		return sgs_Msg( C, SGS_WARNING, "could not use texture" );
	
	if( F->renderer != GCurRr )
		_WARN( "vertex format was created with another renderer" );
	
	GCurRI->draw_ext( GCurRr, F, data, rb->B.size, NULL, 0, 0, start, count, type );
	
	SGS_RETURN_THIS( C );
}


#define RBHDR ss_renderbuf* rb = (ss_renderbuf*) data->data

static int ss_renderbuf_destruct( SGS_CTX, sgs_VarObj* data )
{
	RBHDR;
	membuf_destroy( &rb->B, C );
	return SGS_SUCCESS;
}

static int ss_renderbuf_getindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, int isprop )
{
	char* str;
	UNUSED( isprop );
	if( sgs_ParseStringP( C, key, &str, NULL ) )
	{
		if( !strcmp( str, "begin" ) ){ sgs_PushCFunction( C, ss_renderbuf_begin ); return SGS_SUCCESS; }
		if( !strcmp( str, "reserve" ) ){ sgs_PushCFunction( C, ss_renderbuf_reserve ); return SGS_SUCCESS; }
		if( !strcmp( str, "f" ) ){ sgs_PushCFunction( C, ss_renderbuf_f ); return SGS_SUCCESS; }
		if( !strcmp( str, "b" ) ){ sgs_PushCFunction( C, ss_renderbuf_b ); return SGS_SUCCESS; }
		if( !strcmp( str, "dw" ) ){ sgs_PushCFunction( C, ss_renderbuf_dw ); return SGS_SUCCESS; }
		if( !strcmp( str, "cf2b" ) ){ sgs_PushCFunction( C, ss_renderbuf_cf2b ); return SGS_SUCCESS; }
		if( !strcmp( str, "pad" ) ){ sgs_PushCFunction( C, ss_renderbuf_pad ); return SGS_SUCCESS; }
		if( !strcmp( str, "draw" ) ){ sgs_PushCFunction( C, ss_renderbuf_draw ); return SGS_SUCCESS; }
		return SGS_ENOTFND;
	}
	return SGS_EINVAL;
}

static sgs_ObjInterface renderbuf_iface[1] =
{{
	"SS_RenderBuffer",
	ss_renderbuf_destruct, NULL,
	ss_renderbuf_getindex, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL
}};

static int SS_CreateRenderBuffer( SGS_CTX )
{
	ss_renderbuf* rb;
	SGSFN( "SS_CreateRenderBuffer" );
	rb = (ss_renderbuf*) sgs_PushObjectIPA( C, sizeof(ss_renderbuf), renderbuf_iface );
	rb->B = membuf_create();
	return 1;
}




/*	-------------------  */


static inline void Matrix4x4MultiplyBy4x4( float src1[4][4], float src2[4][4], float dest[4][4] )
{
	dest[0][0] = src1[0][0] * src2[0][0] + src1[0][1] * src2[1][0] + src1[0][2] * src2[2][0] + src1[0][3] * src2[3][0]; 
	dest[0][1] = src1[0][0] * src2[0][1] + src1[0][1] * src2[1][1] + src1[0][2] * src2[2][1] + src1[0][3] * src2[3][1]; 
	dest[0][2] = src1[0][0] * src2[0][2] + src1[0][1] * src2[1][2] + src1[0][2] * src2[2][2] + src1[0][3] * src2[3][2]; 
	dest[0][3] = src1[0][0] * src2[0][3] + src1[0][1] * src2[1][3] + src1[0][2] * src2[2][3] + src1[0][3] * src2[3][3]; 
	dest[1][0] = src1[1][0] * src2[0][0] + src1[1][1] * src2[1][0] + src1[1][2] * src2[2][0] + src1[1][3] * src2[3][0]; 
	dest[1][1] = src1[1][0] * src2[0][1] + src1[1][1] * src2[1][1] + src1[1][2] * src2[2][1] + src1[1][3] * src2[3][1]; 
	dest[1][2] = src1[1][0] * src2[0][2] + src1[1][1] * src2[1][2] + src1[1][2] * src2[2][2] + src1[1][3] * src2[3][2]; 
	dest[1][3] = src1[1][0] * src2[0][3] + src1[1][1] * src2[1][3] + src1[1][2] * src2[2][3] + src1[1][3] * src2[3][3]; 
	dest[2][0] = src1[2][0] * src2[0][0] + src1[2][1] * src2[1][0] + src1[2][2] * src2[2][0] + src1[2][3] * src2[3][0]; 
	dest[2][1] = src1[2][0] * src2[0][1] + src1[2][1] * src2[1][1] + src1[2][2] * src2[2][1] + src1[2][3] * src2[3][1]; 
	dest[2][2] = src1[2][0] * src2[0][2] + src1[2][1] * src2[1][2] + src1[2][2] * src2[2][2] + src1[2][3] * src2[3][2]; 
	dest[2][3] = src1[2][0] * src2[0][3] + src1[2][1] * src2[1][3] + src1[2][2] * src2[2][3] + src1[2][3] * src2[3][3]; 
	dest[3][0] = src1[3][0] * src2[0][0] + src1[3][1] * src2[1][0] + src1[3][2] * src2[2][0] + src1[3][3] * src2[3][0]; 
	dest[3][1] = src1[3][0] * src2[0][1] + src1[3][1] * src2[1][1] + src1[3][2] * src2[2][1] + src1[3][3] * src2[3][1]; 
	dest[3][2] = src1[3][0] * src2[0][2] + src1[3][1] * src2[1][2] + src1[3][2] * src2[2][2] + src1[3][3] * src2[3][2]; 
	dest[3][3] = src1[3][0] * src2[0][3] + src1[3][1] * src2[1][3] + src1[3][2] * src2[2][3] + src1[3][3] * src2[3][3]; 
};


static int SS_MatrixPush( SGS_CTX )
{
	int set = 0;
	float mtx[ 16 ] = {0}, *mtxin, omtx[16];
	int ssz = sgs_StackSize( C );
	
	SGSFN( "SS_MatrixPush" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( ssz < 1 || ssz > 2 ||
		_parse_floatvec( C, 0, mtx, 16 ) ||
		( ssz >= 2 && !sgs_ParseBool( C, 0, &set ) ) )
		_WARN( "unexpected arguments; "
			"function expects 1-2 arguments: array(real x16)[, bool]" )
	
	if( GRCurMatrix >= SS_MATRIX_STACK_SIZE )
		return 0;
	mtxin = (float*) GRWorldMatrices[ GRCurMatrix++ ];
	if( set )
		memcpy( omtx, mtx, sizeof(float)*16 );
	else
		Matrix4x4MultiplyBy4x4( (float (*)[4]) mtx, (float (*)[4]) mtxin, (float (*)[4]) omtx );
	
	GCurRI->set_matrix( GCurRr, SS_RMAT_WORLD, omtx );
	
	sgs_PushBool( C, 1 );
	return 1;
}

static int SS_MatrixPop( SGS_CTX )
{
	SGSFN( "SS_MatrixPop" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( sgs_StackSize( C ) )
		_WARN( "unexpected arguments" )
	
	if( GRCurMatrix > 0 )
	{
		GRCurMatrix--;
		GCurRI->set_matrix( GCurRr, SS_RMAT_WORLD, (float*) GRWorldMatrices[ GRCurMatrix ] );
		
		sgs_PushBool( C, 1 );
		return 1;
	}
	
	return 0;
}


static int SS_SetCamera( SGS_CTX )
{
	float mtx[ 16 ] = {0};
	float mtx2[ 16 ] = {0};
	int ssz = sgs_StackSize( C );
	
	SGSFN( "SS_SetCamera" );
	SCRFN_NEEDS_RENDER_CONTEXT;

	if( ssz < 1 || ssz > 2 ||
		_parse_floatvec( C, 0, mtx, 16 ) ||
		( ssz >= 2 && _parse_floatvec( C, 1, mtx2, 16 ) ) )
		_WARN( "expected an array of 16 'real' values" )
	
	GCurRI->set_matrix( GCurRr, SS_RMAT_VIEW, mtx );
	if( ssz < 2 ){ mtx2[0] = 1; mtx2[5] = 1; mtx2[10] = 1; mtx2[15] = 1; }
	GCurRI->set_matrix( GCurRr, SS_RMAT_PROJ, mtx2 );
	
	return 0;
}


/*
	The font system
*/

SGS_DECLARE sgs_ObjInterface font_iface[1];

typedef
struct _ss_glyph
{
	FT_UInt glyph_id;
	int bmoffx;
	int bmoffy;
	int advx;
	int hastex;
	SS_Texture tex;
}
ss_glyph;

typedef
struct _ss_font
{
	int loaded;
	FT_Face face;
	int size;
	VHTable glyphs;
	
	SS_RenderInterface* riface;
	SS_Renderer* renderer;
}
ss_font;

static int ss_font_init( ss_font* font, SGS_CTX, const char* filename, int size )
{
	font->loaded = 0;
	if( FT_New_Face( g_ftlib, filename, 0, &font->face ) )
		return 0;
	font->size = size;
	FT_Set_Pixel_Sizes( font->face, size, 0 );
	/*
	puts( "FONT LOADED" );
	printf( "size = %d\n", size );
	puts( "-- face info --" );
	printf( "ascender = %d\n", (int) font->face->size->metrics.ascender >> 6 );
	printf( "descender = %d\n", (int) font->face->size->metrics.descender >> 6 );
	*/
	vht_init( &font->glyphs, C, 16, 16 );
	
	font->riface = GCurRI;
	font->renderer = GCurRr;
	
	font->loaded = 1;
	return 1;
}


static void ss_font_free( ss_font* font, SGS_CTX )
{
	if( font->loaded )
	{
		sgs_SizeVal i;
		for( i = 0; i < font->glyphs.size; ++i )
		{
			ss_glyph* G = (ss_glyph*) font->glyphs.vars[ i ].val.data.P;
			if( G->hastex )
				GCurRI->destroy_texture( GCurRr, &G->tex );
			sgs_Dealloc( G );
		}
		FT_Done_Face( font->face );
		vht_free( &font->glyphs, C );
	}
	font->loaded = 0;
}

#define FONTHDR ss_font* font = (ss_font*) data->data

static int ss_font_destruct( SGS_CTX, sgs_VarObj* data )
{
	FONTHDR;
	if( font->riface )
	{
		SS_TmpCtx ctx = ss_TmpMakeCurrent( font->riface, font->renderer );
		ss_font_free( font, C );
		font->riface = NULL;
		font->renderer = NULL;
		GCurRI->poke_resource( GCurRr, data, 0 );
		ss_TmpRestoreCurrent( &ctx );
	}
	return SGS_SUCCESS;
}

#define FONT_IHDR( method ) ss_font* font; \
	if( !SGS_PARSE_METHOD( C, font_iface, font, SS_Font, method ) ) return 0;

static ss_glyph* ss_font_get_glyph( ss_font* font, SGS_CTX, uint32_t cp );
static int ss_fontI_get_advance( SGS_CTX )
{
	int adv = 0;
	sgs_Integer a = 0, b = 0;
	ss_font* font;
	
	SGSFN( "SS_Font.getAdvance" );

	if( !sgs_Method( C ) ||
		sgs_StackSize( C ) != 3 ||
		!sgs_IsObject( C, 0, font_iface ) ||
		!( sgs_ItemType( C, 1 ) == SVT_NULL || sgs_ParseInt( C, 1, &a ) ) ||
		!sgs_ParseInt( C, 2, &b ) )
		_WARN( "unexpected arguments; "
			"method expects this=font and 2 arguments: int|null, int" )

	font = (ss_font*) sgs_GetObjectData( C, 0 );

	if( b )
	{
		ss_glyph* G = ss_font_get_glyph( font, C, (uint32_t) b ), *G2;
		if( G )
			adv += G->advx;
		if( FT_HAS_KERNING( font->face ) && a && ( G2 = ss_font_get_glyph( font, C, (uint32_t) a ) ) )
		{
			FT_Vector delta;
			FT_Get_Kerning( font->face, G2->glyph_id, G->glyph_id, FT_KERNING_DEFAULT, &delta );
			adv += delta.x >> 6;
		}
	}
	sgs_PushInt( C, adv );
	return 1;
}

static int ss_fontI_get_text_length( SGS_CTX )
{
	char* str = NULL;
	sgs_SizeVal size = 0;
	sgs_Int length = 0;
	ss_glyph *G, *G2 = NULL;
	
	FONT_IHDR( getTextLength );
	if( !sgs_LoadArgs( C, "m", &str, &size ) )
		return 0;
	
	while( size > 0 )
	{
		uint32_t cp = SGS_UNICODE_INVCHAR;
		int ret = sgs_utf8_decode( str, size, &cp );
		ret = abs( ret );
		str += ret;
		size -= ret;
		
		G = ss_font_get_glyph( font, C, cp );
		if( G )
		{
			length += G->advx;
			if( FT_HAS_KERNING( font->face ) && G2 )
			{
				FT_Vector delta;
				FT_Get_Kerning( font->face, G2->glyph_id, G->glyph_id, FT_KERNING_DEFAULT, &delta );
				length += delta.x >> 6;
			}
		}
		G2 = G;
	}
	sgs_PushInt( C, length );
	return 1;
}

static int ss_font_getindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, int isprop )
{
	char* str;
	FONTHDR;
	UNUSED( isprop );
	if( sgs_ParseStringP( C, key, &str, NULL ) )
	{
		if( 0 == strcmp( str, "size" ) ){ sgs_PushInt( C, font->size ); return SGS_SUCCESS; }
		if( 0 == strcmp( str, "x_ppem" ) ){ sgs_PushInt( C, font->face->size->metrics.x_ppem ); return SGS_SUCCESS; }
		if( 0 == strcmp( str, "y_ppem" ) ){ sgs_PushInt( C, font->face->size->metrics.y_ppem ); return SGS_SUCCESS; }
		if( 0 == strcmp( str, "ascender" ) ){ sgs_PushInt( C, font->face->size->metrics.ascender >> 6 ); return SGS_SUCCESS; }
		if( 0 == strcmp( str, "descender" ) ){ sgs_PushInt( C, font->face->size->metrics.descender >> 6 ); return SGS_SUCCESS; }
		if( 0 == strcmp( str, "height" ) ){ sgs_PushInt( C, font->face->size->metrics.height >> 6 ); return SGS_SUCCESS; }
		if( 0 == strcmp( str, "max_advance" ) ){ sgs_PushInt( C, font->face->size->metrics.max_advance >> 6 ); return SGS_SUCCESS; }
		
		if( 0 == strcmp( str, "getAdvance" ) ){ sgs_PushCFunction( C, ss_fontI_get_advance ); return SGS_SUCCESS; }
		if( 0 == strcmp( str, "getTextLength" ) ){ sgs_PushCFunction( C, ss_fontI_get_text_length ); return SGS_SUCCESS; }
	}
	return SGS_ENOTFND;
}

static sgs_ObjInterface font_iface[1] =
{{
	"SS_Font",
	ss_font_destruct, NULL,
	ss_font_getindex, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL
}};

static int SS_CreateFont( SGS_CTX )
{
	char* fontname;
	sgs_SizeVal fnsize;
	sgs_Integer fontsize;
	
	SGSFN( "SS_CreateFont" );
	SCRFN_NEEDS_RENDER_CONTEXT;

	if( sgs_StackSize( C ) != 2 ||
		!sgs_ParseString( C, 0, &fontname, &fnsize ) ||
		!sgs_ParseInt( C, 1, &fontsize ) )
		_WARN( "unexpected arguments; function expects 2 arguments: string, int" )

	/* make key */
	sgs_PushItem( C, 0 );
	sgs_PushString( C, ":" );
	sgs_PushItem( C, 1 );
	sgs_StringConcat( C, 3 );

	/* check if dict has the font */
	if( sgs_PushIndexPI( C, &GCurRr->fonts, -1, 0 ) == SGS_SUCCESS )
		return 1;

	/* attempt to load font with different base paths */
	{
		char* paths = NULL;
		MemBuf fpath = membuf_create();
		ss_font* fn = (ss_font*) sgs_PushObjectIPA( C, sizeof(ss_font), font_iface );
		sgs_VarObj* obj = sgs_GetObjectStruct( C, -1 );
		fn->loaded = 0;

		if( sgs_PushGlobal( C, "ss_font_search_paths" ) ||
			!sgs_ParseString( C, -1, &paths, NULL ) )
			_WARN( "could not load search paths" )
		sgs_Pop( C, 1 );

		char* bp = paths, *bps = paths;
		for(;;)
		{
			if( *bp == '\0' || *bp == ';' )
			{
				membuf_resize( &fpath, C, 0 );
				membuf_appbuf( &fpath, C, bps, bp - bps );
				membuf_appchr( &fpath, C, '/' );
				membuf_appbuf( &fpath, C, fontname, fnsize );
				membuf_appchr( &fpath, C, 0 );
				if( ss_font_init( fn, C, fpath.ptr, fontsize ) )
					break;
				if( !*bp )
					break;
				bps = ++bp;
			}
			bp++;
		}
		membuf_destroy( &fpath, C );
		if( !fn->loaded )
		{
			sgs_Msg( C, SGS_WARNING,
				"could not find font '%.*s', paths: %s", fnsize, fontname, paths );
			return 0;
		}
		GCurRI->poke_resource( GCurRr, obj, 1 );
	}

	/* save and return the font object */
	sgs_SetIndexPII( C, &GCurRr->fonts, -2, -1, 0 );
	return 1;
}


static ss_glyph* ss_font_create_glyph( ss_font* font, SGS_CTX, uint32_t cp )
{
	FT_GlyphSlot glyph;
	ss_glyph* G = sgs_Alloc( ss_glyph );
	G->hastex = 0;
	
	FT_Load_Char( font->face, cp, 0 );
	glyph = font->face->glyph;
	FT_Render_Glyph( glyph, FT_RENDER_MODE_NORMAL );
	
	if( glyph->bitmap.width * glyph->bitmap.rows )
	{
		int ret = GCurRI->create_texture_a8( GCurRr, &G->tex, glyph->bitmap.buffer, glyph->bitmap.width, glyph->bitmap.rows, glyph->bitmap.pitch );
		sgs_BreakIf( !ret && "failed to create font texture" );
		G->hastex = 1;
	}

	G->glyph_id = FT_Get_Char_Index( font->face, cp );
	
	G->bmoffx = glyph->bitmap_left;
	G->bmoffy = glyph->bitmap_top;
	G->advx = glyph->advance.x >> 6;

	return G;
}

static ss_glyph* ss_font_get_glyph( ss_font* font, SGS_CTX, uint32_t cp )
{
	sgs_Variable K;
	K.type = SVT_INT;
	K.data.I = cp;
	VHTVar* p = vht_get( &font->glyphs, &K );
	if( !p )
	{
		sgs_Variable V;
		V.type = SVT_PTR;
		ss_glyph* ng = ss_font_create_glyph( font, C, cp );
		V.data.P = ng;
		vht_set( &font->glyphs, C, &K, &V );
		return ng;
	}
	else
		return (ss_glyph*) p->val.data.P;
}

static void ss_int_drawtext_line( ss_font* font, SGS_CTX, char* str,
	sgs_SizeVal size, int x, int y, int xto, float* color )
{
	int xadv = 0, ret, use_kerning;
	uint32_t previous = 0, color_u32;
	ss_glyph* G;
	
	color_u32 = col4f_pack_native( color );
	
	use_kerning = FT_HAS_KERNING( font->face );
	
	while( size > 0 )
	{
		uint32_t cp = SGS_UNICODE_INVCHAR;
		ret = sgs_utf8_decode( str, size, &cp );
		ret = abs( ret );
		str += ret;
		size -= ret;
		
		G = ss_font_get_glyph( font, C, cp );
		if( !G )
			continue;
		
		if( use_kerning && previous && G->glyph_id )
		{
			FT_Vector delta;
			FT_Get_Kerning( font->face, previous, G->glyph_id, FT_KERNING_DEFAULT, &delta );
			xadv += delta.x >> 6;
		}
		previous = G->glyph_id;
		x += xadv;
		
		if( x > xto )
			break;
		
		if( G->hastex )
		{
			float tox, toy;
			int W, H, mx, my;
			
			W = G->tex.width;
			H = G->tex.height;
			
			mx = x + G->bmoffx;
			my = y + font->size - G->bmoffy;
			
			GCurRI->apply_texture( GCurRr, &G->tex );
			if( GCurRI->flags & SS_RI_HALFPIXELOFFSET )
			{
				tox = 0.5f / W;
				toy = 0.5f / H;
			}
			else
			{
				tox = 0;
				toy = 0;
			}
			
			{
				SS_BasicVertex vdata[4] =
				{
					{ { mx, my, 0 },     color_u32, { tox, toy }, {0,0} },
					{ { mx, my+H, 0 },   color_u32, { tox, 1+toy }, {0,0} },
					{ { mx+W, my+H, 0 }, color_u32, { 1+tox, 1+toy }, {0,0} },
					{ { mx+W, my, 0 },   color_u32, { 1+tox, toy }, {0,0} }
				};
				GCurRI->draw_basic_vertices( GCurRr, vdata, 4, SS_PT_TRIANGLE_FAN );
			}
		}
		
		xadv = G->advx;
	}
}

static int SS_IsFont( SGS_CTX )
{
	SGSFN( "SS_IsFont" );
	if( sgs_StackSize( C ) != 1 )
		_WARN( "unexpected arguments; function expects 1 argument" )

	sgs_PushBool( C, sgs_IsObject( C, 0, font_iface ) );
	return 1;
}

static int ss_draw_text_line_int( SGS_CTX, int (*off_fn) (ss_font*) )
{
	int ret = 1;
	char* str;
	sgs_SizeVal strsize;
	sgs_Integer X, Y;
	float color[ 4 ];
	ss_font* ssfont;
	
	if( sgs_StackSize( C ) != 5 )
		_WARN( "unexpected arguments; function expects 5 arguments" )

	if( !sgs_ParseString( C, 0, &str, &strsize ) )
		_WARN( "argument 1 (text) must be 'string'" )
	if( !sgs_IsObject( C, 1, font_iface ) )
		_WARN( "argument 2 (font) has wrong type (must be 'font')" )
	if( !sgs_ParseInt( C, 2, &X ) )
		_WARN( "could not parse argument 3 (X position)" )
	if( !sgs_ParseInt( C, 3, &Y ) )
		_WARN( "could not parse argument 4 (Y position)" )
	if( !ss_ParseColor( C, 4, color ) )
		_WARN( "could not parse argument 5 (color)" )
	
	ssfont = (ss_font*) sgs_GetObjectData( C, 1 );
	if( !ssfont->loaded )
	{
		sgs_Msg( C, SGS_WARNING, "unloaded font detected" );
		goto cleanup;
	}
	
	SCRFN_NEEDS_SPECIFIC_RENDER_CONTEXT( ssfont->riface, ssfont->renderer );
	
	ss_int_drawtext_line( ssfont, C, str, strsize, X, Y + ( off_fn ? off_fn( ssfont ) : 0 ), 0x7fffffff, color );

end:
	sgs_PushBool( C, ret );
	return 1;
cleanup:
	ret = 0;
	goto end;
}

static int offset_from_font_bl( ss_font* font ){ return -font->size; }
static int offset_from_font_vn( ss_font* font )
{
	FT_Size_Metrics m = font->face->size->metrics;
	return -( ( ( m.ascender + abs( m.descender ) ) >> 6 ) - m.y_ppem ) / 2;
}
static int offset_from_font_vc( ss_font* font )
{
	FT_Size_Metrics m = font->face->size->metrics;
	return -( ( ( m.ascender + abs( m.descender ) ) >> 6 ) ) / 2;
}
static int offset_from_font_ta( ss_font* font ){ return offset_from_font_vn( font ) * 2; }
static int offset_from_font_ba( ss_font* font ){ return 0; }

static int SS_DrawTextLine   ( SGS_CTX ){ SGSFN("DrawTextLine"); return ss_draw_text_line_int( C, offset_from_font_vn ); }
static int SS_DrawTextLine_TA( SGS_CTX ){ SGSFN("DrawTextLine_TA"); return ss_draw_text_line_int( C, offset_from_font_ta ); }
static int SS_DrawTextLine_BA( SGS_CTX ){ SGSFN("DrawTextLine_BA"); return ss_draw_text_line_int( C, offset_from_font_ba ); }
static int SS_DrawTextLine_BL( SGS_CTX ){ SGSFN("DrawTextLine_BL"); return ss_draw_text_line_int( C, offset_from_font_bl ); }
static int SS_DrawTextLine_VN( SGS_CTX ){ SGSFN("DrawTextLine_VN"); return ss_draw_text_line_int( C, offset_from_font_vn ); }
static int SS_DrawTextLine_VC( SGS_CTX ){ SGSFN("DrawTextLine_VC"); return ss_draw_text_line_int( C, offset_from_font_vc ); }


static int SS_SetClipRect( SGS_CTX )
{
	sgs_Integer x1, x2, y1, y2;
	SGSFN( "SS_SetClipRect" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( sgs_StackSize( C ) == 1 &&
		sgs_ItemType( C, 0 ) == SVT_NULL )
	{
		GCurRI->set_render_state( GCurRr, SS_RS_CLIPENABLE, 0, 0,0,0 );
		sgs_PushBool( C, 1 );
		return 1;
	}
	else if( sgs_StackSize( C ) == 4 &&
		sgs_ParseInt( C, 0, &x1 ) &&
		sgs_ParseInt( C, 1, &x2 ) &&
		sgs_ParseInt( C, 2, &y1 ) &&
		sgs_ParseInt( C, 3, &y2 ) )
	{
		if( x2 < x1 || y2 < y1 )
			_WARN( "invalid (negative) width and/or height" )
		GCurRI->set_render_state( GCurRr, SS_RS_CLIPRECT, x1, y1, x2, y2 );
		GCurRI->set_render_state( GCurRr, SS_RS_CLIPENABLE, 1, 0,0,0 );
		sgs_PushBool( C, 1 );
		return 1;
	}
	else
		_WARN( "unexpected arguments; function expects null or 4 int values" )
}

static int SS_SetDepthTest( SGS_CTX )
{
	sgs_Bool set;
	SGSFN( "SS_SetDepthTest" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( !sgs_LoadArgs( C, "b", &set ) )
		return 0;
	
	GCurRI->set_render_state( GCurRr, SS_RS_ZENABLE, set, 0,0,0 );
	
	return 0;
}

static int SS_SetCulling( SGS_CTX )
{
	sgs_Integer ii;
	SGSFN( "SS_SetCulling" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( !sgs_LoadArgs( C, "i", &ii ) )
		return 0;
	
	GCurRI->set_render_state( GCurRr, SS_RS_CULLING, ii, 0,0,0 );
	return 0;
}


static int SS_SetBlending( SGS_CTX )
{
	sgs_Integer func = 0, src, dst;
	SGSFN( "SS_SetBlending" );
	SCRFN_NEEDS_RENDER_CONTEXT;
	
	if( !sgs_LoadArgs( C, "iii", &func, &src, &dst ) )
		return 0;
	
	if( func < 0 || func >= SS_BLENDOP__COUNT )
		return sgs_Msg( C, SGS_WARNING, "wrong blend function" );
	if( src < 0 || src >= SS_BLEND__COUNT )
		return sgs_Msg( C, SGS_WARNING, "wrong source blend factor" );
	if( dst < 0 || dst >= SS_BLEND__COUNT )
		return sgs_Msg( C, SGS_WARNING, "wrong destination blend factor" );
	
	GCurRI->set_render_state( GCurRr, SS_RS_BLENDFACTORS, src, dst, 0,0 );
	GCurRI->set_render_state( GCurRr, SS_RS_BLENDOP, func, 0,0,0 );
	return 0;
}


static sgs_RegIntConst gl_ints[] =
{
	/* GL draw modes */
	IC( SS_PT_POINTS ),
	IC( SS_PT_LINES ),
	IC( SS_PT_LINE_STRIP ),
	IC( SS_PT_TRIANGLES ),
	IC( SS_PT_TRIANGLE_FAN ),
	IC( SS_PT_TRIANGLE_STRIP ),
	IC( SS_PT_QUADS ),
	
	/* blending */
	IC( SS_BLENDOP_ADD ),
	IC( SS_BLENDOP_SUBTRACT ),
	IC( SS_BLENDOP_REVERSE_SUBTRACT ),
	IC( SS_BLENDOP_MIN ),
	IC( SS_BLENDOP_MAX ),
	
	IC( SS_BLEND_ZERO ),
	IC( SS_BLEND_ONE ),
	IC( SS_BLEND_SRCCOLOR ),
	IC( SS_BLEND_INVSRCCOLOR ),
	IC( SS_BLEND_SRCALPHA ),
	IC( SS_BLEND_INVSRCALPHA ),
	IC( SS_BLEND_DESTCOLOR ),
	IC( SS_BLEND_INVDESTCOLOR ),
	IC( SS_BLEND_DESTALPHA ),
	IC( SS_BLEND_INVDESTALPHA ),
	IC( SS_BLEND_SRCALPHASAT ),
};

static sgs_RegFuncConst gl_funcs[] =
{
	FN( CreateTexture ),
	FN( Draw ),
	FN( MakeVertexFormat ), FN( DrawPacked ),
	FN( CreateRenderBuffer ),
	FN( CreateFont ), FN( IsFont ),
	FN( DrawTextLine ), FN( DrawTextLine_TA ), FN( DrawTextLine_BA ), FN( DrawTextLine_BL ), FN( DrawTextLine_VN ), FN( DrawTextLine_VC ),
	FN( MatrixPush ), FN( MatrixPop ),
	FN( SetCamera ), FN( SetClipRect ),
	FN( SetDepthTest ), FN( SetCulling ), FN( SetBlending ),
};

int ss_InitGraphics( SGS_CTX )
{
	int ret, mid;
	
	for( mid = 0; mid < SS_MATRIX_STACK_SIZE; ++mid )
	{
		_mtx_identity( (float*) GRWorldMatrices[ mid ] );
	}

	FT_Init_FreeType( &g_ftlib );

	ret = sgs_RegIntConsts( C, gl_ints, ARRAY_SIZE( gl_ints ) );
	if( ret != SGS_SUCCESS ) return ret;
	ret = sgs_RegFuncConsts( C, gl_funcs, ARRAY_SIZE( gl_funcs ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	sgs_RegisterType( C, "SS_Texture", tex_iface );
	
	return SGS_SUCCESS;
}

