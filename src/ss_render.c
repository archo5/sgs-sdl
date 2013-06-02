
#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define SGS_INTERNAL

#include "../sgscript/src/sgs_util.h"
#undef ARRAY_SIZE

#include "ss_main.h"

#define FN( f ) { #f, ss_##f }
#define IC( i ) { #i, i }
#define _WARN( err ) { sgs_Printf( C, SGS_WARNING, err ); return 0; }




FT_Library g_ftlib;




void _mtx_transpose( float* m )
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



#define CT_HREPEAT 1
#define CT_VREPEAT 2
#define CT_NOLERP 4
#define CT_MIPMAPS 8

typedef struct _sgs_Texture
{
	GLuint id;
	int32_t flags;
	int16_t width;
	int16_t height;
}
sgs_Texture;

#define TEXHDR sgs_Texture* tex = (sgs_Texture*) data->data

int sstex_destruct( SGS_CTX, sgs_VarObj* data, int dco )
{
	TEXHDR;
	glDeleteTextures( 1, &tex->id );
	sgs_Dealloc( tex );
	return SGS_SUCCESS;
}

int sstex_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "texture" );
		return SGS_SUCCESS;
	}
	else if( type == SVT_STRING )
	{
		char buf[ 48 ];
		TEXHDR;
		sprintf( buf, "Texture (%d x %d, type %d)", (int) tex->width, (int) tex->height, (int) tex->flags );
		sgs_PushString( C, buf );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

int sstex_getindex( SGS_CTX, sgs_VarObj* data, int prop )
{
	char* str;
	sgs_SizeVal size;
	TEXHDR;
	
	if( !sgs_ParseString( C, 0, &str, &size ) )
		return SGS_EINVAL;
	
	if( !strcmp( str, "width" ) ){ sgs_PushInt( C, tex->width ); return SGS_SUCCESS; }
	if( !strcmp( str, "height" ) ){ sgs_PushInt( C, tex->height ); return SGS_SUCCESS; }
	
	return SGS_ENOTFND;
}

void* tex_iface[] =
{
	SOP_GETINDEX, sstex_getindex,
	SOP_CONVERT, sstex_convert,
	SOP_DESTRUCT, sstex_destruct,
	SOP_END
};

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
	- supports image objects (TODO) and filenames as image sources
	- filenames will be converted to images first by taking the extension, lowercasing it and calling "ss_load_image_from_file_<ext>"
		- if function doesn't exist or it simply returns null, texture creation fails
*/

int ss_create_texture( SGS_CTX )
{
	uint32_t flags;
	sgs_Image* ii;
	int argc = sgs_StackSize( C ), bystr = 0;
	
	static flag_string_item_t flagitems[] =
	{
		{ "hrepeat", CT_HREPEAT },
		{ "vrepeat", CT_VREPEAT },
		{ "nolerp", CT_NOLERP },
	/*	{ "mipmaps", CT_MIPMAPS }, TODO */
		FSI_LAST
	};
	
	if( argc < 1 || argc > 2 )
		_WARN( "create_texture() - unexpected arguments; function expects 1-2 arguments: (image|string)[, string]" )
	
	flags = sgs_GetFlagString( C, 1, flagitems );
	
	sgs_PushItem( C, 0 ); /* NAME [FLAGS] NAME */
	
	if( sgs_ItemType( C, 0 ) == SVT_STRING )
	{
		sgs_Variable var, obj, idx;
		
		bystr = 1;
		
		/* check if image already loaded */
		sgs_PushString( C, "|" ); /* NAME [FLAGS] NAME "|" */
		sgs_PushInt( C, flags ); /* NAME [FLAGS] NAME "\0" INT_FLAGS */
		sgs_StringMultiConcat( C, 3 ); /* NAME [FLAGS] KEY */
		
		sgs_PushGlobal( C, "_Gtex" ); /* NAME [FLAGS] KEY _Gtex */
		if( sgs_GetStackItem( C, -1, &obj ) && sgs_GetStackItem( C, -2, &idx ) && sgs_GetIndex( C, &var, &obj, &idx ) == SGS_SUCCESS )
		{
			/* found it! */
			sgs_PushVariable( C, &var ); /* NAME [FLAGS] KEY _Gtex TEXTURE */
			sgs_Release( C, &var );
			return 1;
		}
		sgs_Pop( C, 1 );
		
		/* convert string to image */
		if( !sgs_LoadImageHelper( C, (char*) sgs_GetStringPtr( C, 0 ), sgs_GetStringSize( C, 0 ), "create_texture" ) )
			return 0; /* error printed by LIH */
		
		/* NAME [FLAGS] KEY IMAGE */
		
		/* insert return value as argument #0 */
		sgs_StoreItem( C, 0 );
		/* IMAGE [FLAGS] KEY */
		
		/* texture key must stay at position -1 */
	}
	
	/* IMAGE [FLAGS] [KEY](if bystr) */
	
	if( !stdlib_toimage( C, 0, &ii ) )
		_WARN( "create_texture() - unexpected arguments; function expects 1-2 arguments: (image|string)[, string]" )
	
	{
		sgs_Texture* tt;
		GLuint tex;
		glGenTextures( 1, &tex );
		glBindTexture( GL_TEXTURE_2D, tex );
		
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
#ifndef GL_BGRA
# define GL_BGRA 0x80E1
#endif
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, ii->width, ii->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, ii->data );
		
		if( flags & CT_HREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		if( flags & CT_VREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flags & CT_NOLERP ? GL_NEAREST : GL_LINEAR );
		{
			GLuint magf = flags & CT_MIPMAPS ?
				( flags & CT_NOLERP ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR ) :
				( flags & CT_NOLERP ? GL_NEAREST : GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magf );
		}
		
		tt = sgs_Alloc( sgs_Texture );
		tt->id = tex;
		tt->flags = flags;
		tt->width = ii->width;
		tt->height = ii->height;
		sgs_PushObject( C, tt, tex_iface );
	}
	
	/* IMAGE [FLAGS] [KEY](if bystr) TEXTURE */
	
	/* texture key at position -2 */
	if( bystr )
	{
		sgs_Variable obj, idx, val;
		sgs_PushGlobal( C, "_Gtex" ); /* IMAGE [FLAGS] KEY TEXTURE _Gtex */
		sgs_GetStackItem( C, -1, &obj );
		sgs_GetStackItem( C, -3, &idx );
		sgs_GetStackItem( C, -2, &val );
		sgs_SetIndex( C, &obj, &idx, &val );
		sgs_Pop( C, 1 ); /* IMAGE [FLAGS] KEY TEXTURE */
	}
	
	return 1;
}


GLuint sgs_GetTextureId( SGS_CTX, sgs_Variable* var )
{
	if( var->type != SVT_OBJECT || var->data.O->iface != tex_iface )
		return 0;
	
	return ((sgs_Texture*) var->data.O->data)->id;
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
	>> tech
	- vertex arrays // TODO, currently get it out there with immediate mode
	>> intermediate storages
	- data loading functions will return additional values to specify if a buffer was created in the call
	
	>> CHANGES
	- renamed "shape" to "preset"
*/
typedef struct floatbuf_s
{
	float* data; /* this can point to stack, if so - 'my' = 0 as with all cases where no allocations are done */
	int32_t size;
	int32_t cnt;
	int my;
}
floatbuf;
#define NFB { NULL, 0, 0, 0 }
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
const char* _parse_floatvec( SGS_CTX, float* out, int numcomp )
{
	sgs_Real data[ 2 ];
	sgs_Variable var;
	
	if( stdlib_tovec2d( C, -1, data, 0 ) )
	{
		out[ 0 ] = data[ 0 ];
		if( numcomp > 1 )
			out[ 1 ] = data[ 1 ];
		return NULL;
	}
	
	sgs_GetStackItem( C, -1, &var );
	if( sgs_IsArray( C, &var ) )
	{
		int32_t i, asz = sgs_ArraySize( C, &var );
		if( asz > numcomp )
			asz = numcomp;
		
		for( i = 0; i < asz; ++i )
		{
			sgs_Real real;
			sgs_Variable item;
			if( !sgs_ArrayGet( C, &var, i, &item ) )
			{
				return "could not read from array";
			}
			
			sgs_PushVariable( C, &item );
			sgs_Release( C, &item );
			if( !sgs_ParseReal( C, -1, &real ) )
			{
				sgs_Pop( C, 1 );
				return "non-number value found";
			}
			sgs_Pop( C, 1 );
			
			out[ i ] = real;
		}
		
		return NULL;
	}
	
	return "item was not a vector or array of floats";
}
const char* _parse_floatbuf( SGS_CTX, sgs_Variable* var, floatbuf* out, int numcomp, float* defcomp, int arr )
{
	float* off;
	int32_t i, asz;
	
	if( !arr )
	{
		const char* res;
		out->cnt = 1;
		out->size = numcomp;
		if( !out->data )
		{
			out->data = sgs_Alloc_n( float, out->size );
			out->my = 1;
		}
		memcpy( out->data, defcomp, numcomp * sizeof(float) );
		sgs_PushVariable( C, var );
		res = _parse_floatvec( C, out->data, numcomp );
		sgs_Pop( C, 1 );
		if( res && out->my )
		{
			sgs_Dealloc( out->data );
			out->my = 0;
		}
		return res;
	}
	
	if( !sgs_IsArray( C, var ) )
		return "array expected";
	
	asz = sgs_ArraySize( C, var );
	out->cnt = asz;
	out->size = asz * numcomp;
	out->data = sgs_Alloc_n( float, out->size );
	
	off = out->data;
	for( i = 0; i < asz; ++i )
	{
		const char* subres;
		sgs_Variable item;
		if( !sgs_ArrayGet( C, var, i, &item ) || item.type != SVT_OBJECT )
		{
			sgs_Dealloc( out->data );
			return "element was not an object";
		}
		
		memcpy( off, defcomp, numcomp * sizeof(float) );
		
		sgs_PushVariable( C, &item );
		sgs_Release( C, &item );
		subres = _parse_floatvec( C, off, numcomp );
		sgs_Pop( C, 1 );
		
		if( subres )
		{
			sgs_Dealloc( out->data );
			return subres;
		}
		
		off += numcomp;
	}
	
	out->my = 1;
	
	return NULL;
}
int _draw_load_geom( SGS_CTX, int* outmode, floatbuf* vert, floatbuf* vcol, floatbuf* vtex )
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
	
	if( !sgs_UnpackDict( C, 0, gi ) )
		_WARN( "draw(): no geometry data found" )
	
	if( gi[0].var && ( gi[1].var || gi[2].var ) )
	{
		sgs_UnpackFree( C, gi );
		_WARN( "draw(): 'preset' doesn't work together with 'mode' or 'vertices'" )
	}
	
	if( gi[0].var )
	{
		int ret = 0;
		char* str;
		sgs_SizeVal size;
		sgs_PushVariable( C, gi[0].var );
		if( !sgs_ParseString( C, -1, &str, &size ) )
		{
			sgs_Pop( C, 1 );
			sgs_UnpackFree( C, gi );
			_WARN( "draw(): 'preset' must be a string" )
		}
		sgs_Pop( C, 1 );
		
		if( !strcmp( str, "box" ) )
		{
			*outmode = GL_QUADS;
			static const float boxbuf[] =
			{
				-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
				0, 0, 1, 0, 1, 1, 0, 1,
			};
			vert->my = 1;
			vert->cnt = 4;
			vert->size = 8;
			vert->data = sgs_Alloc_n( float, 8 );
			memcpy( vert->data, boxbuf, sizeof(float) * 8 );
			vtex->my = 1;
			vtex->cnt = 4;
			vtex->size = 8;
			vtex->data = sgs_Alloc_n( float, 8 );
			memcpy( vtex->data, boxbuf + 8, sizeof(float) * 8 );
			ret = 1;
		}
		if( !strcmp( str, "tile" ) )
		{
			*outmode = GL_QUADS;
			static const float boxbuf[] =
			{
				0, 0, 1, 0, 1, 1, 0, 1,
			};
			vert->my = 1;
			vert->cnt = 4;
			vert->size = 8;
			vert->data = sgs_Alloc_n( float, 8 );
			memcpy( vert->data, boxbuf, sizeof(float) * 8 );
			vtex->my = 1;
			vtex->cnt = 4;
			vtex->size = 8;
			vtex->data = sgs_Alloc_n( float, 8 );
			memcpy( vtex->data, boxbuf, sizeof(float) * 8 );
			ret = 1;
		}
		
		sgs_UnpackFree( C, gi );
		if( !ret )
			_WARN( "draw(): preset not found" )
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
			sgs_Printf( C, SGS_WARNING, "draw(): failed to load vertices - %s", res );
			goto cleanup;
		}
		
		if( !gi[1].var )
		{
			sgs_Printf( C, SGS_WARNING, "draw(): 'mode' not found" );
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
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load vertex colors - %s", res );
				goto cleanup;
			}
		}
		
		if( gi[4].var )
		{
			res = _parse_floatbuf( C, gi[4].var, &tdata, 2, defcomp+8, 1 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load vertex texcoords - %s", res );
				goto cleanup;
			}
		}
		
		sgs_UnpackFree( C, gi );
		if( pdata.data ) *vert = pdata;
		if( cdata.data ) *vcol = cdata;
		if( tdata.data ) *vtex = tdata;
		return 1;
		
cleanup:
		sgs_UnpackFree( C, gi );
		if( pdata.my ) sgs_Dealloc( pdata.data );
		if( cdata.my ) sgs_Dealloc( cdata.data );
		if( tdata.my ) sgs_Dealloc( tdata.data );
		return 0;
	}
	
	sgs_UnpackFree( C, gi );
	_WARN( "draw(): no geometry data found" )
}
int _draw_load_inst( SGS_CTX, floatbuf* xform, floatbuf* icol )
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
	
	if( !sgs_UnpackDict( C, 0, tfi ) )
		_WARN( "draw(): no instancing data found" )
	
	if( tfi[1].var ) /* found 'transforms', array of matrices */
	{
		sgs_UnpackFree( C, tfi );
		_WARN( "MATRICES ARE NOT YET IMPLEMENTED" )
	}
	
	else if( tfi[0].var ) /* found 'transform', one matrix */
	{
		sgs_UnpackFree( C, tfi );
		_WARN( "MATRICES ARE NOT YET IMPLEMENTED" )
	}
	
	else
	{
		int ret = 1;
		int32_t i;
		float defcomp[] = { 0, 0, 0, 0, 1, 1, 1, 1 };
		float tmpfloats[ 5 ];
		floatbuf posdata = NFB, angdata = NFB, scaledata = NFB;
		posdata.data = tmpfloats;
		angdata.data = tmpfloats + 2;
		scaledata.data = tmpfloats + 3;
		if( tfi[3].var ) /* found 'positions', array of vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[3].var, &posdata, 2, defcomp, 1 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load positions - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[2].var ) /* found 'position', one vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[2].var, &posdata, 2, defcomp, 0 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load position - %s", res );
				goto cleanup;
			}
		}
		else
		{
			sgs_Printf( C, SGS_WARNING, "draw(): no instance position data found" );
		}
		
		if( tfi[5].var ) /* found 'angles', array of real */
		{
			const char* res = _parse_floatbuf( C, tfi[5].var, &angdata, 1, defcomp, 1 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load angles - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[4].var ) /* found 'angle', one real */
		{
			const char* res = _parse_floatbuf( C, tfi[4].var, &angdata, 1, defcomp, 0 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load angle - %s", res );
				goto cleanup;
			}
		}
		
		if( tfi[7].var ) /* found 'scales', array of vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[7].var, &scaledata, 2, defcomp+4, 1 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load scales - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[6].var ) /* found 'scale', one vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[6].var, &scaledata, 2, defcomp+4, 0 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load scale - %s", res );
				goto cleanup;
			}
		}
		
		/* mix-and-match */
		xform->data = sgs_Alloc_n( float, 16 * posdata.cnt );
		xform->size = 16 * posdata.cnt;
		xform->cnt = posdata.cnt;
		xform->my = 1;
		
		for( i = 0; i < posdata.cnt; ++i )
		{
			float* mtx = xform->data + i * 16;
			float posx = posdata.data[ i * 2 ];
			float posy = posdata.data[ i * 2 + 1 ];
			float angle = 0;
			float sclx = 1;
			float scly = 1;
			if( angdata.size )
				angle = angdata.data[ i % angdata.cnt ];
			if( scaledata.size )
			{
				int32_t off = i % scaledata.cnt;
				sclx = scaledata.data[ off * 2 ];
				scly = scaledata.data[ off * 2 + 1 ];
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
				mtx[ 0 ] = ca * sclx; mtx[ 1 ] = -sa * sclx; mtx[ 3 ] = posx;
				mtx[ 4 ] = sa * scly; mtx[ 5 ] = ca * scly; mtx[ 7 ] = posy;
				mtx[ 10 ] = mtx[ 15 ] = 1;
				mtx[ 2 ] = mtx[ 6 ] = mtx[ 8 ] = mtx[ 9 ] =
					mtx[ 11 ] = mtx[ 12 ] = mtx[ 13 ] = mtx[ 14 ] = 0;
				
				_mtx_transpose( mtx );
			}
		}
		
end:
		if( posdata.my ) sgs_Dealloc( posdata.data );
		if( angdata.my ) sgs_Dealloc( angdata.data );
		if( scaledata.my ) sgs_Dealloc( scaledata.data );
		if( !ret )
		{
			sgs_UnpackFree( C, tfi );
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
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load colors - %s", res );
				sgs_UnpackFree( C, tfi );
				return 0;
			}
		}
		else if( tfi[8].var ) /* found 'colors', array of real4 */
		{
			const char* res = _parse_floatbuf( C, tfi[8].var, icol, 4, defcomp, 0 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, "draw(): failed to load color - %s", res );
				sgs_UnpackFree( C, tfi );
				return 0;
			}
		}
	}
	
	sgs_UnpackFree( C, tfi );
	return 1;
}
int ss_draw( SGS_CTX )
{
	float *tf, *cc, *vp, *vt, *vc;
	int mode = GL_TRIANGLES, ret = 1;
	GLuint texid = 0;
	floatbuf vert = NFB, vcol = NFB, vtex = NFB, xform = NFB, icol = NFB;
	sgs_Variable texture;
	dict_unpack_item_t mi[] =
	{
		{ "texture", &texture },
		DUI_LAST,
	};
	
	if( sgs_StackSize( C ) != 1 ||
		sgs_ItemType( C, 0 ) != SVT_OBJECT )
		_WARN( "draw(): expected one dictionary argument" )
	
	sgs_UnpackDict( C, 0, mi );
	
	if( !_draw_load_geom( C, &mode, &vert, &vcol, &vtex ) )
		goto cleanup;
	if( !_draw_load_inst( C, &xform, &icol ) )
		goto cleanup;
	
	if( mi[0].var )
	{
		texid = sgs_GetTextureId( C, mi[0].var );
		if( !texid )
		{
			sgs_Printf( C, SGS_WARNING, "draw(): could not use texture" );
		}
	}
	
	if( texid )
	{
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texid );
	}
	else
		glDisable( GL_TEXTURE_2D );
	
	glMatrixMode( GL_MODELVIEW );
	glColor4f( 1, 1, 1, 1 );
	glTexCoord2f( 0, 0 );
	cc = icol.data;
	for( tf = xform.data; tf < xform.data + xform.size; tf += 16 )
	{
		glPushMatrix();
		glMultMatrixf( tf );
		
		if( cc < icol.data + icol.size )
		{
			/* TODO: color multiplication */
			glColor4fv( cc );
			cc += 4;
		}
		
		glBegin( mode );
		
		vt = vtex.data;
		vc = vcol.data;
		for( vp = vert.data; vp < vert.data + vert.size; vp += 2 )
		{
			if( vt < vtex.data + vtex.size )
			{
				glTexCoord2f( vt[0], 1-vt[1] );
				vt += 2;
			}
			if( vc < vcol.data + vcol.size )
			{
				glColor4fv( vc );
				vc += 4;
			}
			glVertex2fv( vp );
		}
		
		glEnd();
		
		glPopMatrix();
	}
	
