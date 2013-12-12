
#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define SGS_INTERNAL

#include "../sgscript/src/sgs_util.h"
#undef ARRAY_SIZE

#include "ss_main.h"

#define FN( f ) { #f, ss_##f }
#define IC( i ) { #i, i }
#define _WARN( err ) return sgs_Printf( C, SGS_WARNING, err );




FT_Library g_ftlib;


#ifdef SS_USED3D
#define PT_POINTS D3DPT_POINTLIST
#define PT_LINES D3DPT_LINELIST
#define PT_LINE_STRIP D3DPT_LINESTRIP
#define PT_TRIANGLES D3DPT_TRIANGLELIST
#define PT_TRIANGLE_FAN D3DPT_TRIANGLEFAN
#define PT_TRIANGLE_STRIP D3DPT_TRIANGLESTRIP
#define PT_QUADS 10

#else
#define PT_POINTS GL_POINTS
#define PT_LINES GL_LINES
#define PT_LINE_STRIP GL_LINE_STRIP
#define PT_TRIANGLES GL_TRIANGLES
#define PT_TRIANGLE_FAN GL_TRIANGLE_FAN
#define PT_TRIANGLE_STRIP GL_TRIANGLE_STRIP
#define PT_QUADS GL_QUADS

#endif




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


#define TEXHDR sgs_Texture* tex = (sgs_Texture*) data->data

int sstex_destruct( SGS_CTX, sgs_VarObj* data, int dco )
{
	TEXHDR;
#ifndef SS_USED3D
	glDeleteTextures( 1, &tex->id );
#else
	IDirect3DResource9_Release( tex->obj );
#endif
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

sgs_ObjCallback tex_iface[] =
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
		{ "mipmaps", CT_MIPMAPS },
		FSI_LAST
	};
	
	if( argc < 1 || argc > 2 )
		_WARN( "create_texture() - unexpected arguments; function expects 1-2 arguments: (image|string)[, string]" )
	
	flags = sgs_GetFlagString( C, 1, flagitems );
	
	sgs_PushItem( C, 0 ); /* NAME [FLAGS] NAME */
	
	if( sgs_ItemType( C, 0 ) == SVT_STRING )
	{
		bystr = 1;
		
		/* check if image already loaded */
		sgs_PushString( C, "|" ); /* NAME [FLAGS] NAME "|" */
		sgs_PushInt( C, flags ); /* NAME [FLAGS] NAME "\0" INT_FLAGS */
		sgs_StringMultiConcat( C, 3 ); /* NAME [FLAGS] KEY */
		
		sgs_PushGlobal( C, "_Gtex" ); /* NAME [FLAGS] KEY _Gtex */
		if( sgs_PushIndex( C, -1, -2 ) == SGS_SUCCESS )
		{
			/* found it! */
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
		sgs_Texture* tt = (sgs_Texture*) sgs_PushObjectIPA( C, sizeof(sgs_Texture), tex_iface );
		tt->flags = flags;
		tt->width = ii->width;
		tt->height = ii->height;
		
#ifdef SS_USED3D
		{
			int miplev = 1, i, y;
			sgs_Image* pdii = ii, *pii;
			IDirect3DTexture9* tex = NULL;
			if( flags & CT_MIPMAPS )
			{
				int sz = ii->width > ii->height ? ii->width : ii->height;
				while( sz > 1 )
				{
					sz /= 2;
					miplev++;
				}
			}
			IDirect3DDevice9_CreateTexture( GD3DDev, ii->width, ii->height,
				miplev, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, NULL );
			tt->obj = (IDirect3DBaseTexture9*) tex;
			for( i = 0; i < miplev; ++i )
			{
				pii = pdii;
				D3DLOCKED_RECT lr;
				IDirect3DTexture9_LockRect( tex, i, &lr, NULL, D3DLOCK_DISCARD );
				for( y = 0; y < pdii->height; ++y )
					memcpy( ((uint8_t*)lr.pBits) + lr.Pitch * y, pdii->data + pdii->width * 4 * y, pdii->width * 4 );
				IDirect3DTexture9_UnlockRect( tex, i );
				if( i < miplev-1 )
					pdii = sgs_ImageDS2X( pdii, C );
				if( pii != ii )
					sgs_DeleteImage( pii, C );
			}
		}
		
#else
		glGenTextures( 1, &tt->id );
		glBindTexture( GL_TEXTURE_2D, tt->id );
		
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
#ifndef GL_BGRA
# define GL_BGRA 0x80E1
#endif
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, ii->width, ii->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, ii->data );
		if( flags & CT_MIPMAPS )
		{
			int miplev = 0;
			int more = ii->width > 1 || ii->height > 1;
			sgs_Image* pdii = ii;
			while( more )
			{
				sgs_Image* dii = sgs_ImageDS2X( pdii, C );
				if( pdii != ii )
					sgs_DeleteImage( pdii, C );
				pdii = dii;
				more = dii->width > 1 || dii->height > 1;
				glTexImage2D( GL_TEXTURE_2D, ++miplev, GL_RGBA, dii->width,
					dii->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, dii->data );
			}
			if( pdii != ii )
				sgs_DeleteImage( pdii, C );
		}
		
		if( flags & CT_HREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		if( flags & CT_VREPEAT ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flags & CT_NOLERP ? GL_NEAREST : GL_LINEAR );
		{
			GLuint minf = flags & CT_MIPMAPS ?
				( flags & CT_NOLERP ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR ) :
				( flags & CT_NOLERP ? GL_NEAREST : GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minf );
		}
		
#endif
	}
	
	/* IMAGE [FLAGS] [KEY](if bystr) TEXTURE */
	
	/* texture key at position -2 */
	if( bystr )
	{
		sgs_PushGlobal( C, "_Gtex" ); /* IMAGE [FLAGS] KEY TEXTURE _Gtex */
		sgs_PushItem( C, -2 );
		sgs_StoreIndex( C, -2, -1 );
		sgs_Pop( C, 1 ); /* IMAGE [FLAGS] KEY TEXTURE */
	}
	
	return 1;
}


