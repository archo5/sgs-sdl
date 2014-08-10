
#include <math.h>
#include <ctype.h>


#include "ss_main.h"

#include "../ext/src/libjpg/jpeglib.h"
#include "../ext/src/libpng/png.h"
#include "dds.c"


#define FN( f ) { "SS_" #f, SS_##f }
#define FNP( f ) { #f, f }
#define FNP2( f, f2 ) { #f, f2 }
#define IC( i ) { #i, i }
#define _WARN( err ) { sgs_Msg( C, SGS_WARNING, err ); return 0; }


SGS_DECLARE sgs_ObjInterface image_iface[1];
#define IMGHDR SS_Image* img = (SS_Image*) data->data

#define IMG_IHDR( funcname ) SS_Image* ii; \
	if( !SGS_PARSE_METHOD( C, image_iface, ii, SS_Image, funcname ) ) return 0;

static int _make_image( SGS_CTX, int16_t w, int16_t h, const void* src )
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

static int ss_image_destruct( SGS_CTX, sgs_VarObj* data )
{
	IMGHDR;
	sgs_Dealloc( img->data );
	sgs_Dealloc( img );
	return SGS_SUCCESS;
}

static int ss_image_resize( SGS_CTX )
{
	sgs_Integer w = 0, h = 0;
	
	IMG_IHDR( resize );
	if( !sgs_LoadArgs( C, "ii", &w, &h ) )
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
			memcpy( nbuf + y * w, ((char*)ii->data) + y * ii->width, sizeof(uint32_t) * cw );
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

static int ss_image_clear( SGS_CTX )
{
	uint32_t i = 0, cc = 0;
	uint8_t r = 0, g = 0, b = 0, a = 255;
	
	IMG_IHDR( clear );
	if( !sgs_LoadArgs( C, "^+ccc|c", &r, &g, &b, &a ) )
		return 0;
	
	cc = (a<<24)|(r<<16)|(g<<8)|(b);
	for( i = 0; i < ii->width * ii->height; ++i )
		((uint32_t*)ii->data)[ i ] = cc;
	
	return 0;
}

static int ss_image_getData( SGS_CTX )
{
	IMG_IHDR( getData );
	
	sgs_PushStringBuf( C, ii->data, ii->width * ii->height * 4 );
	return 1;
}

static int ss_image_setData( SGS_CTX )
{
	int ret = 0;
	char* buf = NULL;
	sgs_SizeVal size = 0, i = 0, pxcnt = 0;
	
	IMG_IHDR( setData );
	if( !sgs_LoadArgs( C, "m", &buf, &size ) )
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

static int ss_image_getindex( SGS_CTX, sgs_VarObj* data, sgs_Variable* key, int isprop )
{
	char* str;
	sgs_SizeVal size;
	IMGHDR;
	UNUSED( isprop );
	if( sgs_ParseStringP( C, key, &str, &size ) )
	{
		if( !strcmp( str, "width" ) ){ sgs_PushInt( C, img->width ); return SGS_SUCCESS; }
		if( !strcmp( str, "height" ) ){ sgs_PushInt( C, img->height ); return SGS_SUCCESS; }
		if( !strcmp( str, "resize" ) ){ sgs_PushCFunction( C, ss_image_resize ); return SGS_SUCCESS; }
		if( !strcmp( str, "clear" ) ){ sgs_PushCFunction( C, ss_image_clear ); return SGS_SUCCESS; }
		if( !strcmp( str, "getData" ) ){ sgs_PushCFunction( C, ss_image_getData ); return SGS_SUCCESS; }
		if( !strcmp( str, "setData" ) ){ sgs_PushCFunction( C, ss_image_setData ); return SGS_SUCCESS; }
	}
	return SGS_ENOTFND;
}

static int ss_image_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_CONVOP_CLONE )
	{
		IMGHDR;
		return _make_image( C, img->width, img->height, img->data );
	}
	else if( type == SGS_VT_STRING )
	{
		char buf[ 32 ];
		IMGHDR;
		sprintf( buf, "Image (%d x %d)", (int) img->width, (int) img->height );
		sgs_PushString( C, buf );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}


static sgs_ObjInterface image_iface[1] =
{{
	"SS_Image",
	ss_image_destruct, NULL,
	ss_image_getindex, NULL,
	ss_image_convert, NULL, NULL, NULL,
	NULL, NULL
}};

static int SS_CreateImage( SGS_CTX )
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


static uint8_t* ss_image_data( SGS_CTX )
{
	SS_Image* ii = (SS_Image*) sgs_GetObjectData( C, -1 );
	return (uint8_t*) ii->data;
}


int ss_LoadImageHelper( SGS_CTX, char* str, int size )
{
	char *ptr, *pp, buf[ 64 ];
	sgs_StkIdx ssz;
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
	ssz = sgs_StackSize( C );
	sgs_PushStringBuf( C, str, size );
	sgs_PushItem( C, -1 );
	if( SGS_FAILED( sgs_GlobalCall( C, "ss_load_file", 1, 1 ) ) )
	{
		sgs_Msg( C, SGS_WARNING, "failed to call file loader" );
		goto fail;
	}
	if( sgs_ItemType( C, -1 ) != SGS_VT_STRING )
	{
		/* error was already sent by ss_load_file */
		goto fail;
	}
	
	sgs_PushItem( C, -2 );
	int ret = sgs_GlobalCall( C, buf, 2, 1 );
	if( ret == SGS_ENOTFND )
	{
		sgs_Msg( C, SGS_WARNING, "unsupported format: '%.4s'", ptr + 1 );
		goto fail;
	}
	if( SGS_FAILED( ret ) || !sgs_IsObject( C, -1, image_iface ) )
	{
		/* error was already sent by ss_load_image_**** */
		goto fail;
	}
	
	sgs_PopSkip( C, sgs_StackSize( C ) - ssz - 1, 1 );
	return 1;
	
fail:
	sgs_SetStackSize( C, ssz );
	return 0;
}

static int SS_LoadImage( SGS_CTX )
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
	if( w < 1 || w > 4096 || h < 1 || h > 4096 )
		_WARN( "invalid image size; must be between 1 and 4096 in each dimension" )
	
	_make_image( C, w, h, bits );
	return 1;
}