end:
	if( vert.my ) sgs_Dealloc( vert.data );
	if( vcol.my ) sgs_Dealloc( vcol.data );
	if( vtex.my ) sgs_Dealloc( vtex.data );
	if( xform.my ) sgs_Dealloc( xform.data );
	if( icol.my ) sgs_Dealloc( icol.data );
	sgs_UnpackFree( C, mi );
	
	sgs_PushBool( C, ret );
	return 1;

cleanup:
	ret = 0;
	goto end;
}

int ss_set_camera( SGS_CTX )
{
	float mtx[ 16 ] = {0};

	if( sgs_StackSize( C ) != 1 ||
		_parse_floatvec( C, mtx, 16 ) )
		_WARN( "set_camera(): expected an array of 16 'real' values" )

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	_mtx_transpose( mtx );
	glLoadMatrixf( mtx );
	return 0;
}


/*
	The font system
*/

void* font_iface[];

typedef
struct _ss_glyph
{
	FT_UInt glyph_id;
	int texwidth;
	int texheight;
	int bmoffx;
	int bmoffy;
	int advx;
	GLuint texture;
	double usagetime;
	float sortQ;
}
ss_glyph;

typedef
struct _ss_font
{
	int loaded;
	FT_Face face;
	int size;
	HashTable glyphs;
}
ss_font;