#ifndef SS_USED3D
GLuint sgs_GetTextureId( SGS_CTX, sgs_Variable* var )
{
	if( BASETYPE(var->type) != SVT_OBJECT || var->data.O->iface != tex_iface )
		return 0;
	
	return ((sgs_Texture*) var->data.O->data)->id;
}

#else
IDirect3DBaseTexture9* sgs_GetTexture( SGS_CTX, sgs_Variable* var )
{
	if( BASETYPE(var->type) != SVT_OBJECT || var->data.O->iface != tex_iface )
		return 0;
	
	return ((sgs_Texture*) var->data.O->data)->obj;
}

#endif


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
const char* _parse_floatvec( SGS_CTX, int stkitem, float* out, int numcomp )
{
	if( sgs_ParseVec2( C, stkitem, out, 0 ) )
		return NULL;
	
	if( sgs_ItemTypeExt( C, stkitem ) == VTC_ARRAY )
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
		
		return NULL;
	}
	
	return "item was not a vector or array of floats";
}
const char* _parse_floatbuf( SGS_CTX, sgs_Variable* var, floatbuf* out, int numcomp, float* defcomp, int arr )
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
		if( !out->data )
		{
			out->data = sgs_Alloc_n( float, out->size );
			out->my = 1;
		}
		memcpy( out->data, defcomp, numcomp * sizeof(float) );
		res = _parse_floatvec( C, -1, out->data, numcomp );
		if( res && out->my )
		{
			sgs_Dealloc( out->data );
			out->my = 0;
		}
		sgs_Pop( C, 1 );
		return res;
	}
	
	if( var->type != VTC_ARRAY )
	{
		sgs_Pop( C, 1 );
		return "array expected";
	}
	
	asz = sgs_ArraySize( C, -1 );
	out->cnt = asz;
	out->size = asz * numcomp;
	out->data = sgs_Alloc_n( float, out->size );
	
	off = out->data;
	for( i = 0; i < asz; ++i )
	{
		const char* subres;
		if( sgs_PushNumIndex( C, -1, i ) || sgs_ItemType( C, -1 ) != SVT_OBJECT )
		{
			sgs_Dealloc( out->data );
			sgs_Pop( C, sgs_StackSize( C ) - ssz );
			return "element was not an object";
		}
		
		memcpy( off, defcomp, numcomp * sizeof(float) );
		
		subres = _parse_floatvec( C, -1, off, numcomp );
		sgs_Pop( C, 1 );
		
		if( subres )
		{
			sgs_Dealloc( out->data );
			sgs_Pop( C, 1 );
			return subres;
		}
		
		off += numcomp;
	}
	
	out->my = 1;
	
	sgs_Pop( C, 1 );
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
			*outmode = PT_QUADS;
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
			*outmode = PT_QUADS;
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
				mtx[ 0 ] = ca * sclx; mtx[ 1 ] = -sa * scly; mtx[ 3 ] = posx;
				mtx[ 4 ] = sa * sclx; mtx[ 5 ] = ca * scly; mtx[ 7 ] = posy;
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

typedef struct _ssvtx
{
	float pos[ 3 ];
	uint32_t col;
	float tex[ 2 ];
	float padding[2];
}
ssvtx;

uint32_t col4f_pack( float* col )
{
#define MAX( a, b ) ((a)>(b)?(a):(b))
#define MIN( a, b ) ((a)<(b)?(a):(b))
	float r = col[0], g = col[1], b = col[2], a = col[3];
	uint32_t ir = r * 255, ig = g * 255, ib = b * 255, ia = a * 255;
	ir = MAX( 0, MIN( 255, ir ) ); ig = MAX( 0, MIN( 255, ig ) );
	ib = MAX( 0, MIN( 255, ib ) ); ia = MAX( 0, MIN( 255, ia ) );
#ifdef SS_USED3D
	return D3DCOLOR_ARGB( ia, ir, ig, ib );
#else
	return ir | (ig<<8) | (ib<<16) | (ia<<24);
#endif
#undef MIN
#undef MAX
}

uint32_t getprimitivecount( int mode, uint32_t vcount )
{
	switch( mode )
	{
	case PT_POINTS: return vcount;
	case PT_LINES: return vcount / 2;
	case PT_LINE_STRIP: return vcount - 1;
	case PT_TRIANGLES: return vcount / 3;
	case PT_TRIANGLE_FAN: return vcount - 2;
	case PT_TRIANGLE_STRIP: return vcount - 2;
	case PT_QUADS: return vcount / 4;
	}
	return 0;
}

int ss_draw( SGS_CTX )
{
	MemBuf B = membuf_create();
	ssvtx tmp = { { 0, 0, 0 }, 0xffffffff, { 0, 0 }, {0,0} };
	
	float *tf, *cc, *vp, *vt, *vc, tox = 0, toy = 0;
	int mode = PT_TRIANGLES, ret = 1;
#ifdef SS_USED3D
	float mtxbk[ 16 ];
	IDirect3DBaseTexture9* texobj = NULL;
#else
	GLuint texid = 0;
#endif
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
#ifdef SS_USED3D
		texobj = sgs_GetTexture( C, mi[0].var );
		if( !texobj )
#else
		texid = sgs_GetTextureId( C, mi[0].var );
		if( !texid )
#endif
		{
			sgs_Printf( C, SGS_WARNING, "draw(): could not use texture" );
		}
	}
	
#ifdef SS_USED3D
	IDirect3DDevice9_SetTexture( GD3DDev, 0, texobj );
	if( texobj )
	{
		sgs_Texture* tex = (sgs_Texture*) mi[0].var->data.O->data;
		int lin = !( tex->flags & CT_NOLERP );
		int mip = ( tex->flags & CT_MIPMAPS );
		int hr = ( tex->flags & CT_HREPEAT );
		int vr = ( tex->flags & CT_VREPEAT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MINFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MAGFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MIPFILTER, mip ? ( lin ? D3DTEXF_LINEAR : D3DTEXF_POINT ) : D3DTEXF_NONE );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_ADDRESSU, hr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_ADDRESSV, vr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
		tox = 0.5f / tex->width;
		toy = 0.5f / tex->height;
	}
	
	IDirect3DDevice9_GetTransform( GD3DDev, D3DTS_WORLD, (D3DMATRIX*) mtxbk );

