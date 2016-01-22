

#pragma once

#include "../sgscript/ext/sgs_cppbc.h"
#include "../sgscript/ext/sgsxgmath.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <vector>
#include <string>


#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((__always_inline__))
#endif


#define SMALL_FLOAT 0.001f

#define DEG2RAD( x ) ((x)/180.0f*M_PI)


template< class T > T TMIN( const T& a, const T& b ){ return a < b ? a : b; }
template< class T > T TMAX( const T& a, const T& b ){ return a > b ? a : b; }
template< class T > void TMEMSET( T* a, size_t c, const T& v )
{
	for( size_t i = 0; i < c; ++i )
		a[ i ] = v;
}


struct Vec3
{
	float x, y, z;
	
	static FORCE_INLINE Vec3 Create( float x ){ Vec3 v = { x, x, x }; return v; }
	static FORCE_INLINE Vec3 Create( float x, float y, float z ){ Vec3 v = { x, y, z }; return v; }
	static FORCE_INLINE Vec3 CreateFromPtr( const float* x ){ Vec3 v = { x[0], x[1], x[2] }; return v; }
	
	FORCE_INLINE Vec3 operator + () const { return *this; }
	FORCE_INLINE Vec3 operator - () const { Vec3 v = { -x, -y, -z }; return v; }
	
	FORCE_INLINE Vec3 operator + ( const Vec3& o ) const { Vec3 v = { x + o.x, y + o.y, z + o.z }; return v; }
	FORCE_INLINE Vec3 operator - ( const Vec3& o ) const { Vec3 v = { x - o.x, y - o.y, z - o.z }; return v; }
	FORCE_INLINE Vec3 operator * ( const Vec3& o ) const { Vec3 v = { x * o.x, y * o.y, z * o.z }; return v; }
	FORCE_INLINE Vec3 operator / ( const Vec3& o ) const { Vec3 v = { x / o.x, y / o.y, z / o.z }; return v; }
	
	FORCE_INLINE Vec3 operator + ( float f ) const { Vec3 v = { x + f, y + f, z + f }; return v; }
	FORCE_INLINE Vec3 operator - ( float f ) const { Vec3 v = { x - f, y - f, z - f }; return v; }
	FORCE_INLINE Vec3 operator * ( float f ) const { Vec3 v = { x * f, y * f, z * f }; return v; }
	FORCE_INLINE Vec3 operator / ( float f ) const { Vec3 v = { x / f, y / f, z / f }; return v; }
	
	FORCE_INLINE Vec3& operator += ( const Vec3& o ){ x += o.x; y += o.y; z += o.z; return *this; }
	FORCE_INLINE Vec3& operator -= ( const Vec3& o ){ x -= o.x; y -= o.y; z -= o.z; return *this; }
	FORCE_INLINE Vec3& operator *= ( const Vec3& o ){ x *= o.x; y *= o.y; z *= o.z; return *this; }
	FORCE_INLINE Vec3& operator /= ( const Vec3& o ){ x /= o.x; y /= o.y; z /= o.z; return *this; }
	
	FORCE_INLINE Vec3& operator += ( float f ){ x += f; y += f; z += f; return *this; }
	FORCE_INLINE Vec3& operator -= ( float f ){ x -= f; y -= f; z -= f; return *this; }
	FORCE_INLINE Vec3& operator *= ( float f ){ x *= f; y *= f; z *= f; return *this; }
	FORCE_INLINE Vec3& operator /= ( float f ){ x /= f; y /= f; z /= f; return *this; }
	
	FORCE_INLINE bool operator == ( const Vec3& o ) const { return x == o.x && y == o.y && z == o.z; }
	FORCE_INLINE bool operator != ( const Vec3& o ) const { return x != o.x || y != o.y || z != o.z; }
	