int ss_font_init( ss_font* font, SGS_CTX, const char* filename, int size )
{
	font->loaded = 0;
	if( FT_New_Face( g_ftlib, filename, 0, &font->face ) )
		return 0;
	font->size = size;
	FT_Set_Pixel_Sizes( font->face, size, 0 );
	ht_init( &font->glyphs, C, 4 );
	font->loaded = 1;
	return 1;
}

void ss_font_free( ss_font* font, SGS_CTX )
{
	if( font->loaded )
	{
		HTPair *p = font->glyphs.pairs, *pend = font->glyphs.pairs + font->glyphs.size;
		while( p < pend )
		{
			if( p->str && p->ptr )
			{
				ss_glyph* G = (ss_glyph*) p->ptr;
				if( G->texture )
					glDeleteTextures( 1, &G->texture );
				sgs_Dealloc( G );
			}
			p++;
		}
		FT_Done_Face( font->face );
		ht_free( &font->glyphs, C );
	}
	font->loaded = 0;
}

#define FONTHDR ss_font* font = (ss_font*) data->data

int ss_font_destruct( SGS_CTX, sgs_VarObj* data, int dco )
{
	FONTHDR;
	ss_font_free( font, C );
	sgs_Dealloc( font );
	return SGS_SUCCESS;
}

