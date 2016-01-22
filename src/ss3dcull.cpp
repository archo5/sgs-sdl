
#include <windows.h>
#include <emmintrin.h>
#include <float.h>

#include "ss3dcull.hpp"

extern "C" {
#include "ss3d_engine.h"
}



double ftime()
{
	LARGE_INTEGER freq, counter;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);
	return (double) counter.QuadPart / (double) freq.QuadPart;
}


//
// RASTERIZATION
//
// - p1, p2, p3 - in image space
//


struct Point2D
{
	int x, y;
};

FORCE_INLINE int orient2d(const Point2D& a, const Point2D& b, const Point2D& c)
{
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

void RasterizeTriangle2D_1( float* image, int width, int height, const PPVertex& p1, const PPVertex& p2, const PPVertex& p3 )
{
	int maxX = TMAX( p1.x, TMAX( p2.x, p3.x ) );
	int minX = TMIN( p1.x, TMIN( p2.x, p3.x ) );
	int maxY = TMAX( p1.y, TMAX( p2.y, p3.y ) );
	int minY = TMIN( p1.y, TMIN( p2.y, p3.y ) );
	
	if( maxX < 0 || minX >= width || maxY < 0 || minY >= height )
		return;
	if( maxX < 0 ) maxX = 0; else if( maxX >= width ) maxX = width - 1;
	if( minX < 0 ) minX = 0; else if( minX >= width ) minX = width - 1;
	if( maxY < 0 ) maxY = 0; else if( maxY >= height ) maxY = height - 1;
	if( minY < 0 ) minY = 0; else if( minY >= height ) minY = height - 1;
	
	Point2D v0 = { p1.x, p1.y }, v1 = { p2.x, p2.y }, v2 = { p3.x, p3.y };
	
	// Triangle setup
	int A01 = v0.y - v1.y, B01 = v1.x - v0.x;
	int A12 = v1.y - v2.y, B12 = v2.x - v1.x;
	int A20 = v2.y - v0.y, B20 = v0.x - v2.x;
	
	Point2D p = { minX, minY };
	int w0_row = orient2d( v1, v2, p );
	int w1_row = orient2d( v2, v0, p );
	int w2_row = orient2d( v0, v1, p );
	
	int wtotal = orient2d( v0, v1, v2 );
	float invfac = 0.5f / ( wtotal );
	
	float p1p2z = ( p2.z - p1.z ) * invfac;
	float p1p3z = ( p3.z - p1.z ) * invfac;
	
	for( p.y = minY; p.y <= maxY; p.y++ )
	{
		// Barycentric coordinates at start of row
		int w0 = w0_row;
		int w1 = w1_row;
		int w2 = w2_row;
		
		for( p.x = minX; p.x <= maxX; p.x++ )
		{
			if( (w0 | w1 | w2) >= 0 )
			{
				float& imgpx = image[ p.x + width * p.y ];
				//float imgval = ( p1.z * w0 + p2.z * w1 + p3.z * w2 ) * invfac;
				float imgval = ( p1.z + p1p2z * w1 + p1p3z * w2 );
				if( imgpx > imgval )
					imgpx = imgval;
			}
			
			// One step to the right
			w0 += A12;
			w1 += A20;
			w2 += A01;
		}
		
		// One row step
		w0_row += B12;
		w1_row += B20;
		w2_row += B01;
	}
}


static inline __m128i muly(const __m128i &a, const __m128i &b)
{
    __m128i tmp1 = _mm_mul_epu32(a,b); /* mul 2,0*/
    __m128i tmp2 = _mm_mul_epu32( _mm_srli_si128(a,4), _mm_srli_si128(b,4)); /* mul 3,1 */
    return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE (0,0,2,0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE (0,0,2,0))); /* shuffle results to [63..0] and pack */
}

struct Vec4i
{
	__m128i data;
	
	Vec4i() {}
	Vec4i( __m128i iv ) : data( iv ) {}
	Vec4i( int i ) : data( _mm_set1_epi32( i ) ) {}
	Vec4i( int a, int b, int c, int d ) : data( _mm_setr_epi32( a, b, c, d ) ) {}
	
