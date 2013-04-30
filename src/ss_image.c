
#include <math.h>

#define SGS_INTERNAL

#include "ss_main.h"

#include "../freeimage/FreeImage.h"


#define FN( f ) { #f, ss_##f }
#define FNP( f ) { #f, f }
#define IC( i ) { #i, i }
#define _WARN( err ) { sgs_Printf( C, SGS_WARNING, err ); return 0; }


void* image_iface[];
#define IMGHDR sgs_Image* img = (sgs_Image*) data->data

int _make_image( SGS_CTX, int16_t w, int16_t h, const void* src )
{
	sgs_Image* ii = sgs_Alloc( sgs_Image );
	ii->width = w;
	ii->height = h;
	ii->data = sgs_Alloc_n( uint32_t, w * h );
	if( !src )
		memset( ii->data, 0, sizeof( uint32_t ) * w * h );
	else
		memcpy( ii->data, src, sizeof( uint32_t ) * w * h );
	sgs_PushObject( C, ii, image_iface );
	return SGS_SUCCESS;
}

int ss_image_destruct( SGS_CTX, sgs_VarObj* data )
{
	IMGHDR;
	sgs_Dealloc( img->data );
	sgs_Dealloc( img );
	return SGS_SUCCESS;
}

int ss_image_clone( SGS_CTX, sgs_VarObj* data )
{
	IMGHDR;
	return _make_image( C, img->width, img->height, img->data );
}

int ss_image_gettype( SGS_CTX, sgs_VarObj* data )
{
	UNUSED( data );
	sgs_PushString( C, "image" );
	return SGS_SUCCESS;
}


int ss_image_resize( SGS_CTX )
{
	sgs_Image* ii;
	sgs_Integer w, h;
	
	if( !sgs_Method( C ) )
		_WARN( "image::resize(): not called in object context" )
	
	if( !stdlib_toimage( C, 0, &ii ) )
		_WARN( "image::resize(): 'this' is not an image" )
	
	if( sgs_StackSize( C ) != 3 || !sgs_ParseInt( C, 1, &w ) || !sgs_ParseInt( C, 2, &h ) )
		_WARN( "image::resize(): unexpected arguments; function expects 2 arguments: int, int" )
	
	{
		int x, y, cw, ch;
		if( ii->width == w && ii->height == h )
			goto end;
	
		if( w < 1 || w > 4096 || h < 1 || h > 4096 )
			_WARN( "image::resize(): invalid image size; must be between 1 and 4096 in each dimension" )
		
		uint32_t* nbuf = sgs_Alloc_n( uint32_t, w * h );
		cw = w < ii->width ? w : ii->width;
		ch = h < ii->height ? h : ii->height;
		for( y = 0; y < ch; ++y )
		{
			memcpy( nbuf + y * w, ii->data + y * ii->width, sizeof(uint32_t) * cw );
			for( x = cw; x < w; ++x )
				nbuf[ y * w + x ] = 0;
		}
		if( y < h )
			memset( nbuf + y * w, 0, sizeof(uint32_t) * w * ( h - ch ) );
		
		sgs_Dealloc( ii->data );
		ii->data = nbuf;
		ii->width = w;
		ii->height = h;
	}
	
end:
	sgs_PushBool( C, 1 );
	return 1;
}

int ss_image_getprop( SGS_CTX, sgs_VarObj* data )
{
	char* str;
	sgs_SizeVal size;
	IMGHDR;
	
	if( !sgs_ParseString( C, 0, &str, &size ) )
		return SGS_EINVAL;
	
	if( !strcmp( str, "width" ) ){ sgs_PushInt( C, img->width ); return SGS_SUCCESS; }
	if( !strcmp( str, "height" ) ){ sgs_PushInt( C, img->height ); return SGS_SUCCESS; }
	if( !strcmp( str, "resize" ) ){ sgs_PushCFunction( C, ss_image_resize ); return SGS_SUCCESS; }
	
	return SGS_ENOTFND;
}


int ss_image_tostring( SGS_CTX, sgs_VarObj* data )
{
	char buf[ 32 ];
	IMGHDR;
	sprintf( buf, "Image (%d x %d)", (int) img->width, (int) img->height );
	sgs_PushString( C, buf );
	return SGS_SUCCESS;
}


void* image_iface[] =
{
	SOP_DESTRUCT, ss_image_destruct,
	SOP_CLONE, ss_image_clone,
	SOP_GETTYPE, ss_image_gettype,
	SOP_GETPROP, ss_image_getprop,
	SOP_TOSTRING, ss_image_tostring,
	SOP_END
};

int ss_create_image( SGS_CTX )
{
	sgs_Integer w, h;
	int argc = sgs_StackSize( C );
	
	if( argc < 1 || argc > 2 ||
		!sgs_ParseInt( C, 0, &w ) ||
		( argc >= 2 && !sgs_ParseInt( C, 1, &h ) ) )
		_WARN( "create_image(): unexpected arguments; function expects 1-2 arguments: int[, int]" )
	
	if( argc != 2 )
		h = w;
	
	if( w < 1 || w > 4096 || h < 1 || h > 4096 )
		_WARN( "create_image(): invalid image size; must be between 1 and 4096 in each dimension" )
	
	_make_image( C, w, h, NULL );
	return 1;
}