	FORCE_INLINE bool IsZero() const { return x == 0 && y == 0 && z == 0; }
	FORCE_INLINE bool NearZero() const { return fabs(x) < SMALL_FLOAT && fabs(y) < SMALL_FLOAT && fabs(z) < SMALL_FLOAT; }
	FORCE_INLINE float LengthSq() const { return x * x + y * y + z * z; }
	FORCE_INLINE float Length() const { return sqrtf( LengthSq() ); }
	FORCE_INLINE Vec3 Normalized() const
	{
		float lensq = LengthSq();
		if( lensq == 0 )
		{
			Vec3 v = { 0, 0, 0 };
			return v;
		}
		float invlen = 1.0f / sqrtf( lensq );
		Vec3 v = { x * invlen, y * invlen, z * invlen };
		return v;
	}
};

FORCE_INLINE Vec3 operator + ( float f, const Vec3& v ){ Vec3 out = { f + v.x, f + v.y, f + v.z }; return out; }
FORCE_INLINE Vec3 operator - ( float f, const Vec3& v ){ Vec3 out = { f - v.x, f - v.y, f - v.z }; return out; }
FORCE_INLINE Vec3 operator * ( float f, const Vec3& v ){ Vec3 out = { f * v.x, f * v.y, f * v.z }; return out; }
FORCE_INLINE Vec3 operator / ( float f, const Vec3& v ){ Vec3 out = { f / v.x, f / v.y, f / v.z }; return out; }