	static bool any( const Vec4i& iv ){ return iv[0] | iv[1] | iv[2] | iv[3]; }
	
	FORCE_INLINE Vec4i operator + ( const Vec4i& other ) const { return _mm_add_epi32( data, other.data ); }
	FORCE_INLINE Vec4i& operator += ( const Vec4i& other ) { data = _mm_add_epi32( data, other.data ); return *this; }
	FORCE_INLINE Vec4i operator * ( const Vec4i& other ) const { return muly( data, other.data ); }
	FORCE_INLINE Vec4i operator | ( const Vec4i& other ) const { return _mm_or_si128( data, other.data ); }
	FORCE_INLINE Vec4i operator >= ( const Vec4i& other ) const { return _mm_cmplt_epi32( other.data, data ); }
	
	int operator [] ( int i ) const { return data[ i ]; }
};

struct Edge
{
	// Dimensions of our pixel group
	static const int stepXSize = 4;
	static const int stepYSize = 1;
	
	Vec4i oneStepX;
	Vec4i oneStepY;
	
	Vec4i init( const Point2D& v0, const Point2D& v1, const Point2D& origin )
	{
		// Edge setup
		int A = v0.y - v1.y, B = v1.x - v0.x;
		int C = v0.x * v1.y - v0.y * v1.x;
		
		// Step deltas
		oneStepX = Vec4i( A * stepXSize );
		oneStepY = Vec4i( B * stepYSize );
		
		// x/y values for initial pixel block
		Vec4i x = Vec4i( origin.x ) + Vec4i( 0, 1, 2, 3 );
		Vec4i y = Vec4i( origin.y );
		
		// Edge function values at origin
		return Vec4i( A ) * x + Vec4i( B ) * y + Vec4i( C );
	}
};