int sgs_LoadImageHelper( SGS_CTX, char* str, int size, const char* func )
{
	char *ptr, *pp, buf[ 64 ];
	ptr = str + size;
	while( str <-- ptr )
	{
		if( *ptr == '/' || *ptr == '\\' )
		{
			sprintf( buf, "%s() - filename has no extension", func );
			_WARN( buf )
		}
		if( *ptr == '.' )
			break;
	}
	if( *ptr != '.' )
	{
		sprintf( buf, "%s() - filename has no extension", func );
		_WARN( buf )
	}
	
	sprintf( buf, "ss_load_image_%.4s", ptr + 1 );
	pp = buf + 14; /* extension part */
	while( *pp )
	{
		*pp = tolower( *pp );
		pp++;
	}
	sgs_PushStringBuf( C, str, size );
	if( sgs_PushGlobal( C, buf ) != SGS_SUCCESS )
	{
		sprintf( buf, "%s() - unsupported format: '%.4s'", func, ptr + 1 );
		_WARN( buf )
	}
	if( sgs_Call( C, 1, 1 ) != SGS_SUCCESS ) /* function is expected to provide detailed info on failure */
	{
		sprintf( buf, "%s() - failed to load image file", func );
		_WARN( buf )
	}
	
	return 1;
}

int ss_load_image( SGS_CTX )
{
	char *str;
	sgs_SizeVal size;
	
	if( sgs_StackSize( C ) != 1 || !sgs_ParseString( C, 0, &str, &size ) )
		_WARN( "load_image(): unexpected arguments; function expects 1 argument: string" )
	
	return sgs_LoadImageHelper( C, str, size, "load_image" );
}


int sgs_CreateImageHelper( SGS_CTX, int16_t w, int16_t h, const void* bits, const char* func )
{
	int ret;
	char buf[ 128 ];
	
	if( w < 1 || w > 4096 || h < 1 || h > 4096 )
	{
		sprintf( buf, "%.32s(): invalid image size; must be between 1 and 4096 in each dimension", func );
		_WARN( buf )
	}
	
	ret = _make_image( C, w, h, bits );
	if( ret != SGS_SUCCESS )
	{
		sprintf( buf, "%.32s(): failed to upload image", func );
		_WARN( buf )
	}
	
	return 1;
}

int ss_load_image_png( SGS_CTX )
{
	char *str;
	sgs_SizeVal size;
	
	if( sgs_StackSize( C ) != 1 || !sgs_ParseString( C, 0, &str, &size ) )
		_WARN( "ss_load_image_*(): unexpected arguments; function expects 1 argument: string" )
	
	{
		int ret;
		sgs_Image* img;
		FIBITMAP* dib;
		BITMAPINFOHEADER* bih;
		int16_t w, h;
		
		dib = FreeImage_Load( FIF_PNG, str, PNG_DEFAULT );
		if( !dib )
			_WARN( "ss_load_image_*(): failed to load image" )
		
		bih = FreeImage_GetInfoHeader( dib );
		if( !bih )
			_WARN( "ss_load_image_*(): failed to prepare image" )
		
		w = bih->biWidth, h = bih->biHeight;
		if( bih->biBitCount != 32 )
		{
			FIBITMAP* odib = dib;
			dib = FreeImage_ConvertTo32Bits( odib );
			FreeImage_Unload( odib );
			if( !dib )
				_WARN( "ss_load_image_*(): failed to prepare image" )
		}
		
		ret = sgs_CreateImageHelper( C, w, h, FreeImage_GetBits( dib ), "ss_load_image_*" );
		
		FreeImage_Unload( dib );
		return ret;
	}
}


sgs_RegIntConst img_ints[] =
{
};

sgs_RegFuncConst img_funcs[] =
{
	FN( create_image ),
	FN( load_image ),
	
	FNP( ss_load_image_png ),
};

int sgs_InitImage( SGS_CTX )
{
	int ret;
	ret = sgs_RegIntConsts( C, img_ints, ARRAY_SIZE( img_ints ) );
	if( ret != SGS_SUCCESS ) return ret;
	ret = sgs_RegFuncConsts( C, img_funcs, ARRAY_SIZE( img_funcs ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	return SGS_SUCCESS;
}

int sgs_IsImageVar( sgs_Variable* var )
{
	return var->type == SVT_OBJECT && var->data.O->iface == image_iface;
}

int stdlib_toimage( SGS_CTX, int pos, sgs_Image** out )
{
	if( sgs_ItemType( C, pos ) != SVT_OBJECT ||
		sgs_GetObjectData( C, pos )->iface != image_iface )
		return 0;
	
	*out = (sgs_Image*) sgs_GetObjectData( C, pos )->data;
	return 1;
}

