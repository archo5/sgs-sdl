
#include <math.h>

#include "ss_main.h"

#define FN( f ) { #f, ss_##f }
#define IC( i ) { #i, i }
#define _WARN( err ) { sgs_Printf( C, SGS_ERROR, -1, err ); return 0; }


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

#define CT_HREPEAT 1
#define CT_VREPEAT 2
#define CT_NOLERP 4
#define CT_MIPMAPS 8

int ss_create_texture( SGS_CTX )
{
	uint32_t flags;
	sgs_Variable var;
	int argc = sgs_StackSize( C );
	
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
	
	var = *sgs_StackItem( C, 0 );
	sgs_PushVariable( C, &var );
	
	if( sgs_ItemType( C, 0 ) == SVT_STRING )
	{
		/* check if image already loaded */
		sgs_PushStringBuf( C, "\0", 1 );
		sgs_PushInt( C, flags );
		sgs_StringMultiConcat( C, 3 );
		
		sgs_GetGlobal( C, "_Gtex" );
		if( sgs_GetIndex( C, &var, sgs_StackItem( C, -1 ), sgs_StackItem( C, -2 ) ) == SGS_SUCCESS )
		{
			/* found it! */
			sgs_PushVariable( C, &var );
			sgs_Release( C, &var );
			return 1;
		}
		
		/* convert string to image */
		{
			int size;
			char *str, *ptr, buf[ 64 ];
			str = sgs_GetStringPtr( C, 0 );
			size = sgs_GetStringSize( C, 0 );
			ptr = str + size;
			while( str <-- ptr )
			{
				if( *ptr == '/' || *ptr == '\\' )
					_WARN( "create_texture() - filename has no extension" );
				if( *ptr == '.' )
					break;
			}
			if( *ptr != '.' )
				_WARN( "create_texture() - filename has no extension" );
			
			sprintf( buf, "ss_load_image_%.4s", ptr + 1 );
			sgs_PushVariable( C, &var );
			if( sgs_GetGlobal( C, buf ) != SGS_SUCCESS )
			{
				sprintf( buf, "create_texture() - unsupported format: '%.4s'", ptr + 1 );
				_WARN( buf )
			}
			if( sgs_Call( C, 1, 1 ) != SGS_SUCCESS ) /* function is expected to provide detailed info on failure */
				_WARN( "create_texture() - failed to load image file" )
			
			/* insert return value as argument #0 */
			sgs_Release( C, sgs_StackItem( C, 0 ) );
			*sgs_StackItem( C, 0 ) = *sgs_StackItem( C, -1 );
			sgs_Acquire( C, sgs_StackItem( C, 0 ) );
			sgs_Pop( C, 1 );
		}
	}
	
	if( sgs_ItemType( C, 0 ) == SVT_OBJECT && sgs_GetObjectData( C, 0 )->data == NULL ) /* TODO */
	{
		/* create a texture from the image */
	}
	
	return 0;
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
	sgs_Variable* var;
	
	if( stdlib_tovec2d( C, -1, data, 0 ) )
	{
		out[ 0 ] = data[ 0 ];
		if( numcomp > 1 )
			out[ 1 ] = data[ 1 ];
		return NULL;
	}
	
	var = sgs_StackItem( C, -1 );
	if( stdlib_is_array( C, var ) )
	{
		int32_t i, asz = stdlib_array_size( C, var );
		if( asz > numcomp )
			asz = numcomp;
		
		for( i = 0; i < asz; ++i )
		{
			sgs_Real real;
			sgs_Variable item;
			if( !stdlib_array_getval( C, var, i, &item ) )
			{
				return "could not read from array";
			}
			
			sgs_PushVariable( C, &item );
			sgs_Release( C, &item );
			if( !stdlib_toreal( C, -1, &real ) )
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
			sgs_Free( out->data );
			out->my = 0;
		}
		return res;
	}
	
	if( !stdlib_is_array( C, var ) )
		return "array expected";
	
	asz = stdlib_array_size( C, var );
	out->cnt = asz;
	out->size = asz * numcomp;
	out->data = sgs_Alloc_n( float, out->size );
	
	off = out->data;
	for( i = 0; i < asz; ++i )
	{
		const char* subres;
		sgs_Variable item;
		if( !stdlib_array_getval( C, var, i, &item ) || item.type != SVT_OBJECT )
		{
			sgs_Free( out->data );
			return "element was not an object";
		}
		
		memcpy( off, defcomp, numcomp * sizeof(float) );
		
		sgs_PushVariable( C, &item );
		sgs_Release( C, &item );
		subres = _parse_floatvec( C, off, numcomp );
		sgs_Pop( C, 1 );
		
		if( subres )
		{
			sgs_Free( out->data );
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
		char* str;
		sgs_Integer size;
		sgs_PushVariable( C, gi[0].var );
		if( !stdlib_tostring( C, -1, &str, &size ) )
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
			return 1;
		}
		
		sgs_UnpackFree( C, gi );
		_WARN( "draw(): preset not found" )
	}
	else if( gi[2].var )
	{
		sgs_Integer imode;
		float defcomp[] = { 0, 0, 0, 0, 1, 1, 1, 1 };
		floatbuf pdata = NFB, cdata = NFB, tdata = NFB;
		const char* res = _parse_floatbuf( C, gi[2].var, &pdata, 2, defcomp, 1 );
		if( res )
		{
			sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load vertices - %s", res );
			goto cleanup;
		}
		
		if( !gi[1].var )
		{
			sgs_Printf( C, SGS_WARNING, -1, "draw(): 'mode' not found" );
			goto cleanup;
		}
		
		sgs_PushVariable( C, gi[1].var );
		if( !stdlib_toint( C, -1, &imode ) )
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
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load vertex colors - %s", res );
				goto cleanup;
			}
		}
		
		if( gi[4].var )
		{
			res = _parse_floatbuf( C, gi[4].var, &tdata, 4, defcomp, 1 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load vertex texcoords - %s", res );
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
		if( pdata.my ) sgs_Free( pdata.data );
		if( cdata.my ) sgs_Free( cdata.data );
		if( tdata.my ) sgs_Free( tdata.data );
		return 0;
	}
	
	sgs_UnpackFree( C, gi );
	_WARN( "draw(): no geometry data found" )
}
int _draw_load_inst( SGS_CTX, floatbuf* xform, floatbuf* icol )
{
	sgs_Variable transform, transforms, position,
		positions, angle, angles, scale, scales, *var;
	dict_unpack_item_t tfi[] =
	{
		{ "transform", &transform }, { "transforms", &transforms },
		{ "position", &position }, { "positions", &positions },
		{ "angle", &angle }, { "angles", &angles },
		{ "scale", &scale }, { "scales", &scales },
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
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load positions - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[2].var ) /* found 'position', one vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[2].var, &posdata, 2, defcomp, 0 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load position - %s", res );
				goto cleanup;
			}
		}
		else
		{
			sgs_Printf( C, SGS_WARNING, -1, "draw(): no instance position data found" );
		}
		
		if( tfi[5].var ) /* found 'angles', array of real */
		{
			const char* res = _parse_floatbuf( C, tfi[5].var, &angdata, 1, defcomp, 1 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load angles - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[4].var ) /* found 'angle', one real */
		{
			const char* res = _parse_floatbuf( C, tfi[4].var, &angdata, 1, defcomp, 0 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load angle - %s", res );
				goto cleanup;
			}
		}
		
		if( tfi[7].var ) /* found 'scales', array of vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[7].var, &scaledata, 2, defcomp+4, 1 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load scales - %s", res );
				goto cleanup;
			}
		}
		else if( tfi[6].var ) /* found 'scale', one vec2d */
		{
			const char* res = _parse_floatbuf( C, tfi[6].var, &scaledata, 2, defcomp+4, 0 );
			if( res )
			{
				sgs_Printf( C, SGS_WARNING, -1, "draw(): failed to load scale - %s", res );
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
		sgs_UnpackFree( C, tfi );
		if( posdata.my ) sgs_Free( posdata.data );
		if( angdata.my ) sgs_Free( angdata.data );
		if( scaledata.my ) sgs_Free( scaledata.data );
		return ret;
		
cleanup:
		ret = 0;
		goto end;
	}
	
	return 0;
}
int ss_draw( SGS_CTX )
{
	float *tf, *cc, *vp, *vt, *vc;
	int mode = GL_TRIANGLES, ret = 1;
	floatbuf vert = NFB, vcol = NFB, vtex = NFB, xform = NFB, icol = NFB;
	
	if( sgs_StackSize( C ) != 1 ||
		sgs_ItemType( C, 0 ) != SVT_OBJECT )
		_WARN( "draw(): expected one dictionary argument" )
	
	if( !_draw_load_geom( C, &mode, &vert, &vcol, &vtex ) )
		goto cleanup;
	if( !_draw_load_inst( C, &xform, &icol ) )
		goto cleanup;
	
	glMatrixMode( GL_MODELVIEW );
	cc = icol.data;
	for( tf = xform.data; tf < xform.data + xform.size; tf += 16 )
	{
		glPushMatrix();
		glMultMatrixf( tf );
		
		if( cc < icol.data + icol.size )
		{
			/* TODO, materials */
			cc += 4;
		}
		
		glBegin( mode );
		
		vt = vtex.data;
		vc = vcol.data;
		for( vp = vert.data; vp < vert.data + vert.size; vp += 2 )
		{
			if( vt < vtex.data + vtex.size )
			{
				glTexCoord2fv( vt );
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
	if( vert.my ) sgs_Free( vert.data );
	if( vcol.my ) sgs_Free( vcol.data );
	if( vtex.my ) sgs_Free( vtex.data );
	if( xform.my ) sgs_Free( xform.data );
	if( icol.my ) sgs_Free( icol.data );
	
	sgs_PushBool( C, ret );
	return 1;

cleanup:
	ret = 0;
	goto end;
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
};

int sgs_InitGL( SGS_CTX )
{
	int ret;
	ret = sgs_RegIntConsts( C, gl_ints, ARRAY_SIZE( gl_ints ) );
	if( ret != SGS_SUCCESS ) return ret;
	ret = sgs_RegFuncConsts( C, gl_funcs, ARRAY_SIZE( gl_funcs ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	return SGS_SUCCESS;
}