//
// PNG SUPPORT

static void* _ss_png_alloc( png_structp png_ptr, png_size_t size )
{
	SGS_CTX = (sgs_Context*) png_get_mem_ptr( png_ptr );
	return sgs_Alloc_n( uint8_t, size );
}
static void _ss_png_free( png_structp png_ptr, png_voidp ptr )
{
	SGS_CTX = (sgs_Context*) png_get_mem_ptr( png_ptr );
	sgs_Dealloc( ptr );
}

typedef struct _png_read_data
{
	uint8_t *data, *at;
	size_t size;
}
png_read_data;

static void _png_memread( png_structp png_ptr, png_bytep data, png_size_t size )
{
	png_read_data* pd = (png_read_data*) png_get_io_ptr( png_ptr );
	sgs_BreakIf( pd->at + size > pd->data + pd->size );
	memcpy( data, pd->at, size );
	pd->at += size;
}

/*
static void _png_memwrite( png_structp png_ptr, png_bytep data, png_size_t size )
{
	FByteWriter* bw = (FByteWriter*) png_get_io_ptr( png_ptr );
	bw->Serialize( data, size, 1 );
}
*/

static int ss_load_image_png( SGS_CTX )
{
	uint8_t *str;
	char* imgname;
	sgs_SizeVal size;
	SGSFN( "ss_load_image_png" );
	if( !sgs_LoadArgs( C, "ms", &str, &size, &imgname ) )
		return 0;
	else
	{
		png_structp png_ptr = png_create_read_struct_2( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL, C, &_ss_png_alloc, &_ss_png_free );
		
		if( !png_ptr )
			_WARN( "failed to initialize PNG" );
		
		if( setjmp( png_jmpbuf( png_ptr ) ) )
		{
			png_destroy_read_struct( &png_ptr, NULL, NULL );
			return sgs_Msg( C, SGS_WARNING, "failed to read PNG image - %s", imgname );
		}
		
		png_infop info_ptr = png_create_info_struct( png_ptr );
		
		if( !info_ptr )
		{
			png_destroy_read_struct( &png_ptr, NULL, NULL );
			_WARN( "failed to set up PNG reading" );
		}
		
		// Load..
		png_read_data prd = { str, str, size };
		png_set_read_fn( png_ptr, &prd, (png_rw_ptr) &_png_memread );
		png_set_user_limits( png_ptr, 4096, 4096 );
		
		png_read_info( png_ptr, info_ptr );
		png_set_strip_16( png_ptr );
		png_set_packing( png_ptr );
		png_set_gray_to_rgb( png_ptr );
		png_set_bgr( png_ptr );
		png_set_add_alpha( png_ptr, 0xffffffff, PNG_FILLER_AFTER );
		
		// send info..
		uint32_t width = png_get_image_width( png_ptr, info_ptr );
		uint32_t height = png_get_image_height( png_ptr, info_ptr );
		
		ss_CreateImageHelper( C, width, height, NULL );
		uint8_t* imgdata = ss_image_data( C );
		
		uint16_t offsets[ 4096 ] = {0};
		int pass, number_passes = png_set_interlace_handling(png_ptr);
		for( pass = 0; pass < number_passes; ++pass )
		{
			uint32_t y;
			for( y = 0; y < height; ++y )
			{
				png_bytep rowp = (png_bytep) imgdata + y * width * 4;
				png_bytep crp = rowp + offsets[ y ];
				png_read_rows(png_ptr, &crp, NULL, 1);
				offsets[ y ] = crp - rowp;
			}
		}
		
		png_read_end( png_ptr, info_ptr );
		
		png_destroy_read_struct( &png_ptr, &info_ptr, NULL );
		return 1;
	}
}