FORCE_INLINE float Vec3Dot( const Vec3& v1, const Vec3& v2 ){ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
FORCE_INLINE Vec3 Vec3Cross( const Vec3& v1, const Vec3& v2 )
{
	Vec3 out =
	{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,
	};
	return out;
}


struct Mat4
{
	union
	{
		float a[16];
		float m[4][4];
	};
	
	void SetIdentity()
	{
		for( int i = 0; i < 4; ++i )
			for( int j = 0; j < 4; ++j )
				m[i][j] = i == j;
	}
	static Mat4 CreateIdentity()
	{
		Mat4 m;
		m.SetIdentity();
		return m;
	}
	
	FORCE_INLINE Vec3 TransformPos( const Vec3& v ) const
	{
		Vec3 out =
		{
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		};
		float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
		float q = w ? 1.0f / w : 1.0f;
		return out * q;
	}
	
	FORCE_INLINE void TransformPosPersp( const Vec3& v, Vec3& out_v, float& out_w ) const
	{
		Vec3 out =
		{
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		};
		float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
		float q = w ? 1.0f / w : 1.0f;
		out_v = out * fabsf( q );
		out_w = q;
	}
	
	FORCE_INLINE void TransformPosPrePersp( const Vec3& v, Vec3& out_v, float& out_w ) const
	{
		Vec3 out =
		{
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		};
		out_v = out;
		out_w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
	}
	
	FORCE_INLINE Vec3 TransformPosPerspXY( const Vec3& v ) const
	{
		Vec3 out =
		{
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		};
		float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
		float q = fabs( w ? 1.0f / w : 1.0f );
		out *= q;
		return out;
	}
	
	void Multiply( const Mat4& A, const Mat4& B )
	{
		m[0][0] = A.m[0][0] * B.m[0][0] + A.m[0][1] * B.m[1][0] + A.m[0][2] * B.m[2][0] + A.m[0][3] * B.m[3][0];
		m[0][1] = A.m[0][0] * B.m[0][1] + A.m[0][1] * B.m[1][1] + A.m[0][2] * B.m[2][1] + A.m[0][3] * B.m[3][1];
		m[0][2] = A.m[0][0] * B.m[0][2] + A.m[0][1] * B.m[1][2] + A.m[0][2] * B.m[2][2] + A.m[0][3] * B.m[3][2];
		m[0][3] = A.m[0][0] * B.m[0][3] + A.m[0][1] * B.m[1][3] + A.m[0][2] * B.m[2][3] + A.m[0][3] * B.m[3][3];
		m[1][0] = A.m[1][0] * B.m[0][0] + A.m[1][1] * B.m[1][0] + A.m[1][2] * B.m[2][0] + A.m[1][3] * B.m[3][0];
		m[1][1] = A.m[1][0] * B.m[0][1] + A.m[1][1] * B.m[1][1] + A.m[1][2] * B.m[2][1] + A.m[1][3] * B.m[3][1];
		m[1][2] = A.m[1][0] * B.m[0][2] + A.m[1][1] * B.m[1][2] + A.m[1][2] * B.m[2][2] + A.m[1][3] * B.m[3][2];
		m[1][3] = A.m[1][0] * B.m[0][3] + A.m[1][1] * B.m[1][3] + A.m[1][2] * B.m[2][3] + A.m[1][3] * B.m[3][3];
		m[2][0] = A.m[2][0] * B.m[0][0] + A.m[2][1] * B.m[1][0] + A.m[2][2] * B.m[2][0] + A.m[2][3] * B.m[3][0];
		m[2][1] = A.m[2][0] * B.m[0][1] + A.m[2][1] * B.m[1][1] + A.m[2][2] * B.m[2][1] + A.m[2][3] * B.m[3][1];
		m[2][2] = A.m[2][0] * B.m[0][2] + A.m[2][1] * B.m[1][2] + A.m[2][2] * B.m[2][2] + A.m[2][3] * B.m[3][2];
		m[2][3] = A.m[2][0] * B.m[0][3] + A.m[2][1] * B.m[1][3] + A.m[2][2] * B.m[2][3] + A.m[2][3] * B.m[3][3];
		m[3][0] = A.m[3][0] * B.m[0][0] + A.m[3][1] * B.m[1][0] + A.m[3][2] * B.m[2][0] + A.m[3][3] * B.m[3][0];
		m[3][1] = A.m[3][0] * B.m[0][1] + A.m[3][1] * B.m[1][1] + A.m[3][2] * B.m[2][1] + A.m[3][3] * B.m[3][1];
		m[3][2] = A.m[3][0] * B.m[0][2] + A.m[3][1] * B.m[1][2] + A.m[3][2] * B.m[2][2] + A.m[3][3] * B.m[3][2];
		m[3][3] = A.m[3][0] * B.m[0][3] + A.m[3][1] * B.m[1][3] + A.m[3][2] * B.m[2][3] + A.m[3][3] * B.m[3][3];
	}
	
	void Scale( Vec3 scale )
	{
		SetIdentity();
		m[0][0] = scale.x;
		m[1][1] = scale.y;
		m[2][2] = scale.z;
	}
};


typedef std::vector< uint32_t > U32Vector;
typedef std::vector< Vec3 > Vec3Vector;

struct PPVertex
{
	int x, y;
	float z;
};
typedef std::vector< PPVertex > PPVVector;

struct OcclusionTest
{
	OcclusionTest( int w, int h );
	~OcclusionTest();
	
	void SetViewProjMatrix( const Mat4& matrix );
	
	void ClearWorld();
	void AddWorldBox( const Vec3& from, const Vec3& to, const Mat4& matrix = Mat4::CreateIdentity() );
	void AddWorldTriangle( const Vec3& v0, const Vec3& v1, const Vec3& v2 );
	void AddWorldTriangleNoIndex( const Vec3& v0, const Vec3& v1, const Vec3& v2 );
	void AddWorldTriangles( const Vec3* verts, size_t numverts, const uint32_t* indices, size_t numtris, bool flip = false );
	
	void ClearQueries();
	int32_t AddQueryAABB( const Vec3& from, const Vec3& to );
	int32_t AddQueryBox( const Vec3& from, const Vec3& to, const Mat4& matrix );
	int32_t AddQueryPointList( const Vec3* pts, size_t count );
	
	void Prepare();
	// returns bitmask (don't expect a valid value with an empty query)
	uint32_t* Query();
	
	
	
	int m_width;
	int m_height;
	int m_pitch;
	
	float* m_zbuffer;
	
	Vec3Vector m_vertices;
	U32Vector m_indices;
	
	Vec3Vector m_queryData;
	U32Vector m_queryOffsetSize;
	
	Mat4 m_viewProjMatrix;
	Mat4 m_viewProjImgMatrix;
	
	PPVVector m_transformedVerts;
	U32Vector m_queryOutputCache;
	
	double m_time_xform;
	double m_time_render;
	double m_time_check;
};

inline OcclusionTest::OcclusionTest( int w, int h ) : m_width(w), m_height(h), m_pitch(w+3)
{
	m_zbuffer = new float[ m_pitch * m_height ];
}

inline OcclusionTest::~OcclusionTest()
{
	delete [] m_zbuffer;
}

inline void OcclusionTest::SetViewProjMatrix( const Mat4& matrix )
{
	Mat4 imgmtx; imgmtx.Scale( Vec3::Create( m_width / 2.0f, m_height / -2.0f, 1 ) );
	imgmtx.m[3][0] = m_width / 2.0f;
	imgmtx.m[3][1] = m_height / 2.0f;
	
	m_viewProjMatrix = matrix;
	m_viewProjImgMatrix.Multiply( matrix, imgmtx );
}

inline void OcclusionTest::ClearWorld()
{
	m_vertices.clear();
	m_indices.clear();
}

inline void OcclusionTest::AddWorldBox( const Vec3& from, const Vec3& to, const Mat4& matrix )
{
	Vec3 pts[8] =
	{
		from, {to.x,from.y,from.z}, {from.x,to.y,from.z}, {to.x,to.y,from.z},
		{from.x,from.y,to.z}, {to.x,from.y,to.z}, {from.x,to.y,to.z}, to
	};
	for( int i = 0; i < 8; ++i )
		pts[ i ] = matrix.TransformPos( pts[ i ] );
	
	uint32_t tris[36] =
	{
		0, 1, 2, 1, 3, 2,
		2, 3, 7, 2, 7, 6,
		1, 7, 3, 1, 5, 7,
		6, 7, 4, 7, 5, 4,
		0, 4, 1, 1, 4, 5,
		2, 6, 4, 0, 2, 4,
	};
	
	AddWorldTriangles( pts, 8, tris, 12 );
}

inline void OcclusionTest::AddWorldTriangle( const Vec3& v0, const Vec3& v1, const Vec3& v2 )
{
	const Vec3 tri[3] = { v0, v1, v2 };
	for( int v = 0; v < 3; ++v )
	{
		Vec3 vcur = tri[ v ];
		for( uint32_t i = 0; i < m_vertices.size(); ++i )
		{
			if( vcur == m_vertices[ i ] )
			{
				m_indices.push_back( i );
				goto added;
			}
		}
		m_indices.push_back( m_vertices.size() );
		m_vertices.push_back( vcur );
added:;
	}
}

inline void OcclusionTest::AddWorldTriangleNoIndex( const Vec3& v0, const Vec3& v1, const Vec3& v2 )
{
	m_indices.push_back( m_vertices.size() );
	m_indices.push_back( m_vertices.size() + 1 );
	m_indices.push_back( m_vertices.size() + 2 );
	m_vertices.push_back( v0 );
	m_vertices.push_back( v1 );
	m_vertices.push_back( v2 );
}

inline void OcclusionTest::AddWorldTriangles( const Vec3* verts, size_t numverts, const uint32_t* indices, size_t numtris, bool flip )
{
	uint32_t voff = m_vertices.size();
	m_vertices.resize( voff + numverts );
	for( size_t i = 0; i < numverts; ++i )
		m_vertices[ voff + i ] = verts[ i ];
	
	uint32_t ioff = m_indices.size();
	m_indices.resize( ioff + numtris * 3 );
	if( flip )
	{
		for( size_t i = 0; i < numtris * 3; i += 3 )
		{
			m_indices[ ioff + i + 0 ] = voff + indices[ i + 0 ];
			m_indices[ ioff + i + 1 ] = voff + indices[ i + 2 ];
			m_indices[ ioff + i + 2 ] = voff + indices[ i + 1 ];
		}
	}
	else
	{
		for( size_t i = 0; i < numtris * 3; ++i )
			m_indices[ ioff + i ] = voff + indices[ i ];
	}
}

inline void OcclusionTest::ClearQueries()
{
	m_queryData.clear();
	m_queryOffsetSize.clear();
}

inline int32_t OcclusionTest::AddQueryAABB( const Vec3& from, const Vec3& to )
{
	Vec3 pts[8] =
	{
		from, {to.x,from.y,from.z}, {from.x,to.y,from.z}, {to.x,to.y,from.z},
		{from.x,from.y,to.z}, {to.x,from.y,to.z}, {from.x,to.y,to.z}, to
	};
	return AddQueryPointList( pts, 8 );
}

inline int32_t OcclusionTest::AddQueryBox( const Vec3& from, const Vec3& to, const Mat4& matrix )
{
	Vec3 pts[8] =
	{
		from, {to.x,from.y,from.z}, {from.x,to.y,from.z}, {to.x,to.y,from.z},
		{from.x,from.y,to.z}, {to.x,from.y,to.z}, {from.x,to.y,to.z}, to
	};
	for( int i = 0; i < 8; ++i )
		pts[ i ] = matrix.TransformPos( pts[ i ] );
	return AddQueryPointList( pts, 8 );
}

inline int32_t OcclusionTest::AddQueryPointList( const Vec3* pts, size_t count )
{
	int32_t off = m_queryOffsetSize.size() / 2;
	m_queryOffsetSize.push_back( m_queryData.size() );
	m_queryData.reserve( m_queryData.size() + count );
	for( size_t i = 0; i < count; ++i )
		m_queryData.push_back( pts[ i ] );
	m_queryOffsetSize.push_back( m_queryData.size() );
	return off;
}





// Vec3 interface
template<> inline void sgs_PushVar<Vec3>( SGS_CTX, const Vec3& v ){ sgs_CreateVec3( C, NULL, v.x, v.y, v.z ); }
template<> struct sgs_GetVar<Vec3> { Vec3 operator () ( SGS_CTX, sgs_StkIdx item ){ Vec3 v; sgs_ParseVec3( C, item, &v.x, 0 ); return v; }};

// Mat4 interface
template<> inline void sgs_PushVar<Mat4>( SGS_CTX, const Mat4& v ){ sgs_CreateMat4( C, NULL, v.a, 0 ); }
template<> struct sgs_GetVar<Mat4> { Mat4 operator () ( SGS_CTX, sgs_StkIdx item ){ Mat4 v; sgs_ParseMat4( C, item, v.a ); return v; }};


struct SS3D_OcclusionTest : OcclusionTest
{
	SGS_OBJECT;
	
	SS3D_OcclusionTest( int w, int h ) : OcclusionTest( w, h ){}
	
	SGS_METHOD void ClearWorld(){ return OcclusionTest::ClearWorld(); }
	SGS_METHOD void AddWorldBox( const Vec3& vmin, const Vec3& vmax, Mat4 mtx )
	{
		if( sgs_StackSize( C ) < 3 )
			mtx.SetIdentity();
		OcclusionTest::AddWorldBox( vmin, vmax, mtx );
	}
	SGS_METHOD void AddWorldTriangle( const Vec3& v0, const Vec3& v1, const Vec3& v2, bool noindex )
	{
		if( noindex )
			OcclusionTest::AddWorldTriangleNoIndex( v0, v1, v2 );
		else
			OcclusionTest::AddWorldTriangle( v0, v1, v2 );
	}
	// TODO AddWorldTriangles
	
	SGS_METHOD sgsVariable CreateCullScene();
	
	SGS_METHOD void DumpBuffer( sgsString tgafile );
	SGS_METHOD SGS_MULTRET DumpImage( float scale, float power );
};


