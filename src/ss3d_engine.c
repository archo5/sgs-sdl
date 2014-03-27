

#include "lodepng.h"
#include "dds.h"

#include "ss3d_engine.h"

#define FN( x ) { "SS3D_" #x, SS3D_##x }
#define CN( x ) { "SS3D" #x, SS3D##x }


//
// MATH

void SS3D_Mtx_Identity( MAT4 out )
{
	int i, j;
	for( j = 0; j < 4; ++j )
		for( i = 0; i < 4; ++i )
			out[ i ][ j ] = i == j ? 1.0f : 0.0f;
}

void SS3D_Mtx_Transpose( MAT4 mtx )
{
	float tmp;
#define _MSWAP( a, b ) { tmp = a; a = b; b = tmp; }
	_MSWAP( mtx[0][1], mtx[1][0] );
	_MSWAP( mtx[0][2], mtx[2][0] );
	_MSWAP( mtx[0][3], mtx[3][0] );
	_MSWAP( mtx[1][2], mtx[2][1] );
	_MSWAP( mtx[1][3], mtx[3][1] );
	_MSWAP( mtx[2][3], mtx[3][2] );
#undef _MSWAP
}

void SS3D_Mtx_Multiply( MAT4 out, MAT4 A, MAT4 B )
{
	out[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0];
	out[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1];
	out[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2];
	out[0][3] = A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3];
	out[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0];
	out[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1];
	out[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2];
	out[1][3] = A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3];
	out[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0];
	out[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1];
	out[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2];
	out[2][3] = A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3];
	out[3][0] = A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0];
	out[3][1] = A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1];
	out[3][2] = A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2];
	out[3][3] = A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3];
};

void SS3D_Mtx_Transform( VEC4 out, VEC4 v, MAT4 mtx )
{
	VEC4 r_;
	int i, j;
	for(j=0; j<4; ++j) {
		r_[j] = 0.;
		for(i=0; i<4; ++i) {
			r_[j] += mtx[i][j] * v[i];
		}
	}
	memcpy(out, r_, sizeof(r_));
}

void SS3D_Mtx_TransformPos( VEC3 out, VEC3 pos, MAT4 mtx )
{
	VEC4 tmp, xpos = {pos[0],pos[1],pos[2],1};
	SS3D_Mtx_Transform( tmp, xpos, mtx );
	out[0] = tmp[0] / tmp[3]; out[1] = tmp[1] / tmp[3]; out[2] = tmp[2] / tmp[3];
}

void SS3D_Mtx_TransformNormal( VEC3 out, VEC3 pos, MAT4 mtx )
{
	VEC4 tmp, xpos = {pos[0],pos[1],pos[2],0};
	SS3D_Mtx_Transform( tmp, xpos, mtx );
	out[0] = tmp[0]; out[1] = tmp[1]; out[2] = tmp[2];
}

void SS3D_Mtx_Dump( MAT4 mtx )
{
	puts("{");
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[0][0], mtx[0][1], mtx[0][2], mtx[0][3] );
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[1][0], mtx[1][1], mtx[1][2], mtx[1][3] );
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[2][0], mtx[2][1], mtx[2][2], mtx[2][3] );
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[3][0], mtx[3][1], mtx[3][2], mtx[3][3] );
	puts("}");
}

void SS3D_Mtx_LookAt( MAT4 out, VEC3 pos, VEC3 dir, VEC3 up )
{
	VEC3 zaxis, xaxis, yaxis;
	VEC3_Normalized( zaxis, dir );
	VEC3_Cross( xaxis, up, zaxis );
	VEC3_Normalized( xaxis, xaxis );
	VEC3_Cross( yaxis, zaxis, xaxis );
	
	out[0][0] = xaxis[0]; out[0][1] = yaxis[0]; out[0][2] = zaxis[0]; out[0][3] = 0;
	out[1][0] = xaxis[1]; out[1][1] = yaxis[1]; out[1][2] = zaxis[1]; out[1][3] = 0;
	out[2][0] = xaxis[2]; out[2][1] = yaxis[2]; out[2][2] = zaxis[2]; out[2][3] = 0;
	out[3][0] = -VEC3_Dot( xaxis, pos );
	out[3][1] = -VEC3_Dot( yaxis, pos );
	out[3][2] = -VEC3_Dot( zaxis, pos );
	out[3][3] = 1;
}

void SS3D_Mtx_Perspective( MAT4 out, float angle, float aspect, float aamix, float znear, float zfar )
{
	float tha = tan( DEG2RAD( angle ) / 2.0f );
	if( tha < 0.001f ) tha = 0.001f;
	float itha = 1.0f / tha;
	float xscale = itha / pow( aspect, aamix );
	float yscale = itha * pow( aspect, 1 - aamix );
	
	out[0][0] = -xscale;
	out[0][1] = out[0][2] = out[0][3] = 0;
	out[1][1] = yscale;
	out[1][0] = out[1][2] = out[1][3] = 0;
	out[2][2] = zfar / ( zfar - znear );
	out[2][0] = out[2][1] = 0; out[2][3] = 1;
	out[3][2] = -znear * zfar / ( zfar - znear );
	out[3][0] = out[3][1] = out[3][3] = 0;
}


//
// MESH GENERATORS

typedef struct _genVtx
{
	float x, y, z;
	float tx, ty;
	float nx, ny, nz;
	float tgx, tgy, tgz, tgw;
	float cr, cg, cb, ca;
}
genVtx;

static int SS3D_MeshGen_Cube( SGS_CTX )
{
	VEC3 pos = {0,0,0};
	VEC4 col = {1,1,1,1};
	float ext;
	SGSFN( "SS3D_MeshGen_Cube" );
	if( !sgs_LoadArgs( C, "f|xx", &ext, sgs_ArgCheck_Vec3, pos, sgs_ArgCheck_Color, col ) )
		return 0;
	
	genVtx vertices[] =
	{
		// front
		{ pos[0]-ext, pos[1]-ext, pos[2]-ext,  0, 0,   0,  0, -1,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]-ext, pos[2]-ext,  0, 1,   0,  0, -1,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]+ext, pos[2]-ext,  1, 1,   0,  0, -1,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]-ext, pos[1]+ext, pos[2]-ext,  1, 0,   0,  0, -1,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		// top
		{ pos[0]-ext, pos[1]+ext, pos[2]-ext,  0, 0,   0, +1,  0,  0,  0,  1, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]+ext, pos[2]-ext,  0, 1,   0, +1,  0,  0,  0,  1, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]+ext, pos[2]+ext,  1, 1,   0, +1,  0,  0,  0,  1, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]-ext, pos[1]+ext, pos[2]+ext,  1, 0,   0, +1,  0,  0,  0,  1, 1,  col[0], col[1], col[2], col[3] },
		// back
		{ pos[0]-ext, pos[1]+ext, pos[2]+ext,  0, 0,   0,  0, +1,  0, -1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]+ext, pos[2]+ext,  0, 1,   0,  0, +1,  0, -1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]-ext, pos[2]+ext,  1, 1,   0,  0, +1,  0, -1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]-ext, pos[1]-ext, pos[2]+ext,  1, 0,   0,  0, +1,  0, -1,  0, 1,  col[0], col[1], col[2], col[3] },
		// bottom
		{ pos[0]-ext, pos[1]-ext, pos[2]+ext,  0, 0,   0, -1,  0,  0,  0, -1, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]-ext, pos[2]+ext,  0, 1,   0, -1,  0,  0,  0, -1, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]-ext, pos[2]-ext,  1, 1,   0, -1,  0,  0,  0, -1, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]-ext, pos[1]-ext, pos[2]-ext,  1, 0,   0, -1,  0,  0,  0, -1, 1,  col[0], col[1], col[2], col[3] },
		// left
		{ pos[0]-ext, pos[1]-ext, pos[2]+ext,  0, 0,  -1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]-ext, pos[1]-ext, pos[2]-ext,  0, 1,  -1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]-ext, pos[1]+ext, pos[2]-ext,  1, 1,  -1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]-ext, pos[1]+ext, pos[2]+ext,  1, 0,  -1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		// right
		{ pos[0]+ext, pos[1]-ext, pos[2]-ext,  0, 0,  +1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]-ext, pos[2]+ext,  0, 1,  +1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]+ext, pos[2]+ext,  1, 1,  +1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
		{ pos[0]+ext, pos[1]+ext, pos[2]-ext,  1, 0,  +1,  0,  0,  0,  1,  0, 1,  col[0], col[1], col[2], col[3] },
	};
	
	uint16_t indices[] =
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// left
		16, 17, 18,
		18, 19, 16,
		// right
		20, 21, 22,
		22, 23, 20,
	};
	
	sgs_PushStringBuf( C, (char*) vertices, sizeof(vertices) );
	sgs_PushStringBuf( C, (char*) indices, sizeof(indices) );
	sgs_PushInt( C, 4 * 6 );
	sgs_PushInt( C, 6 * 6 );
	return 4;
}