void RasterizeTriangle2D_2( float* image, int width, int height, int pitch, const PPVertex& p1, const PPVertex& p2, const PPVertex& p3 )
{
	int maxX = TMAX( p1.x, TMAX( p2.x, p3.x ) );
	int minX = TMIN( p1.x, TMIN( p2.x, p3.x ) );
	int maxY = TMAX( p1.y, TMAX( p2.y, p3.y ) );
	int minY = TMIN( p1.y, TMIN( p2.y, p3.y ) );
	
	if( maxX < 0 || minX >= width || maxY < 0 || minY >= height )
		return;
#if 1
	if( p1.z <= 0 || p1.z >= 1 || p2.z <=0 || p2.z >= 1 || p3.z <= 0 || p3.z >= 1 )
		return;
#else
	if( ( p1.z <= 0 && p2.z <= 0 && p3.z <= 0 ) || ( p1.z >= 1 && p2.z >= 1 && p3.z >= 1 ) )
		return;
#endif
	if( maxX < 0 ) maxX = 0; else if( maxX >= width ) maxX = width - 1;
	if( minX < 0 ) minX = 0; else if( minX >= width ) minX = width - 1;
	if( maxY < 0 ) maxY = 0; else if( maxY >= height ) maxY = height - 1;
	if( minY < 0 ) minY = 0; else if( minY >= height ) minY = height - 1;
	
	Point2D v0 = { p1.x, p1.y }, v1 = { p2.x, p2.y }, v2 = { p3.x, p3.y };
	
	// Triangle setup
	Point2D p = { minX, minY };
    Edge e01, e12, e20;
	Vec4i w0_row = e12.init( v1, v2, p );
	Vec4i w1_row = e20.init( v2, v0, p );
	Vec4i w2_row = e01.init( v0, v1, p );
	
	int wtotal = orient2d( v0, v1, v2 );
	float invfac = 1.0f / ( wtotal );
	
	float p1p2z = ( p2.z - p1.z ) * invfac;
	float p1p3z = ( p3.z - p1.z ) * invfac;
	
	__m128 p1z_x4 = _mm_set1_ps( p1.z );
	__m128 p1p2z_x4 = _mm_set1_ps( p1p2z );
	__m128 p1p3z_x4 = _mm_set1_ps( p1p3z );
#if 0
	__m128 f0_x4 = _mm_set1_ps( 0 );
	__m128 f1_x4 = _mm_set1_ps( 1 );
#endif
	
	for( p.y = minY; p.y <= maxY; p.y += Edge::stepYSize )
	{
		// Barycentric coordinates at start of row
		Vec4i w0 = w0_row;
		Vec4i w1 = w1_row;
		Vec4i w2 = w2_row;
		
		for( p.x = minX; p.x <= maxX; p.x += Edge::stepXSize )
		{
			Vec4i mask = ( w0 | w1 | w2 ) >= 0;
			if( Vec4i::any( mask ) )
			{
				float* imgpos = &image[ p.x + pitch * p.y ];
				
				__m128 imgval_x4 = _mm_add_ps( p1z_x4, _mm_add_ps(
					_mm_mul_ps( p1p2z_x4, _mm_cvtepi32_ps( w1.data ) ),
					_mm_mul_ps( p1p3z_x4, _mm_cvtepi32_ps( w2.data ) ) ) );
				__m128 imgpx_x4 = _mm_loadu_ps( imgpos );
#if 1
				__m128 combmask = _mm_and_ps( _mm_castsi128_ps( mask.data ), _mm_cmpgt_ps( imgpx_x4, imgval_x4 ) );
#else
				__m128 combmask = _mm_and_ps(
					_mm_and_ps( _mm_castsi128_ps( mask.data ), _mm_cmpgt_ps( imgpx_x4, imgval_x4 ) ),
					_mm_and_ps( _mm_cmpgt_ps( imgval_x4, f0_x4 ), _mm_cmpgt_ps( f1_x4, imgval_x4 ) )
				);
#endif
				__m128 output = _mm_or_ps( _mm_and_ps( combmask, imgval_x4 ), _mm_andnot_ps( combmask, imgpx_x4 ) );
				_mm_storeu_ps( imgpos, output );
			}
			
			// One step to the right
			w0 += e12.oneStepX;
			w1 += e20.oneStepX;
			w2 += e01.oneStepX;
		}
		
		// One row step
		w0_row += e12.oneStepY;
		w1_row += e20.oneStepY;
		w2_row += e01.oneStepY;
	}
}


void OcclusionTest::Prepare()
{
	const int IMG_WIDTH = m_width;
	const int IMG_HEIGHT = m_height;
	const int IMG_PITCH = m_pitch;
	
	/// TRANSFORM
	//
	double t1;
	t1 = ftime();
	m_transformedVerts.resize( m_vertices.size() );
	for( size_t i = 0; i < m_vertices.size(); ++i )
	{
		Vec3 v = m_viewProjMatrix.TransformPosPerspXY( m_vertices[ i ] );
		PPVertex ppv = { (int)( ( v.x * 0.5 + 0.5 ) * IMG_WIDTH ), (int)( ( v.y * -0.5 + 0.5 ) * IMG_HEIGHT ), v.z };
		m_transformedVerts[ i ] = ppv;
	}
	m_time_xform = ftime() - t1;
	
	/// RENDER
	//
	const U32Vector& l_indices = m_indices;
	const PPVVector& l_transformedVerts = m_transformedVerts;
	
	t1 = ftime();
	TMEMSET( m_zbuffer, IMG_PITCH * IMG_HEIGHT, 999999.0f );
	for( size_t i = 0; i < m_indices.size(); i += 3 )
	{
		const PPVertex& v0 = l_transformedVerts[ l_indices[ i+0 ] ];
		const PPVertex& v1 = l_transformedVerts[ l_indices[ i+1 ] ];
		const PPVertex& v2 = l_transformedVerts[ l_indices[ i+2 ] ];
		RasterizeTriangle2D_2( m_zbuffer, IMG_WIDTH, IMG_HEIGHT, IMG_PITCH, v0, v1, v2 );
	}
	m_time_render = ftime() - t1;
}