#else
	if( texid )
	{
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texid );
	}
	else
		glDisable( GL_TEXTURE_2D );
	
	glMatrixMode( GL_MODELVIEW );
	
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

#endif
	
	cc = icol.data;
	for( tf = xform.data; tf < xform.data + xform.size; tf += 16 )
	{
#ifdef SS_USED3D
		IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_WORLD, (D3DMATRIX*) tf );

#else
		glPushMatrix();
		glMultMatrixf( tf );

#endif
		
		if( cc < icol.data + icol.size )
		{
			/* TODO: color multiplication */
			tmp.col = col4f_pack( cc );
			cc += 4;
		}
		
		membuf_resize( &B, C, 0 );
		
		vt = vtex.data;
		vc = vcol.data;
		for( vp = vert.data; vp < vert.data + vert.size; vp += 2 )
		{
			if( vt < vtex.data + vtex.size )
			{
				tmp.tex[0] = vt[0] + tox;
				tmp.tex[1] = 1 - vt[1] + toy;
				vt += 2;
			}
			if( vc < vcol.data + vcol.size )
			{
				tmp.col = col4f_pack( vc );
				vc += 4;
			}
			tmp.pos[0] = vp[0];
			tmp.pos[1] = vp[1];
			membuf_appbuf( &B, C, &tmp, sizeof(tmp) );
		}
		
#ifdef SS_USED3D
		IDirect3DDevice9_SetFVF( GD3DDev, D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE );
		if( mode == PT_QUADS )
		{
			int i, cnt = B.size / sizeof(ssvtx) - 3;
			for( i = 0; i < cnt; i += 4 )
			{
				IDirect3DDevice9_DrawPrimitiveUP( GD3DDev, D3DPT_TRIANGLEFAN,
					2, B.ptr + sizeof(ssvtx) * i, sizeof(ssvtx) );
			}
		}
		else
		{
			IDirect3DDevice9_DrawPrimitiveUP( GD3DDev, mode,
				getprimitivecount( mode, B.size / sizeof(ssvtx) ),
				B.ptr, sizeof(ssvtx) );
		}
	}
	
	IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_WORLD, (D3DMATRIX*) mtxbk );

#else
		/* TODO: fix hardcoded offsets, maybe */
		glVertexPointer( 3, GL_FLOAT, sizeof(ssvtx), B.ptr );
		glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(ssvtx), B.ptr + 12 );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(ssvtx), B.ptr + 16 );
		
		glDrawArrays( mode, 0, B.size / sizeof(ssvtx) );
		
		glPopMatrix();
	}
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );

#endif
	
	membuf_destroy( &B, C );
	
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



#ifndef GL_FLOAT
#  define GL_FLOAT 1
#  define GL_UNSIGNED_BYTE 2
#endif

typedef struct _vtxfmt vtxfmt;
struct _vtxfmt
{
	int size;
	/* use / offset / type / count / size / order */
	uint32_t P[ 6 ];
	uint32_t T[ 6 ];
	uint32_t C[ 6 ];
	uint32_t N[ 6 ];
	
#ifdef SS_USED3D
	IDirect3DVertexDeclaration9* vdecl;
#endif
};


#ifdef SS_USED3D
static int vd_make_typecount( int type, int count )
{
	if( type == GL_FLOAT && count == 1 ) return D3DDECLTYPE_FLOAT1;
	if( type == GL_FLOAT && count == 2 ) return D3DDECLTYPE_FLOAT2;
	if( type == GL_FLOAT && count == 3 ) return D3DDECLTYPE_FLOAT3;
	if( type == GL_FLOAT && count == 4 ) return D3DDECLTYPE_FLOAT4;
	if( type == GL_UNSIGNED_BYTE && count == 4 ) return D3DDECLTYPE_D3DCOLOR;
	return 0;
}

static void initialize_optimized_format( vtxfmt* F )
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
	
	F->vdecl = NULL;
	hr = IDirect3DDevice9_CreateVertexDeclaration( GD3DDev, els, &F->vdecl );
	sgs_BreakIf( FAILED( hr ) && "vertex declaration creation failed" );
}

static void free_optimized_format( vtxfmt* F )
{
	IDirect3DVertexDeclaration9_Release( F->vdecl );
}

#else
#define initialize_optimized_format(x)
#define free_optimized_format(x)

#endif


int ss_vertex_format_destruct( SGS_CTX, sgs_VarObj* data, int dco )
{
	free_optimized_format( (vtxfmt*) data->data );
	return SGS_SUCCESS;
}

sgs_ObjCallback vertex_format_iface[] =
{
	SOP_DESTRUCT, ss_vertex_format_destruct,
	SOP_END,
};

int ss_make_vertex_format( SGS_CTX )
{
	char *fmt;
	sgs_SizeVal fmtsize;
	
	SGSFN( "make_vertex_format" );
	
	if( sgs_StackSize( C ) != 1 ||
		!sgs_ParseString( C, 0, &fmt, &fmtsize ) )
		_WARN( "unexpected arguments; "
			"function expects 1 argument: string" )
	
	{
		vtxfmt* ef;
		vtxfmt F = {0};
		char* fmtend = fmt + fmtsize;
		int order = 0;
		
		int aligned = fmt < fmtend && *fmt == '|';
		if( aligned )
			fmt++;
		
		while( fmt < fmtend - 2 )
		{
			int isz = 0;
			uint32_t* dst;
			
			int ch = fmt[0], type = fmt[1], cnt = fmt[2];
			if( ch != 'p' && ch != 't' && ch != 'c' && ch != 'n' )
				_WARN( "wrong channel specifier (not p/t/c/n)" )
			if( type != 'f'  && type != 'c' )
				_WARN( "wrong type specifier (not f/c)" )
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
			if( type == 'f' ){ isz = 4; dst[2] = GL_FLOAT; }
			else if( type == 'c' ){ isz = 1; dst[2] = GL_UNSIGNED_BYTE; }
			
			if( cnt == '1' ) dst[3] = 1;
			else if( cnt == '2' ) dst[3] = 2;
			else if( cnt == '3' ) dst[3] = 3;
			else if( cnt == '4' ) dst[3] = 4;
			
			if( ch == 'n' && cnt != '3' )
				_WARN( "normals must have 3 components" )
			
			F.size += dst[4] = isz * dst[3];
			dst[5] = ++order;
			
			fmt += 3;
		}
		
		if( !F.size )
			_WARN( "empty vertex format" )
		
		if( aligned )
			F.size = ( ( F.size - 1 ) / 32 + 1 ) * 32;
		
		ef = (vtxfmt*) sgs_PushObjectIPA( C, sizeof(F), vertex_format_iface );
		memcpy( ef, &F, sizeof(F) );
		initialize_optimized_format( ef );
		return 1;
	}
}