int ss_font_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_CONVOP_TOTYPE )
	{
		UNUSED( data );
		sgs_PushString( C, "font" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

ss_glyph* ss_font_get_glyph( ss_font* font, SGS_CTX, uint32_t cp );
int ss_fontI_get_advance( SGS_CTX )
{
	int adv = 0;
	sgs_Integer a = 0, b = 0;
	ss_font* font;

	if( !sgs_Method( C ) ||
		sgs_StackSize( C ) != 3 ||
		sgs_ItemType( C, 0 ) != SVT_OBJECT ||
		sgs_GetObjectData( C, 0 )->iface != font_iface ||
		!( sgs_ItemType( C, 1 ) == SVT_NULL || sgs_ParseInt( C, 1, &a ) ) ||
		!sgs_ParseInt( C, 2, &b ) )
		_WARN( "font::get_advance(): unexpected arguments; "
			"method expects this=font and 2 arguments: int|null, int" )

	font = (ss_font*) sgs_GetObjectData( C, 0 )->data;

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

int ss_font_getindex( SGS_CTX, sgs_VarObj* data, int prop )
{
	char* str = sgs_ToString( C, 0 );
	FONTHDR;

	if( 0 == strcmp( str, "size" ) ){ sgs_PushInt( C, font->size ); return SGS_SUCCESS; }
	if( 0 == strcmp( str, "get_advance" ) ){ sgs_PushCFunction( C, ss_fontI_get_advance ); return SGS_SUCCESS; }

	return SGS_ENOTFND;
}

void* font_iface[] =
{
	SOP_GETINDEX, ss_font_getindex,
	SOP_CONVERT, ss_font_convert,
	SOP_DESTRUCT, ss_font_destruct,
	SOP_END,
};

int ss_create_font( SGS_CTX )
{
	char* fontname;
	sgs_SizeVal fnsize;
	sgs_Integer fontsize;

	if( sgs_StackSize( C ) != 2 ||
		!sgs_ParseString( C, 0, &fontname, &fnsize ) ||
		!sgs_ParseInt( C, 1, &fontsize ) )
		_WARN( "create_font(): unexpected arguments; function expects 2 arguments: string, int" )

	/* make key */
	sgs_PushItem( C, 0 );
	sgs_PushString( C, ":" );
	sgs_PushItem( C, 1 );
	sgs_StringMultiConcat( C, 3 );

	/* check if dict has the font */
	sgs_PushGlobal( C, "_Gfonts" );
	if( sgs_PushIndex( C, -1, -2 ) == SGS_SUCCESS )
		return 1;

	/* attempt to load font with different base paths */
	{
		char* paths = NULL;
		MemBuf fpath = membuf_create();
		ss_font* fn = sgs_Alloc( ss_font );
		fn->loaded = 0;
		sgs_PushObject( C, fn, font_iface );

		if( sgs_PushGlobal( C, "ss_font_search_paths" ) ||
			!sgs_ParseString( C, -1, &paths, NULL ) )
			_WARN( "create_font(): could not load search paths" )
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
			sgs_Printf( C, SGS_WARNING, "create_font(): "
				"could not find font '%.*s', paths: %s", fnsize, fontname, paths );
			return 0;
		}
	}

	/* save and return the font object */
	{
		sgs_Variable obj, idx, val;
		sgs_GetStackItem( C, -2, &obj );
		sgs_GetStackItem( C, -3, &idx );
		sgs_GetStackItem( C, -1, &val );
		sgs_SetIndex( C, &obj, &idx, &val );
		return 1;
	}
}


ss_glyph* ss_font_create_glyph( ss_font* font, SGS_CTX, uint32_t cp )
{
	int x, y;
	uint8_t* imgdata, *pp;
	GLuint tex = 0;
	FT_GlyphSlot glyph;
	ss_glyph* G = sgs_Alloc( ss_glyph );

	FT_Load_Char( font->face, cp, 0 );
	glyph = font->face->glyph;
	FT_Render_Glyph( glyph, FT_RENDER_MODE_NORMAL );
	
	if( glyph->bitmap.width * glyph->bitmap.rows )
	{
		glGenTextures( 1, &tex );
		glBindTexture( GL_TEXTURE_2D, tex );
		imgdata = sgs_Alloc_n( uint8_t, glyph->bitmap.width * glyph->bitmap.rows * 4 );
		pp = glyph->bitmap.buffer;
		for( y = 0; y < glyph->bitmap.rows; ++y )
		{
			for( x = 0; x < glyph->bitmap.width; ++x )
			{
				int off = y * glyph->bitmap.pitch * 4;
				imgdata[ off + x * 4 ] = 0xff;
				imgdata[ off + x * 4 + 1 ] = 0xff;
				imgdata[ off + x * 4 + 2 ] = 0xff;
				imgdata[ off + x * 4 + 3 ] = pp[ x ];
			}
			pp += glyph->bitmap.pitch;
		}
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, glyph->bitmap.width, glyph->bitmap.rows,
			0, GL_RGBA, GL_UNSIGNED_BYTE, imgdata );
		sgs_Dealloc( imgdata );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	}

	G->glyph_id = FT_Get_Char_Index( font->face, cp );
	G->texture = tex;
	G->texwidth = glyph->bitmap.width;
	G->texheight = glyph->bitmap.rows;
	G->bmoffx = glyph->bitmap_left;
	G->bmoffy = glyph->bitmap_top;
	G->advx = glyph->advance.x >> 6;

	return G;
}

ss_glyph* ss_font_get_glyph( ss_font* font, SGS_CTX, uint32_t cp )
{
	void* g = ht_get( &font->glyphs, (const char*) &cp, 4 );
	if( !g )
	{
		ss_glyph* ng = ss_font_create_glyph( font, C, cp );
		ht_set( &font->glyphs, C, (const char*) &cp, 4, ng );
		return ng;
	}
	else
		return (ss_glyph*) g;
}

void ss_int_drawtext_line( ss_font* font, SGS_CTX, char* str,
	sgs_SizeVal size, int x, int y, int xto, sgs_Real* color )
{
	int W, H, mx, my, xadv = 0, ret, use_kerning;
	uint32_t previous = 0;
	ss_glyph* G;

	glEnable( GL_TEXTURE_2D );
	glColor4f( color[0], color[1], color[2], color[3] );

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
		
		if( G->texture )
		{
			W = G->texwidth;
			H = G->texheight;
			
			mx = x + G->bmoffx;
			my = y + font->size - G->bmoffy;
			
			glBindTexture( GL_TEXTURE_2D, G->texture );
			glBegin( GL_QUADS );
			glTexCoord2f( 0, 0 );
			glVertex2f( mx, my );
			glTexCoord2f( 0, 1 );
			glVertex2f( mx, my+H );
			glTexCoord2f( 1, 1 );
			glVertex2f( mx+W, my+H );
			glTexCoord2f( 1, 0 );
			glVertex2f( mx+W, my );
			glEnd();
		}

		xadv = G->advx;
	}
}