uint32_t* OcclusionTest::Query()
{
	const int IMG_WIDTH = m_width;
	const int IMG_HEIGHT = m_height;
	const int IMG_PITCH = m_pitch;
	
	/// QUERY
	//
	double t1;
	t1 = ftime();
	uint32_t qcount = m_queryOffsetSize.size() / 2;
	m_queryOutputCache.resize( ( qcount + 31 ) / 32 );
	TMEMSET( &m_queryOutputCache[0], m_queryOutputCache.size(), 0U );
	for( size_t i = 0; i < m_queryOffsetSize.size(); i += 2 )
	{
		uint32_t qid = i / 2;
		uint32_t query_begin = m_queryOffsetSize[ i ];
		uint32_t query_end = m_queryOffsetSize[ i + 1 ];
		uint32_t qout_quad = qid / 32;
		uint32_t qout_bit = qid % 32;
		
		Vec3 bbmin = { FLT_MAX, FLT_MAX, FLT_MAX }, bbmax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
	//	Vec3 wbbmin = { FLT_MAX, FLT_MAX, FLT_MAX }, wbbmax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
		const Vec3 boundsmin = { -1, -1, 0 }, boundsmax = { 1, 1, 1 }; // flip'd
		for( uint32_t j = query_begin; j < query_end; ++j )
		{
			Vec3 newpos = m_viewProjMatrix.TransformPosPerspXY( m_queryData[ j ] );
			newpos.y = -newpos.y;
			if( bbmin.x > newpos.x ) bbmin.x = newpos.x;
			if( bbmin.y > newpos.y ) bbmin.y = newpos.y;
			if( bbmin.z > newpos.z ) bbmin.z = newpos.z;
			if( bbmax.x < newpos.x ) bbmax.x = newpos.x;
			if( bbmax.y < newpos.y ) bbmax.y = newpos.y;
			if( bbmax.z < newpos.z ) bbmax.z = newpos.z;
			
	//		if( wbbmin.x > m_queryData[ j ].x ) wbbmin.x = m_queryData[ j ].x;
	//		if( wbbmin.y > m_queryData[ j ].y ) wbbmin.y = m_queryData[ j ].y;
	//		if( wbbmin.z > m_queryData[ j ].z ) wbbmin.z = m_queryData[ j ].z;
	//		if( wbbmax.x < m_queryData[ j ].x ) wbbmax.x = m_queryData[ j ].x;
	//		if( wbbmax.y < m_queryData[ j ].y ) wbbmax.y = m_queryData[ j ].y;
	//		if( wbbmax.z < m_queryData[ j ].z ) wbbmax.z = m_queryData[ j ].z;
		}
	//	printf( "query #%d (%d - %d): (%g;%g;%g) -> (%g;%g;%g)\n",
	//		i/2, query_begin, query_end, bbmin.x, bbmin.y, bbmin.z, bbmax.x, bbmax.y, bbmax.z );
		
		int vis = 0;
		if( bbmin.x < boundsmax.x && bbmax.x > boundsmin.x &&
			bbmin.y < boundsmax.y && bbmax.y > boundsmin.y &&
			bbmin.z < boundsmax.z && bbmax.z > boundsmin.z )
		{
	//		if( bbmin.y >= boundsmax.y || bbmax.y <= boundsmin.y )
	//		{
	//			printf( "%f >= %f || %f <= %f\n", bbmin.y , boundsmax.y , bbmax.y , boundsmin.y );
	//			printf( "WBB %f %f %f => %f %f %f\n", wbbmin.x, wbbmin.y, wbbmin.z, wbbmax.x, wbbmax.y, wbbmax.z );
	//		}
			if( bbmin.z < 0 )
			{
				vis = 1;
				goto quickexit;
			}
			int xfrom = floor( ( TMAX( bbmin.x, boundsmin.x ) * 0.5 + 0.5 ) * ( IMG_WIDTH - 1 ) );
			int yfrom = floor( ( TMAX( bbmin.y, boundsmin.y ) * 0.5 + 0.5 ) * ( IMG_HEIGHT - 1 ) );
			int xto = floor( ( TMIN( bbmax.x, boundsmax.x ) * 0.5 + 0.5 ) * ( IMG_WIDTH - 1 ) );
			int yto = floor( ( TMIN( bbmax.y, boundsmax.y ) * 0.5 + 0.5 ) * ( IMG_HEIGHT - 1 ) );
			for( int y = yfrom; y <= yto; ++y )
			{
				for( int x = xfrom; x <= xto; ++x )
				{
					if( m_zbuffer[ x + IMG_PITCH * y ] > bbmin.z )
					{
						vis = 1;
						goto quickexit;
					}
					// TRACE TEST
				//	m_zbuffer[ x + IMG_PITCH * y ] = i / 510.0f;
				}
			}
		}
quickexit:
		if( vis )
			m_queryOutputCache[ qout_quad ] |= 1 << qout_bit;
	}
	m_time_check = ftime() - t1;
	
	return &m_queryOutputCache[0];
}