/*
	- texture
	- format
	- data
*/
int ss_draw_packed( SGS_CTX )
{
	sgs_Integer start, count, type;
	sgs_Texture* T = NULL;
	vtxfmt* F;
	char *data, *idcs = NULL;
	sgs_SizeVal datasize, idcsize = 0;
	int ssz = sgs_StackSize( C );
	
	SGSFN( "draw_packed" );
	
	if( !( ssz == 6 || ssz == 7 ) ||
		!( sgs_ItemType( C, 0 ) == SVT_NULL || sgs_IsObject( C, 0, tex_iface ) ) ||
		!sgs_IsObject( C, 1, vertex_format_iface ) ||
		!sgs_ParseString( C, 2, &data, &datasize ) ||
		!sgs_ParseInt( C, 3, &start ) ||
		!sgs_ParseInt( C, 4, &count ) ||
		!sgs_ParseInt( C, 5, &type ) ||
		( ssz >=7 && !sgs_ParseString( C, 6, &idcs, &idcsize ) )
		)
		_WARN( "unexpected arguments; function expects 6 arguments: "
			"texture|null, format, string, int, int, int, bool" )
	
	F = (vtxfmt*) sgs_GetObjectData( C, 1 );
	if( sgs_IsObject( C, 0, tex_iface ) )
		T = (sgs_Texture*) sgs_GetObjectData( C, 0 );
	
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
	
#ifdef SS_USED3D
	IDirect3DDevice9_SetTexture( GD3DDev, 0, T ? T->obj : NULL );
	if( T && T->obj )
	{
		sgs_Texture* tex = T;
		int lin = !( tex->flags & CT_NOLERP );
		int mip = ( tex->flags & CT_MIPMAPS );
		int hr = ( tex->flags & CT_HREPEAT );
		int vr = ( tex->flags & CT_VREPEAT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MINFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MAGFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MIPFILTER, mip ? ( lin ? D3DTEXF_LINEAR : D3DTEXF_POINT ) : D3DTEXF_NONE );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_ADDRESSU, hr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_ADDRESSV, vr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
	}
	
	IDirect3DDevice9_SetVertexDeclaration( GD3DDev, F->vdecl );
	if( idcs )
		IDirect3DDevice9_DrawIndexedPrimitiveUP( GD3DDev, type, 0, count,
			getprimitivecount( type, count ), idcs + start * 2, D3DFMT_INDEX16,
			data, F->size );
	else
		IDirect3DDevice9_DrawPrimitiveUP( GD3DDev, type,
			getprimitivecount( type, count ),
			data, F->size );
	IDirect3DDevice9_SetVertexDeclaration( GD3DDev, NULL );

#else
	if( F->P[0] ) glVertexPointer( F->P[3], F->P[2], F->size, data + F->P[1] );
	if( F->T[0] ) glTexCoordPointer( F->T[3], F->T[2], F->size, data + F->T[1] );
	if( F->C[0] ) glColorPointer( F->C[3], F->C[2], F->size, data + F->C[1] );
	if( F->N[0] ) glNormalPointer( F->N[2], F->size, data + F->N[1] );
	
	if( T )
	{
		glBindTexture( GL_TEXTURE_2D, T->id );
		glEnable( GL_TEXTURE_2D );
	}
	else
		glDisable( GL_TEXTURE_2D );
	
	if( F->P[0] ) glEnableClientState( GL_VERTEX_ARRAY );
	if( F->T[0] ) glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	if( F->C[0] ) glEnableClientState( GL_COLOR_ARRAY );
	if( F->N[0] ) glEnableClientState( GL_NORMAL_ARRAY );
	
	glColor4f( 1, 1, 1, 1 );
	if( idcs )
		glDrawElements( type, count, GL_UNSIGNED_SHORT, idcs + start * 2 );
	else
		glDrawArrays( type, start, count );
	
	if( F->P[0] ) glDisableClientState( GL_VERTEX_ARRAY );
	if( F->T[0] ) glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	if( F->C[0] ) glDisableClientState( GL_COLOR_ARRAY );
	if( F->N[0] ) glDisableClientState( GL_NORMAL_ARRAY );
	
#endif
	
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

static sgs_ObjCallback renderbuf_iface[];


#define RB_IHDR( funcname ) \
	int method_call = sgs_Method( C ); \
	sgs_FuncName( C, method_call ? "renderbuf." #funcname : "renderbuf_" #funcname ); \
	if( !sgs_IsObject( C, 0, renderbuf_iface ) ) \
		return sgs_ArgErrorExt( C, 0, method_call, "renderbuf", "" ); \
	ss_renderbuf* rb = (ss_renderbuf*) sgs_GetObjectData( C, 0 );

/* .begin() */
static int ss_renderbuf_begin( SGS_CTX )
{
	RB_IHDR( begin );
	
	membuf_resize( &rb->B, C, 0 );
	sgs_SetStackSize( C, 1 );
	return 1;
}

/* .reserve( int bytes ) */
static int ss_renderbuf_reserve( SGS_CTX )
{
	sgs_SizeVal numbytes;
	
	RB_IHDR( reserve );
	if( !sgs_LoadArgs( C, "@>l", &numbytes ) )
		return 0;
	
	membuf_reserve( &rb->B, C, numbytes );
	sgs_SetStackSize( C, 1 );
	return 1;
}

/* .f( real{1,64} ) - floats */
static int ss_renderbuf_f( SGS_CTX )
{
	int argc, i;
	float f[64];
	
	RB_IHDR( f );
	argc = sgs_StackSize( C ) - 1;
	if( argc > 0 )
	{
		if( argc > 64 )
			argc = 64;
		for( i = 1; i <= argc; ++i )
			f[i-1] = sgs_ToReal( C, i );
		
		membuf_appbuf( &rb->B, C, f, sizeof(*f)*argc );
	}
	sgs_SetStackSize( C, 1 );
	return 1;
}

/* .b( int{1,64} ) - bytes */
static int ss_renderbuf_b( SGS_CTX )
{
	int argc, i;
	uint8_t b[64];
	
	RB_IHDR( b );
	argc = sgs_StackSize( C ) - 1;
	if( argc > 0 )
	{
		if( argc > 64 )
			argc = 64;
		for( i = 1; i <= argc; ++i )
			b[i-1] = (uint8_t) sgs_ToInt( C, i );
		
		membuf_appbuf( &rb->B, C, b, sizeof(*b)*argc );
	}
	sgs_SetStackSize( C, 1 );
	return 1;
}

/* .cf2b( real{1,64} ) - clamped float to byte */
static int ss_renderbuf_cf2b( SGS_CTX )
{
	int argc, i;
	uint8_t b[64];
	
	RB_IHDR( cf2b );
	argc = sgs_StackSize( C ) - 1;
	if( argc > 0 )
	{
		if( argc > 64 )
			argc = 64;
		for( i = 1; i <= argc; ++i )
		{
			float f = sgs_ToReal( C, i );
			if( f < 0 ) f = 0;
			if( f > 1 ) f = 1;
			b[i-1] = f * 255;
		}
		
		membuf_appbuf( &rb->B, C, b, sizeof(*b)*argc );
	}
	sgs_SetStackSize( C, 1 );
	return 1;
}

/* .pad( int ) - padding */
static int ss_renderbuf_pad( SGS_CTX )
{
	sgs_SizeVal numbytes;
	
	RB_IHDR( pad );
	if( !sgs_LoadArgs( C, "@>l", &numbytes ) )
		return 0;
	
	if( rb->B.size + numbytes < 0 )
		return sgs_Printf( C, SGS_WARNING, "padding so big that it's negative (overflow)" );
	
	membuf_resize( &rb->B, C, rb->B.size + numbytes );
	sgs_SetStackSize( C, 1 );
	return 1;
}

/* .draw( texture|null, vertex_format, int start, int count, int type ) */
static int ss_renderbuf_draw( SGS_CTX )
{
	sgs_Texture* T = NULL;
	vtxfmt* F = NULL;
	sgs_SizeVal start, count, type;
	char* data;
	
	RB_IHDR( draw );
	if( !sgs_LoadArgs( C, "@>>olll", vertex_format_iface, &F, &start, &count, &type ) )
		return 0;
	if( sgs_ItemType( C, 1 ) != SVT_NULL )
	{
		if( !sgs_IsObject( C, 1, tex_iface ) )
			return sgs_ArgErrorExt( C, 1, 1, "texture or null", "" );
		T = (sgs_Texture*) sgs_GetObjectData( C, 1 );
	}
	data = rb->B.ptr;
	
	if( F->size * (start+count) > rb->B.size )
		_WARN( "not enough data to draw with given start/count values" )
	
	/* DRAWING CODE */
#ifdef SS_USED3D
	IDirect3DDevice9_SetTexture( GD3DDev, 0, T ? T->obj : NULL );
	if( T && T->obj )
	{
		sgs_Texture* tex = T;
		int lin = !( tex->flags & CT_NOLERP );
		int mip = ( tex->flags & CT_MIPMAPS );
		int hr = ( tex->flags & CT_HREPEAT );
		int vr = ( tex->flags & CT_VREPEAT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MINFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MAGFILTER, lin ? D3DTEXF_LINEAR : D3DTEXF_POINT );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_MIPFILTER, mip ? ( lin ? D3DTEXF_LINEAR : D3DTEXF_POINT ) : D3DTEXF_NONE );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_ADDRESSU, hr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
		IDirect3DDevice9_SetSamplerState( GD3DDev, 0, D3DSAMP_ADDRESSV, vr ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP );
	}
	
	IDirect3DDevice9_SetVertexDeclaration( GD3DDev, F->vdecl );
	IDirect3DDevice9_DrawPrimitiveUP( GD3DDev, type,
		getprimitivecount( type, count ),
		data, F->size );
	IDirect3DDevice9_SetVertexDeclaration( GD3DDev, NULL );

#else
	if( F->P[0] ) glVertexPointer( F->P[3], F->P[2], F->size, data + F->P[1] );
	if( F->T[0] ) glTexCoordPointer( F->T[3], F->T[2], F->size, data + F->T[1] );
	if( F->C[0] ) glColorPointer( F->C[3], F->C[2], F->size, data + F->C[1] );
	if( F->N[0] ) glNormalPointer( F->N[2], F->size, data + F->N[1] );
	
	if( T )
	{
		glBindTexture( GL_TEXTURE_2D, T->id );
		glEnable( GL_TEXTURE_2D );
	}
	else
		glDisable( GL_TEXTURE_2D );
	
	if( F->P[0] ) glEnableClientState( GL_VERTEX_ARRAY );
	if( F->T[0] ) glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	if( F->C[0] ) glEnableClientState( GL_COLOR_ARRAY );
	if( F->N[0] ) glEnableClientState( GL_NORMAL_ARRAY );
	
	glColor4f( 1, 1, 1, 1 );
	glDrawArrays( type, start, count );
	
	if( F->P[0] ) glDisableClientState( GL_VERTEX_ARRAY );
	if( F->T[0] ) glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	if( F->C[0] ) glDisableClientState( GL_COLOR_ARRAY );
	if( F->N[0] ) glDisableClientState( GL_NORMAL_ARRAY );
	
#endif
	
	sgs_SetStackSize( C, 1 );
	return 1;
}


#define RBHDR ss_renderbuf* rb = (ss_renderbuf*) data->data

static int ss_renderbuf_destruct( SGS_CTX, sgs_VarObj* data, int unused )
{
	RBHDR;
	UNUSED( unused );
	membuf_destroy( &rb->B, C );
	return SGS_SUCCESS;
}

static int ss_renderbuf_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* str;
	UNUSED( isprop );
	if( sgs_ParseString( C, 0, &str, NULL ) )
	{
		if( !strcmp( str, "begin" ) ){ sgs_PushCFunction( C, ss_renderbuf_begin ); return SGS_SUCCESS; }
		if( !strcmp( str, "reserve" ) ){ sgs_PushCFunction( C, ss_renderbuf_reserve ); return SGS_SUCCESS; }
		if( !strcmp( str, "f" ) ){ sgs_PushCFunction( C, ss_renderbuf_f ); return SGS_SUCCESS; }
		if( !strcmp( str, "b" ) ){ sgs_PushCFunction( C, ss_renderbuf_b ); return SGS_SUCCESS; }
		if( !strcmp( str, "cf2b" ) ){ sgs_PushCFunction( C, ss_renderbuf_cf2b ); return SGS_SUCCESS; }
		if( !strcmp( str, "pad" ) ){ sgs_PushCFunction( C, ss_renderbuf_pad ); return SGS_SUCCESS; }
		if( !strcmp( str, "draw" ) ){ sgs_PushCFunction( C, ss_renderbuf_draw ); return SGS_SUCCESS; }
		return SGS_ENOTFND;
	}
	return SGS_EINVAL;
}