typedef struct _particleVtx
{
	VEC3 pos;
	float u, v;
	VEC4 color;
}
particleVtx;

static int SS3D_MeshGen_Particles( SGS_CTX )
{
	static const XGM_VT defdata[5] = { 1, 1, 1, 1, 0 };
	MAT4 viewmatrix;
	xgm_vtarray* arr_pos = NULL;
	xgm_vtarray* arr_size = NULL;
	xgm_vtarray* arr_color = NULL;
	xgm_vtarray* arr_angle = NULL;
	
	sgs_SizeVal i, position_count;
	XGM_VT* positions;
	const XGM_VT* sizes = defdata;
	sgs_SizeVal size_count = 1;
	const XGM_VT* colors = defdata;
	sgs_SizeVal color_count = 1;
	const XGM_VT* angles = defdata + 4;
	sgs_SizeVal angle_count = 1;
	
	particleVtx* vdata;
	uint16_t* idata;
	
	SGSFN( "SS3D_MeshGen_Particles" );
	if( !sgs_LoadArgs( C, "xx|xxx",
		sgs_ArgCheck_Mat4, viewmatrix,
		sgs_ArgCheck_FloatArray, &arr_pos,
		sgs_ArgCheck_FloatArray, &arr_size,
		sgs_ArgCheck_FloatArray, &arr_color,
		sgs_ArgCheck_FloatArray, &arr_angle ) )
		return 0;
	
	if( arr_pos->size < 3 )
		return sgs_Msg( C, SGS_WARNING, "positions float array must contain at least 3 items" );
	
	positions = arr_pos->data;
	position_count = arr_pos->size / 3;
	if( arr_size && arr_size->size >= 1 )
	{
		sizes = arr_size->data;
		size_count = arr_size->size;
	}
	if( arr_color && arr_color->size >= 4 )
	{
		colors = arr_color->data;
		color_count = arr_color->size / 4;
	}
	if( arr_angle && arr_angle->size >= 1 )
	{
		angles = arr_angle->data;
		angle_count = arr_angle->size;
	}
	
	viewmatrix[3][0] = viewmatrix[3][1] = viewmatrix[3][2] = 0;
	viewmatrix[0][3] = viewmatrix[1][3] = viewmatrix[2][3] = 0;
	viewmatrix[3][3] = 1;
	SS3D_Mtx_Transpose( viewmatrix );
	
	sgs_PushStringBuf( C, NULL, position_count * 4 * sizeof(*vdata) );
	vdata = (particleVtx*) sgs_GetStringPtr( C, -1 );
	
	for( i = 0; i < position_count; ++i )
	{
		float* position = positions + i * 3;
		float extent = sizes[ i % size_count ] * 0.5f;
		float angle = angles[ i % angle_count ];
		const float* color = colors + ( i % color_count ) * 4;
		float ang_sin = sin( angle ) * extent;
		float ang_cos = cos( angle ) * extent;
		
		VEC3 vp00 = { +ang_sin -ang_cos, -ang_sin -ang_cos, 0 };
		VEC3 vp10 = { +ang_sin +ang_cos, +ang_sin -ang_cos, 0 };
		VEC3 vp11 = { -ang_sin +ang_cos, +ang_sin +ang_cos, 0 };
		VEC3 vp01 = { -ang_sin -ang_cos, -ang_sin +ang_cos, 0 };
		
		SS3D_Mtx_TransformPos( vp00, vp00, viewmatrix );
		SS3D_Mtx_TransformPos( vp10, vp10, viewmatrix );
		SS3D_Mtx_TransformPos( vp11, vp11, viewmatrix );
		SS3D_Mtx_TransformPos( vp01, vp01, viewmatrix );
		
		VEC3_Add( vdata->pos, position, vp00 );
		vdata->u = 0; vdata->v = 0;
		VEC4_Copy( vdata->color, color );
		vdata++;
		
		VEC3_Add( vdata->pos, position, vp10 );
		vdata->u = 1; vdata->v = 0;
		VEC4_Copy( vdata->color, color );
		vdata++;
		
		VEC3_Add( vdata->pos, position, vp11 );
		vdata->u = 1; vdata->v = 1;
		VEC4_Copy( vdata->color, color );
		vdata++;
		
		VEC3_Add( vdata->pos, position, vp01 );
		vdata->u = 0; vdata->v = 1;
		VEC4_Copy( vdata->color, color );
		vdata++;
	}
	
	sgs_PushStringBuf( C, NULL, position_count * 6 * sizeof(*idata) );
	idata = (uint16_t*) sgs_GetStringPtr( C, -1 );
	
	for( i = 0; i < position_count; ++i )
	{
		uint16_t bv = i * 4;
		idata[0] = bv;
		idata[1] = bv+1;
		idata[2] = bv+2;
		idata[3] = bv+2;
		idata[4] = bv+3;
		idata[5] = bv;
		idata += 6;
	}
	
	sgs_PushInt( C, position_count * 4 );
	sgs_PushInt( C, position_count * 6 );
	
	return 4;
}


//
// MISC. UTILITY

static void scene_poke_resource( SS3D_Scene* S, sgs_VHTable* which, sgs_VarObj* obj, int add )
{
	sgs_Variable K;
	
	if( !S->renderer || S->destroying )
		return;
	
	sgs_InitPtr( &K, obj );
	if( add )
		sgs_vht_set( which, S->renderer->C, &K, &K );
	else
		sgs_vht_unset( which, S->renderer->C, &K );
}


//
// TEXTURE

static size_t divideup( size_t x, int d )
{
	return ( x + d - 1 ) / d;
}

size_t SS3D_TextureInfo_GetTextureSideSize( SS3D_TextureInfo* TI )
{
	size_t width = TI->width, height = TI->height, depth = TI->depth;
	int bpu = 0;
	switch( TI->format )
	{
	/* bytes per pixel */
	case SS3DFORMAT_BGRA8:
	case SS3DFORMAT_RGBA8: bpu = 4; break;
	case SS3DFORMAT_R5G6B5: bpu = 2; break;
	/* bytes per block */
	case SS3DFORMAT_DXT1: bpu = 8; break;
	case SS3DFORMAT_DXT3:
	case SS3DFORMAT_DXT5: bpu = 16; break;
	}
	if( SS3DFORMAT_ISBLOCK4FORMAT( TI->format ) )
	{
		width = divideup( width, 4 );
		height = divideup( height, 4 );
		depth = divideup( depth, 4 );
	}
	switch( TI->type )
	{
	case SS3DTEXTURE_2D: return width * height * bpu;
	case SS3DTEXTURE_CUBE: return width * width * bpu;
	case SS3DTEXTURE_VOLUME: return width * height * depth * bpu;
	}
	return 0;
}

void SS3D_TextureInfo_GetCopyDims( SS3D_TextureInfo* TI, size_t* outcopyrowsize, size_t* outcopyrowcount )
{
	size_t width = TI->width, height = TI->height, depth = TI->depth;
	int bpu = 0;
	switch( TI->format )
	{
	/* bytes per pixel */
	case SS3DFORMAT_BGRA8:
	case SS3DFORMAT_RGBA8: bpu = 4; break;
	case SS3DFORMAT_R5G6B5: bpu = 2; break;
	/* bytes per block */
	case SS3DFORMAT_DXT1: bpu = 8; break;
	case SS3DFORMAT_DXT3:
	case SS3DFORMAT_DXT5: bpu = 16; break;
	}
	if( SS3DFORMAT_ISBLOCK4FORMAT( TI->format ) )
	{
		width = divideup( width, 4 );
		height = divideup( height, 4 );
		depth = divideup( depth, 4 );
	}
	switch( TI->type )
	{
	case SS3DTEXTURE_2D: *outcopyrowsize = width * bpu; *outcopyrowcount = height; break;
	case SS3DTEXTURE_CUBE: *outcopyrowsize = width * bpu; *outcopyrowcount = width; break;
	case SS3DTEXTURE_VOLUME: *outcopyrowsize = width * bpu; *outcopyrowcount = height * depth; break;
	default: *outcopyrowsize = 0; *outcopyrowcount = 0; break;
	}
}