int ss_is_font( SGS_CTX )
{
	if( sgs_StackSize( C ) != 1 )
		_WARN( "is_font(): unexpected arguments; function expects 1 argument" )

	sgs_PushBool( C, sgs_ItemType( C, 0 ) == SVT_OBJECT &&
		sgs_GetObjectData( C, 0 )->iface == font_iface );
	return 1;
}

int ss_draw_text_line( SGS_CTX )
{
	int ret = 1;
	char* str;
	sgs_SizeVal strsize;
	sgs_Variable fontvar;
	sgs_Integer X, Y;
	sgs_Real color[ 4 ];
	ss_font* ssfont;
	
	if( sgs_StackSize( C ) != 5 )
		_WARN( "draw_text_line(): unexpected arguments; function expects 5 arguments" )

	if( !sgs_ParseString( C, 0, &str, &strsize ) )
		_WARN( "draw_text_line(): argument 1 (text) must be 'string'" )
	if( sgs_ItemType( C, 1 ) != SVT_OBJECT || !sgs_GetStackItem( C, 1, &fontvar )
		|| fontvar.data.O->iface != font_iface )
		_WARN( "draw_text_line(): argument 2 (font) has wrong type (must be 'font')" )
	if( !sgs_ParseInt( C, 2, &X ) )
		_WARN( "draw_text_line(): could not parse argument 3 (X position)" )
	if( !sgs_ParseInt( C, 3, &Y ) )
		_WARN( "draw_text_line(): could not parse argument 4 (Y position)" )
	if( !stdlib_tocolor4( C, 4, color ) )
		_WARN( "draw_text_line(): could not parse argument 5 (color)" )
	
	ssfont = (ss_font*) fontvar.data.O->data;
	if( !ssfont->loaded )
	{
		sgs_Printf( C, SGS_WARNING, "draw_text(): unloaded font detected" );
		goto cleanup;
	}
	ss_int_drawtext_line( ssfont, C, str, strsize, X, Y, 0x7fffffff, color );

end:
	sgs_PushBool( C, ret );
	return 1;
cleanup:
	ret = 0;
	goto end;
}