static int ss_renderbuf_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_CONVOP_TOTYPE )
	{
		UNUSED( data );
		sgs_PushString( C, "renderbuf" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static sgs_ObjCallback renderbuf_iface[] =
{
	SOP_GETINDEX, ss_renderbuf_getindex,
	SOP_DESTRUCT, ss_renderbuf_destruct,
	SOP_CONVERT, ss_renderbuf_convert,
	SOP_END
};

static int ss_create_renderbuf( SGS_CTX )
{
	ss_renderbuf* rb = (ss_renderbuf*) sgs_PushObjectIPA( C, sizeof(ss_renderbuf), renderbuf_iface );
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


typedef float mat4x4[4][4];
mat4x4 matrices[8];
int curmtx = 0;

int ss_matrix_push( SGS_CTX )
{
	int set = 0;
	float mtx[ 16 ] = {0};
	int ssz = sgs_StackSize( C );
	
	SGSFN( "matrix_push" );
	
	if( ssz < 1 || ssz > 2 ||
		_parse_floatvec( C, 0, mtx, 16 ) ||
		( ssz >= 2 && !sgs_ParseBool( C, 0, &set ) ) )
		_WARN( "unexpected arguments; "
			"function expects 1-2 arguments: array(real x16)[, bool]" )
	
#ifdef SS_USED3D
	{
		if( curmtx >= 8 )
			return 0;
		float *mtxin = (float*) matrices[ curmtx++ ], omtx[ 16 ];
		IDirect3DDevice9_GetTransform( GD3DDev, D3DTS_WORLD, (D3DMATRIX*) mtxin );
		if( set )
			memcpy( omtx, mtx, sizeof(float)*16 );
		else
			Matrix4x4MultiplyBy4x4( (float (*)[4]) mtx, (float (*)[4]) mtxin, (float (*)[4]) omtx );
		IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_WORLD, (D3DMATRIX*) omtx );
	}
	
#else
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	_mtx_transpose( mtx );
	if( set )
		glLoadMatrixf( mtx );
	else
		glMultMatrixf( mtx );
	
#endif
	
	return 0;
}

int ss_matrix_pop( SGS_CTX )
{
	SGSFN( "matrix_pop" );
	
	if( sgs_StackSize( C ) )
		_WARN( "unexpected arguments" )
	
#ifdef SS_USED3D
	if( curmtx > 0 )
	{
		curmtx--;
		IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_WORLD, (D3DMATRIX*) matrices[ curmtx ] );
	}
	
#else
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	
#endif
	
	return 0;
}

int ss_set_depth_test( SGS_CTX )
{
	int set;
	
	SGSFN( "set_depth_test" );
	
	if( sgs_StackSize( C ) != 1 ||
		!sgs_ParseBool( C, 0, &set ) )
		_WARN( "unexpected arguments; function expects 1 argument: bool" )
	
#ifdef SS_USED3D
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_ZENABLE, set );
	
#else
	if( set )
		glEnable( GL_DEPTH_TEST );
	else
		glDisable( GL_DEPTH_TEST );
	
#endif
	
	return 0;
}


