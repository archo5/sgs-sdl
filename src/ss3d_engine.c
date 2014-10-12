

#include "lodepng.h"
#include "dds.h"

#include "ss3d_engine.h"

#define FN( x ) { "SS3D_" #x, SS3D_##x }
#define CN( x ) { "SS3D" #x, SS3D##x }



static size_t divideup( size_t x, int d )
{
	return ( x + d - 1 ) / d;
}

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

int SS3D_Mtx_Invert( MAT4 out, MAT4 M )
{
	float inv[16], *m = M[0], *outInv = out[0], det;
	int i;
	
	inv[0] = m[5]  * m[10] * m[15] -
			 m[5]  * m[11] * m[14] -
			 m[9]  * m[6]  * m[15] +
			 m[9]  * m[7]  * m[14] +
			 m[13] * m[6]  * m[11] -
			 m[13] * m[7]  * m[10];
	
	inv[4] = -m[4]  * m[10] * m[15] +
			  m[4]  * m[11] * m[14] +
			  m[8]  * m[6]  * m[15] -
			  m[8]  * m[7]  * m[14] -
			  m[12] * m[6]  * m[11] +
			  m[12] * m[7]  * m[10];
	
	inv[8] = m[4]  * m[9] * m[15] -
			 m[4]  * m[11] * m[13] -
			 m[8]  * m[5] * m[15] +
			 m[8]  * m[7] * m[13] +
			 m[12] * m[5] * m[11] -
			 m[12] * m[7] * m[9];
	
	inv[12] = -m[4]  * m[9] * m[14] +
			   m[4]  * m[10] * m[13] +
			   m[8]  * m[5] * m[14] -
			   m[8]  * m[6] * m[13] -
			   m[12] * m[5] * m[10] +
			   m[12] * m[6] * m[9];
	
	inv[1] = -m[1]  * m[10] * m[15] +
			  m[1]  * m[11] * m[14] +
			  m[9]  * m[2] * m[15] -
			  m[9]  * m[3] * m[14] -
			  m[13] * m[2] * m[11] +
			  m[13] * m[3] * m[10];
	
	inv[5] = m[0]  * m[10] * m[15] -
			 m[0]  * m[11] * m[14] -
			 m[8]  * m[2] * m[15] +
			 m[8]  * m[3] * m[14] +
			 m[12] * m[2] * m[11] -
			 m[12] * m[3] * m[10];
	
	inv[9] = -m[0]  * m[9] * m[15] +
			  m[0]  * m[11] * m[13] +
			  m[8]  * m[1] * m[15] -
			  m[8]  * m[3] * m[13] -
			  m[12] * m[1] * m[11] +
			  m[12] * m[3] * m[9];
	
	inv[13] = m[0]  * m[9] * m[14] -
			  m[0]  * m[10] * m[13] -
			  m[8]  * m[1] * m[14] +
			  m[8]  * m[2] * m[13] +
			  m[12] * m[1] * m[10] -
			  m[12] * m[2] * m[9];
	
	inv[2] = m[1]  * m[6] * m[15] -
			 m[1]  * m[7] * m[14] -
			 m[5]  * m[2] * m[15] +
			 m[5]  * m[3] * m[14] +
			 m[13] * m[2] * m[7] -
			 m[13] * m[3] * m[6];
	
	inv[6] = -m[0]  * m[6] * m[15] +
			  m[0]  * m[7] * m[14] +
			  m[4]  * m[2] * m[15] -
			  m[4]  * m[3] * m[14] -
			  m[12] * m[2] * m[7] +
			  m[12] * m[3] * m[6];
	
	inv[10] = m[0]  * m[5] * m[15] -
			  m[0]  * m[7] * m[13] -
			  m[4]  * m[1] * m[15] +
			  m[4]  * m[3] * m[13] +
			  m[12] * m[1] * m[7] -
			  m[12] * m[3] * m[5];
	
	inv[14] = -m[0]  * m[5] * m[14] +
			   m[0]  * m[6] * m[13] +
			   m[4]  * m[1] * m[14] -
			   m[4]  * m[2] * m[13] -
			   m[12] * m[1] * m[6] +
			   m[12] * m[2] * m[5];
	
	inv[3] = -m[1] * m[6] * m[11] +
			  m[1] * m[7] * m[10] +
			  m[5] * m[2] * m[11] -
			  m[5] * m[3] * m[10] -
			  m[9] * m[2] * m[7] +
			  m[9] * m[3] * m[6];
	
	inv[7] = m[0] * m[6] * m[11] -
			 m[0] * m[7] * m[10] -
			 m[4] * m[2] * m[11] +
			 m[4] * m[3] * m[10] +
			 m[8] * m[2] * m[7] -
			 m[8] * m[3] * m[6];
	
	inv[11] = -m[0] * m[5] * m[11] +
			   m[0] * m[7] * m[9] +
			   m[4] * m[1] * m[11] -
			   m[4] * m[3] * m[9] -
			   m[8] * m[1] * m[7] +
			   m[8] * m[3] * m[5];
	
	inv[15] = m[0] * m[5] * m[10] -
			  m[0] * m[6] * m[9] -
			  m[4] * m[1] * m[10] +
			  m[4] * m[2] * m[9] +
			  m[8] * m[1] * m[6] -
			  m[8] * m[2] * m[5];
	
	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	
	if( det == 0 )
		return 0;
	
	det = 1.0f / det;
	
	for( i = 0; i < 16; ++i )
		outInv[ i ] = inv[ i ] * det;
	
	return 1;
}

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
	float xscale = -itha / pow( aspect, aamix );
	float yscale = itha * pow( aspect, 1 - aamix );
	
	out[0][0] = xscale;
	out[0][1] = out[0][2] = out[0][3] = 0;
	out[1][1] = yscale;
	out[1][0] = out[1][2] = out[1][3] = 0;
	out[2][2] = zfar / ( zfar - znear );
	out[2][0] = out[2][1] = 0; out[2][3] = 1;
	out[3][2] = -znear * zfar / ( zfar - znear );
	out[3][0] = out[3][1] = out[3][3] = 0;
}

void SS3D_PerspectiveAngles( float angle, float aspect, float aamix, float* outh, float* outv )
{
	float tha = tan( DEG2RAD( angle ) / 2.0f );
	if( tha < 0.001f ) tha = 0.001f;
	float itha = 1.0f / tha;
	float xscale = itha / pow( aspect, aamix );
	float yscale = itha * pow( aspect, 1 - aamix );
	if( outh ) *outh = atan( xscale );
	if( outv ) *outv = atan( yscale );
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
	
	sgs_PushStringAlloc( C, position_count * 4 * sizeof(*vdata) );
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
	sgs_FinalizeStringAlloc( C, -1 );
	
	sgs_PushStringAlloc( C, position_count * 6 * sizeof(*idata) );
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
	sgs_FinalizeStringAlloc( C, -1 );
	
	sgs_PushInt( C, position_count * 4 );
	sgs_PushInt( C, position_count * 6 );
	
	return 4;
}

typedef struct _terrainVtx
{
	VEC3 pos;
	float t1x, t1y;
	float t2x, t2y;
	VEC3 normal;
	VEC4 tg;
}
terrainVtx;