SGSBOOL SS3D_TextureInfo_GetMipInfo( SS3D_TextureInfo* TI, int mip, SS3D_TextureInfo* outinfo )
{
	SS3D_TextureInfo info = *TI;
	if( mip >= TI->mipcount )
		return 0;
	info.width /= pow( 2, mip ); if( info.width < 1 ) info.width = 1;
	info.height /= pow( 2, mip ); if( info.height < 1 ) info.height = 1;
	info.depth /= pow( 2, mip ); if( info.depth < 1 ) info.depth = 1;
	info.mipcount -= mip;
	*outinfo = info;
	return 1;
}


#define COLOR_EXTRACT_( c, off ) (((c)>>(off))&0xff)
#define COLOR_EXTRACT_R( c ) COLOR_EXTRACT_( c, 24 )
#define COLOR_EXTRACT_G( c ) COLOR_EXTRACT_( c, 16 )
#define COLOR_EXTRACT_B( c ) COLOR_EXTRACT_( c, 8 )
#define COLOR_EXTRACT_A( c ) COLOR_EXTRACT_( c, 0 )
#define COLOR_COMBINE( r, g, b, a ) (((r)<<24)|((g)<<16)|((b)<<8)|((a)))
static uint32_t _avg_col4( uint32_t a, uint32_t b, uint32_t c, uint32_t d )
{
	uint32_t or = ( COLOR_EXTRACT_R( a ) + COLOR_EXTRACT_R( b ) + COLOR_EXTRACT_R( c ) + COLOR_EXTRACT_R( d ) ) / 4;
	uint32_t og = ( COLOR_EXTRACT_G( a ) + COLOR_EXTRACT_G( b ) + COLOR_EXTRACT_G( c ) + COLOR_EXTRACT_G( d ) ) / 4;
	uint32_t ob = ( COLOR_EXTRACT_B( a ) + COLOR_EXTRACT_B( b ) + COLOR_EXTRACT_B( c ) + COLOR_EXTRACT_B( d ) ) / 4;
	uint32_t oa = ( COLOR_EXTRACT_A( a ) + COLOR_EXTRACT_A( b ) + COLOR_EXTRACT_A( c ) + COLOR_EXTRACT_A( d ) ) / 4;
	return COLOR_COMBINE( or, og, ob, oa );
}

static void _img_ds2x( uint32_t* dst, unsigned dstW, unsigned dstH, uint32_t* src, unsigned srcW, unsigned srcH )
{
	unsigned x, y, sx0, sy0, sx1, sy1;
	uint32_t c00, c10, c01, c11;
	for( y = 0; y < dstH; ++y )
	{
		for( x = 0; x < dstW; ++x )
		{
			sx0 = ( x * 2 ) % srcW;
			sy0 = ( y * 2 ) % srcH;
			sx1 = ( x * 2 + 1 ) % srcW;
			sy1 = ( y * 2 + 1 ) % srcH;
			
			c00 = src[ sx0 + sy0 * srcW ];
			c10 = src[ sx1 + sy0 * srcW ];
			c01 = src[ sx0 + sy1 * srcW ];
			c11 = src[ sx1 + sy1 * srcW ];
			
			dst[ x + y * dstW ] = _avg_col4( c00, c10, c01, c11 );
		}
	}
}

static int ddsfmt_to_enginefmt( dds_u32 fmt )
{
	switch( fmt )
	{
	case DDS_FMT_R8G8B8A8: return SS3DFORMAT_RGBA8;
	case DDS_FMT_B8G8R8A8: return SS3DFORMAT_BGRA8;
	case DDS_FMT_DXT1: return SS3DFORMAT_DXT1;
	case DDS_FMT_DXT3: return SS3DFORMAT_DXT3;
	case DDS_FMT_DXT5: return SS3DFORMAT_DXT5;
	default: return SS3DFORMAT_UNKNOWN;
	}
}

SGSRESULT SS3D_TextureData_LoadFromFile( SS3D_TextureData* TD, const char* file )
{
	unsigned char* out;
	unsigned w, h;
	int err;
	
	static const dds_u32 dds_supfmt[] = { DDS_FMT_R8G8B8A8, DDS_FMT_B8G8R8A8, DDS_FMT_DXT1, DDS_FMT_DXT3, DDS_FMT_DXT5, 0 };
	dds_info ddsinfo;
	
	memset( TD, 0, sizeof(*TD) );
	
	// Try to load DDS
	err = dds_load_from_file( file, &ddsinfo, dds_supfmt );
	if( err == DDS_ENOTFND ) return SGS_ENOTFND;
	if( err == DDS_SUCCESS )
	{
		dds_u32 cmf = ddsinfo.flags & DDS_CUBEMAP_FULL;
		if( cmf && cmf != DDS_CUBEMAP_FULL )
		{
			dds_close( &ddsinfo );
			return SGS_EINVAL;
		}
		TD->info.type = ddsinfo.flags & DDS_CUBEMAP ? SS3DTEXTURE_CUBE : ( ddsinfo.flags & DDS_VOLUME ? SS3DTEXTURE_VOLUME : SS3DTEXTURE_2D );
		TD->info.width = ddsinfo.image.width;
		TD->info.height = ddsinfo.image.height;
		TD->info.depth = ddsinfo.image.depth;
		TD->info.format = ddsfmt_to_enginefmt( ddsinfo.image.format );
		TD->info.mipcount = ddsinfo.mipcount;
		out = dds_read_all( &ddsinfo );
		dds_close( &ddsinfo );
		sgs_BreakIf( !out );
		goto success;
	}
	
	// Try to load PNG
	err = lodepng_decode32_file( &out, &w, &h, file );
	if( err == 78 ) return SGS_ENOTFND;
	if( err == 0 )
	{
		TD->info.type = SS3DTEXTURE_2D;
		TD->info.width = w;
		TD->info.height = h;
		TD->info.depth = 1;
		TD->info.format = SS3DFORMAT_RGBA8;
		TD->info.flags = 0;
		TD->info.mipcount = 1;
		goto success_genmips;
	}
	
	// type not supported
	goto failure;
	
success_genmips:
	if( TD->info.type == SS3DTEXTURE_2D && ( TD->info.format == SS3DFORMAT_RGBA8 || TD->info.format == SS3DFORMAT_BGRA8 ) )
	{
		size_t addspace = 0;
		unsigned char* old = out, *cur;
		
		// calculate additional space required
		while( w > 1 && h > 1 )
		{
			addspace += w * h * 4;
			w /= 2; if( w < 1 ) w = 1;
			h /= 2; if( h < 1 ) h = 1;
			TD->info.mipcount++;
		}
		addspace += 4; /* 1x1 */
		w = TD->info.width;
		h = TD->info.height;
		
		// reallocate
		out = (unsigned char*) malloc( addspace );
		memcpy( out, old, w * h * 4 );
		free( old );
		
		// do cascaded ds2x
		cur = out;
		while( w > 1 && h > 1 )
		{
			unsigned char* dst = cur + w * h * 4;
			unsigned pw = w, ph = h;
			w /= 2; if( w < 1 ) w = 1;
			h /= 2; if( h < 1 ) h = 1;
			_img_ds2x( (uint32_t*) dst, w, h, (uint32_t*) cur, pw, ph );
			cur = dst;
		}
	}
success:
	TD->data = out;
	return SGS_SUCCESS;
failure:
	return SGS_ENOTSUP;
}

void SS3D_TextureData_Free( SS3D_TextureData* TD )
{
	if( TD->data )
		free( TD->data );
}

