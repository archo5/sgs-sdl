
#pragma once

#include <inttypes.h>


#define DDS_FMT_UNKNOWN  0
#define DDS_FMT_R8G8B8A8 1
#define DDS_FMT_B8G8R8A8 2
#define DDS_FMT_DXT1     50
#define DDS_FMT_DXT3     51
#define DDS_FMT_DXT5     52

#define DDS_CUBEMAP     0x00000001
#define DDS_VOLUME      0x00000002
#define DDS_CUBEMAP_PX  0x00000100
#define DDS_CUBEMAP_NX  0x00000200
#define DDS_CUBEMAP_PY  0x00000400
#define DDS_CUBEMAP_NY  0x00000800
#define DDS_CUBEMAP_PZ  0x00001000
#define DDS_CUBEMAP_NZ  0x00002000
#define DDS_FILE_READER 0x10000000

#define DDS_SUCCESS 0
#define DDS_ENOTFND -1
#define DDS_EINVAL  -2
#define DDS_ENOTSUP -3


typedef unsigned char dds_byte;
typedef uint32_t dds_u32;


typedef struct _dds_image_info
{
	dds_u32 size;
	dds_u32 width;
	dds_u32 height;
	dds_u32 depth;
	dds_u32 pitch; /* or linear size */
	dds_u32 mipcount;
	dds_u32 format;
}
dds_image_info;

typedef struct _dds_info
{
	/* reading state */
	void* data;
	int side, mip;
	
	/* image info */
	dds_image_info image;
	dds_u32 flags;
}
dds_info;


int dds_load_from_memory( dds_byte* bytes, size_t size, dds_info* out, dds_u32* supfmt );
int dds_load_from_file( const char* file, dds_info* out, dds_u32* supfmt );

int dds_seek( dds_info* info, int side, int mip );
int dds_getinfo( dds_info* info, dds_image_info* outplaneinfo );
void dds_read( dds_info* info, void* out );

void dds_close( dds_info* info );