int ss_set_camera( SGS_CTX )
{
	float mtx[ 16 ] = {0};
	float mtx2[ 16 ] = {0};
	int ssz = sgs_StackSize( C );
	
	SGSFN( "set_camera" );

	if( ssz < 1 || ssz > 2 ||
		_parse_floatvec( C, 0, mtx, 16 ) ||
		( ssz >= 2 && _parse_floatvec( C, 1, mtx2, 16 ) ) )
		_WARN( "expected an array of 16 'real' values" )
	
	_mtx_transpose( mtx );
	
#ifdef SS_USED3D
	IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_VIEW, (D3DMATRIX*) mtx );
	if( ssz < 2 ){ mtx2[0] = 1; mtx2[5] = 1; mtx2[10] = 1; mtx2[15] = 1; }
	else _mtx_transpose( mtx2 );
	IDirect3DDevice9_SetTransform( GD3DDev, D3DTS_PROJECTION, (D3DMATRIX*) mtx2 );
	
#else
	glMatrixMode( GL_PROJECTION );
	if( ssz >= 2 )
	{
		_mtx_transpose( mtx2 );
		glLoadMatrixf( mtx2 );
	}
	else
		glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadMatrixf( mtx );
	
#endif
	return 0;
}


/*
	The font system
*/

sgs_ObjCallback font_iface[];