size_t SS3D_TextureData_GetMipDataOffset( SS3D_TextureData* TD, int side, int mip )
{
	size_t off = 0;
	int mipit = mip;
	while( mipit --> 0 )
		off += SS3D_TextureData_GetMipDataSize( TD, mipit );
	if( side && TD->info.type == SS3DTEXTURE_CUBE )
	{
		size_t fullsidesize = 0;
		mipit = TD->info.mipcount;
		while( mipit --> 0 )
			fullsidesize += SS3D_TextureData_GetMipDataSize( TD, mipit );
		off += fullsidesize * side;
	}
	return off;
}

size_t SS3D_TextureData_GetMipDataSize( SS3D_TextureData* TD, int mip )
{
	SS3D_TextureInfo mipTI;
	if( !SS3D_TextureInfo_GetMipInfo( &TD->info, mip, &mipTI ) )
		return 0;
	return SS3D_TextureInfo_GetTextureSideSize( &mipTI );
}


//
// MESH PARSING

/* FORMAT
	BUFFER: (min size = 4)
	- uint32 size
	- uint8 data[size]
	
	SMALLBUF: (min size = 1)
	- uint8 size
	- uint8 data[size]
	
	PART: (min size = 19)
	- uint32 voff
	- uint32 vcount
	- uint32 ioff
	- uint32 icount
	- uint16 flags
	- uint8 texcount
	- smallbuf shader
	- smallbuf textures[texcount]
	
	MESH:
	- magic "SS3DMESH"
	- uint32 flags
	
	- float boundsmin[3]
	- float boundsmax[3]
	- float center[3]
	- float radius
	
	- buffer vdata
	- buffer idata
	- smallbuf format
	- uint8 numparts
	- part parts[numparts]
	
	minimum size = 12+40+10 = 62
*/

static int md_parse_buffer( char* buf, size_t size, char** outptr, uint32_t* outsize )
{
	if( size < 4 )
		return 0;
	memcpy( outsize, buf, 4 );
	if( size < *outsize + 4 )
		return 0;
	*outptr = buf + 4;
	return 1;
}

static int md_parse_smallbuf( char* buf, size_t size, char** outptr, uint8_t* outsize )
{
	if( size < 1 )
		return 0;
	memcpy( outsize, buf, 1 );
	if( size < *outsize + 1 )
		return 0;
	*outptr = buf + 1;
	return 1;
}

int SS3D_MeshData_Parse( char* buf, size_t size, SS3D_MeshFileData* out )
{
	uint8_t p, t;
	size_t off = 0;
	if( size < 61 || memcmp( buf, "SS3DMESH", 8 ) != 0 )
		return 0;
	memcpy( &out->dataFlags, buf + 8, 4 );
	memcpy( &out->boundsMin, buf + 12, 12 );
	memcpy( &out->boundsMax, buf + 24, 12 );
	memcpy( &out->center, buf + 36, 12 );
	memcpy( &out->radius, buf + 48, 4 );
	off = 52;
	if( !md_parse_buffer( buf + 52, size - 52, &out->vertexData, &out->vertexDataSize ) )
		return 0;
	off += 4 + out->vertexDataSize;
	if( !md_parse_buffer( buf + off, size - off, &out->indexData, &out->indexDataSize ) )
		return 0;
	off += 4 + out->indexDataSize;
	if( !md_parse_smallbuf( buf + off, size - off, &out->formatData, &out->formatSize ) )
		return 0;
	off += 1 + out->formatSize;
	if( off >= size )
		return 0;
	out->numParts = (uint8_t) buf[ off++ ];
	if( out->numParts > SS3D_MAX_MESH_PARTS )
		return 0;
	for( p = 0; p < out->numParts; ++p )
	{
		SS3D_MeshFilePartData* pout = out->parts + p;
		memset( pout, 0, sizeof(*pout) );
		if( off + 19 > size )
			return 0;
		memcpy( &pout->vertexOffset, buf + off, 4 ); off += 4;
		memcpy( &pout->vertexCount, buf + off, 4 ); off += 4;
		memcpy( &pout->indexOffset, buf + off, 4 ); off += 4;
		memcpy( &pout->indexCount, buf + off, 4 ); off += 4;
		memcpy( &pout->materialFlags, buf + off, 2 ); off += 2;
		memcpy( &pout->materialTextureCount, buf + off, 1 ); off += 1;
		for( t = 0; t < pout->materialTextureCount + 1; ++t )
		{
			if( !md_parse_smallbuf( buf + off, size - off, &pout->materialStrings[t], &pout->materialStringSizes[t] ) )
				return 0;
			off += 1 + pout->materialStringSizes[t];
		}
	}
	return 1;
}


//
// VDECL

#define USAGE_PADDING 723
const char* SS3D_VDeclInfo_Parse( SS3D_VDeclInfo* info, const char* text )
{
	int offset = 0, count = 0, align32 = 0;
	if( *text == '|' )
	{
		align32 = 1;
		text++;
	}
	while( *text )
	{
		int usage = -1, type = -1, size = -1;
		char chr_usage, chr_type, chr_mult;
		chr_usage = *text++; if( !chr_usage ) return "unexpected end of sequence";
		chr_type = *text++; if( !chr_type ) return "unexpected end of sequence";
		chr_mult = *text++; if( !chr_mult ) return "unexpected end of sequence";
		
		if( chr_usage == 'p' ) usage = SS3D_VDECLUSAGE_POSITION;
		else if( chr_usage == 'c' ) usage = SS3D_VDECLUSAGE_COLOR;
		else if( chr_usage == 'n' ) usage = SS3D_VDECLUSAGE_NORMAL;
		else if( chr_usage == 't' ) usage = SS3D_VDECLUSAGE_TANGENT;
		else if( chr_usage == '0' ) usage = SS3D_VDECLUSAGE_TEXTURE0;
		else if( chr_usage == '1' ) usage = SS3D_VDECLUSAGE_TEXTURE1;
		else if( chr_usage == '2' ) usage = SS3D_VDECLUSAGE_TEXTURE2;
		else if( chr_usage == '3' ) usage = SS3D_VDECLUSAGE_TEXTURE3;
		else if( chr_usage == 'x' ) usage = USAGE_PADDING;
		else return "usage type specifier not recognized";
		
		if( chr_type == 'f' )
		{
			if( chr_mult == '1' ){ type = SS3D_VDECLTYPE_FLOAT1; size = 4; }
			else if( chr_mult == '2' ){ type = SS3D_VDECLTYPE_FLOAT2; size = 8; }
			else if( chr_mult == '3' ){ type = SS3D_VDECLTYPE_FLOAT3; size = 12; }
			else if( chr_mult == '4' ){ type = SS3D_VDECLTYPE_FLOAT4; size = 16; }
			else return "invalid multiplier";
		}
		else if( chr_type == 'b' )
		{
			if( chr_mult == '1' || chr_mult == '2' || chr_mult == '3' )
				return "type/multiplier combo not supported";
			else if( chr_mult == '4' ){ type = SS3D_VDECLTYPE_BCOL4; size = 4; }
			else return "invalid multiplier";
		}
		else return "invalid data type specified";
		
		if( usage != USAGE_PADDING )
		{
			info->offsets[ count ] = offset;
			info->types[ count ] = type;
			info->usages[ count ] = usage;
			count++;
		}
		offset += size;
	}
	
	if( align32 )
		offset = ( ( offset + 31 ) / 32 ) * 32;
	
	if( offset == 0 )
		return "vertex is empty";
	if( offset > 255 )
		return "vertex size too big (> 255)";
	
	info->count = count;
	info->size = offset;
	
	return NULL;
}


//
// MATERIAL

#if 0
#define MTL_HDR SS3D_Material* MTL = (SS3D_Material*) obj->data;
#define MTL_IHDR( funcname ) SS3D_Material* MTL; \
	if( !SGS_PARSE_METHOD( C, SS3D_Material_iface, MTL, SS3D_Material, funcname ) ) return 0;

static int material_destruct( SGS_CTX, sgs_VarObj* obj )
{
	MTL_HDR;
	if( MTL->renderer )
	{
		int i;
		MTL->renderer = NULL;
		if( MTL->shader )
		{
			sgs_ObjRelease( C, MTL->shader );
			MTL->shader = NULL;
		}
		for( i = 0; i < SS3D_NUM_MATERIAL_TEXTURES; ++i )
		{
			if( MTL->textures[i] )
			{
				sgs_ObjRelease( C, MTL->textures[i] );
				MTL->textures[i] = NULL;
			}
		}
	}
	return SGS_SUCCESS;
}