//
// JPG SUPPORT

typedef struct _jpg_error_mgr
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
}
jpg_error_mgr;

static void _jpg_error_exit( j_common_ptr cinfo )
{
	jpg_error_mgr* myerr = (jpg_error_mgr*) cinfo->err;
	(*cinfo->err->output_message) (cinfo);
	longjmp(myerr->setjmp_buffer, 1);
}

static int ss_load_image_jpg( SGS_CTX )
{
	uint8_t *str;
	char* imgname;
	sgs_SizeVal size;
	SGSFN( "ss_load_image_jpg" );
	if( !sgs_LoadArgs( C, "ms", &str, &size, &imgname ) )
		return 0;
	else
	{
		struct jpeg_decompress_struct cinfo;
		jpg_error_mgr jerr;
		
		JSAMPARRAY buffer;
		int x, row_stride;
		
		cinfo.err = jpeg_std_error( &jerr.pub );
		jerr.pub.error_exit = _jpg_error_exit;
		if( setjmp( jerr.setjmp_buffer ) )
		{
			jpeg_destroy_decompress( &cinfo );
			return sgs_Msg( C, SGS_WARNING, "failed to read JPG image - %s", imgname );
		}
		
		jpeg_create_decompress( &cinfo );
		jpeg_mem_src( &cinfo, str, size );
		jpeg_read_header( &cinfo, 1 );
		jpeg_start_decompress( &cinfo );
		
		ss_CreateImageHelper( C, cinfo.output_width, cinfo.output_height, NULL );
		uint8_t* imgdata = ss_image_data( C );
		
		row_stride = cinfo.output_width * cinfo.output_components;
		buffer = (*cinfo.mem->alloc_sarray)( (j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1 );
		
		while( cinfo.output_scanline < cinfo.output_height )
		{
			jpeg_read_scanlines( &cinfo, buffer, 1 );
			for( x = 0; x < cinfo.output_width; ++x )
			{
				imgdata[ x * 4   ] = buffer[0][ x * 3+2 ];
				imgdata[ x * 4+1 ] = buffer[0][ x * 3+1 ];
				imgdata[ x * 4+2 ] = buffer[0][ x * 3   ];
				imgdata[ x * 4+3 ] = 0xff;
			}
			imgdata += cinfo.output_width * 4;
		}
		
		jpeg_finish_decompress( &cinfo );
		jpeg_destroy_decompress( &cinfo );
		
		return 1;
	}
}


//
// DDS SUPPORT

static int ss_load_image_dds( SGS_CTX )
{
	uint8_t *str;
	char* imgname;
	sgs_SizeVal size;
	SGSFN( "ss_load_image_dds" );
	if( !sgs_LoadArgs( C, "ms", &str, &size, &imgname ) )
		return 0;
	else
	{
		static const dds_u32 supfmts[] = { DDS_FMT_R8G8B8A8, DDS_FMT_B8G8R8A8, DDS_FMT_B8G8R8X8, 0 };
		dds_u32 i;
		dds_info info;
		dds_image_info imginfo;
		
		int ret = dds_load_from_memory( (dds_byte*) str, size, &info, supfmts );
		if( ret != DDS_SUCCESS )
		{
			return sgs_Msg( C, SGS_WARNING, "failed to read DDS image%s - %s", ret == DDS_ENOTSUP ? " (format is not supported)" : "", imgname );
		}
		
		if( dds_seek( &info, 0, 0 ) != DDS_SUCCESS )
		{
			dds_close( &info );
			return sgs_Msg( C, SGS_WARNING, "could not find image data in DDS image - %s", imgname );
		}
		
		dds_getinfo( &info, &imginfo );
		
		ss_CreateImageHelper( C, imginfo.width, imginfo.height, NULL );
		uint8_t* imgdata = ss_image_data( C );
		
		dds_read( &info, imgdata );
		if( imginfo.format == DDS_FMT_B8G8R8X8 )
		{
			for( i = 0; i < imginfo.width * imginfo.height; ++i )
				imgdata[ i * 4 + 3 ] = 0xff;
		}
		else if( imginfo.format == DDS_FMT_R8G8B8A8 )
		{
			for( i = 0; i < imginfo.width * imginfo.height; ++i )
			{
				uint8_t tmp = imgdata[ i * 4 ];
				imgdata[ i * 4 ] = imgdata[ i * 4 + 2 ];
				imgdata[ i * 4 + 2 ] = tmp;
			}
		}
		
		dds_close( &info );
		
		return 1;
	}
}


static sgs_RegIntConst img_ints[] =
{
};

static sgs_RegFuncConst img_funcs[] =
{
	FN( CreateImage ),
	FN( LoadImage ),
	
	FNP( ss_load_image_png ),
	FNP( ss_load_image_jpg ),
	FNP2( ss_load_image_jpeg, ss_load_image_jpg ),
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
	return var->type == SGS_VT_OBJECT && var->data.O->iface == image_iface;
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