void dumpimg_bw( const char* file, float* img_rgb, uint32_t width, uint32_t height, uint32_t pitch, float top = 1.0f )
{
	float mult = 255.0f / top;
	
	FILE* fh = fopen( file, "wb" );
	if( !fh )
	{
		printf( "FAILED TO WRITE TO FILE: %s\n", file );
		return;
	}
	unsigned char header[18]={0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	header[12] = width         & 0xFF;
	header[13] = ( width >> 8)  & 0xFF;
	header[14] = (height)       & 0xFF; 
	header[15] = (height >> 8)  & 0xFF;
	header[16] = 24;
	
	fwrite( header, 1, 18, fh );
	for( uint32_t y = height; y > 0; )
	{
		--y;
		for( uint32_t x = 0; x < width; ++x )
		{
			uint32_t off = ( x + pitch * y );
			float val = TMIN( img_rgb[ off ] * mult, 255.0f );
			unsigned char btwr[3] =
			{
				(unsigned char) val,
				(unsigned char) val,
				(unsigned char) val
			};
			fwrite( btwr, 1, 3, fh );
		}
	}
	fclose( fh );
}



static void SS3D_OTCULL_Camera_Prepare( void* data, SS3D_CullSceneCamera* camera )
{
	SS3D_OcclusionTest* OT = (SS3D_OcclusionTest*) data;
	OT->SetViewProjMatrix( *(Mat4*) camera->viewProjMatrix );
	OT->Prepare();
}

static int SS3D_OTCULL_Camera_MeshList( void* data, uint32_t count, SS3D_CullSceneCamera* camera, SS3D_CullSceneMesh* meshes, uint32_t* outbitfield )
{
	SS3D_OcclusionTest* OT = (SS3D_OcclusionTest*) data;
	OT->ClearQueries();
	for( uint32_t i = 0; i < count; ++i )
	{
		OT->AddQueryBox( Vec3::CreateFromPtr( meshes[i].min ), Vec3::CreateFromPtr( meshes[i].max ), *(Mat4*) meshes[i].transform );
	}
	uint32_t* srcbf = OT->Query();
	size_t copycount = ( count + 31 ) / 32;
	memcpy( outbitfield, srcbf, copycount * 4 );
	return 1;
}

static int SS3D_OTCULL_Camera_PointLightList( void* data, uint32_t count, SS3D_CullSceneCamera* camera, SS3D_CullScenePointLight* lights, uint32_t* outbitfield )
{
	SS3D_OcclusionTest* OT = (SS3D_OcclusionTest*) data;
	OT->ClearQueries();
	for( uint32_t i = 0; i < count; ++i )
	{
		Vec3 pos = Vec3::CreateFromPtr( lights[i].position );
		Vec3 radoff = Vec3::Create( lights[i].radius );
		OT->AddQueryAABB( pos - radoff, pos + radoff );
	}
	uint32_t* srcbf = OT->Query();
	size_t copycount = ( count + 31 ) / 32;
	memcpy( outbitfield, srcbf, copycount * 4 );
	return 1;
}

static int SS3D_OTCULL_Camera_SpotLightList( void* data, uint32_t count, SS3D_CullSceneCamera* camera, SS3D_CullSceneFrustum* frusta, MAT4* inv_matrices, uint32_t* outbitfield )
{
	SS3D_OcclusionTest* OT = (SS3D_OcclusionTest*) data;
	OT->ClearQueries();
	for( uint32_t i = 0; i < count; ++i )
	{
		Mat4* mtx = (Mat4*) &inv_matrices[i];
		Vec3 fpts[] =
		{
			Vec3::CreateFromPtr( frusta[i].position ),
			mtx->TransformPos( Vec3::Create(-1,-1,1) ),
			mtx->TransformPos( Vec3::Create( 1,-1,1) ),
			mtx->TransformPos( Vec3::Create( 1, 1,1) ),
			mtx->TransformPos( Vec3::Create(-1, 1,1) ),
		};
		OT->AddQueryPointList( fpts, 5 );
	}
	uint32_t* srcbf = OT->Query();
	size_t copycount = ( count + 31 ) / 32;
	memcpy( outbitfield, srcbf, copycount * 4 );
	return 1;
}

sgsVariable SS3D_OcclusionTest::CreateCullScene()
{
	SS3D_CullScene* CS = SS3D_PushCullScene( C );
	CS->camera_prepare = SS3D_OTCULL_Camera_Prepare;
	CS->camera_meshlist = SS3D_OTCULL_Camera_MeshList;
	CS->camera_pointlightlist = SS3D_OTCULL_Camera_PointLightList;
	CS->camera_spotlightlist = SS3D_OTCULL_Camera_SpotLightList;
	CS->data = this;
	sgsVariable V = sgsHandle<SS3D_OcclusionTest>( this ).get_variable();
	V._acquire();
	CS->store = V.var;
	return sgsVariable( C, -1 );
}

void SS3D_OcclusionTest::DumpBuffer( sgsString tgafile )
{
	if( tgafile.size() )
		dumpimg_bw( tgafile.c_str(), m_zbuffer, m_width, m_height, m_pitch );
}

SGS_MULTRET SS3D_OcclusionTest::DumpImage( float scale, float power )
{
	if( sgs_StackSize( C ) < 1 ) scale = 1;
	if( sgs_StackSize( C ) < 2 ) power = 1;
	sgs_PushInt( C, m_width );
	sgs_PushInt( C, m_height );
	uint8_t* buf = (uint8_t*) sgs_PushStringAlloc( C, m_width * m_height * 4 );
	for( int y = 0; y < m_height; ++y )
	{
		for( int x = 0; x < m_width; ++x )
		{
			int dstoff = ( x + y * m_width ) * 4;
			int srcoff = x + y * m_pitch;
			float val = m_zbuffer[ srcoff ];
			val *= scale;
			val = powf( val, power );
			uint8_t cval = TMAX( TMIN( val, 1.0f ), 0.0f ) * 255.0f;
			buf[ dstoff+0 ] = cval;
			buf[ dstoff+1 ] = cval;
			buf[ dstoff+2 ] = cval;
			buf[ dstoff+3 ] = 0xFF;
		}
	}
	sgs_FinalizeStringAlloc( C, -1 );
	return 3;
}

static int SS3DCull_Create( SGS_CTX )
{
	int32_t w, h;
	SGSFN( "SS3DCull_Create" );
	if( !sgs_LoadArgs( C, "ll", &w, &h ) )
		return 0;
	SGS_CREATECLASS( C, NULL, SS3D_OcclusionTest, ( w, h ) );
	return 1;
}

static sgs_RegFuncConst fconsts[] =
{
	{ "SS3DCull_Create", SS3DCull_Create },
};

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
int sgscript_main( SGS_CTX )
{
	sgs_RegFuncConsts( C, fconsts, sizeof(fconsts) / sizeof(fconsts[0]) );
	return SGS_SUCCESS;
}