static int material_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	int i;
	MTL_HDR;
	if( MTL->shader )
	{
		sgs_ObjGCMark( C, MTL->shader );
		MTL->shader = NULL;
	}
	for( i = 0; i < SS3D_NUM_MATERIAL_TEXTURES; ++i )
	{
		if( MTL->textures[i] )
		{
			sgs_ObjGCMark( C, MTL->textures[i] );
			MTL->textures[i] = NULL;
		}
	}
	return SGS_SUCCESS;
}

static int material_setTexture( SGS_CTX )
{
	sgs_Int index;
	MTL_IHDR( setTexture );
	if( !sgs_LoadArgs( C, "i|?o", &index, MTL->renderer->ifTexture ) )
		return 0;
	if( index < 0 || index >= SS3D_NUM_MATERIAL_TEXTURES )
		return sgs_Msg( C, SGS_WARNING, "texture index %d not available", (int) index );
	sgs_ObjAssign( C, &MTL->textures[ index ], sgs_ItemType( C, 1 ) == SGS_VT_OBJECT ? sgs_GetObjectStruct( C, 1 ) : NULL );
	SGS_RETURN_BOOL( 1 )
}

static int material_getindex( SGS_ARGS_GETINDEXFUNC )
{
	MTL_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "transparent" ) SGS_RETURN_BOOL( MTL->transparent )
		SGS_CASE( "shader" )     SGS_RETURN_OBJECT( MTL->shader )
		
		SGS_CASE( "setTexture" ) SGS_RETURN_CFUNC( material_setTexture )
	SGS_END_INDEXFUNC;
}

static int material_setindex( SGS_ARGS_SETINDEXFUNC )
{
	MTL_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "transparent" ) SGS_PARSE_BOOL( MTL->transparent )
		SGS_CASE( "shader" )    { if( !MTL->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( MTL->renderer->ifShader, MTL->shader, 0 ) }
	SGS_END_INDEXFUNC;
}

sgs_ObjInterface SS3D_Material_iface[1] =
{{
	"SS3D_Material",
	material_destruct, material_gcmark,
	material_getindex, material_setindex,
	NULL, NULL, NULL, NULL,
	NULL, NULL
}};

int SS3D_Material_Create( SS3D_Renderer* R )
{
	SS3D_Material* MTL = (SS3D_Material*) sgs_PushObjectIPA( R->C, sizeof(*MTL), SS3D_Material_iface );
	memset( MTL, 0, sizeof(*MTL) );
	MTL->renderer = R;
	return 1;
}
#endif


//
// MESH

void SS3D_Mesh_Init( SS3D_Mesh* mesh )
{
	mesh->renderer = NULL;
	
	mesh->dataFlags = 0;
	mesh->vertexDecl = NULL;
	mesh->vertexCount = 0;
	mesh->vertexDataSize = 0;
	mesh->indexCount = 0;
	mesh->indexDataSize = 0;
	memset( mesh->parts, 0, sizeof( mesh->parts ) );
	mesh->numParts = 0;
	
	VEC3_Set( mesh->boundsMin, 0, 0, 0 );
	VEC3_Set( mesh->boundsMax, 0, 0, 0 );
	VEC3_Set( mesh->center, 0, 0, 0 );
	mesh->radius = 0;
}


//
// MESH INSTANCE

#define MI_HDR SS3D_MeshInstance* MI = (SS3D_MeshInstance*) obj->data

static int meshinst_destruct( SGS_CTX, sgs_VarObj* obj )
{
	MI_HDR;
	if( MI->scene )
	{
		scene_poke_resource( MI->scene, &MI->scene->meshInstances, obj, 0 );
		MI->scene = NULL;
		if( MI->mesh )
		{
			sgs_ObjRelease( C, MI->mesh );
			MI->mesh = NULL;
		}
	}
	return SGS_SUCCESS;
}

static int meshinst_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	MI_HDR;
	if( MI->mesh )
		sgs_ObjGCMark( C, MI->mesh );
	return SGS_SUCCESS;
}

static int meshinst_getindex( SGS_ARGS_GETINDEXFUNC )
{
	MI_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mesh" )    SGS_RETURN_OBJECT( MI->mesh )
		SGS_CASE( "matrix" )  SGS_RETURN_MAT4( *MI->matrix )
		SGS_CASE( "color" )   SGS_RETURN_COLOR( MI->color )
		SGS_CASE( "enabled" ) SGS_RETURN_BOOL( MI->enabled )
	SGS_END_INDEXFUNC;
}

static int meshinst_setindex( SGS_ARGS_SETINDEXFUNC )
{
	MI_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mesh" )    { if( !MI->scene || !MI->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( MI->scene->renderer->ifMesh, MI->mesh, 0 ) }
		SGS_CASE( "matrix" )  SGS_PARSE_MAT4( *MI->matrix )
		SGS_CASE( "color" )   SGS_PARSE_COLOR( MI->color, 0 )
		SGS_CASE( "enabled" ) SGS_PARSE_BOOL( MI->enabled )
	SGS_END_INDEXFUNC;
}

sgs_ObjInterface SS3D_MeshInstance_iface[1] =
{{
	"SS3D_MeshInstance",
	meshinst_destruct, meshinst_gcmark,
	meshinst_getindex, meshinst_setindex,
	NULL, NULL, NULL, NULL,
	NULL, NULL
}};


//
// LIGHT

#define L_HDR SS3D_Light* L = (SS3D_Light*) obj->data;

static int light_getindex( SGS_ARGS_GETINDEXFUNC )
{
	L_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" )          SGS_RETURN_INT( L->type )
		SGS_CASE( "isEnabled" )     SGS_RETURN_BOOL( L->isEnabled )
		SGS_CASE( "position" )      SGS_RETURN_VEC3P( L->position )
		SGS_CASE( "direction" )     SGS_RETURN_VEC3P( L->direction )
		SGS_CASE( "color" )         SGS_RETURN_VEC3P( L->color )
		SGS_CASE( "range" )         SGS_RETURN_REAL( L->range )
		SGS_CASE( "power" )         SGS_RETURN_REAL( L->power )
		SGS_CASE( "minangle" )      SGS_RETURN_REAL( L->minangle )
		SGS_CASE( "maxangle" )      SGS_RETURN_REAL( L->maxangle )
		SGS_CASE( "cookieTexture" ) SGS_RETURN_OBJECT( L->cookieTexture )
		SGS_CASE( "projMatrix" )    SGS_RETURN_MAT4( *L->projMatrix )
		SGS_CASE( "hasShadows" )    SGS_RETURN_BOOL( L->hasShadows )
	SGS_END_INDEXFUNC;
}

