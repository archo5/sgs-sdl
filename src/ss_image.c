
#include <math.h>

#define SGS_INTERNAL

#include "ss_main.h"

#include "../freeimage/FreeImage.h"


#define FN( f ) { "SS_" #f, SS_##f }
#define FNP( f ) { #f, f }
#define IC( i ) { #i, i }
#define _WARN( err ) { sgs_Printf( C, SGS_WARNING, err ); return 0; }


sgs_ObjCallback image_iface[];
#define IMGHDR SS_Image* img = (SS_Image*) data->data

int _make_image( SGS_CTX, int16_t w, int16_t h, const void* src )
{
	SS_Image* ii = sgs_Alloc( SS_Image );
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

int ss_image_destruct( SGS_CTX, sgs_VarObj* data, int dco )
{
	IMGHDR;
	sgs_Dealloc( img->data );
	sgs_Dealloc( img );
	return SGS_SUCCESS;
}

int ss_image_resize( SGS_CTX )
{
	SS_Image* ii = NULL;
	sgs_Integer w = 0, h = 0;
	
	SGSFN( "image.resize" );
	
	sgs_Method( C );
	if( !ss_ParseImage( C, 0, &ii ) )
		_WARN( "'this' is not an image" )
	
	if( !sgs_LoadArgs( C, "@>ii", &w, &h ) )
		return 0;
	
	{
		int x, y, cw, ch;
		if( ii->width == w && ii->height == h )
			goto end;
	
		if( w < 1 || w > 4096 || h < 1 || h > 4096 )
			_WARN( "invalid image size; must be between 1 and 4096 in each dimension" )
		
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

int ss_image_clear( SGS_CTX )
{
	SS_Image* ii = NULL;
	uint32_t i = 0, cc = 0;
	uint8_t r = 0, g = 0, b = 0, a = 255;
	
	SGSFN( "image.clear" );
	
	sgs_Method( C );
	if( !ss_ParseImage( C, 0, &ii ) )
		_WARN( "'this' is not an image" )
	
	if( !sgs_LoadArgs( C, "@>^+ccc|c", &r, &g, &b, &a ) )
		return 0;
	
	cc = (a<<24)|(r<<16)|(g<<8)|(b);
	for( i = 0; i < ii->width * ii->height; ++i )
		((uint32_t*)ii->data)[ i ] = cc;
	
	return 0;
}

int ss_image_setData( SGS_CTX )
{
	int ret = 0;
	SS_Image* ii = NULL;
	char* buf = NULL;
	sgs_SizeVal size = 0, i = 0, pxcnt = 0;
	
	SGSFN( "image.setData" );
	
	sgs_Method( C );
	if( !ss_ParseImage( C, 0, &ii ) )
		_WARN( "'this' is not an image" )
	
	if( !sgs_LoadArgs( C, "@>m", &buf, &size ) )
		return 0;
	
	pxcnt = size / 4;
	if( pxcnt < ii->width * ii->height )
	{
		memcpy( ii->data, buf, pxcnt * 4 );
		ret = 0;
	}
	else
	{
		memcpy( ii->data, buf, ii->width * ii->height * 4 );
		ret = size > ii->width * ii->height * 4 ? 2 : 1;
		pxcnt = ii->width * ii->height;
	}
	
	/* R/B flip */
	for( i = 0; i < pxcnt; ++i )
	{
		uint32_t* px = ((uint32_t*)ii->data) + i;
		uint32_t P = *px;
		*px = ((P&0xff)<<16)|((P&0xff00)<<0)|((P&0xff0000)>>16)|((P&0xff000000)>>0);
	}
	
	sgs_PushInt( C, ret );
	return 1;
}

int ss_image_getindex( SGS_CTX, sgs_VarObj* data, int prop )
{
	char* str;
	sgs_SizeVal size;
	IMGHDR;
	
	if( !sgs_ParseString( C, 0, &str, &size ) )
		return SGS_EINVAL;
	
	if( !strcmp( str, "width" ) ){ sgs_PushInt( C, img->width ); return SGS_SUCCESS; }
	if( !strcmp( str, "height" ) ){ sgs_PushInt( C, img->height ); return SGS_SUCCESS; }
	if( !strcmp( str, "resize" ) ){ sgs_PushCFunction( C, ss_image_resize ); return SGS_SUCCESS; }
	if( !strcmp( str, "clear" ) ){ sgs_PushCFunction( C, ss_image_clear ); return SGS_SUCCESS; }
	if( !strcmp( str, "setData" ) ){ sgs_PushCFunction( C, ss_image_setData ); return SGS_SUCCESS; }
	
	return SGS_ENOTFND;
}

int ss_image_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_CONVOP_CLONE )
	{
		IMGHDR;
		return _make_image( C, img->width, img->height, img->data );
	}
	else if( type == SGS_CONVOP_TOTYPE )
	{
		UNUSED( data );
		sgs_PushString( C, "image" );
		return SGS_SUCCESS;
	}
	else if( type == SVT_STRING )
	{
		char buf[ 32 ];
		IMGHDR;
		sprintf( buf, "Image (%d x %d)", (int) img->width, (int) img->height );
		sgs_PushString( C, buf );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}


sgs_ObjCallback image_iface[] =
{
	SOP_GETINDEX, ss_image_getindex,
	SOP_CONVERT, ss_image_convert,
	SOP_DESTRUCT, ss_image_destruct,
	SOP_END
};

int SS_CreateImage( SGS_CTX )
{
	sgs_Integer w, h;
	int argc = sgs_StackSize( C );
	
	SGSFN( "SS_CreateImage" );
	
	if( argc < 1 || argc > 2 ||
		!sgs_ParseInt( C, 0, &w ) ||
		( argc >= 2 && !sgs_ParseInt( C, 1, &h ) ) )
		_WARN( "unexpected arguments; function expects 1-2 arguments: int[, int]" )
	
	if( argc != 2 )
		h = w;
	
	if( w < 1 || w > 4096 || h < 1 || h > 4096 )
		_WARN( "invalid image size; must be between 1 and 4096 in each dimension" )
	
	_make_image( C, w, h, NULL );
	return 1;
}


int ss_LoadImageHelper( SGS_CTX, char* str, int size )
{
	char *ptr, *pp, buf[ 64 ];
	ptr = str + size;
	while( str <-- ptr )
	{
		if( *ptr == '/' || *ptr == '\\' )
			_WARN( "filename has no extension" )
		if( *ptr == '.' )
			break;
	}
	if( *ptr != '.' )
		_WARN( "filename has no extension" )
	
	sprintf( buf, "ss_load_image_%.4s", ptr + 1 );
	pp = buf + 14; /* extension part */
	while( *pp )
	{
		*pp = tolower( *pp );
		pp++;
	}
	sgs_PushStringBuf( C, str, size );
	if( sgs_PushGlobal( C, buf ) != SGS_SUCCESS )
		return sgs_Printf( C, SGS_WARNING, "unsupported format: '%.4s'", ptr + 1 );
	if( sgs_Call( C, 1, 1 ) != SGS_SUCCESS ) /* function is expected to provide detailed info on failure */
		_WARN( "failed to load image file" )
	
	return 1;
}

int SS_LoadImage( SGS_CTX )
{
	char *str;
	sgs_SizeVal size;
	
	SGSFN( "SS_LoadImage" );
	
	if( sgs_StackSize( C ) != 1 || !sgs_ParseString( C, 0, &str, &size ) )
		_WARN( "unexpected arguments; function expects 1 argument: string" )
	
	return ss_LoadImageHelper( C, str, size );
}


int ss_CreateImageHelper( SGS_CTX, int16_t w, int16_t h, const void* bits )
{
	int ret;
	
	if( w < 1 || w > 4096 || h < 1 || h > 4096 )
		_WARN( "invalid image size; must be between 1 and 4096 in each dimension" )
	
	ret = _make_image( C, w, h, bits );
	if( ret != SGS_SUCCESS )
		_WARN( "failed to upload image" )
	
	return 1;
}

int ss_load_image_( SGS_CTX, int type1, int type2 )
{
	char *str;
	sgs_SizeVal size;
	
	if( sgs_StackSize( C ) != 1 || !sgs_ParseString( C, 0, &str, &size ) )
		_WARN( "unexpected arguments; function expects 1 argument: string" )
	
	{
		int ret;
		FIBITMAP* dib;
		BITMAPINFOHEADER* bih;
		int16_t w, h;
		
		dib = FreeImage_Load( type1, str, type2 );
		if( !dib )
			_WARN( "failed to load image" )
		
		bih = FreeImage_GetInfoHeader( dib );
		if( !bih || !FreeImage_FlipVertical( dib ) )
			_WARN( "failed to prepare image" )
		
		w = bih->biWidth, h = bih->biHeight;
		if( bih->biBitCount != 32 )
		{
			FIBITMAP* odib = dib;
			dib = FreeImage_ConvertTo32Bits( odib );
			FreeImage_Unload( odib );
			if( !dib )
				_WARN( "failed to prepare image" )
		}
		
		ret = ss_CreateImageHelper( C, w, h, FreeImage_GetBits( dib ) );
		
		FreeImage_Unload( dib );
		return ret;
	}
}
int ss_load_image_png( SGS_CTX ){ SGSFN( "ss_load_image_png" ); return ss_load_image_( C, FIF_PNG, PNG_DEFAULT ); }
int ss_load_image_jpg( SGS_CTX ){ SGSFN( "ss_load_image_jpg" ); return ss_load_image_( C, FIF_JPEG, PNG_DEFAULT ); }
int ss_load_image_jpeg( SGS_CTX ){ SGSFN( "ss_load_image_jpeg" ); return ss_load_image_( C, FIF_JPEG, PNG_DEFAULT ); }
int ss_load_image_dds( SGS_CTX ){ SGSFN( "ss_load_image_dds" ); return ss_load_image_( C, FIF_DDS, DDS_DEFAULT ); }


sgs_RegIntConst img_ints[] =
{
};

sgs_RegFuncConst img_funcs[] =
{
	FN( CreateImage ),
	FN( LoadImage ),
	
	FNP( ss_load_image_png ),
	FNP( ss_load_image_jpg ),
	FNP( ss_load_image_jpeg ),
	FNP( ss_load_image_dds ),
};

int ss_InitImage( SGS_CTX )
{
	int ret;
	ret = sgs_RegIntConsts( C, img_ints, ARRAY_SIZE( img_ints ) );
	if( ret != SGS_SUCCESS ) return ret;
	ret = sgs_RegFuncConsts( C, img_funcs, ARRAY_SIZE( img_funcs ) );
	if( ret != SGS_SUCCESS ) return ret;
	
	return SGS_SUCCESS;
}

int ss_IsImageVar( sgs_Variable* var )
{
	return BASETYPE(var->type) == SVT_OBJECT && var->data.O->iface == image_iface;
}

int ss_ParseImage( SGS_CTX, int pos, SS_Image** out )
{
	if( !sgs_IsObject( C, pos, image_iface ) )
		return 0;
	
	*out = (SS_Image*) sgs_GetObjectData( C, pos );
	return 1;
}


SS_Image* ss_ImageDS2X( SS_Image* src, SGS_CTX )
{
	int x, y;
	SS_Image* img;
	uint32_t* data, *srcdata = (uint32_t*) src->data;
	int w = src->width / 2;
	int h = src->height / 2;
	
	if( w < 1 ) w = 1;
	if( h < 1 ) h = 1;
	
	img = sgs_Alloc( SS_Image );
	img->width = w;
	img->height = h;
	img->data = data = sgs_Alloc_n( uint32_t, w * h );
	
	for( y = 0; y < h; ++y )
	{
		for( x = 0; x < w; ++x )
		{
			int cx0 = x * 2, cy0 = y * 2;
			int cx1 = ( cx0 + 1 ) % src->width, cy1 = ( cy0 + 1 ) % src->height;
			uint32_t c00 = srcdata[ cx0 + src->width * cy0 ];
			uint32_t c10 = srcdata[ cx1 + src->width * cy0 ];
			uint32_t c01 = srcdata[ cx0 + src->width * cy1 ];
			uint32_t c11 = srcdata[ cx1 + src->width * cy1 ];
			uint32_t com1 = ( ((c00>>24)&0xff) + ((c10>>24)&0xff) + ((c01>>24)&0xff) + ((c11>>24)&0xff) ) / 4;
			uint32_t com2 = ( ((c00>>16)&0xff) + ((c10>>16)&0xff) + ((c01>>16)&0xff) + ((c11>>16)&0xff) ) / 4;
			uint32_t com3 = ( ((c00>>8)&0xff) + ((c10>>8)&0xff) + ((c01>>8)&0xff) + ((c11>>8)&0xff) ) / 4;
			uint32_t com4 = ( ((c00)&0xff) + ((c10)&0xff) + ((c01)&0xff) + ((c11)&0xff) ) / 4;
			uint32_t col = (com1<<24) | (com2<<16) | (com3<<8) | com4;
			data[ x + y * w ] = col;
		}
	}
	return img;
}

void ss_DeleteImage( SS_Image* img, SGS_CTX )
{
	sgs_Dealloc( img->data );
	sgs_Dealloc( img );
}