int ss_set_cliprect( SGS_CTX )
{
	sgs_Integer x1, x2, y1, y2;
	if( sgs_StackSize( C ) == 1 &&
		sgs_ItemType( C, 0 ) == SVT_NULL )
	{
		glDisable( GL_SCISSOR_TEST );
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
			_WARN( "set_cliprect(): invalid (negative) width and/or height" )
		glScissor( x1, g_height - y2, x2 - x1, y2 - y1 );
		glEnable( GL_SCISSOR_TEST );
		sgs_PushBool( C, 1 );
		return 1;
	}
	else
		_WARN( "set_cliprect(): unexpected arguments; function expects null or 4 int values" )
}



sgs_RegIntConst gl_ints[] =
{
	/* GL draw modes */
	IC( GL_POINTS ),
	IC( GL_LINES ),
	IC( GL_LINE_STRIP ),
	IC( GL_TRIANGLES ),
	IC( GL_TRIANGLE_FAN ),
	IC( GL_TRIANGLE_STRIP ),
	IC( GL_QUADS ),
};

sgs_RegFuncConst gl_funcs[] =
{
	FN( create_texture ),
	FN( draw ),
	FN( create_font ),
	FN( draw_text_line ),
	FN( is_font ),
	FN( set_camera ),
	FN( set_cliprect ),
};

const char* gl_init = "global _Gtex = {}, _Gfonts = {};";

int sgs_InitGL( SGS_CTX )
{
	int ret;

	FT_Init_FreeType( &g_ftlib );

	ret = sgs_RegIntConsts( C, gl_ints, ARRAY_SIZE( gl_ints ) );
	if( ret != SGS_SUCCESS ) return ret;
	ret = sgs_RegFuncConsts( C, gl_funcs, ARRAY_SIZE( gl_funcs ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	ret = sgs_ExecString( C, gl_init );
	if( ret != SGS_SUCCESS ) return ret;
	
	return SGS_SUCCESS;
}