static int light_setindex( SGS_ARGS_SETINDEXFUNC )
{
	L_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" )          SGS_PARSE_INT( L->type )
		SGS_CASE( "isEnabled" )     SGS_PARSE_BOOL( L->isEnabled )
		SGS_CASE( "position" )      SGS_PARSE_VEC3( L->position, 0 )
		SGS_CASE( "direction" )     SGS_PARSE_VEC3( L->direction, 0 )
		SGS_CASE( "color" )         SGS_PARSE_VEC3( L->color, 0 )
		SGS_CASE( "range" )         SGS_PARSE_REAL( L->range )
		SGS_CASE( "power" )         SGS_PARSE_REAL( L->power )
		SGS_CASE( "minangle" )      SGS_PARSE_REAL( L->minangle )
		SGS_CASE( "maxangle" )      SGS_PARSE_REAL( L->maxangle )
		SGS_CASE( "cookieTexture" ) { if( !L->scene || !L->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( L->scene->renderer->ifTexture, L->cookieTexture, 0 ) }
		SGS_CASE( "projMatrix" )    SGS_PARSE_MAT4( *L->projMatrix )
		SGS_CASE( "hasShadows" )    SGS_PARSE_BOOL( L->hasShadows )
	SGS_END_INDEXFUNC;
}

static int light_convert( SGS_CTX, sgs_VarObj* obj, int type )
{
	L_HDR;
	if( type == SGS_VT_STRING )
	{
		char bfr[ 32 ];
		sprintf( bfr, "SS3D_Light (%.10s)", L->scene && L->scene->renderer ? L->scene->renderer->API : "unloaded" );
		sgs_PushString( C, bfr );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int light_dump( SGS_CTX, sgs_VarObj* obj, int maxdepth )
{
	char bfr[ 2048 ];
	L_HDR;
	UNUSED( maxdepth );
	
	sprintf( bfr,
		"\ntype=%d"
		"\nisEnabled=%s"
		"\nposition=(%g;%g;%g)"
		"\ndirection=(%g;%g;%g)"
		"\ncolor=(%g;%g;%g)"
		"\nrange=%g"
		"\npower=%g"
		"\nminangle=%g"
		"\nmaxangle=%g"
		"\ncookieTexture=%p"
		"\nprojMatrix=..."
		"\nhasShadows=%s",
		L->type,
		L->isEnabled ? "true" : "false",
		L->position[0], L->position[1], L->position[2],
		L->direction[0], L->direction[1], L->direction[2],
		L->color[0], L->color[1], L->color[2],
		L->range,
		L->power,
		L->minangle,
		L->maxangle,
		L->cookieTexture,
		// projMatrix ...
		L->hasShadows ? "true" : "false"
	);
	sgs_PushString( C, "SS3D_Light\n{" );
	sgs_PushString( C, bfr );
	sgs_PadString( C );
	sgs_PushString( C, "\n}" );
	sgs_StringConcat( C, 3 );
	return SGS_SUCCESS;
}

static int light_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	L_HDR;
	if( L->cookieTexture )
		sgs_ObjGCMark( C, L->cookieTexture );
	return SGS_SUCCESS;
}

static int light_destruct( SGS_CTX, sgs_VarObj* obj )
{
	L_HDR;
	if( L->scene )
	{
		scene_poke_resource( L->scene, &L->scene->lights, obj, 0 );
		L->scene = NULL;
		if( L->cookieTexture )
		{
			sgs_ObjRelease( C, L->cookieTexture );
			L->cookieTexture = NULL;
		}
	}
	return SGS_SUCCESS;
}

sgs_ObjInterface SS3D_Light_iface[1] =
{{
	"SS3D_Light",
	light_destruct, light_gcmark,
	light_getindex, light_setindex,
	light_convert, NULL, light_dump, NULL,
	NULL, NULL
}};


//
// CULL SCENE

sgs_ObjInterface SS3D_CullScene_iface[1] =
{{
	"SS3D_CullScene",
	NULL, NULL,
	NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL,
}};


//
// CAMERA

static void camera_recalc_viewmtx( SS3D_Camera* CAM )
{
	SS3D_Mtx_LookAt( CAM->mView, CAM->position, CAM->direction, CAM->up );
	memcpy( CAM->mInvView, CAM->mView, sizeof( CAM->mView ) );
	SS3D_Mtx_Transpose( CAM->mInvView );
}

static void camera_recalc_projmtx( SS3D_Camera* CAM )
{
	SS3D_Mtx_Perspective( CAM->mProj, CAM->angle, CAM->aspect, CAM->aamix, CAM->znear, CAM->zfar );
}

#define CAM_HDR SS3D_Camera* CAM = (SS3D_Camera*) obj->data;
#define CAM_IHDR( funcname ) SS3D_Camera* CAM; \
	if( !SGS_PARSE_METHOD( C, SS3D_Camera_iface, CAM, SS3D_Camera, funcname ) ) return 0;

static int camerai_worldToScreen( SGS_CTX )
{
	VEC3 pos;
	CAM_IHDR( worldToScreen );
	if( !sgs_LoadArgs( C, "x", sgs_ArgCheck_Vec3, pos ) )
		return 0;
	
	SS3D_Mtx_TransformPos( pos, pos, CAM->mView );
	SS3D_Mtx_TransformPos( pos, pos, CAM->mProj );
	pos[0] = pos[0] * 0.5f + 0.5f;
	pos[1] = pos[1] * -0.5f + 0.5f;
	sgs_PushVec3p( C, pos );
	return 1;
}

static int camera_getindex( SGS_ARGS_GETINDEXFUNC )
{
	CAM_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" )  SGS_RETURN_VEC3P( CAM->position )
		SGS_CASE( "direction" ) SGS_RETURN_VEC3P( CAM->direction )
		SGS_CASE( "up" )        SGS_RETURN_VEC3P( CAM->up )
		SGS_CASE( "angle" )     SGS_RETURN_REAL( CAM->angle )
		SGS_CASE( "aspect" )    SGS_RETURN_REAL( CAM->aspect )
		SGS_CASE( "aamix" )     SGS_RETURN_REAL( CAM->aamix )
		SGS_CASE( "znear" )     SGS_RETURN_REAL( CAM->znear )
		SGS_CASE( "zfar" )      SGS_RETURN_REAL( CAM->zfar )
		
		SGS_CASE( "viewMatrix" ) SGS_RETURN_MAT4( *CAM->mView )
		SGS_CASE( "invViewMatrix" ) SGS_RETURN_MAT4( *CAM->mInvView )
		SGS_CASE( "projMatrix" ) SGS_RETURN_MAT4( *CAM->mProj )
		
		SGS_CASE( "worldToScreen" ) SGS_RETURN_CFUNC( camerai_worldToScreen )
	SGS_END_INDEXFUNC;
}

static int camera_setindex_( SGS_ARGS_SETINDEXFUNC )
{
	CAM_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" )  { return sgs_ParseVec3P( C, val, CAM->position, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "direction" ) { return sgs_ParseVec3P( C, val, CAM->direction, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "up" )        { return sgs_ParseVec3P( C, val, CAM->up, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "angle" )     { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->angle = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "aspect" )    { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->aspect = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "aamix" )     { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->aamix = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "znear" )     { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->znear = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "zfar" )      { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->zfar = V; return 2; } return SGS_EINVAL; }
	SGS_END_INDEXFUNC;
}

static int camera_setindex( SGS_ARGS_SETINDEXFUNC )
{
	CAM_HDR;
	int ret = camera_setindex_( C, obj, key, val, isprop );
	if( ret < 0 )
		return ret;
	if( ret == 1 ) camera_recalc_viewmtx( CAM );
	if( ret == 2 ) camera_recalc_projmtx( CAM );
	return SGS_SUCCESS;
}

static int camera_dump( SGS_CTX, sgs_VarObj* obj, int maxdepth )
{
	char bfr[ 2048 ];
	CAM_HDR;
	UNUSED( maxdepth );
	
	sprintf( bfr,
		"\nposition=(%g;%g;%g)"
		"\ndirection=(%g;%g;%g)"
		"\nup=(%g;%g;%g)"
		"\nangle=%g"
		"\naspect=%g"
		"\naamix=%g"
		"\nznear=%g"
		"\nzfar=%g",
		CAM->position[0], CAM->position[1], CAM->position[2],
		CAM->direction[0], CAM->direction[1], CAM->direction[2],
		CAM->up[0], CAM->up[1], CAM->up[2],
		CAM->angle,
		CAM->aspect,
		CAM->aamix,
		CAM->znear,
		CAM->zfar
	);
	sgs_PushString( C, "SS3D_Camera\n{" );
	sgs_PushString( C, bfr );
	sgs_PadString( C );
	sgs_PushString( C, "\n}" );
	sgs_StringConcat( C, 3 );
	return SGS_SUCCESS;
}

sgs_ObjInterface SS3D_Camera_iface[1] =
{{
	"SS3D_Camera",
	NULL, NULL,
	camera_getindex, camera_setindex,
	NULL, NULL, camera_dump, NULL,
	NULL, NULL,
}};

int SS3D_CreateCamera( SGS_CTX )
{
	SS3D_Camera* CAM = (SS3D_Camera*) sgs_PushObjectIPA( C, sizeof(*CAM), SS3D_Camera_iface );
	VEC3_Set( CAM->position, 0, 0, 0 );
	VEC3_Set( CAM->direction, 0, 1, 0 );
	VEC3_Set( CAM->up, 0, 0, 1 );
	CAM->angle = 90;
	CAM->aspect = 1;
	CAM->aamix = 0.5;
	CAM->znear = 1;
	CAM->zfar = 1000;
	
	camera_recalc_viewmtx( CAM );
	camera_recalc_projmtx( CAM );
	
	return 1;
}


//
// VIEWPORT

#define VP_HDR SS3D_Viewport* VP = (SS3D_Viewport*) obj->data;

static int viewport_getindex( SGS_ARGS_GETINDEXFUNC )
{
	VP_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "x1" )  SGS_RETURN_INT( VP->x1 )
		SGS_CASE( "y1" )  SGS_RETURN_INT( VP->y1 )
		SGS_CASE( "x2" )  SGS_RETURN_INT( VP->x2 )
		SGS_CASE( "y2" )  SGS_RETURN_INT( VP->y2 )
	SGS_END_INDEXFUNC;
}

static int viewport_setindex( SGS_ARGS_SETINDEXFUNC )
{
	VP_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "x1" )  SGS_PARSE_INT( VP->x1 )
		SGS_CASE( "y1" )  SGS_PARSE_INT( VP->y1 )
		SGS_CASE( "x2" )  SGS_PARSE_INT( VP->x2 )
		SGS_CASE( "y2" )  SGS_PARSE_INT( VP->y2 )
	SGS_END_INDEXFUNC;
}