typedef
struct _ss_glyph
{
	FT_UInt glyph_id;
	int texwidth;
	int texheight;
	int bmoffx;
	int bmoffy;
	int advx;
#ifdef SS_USED3D
	IDirect3DTexture9* texture;
#else
	GLuint texture;
#endif
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


static void fontfreefunc( HTPair* p, void* ud )
{
	SGS_CTX = (sgs_Context*) ud;
	ss_glyph* G = (ss_glyph*) p->ptr;
	if( G->texture )
#ifdef SS_USED3D
		IDirect3DTexture9_Release( G->texture );
#else
		glDeleteTextures( 1, &G->texture );
#endif
	sgs_Dealloc( G );
}

void ss_font_free( ss_font* font, SGS_CTX )
{
	if( font->loaded )
	{
		ht_iterate( &font->glyphs, fontfreefunc, C );
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
		!sgs_IsObject( C, 0, font_iface ) ||
		!( sgs_ItemType( C, 1 ) == SVT_NULL || sgs_ParseInt( C, 1, &a ) ) ||
		!sgs_ParseInt( C, 2, &b ) )
		_WARN( "font::get_advance(): unexpected arguments; "
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

int ss_font_getindex( SGS_CTX, sgs_VarObj* data, int prop )
{
	char* str = sgs_ToString( C, 0 );
	FONTHDR;

	if( 0 == strcmp( str, "size" ) ){ sgs_PushInt( C, font->size ); return SGS_SUCCESS; }
	if( 0 == strcmp( str, "get_advance" ) ){ sgs_PushCFunction( C, ss_fontI_get_advance ); return SGS_SUCCESS; }

	return SGS_ENOTFND;
}

sgs_ObjCallback font_iface[] =
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
		ss_font* fn = (ss_font*) sgs_PushObjectIPA( C, sizeof(ss_font), font_iface );
		fn->loaded = 0;

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
		sgs_PushItem( C, -1 );
		sgs_StoreIndex( C, -3, -4 );
		return 1;
	}
}


ss_glyph* ss_font_create_glyph( ss_font* font, SGS_CTX, uint32_t cp )
{
	int x, y;
	uint8_t* imgdata, *pp;
#ifdef SS_USED3D
	IDirect3DTexture9* tex = NULL;
#else
	GLuint tex = 0;
#endif
	FT_GlyphSlot glyph;
	ss_glyph* G = sgs_Alloc( ss_glyph );
	
	UNUSED(imgdata);
	FT_Load_Char( font->face, cp, 0 );
	glyph = font->face->glyph;
	FT_Render_Glyph( glyph, FT_RENDER_MODE_NORMAL );
	
	if( glyph->bitmap.width * glyph->bitmap.rows )
	{
#ifdef SS_USED3D
		HRESULT hr;
		D3DLOCKED_RECT lr;
		hr = IDirect3DDevice9_CreateTexture( GD3DDev, glyph->bitmap.width,
			glyph->bitmap.rows, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, NULL );
		sgs_BreakIf( tex == NULL || FAILED(hr) );
		IDirect3DTexture9_LockRect( tex, 0, &lr, NULL, D3DLOCK_DISCARD );
		pp = glyph->bitmap.buffer;
		for( y = 0; y < glyph->bitmap.rows; ++y )
		{
			for( x = 0; x < glyph->bitmap.width; ++x )
			{
				int off = y * lr.Pitch;
				((uint8_t*)lr.pBits)[ off + x * 4 ] = 0xff;
				((uint8_t*)lr.pBits)[ off + x * 4 + 1 ] = 0xff;
				((uint8_t*)lr.pBits)[ off + x * 4 + 2 ] = 0xff;
				((uint8_t*)lr.pBits)[ off + x * 4 + 3 ] = pp[ x ];
			}
			pp += glyph->bitmap.pitch;
		}
		IDirect3DTexture9_UnlockRect( tex, 0 );
		
#else
		glGenTextures( 1, &tex );
		glBindTexture( GL_TEXTURE_2D, tex );
		imgdata = sgs_Alloc_n( uint8_t, glyph->bitmap.width * glyph->bitmap.rows * 4 );
		pp = glyph->bitmap.buffer;
		for( y = 0; y < glyph->bitmap.rows; ++y )
		{
			for( x = 0; x < glyph->bitmap.width; ++x )
			{
				int off = y * glyph->bitmap.width * 4;
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
		
#endif
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
	const char* cpc = (const char*) &cp;
	HTPair* p = ht_find( &font->glyphs, cpc, 4, sgs_HashFunc( cpc, 4 ) );
	if( !p || !p->ptr )
	{
		ss_glyph* ng = ss_font_create_glyph( font, C, cp );
		ht_set( &font->glyphs, C, (const char*) &cp, 4, ng );
		return ng;
	}
	else
		return (ss_glyph*) p->ptr;
}

typedef struct _fontvtx
{
	float x,y,z;
	uint32_t col;
	float u,v;
}
fontvtx;

void ss_int_drawtext_line( ss_font* font, SGS_CTX, char* str,
	sgs_SizeVal size, int x, int y, int xto, sgs_Real* color )
{
	int W, H, mx, my, xadv = 0, ret, use_kerning;
	uint32_t previous = 0;
	ss_glyph* G;

#ifdef SS_USED3D
	uint32_t cc = D3DCOLOR_ARGB( ((int)(color[3]*255)),
		((int)(color[0]*255)), ((int)(color[1]*255)), ((int)(color[2]*255)) );
	
#else
	glEnable( GL_TEXTURE_2D );
	glColor4f( color[0], color[1], color[2], color[3] );
	
#endif

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
			
#ifdef SS_USED3D
			{
				float tox = 0.5f / W, toy = 0.5f / H;
				fontvtx vdata[4] = { { mx, my, 0, cc, tox, toy }, { mx, my+H, 0, cc, tox, 1+toy },
					{ mx+W, my+H, 0, cc, 1+tox, 1+toy }, { mx+W, my, 0, cc, 1+tox, toy } };
				IDirect3DDevice9_SetFVF( GD3DDev, D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
				IDirect3DDevice9_SetTexture( GD3DDev, 0,
					(IDirect3DBaseTexture9*) G->texture );
				IDirect3DDevice9_DrawPrimitiveUP( GD3DDev,
					D3DPT_TRIANGLEFAN, 2, vdata, sizeof(fontvtx) );
			}
			
#else
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
#endif
		}

		xadv = G->advx;
	}
}

int ss_is_font( SGS_CTX )
{
	if( sgs_StackSize( C ) != 1 )
		_WARN( "is_font(): unexpected arguments; function expects 1 argument" )

	sgs_PushBool( C, sgs_IsObject( C, 0, font_iface ) );
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
#ifdef SS_USED3D
		IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_SCISSORTESTENABLE, 0 );
#else
		glDisable( GL_SCISSOR_TEST );
#endif
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
#ifdef SS_USED3D
		{
			RECT rect = { x1, y1, x2, y2 };
			IDirect3DDevice9_SetScissorRect( GD3DDev, &rect );
		}
		IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_SCISSORTESTENABLE, 1 );
#else
		glScissor( x1, g_height - y2, x2 - x1, y2 - y1 );
		glEnable( GL_SCISSOR_TEST );
#endif
		sgs_PushBool( C, 1 );
		return 1;
	}
	else
		_WARN( "set_cliprect(): unexpected arguments; function expects null or 4 int values" )
}