static int SS3D_MeshGen_Terrain( SGS_CTX )
{
	sgs_SizeVal x, y;
	sgs_Int width, height;
	xgm_vtarray* heightlist;
	VEC3 v_minpos;
	VEC3 v_maxpos;
	
	terrainVtx* vdata, *pv;
	uint32_t* idata;
	
	SGSFN( "SS3D_MeshGen_Terrain" );
	if( !sgs_LoadArgs( C, "iixxx", &width, &height, sgs_ArgCheck_FloatArray, &heightlist, sgs_ArgCheck_Vec3, v_minpos, sgs_ArgCheck_Vec3, v_maxpos ) )
		return 0;
	
	if( width < 1 || height < 1 )
		return sgs_Msg( C, SGS_WARNING, "invalid width and/or height" );
	if( width * height > heightlist->size )
		return sgs_Msg( C, SGS_WARNING, "not enough data for specified terrain size" );
	
	sgs_PushStringAlloc( C, width * height * sizeof(*vdata) );
	pv = vdata = (terrainVtx*) sgs_GetStringPtr( C, -1 );
	for( y = 0; y < height; ++y )
	{
		for( x = 0; x < width; ++x )
		{
			float fx = (float) x / (float) ( width - 1 );
			float fy = (float) y / (float) ( height - 1 );
			float fz = heightlist->data[ x + width * y ];
			
			pv->pos[0] = LERP( v_minpos[0], v_maxpos[0], fx );
			pv->pos[1] = LERP( v_minpos[1], v_maxpos[1], fy );
			pv->pos[2] = LERP( v_minpos[2], v_maxpos[2], fz );
			
			pv->t1x = (float) x;
			pv->t1y = (float) y;
			pv->t2x = fx;
			pv->t2y = fy;
			
			pv->tg[3] = 1;
			
			pv++;
		}
	}
	/* normal/tangent generation */
	for( y = 0; y < height; ++y )
	{
		for( x = 0; x < width; ++x )
		{
			VEC3 v01, v11, v21, v10, v12, vdx, vdy, nrm;
			VEC3_Copy( v11, vdata[ x + width * y ].pos );
			if( x > 0 ){ VEC3_Copy( v01, vdata[ x - 1 + width * y ].pos ); } else { VEC3_Copy( v01, v11 ); }
			if( x < width - 1 ){ VEC3_Copy( v21, vdata[ x + 1 + width * y ].pos ); } else { VEC3_Copy( v21, v11 ); }
			if( y > 0 ){ VEC3_Copy( v10, vdata[ x + width * ( y - 1 ) ].pos ); } else { VEC3_Copy( v10, v11 ); }
			if( y < height - 1 ){ VEC3_Copy( v12, vdata[ x + width * ( y + 1 ) ].pos ); } else { VEC3_Copy( v12, v11 ); }
			
			VEC3_Sub( vdx, v21, v01 );
			VEC3_Sub( vdy, v12, v10 );
			VEC3_Normalized( vdata[ x + width * y ].tg, vdx );
			VEC3_Set( nrm, -vdx[2] / vdx[0], -vdy[2] / vdy[1], 1 );
			VEC3_Normalized( vdata[ x + width * y ].normal, nrm );
		}
	}
	sgs_FinalizeStringAlloc( C, -1 );
	
	sgs_PushStringAlloc( C, ( width - 1 ) * ( height - 1 ) * 6 * sizeof(*idata) );
	idata = (uint32_t*) sgs_GetStringPtr( C, -1 );
	for( y = 0; y < height - 1; ++y )
	{
		for( x = 0; x < width - 1; ++x )
		{
			idata[0] = width * y + x;
			idata[1] = width * y + x + 1;
			idata[2] = width * ( y + 1 ) + x + 1;
			idata[3] = idata[2];
			idata[4] = width * ( y + 1 ) + x;
			idata[5] = idata[0];
			idata += 6;
		}
	}
	sgs_FinalizeStringAlloc( C, -1 );
	
	sgs_PushInt( C, width * height );
	sgs_PushInt( C, ( width - 1 ) * ( height - 1 ) * 6 );
	
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

size_t SS3D_TextureInfo_GetTextureSideSize( SS3D_TextureInfo* TI )
{
	size_t width = TI->width, height = TI->height, depth = TI->depth;
	int bpu = 0;
	switch( TI->format )
	{
	/* bytes per pixel */
	case SS3DFORMAT_BGRA8:
	case SS3DFORMAT_BGRX8:
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
	case SS3DFORMAT_BGRX8:
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
	case DDS_FMT_B8G8R8X8: return SS3DFORMAT_BGRX8;
	case DDS_FMT_DXT1: return SS3DFORMAT_DXT1;
	case DDS_FMT_DXT3: return SS3DFORMAT_DXT3;
	case DDS_FMT_DXT5: return SS3DFORMAT_DXT5;
	default: return SS3DFORMAT_UNKNOWN;
	}
}

SGSRESULT SS3D_TextureData_LoadFromFile( SGS_CTX, SS3D_TextureData* TD, sgs_Variable* vFile )
{
	unsigned char* out;
	unsigned w, h;
	int err;
	
	static const dds_u32 dds_supfmt[] = { DDS_FMT_R8G8B8A8, DDS_FMT_B8G8R8A8, DDS_FMT_B8G8R8X8, DDS_FMT_DXT1, DDS_FMT_DXT3, DDS_FMT_DXT5, 0 };
	dds_info ddsinfo;
	
	memset( TD, 0, sizeof(*TD) );
	
	// Try to load DDS
	err = dds_load_from_file( sgs_var_cstr( vFile ), &ddsinfo, dds_supfmt );
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
	err = lodepng_decode32_file( &out, &w, &h, sgs_var_cstr( vFile ) );
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
	
	sgs_PushVariable( C, vFile );
	if( SGS_SUCCEEDED( sgs_GlobalCall( C, "_SS3D_Texture_GetType", 1, 1 ) ) )
	{
		TD->info.usage = (int) sgs_GetInt( C, -1 );
		sgs_Pop( C, 1 );
	}
	
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
	- uint8 texcount
	- smallbuf shader
	- smallbuf textures[texcount]
	
	MESH:
	- magic "SS3DMESH"
	- uint32 flags
	
	- float boundsmin[3]
	- float boundsmax[3]
	
	- buffer vdata
	- buffer idata
	- smallbuf format
	- uint8 numparts
	- part parts[numparts]
	
	minimum size = 12+24+10 = 46
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

const char* SS3D_MeshData_Parse( char* buf, size_t size, SS3D_MeshFileData* out )
{
	uint8_t p, t;
	size_t off = 0;
	if( size < 46 || memcmp( buf, "SS3DMESH", 8 ) != 0 )
		return "file too small or not SS3DMESH";
	memcpy( &out->dataFlags, buf + 8, 4 );
	memcpy( &out->boundsMin, buf + 12, 12 );
	memcpy( &out->boundsMax, buf + 24, 12 );
	off = 36;
	if( !md_parse_buffer( buf + off, size - off, &out->vertexData, &out->vertexDataSize ) )
		return "failed to parse VDATA buffer";
	off += 4 + out->vertexDataSize;
	if( !md_parse_buffer( buf + off, size - off, &out->indexData, &out->indexDataSize ) )
		return "failed to parse IDATA buffer";
	off += 4 + out->indexDataSize;
	if( !md_parse_smallbuf( buf + off, size - off, &out->formatData, &out->formatSize ) )
		return "failed to parse FORMAT buffer";
	off += 1 + out->formatSize;
	if( off >= size )
		return "mesh incomplete (missing part data)";
	out->numParts = (uint8_t) buf[ off++ ];
	if( out->numParts > SS3D_MAX_MESH_PARTS )
		return "invalid part count";
	for( p = 0; p < out->numParts; ++p )
	{
		SS3D_MeshFilePartData* pout = out->parts + p;
		memset( pout, 0, sizeof(*pout) );
		if( off + 19 > size )
			return "mesh incomplete (corrupted part data)";
		memcpy( &pout->vertexOffset, buf + off, 4 ); off += 4;
		memcpy( &pout->vertexCount, buf + off, 4 ); off += 4;
		memcpy( &pout->indexOffset, buf + off, 4 ); off += 4;
		memcpy( &pout->indexCount, buf + off, 4 ); off += 4;
		memcpy( &pout->materialTextureCount, buf + off, 1 ); off += 1;
		for( t = 0; t < pout->materialTextureCount + 1; ++t )
		{
			if( !md_parse_smallbuf( buf + off, size - off, &pout->materialStrings[t], &pout->materialStringSizes[t] ) )
				return "failed to parse material string buffer";
			off += 1 + pout->materialStringSizes[t];
		}
	}
	return NULL;
}

static void _ss3dmesh_extract_vertex( SS3D_MeshFileData* mfd, SS3D_VDeclInfo* info, SS3D_MeshFilePartData* part, int vidx, VEC3 vout )
{
	uint8_t* pudata;
	char* vdata = mfd->vertexData;
	int i;
	VEC3_Set( vout, 0, 0, 0 );
	for( i = 0; i < info->count; ++i )
	{
		if( info->usages[ i ] == SS3D_VDECLUSAGE_POSITION )
			break;
	}
	if( i == info->count )
		return;
	
	vdata += info->offsets[ i ] + info->size * ( part->vertexOffset + vidx );
	switch( info->types[ i ] )
	{
	case SS3D_VDECLTYPE_FLOAT1: /* read 1 float, y;z=0;0 */
		VEC3_Set( vout, ((float*) vdata)[0], 0, 0 );
		break;
	case SS3D_VDECLTYPE_FLOAT2: /* read 2 floats, z=0 */
		VEC3_Set( vout, ((float*) vdata)[0], ((float*) vdata)[1], 0 );
		break;
	case SS3D_VDECLTYPE_FLOAT3:
	case SS3D_VDECLTYPE_FLOAT4: /* read 3 floats */
		VEC3_Copy( vout, ((float*)vdata) );
		break;
	case SS3D_VDECLTYPE_BCOL4: /* read u8[3] */
		pudata = (uint8_t*) vdata;
		VEC3_Set( vout, pudata[0] * (1.0f/255.0f), pudata[1] * (1.0f/255.0f), pudata[2] * (1.0f/255.0f) );
		break;
	default:
		VEC3_Set( vout, 0, 0, 0 );
		break;
	}
}

static int SS3D_MeshData_GetVertexIndexArrays( SGS_CTX )
{
	int p, i;
	char* buf, fdbuf[ 257 ];
	const char* err;
	sgs_SizeVal size;
	SS3D_MeshFileData mfd;
	SS3D_VDeclInfo vdinfo;
	
	SGSFN( "SS3D_MeshData_GetVertexIndexArrays" );
	if( !sgs_LoadArgs( C, "m", &buf, &size ) )
		return 0;
	
	err = SS3D_MeshData_Parse( buf, size, &mfd );
	if( err )
		return sgs_Msg( C, SGS_WARNING, "could not parse mesh data: %s", err );
	if( mfd.formatSize > 256 )
		err = "vertex declaration too long for this function";
	else
	{
		memset( fdbuf, 0, sizeof(fdbuf) );
		memcpy( fdbuf, mfd.formatData, mfd.formatSize );
		err = SS3D_VDeclInfo_Parse( &vdinfo, fdbuf );
	}
	if( err )
		return sgs_Msg( C, SGS_WARNING, "could not parse mesh vertex declaration data: %s", err );
	
	for( p = 0; p < mfd.numParts; ++p )
	{
		sgs_PushString( C, "vertices" );
		SS3D_MeshFilePartData* part = mfd.parts + p;
		for( i = 0; i < part->vertexCount; ++i )
		{
			VEC3 vout;
			_ss3dmesh_extract_vertex( &mfd, &vdinfo, part, i, vout );
			sgs_PushVec3p( C, vout );
		}
		sgs_PushArray( C, part->vertexCount );
		sgs_PushString( C, "indices" );
		if( mfd.dataFlags & SS3D_MDF_TRIANGLESTRIP )
		{
			int nic = ( part->indexCount - 2 ) * 3;
			sgs_PushInt( C, mfd.dataFlags & SS3D_MDF_INDEX_32 ? *(((uint32_t*)mfd.indexData) + part->indexOffset + 0) : *(((uint16_t*)mfd.indexData) + part->indexOffset + 0) );
			sgs_PushInt( C, mfd.dataFlags & SS3D_MDF_INDEX_32 ? *(((uint32_t*)mfd.indexData) + part->indexOffset + 2) : *(((uint16_t*)mfd.indexData) + part->indexOffset + 2) );
			sgs_PushInt( C, mfd.dataFlags & SS3D_MDF_INDEX_32 ? *(((uint32_t*)mfd.indexData) + part->indexOffset + 1) : *(((uint16_t*)mfd.indexData) + part->indexOffset + 1) );
			for( i = 3; i < part->indexCount; ++i )
			{
				if( i % 2 == 0 )
				{
					sgs_PushItem( C, -1 );
					sgs_PushItem( C, -3 );
				}
				else
				{
					sgs_PushItem( C, -2 );
					sgs_PushItem( C, -2 );
				}
				sgs_PushInt( C, mfd.dataFlags & SS3D_MDF_INDEX_32 ? *(((uint32_t*)mfd.indexData) + part->indexOffset + i) : *(((uint16_t*)mfd.indexData) + part->indexOffset + i) );
			}
			sgs_PushArray( C, nic );
		}
		else
		{
			for( i = 0; i < part->indexCount; ++i )
				sgs_PushInt( C, mfd.dataFlags & SS3D_MDF_INDEX_32 ? *(((uint32_t*)mfd.indexData) + part->indexOffset + i) : *(((uint16_t*)mfd.indexData) + part->indexOffset + i) );
			sgs_PushArray( C, part->indexCount );
		}
		sgs_PushDict( C, 4 );
	}
	sgs_PushArray( C, mfd.numParts );
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

int SS3D_GetAABBFromVertexData( SS3D_VDeclInfo* info, const char* vdata, size_t vdsize, VEC3 outMin, VEC3 outMax )
{
	int i;
	const char* vdend;
	float tmp1, tmp2;
	VEC3 tmpv;
	uint8_t* pudata;
	if( vdsize < info->size )
		goto fail;
	
	for( i = 0; i < info->count; ++i )
	{
		if( info->usages[ i ] == SS3D_VDECLUSAGE_POSITION )
			break;
	}
	if( i == info->count )
		goto fail;
	
	vdata += info->offsets[ i ];
	vdend = vdata + vdsize;
	switch( info->types[ i ] )
	{
	case SS3D_VDECLTYPE_FLOAT1: /* read 1 float, y;z=0;0 */
		tmp1 = ((float*) vdata)[0];
		VEC3_Set( outMin, tmp1, 0, 0 );
		VEC3_Set( outMax, tmp1, 0, 0 );
		vdata += info->size;
		while( vdata + info->size <= vdend )
		{
			tmp1 = ((float*) vdata)[0];
			if( outMin[0] > tmp1 ) outMin[0] = tmp1;
			if( outMax[0] < tmp1 ) outMax[0] = tmp1;
			vdata += info->size;
		}
		break;
	case SS3D_VDECLTYPE_FLOAT2: /* read 2 floats, z=0 */
		tmp1 = ((float*) vdata)[0];
		tmp2 = ((float*) vdata)[1];
		VEC3_Set( outMin, tmp1, tmp2, 0 );
		VEC3_Set( outMax, tmp1, tmp2, 0 );
		vdata += info->size;
		while( vdata + info->size <= vdend )
		{
			tmp1 = ((float*) vdata)[0];
			tmp2 = ((float*) vdata)[1];
			if( outMin[0] > tmp1 ) outMin[0] = tmp1;
			if( outMax[0] < tmp1 ) outMax[0] = tmp1;
			if( outMin[1] > tmp2 ) outMin[1] = tmp2;
			if( outMax[1] < tmp2 ) outMax[1] = tmp2;
			vdata += info->size;
		}
		break;
	case SS3D_VDECLTYPE_FLOAT3:
	case SS3D_VDECLTYPE_FLOAT4: /* read 3 floats */
		VEC3_Copy( tmpv, ((float*)vdata) );
		VEC3_Copy( outMin, tmpv );
		VEC3_Copy( outMax, tmpv );
		vdata += info->size;
		while( vdata + info->size <= vdend )
		{
			VEC3_Copy( tmpv, ((float*)vdata) );
			VEC3_Min( outMin, outMin, tmpv );
			VEC3_Max( outMax, outMax, tmpv );
			vdata += info->size;
		}
		break;
	case SS3D_VDECLTYPE_BCOL4: /* read u8[3] */
		pudata = (uint8_t*) vdata;
		VEC3_Set( tmpv, pudata[0] * (1.0f/255.0f), pudata[1] * (1.0f/255.0f), pudata[2] * (1.0f/255.0f) );
		VEC3_Copy( outMin, tmpv );
		VEC3_Copy( outMax, tmpv );
		vdata += info->size;
		while( vdata + info->size <= vdend )
		{
			VEC3_Set( tmpv, pudata[0] * (1.0f/255.0f), pudata[1] * (1.0f/255.0f), pudata[2] * (1.0f/255.0f) );
			VEC3_Min( outMin, outMin, tmpv );
			VEC3_Max( outMax, outMax, tmpv );
			vdata += info->size;
		}
		break;
	}
	
	return 1;
	
fail:
	VEC3_Set( outMin, 0, 0, 0 );
	VEC3_Set( outMax, 0, 0, 0 );
	return 0;
}


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
}


//
// MESH INSTANCE

#define MI_HDR SS3D_MeshInstance* MI = (SS3D_MeshInstance*) obj->data
#define MI_IHDR( funcname ) SS3D_MeshInstance* MI; \
	if( !SGS_PARSE_METHOD( C, SS3D_MeshInstance_iface, MI, SS3D_MeshInstance, funcname ) ) return 0;

static int meshinsti_setConstF( SGS_CTX )
{
	int32_t pos;
	float val;
	
	MI_IHDR( setConstF );
	if( !sgs_LoadArgs( C, "lf", &pos, &val ) )
		return 0;
	if( pos < 0 || pos >= SS3D_MAX_MI_CONSTANTS )
		return sgs_Msg( C, SGS_WARNING, "invalid target position: %d (must be between 0 and %d)", pos, SS3D_MAX_MI_CONSTANTS - 1 );
	
	VEC4_Set( MI->constants[ pos ], val, val, val, val );
	return 0;
}

static int meshinsti_setConstV2( SGS_CTX )
{
	int32_t pos;
	float val[2];
	
	MI_IHDR( setConstV2 );
	if( !sgs_LoadArgs( C, "lx", &pos, sgs_ArgCheck_Vec2, val ) )
		return 0;
	if( pos < 0 || pos >= SS3D_MAX_MI_CONSTANTS )
		return sgs_Msg( C, SGS_WARNING, "invalid target position: %d (must be between 0 and %d)", pos, SS3D_MAX_MI_CONSTANTS - 1 );
	
	VEC4_Set( MI->constants[ pos ], val[0], val[1], 0, 0 );
	return 0;
}

static int meshinsti_setConstV3( SGS_CTX )
{
	int32_t pos;
	float val[3];
	
	MI_IHDR( setConstV3 );
	if( !sgs_LoadArgs( C, "lx", &pos, sgs_ArgCheck_Vec3, val ) )
		return 0;
	if( pos < 0 || pos >= SS3D_MAX_MI_CONSTANTS )
		return sgs_Msg( C, SGS_WARNING, "invalid target position: %d (must be between 0 and %d)", pos, SS3D_MAX_MI_CONSTANTS - 1 );
	
	VEC4_Set( MI->constants[ pos ], val[0], val[1], val[2], 0 );
	return 0;
}

static int meshinsti_setConstV4( SGS_CTX )
{
	int32_t pos;
	float val[4];
	
	MI_IHDR( setConstV4 );
	if( !sgs_LoadArgs( C, "lx", &pos, sgs_ArgCheck_Vec4, val ) )
		return 0;
	if( pos < 0 || pos >= SS3D_MAX_MI_CONSTANTS )
		return sgs_Msg( C, SGS_WARNING, "invalid target position: %d (must be between 0 and %d)", pos, SS3D_MAX_MI_CONSTANTS - 1 );
	
	VEC4_Set( MI->constants[ pos ], val[0], val[1], val[2], val[3] );
	return 0;
}

static int meshinsti_setConstM4( SGS_CTX )
{
	int32_t pos;
	MAT4 val;
	
	MI_IHDR( setConstM4 );
	if( !sgs_LoadArgs( C, "lx", &pos, sgs_ArgCheck_Mat4, val ) )
		return 0;
	if( pos < 0 || pos >= SS3D_MAX_MI_CONSTANTS - 3 )
		return sgs_Msg( C, SGS_WARNING, "invalid target position: %d (must be between 0 and %d)", pos, SS3D_MAX_MI_CONSTANTS - 4 );
	
	memcpy( MI->constants[ pos ], val, sizeof(val) );
	return 0;
}

static int meshinsti_setTexture( SGS_CTX )
{
	int32_t pos;
	
	MI_IHDR( setTexture );
	if( !sgs_LoadArgs( C, "l?x", &pos, MI->scene->renderer->ifTexture ) )
		return 0;
	if( pos < 0 || pos >= SS3D_MAX_MI_TEXTURES )
		return sgs_Msg( C, SGS_WARNING, "invalid texture slot: %d (must be between 0 and %d)", pos, SS3D_MAX_MI_TEXTURES - 1 );
	
	sgs_ObjAssign( C, &MI->textures[ pos ], sgs_GetObjectStruct( C, 1 ) );
	return 0;
}

static int meshinst_destruct( SGS_CTX, sgs_VarObj* obj )
{
	MI_HDR;
	if( MI->scene )
	{
		int i;
		scene_poke_resource( MI->scene, &MI->scene->meshInstances, obj, 0 );
		MI->scene = NULL;
		sgs_ObjAssign( C, &MI->mesh, NULL );
		for( i = 0; i < SS3D_MAX_MI_TEXTURES; ++i )
			sgs_ObjAssign( C, &MI->textures[ i ], NULL );
	}
	return SGS_SUCCESS;
}

static int meshinst_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	int i;
	MI_HDR;
	if( MI->mesh ) sgs_ObjGCMark( C, MI->mesh );
	for( i = 0; i < SS3D_MAX_MI_TEXTURES; ++i )
		sgs_ObjGCMark( C, MI->textures[ i ] );
	return SGS_SUCCESS;
}

static int meshinst_getindex( SGS_ARGS_GETINDEXFUNC )
{
	MI_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mesh" )    SGS_RETURN_OBJECT( MI->mesh );
		SGS_CASE( "matrix" )  SGS_RETURN_MAT4( *MI->matrix );
		SGS_CASE( "color" )   SGS_RETURN_COLORP( MI->color );
		SGS_CASE( "enabled" ) SGS_RETURN_BOOL( MI->enabled );
		
		SGS_CASE( "setConstF" ) SGS_RETURN_CFUNC( meshinsti_setConstF );
		SGS_CASE( "setConstV2" ) SGS_RETURN_CFUNC( meshinsti_setConstV2 );
		SGS_CASE( "setConstV3" ) SGS_RETURN_CFUNC( meshinsti_setConstV3 );
		SGS_CASE( "setConstV4" ) SGS_RETURN_CFUNC( meshinsti_setConstV4 );
		SGS_CASE( "setConstM4" ) SGS_RETURN_CFUNC( meshinsti_setConstM4 );
		SGS_CASE( "setTexture" ) SGS_RETURN_CFUNC( meshinsti_setTexture );
		
		SGS_CASE( "texture0" ) SGS_RETURN_OBJECT( MI->textures[0] );
		SGS_CASE( "texture1" ) SGS_RETURN_OBJECT( MI->textures[1] );
		SGS_CASE( "texture2" ) SGS_RETURN_OBJECT( MI->textures[2] );
		SGS_CASE( "texture3" ) SGS_RETURN_OBJECT( MI->textures[3] );
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
		
		SGS_CASE( "texture0" ) { if( !MI->scene || !MI->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( MI->scene->renderer->ifTexture, MI->textures[0], 0 ) }
		SGS_CASE( "texture1" ) { if( !MI->scene || !MI->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( MI->scene->renderer->ifTexture, MI->textures[1], 0 ) }
		SGS_CASE( "texture2" ) { if( !MI->scene || !MI->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( MI->scene->renderer->ifTexture, MI->textures[2], 0 ) }
		SGS_CASE( "texture3" ) { if( !MI->scene || !MI->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( MI->scene->renderer->ifTexture, MI->textures[3], 0 ) }
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
#define L_IHDR( funcname ) SS3D_Light* L; \
	if( !SGS_PARSE_METHOD( C, SS3D_Light_iface, L, SS3D_Light, funcname ) ) return 0;

static int lighti_genSpotLightMatrices( SGS_CTX )
{
	L_IHDR( genSpotLightMatrices );
	
	SS3D_Mtx_LookAt( L->viewMatrix, L->position, L->direction, L->updir );
	SS3D_Mtx_Perspective( L->projMatrix, L->angle, L->aspect, 0.5, L->range * 0.001f, L->range );
	SS3D_Mtx_Multiply( L->viewProjMatrix, L->viewMatrix, L->projMatrix );
	
	return 0;
}

static int light_getindex( SGS_ARGS_GETINDEXFUNC )
{
	L_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" )          SGS_RETURN_INT( L->type );
		SGS_CASE( "isEnabled" )     SGS_RETURN_BOOL( L->isEnabled );
		SGS_CASE( "position" )      SGS_RETURN_VEC3P( L->position );
		SGS_CASE( "direction" )     SGS_RETURN_VEC3P( L->direction );
		SGS_CASE( "updir" )         SGS_RETURN_VEC3P( L->updir );
		SGS_CASE( "color" )         SGS_RETURN_VEC3P( L->color );
		SGS_CASE( "range" )         SGS_RETURN_REAL( L->range );
		SGS_CASE( "power" )         SGS_RETURN_REAL( L->power );
		SGS_CASE( "angle" )         SGS_RETURN_REAL( L->angle );
		SGS_CASE( "aspect" )        SGS_RETURN_REAL( L->aspect );
		SGS_CASE( "cookieTexture" ) SGS_RETURN_OBJECT( L->cookieTexture );
		SGS_CASE( "shadowTexture" ) SGS_RETURN_OBJECT( L->shadowTexture );
		SGS_CASE( "projMatrix" )    SGS_RETURN_MAT4( *L->projMatrix );
		SGS_CASE( "hasShadows" )    SGS_RETURN_BOOL( L->hasShadows );
		
		SGS_CASE( "genSpotLightMatrices" ) SGS_RETURN_CFUNC( lighti_genSpotLightMatrices );
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
		SGS_CASE( "updir" )         SGS_PARSE_VEC3( L->updir, 0 )
		SGS_CASE( "color" )         SGS_PARSE_VEC3( L->color, 0 )
		SGS_CASE( "range" )         SGS_PARSE_REAL( L->range )
		SGS_CASE( "power" )         SGS_PARSE_REAL( L->power )
		SGS_CASE( "angle" )         SGS_PARSE_REAL( L->angle )
		SGS_CASE( "aspect" )        SGS_PARSE_REAL( L->aspect )
		SGS_CASE( "cookieTexture" )
		{
			if( !L->scene || !L->scene->renderer ) return SGS_EINPROC;
			if( val->type == SGS_VT_NULL )
				sgs_ObjAssign( C, &L->cookieTexture, NULL );
			else if( sgs_IsObjectP( val, L->scene->renderer->ifTexture ) || sgs_IsObjectP( val, L->scene->renderer->ifRT ) )
				sgs_ObjAssign( C, &L->cookieTexture, sgs_GetObjectStructP( val ) );
			else
				return SGS_EINVAL;
			return SGS_SUCCESS;
		}
		SGS_CASE( "shadowTexture" ) { if( !L->scene || !L->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( L->scene->renderer->ifRT, L->shadowTexture, 0 ) }
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
		"\nupdir=(%g;%g;%g)"
		"\ncolor=(%g;%g;%g)"
		"\nrange=%g"
		"\npower=%g"
		"\nangle=%g"
		"\naspect=%g"
		"\ncookieTexture=%p"
		"\nshadowTexture=%p"
		"\nprojMatrix=..."
		"\nhasShadows=%s",
		L->type,
		L->isEnabled ? "true" : "false",
		L->position[0], L->position[1], L->position[2],
		L->direction[0], L->direction[1], L->direction[2],
		L->updir[0], L->updir[1], L->updir[2],
		L->color[0], L->color[1], L->color[2],
		L->range,
		L->power,
		L->angle,
		L->aspect,
		L->cookieTexture,
		L->shadowTexture,
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
	if( L->cookieTexture ) sgs_ObjGCMark( C, L->cookieTexture );
	if( L->shadowTexture ) sgs_ObjGCMark( C, L->shadowTexture );
	return SGS_SUCCESS;
}

static int light_destruct( SGS_CTX, sgs_VarObj* obj )
{
	L_HDR;
	if( L->scene )
	{
		scene_poke_resource( L->scene, &L->scene->lights, obj, 0 );
		L->scene = NULL;
	}
	if( L->cookieTexture )
	{
		sgs_ObjRelease( C, L->cookieTexture );
		L->cookieTexture = NULL;
	}
	if( L->shadowTexture )
	{
		sgs_ObjRelease( C, L->shadowTexture );
		L->shadowTexture = NULL;
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
// DEFAULT CULLING FUNCTIONS

#define FRUSTUM_PLANE_NEAR   0
#define FRUSTUM_PLANE_FAR    1
#define FRUSTUM_PLANE_LEFT   2
#define FRUSTUM_PLANE_RIGHT  3
#define FRUSTUM_PLANE_TOP    4
#define FRUSTUM_PLANE_BOTTOM 5

static void SS3D_MakePlaneFromPoints( PLANE plane, VEC3 p0, VEC3 p1, VEC3 p2 )
{
	VEC3 p0p1, p0p2;
	VEC3_Sub( p0p1, p1, p0 );
	VEC3_Sub( p0p2, p2, p0 );
	VEC3_Cross( plane, p0p1, p0p2 );
	VEC3_Normalized( plane, plane );
	plane[3] = VEC3_Dot( plane, p0 );
}

static void SS3D_MakePlanesFromBoxPoints( PLANE planes[6], VEC3 points[8] )
{
	SS3D_MakePlaneFromPoints( planes[ FRUSTUM_PLANE_NEAR   ], points[0], points[1], points[2] );
	SS3D_MakePlaneFromPoints( planes[ FRUSTUM_PLANE_FAR    ], points[7], points[6], points[5] );
	SS3D_MakePlaneFromPoints( planes[ FRUSTUM_PLANE_LEFT   ], points[0], points[3], points[4] );
	SS3D_MakePlaneFromPoints( planes[ FRUSTUM_PLANE_RIGHT  ], points[1], points[5], points[2] );
	SS3D_MakePlaneFromPoints( planes[ FRUSTUM_PLANE_TOP    ], points[2], points[6], points[3] );
	SS3D_MakePlaneFromPoints( planes[ FRUSTUM_PLANE_BOTTOM ], points[0], points[4], points[1] );
}

static void SS3D_GetFrustumPlanes( PLANE frustum[6], MAT4 mIVP )
{
	static VEC3 psp[8] =
	{
		{  1,  1, 0 },
		{ -1,  1, 0 },
		{ -1, -1, 0 },
		{  1, -1, 0 },
		{  1,  1, 1 },
		{ -1,  1, 1 },
		{ -1, -1, 1 },
		{  1, -1, 1 },
	};
	
	int i;
	VEC3 wsp[8];
	for( i = 0; i < 8; ++i )
		SS3D_Mtx_TransformPos( wsp[i], psp[i], mIVP );
	
	SS3D_MakePlanesFromBoxPoints( frustum, wsp );
}

static void SS3D_GetFrustumAABB( VEC3 aabb[2], MAT4 mIVP )
{
	static VEC3 psp[8] =
	{
		{  1,  1, 0 },
		{ -1,  1, 0 },
		{ -1, -1, 0 },
		{  1, -1, 0 },
		{  1,  1, 1 },
		{ -1,  1, 1 },
		{ -1, -1, 1 },
		{  1, -1, 1 },
	};
	
	int i;
	VEC3 tmp;
	SS3D_Mtx_TransformPos( tmp, psp[0], mIVP );
	VEC3_Copy( aabb[0], tmp );
	VEC3_Copy( aabb[1], tmp );
	for( i = 1; i < 8; ++i )
	{
		SS3D_Mtx_TransformPos( tmp, psp[i], mIVP );
		VEC3_Min( aabb[0], aabb[0], tmp );
		VEC3_Max( aabb[1], aabb[1], tmp );
	}
}

static void SS3D_GetTfAABB( VEC3 aabb[2], MAT4 mtx, VEC3 min, VEC3 max )
{
	VEC3 wsp[8] =
	{
		{ min[0], min[1], min[2] },
		{ max[0], min[1], min[2] },
		{ max[0], max[1], min[2] },
		{ min[0], max[1], min[2] },
		{ min[0], min[1], max[2] },
		{ max[0], min[1], max[2] },
		{ max[0], max[1], max[2] },
		{ min[0], max[1], max[2] },
	};
	
	int i;
	SS3D_Mtx_TransformPos( aabb[0], wsp[0], mtx );
	VEC3_Copy( aabb[1], aabb[0] );
	for( i = 1; i < 8; ++i )
	{
		VEC3 tmp;
		SS3D_Mtx_TransformPos( tmp, wsp[i], mtx );
		VEC3_Min( aabb[0], aabb[0], tmp );
		VEC3_Max( aabb[1], aabb[1], tmp );
	}
}

static int SS3D_FrustumAABBIntersection( PLANE planes[6], VEC3 min, VEC3 max )
{
	int i;
	for( i = 0; i < 6; ++i )
	{
		VEC3 vcmp =
		{
			planes[i][0] > 0 ? min[0] : max[0],
			planes[i][1] > 0 ? min[1] : max[1],
			planes[i][2] > 0 ? min[2] : max[2],
		};
		if( VEC3_Dot( vcmp, planes[i] ) > planes[i][3] )
			return 0;
	}
	return 1;
}

static int SS3D_FrustumSphereIntersection( PLANE planes[6], VEC3 pos, float radius )
{
	int i;
	for( i = 0; i < 6; ++i )
	{
		if( VEC3_Dot( pos, planes[i] ) - radius > planes[i][3] )
			return 0;
	}
	return 1;
}


static int SS3D_ISCF_Camera_MeshList( void* data, uint32_t count, SS3D_CullSceneCamera* camera, SS3D_CullSceneMesh* meshes, uint32_t* outbitfield )
{
	uint32_t i, o = 0;
	PLANE frustum[6];
	VEC3* meshaabbs = malloc( 2 * sizeof(VEC3) * count );
	
	SS3D_GetFrustumPlanes( frustum, camera->invViewProjMatrix );
	for( i = 0; i < count; ++i )
		SS3D_GetTfAABB( meshaabbs + i * 2, meshes[ i ].transform, meshes[ i ].min, meshes[ i ].max );
	
	for( i = 0; i < count; )
	{
		int sub = 32;
		uint32_t bfout = 0;
		while( i < count && sub --> 0 )
		{
			uint32_t mask = 1 << ( i % 32 );
			if( SS3D_FrustumAABBIntersection( frustum, meshaabbs[ i * 2 ], meshaabbs[ i * 2 + 1 ] ) )
				bfout |= mask;
			i++;
		}
		outbitfield[ o++ ] = bfout;
	}
	
	free( meshaabbs );
	return 1;
}

static int SS3D_ISCF_Camera_PointLightList( void* data, uint32_t count, SS3D_CullSceneCamera* camera, SS3D_CullScenePointLight* lights, uint32_t* outbitfield )
{
	uint32_t i, o = 0;
	PLANE frustum[6];
	
	SS3D_GetFrustumPlanes( frustum, camera->invViewProjMatrix );
	
	for( i = 0; i < count; )
	{
		int sub = 32;
		uint32_t bfout = 0;
		while( i < count && sub --> 0 )
		{
			uint32_t mask = 1 << ( i % 32 );
			if( SS3D_FrustumSphereIntersection( frustum, lights[ i ].position, lights[ i ].radius ) )
				bfout |= mask;
			i++;
		}
		outbitfield[ o++ ] = bfout;
	}
	
	return 1;
}

static int SS3D_ISCF_Camera_SpotLightList( void* data, uint32_t count, SS3D_CullSceneCamera* camera, SS3D_CullSceneFrustum* frusta, MAT4* inv_matrices, uint32_t* outbitfield )
{
	uint32_t i, o = 0;
	PLANE frustum[6];
	VEC3* lightaabbs = malloc( 2 * sizeof(VEC3) * count );
	
	SS3D_GetFrustumPlanes( frustum, camera->invViewProjMatrix );
	for( i = 0; i < count; ++i )
		SS3D_GetFrustumAABB( lightaabbs + i * 2, inv_matrices[ i ] );
	
	for( i = 0; i < count; )
	{
		int sub = 32;
		uint32_t bfout = 0;
		while( i < count && sub --> 0 )
		{
			uint32_t mask = 1 << ( i % 32 );
			if( SS3D_FrustumAABBIntersection( frustum, lightaabbs[ i * 2 ], lightaabbs[ i * 2 + 1 ] ) )
				bfout |= mask;
			i++;
		}
		outbitfield[ o++ ] = bfout;
	}
	
	free( lightaabbs );
	return 1;
}


//
// CULL SCENE

#define CS_HDR SS3D_CullScene* CS = (SS3D_CullScene*) obj->data;

static int cullscene_destruct( SGS_CTX, sgs_VarObj* obj )
{
	CS_HDR;
	sgs_Release( C, &CS->store );
	return SGS_SUCCESS;
}

static int cullscene_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	CS_HDR;
	sgs_GCMark( C, &CS->store );
	return SGS_SUCCESS;
}

static int cullscene_getindex( SGS_ARGS_GETINDEXFUNC )
{
	CS_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "camera_meshlist" ) SGS_RETURN_PTR( CS->camera_meshlist );
		SGS_CASE( "camera_pointlightlist" ) SGS_RETURN_PTR( CS->camera_pointlightlist );
		SGS_CASE( "camera_spotlightlist" ) SGS_RETURN_PTR( CS->camera_spotlightlist );
		SGS_CASE( "mesh_pointlightlist" ) SGS_RETURN_PTR( CS->mesh_pointlightlist );
		SGS_CASE( "mesh_spotlightlist" ) SGS_RETURN_PTR( CS->mesh_spotlightlist );
		SGS_CASE( "data" ) SGS_RETURN_PTR( CS->data );
		SGS_CASE( "store" ) { sgs_PushVariable( C, &CS->store ); return SGS_SUCCESS; }
		
		SGS_CASE( "enable_camera_meshlist" ) SGS_RETURN_BOOL( CS->flags & SS3D_CF_ENABLE_CAM_MESH );
		SGS_CASE( "enable_camera_pointlightlist" ) SGS_RETURN_BOOL( CS->flags & SS3D_CF_ENABLE_CAM_PLT );
		SGS_CASE( "enable_camera_spotlightlist" ) SGS_RETURN_BOOL( CS->flags & SS3D_CF_ENABLE_CAM_SLT );
		SGS_CASE( "enable_mesh_pointlightlist" ) SGS_RETURN_BOOL( CS->flags & SS3D_CF_ENABLE_MESH_PLT );
		SGS_CASE( "enable_mesh_spotlightlist" ) SGS_RETURN_BOOL( CS->flags & SS3D_CF_ENABLE_MESH_SLT );
	SGS_END_INDEXFUNC;
}

static int cullscene_setindex( SGS_ARGS_SETINDEXFUNC )
{
	CS_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "camera_meshlist" ) SGS_PARSE_PTR( CS->camera_meshlist )
		SGS_CASE( "camera_pointlightlist" ) SGS_PARSE_PTR( CS->camera_pointlightlist )
		SGS_CASE( "camera_spotlightlist" ) SGS_PARSE_PTR( CS->camera_spotlightlist )
		SGS_CASE( "mesh_pointlightlist" ) SGS_PARSE_PTR( CS->mesh_pointlightlist )
		SGS_CASE( "mesh_spotlightlist" ) SGS_PARSE_PTR( CS->mesh_spotlightlist )
		SGS_CASE( "data" ) SGS_PARSE_PTR( CS->data )
		SGS_CASE( "store" ) { sgs_Assign( C, &CS->store, val ); return SGS_SUCCESS; }
		
		SGS_CASE( "enable_camera_meshlist" ) { sgs_Bool v; if( sgs_ParseBoolP( C, val, &v ) ){ CS->flags = ( CS->flags & ~SS3D_CF_ENABLE_CAM_MESH ) | ( v * SS3D_CF_ENABLE_CAM_MESH ); return SGS_SUCCESS; } return SGS_EINVAL; }
		SGS_CASE( "enable_camera_pointlightlist" ) { sgs_Bool v; if( sgs_ParseBoolP( C, val, &v ) ){ CS->flags = ( CS->flags & ~SS3D_CF_ENABLE_CAM_PLT ) | ( v * SS3D_CF_ENABLE_CAM_PLT ); return SGS_SUCCESS; } return SGS_EINVAL; }
		SGS_CASE( "enable_camera_spotlightlist" ) { sgs_Bool v; if( sgs_ParseBoolP( C, val, &v ) ){ CS->flags = ( CS->flags & ~SS3D_CF_ENABLE_CAM_SLT ) | ( v * SS3D_CF_ENABLE_CAM_SLT ); return SGS_SUCCESS; } return SGS_EINVAL; }
		SGS_CASE( "enable_mesh_pointlightlist" ) { sgs_Bool v; if( sgs_ParseBoolP( C, val, &v ) ){ CS->flags = ( CS->flags & ~SS3D_CF_ENABLE_MESH_PLT ) | ( v * SS3D_CF_ENABLE_MESH_PLT ); return SGS_SUCCESS; } return SGS_EINVAL; }
		SGS_CASE( "enable_mesh_spotlightlist" ) { sgs_Bool v; if( sgs_ParseBoolP( C, val, &v ) ){ CS->flags = ( CS->flags & ~SS3D_CF_ENABLE_MESH_SLT ) | ( v * SS3D_CF_ENABLE_MESH_SLT ); return SGS_SUCCESS; } return SGS_EINVAL; }
	SGS_END_INDEXFUNC;
}

sgs_ObjInterface SS3D_CullScene_iface[1] =
{{
	"SS3D_CullScene",
	cullscene_destruct, cullscene_gcmark,
	cullscene_getindex, cullscene_setindex,
	NULL, NULL, NULL, NULL,
	NULL, NULL,
}};

static SS3D_CullScene* push_cullscene( SGS_CTX )
{
	SS3D_CullScene* cs = (SS3D_CullScene*) sgs_PushObjectIPA( C, sizeof(*cs), SS3D_CullScene_iface );
	memset( cs, 0, sizeof(*cs) );
	cs->flags = SS3D_CF_ENABLE_ALL;
	return cs;
}

static void push_default_cullscene( SGS_CTX )
{
	SS3D_CullScene* CS = push_cullscene( C );
	CS->camera_meshlist = SS3D_ISCF_Camera_MeshList;
	CS->camera_pointlightlist = SS3D_ISCF_Camera_PointLightList;
	CS->camera_spotlightlist = SS3D_ISCF_Camera_SpotLightList;
}

static int SS3D_CreateCullScene( SGS_CTX )
{
	SGSFN( "SS3D_CreateCullScene" );
	push_cullscene( C );
	return 1;
}


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

static int camerai_genViewMatrix( SGS_CTX )
{
	CAM_IHDR( genViewMatrix );
	camera_recalc_viewmtx( CAM );
	return 0;
}

static int camerai_genProjMatrix( SGS_CTX )
{
	CAM_IHDR( genProjMatrix );
	camera_recalc_projmtx( CAM );
	return 0;
}

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

static int camerai_getCursorRay( SGS_CTX )
{
	float x, y;
	VEC3 pos, tgt, dir;
	MAT4 viewProjMatrix, inv;
	
	CAM_IHDR( getCursorRay );
	if( !sgs_LoadArgs( C, "ff", &x, &y ) )
		return 0;
	
	VEC3_Set( pos, x * 2 - 1, y * -2 + 1, 0 );
	VEC3_Set( tgt, x * 2 - 1, y * -2 + 1, 1 );
	
	SS3D_Mtx_Multiply( viewProjMatrix, CAM->mView, CAM->mProj );
	if( !SS3D_Mtx_Invert( inv, viewProjMatrix ) )
		return sgs_Msg( C, SGS_WARNING, "failed to invert view*projection matrix" );
	
	SS3D_Mtx_TransformPos( pos, pos, inv );
	SS3D_Mtx_TransformPos( tgt, tgt, inv );
	VEC3_Sub( dir, tgt, pos );
	VEC3_Normalized( dir, dir );
	
	sgs_PushVec3p( C, pos );
	sgs_PushVec3p( C, dir );
	return 2;
}

static int camera_getindex( SGS_ARGS_GETINDEXFUNC )
{
	CAM_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" )  SGS_RETURN_VEC3P( CAM->position );
		SGS_CASE( "direction" ) SGS_RETURN_VEC3P( CAM->direction );
		SGS_CASE( "up" )        SGS_RETURN_VEC3P( CAM->up );
		SGS_CASE( "angle" )     SGS_RETURN_REAL( CAM->angle );
		SGS_CASE( "aspect" )    SGS_RETURN_REAL( CAM->aspect );
		SGS_CASE( "aamix" )     SGS_RETURN_REAL( CAM->aamix );
		SGS_CASE( "znear" )     SGS_RETURN_REAL( CAM->znear );
		SGS_CASE( "zfar" )      SGS_RETURN_REAL( CAM->zfar );
		
		SGS_CASE( "viewMatrix" ) SGS_RETURN_MAT4( *CAM->mView );
		SGS_CASE( "invViewMatrix" ) SGS_RETURN_MAT4( *CAM->mInvView );
		SGS_CASE( "projMatrix" ) SGS_RETURN_MAT4( *CAM->mProj );
		
		SGS_CASE( "genViewMatrix" ) SGS_RETURN_CFUNC( camerai_genViewMatrix );
		SGS_CASE( "genProjMatrix" ) SGS_RETURN_CFUNC( camerai_genProjMatrix );
		SGS_CASE( "worldToScreen" ) SGS_RETURN_CFUNC( camerai_worldToScreen );
		SGS_CASE( "getCursorRay" ) SGS_RETURN_CFUNC( camerai_getCursorRay );
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

static int SS3D_CreateCamera( SGS_CTX )
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

static int SS3D_CreateViewport( SGS_CTX )
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
	int i;
	SS3D_MeshInstance* MI;
	SC_IHDR( createMeshInstance );
	MI = (SS3D_MeshInstance*) sgs_PushObjectIPA( C, sizeof(*MI), SS3D_MeshInstance_iface );
	
	MI->scene = S;
	MI->mesh = NULL;
	SS3D_Mtx_Identity( MI->matrix );
	VEC4_Set( MI->color, 1, 1, 1, 1 );
	MI->enabled = 1;
	for( i = 0; i < SS3D_MAX_MI_CONSTANTS; ++i )
	{
		VEC4_Set( MI->constants[ i ], 0, 0, 0, 0 );
	}
	for( i = 0; i < SS3D_MAX_MI_TEXTURES; ++i )
		MI->textures[ i ] = NULL;
	
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
	VEC3_Set( L->updir, 0, 0, 1 );
	L->angle = 60;
	L->aspect = 1;
	
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


/************ SCENE CULLING *************/
static void get_frustum_from_camera( SS3D_Camera* CAM, SS3D_CullSceneCamera* out )
{
	VEC3_Copy( out->frustum.position, CAM->position );
	VEC3_Copy( out->frustum.direction, CAM->direction );
	VEC3_Copy( out->frustum.up, CAM->up );
	SS3D_PerspectiveAngles( CAM->angle, CAM->aspect, CAM->aamix, &out->frustum.hangle, &out->frustum.vangle );
	out->frustum.znear = CAM->znear;
	out->frustum.zfar = CAM->zfar;
	SS3D_Mtx_Multiply( out->viewProjMatrix, CAM->mView, CAM->mProj );
	SS3D_Mtx_Identity( out->invViewProjMatrix );
	SS3D_Mtx_Invert( out->invViewProjMatrix, out->viewProjMatrix );
}

static void get_frustum_from_light( SS3D_Light* L, SS3D_CullSceneCamera* out )
{
	VEC3_Copy( out->frustum.position, L->position );
	VEC3_Copy( out->frustum.direction, L->direction );
	VEC3_Copy( out->frustum.up, L->updir );
	SS3D_PerspectiveAngles( L->angle, L->aspect, 0.5, &out->frustum.hangle, &out->frustum.vangle );
	out->frustum.znear = L->range * 0.001f;
	out->frustum.zfar = L->range;
	memcpy( out->viewProjMatrix, L->viewProjMatrix, sizeof( L->viewProjMatrix ) );
	SS3D_Mtx_Identity( out->invViewProjMatrix );
	SS3D_Mtx_Invert( out->invViewProjMatrix, out->viewProjMatrix );
}

uint32_t SS3D_Scene_Cull_Camera_MeshList( SGS_CTX, sgs_MemBuf* MB, SS3D_Scene* S )
{
	SS3D_Camera* CAM = (SS3D_Camera*) S->camera->data;
	if( !CAM )
		return 0;
	
	uint32_t i, data_size = 0;
	size_t mbsize = MB->size;
	
	SS3D_CullSceneCamera camera_frustum;
	get_frustum_from_camera( CAM, &camera_frustum );
	
	sgs_membuf_resize( MB, C, mbsize + sizeof(SS3D_MeshInstance*) * S->meshInstances.size );
	SS3D_MeshInstance** mesh_instances = (SS3D_MeshInstance**) ( MB->ptr + mbsize );
	SS3D_CullSceneMesh* mesh_bounds = sgs_Alloc_n( SS3D_CullSceneMesh, S->meshInstances.size );
	uint32_t* mesh_visiblity = sgs_Alloc_n( uint32_t, divideup( S->meshInstances.size, 32 ) );
	
	/* fill in instance data */
	sgs_SizeVal inst_id;
	for( inst_id = 0; inst_id < S->meshInstances.size; ++inst_id )
	{
		SS3D_MeshInstance* MI = (SS3D_MeshInstance*) S->meshInstances.vars[ inst_id ].val.data.O->data;
		if( !MI->mesh || !MI->enabled )
			continue;
		SS3D_Mesh* M = (SS3D_Mesh*) MI->mesh->data;
		
		mesh_instances[ data_size ] = MI;
		memcpy( mesh_bounds[ data_size ].transform, MI->matrix, sizeof( MAT4 ) );
		memcpy( mesh_bounds[ data_size ].min, M->boundsMin, sizeof( VEC3 ) );
		memcpy( mesh_bounds[ data_size ].max, M->boundsMax, sizeof( VEC3 ) );
		data_size++;
	}
	
	/* iterate all cullscenes */
	sgs_Variable arr, it, val;
	sgs_InitObjectPtr( &arr, S->cullScenes );
	sgs_GetIteratorP( C, &arr, &it );
	while( sgs_IterAdvanceP( C, &it ) > 0 )
	{
		sgs_IterGetDataP( C, &it, NULL, &val );
		if( sgs_IsObjectP( &val, SS3D_CullScene_iface ) )
		{
			SS3D_CullScene* CS = (SS3D_CullScene*) sgs_GetObjectDataP( &val );
			
			if( CS->camera_meshlist && ( CS->flags & SS3D_CF_ENABLE_CAM_MESH ) != 0 )
			{
				if( CS->camera_meshlist( CS->data, data_size, &camera_frustum, mesh_bounds, mesh_visiblity ) )
				{
					uint32_t outpos = 0;
					for( i = 0; i < data_size; ++i )
					{
						if( mesh_visiblity[ i / 32 ] & ( 1 << ( i % 32 ) ) )
						{
							if( i > outpos )
							{
								mesh_instances[ outpos ] = mesh_instances[ i ];
								memcpy( &mesh_bounds[ outpos ], &mesh_bounds[ i ], sizeof( mesh_bounds[0] ) );
							}
							outpos++;
						}
					}
					data_size = outpos;
				}
			}
		}
		sgs_Release( C, &val );
	}
	sgs_Release( C, &it );
	
	sgs_Dealloc( mesh_bounds );
	sgs_Dealloc( mesh_visiblity );
	
	sgs_membuf_resize( MB, C, mbsize + sizeof(SS3D_MeshInstance*) * data_size );
	return data_size;
}

uint32_t SS3D_Scene_Cull_Camera_PointLightList( SGS_CTX, sgs_MemBuf* MB, SS3D_Scene* S )
{
	SS3D_Camera* CAM = (SS3D_Camera*) S->camera->data;
	if( !CAM )
		return 0;
	
	uint32_t i, data_size = 0;
	size_t mbsize = MB->size;
	
	SS3D_CullSceneCamera camera_frustum;
	get_frustum_from_camera( CAM, &camera_frustum );
	
	sgs_membuf_resize( MB, C, mbsize + sizeof(SS3D_Light*) * S->lights.size );
	SS3D_Light** light_instances = (SS3D_Light**) ( MB->ptr + mbsize );
	SS3D_CullScenePointLight* light_bounds = sgs_Alloc_n( SS3D_CullScenePointLight, S->lights.size );
	uint32_t* light_visiblity = sgs_Alloc_n( uint32_t, divideup( S->lights.size, 32 ) );
	
	/* fill in light data */
	sgs_SizeVal light_id;
	for( light_id = 0; light_id < S->lights.size; ++light_id )
	{
		SS3D_Light* L = (SS3D_Light*) S->lights.vars[ light_id ].val.data.O->data;
		if( !L->isEnabled || L->type != SS3DLIGHT_POINT )
			continue;
		
		light_instances[ data_size ] = L;
		memcpy( light_bounds[ data_size ].position, L->position, sizeof( VEC3 ) );
		light_bounds[ data_size ].radius = L->range;
		data_size++;
	}
	
	/* iterate all cullscenes */
	sgs_Variable arr, it, val;
	sgs_InitObjectPtr( &arr, S->cullScenes );
	sgs_GetIteratorP( C, &arr, &it );
	while( sgs_IterAdvanceP( C, &it ) > 0 )
	{
		sgs_IterGetDataP( C, &it, NULL, &val );
		if( sgs_IsObjectP( &val, SS3D_CullScene_iface ) )
		{
			SS3D_CullScene* CS = (SS3D_CullScene*) sgs_GetObjectDataP( &val );
			
			if( CS->camera_pointlightlist && ( CS->flags & SS3D_CF_ENABLE_CAM_PLT ) != 0 )
			{
				if( CS->camera_pointlightlist( CS->data, data_size, &camera_frustum, light_bounds, light_visiblity ) )
				{
					uint32_t outpos = 0;
					for( i = 0; i < data_size; ++i )
					{
						if( light_visiblity[ i / 32 ] & ( 1 << ( i % 32 ) ) )
						{
							if( i > outpos )
							{
								light_instances[ outpos ] = light_instances[ i ];
								memcpy( &light_bounds[ outpos ], &light_bounds[ i ], sizeof( light_bounds[0] ) );
							}
							outpos++;
						}
					}
					data_size = outpos;
				}
			}
		}
		sgs_Release( C, &val );
	}
	sgs_Release( C, &it );
	
	sgs_Dealloc( light_bounds );
	sgs_Dealloc( light_visiblity );
	
	sgs_membuf_resize( MB, C, mbsize + sizeof(SS3D_Light*) * data_size );
	return data_size;
}

uint32_t SS3D_Scene_Cull_Camera_SpotLightList( SGS_CTX, sgs_MemBuf* MB, SS3D_Scene* S )
{
	SS3D_Camera* CAM = (SS3D_Camera*) S->camera->data;
	if( !CAM )
		return 0;
	
	uint32_t i, data_size = 0;
	size_t mbsize = MB->size;
	
	SS3D_CullSceneCamera camera_frustum;
	get_frustum_from_camera( CAM, &camera_frustum );
	
	sgs_membuf_resize( MB, C, mbsize + sizeof(SS3D_Light*) * S->lights.size );
	SS3D_Light** light_instances = (SS3D_Light**) ( MB->ptr + mbsize );
	SS3D_CullSceneFrustum* light_bounds = sgs_Alloc_n( SS3D_CullSceneFrustum, S->lights.size );
	MAT4* light_matrices = sgs_Alloc_n( MAT4, S->lights.size );
	uint32_t* light_visiblity = sgs_Alloc_n( uint32_t, divideup( S->lights.size, 32 ) );
	
	/* fill in light data */
	sgs_SizeVal light_id;
	for( light_id = 0; light_id < S->lights.size; ++light_id )
	{
		SS3D_CullSceneCamera light_frustum;
		SS3D_Light* L = (SS3D_Light*) S->lights.vars[ light_id ].val.data.O->data;
		if( !L->isEnabled || L->type != SS3DLIGHT_SPOT )
			continue;
		
		get_frustum_from_light( L, &light_frustum );
		light_instances[ data_size ] = L;
		memcpy( &light_bounds[ data_size ], &light_frustum.frustum, sizeof( light_frustum.frustum ) );
		memcpy( &light_matrices[ data_size ], &light_frustum.invViewProjMatrix, sizeof( light_frustum.invViewProjMatrix ) );
		data_size++;
	}
	
	/* iterate all cullscenes */
	sgs_Variable arr, it, val;
	sgs_InitObjectPtr( &arr, S->cullScenes );
	sgs_GetIteratorP( C, &arr, &it );
	while( sgs_IterAdvanceP( C, &it ) > 0 )
	{
		sgs_IterGetDataP( C, &it, NULL, &val );
		if( sgs_IsObjectP( &val, SS3D_CullScene_iface ) )
		{
			SS3D_CullScene* CS = (SS3D_CullScene*) sgs_GetObjectDataP( &val );
			
			if( CS->camera_spotlightlist && ( CS->flags & SS3D_CF_ENABLE_CAM_PLT ) != 0 )
			{
				if( CS->camera_spotlightlist( CS->data, data_size, &camera_frustum, light_bounds, light_matrices, light_visiblity ) )
				{
					uint32_t outpos = 0;
					for( i = 0; i < data_size; ++i )
					{
						if( light_visiblity[ i / 32 ] & ( 1 << ( i % 32 ) ) )
						{
							if( i > outpos )
							{
								light_instances[ outpos ] = light_instances[ i ];
								memcpy( &light_bounds[ outpos ], &light_bounds[ i ], sizeof( light_bounds[0] ) );
								memcpy( &light_matrices[ outpos ], &light_matrices[ i ], sizeof( light_matrices[0] ) );
							}
							outpos++;
						}
					}
					data_size = outpos;
				}
			}
		}
		sgs_Release( C, &val );
	}
	sgs_Release( C, &it );
	
	sgs_Dealloc( light_matrices );
	sgs_Dealloc( light_bounds );
	sgs_Dealloc( light_visiblity );
	
	sgs_membuf_resize( MB, C, mbsize + sizeof(SS3D_Light*) * data_size );
	return data_size;
}
/********** SCENE CULLING END ***********/

static int scene_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SC_HDR;
	SGS_BEGIN_INDEXFUNC
		// methods
		SGS_CASE( "createMeshInstance" )  SGS_RETURN_CFUNC( scenei_createMeshInstance );
		SGS_CASE( "destroyMeshInstance" ) SGS_RETURN_CFUNC( scenei_destroyMeshInstance );
		SGS_CASE( "createLight" )         SGS_RETURN_CFUNC( scenei_createLight );
		SGS_CASE( "destroyLight" )        SGS_RETURN_CFUNC( scenei_destroyLight );
		
		// properties
		SGS_CASE( "cullScenes" ) SGS_RETURN_OBJECT( S->cullScenes );
		SGS_CASE( "camera" )    SGS_RETURN_OBJECT( S->camera );
		
		SGS_CASE( "fogColor" )         SGS_RETURN_VEC3P( S->fogColor );
		SGS_CASE( "fogHeightFactor" )  SGS_RETURN_REAL( S->fogHeightFactor );
		SGS_CASE( "fogDensity" )       SGS_RETURN_REAL( S->fogDensity );
		SGS_CASE( "fogHeightDensity" ) SGS_RETURN_REAL( S->fogHeightDensity );
		SGS_CASE( "fogStartHeight" )   SGS_RETURN_REAL( S->fogStartHeight );
		SGS_CASE( "fogMinDist" )       SGS_RETURN_REAL( S->fogMinDist );
		
		SGS_CASE( "ambientLightColor" ) SGS_RETURN_VEC3P( S->ambientLightColor );
		SGS_CASE( "dirLightColor" )     SGS_RETURN_VEC3P( S->dirLightColor );
		SGS_CASE( "dirLightDir" )       SGS_RETURN_VEC3P( S->dirLightDir );
		
		SGS_CASE( "skyTexture" )       SGS_RETURN_OBJECT( S->skyTexture );
	SGS_END_INDEXFUNC;
}

static int scene_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SC_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "camera" )
		{
			if( val->type == SGS_VT_NULL )
			{
				sgs_ObjAssign( C, &S->camera, NULL );
				return SGS_SUCCESS;
			}
			else if( sgs_IsObjectP( val, SS3D_Camera_iface ) )
			{
				sgs_ObjAssign( C, &S->camera, sgs_GetObjectStructP( val ) );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		
		SGS_CASE( "fogColor" )         SGS_PARSE_VEC3( S->fogColor, 0 )
		SGS_CASE( "fogHeightFactor" )  SGS_PARSE_REAL( S->fogHeightFactor )
		SGS_CASE( "fogDensity" )       SGS_PARSE_REAL( S->fogDensity )
		SGS_CASE( "fogHeightDensity" ) SGS_PARSE_REAL( S->fogHeightDensity )
		SGS_CASE( "fogStartHeight" )   SGS_PARSE_REAL( S->fogStartHeight )
		SGS_CASE( "fogMinDist" )       SGS_PARSE_REAL( S->fogMinDist )
		
		SGS_CASE( "ambientLightColor" ) SGS_PARSE_VEC3( S->ambientLightColor, 0 )
		SGS_CASE( "dirLightColor" )     SGS_PARSE_VEC3( S->dirLightColor, 0 )
		SGS_CASE( "dirLightDir" )       SGS_PARSE_VEC3( S->dirLightDir, 0 )
		
		SGS_CASE( "skyTexture" )
		{
			if( val->type == SGS_VT_NULL )
			{
				sgs_ObjAssign( C, &S->skyTexture, NULL );
				return SGS_SUCCESS;
			}
			else if( sgs_IsObjectP( val, S->renderer->ifTexture ) )
			{
				sgs_ObjAssign( C, &S->skyTexture, sgs_GetObjectStructP( val ) );
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
			sgs_VarObj* tmpobj = (sgs_VarObj*) S->meshInstances.vars[ i ].val.data.P;
			sgs_ObjCallDtor( C, tmpobj );
		}
		for( i = 0; i < S->lights.size; ++i )
		{
			sgs_VarObj* tmpobj = (sgs_VarObj*) S->lights.vars[ i ].val.data.P;
			sgs_ObjCallDtor( C, tmpobj );
		}
		sgs_vht_free( &S->meshInstances, C );
		sgs_vht_free( &S->lights, C );
		if( S->cullScenes )
		{
			sgs_ObjRelease( C, S->cullScenes );
			S->cullScenes = NULL;
		}
		if( S->skyTexture )
		{
			sgs_ObjRelease( C, S->skyTexture );
			S->skyTexture = NULL;
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
	R->currentRT = NULL;
	R->viewport = NULL;
	
	R->disablePostProcessing = 0;
	R->dbg_rt = 0;
	
	R->stat_numVisMeshes = 0;
	R->stat_numVisPLights = 0;
	R->stat_numVisSLights = 0;
	R->stat_numDrawCalls = 0;
	R->stat_numSDrawCalls = 0;
	R->stat_numMDrawCalls = 0;
	R->stat_numPDrawCalls = 0;
	
	sgs_InitDict( C, &storeVar, 0 );
	R->store = sgs_GetObjectStructP( &storeVar );
	
	/* default pass info */
	memset( R->passes, 0, sizeof(R->passes) );
	R->numPasses = 9;
	/* SHADOW PASS INFO */
	R->passes[0].type = SS3D_RPT_SHADOWS;
	strcpy( R->passes[0].shname, "ps_shadow" );
	/* PASS1: [SOLID,STATIC] LIGHTMAP + SUN + 0-16 POINT LIGHTS (once) */
	R->passes[1].type = SS3D_RPT_OBJECT;
	R->passes[1].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_STATIC | SS3D_RPF_ENABLED;
	R->passes[1].maxruns = 1;
	R->passes[1].pointlight_count = 16;
	R->passes[1].spotlight_count = 0;
	R->passes[1].num_inst_textures = 4;
	strcpy( R->passes[1].shname, "ps_base_isp16" );
	/* PASS2: [SOLID,DYNAMIC] DIRAMB + SUN + 0-16 POINT LIGHTS (once) */
	R->passes[2].type = SS3D_RPT_OBJECT;
	R->passes[2].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_DYNAMIC | SS3D_RPF_ENABLED | SS3D_RPF_CALC_DIRAMB;
	R->passes[2].maxruns = 1;
	R->passes[2].pointlight_count = 16;
	R->passes[2].spotlight_count = 0;
	R->passes[2].num_inst_textures = 0;
	strcpy( R->passes[2].shname, "ps_base_dsp16" );
	/* PASS3: [SOLID,ANY] 0-16 POINT LIGHTS (as much as necessary) */
	R->passes[3].type = SS3D_RPT_OBJECT;
	R->passes[3].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[3].maxruns = -1;
	R->passes[3].pointlight_count = 16;
	R->passes[3].spotlight_count = 0;
	R->passes[3].num_inst_textures = 0;
	strcpy( R->passes[3].shname, "ps_ext_p16" );
	/* PASS4: [SOLID,ANY] 0-4 SPOT LIGHTS (as much as necessary) */
	R->passes[4].type = SS3D_RPT_OBJECT;
	R->passes[4].flags = SS3D_RPF_MTL_SOLID | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[4].maxruns = -1;
	R->passes[4].pointlight_count = 0;
	R->passes[4].spotlight_count = 4;
	R->passes[4].num_inst_textures = 0;
	strcpy( R->passes[4].shname, "ps_ext_s4" );
	/* PASS5: [DEPTH] FOG */
	R->passes[5].type = SS3D_RPT_SCREEN;
	strcpy( R->passes[5].shname, "pp_ss_fog" );
	/* PASS6: [TRANSPARENT,ANY] DIRAMB + SUN + 0-16 POINT LIGHTS (once) */
	R->passes[6].type = SS3D_RPT_OBJECT;
	R->passes[6].flags = SS3D_RPF_MTL_TRANSPARENT | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_CALC_DIRAMB;
	R->passes[6].maxruns = 1;
	R->passes[6].pointlight_count = 16;
	R->passes[6].spotlight_count = 0;
	R->passes[6].num_inst_textures = 4;
	strcpy( R->passes[6].shname, "ps_base_dsp16" );
	/* PASS7: [TRANSPARENT,ANY] 0-16 POINT LIGHTS (as much as necessary) */
	R->passes[7].type = SS3D_RPT_OBJECT;
	R->passes[7].flags = SS3D_RPF_MTL_TRANSPARENT | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[7].maxruns = -1;
	R->passes[7].pointlight_count = 16;
	R->passes[7].spotlight_count = 0;
	R->passes[7].num_inst_textures = 0;
	strcpy( R->passes[7].shname, "ps_ext_p16" );
	/* PASS8: [TRANSPARENT,ANY] 0-4 SPOT LIGHTS (as much as necessary) */
	R->passes[8].type = SS3D_RPT_OBJECT;
	R->passes[8].flags = SS3D_RPF_MTL_TRANSPARENT | SS3D_RPF_OBJ_ALL | SS3D_RPF_ENABLED | SS3D_RPF_LIGHTOVERLAY;
	R->passes[8].maxruns = -1;
	R->passes[8].pointlight_count = 0;
	R->passes[8].spotlight_count = 4;
	R->passes[8].num_inst_textures = 0;
	strcpy( R->passes[8].shname, "ps_ext_s4" );
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
	if( R->currentRT )
		sgs_ObjRelease( R->C, R->currentRT );
	if( R->viewport )
		sgs_ObjRelease( R->C, R->viewport );
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
	
	sgs_Variable cullScenes;
	push_default_cullscene( R->C );
	sgs_InitArray( R->C, &cullScenes, 1 );
	S->cullScenes = sgs_GetObjectStructP( &cullScenes );
	
	VEC3_Set( S->fogColor, 0, 0, 0 );
	S->fogHeightFactor = 0;
	S->fogDensity = 0;
	S->fogHeightDensity = 0;
	S->fogStartHeight = 0;
	S->fogMinDist = 0;
	VEC3_Set( S->ambientLightColor, 0, 0, 0 );
	VEC3_Set( S->dirLightColor, 0, 0, 0 );
	VEC3_Set( S->dirLightDir, 0, 0, -1 );
	
	S->skyTexture = NULL;
	
	SS3D_Renderer_PokeResource( R, sgs_GetObjectStruct( R->C, -1 ), 1 );
}


static int SS3D_CreateRenderer( SGS_CTX )
{
	char* rendererType;
	void* device = NULL;
	
	SGSFN( "SS3D_CreateRenderer" );
	if( !sgs_LoadArgs( C, "s|&", &rendererType, &device ) )
		return 0;
	
	if( !strcmp( rendererType, "D3D9" ) && !device )
		return sgs_Msg( C, SGS_WARNING, "Direct3D requires a device pointer (argument 2)" );
	
	if( !strcmp( rendererType, "D3D9" ) )
		return SS3D_PushRenderer_D3D9( C, device );
	else if( !strcmp( rendererType, "GL" ) )
		return SS3D_PushRenderer_GL( C );
	else
		return sgs_Msg( C, SGS_WARNING, "unsupported renderer type" );
}


static sgs_RegFuncConst ss3d_fconsts[] =
{
	FN( MeshGen_Cube ),
	FN( MeshGen_Particles ),
	FN( MeshGen_Terrain ),
	
	FN( MeshData_GetVertexIndexArrays ),
	
	FN( CreateCullScene ),
	FN( CreateCamera ),
	FN( CreateViewport ),
	FN( CreateRenderer ),
};

static sgs_RegIntConst ss3d_iconsts[] =
{
	CN( TEXTURE_USAGE_MISC ), CN( TEXTURE_USAGE_ALBEDO ), CN( TEXTURE_USAGE_NORMAL ),
	CN( LIGHT_POINT ), CN( LIGHT_SPOT ),
	CN( RT_FORMAT_BACKBUFFER ), CN( RT_FORMAT_DEPTH ),
};


SGS_APIFUNC int sgscript_main( SGS_CTX )
{
	push_default_cullscene( C );
	sgs_StoreGlobal( C, "SS3D_MainCullScene" );
	
	sgs_PushPtr( C, SS3D_ISCF_Camera_MeshList );
	sgs_StoreGlobal( C, "SS3D_ISCF_Camera_MeshList" );
	sgs_PushPtr( C, SS3D_ISCF_Camera_PointLightList );
	sgs_StoreGlobal( C, "SS3D_ISCF_Camera_PointLightList" );
	
	sgs_RegFuncConsts( C, ss3d_fconsts, sizeof(ss3d_fconsts) / sizeof(ss3d_fconsts[0]) );
	sgs_RegIntConsts( C, ss3d_iconsts, sizeof(ss3d_iconsts) / sizeof(ss3d_iconsts[0]) );
	if( !sgs_Include( C, "ss3d/engine" ) )
		return SGS_EINPROC;
	return SGS_SUCCESS;
}