static int viewport_dump( SGS_CTX, sgs_VarObj* obj, int maxdepth )
{
	char bfr[ 2048 ];
	VP_HDR;
	UNUSED( maxdepth );
	
	sprintf( bfr,
		"\nx1=%d"
		"\ny1=%d"
		"\nx2=%d"
		"\ny2=%d",
		VP->x1,
		VP->y1,
		VP->x2,
		VP->y2
	);
	sgs_PushString( C, "SS3D_Viewport\n{" );
	sgs_PushString( C, bfr );
	sgs_PadString( C );
	sgs_PushString( C, "\n}" );
	sgs_StringConcat( C, 3 );
	return SGS_SUCCESS;
}

sgs_ObjInterface SS3D_Viewport_iface[1] =
{{
	"SS3D_Viewport",
	NULL, NULL,
	viewport_getindex, viewport_setindex,
	NULL, NULL, viewport_dump, NULL,
	NULL, NULL,
}};

int SS3D_CreateViewport( SGS_CTX )
{
	SS3D_Viewport* VP = (SS3D_Viewport*) sgs_PushObjectIPA( C, sizeof(*VP), SS3D_Viewport_iface );
	VP->x1 = 0;
	VP->y1 = 0;
	VP->x2 = 100;
	VP->y2 = 100;
	
	return 1;
}


//
// SCENE

#define SC_HDR SS3D_Scene* S = (SS3D_Scene*) obj->data;
#define SC_IHDR( funcname ) SS3D_Scene* S; \
	if( !SGS_PARSE_METHOD( C, SS3D_Scene_iface, S, SS3D_Scene, funcname ) ) return 0;

static int scenei_createMeshInstance( SGS_CTX )
{
	SS3D_MeshInstance* MI;
	SC_IHDR( createMeshInstance );
	MI = (SS3D_MeshInstance*) sgs_PushObjectIPA( C, sizeof(*MI), SS3D_MeshInstance_iface );
	
	MI->scene = S;
	MI->mesh = NULL;
	SS3D_Mtx_Identity( MI->matrix );
	VEC4_Set( MI->color, 1, 1, 1, 1 );
	MI->enabled = 1;
	
	scene_poke_resource( S, &S->meshInstances, sgs_GetObjectStruct( C, -1 ), 1 );
	return 1;
}

static int scenei_destroyMeshInstance( SGS_CTX )
{
	SC_IHDR( destroyMeshInstance );
	if( !sgs_LoadArgs( C, "?o", SS3D_MeshInstance_iface ) )
		return 0;
	
	sgs_ObjCallDtor( C, sgs_GetObjectStruct( C, 0 ) );
	return 0;
}

static int scenei_createLight( SGS_CTX )
{
	SS3D_Light* L;
	SC_IHDR( createLight );
	L = (SS3D_Light*) sgs_PushObjectIPA( C, sizeof(*L), SS3D_Light_iface );
	
	memset( L, 0, sizeof(*L) );
	L->scene = S;
	
	scene_poke_resource( S, &S->lights, sgs_GetObjectStruct( C, -1 ), 1 );
	return 1;
}

static int scenei_destroyLight( SGS_CTX )
{
	SC_IHDR( destroyLight );
	if( !sgs_LoadArgs( C, "?o", SS3D_Light_iface ) )
		return 0;
	
	sgs_ObjCallDtor( C, sgs_GetObjectStruct( C, 0 ) );
	return 0;
}

static int scene_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SC_HDR;
	SGS_BEGIN_INDEXFUNC
		// methods
		SGS_CASE( "createMeshInstance" )  SGS_RETURN_CFUNC( scenei_createMeshInstance )
		SGS_CASE( "destroyMeshInstance" ) SGS_RETURN_CFUNC( scenei_destroyMeshInstance )
		SGS_CASE( "createLight" )         SGS_RETURN_CFUNC( scenei_createLight )
		SGS_CASE( "destroyLight" )        SGS_RETURN_CFUNC( scenei_destroyLight )
		
		// properties
		SGS_CASE( "cullScene" ) SGS_RETURN_OBJECT( S->cullScene )
		SGS_CASE( "camera" )    SGS_RETURN_OBJECT( S->camera )
		SGS_CASE( "viewport" )  SGS_RETURN_OBJECT( S->viewport )
	SGS_END_INDEXFUNC;
}