int ss_set_culling( SGS_CTX )
{
	sgs_Integer ii;
	if( !sgs_LoadArgs( C, "i", &ii ) )
		return 0;
#ifdef SS_USED3D
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_CULLMODE, ii ? ( ii > 0 ? D3DCULL_CCW : D3DCULL_CW ) : D3DCULL_NONE );
#else
	if( ii )
	{
		glCullFace( ii < 0 ? GL_FRONT : GL_BACK );
		glEnable( GL_CULL_FACE );
	}
	else
		glDisable( GL_CULL_FACE );
#endif
	return 0;
}


int ss_set_blending( SGS_CTX )
{
	sgs_Integer func = 0, src, dst;

#define BLENDOP_ADD 0
#define BLENDOP_SUBTRACT 1
#define BLENDOP_REVERSE_SUBTRACT 2
#define BLENDOP_MIN 3
#define BLENDOP_MAX 4

#define BLEND_ZERO 0
#define BLEND_ONE 1
#define BLEND_SRCCOLOR 2
#define BLEND_INVSRCCOLOR 3
#define BLEND_SRCALPHA 4
#define BLEND_INVSRCALPHA 5
#define BLEND_DESTCOLOR 6
#define BLEND_INVDESTCOLOR 7
#define BLEND_DESTALPHA 8
#define BLEND_INVDESTALPHA 9
#define BLEND_SRCALPHASAT 10
	
	static const int blendfuncs[] =
	{
#ifdef SS_USED3D
		D3DBLENDOP_ADD, D3DBLENDOP_SUBTRACT, D3DBLENDOP_REVSUBTRACT, D3DBLENDOP_MIN, D3DBLENDOP_MAX,
#else
		GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX,
#endif
	};
	static const int blendfactors[] =
	{
#ifdef SS_USED3D
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
#else
		GL_ZERO,
		GL_ONE,
		GL_SRC_COLOR,
		GL_ONE_MINUS_SRC_COLOR,
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA,
		GL_DST_COLOR,
		GL_ONE_MINUS_DST_COLOR,
		GL_DST_ALPHA,
		GL_ONE_MINUS_DST_ALPHA,
		GL_SRC_ALPHA_SATURATE,
#endif
	};
	
	if( !sgs_LoadArgs( C, "iii", &func, &src, &dst ) )
		return 0;
	
	if( func < 0 || func >= ARRAY_SIZE(blendfuncs) )
		return sgs_Printf( C, SGS_WARNING, "wrong blend function" );
	if( src < 0 || src >= ARRAY_SIZE(blendfactors) )
		return sgs_Printf( C, SGS_WARNING, "wrong source blend factor" );
	if( dst < 0 || dst >= ARRAY_SIZE(blendfactors) )
		return sgs_Printf( C, SGS_WARNING, "wrong destination blend factor" );
	
#ifdef SS_USED3D
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_SRCBLEND, blendfactors[ src ] );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_DESTBLEND, blendfactors[ dst ] );
	IDirect3DDevice9_SetRenderState( GD3DDev, D3DRS_BLENDOP, blendfuncs[ func ] );
#else
	glBlendFunc( blendfactors[ src ], blendfactors[ dst ] );
	ss_glBlendEquation( blendfuncs[ func ] );
#endif
	return 0;
}



sgs_RegIntConst gl_ints[] =
{
	/* GL draw modes */
	IC( PT_POINTS ),
	IC( PT_LINES ),
	IC( PT_LINE_STRIP ),
	IC( PT_TRIANGLES ),
	IC( PT_TRIANGLE_FAN ),
	IC( PT_TRIANGLE_STRIP ),
	IC( PT_QUADS ),
	
	/* blending */
	IC( BLENDOP_ADD ),
	IC( BLENDOP_SUBTRACT ),
	IC( BLENDOP_REVERSE_SUBTRACT ),
	IC( BLENDOP_MIN ),
	IC( BLENDOP_MAX ),
	
	IC( BLEND_ZERO ),
	IC( BLEND_ONE ),
	IC( BLEND_SRCCOLOR ),
	IC( BLEND_INVSRCCOLOR ),
	IC( BLEND_SRCALPHA ),
	IC( BLEND_INVSRCALPHA ),
	IC( BLEND_DESTCOLOR ),
	IC( BLEND_INVDESTCOLOR ),
	IC( BLEND_DESTALPHA ),
	IC( BLEND_INVDESTALPHA ),
	IC( BLEND_SRCALPHASAT ),
};

sgs_RegFuncConst gl_funcs[] =
{
	FN( create_texture ),
	FN( draw ),
	FN( make_vertex_format ), FN( draw_packed ),
	FN( create_renderbuf ),
	FN( create_font ), FN( draw_text_line ), FN( is_font ),
	FN( matrix_push ), FN( matrix_pop ),
	FN( set_camera ), FN( set_cliprect ),
	FN( set_depth_test ), FN( set_culling ),
	FN( set_blending ),
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