static int scene_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SC_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "cullScene" )
		{
			if( val->type == SGS_VT_NULL )
			{
				if( S->cullScene )
					sgs_ObjRelease( C, S->cullScene );
				S->cullScene = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObjectP( val, SS3D_CullScene_iface ) )
			{
				if( S->cullScene )
					sgs_ObjRelease( C, S->cullScene );
				S->cullScene = sgs_GetObjectStructP( val );
				sgs_ObjAcquire( C, S->cullScene );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		SGS_CASE( "camera" )
		{
			if( val->type == SGS_VT_NULL )
			{
				if( S->camera )
					sgs_ObjRelease( C, S->camera );
				S->camera = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObjectP( val, SS3D_Camera_iface ) )
			{
				if( S->camera )
					sgs_ObjRelease( C, S->camera );
				S->camera = sgs_GetObjectStructP( val );
				sgs_ObjAcquire( C, S->camera );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		SGS_CASE( "viewport" )
		{
			if( val->type == SGS_VT_NULL )
			{
				if( S->viewport )
					sgs_ObjRelease( C, S->viewport );
				S->viewport = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObjectP( val, SS3D_Viewport_iface ) )
			{
				if( S->viewport )
					sgs_ObjRelease( C, S->viewport );
				S->viewport = sgs_GetObjectStructP( val );
				sgs_ObjAcquire( C, S->viewport );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
	SGS_END_INDEXFUNC;
}

static int scene_convert( SGS_CTX, sgs_VarObj* obj, int type )
{
	SC_HDR;
	if( type == SGS_VT_STRING )
	{
		char bfr[ 32 ];
		sprintf( bfr, "SS3D_Scene (%.10s)", S->renderer ? S->renderer->API : "unloaded" );
		sgs_PushString( C, bfr );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int scene_destruct( SGS_CTX, sgs_VarObj* obj )
{
	sgs_SizeVal i;
	SC_HDR;
	if( S->renderer )
	{
		SS3D_Renderer_PokeResource( S->renderer, obj, 0 );
		S->renderer = NULL;
		S->destroying = 1;
		for( i = 0; i < S->meshInstances.size; ++i )
		{
			sgs_VarObj* obj = (sgs_VarObj*) S->meshInstances.vars[ i ].val.data.P;
			sgs_ObjCallDtor( C, obj );
		}
		for( i = 0; i < S->lights.size; ++i )
		{
			sgs_VarObj* obj = (sgs_VarObj*) S->lights.vars[ i ].val.data.P;
			sgs_ObjCallDtor( C, obj );
		}
		sgs_vht_free( &S->meshInstances, C );
		sgs_vht_free( &S->lights, C );
		if( S->cullScene )
		{
			sgs_ObjRelease( C, S->cullScene );
			S->cullScene = NULL;
		}
	}
	return SGS_SUCCESS;
}

sgs_ObjInterface SS3D_Scene_iface[1] =
{{
	"SS3D_Scene",
	scene_destruct, NULL,
	scene_getindex, scene_setindex,
	scene_convert, NULL, NULL, NULL,
	NULL, NULL
}};


//
// RENDERER

void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX )
{
	sgs_Variable storeVar;
	memset( R, 0, sizeof(*R) );
	R->C = C;
	R->destroying = 0;
	sgs_vht_init( &R->resources, C, 128, 128 );
	sgs_vht_init( &R->shaders, C, 128, 128 );
	sgs_vht_init( &R->textures, C, 128, 128 );
	sgs_vht_init( &R->materials, C, 128, 128 );
	R->currentScene = NULL;
	
	sgs_InitDict( C, &storeVar, 0 );
	R->store = sgs_GetObjectStructP( &storeVar );
	
	/* default pass info */
	memset( R->passes, 0, sizeof(R->passes) );
	R->numPasses = 8;
	/* PASS1: [SOLID,STATIC] LIGHTMAP + SUN + 0-16 POINT LIGHTS (once) */
	R->passes[0].type = SS3D_RPT_OBJECT;
	R->passes[0].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_STATIC | SS3D_RPF_ENABLED;
	R->passes[0].maxruns = 1;
	R->passes[0].pointlight_count = 16;
	R->passes[0].spotlight_count = 0;
	R->passes[0].num_inst_textures = 4;
	strcpy( R->passes[0].shname, "ps_base_isp16" );
	/* PASS2: [SOLID,DYNAMIC] DIRAMB + SUN + 0-16 POINT LIGHTS (once) */
	R->passes[1].type = SS3D_RPT_OBJECT;
	R->passes[1].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_DYNAMIC | SS3D_RPF_ENABLED | SS3D_RPF_CALC_DIRAMB;
	R->passes[1].maxruns = 1;
	R->passes[1].pointlight_count = 16;
	R->passes[1].spotlight_count = 0;
	R->passes[1].num_inst_textures = 0;
	strcpy( R->passes[1].shname, "ps_base_dsp16" );
	/* PASS3: [SOLID,ANY] 0-16 POINT LIGHTS (as much as necessary) */
	R->passes[2].type = SS3D_RPT_OBJECT;
	R->passes[2].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[2].maxruns = -1;
	R->passes[2].pointlight_count = 16;
	R->passes[2].spotlight_count = 0;
	R->passes[2].num_inst_textures = 0;
	strcpy( R->passes[2].shname, "ps_ext_p16" );
	/* PASS4: [SOLID,ANY] 0-4 SPOT LIGHTS (as much as necessary) */
	R->passes[3].type = SS3D_RPT_OBJECT;
	R->passes[3].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[3].maxruns = -1;
	R->passes[3].pointlight_count = 0;
	R->passes[3].spotlight_count = 4;
	R->passes[3].num_inst_textures = 0;
	strcpy( R->passes[3].shname, "ps_ext_s4" );
	/* PASS5: [DEPTH] FOG */
	R->passes[4].type = SS3D_RPT_SCREEN;
	strcpy( R->passes[4].shname, "ps_scr_fog" );
	/* PASS6: [TRANSPARENT,ANY] DIRAMB + SUN + 0-16 POINT LIGHTS (once) */
	R->passes[5].type = SS3D_RPT_OBJECT;
	R->passes[5].flags = SS3D_RPF_MTL_TRANSPARENT | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_CALC_DIRAMB;
	R->passes[5].maxruns = 1;
	R->passes[5].pointlight_count = 16;
	R->passes[5].spotlight_count = 0;
	R->passes[5].num_inst_textures = 0;
	strcpy( R->passes[5].shname, "ps_base_dsp16" );
	/* PASS7: [TRANSPARENT,ANY] 0-16 POINT LIGHTS (as much as necessary) */
	R->passes[6].type = SS3D_RPT_OBJECT;
	R->passes[6].flags = SS3D_RPF_MTL_TRANSPARENT | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[6].maxruns = -1;
	R->passes[6].pointlight_count = 16;
	R->passes[6].spotlight_count = 0;
	R->passes[6].num_inst_textures = 0;
	strcpy( R->passes[6].shname, "ps_ext_p16" );
	/* PASS8: [TRANSPARENT,ANY] 0-4 SPOT LIGHTS (as much as necessary) */
	R->passes[7].type = SS3D_RPT_OBJECT;
	R->passes[7].flags = SS3D_RPF_MTL_TRANSPARENT | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[7].maxruns = -1;
	R->passes[7].pointlight_count = 0;
	R->passes[7].spotlight_count = 4;
	R->passes[7].num_inst_textures = 0;
	strcpy( R->passes[7].shname, "ps_ext_s4" );
}

void SS3D_Renderer_Destruct( SS3D_Renderer* R )
{
	sgs_SizeVal i;
	R->destroying = 1;
	for( i = 0; i < R->resources.size; ++i )
	{
		sgs_VarObj* obj = (sgs_VarObj*) R->resources.vars[ i ].val.data.P;
		sgs_ObjCallDtor( R->C, obj );
	}
	sgs_vht_free( &R->resources, R->C );
	sgs_vht_free( &R->shaders, R->C );
	sgs_vht_free( &R->textures, R->C );
	sgs_vht_free( &R->materials, R->C );
	if( R->currentScene )
		sgs_ObjRelease( R->C, R->currentScene );
	sgs_ObjRelease( R->C, R->store );
}

void SS3D_Renderer_Update( SS3D_Renderer* R, float dt )
{
}

void SS3D_Renderer_Resize( SS3D_Renderer* R, int w, int h )
{
	R->width = w;
	R->height = h;
}

void SS3D_Renderer_PokeResource( SS3D_Renderer* R, sgs_VarObj* obj, int add )
{
	sgs_Variable K;
	if( R->destroying )
		return;
	
	K.type = SGS_VT_PTR;
	K.data.P = obj;
	if( add )
		sgs_vht_set( &R->resources, R->C, &K, &K );
	else
		sgs_vht_unset( &R->resources, R->C, &K );
}

void SS3D_Renderer_PushScene( SS3D_Renderer* R )
{
	SS3D_Scene* S = (SS3D_Scene*) sgs_PushObjectIPA( R->C, sizeof(*S), SS3D_Scene_iface );
	S->renderer = R;
	S->destroying = 0;
	sgs_vht_init( &S->meshInstances, R->C, 128, 128 );
	sgs_vht_init( &S->lights, R->C, 128, 128 );
	S->camera = NULL;
	S->cullScene = NULL;
	S->viewport = NULL;
	SS3D_Renderer_PokeResource( R, sgs_GetObjectStruct( R->C, -1 ), 1 );
}


static int SS3D_CreateRenderer( SGS_CTX )
{
	char* rendererType;
	sgs_Int version = 0;
	void* device = NULL;
	
	SGSFN( "SS3D_CreateRenderer" );
	if( !sgs_LoadArgs( C, "s|i&", &rendererType, &version, &device ) )
		return 0;
	
	if( !strcmp( rendererType, "D3D9" ) && !device )
		return sgs_Msg( C, SGS_WARNING, "Direct3D requires a device pointer (argument 3)" );
	
	if( !strcmp( rendererType, "D3D9" ) )
		return SS3D_PushRenderer_D3D9( C, device );
	else if( !strcmp( rendererType, "GL" ) )
		return SS3D_PushRenderer_GL( C, version );
	else
		return sgs_Msg( C, SGS_WARNING, "unsupported renderer type" );
}


static sgs_RegFuncConst ss3d_fconsts[] =
{
	FN( MeshGen_Cube ),
	FN( MeshGen_Particles ),
	
	FN( CreateCamera ),
	FN( CreateViewport ),
	FN( CreateRenderer ),
};

static sgs_RegIntConst ss3d_iconsts[] =
{
	CN( LIGHT_POINT ), CN( LIGHT_DIRECT ), CN( LIGHT_SPOT ),
};


SGS_APIFUNC int sgscript_main( SGS_CTX )
{
	sgs_RegFuncConsts( C, ss3d_fconsts, sizeof(ss3d_fconsts) / sizeof(ss3d_fconsts[0]) );
	sgs_RegIntConsts( C, ss3d_iconsts, sizeof(ss3d_iconsts) / sizeof(ss3d_iconsts[0]) );
	if( !sgs_Include( C, "ss3d/engine" ) )
		return SGS_EINPROC;
	return SGS_SUCCESS;
}

