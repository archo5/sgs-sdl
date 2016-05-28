

#include <sgs_util.h>
#include "../sgscript/ext/sgs_cppbc.h"
#include "../sgscript/ext/sgsxgmath.h"

#include "../ext/src/bullet.h"

#define SGS_N_O_EXPORT // broken with inheritance

typedef btCollisionShape* BulletCollisionShapePointer;
typedef btConvexShape* BulletConvexShapePointer;
typedef btCollisionObject* BulletCollisionObjectPointer;

// btVector3 interface
template<> inline void sgs_PushVar<btVector3>( SGS_CTX, const btVector3& v ){ sgs_CreateVec3( C, NULL, v.x(), v.y(), v.z() ); }
template<> struct sgs_GetVar<btVector3> { btVector3 operator () ( SGS_CTX, sgs_StkIdx item ){
	float vtmp[3] = {0.0f}; sgs_ParseVec3( C, item, vtmp, 0 ); return btVector3( vtmp[0], vtmp[1], vtmp[2] ); }};
template<> inline sgsString sgs_DumpData<btVector3>( SGS_CTX, const btVector3& var, int depth ){ char bfr[ 128 ] = {0};
	snprintf( bfr, 127, "btVector3(%g;%g;%g)", var.x(), var.y(), var.z() ); return sgsString( C, bfr ); }

// btQuaternion interface
template<> inline void sgs_PushVar<btQuaternion>( SGS_CTX, const btQuaternion& v ){ sgs_CreateQuat( C, NULL, v.x(), v.y(), v.z(), v.w() ); }
template<> struct sgs_GetVar<btQuaternion> { btQuaternion operator () ( SGS_CTX, sgs_StkIdx item ){
	float vtmp[4] = {0.0f}; sgs_ParseQuat( C, item, vtmp, 0 ); return btQuaternion( vtmp[0], vtmp[1], vtmp[2], vtmp[3] ); }};
template<> inline sgsString sgs_DumpData<btQuaternion>( SGS_CTX, const btQuaternion& var, int depth ){ char bfr[ 128 ] = {0};
	snprintf( bfr, 127, "btQuaternion(%g;%g;%g;w=%g)", var.x(), var.y(), var.z(), var.w() ); return sgsString( C, bfr ); }

// btMatrix3x3
template<> inline void sgs_PushVar<btMatrix3x3>( SGS_CTX, const btMatrix3x3& v ){
	const btVector3& r0 = v.getRow(0); const btVector3& r1 = v.getRow(1); const btVector3& r2 = v.getRow(2);
	float tmp[9] = { r0.x(), r0.y(), r0.z(), r1.x(), r1.y(), r1.z(), r2.x(), r2.y(), r2.z() }; sgs_CreateMat3( C, NULL, tmp, 0 ); }
template<> struct sgs_GetVar<btMatrix3x3> { btMatrix3x3 operator () ( SGS_CTX, sgs_StkIdx item ){
	float v[9] = {0.0f}; sgs_ParseMat3( C, item, v ); return btMatrix3x3( v[0],v[1],v[2], v[3],v[4],v[5], v[6],v[7],v[8] ); }};

// AABB3
struct BulletAABB3
{
	BulletAABB3(){}
	BulletAABB3( const btVector3& vmin, const btVector3& vmax ) : v_min( vmin ), v_max( vmax ){}
	btVector3 v_min, v_max;
};
template<> inline void sgs_PushVar<BulletAABB3>( SGS_CTX, const BulletAABB3& v ){
	float tmp[6] = { v.v_min.x(), v.v_min.y(), v.v_min.z(), v.v_max.x(), v.v_max.y(), v.v_max.z() }; sgs_CreateAABB3p( C, NULL, tmp ); }
template<> struct sgs_GetVar<BulletAABB3> { BulletAABB3 operator () ( SGS_CTX, sgs_StkIdx item ){
	float v[6]; sgs_ParseAABB3( C, item, v ); return BulletAABB3( btVector3( v[0], v[1], v[2] ), btVector3( v[3], v[4], v[5] ) ); } };

// floatarray interface
struct FloatArray
{
	XGM_VT* data;
	sgs_SizeVal count;
};
template<> struct sgs_GetVar<FloatArray> { FloatArray operator () ( SGS_CTX, sgs_StkIdx item ){
	FloatArray arr = { NULL, 0 }; sgs_ParseFloatArray( C, item, &arr.data, &arr.count ); return arr; }};


struct BulletTransform : btTransform
{
	SGS_OBJECT_LITE;
	
	BulletTransform(){}
	BulletTransform( const btTransform& t ) : btTransform(t){}
	
	SGS_PROPERTY_FUNC( READ getOrigin WRITE setOrigin ) SGS_ALIAS( btVector3 origin );
	SGS_PROPERTY_FUNC( READ getOrigin WRITE setOrigin ) SGS_ALIAS( btVector3 position );
	SGS_PROPERTY_FUNC( READ getBasis WRITE setBasis ) SGS_ALIAS( btMatrix3x3 basis );
	SGS_PROPERTY_FUNC( READ getRotation WRITE setRotation ) SGS_ALIAS( btQuaternion orientation );
	SGS_PROPERTY_FUNC( READ getRotation WRITE setRotation ) SGS_ALIAS( btQuaternion rotation );
};
SGS_DEFAULT_LITE_OBJECT_INTERFACE( BulletTransform );
template<> inline void sgs_PushVar<btTransform>( SGS_CTX, const btTransform& t ){ SGS_CREATELITECLASS( C, NULL, BulletTransform, ( t ) ); }


typedef sgsHandle< struct BulletRigidBody > BulletRigidBodyHandle;


struct BulletStridingMeshInterface
{
	btStridingMeshInterface* m_smi;
	
	SGS_OBJECT SGS_N_O_EXPORT;
	
	~BulletStridingMeshInterface(){ delete m_smi; }
	
	static bool Match( sgs_ObjInterface* iface );
	
	//
	// METHODS
	//
	// > internalProcessAllTriangles
	// > calculateAABBBruteForce
	
	//
	// PROPERTIES
	//
	// > premadeAABB
	// > scaling
	btVector3 _get_scaling(){ return m_smi->getScaling(); }
	void _set_scaling( const btVector3& v ){ m_smi->setScaling( v ); }
	SGS_PROPERTY_FUNC( READ _get_scaling WRITE _set_scaling ) SGS_ALIAS( btVector3 scaling );
};


struct BulletStridingMeshInterfaceHandle
{
	sgs_VarObj* obj;
};
template<> inline void sgs_GCMarkVar<BulletStridingMeshInterfaceHandle>( SGS_CTX, BulletStridingMeshInterfaceHandle& v ){ sgs_ObjGCMark( C, v.obj ); }
template<> inline void sgs_PushVar( SGS_CTX, const BulletStridingMeshInterfaceHandle& bsmih ){
	if( !bsmih.obj ) sgs_PushNull( C ); else sgs_PushObjectPtr( C, bsmih.obj ); }
template<> struct sgs_GetVar<BulletStridingMeshInterfaceHandle> { BulletStridingMeshInterfaceHandle operator () ( SGS_CTX, sgs_StkIdx item ){
	BulletStridingMeshInterfaceHandle bsmih = { NULL };
	if( sgs_ItemType( C, item ) == SGS_VT_OBJECT && BulletStridingMeshInterface::Match( sgs_GetObjectIface( C, item ) ) )
		bsmih.obj = sgs_GetObjectStruct( C, item ); return bsmih; }};


#define m_tiva tiva()
struct BulletTriangleIndexVertexArray : BulletStridingMeshInterface
{
	SGS_OBJECT_INHERIT( BulletStridingMeshInterface ) SGS_N_O_EXPORT;
	
	btTriangleIndexVertexArray*& tiva(){ return *(btTriangleIndexVertexArray**)&m_smi; }
	
	//
	// METHODS
	//
	// > preallocateVertices
	SGS_METHOD void preallocateVertices( int c ){ m_tiva->preallocateVertices( c ); }
	// > preallocateIndices
	SGS_METHOD void preallocateIndices( int c ){ m_tiva->preallocateIndices( c ); }
	
	//
	// PROPERTIES
	//
	// > READONLY numSubParts
	int _get_numSubParts(){ return m_tiva->getNumSubParts(); }
	SGS_PROPERTY_FUNC( READ _get_numSubParts ) SGS_ALIAS( int numSubParts );
};


#define m_triMesh triMesh()
struct BulletTriangleMesh : BulletTriangleIndexVertexArray
{
	SGS_OBJECT_INHERIT( BulletTriangleIndexVertexArray );
	
	btTriangleMesh*& triMesh(){ return *(btTriangleMesh**)&m_smi; }
	
	BulletTriangleMesh( bool i32, bool vc4 ){ m_triMesh = new btTriangleMesh( i32, vc4 ); }
	
	//
	// METHODS
	//
	// > addTriangle
	SGS_METHOD void addTriangle( const btVector3& v0, const btVector3& v1, const btVector3& v2, bool remdup ){ m_triMesh->addTriangle( v0, v1, v2, remdup ); }
	// > findOrAddVertex
	SGS_METHOD uint32_t findOrAddVertex( const btVector3& v, bool remdup ){ return m_triMesh->findOrAddVertex( v, remdup ); }
	// > addIndex
	SGS_METHOD void addIndex( uint32_t i ){ return m_triMesh->addIndex( i ); }
	
	//
	// PROPERTIES
	//
	// > READONLY numTriangles
	int _get_numTriangles(){ return m_triMesh->getNumTriangles(); }
	SGS_PROPERTY_FUNC( READ _get_numTriangles ) SGS_ALIAS( int numTriangles );
	// > READONLY numVertices
	int _get_numVertices(){ return m_triMesh->getIndexedMeshArray()[0].m_numVertices; }
	SGS_PROPERTY_FUNC( READ _get_numVertices ) SGS_ALIAS( int numVertices );
	// > READONLY numIndices
	int _get_numIndices(){ return m_triMesh->getNumTriangles() * 3; }
	SGS_PROPERTY_FUNC( READ _get_numIndices ) SGS_ALIAS( int numIndices );
	// > READONLY use32bitIndices
	// > READONLY 
};


///////////////////
// S H A P E S ////
///////////////////

struct BulletCollisionShape
{
	struct BulletCollisionObject* m_colObj;
	
	SGS_OBJECT SGS_N_O_EXPORT;
	
	BulletCollisionShape() : m_colObj(NULL), m_colShape(NULL){}
	virtual ~BulletCollisionShape();
	
	SGS_GCREF( userData );
	
	static bool Match( sgs_ObjInterface* iface );
	
	//
	// METHODS
	//
	// > getAABB
	// > getBoundingSphere
	SGS_METHOD SGS_MULTRET getBoundingSphere(){ btVector3 c; float r; m_colShape->getBoundingSphere( c, r ); sgs_PushVar( C, c ); sgs_PushVar( C, r ); return 2; }
	// > getAngularMotionDisc
	SGS_METHOD float getAngularMotionDisc(){ return m_colShape->getAngularMotionDisc(); }
	// > getContactBreakingThreshold
	SGS_METHOD float getContactBreakingThreshold( float dctf ){ return m_colShape->getContactBreakingThreshold( dctf ); }
	// > calculateTemporalAABB
	// > calculateLocalInertia
	SGS_METHOD btVector3 calculateLocalInertia( float mass ){ btVector3 i; m_colShape->calculateLocalInertia( mass, i ); return i; }
	// > getAnisotropicRollingFrictionDirection
	SGS_METHOD btVector3 getAnisotropicRollingFrictionDirection(){ return m_colShape->getAnisotropicRollingFrictionDirection(); }
	// > calculateSerializeBufferSize
	SGS_METHOD int calculateSerializeBufferSize(){ return m_colShape->calculateSerializeBufferSize(); }
	
	//
	// PROPERTIES
	//
	// > READONLY isPolyhedral
	bool _get_isPolyhedral(){ return m_colShape->isPolyhedral(); }
	SGS_PROPERTY_FUNC( READ _get_isPolyhedral ) SGS_ALIAS( bool isPolyhedral );
	// > READONLY isConvex2D
	bool _get_isConvex2D(){ return m_colShape->isConvex2d(); }
	SGS_PROPERTY_FUNC( READ _get_isConvex2D ) SGS_ALIAS( bool isConvex2D );
	// > READONLY isConvex
	bool _get_isConvex(){ return m_colShape->isConvex(); }
	SGS_PROPERTY_FUNC( READ _get_isConvex ) SGS_ALIAS( bool isConvex );
	// > READONLY isNonMoving
	bool _get_isNonMoving(){ return m_colShape->isNonMoving(); }
	SGS_PROPERTY_FUNC( READ _get_isNonMoving ) SGS_ALIAS( bool isNonMoving );
	// > READONLY isConcave
	bool _get_isConcave(){ return m_colShape->isConcave(); }
	SGS_PROPERTY_FUNC( READ _get_isConcave ) SGS_ALIAS( bool isConcave );
	// > READONLY isCompound
	bool _get_isCompound(){ return m_colShape->isCompound(); }
	SGS_PROPERTY_FUNC( READ _get_isCompound ) SGS_ALIAS( bool isCompound );
	// > READONLY isSoftBody
	bool _get_isSoftBody(){ return m_colShape->isSoftBody(); }
	SGS_PROPERTY_FUNC( READ _get_isSoftBody ) SGS_ALIAS( bool isSoftBody );
	// > READONLY isInfinite
	bool _get_isInfinite(){ return m_colShape->isInfinite(); }
	SGS_PROPERTY_FUNC( READ _get_isInfinite ) SGS_ALIAS( bool isInfinite );
	// > localScaling
	btVector3 _get_localScaling(){ return m_colShape->getLocalScaling(); }
	void _set_localScaling( const btVector3& v ){ m_colShape->setLocalScaling( v ); }
	SGS_PROPERTY_FUNC( READ _get_localScaling WRITE _set_localScaling ) SGS_ALIAS( btVector3 localScaling );
	// > READONLY name
	sgsString _get_name(){ return sgsString( C, m_colShape->getName() ); }
	SGS_PROPERTY_FUNC( READ _get_name ) SGS_ALIAS( sgsString name );
	// > READONLY shapeType
	int _get_shapeType(){ return m_colShape->getShapeType(); }
	SGS_PROPERTY_FUNC( READ _get_shapeType ) SGS_ALIAS( int shapeType );
	// > margin
	float _get_margin(){ return m_colShape->getMargin(); }
	void _set_margin( float m ){ m_colShape->setMargin( m ); }
	SGS_PROPERTY_FUNC( READ _get_margin WRITE _set_margin ) SGS_ALIAS( float margin );
	
	// > userData
	SGS_PROPERTY sgsVariable userData;
	
	btCollisionShape* m_colShape;
};


template<> inline void sgs_PushVar( SGS_CTX, BulletCollisionShapePointer bcsp ){
	if( !bcsp ) sgs_PushNull( C ); else { BulletCollisionShape* bcs = (BulletCollisionShape*) bcsp->getUserPointer();
		sgs_PushObjectPtr( C, bcs->m_sgsObject ); }}
template<> struct sgs_GetVar<BulletCollisionShapePointer> { BulletCollisionShapePointer operator () ( SGS_CTX, sgs_StkIdx item ){
	if( sgs_ItemType( C, item ) == SGS_VT_OBJECT && BulletCollisionShape::Match( sgs_GetObjectIface( C, item ) ) )
		return ((BulletCollisionShape*)sgs_GetObjectData( C, item ))->m_colShape; else return NULL; }};

inline void BTCS_Acquire( SGS_CTX, btCollisionShape* shape )
{
	if( !shape ) return;
	BulletCollisionShape* bcs = (BulletCollisionShape*) shape->getUserPointer();
	sgs_ObjAcquire( C, bcs->m_sgsObject );
}
inline void BTCS_Release( SGS_CTX, btCollisionShape* shape )
{
	if( !shape ) return;
	BulletCollisionShape* bcs = (BulletCollisionShape*) shape->getUserPointer();
	sgs_ObjRelease( C, bcs->m_sgsObject );
}
inline void BTCS_GCMark( SGS_CTX, btCollisionShape* shape )
{
	if( !shape ) return;
	BulletCollisionShape* bcs = (BulletCollisionShape*) shape->getUserPointer();
	sgs_ObjGCMark( C, bcs->m_sgsObject );
}


#define m_convexShape convexShape()
struct BulletConvexShape : BulletCollisionShape
{
	SGS_OBJECT_INHERIT( BulletCollisionShape ) SGS_N_O_EXPORT;
	
	btConvexShape*& convexShape(){ return *(btConvexShape**)&m_colShape; }
	
	static bool Match( sgs_ObjInterface* iface );
	
	//
	// METHODS
	//
	// > localGetSupportingVertex
	SGS_METHOD btVector3 localGetSupportingVertex( const btVector3& v ){ return m_convexShape->localGetSupportingVertex( v ); }
	// > localGetSupportingVertexWithoutMargin
	SGS_METHOD btVector3 localGetSupportingVertexWithoutMargin( const btVector3& v ){ return m_convexShape->localGetSupportingVertexWithoutMargin( v ); }
	// > localGetSupportVertexWithoutMarginNonVirtual
	// > getMarginNonVirtual
	SGS_METHOD float getMarginNonVirtual(){ return m_convexShape->getMarginNonVirtual(); }
	// > getAABBNonVirtual
	// > project
	// > batchedUnitVectorGetSupportingVertexWithoutMargin
	// > getAABBSlow
	// > getPreferredPenetrationDirection
	SGS_METHOD btVector3 getPreferredPenetrationDirection( int i ){ btVector3 d(0,0,0);
		if( i >= 0 && i < m_convexShape->getNumPreferredPenetrationDirections() ){ m_convexShape->getPreferredPenetrationDirection( i, d ); } return d; }
	
	//
	// PROPERTIES
	//
	// > numPreferredPenetrationDirections
	int _get_numPreferredPenetrationDirections(){ return m_convexShape->getNumPreferredPenetrationDirections(); }
	SGS_PROPERTY_FUNC( READ _get_numPreferredPenetrationDirections ) SGS_ALIAS( int numPreferredPenetrationDirections );
};


template<> struct sgs_GetVar<BulletConvexShapePointer> { BulletConvexShapePointer operator () ( SGS_CTX, sgs_StkIdx item ){
	if( sgs_ItemType( C, item ) == SGS_VT_OBJECT && BulletConvexShape::Match( sgs_GetObjectIface( C, item ) ) )
		return ((BulletConvexShape*)sgs_GetObjectData( C, item ))->m_convexShape; else return NULL; }};


#define m_convexIntShape convexIntShape()
struct BulletConvexInternalShape : BulletConvexShape
{
	SGS_OBJECT_INHERIT( BulletConvexShape ) SGS_N_O_EXPORT;
	
	btConvexInternalShape*& convexIntShape(){ return *(btConvexInternalShape**)&m_colShape; }
	
	//
	// METHODS
	//
	// > setSafeMargin
	
	//
	// PROPERTIES
	//
	// > implicitShapeDimensions
	btVector3 _get_implicitShapeDimensions(){ return m_convexIntShape->getImplicitShapeDimensions(); }
	void _set_implicitShapeDimensions( const btVector3& v ){ m_convexIntShape->setImplicitShapeDimensions( v ); }
	SGS_PROPERTY_FUNC( READ _get_implicitShapeDimensions WRITE _set_implicitShapeDimensions ) SGS_ALIAS( btVector3 implicitShapeDimensions );
	// > READONLY localScalingNV
	btVector3 _get_localScalingNV(){ return m_convexIntShape->getLocalScalingNV(); }
	SGS_PROPERTY_FUNC( READ _get_localScalingNV ) SGS_ALIAS( btVector3 localScalingNV );
	// > READONLY marginNV
	float _get_marginNV(){ return m_convexIntShape->getMarginNV(); }
	SGS_PROPERTY_FUNC( READ _get_marginNV ) SGS_ALIAS( float marginNV );
};


#define m_sphereShape sphereShape()
struct BulletSphereShape : BulletConvexInternalShape
{
	SGS_OBJECT_INHERIT( BulletConvexInternalShape );
	
	btSphereShape*& sphereShape(){ return *(btSphereShape**)&m_colShape; }
	
	BulletSphereShape( float radius ){ m_sphereShape = new btSphereShape( radius ); m_sphereShape->setUserPointer( this ); }
	
	//
	// PROPERTIES
	//
	// > radius
	float _get_radius(){ return m_sphereShape->getImplicitShapeDimensions().getX(); }
	void _set_radius( float r ){ m_sphereShape->setUnscaledRadius( r ); }
	SGS_PROPERTY_FUNC( READ _get_radius WRITE _set_radius ) SGS_ALIAS( float radius );
	// > READONLY scaledRadius
	float _get_scaledRadius(){ return m_sphereShape->getRadius(); }
	SGS_PROPERTY_FUNC( READ _get_scaledRadius ) SGS_ALIAS( float scaledRadius );
};


#define m_capsuleShape capsuleShape()
struct BulletCapsuleShapeY : BulletConvexInternalShape
{
	SGS_OBJECT_INHERIT( BulletConvexInternalShape );
	
	btCapsuleShape*& capsuleShape(){ return *(btCapsuleShape**)&m_colShape; }
	
	BulletCapsuleShapeY(){}
	BulletCapsuleShapeY( float radius, float height ){ m_capsuleShape = new btCapsuleShape( radius, height ); m_capsuleShape->setUserPointer( this ); }
	
	//
	// PROPERTIES
	//
	// > READONLY upAxis
	btVector3 _get_upAxis(){ switch( m_capsuleShape->getUpAxis() ){ case 0: return btVector3(1,0,0); case 1: return btVector3(0,1,0); case 2: return btVector3(0,0,1); default: return btVector3(0,0,0); } }
	SGS_PROPERTY_FUNC( READ _get_upAxis ) SGS_ALIAS( btVector3 upAxis );
	// > READONLY upAxisIndex
	int _get_upAxisIndex(){ return m_capsuleShape->getUpAxis(); }
	SGS_PROPERTY_FUNC( READ _get_upAxisIndex ) SGS_ALIAS( int upAxisIndex );
	// > READONLY radius
	float _get_radius(){ return m_capsuleShape->getRadius(); }
	SGS_PROPERTY_FUNC( READ _get_radius ) SGS_ALIAS( float radius );
	// > READONLY height
	float _get_height(){ return m_capsuleShape->getHalfHeight() * 2; }
	SGS_PROPERTY_FUNC( READ _get_height ) SGS_ALIAS( float height );
	// > READONLY halfHeight
	float _get_halfHeight(){ return m_capsuleShape->getHalfHeight(); }
	SGS_PROPERTY_FUNC( READ _get_halfHeight ) SGS_ALIAS( float halfHeight );
};
struct BulletCapsuleShapeX : BulletCapsuleShapeY
{
	SGS_OBJECT_INHERIT( BulletCapsuleShapeY );
	
	BulletCapsuleShapeX( float radius, float height ){ m_capsuleShape = new btCapsuleShapeX( radius, height ); m_capsuleShape->setUserPointer( this ); }
};
struct BulletCapsuleShapeZ : BulletCapsuleShapeY
{
	SGS_OBJECT_INHERIT( BulletCapsuleShapeY );
	
	BulletCapsuleShapeZ( float radius, float height ){ m_capsuleShape = new btCapsuleShapeZ( radius, height ); m_capsuleShape->setUserPointer( this ); }
};


#define m_polyConvexShape polyConvexShape()
struct BulletPolyhedralConvexShape : BulletConvexInternalShape
{
	SGS_OBJECT_INHERIT( BulletConvexInternalShape ) SGS_N_O_EXPORT;
	
	btPolyhedralConvexShape*& polyConvexShape(){ return *(btPolyhedralConvexShape**)&m_colShape; }
	
	//
	// METHODS
	//
	// > getEdge
	// > getVertex
	// > getPlane
	// > isInside
	
	//
	// PROPERTIES
	//
	// > numVertices
	int _get_numVertices(){ return m_polyConvexShape->getNumVertices(); }
	SGS_PROPERTY_FUNC( READ _get_numVertices ) SGS_ALIAS( numVertices );
	// > numEdges
	int _get_numEdges(){ return m_polyConvexShape->getNumEdges(); }
	SGS_PROPERTY_FUNC( READ _get_numEdges ) SGS_ALIAS( numEdges );
	// > numPlanes
	int _get_numPlanes(){ return m_polyConvexShape->getNumPlanes(); }
	SGS_PROPERTY_FUNC( READ _get_numPlanes ) SGS_ALIAS( numPlanes );
};


#define m_polyConvexAABBCachingShape polyConvexAABBCachingShape()
struct BulletPolyhedralConvexAabbCachingShape : BulletPolyhedralConvexShape
{
	SGS_OBJECT_INHERIT( BulletPolyhedralConvexShape ) SGS_N_O_EXPORT;
	
	btPolyhedralConvexAabbCachingShape*& polyConvexAABBCachingShape(){ return *(btPolyhedralConvexAabbCachingShape**)&m_colShape; }
	
	//
	// METHODS
	//
	// > getNonVirtualAABB
	// > recalcLocalAABB
	SGS_METHOD void recalcLocalAABB(){ m_polyConvexAABBCachingShape->recalcLocalAabb(); }
};


#define m_convexHullShape convexHullShape()
struct BulletConvexHullShape : BulletPolyhedralConvexAabbCachingShape
{
	SGS_OBJECT_INHERIT( BulletPolyhedralConvexAabbCachingShape );
	
	btConvexHullShape*& convexHullShape(){ return *(btConvexHullShape**)&m_colShape; }
	
	BulletConvexHullShape(){ m_convexHullShape = new btConvexHullShape(); m_convexHullShape->setUserPointer( this ); }
	
	//
	// METHODS
	//
	// - addPoint
	SGS_METHOD void addPoint( const btVector3& pt, bool recalcaabb ){ m_convexHullShape->addPoint( pt, recalcaabb ); }
	// - getUnscaledPoint
	SGS_METHOD SGS_MULTRET getUnscaledPoint( int i )
	{
		if( i < 0 || i >= m_convexHullShape->getNumPoints() )
			return sgs_Msg( C, SGS_WARNING, "index out of bounds" );
		sgs_PushVar( C, m_convexHullShape->getUnscaledPoints()[ i ] );
		return 1;
	}
	// - getScaledPoint
	SGS_METHOD SGS_MULTRET getScaledPoint( int i )
	{
		if( i < 0 || i >= m_convexHullShape->getNumPoints() )
			return sgs_Msg( C, SGS_WARNING, "index out of bounds" );
		sgs_PushVar( C, m_convexHullShape->getScaledPoint( i ) );
		return 1;
	}
	
	//
	// PROPERTIES
	//
	// > numPoints
	int _get_numPoints(){ return m_convexHullShape->getNumPoints(); }
	SGS_PROPERTY_FUNC( READ _get_numPoints ) SGS_ALIAS( numPoints );
	// > unscaledPoints
	// > scaledPoints
};


#define m_boxShape boxShape()
struct BulletBoxShape : BulletPolyhedralConvexShape
{
	SGS_OBJECT_INHERIT( BulletPolyhedralConvexShape );
	
	btBoxShape*& boxShape(){ return *(btBoxShape**)&m_colShape; }
	
	BulletBoxShape( const btVector3& halfExtents ){ m_boxShape = new btBoxShape( halfExtents ); m_boxShape->setUserPointer( this ); }
	
	//
	// PROPERTIES
	//
	// > READONLY halfExtentsWithMargin
	// > READONLY halfExtentsWithoutMargin
};


#define m_concaveShape concaveShape()
struct BulletConcaveShape : BulletCollisionShape
{
	SGS_OBJECT_INHERIT( BulletCollisionShape ) SGS_N_O_EXPORT;
	
	btConcaveShape*& concaveShape(){ return *(btConcaveShape**)&m_colShape; }
	
	//
	// METHODS
	//
	// > processAllTriangles
};


#define m_staticPlaneShape staticPlaneShape()
struct BulletStaticPlaneShape : BulletConcaveShape
{
	SGS_OBJECT_INHERIT( BulletConcaveShape );
	
	btStaticPlaneShape*& staticPlaneShape(){ return *(btStaticPlaneShape**)&m_colShape; }
	
	BulletStaticPlaneShape( const btVector3& n, float d ){ m_staticPlaneShape = new btStaticPlaneShape( n, d ); m_staticPlaneShape->setUserPointer( this ); }
	
	//
	// PROPERTIES
	//
	// > READONLY planeNormal
	btVector3 _get_planeNormal(){ return m_staticPlaneShape->getPlaneNormal(); }
	SGS_PROPERTY_FUNC( READ _get_planeNormal ) SGS_ALIAS( btVector3 planeNormal );
	// > READONLY planeConstant
	float _get_planeConstant(){ return m_staticPlaneShape->getPlaneConstant(); }
	SGS_PROPERTY_FUNC( READ _get_planeConstant ) SGS_ALIAS( float planeConstant );
};


#define m_triMeshShape triMeshShape()
struct BulletTriangleMeshShape : BulletConcaveShape
{
	virtual ~BulletTriangleMeshShape(){ if( meshInterface.obj ) sgs_ObjRelease( C, meshInterface.obj ); }
	SGS_OBJECT_INHERIT( BulletConcaveShape ) SGS_N_O_EXPORT;
	SGS_GCREF( meshInterface );
	
	btTriangleMeshShape*& triMeshShape(){ return *(btTriangleMeshShape**)&m_colShape; }
	
	//
	// METHODS
	//
	// > recalcLocalAABB
	SGS_METHOD void recalcLocalAABB(){ m_triMeshShape->recalcLocalAabb(); }
	
	//
	// PROPERTIES
	//
	// > READONLY meshInterface
	SGS_PROPERTY_FUNC( READ ) BulletStridingMeshInterfaceHandle meshInterface;
	// > READONLY localAABBMin
	// > READONLY localAABBMax
};


#define m_bvhtmShape bvhtmShape()
struct BulletBVHTriangleMeshShape : BulletTriangleMeshShape
{
	SGS_OBJECT_INHERIT( BulletTriangleMeshShape );
	
	btBvhTriangleMeshShape*& bvhtmShape(){ return *(btBvhTriangleMeshShape**)&m_colShape; }
	
	BulletBVHTriangleMeshShape( BulletStridingMeshInterfaceHandle mi, bool use_qbbc, bool build_bvh )
	{
		meshInterface = mi;
		sgs_ObjAcquire( C, meshInterface.obj );
		m_bvhtmShape = new btBvhTriangleMeshShape( ((BulletStridingMeshInterface*)mi.obj->data)->m_smi, use_qbbc, build_bvh );
		m_bvhtmShape->setUserPointer( this );
	}
	
	//
	// METHODS
	//
	// > performRaycast
	// > performConvexCast
	// > refitTree
	// > partialRefitTree
	// > buildOptimizedBVH
	SGS_METHOD void buildOptimizedBVH(){ return m_bvhtmShape->buildOptimizedBvh(); }
	// > serializeSingleBVH
	// > serializeSingleBVHTriangleInfoMap
	
	//
	// PROPERTIES
	//
	// > READONLY ownsBVH
	// > optimizedBVH
	// > READONLY usesQuantizedAABBCompression
	// > triangleInfoMap
};


////////////////////////////////////////////


struct BulletRigidBodyCreationInfo : btRigidBody::btRigidBodyConstructionInfo
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		BulletRigidBodyCreationInfo* rbci = (BulletRigidBodyCreationInfo*) obj->data;
		BTCS_GCMark( C, rbci->m_collisionShape );
		return SGS_SUCCESS;
	}
	
	BulletRigidBodyCreationInfo() : btRigidBody::btRigidBodyConstructionInfo( 0, NULL, NULL ){}
	
	SGS_PROPERTY_FUNC( READ WRITE VARNAME additionalAngularDampingFactor ) SGS_ALIAS( float m_additionalAngularDampingFactor );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME additionalAngularDampingThresholdSqr ) SGS_ALIAS( float m_additionalAngularDampingThresholdSqr );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME additionalDamping ) SGS_ALIAS( bool m_additionalDamping );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME additionalDampingFactor ) SGS_ALIAS( float m_additionalDampingFactor );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME additionalLinearDampingThresholdSqr ) SGS_ALIAS( float m_additionalLinearDampingThresholdSqr );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME angularDamping ) SGS_ALIAS( float m_angularDamping );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME angularSleepingThreshold ) SGS_ALIAS( float m_angularSleepingThreshold );
	void _set_collisionShape( BulletCollisionShapePointer shape )
	{
		BTCS_Acquire( C, shape );
		BTCS_Release( C, m_collisionShape );
		m_collisionShape = shape;
	}
	SGS_PROPERTY_FUNC( READ WRITE _set_collisionShape VARNAME collisionShape ) SGS_ALIAS( BulletCollisionShapePointer m_collisionShape );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME friction ) SGS_ALIAS( float m_friction );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME linearDamping ) SGS_ALIAS( float m_linearDamping );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME linearSleepingThreshold ) SGS_ALIAS( float m_linearSleepingThreshold );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME localInertia ) SGS_ALIAS( btVector3 m_localInertia );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME mass ) SGS_ALIAS( float m_mass );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME restitution ) SGS_ALIAS( float m_restitution );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME startWorldTransform ) SGS_ALIAS( BulletTransform m_startWorldTransform );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME transform ) SGS_ALIAS( BulletTransform m_startWorldTransform );
	
	btVector3 _get_position(){ return m_startWorldTransform.getOrigin(); }
	void _set_position( const btVector3& v ){ m_startWorldTransform.setOrigin( v ); }
	SGS_PROPERTY_FUNC( READ _get_position WRITE _set_position ) SGS_ALIAS( btVector3 position );
};
SGS_DEFAULT_LITE_OBJECT_INTERFACE( BulletRigidBodyCreationInfo );


struct BulletCollisionObject
{
	struct BulletDynamicsWorld* m_world;
	btCollisionObject* m_colObj;
	
	SGS_OBJECT SGS_N_O_EXPORT;
	
	virtual ~BulletCollisionObject(){}
	
	SGS_IFUNC( GCMARK ) int gcmark_co( SGS_CTX, sgs_VarObj* obj )
	{
		BulletCollisionObject* bco = (BulletCollisionObject*) obj->data;
		bco->userData.gcmark();
		BTCS_GCMark( C, bco->m_colObj->getCollisionShape() );
		return SGS_SUCCESS;
	}
	
	static bool Match( sgs_ObjInterface* iface );
	
	//
	// METHODS
	//
	
	//
	// PROPERTIES
	//
	// > READONLY mergesSimulationIslands
	bool _get_mergesSimulationIslands(){ return m_colObj->mergesSimulationIslands(); }
	SGS_PROPERTY_FUNC( READ _get_mergesSimulationIslands ) SGS_ALIAS( bool mergesSimulationIslands );
	// > anisotropicFriction
	btVector3 _get_anisotropicFriction(){ return m_colObj->getAnisotropicFriction(); }
	void _set_anisotropicFriction( const btVector3& v ){ m_colObj->setAnisotropicFriction( v ); }
	SGS_PROPERTY_FUNC( READ _get_anisotropicFriction WRITE _set_anisotropicFriction ) SGS_ALIAS( btVector3 anisotropicFriction );
	// > READONLY hasAnisotropicFriction
	bool _get_hasAnisotropicFriction(){ return m_colObj->hasAnisotropicFriction(); }
	SGS_PROPERTY_FUNC( READ _get_hasAnisotropicFriction ) SGS_ALIAS( bool hasAnisotropicFriction );
	// > contactProcessingThreshold
	float _get_contactProcessingThreshold(){ return m_colObj->getContactProcessingThreshold(); }
	void _set_contactProcessingThreshold( float t ){ m_colObj->setContactProcessingThreshold( t ); }
	SGS_PROPERTY_FUNC( READ _get_contactProcessingThreshold WRITE _set_contactProcessingThreshold ) SGS_ALIAS( float contactProcessingThreshold );
	// > READONLY isStaticObject
	bool _get_isStaticObject(){ return m_colObj->isStaticObject(); }
	SGS_PROPERTY_FUNC( READ _get_isStaticObject ) SGS_ALIAS( bool isStaticObject );
	// > isKinematicObject
	bool _get_isKinematicObject(){ return m_colObj->isKinematicObject(); }
	void _set_isKinematicObject( bool v ){ m_colObj->setCollisionFlags( m_colObj->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT); }
	SGS_PROPERTY_FUNC( READ _get_isKinematicObject WRITE _set_isKinematicObject ) SGS_ALIAS( bool isKinematicObject );
	// > READONLY isStaticOrKinematicObject
	bool _get_isStaticOrKinematicObject(){ return m_colObj->isStaticOrKinematicObject(); }
	SGS_PROPERTY_FUNC( READ _get_isStaticOrKinematicObject ) SGS_ALIAS( bool isStaticOrKinematicObject );
	// > READONLY hasContactResponse
	bool _get_hasContactResponse(){ return m_colObj->hasContactResponse(); }
	SGS_PROPERTY_FUNC( READ _get_hasContactResponse ) SGS_ALIAS( bool hasContactResponse );
	// > collisionShape
	BulletCollisionShapePointer _get_collisionShape(){ return m_colObj->getCollisionShape(); }
	void _set_collisionShape( BulletCollisionShapePointer shape )
	{
		BTCS_Acquire( C, shape );
		BTCS_Release( C, m_colObj->getCollisionShape() );
		m_colObj->setCollisionShape( shape );
	}
	SGS_PROPERTY_FUNC( READ _get_collisionShape WRITE _set_collisionShape ) SGS_ALIAS( BulletCollisionShapePointer collisionShape );
	// > activationState
	int _get_activationState(){ return m_colObj->getActivationState(); }
	void _set_activationState( int state ){ m_colObj->setActivationState( state ); }
	SGS_PROPERTY_FUNC( READ _get_activationState WRITE _set_activationState ) SGS_ALIAS( int activationState );
	// > deactivationTime
	float _get_deactivationTime(){ return m_colObj->getDeactivationTime(); }
	void _set_deactivationTime( float f ){ m_colObj->setDeactivationTime( f ); }
	SGS_PROPERTY_FUNC( READ _get_deactivationTime WRITE _set_deactivationTime ) SGS_ALIAS( float deactivationTime );
	// > READONLY isActive
	bool _get_isActive(){ return m_colObj->isActive(); }
	SGS_PROPERTY_FUNC( READ _get_isActive ) SGS_ALIAS( bool isActive );
	// > restitution
	float _get_restitution(){ return m_colObj->getRestitution(); }
	void _set_restitution( float f ){ m_colObj->setRestitution( f ); }
	SGS_PROPERTY_FUNC( READ _get_restitution WRITE _set_restitution ) SGS_ALIAS( float restitution );
	// > friction
	float _get_friction(){ return m_colObj->getFriction(); }
	void _set_friction( float f ){ m_colObj->setFriction( f ); }
	SGS_PROPERTY_FUNC( READ _get_friction WRITE _set_friction ) SGS_ALIAS( float friction );
	// > rollingFriction
	float _get_rollingFriction(){ return m_colObj->getRollingFriction(); }
	void _set_rollingFriction( float f ){ m_colObj->setRollingFriction( f ); }
	SGS_PROPERTY_FUNC( READ _get_rollingFriction WRITE _set_rollingFriction ) SGS_ALIAS( float rollingFriction );
	// > worldTransform
	BulletTransform _get_worldTransform(){ return m_colObj->getWorldTransform(); }
	void _set_worldTransform( const BulletTransform& t ){ m_colObj->setWorldTransform( t ); }
	SGS_PROPERTY_FUNC( READ _get_worldTransform WRITE _set_worldTransform ) SGS_ALIAS( BulletTransform worldTransform );
	// > interpolationWorldTransform
	BulletTransform _get_interpolationWorldTransform(){ return m_colObj->getInterpolationWorldTransform(); }
	void _set_interpolationWorldTransform( const BulletTransform& t ){ m_colObj->setInterpolationWorldTransform( t ); }
	SGS_PROPERTY_FUNC( READ _get_interpolationWorldTransform WRITE _set_interpolationWorldTransform ) SGS_ALIAS( BulletTransform interpolationWorldTransform );
	// > interpolationLinearVelocity
	btVector3 _get_interpolationLinearVelocity(){ return m_colObj->getInterpolationLinearVelocity(); }
	void _set_interpolationLinearVelocity( const btVector3& v ){ m_colObj->setInterpolationLinearVelocity( v ); }
	SGS_PROPERTY_FUNC( READ _get_interpolationLinearVelocity WRITE _set_interpolationLinearVelocity ) SGS_ALIAS( btVector3 interpolationLinearVelocity );
	// > interpolationAngularVelocity
	btVector3 _get_interpolationAngularVelocity(){ return m_colObj->getInterpolationAngularVelocity(); }
	void _set_interpolationAngularVelocity( const btVector3& v ){ m_colObj->setInterpolationAngularVelocity( v ); }
	SGS_PROPERTY_FUNC( READ _get_interpolationAngularVelocity WRITE _set_interpolationAngularVelocity ) SGS_ALIAS( btVector3 interpolationAngularVelocity );
	// > islandTag
	int _get_islandTag(){ return m_colObj->getIslandTag(); }
	void _set_islandTag( int tag ){ m_colObj->setIslandTag( tag ); }
	SGS_PROPERTY_FUNC( READ _get_islandTag WRITE _set_islandTag ) SGS_ALIAS( int islandTag );
	// > companionID
	int _get_companionID(){ return m_colObj->getCompanionId(); }
	void _set_companionID( int id ){ m_colObj->setCompanionId( id ); }
	SGS_PROPERTY_FUNC( READ _get_companionID WRITE _set_companionID ) SGS_ALIAS( int companionID );
	SGS_PROPERTY_FUNC( READ _get_companionID WRITE _set_companionID ) SGS_ALIAS( int companionId );
	// > hitFraction
	float _get_hitFraction(){ return m_colObj->getHitFraction(); }
	void _set_hitFraction( float f ){ m_colObj->setHitFraction( f ); }
	SGS_PROPERTY_FUNC( READ _get_hitFraction WRITE _set_hitFraction ) SGS_ALIAS( float hitFraction );
	// > collisionFlags
	int _get_collisionFlags(){ return m_colObj->getCollisionFlags(); }
	void _set_collisionFlags( int flags ){ m_colObj->setCollisionFlags( flags ); }
	SGS_PROPERTY_FUNC( READ _get_collisionFlags WRITE _set_collisionFlags ) SGS_ALIAS( int collisionFlags );
	// > CCDSweptSphereRadius
	float _get_CCDSweptSphereRadius(){ return m_colObj->getCcdSweptSphereRadius(); }
	void _set_CCDSweptSphereRadius( float t ){ m_colObj->setCcdSweptSphereRadius( t ); }
	SGS_PROPERTY_FUNC( READ _get_CCDSweptSphereRadius WRITE _set_CCDSweptSphereRadius ) SGS_ALIAS( float CCDSweptSphereRadius );
	SGS_PROPERTY_FUNC( READ _get_CCDSweptSphereRadius WRITE _set_CCDSweptSphereRadius ) SGS_ALIAS( float ccdSweptSphereRadius );
	// > CCDMotionThreshold
	float _get_CCDMotionThreshold(){ return m_colObj->getCcdMotionThreshold(); }
	void _set_CCDMotionThreshold( float t ){ m_colObj->setCcdMotionThreshold( t ); }
	SGS_PROPERTY_FUNC( READ _get_CCDMotionThreshold WRITE _set_CCDMotionThreshold ) SGS_ALIAS( float CCDMotionThreshold );
	SGS_PROPERTY_FUNC( READ _get_CCDMotionThreshold WRITE _set_CCDMotionThreshold ) SGS_ALIAS( float ccdMotionThreshold );
	// > READONLY CCDSquareMotionThreshold
	int _get_CCDSquareMotionThreshold(){ return m_colObj->getCcdSquareMotionThreshold(); }
	SGS_PROPERTY_FUNC( READ _get_CCDSquareMotionThreshold ) SGS_ALIAS( int CCDSquareMotionThreshold );
	SGS_PROPERTY_FUNC( READ _get_CCDSquareMotionThreshold ) SGS_ALIAS( int ccdSquareMotionThreshold );
	// > userData
	SGS_PROPERTY sgsVariable userData;
};


template<> inline void sgs_PushVar( SGS_CTX, BulletCollisionObjectPointer bcop ){
	if( !bcop ) sgs_PushNull( C ); else { BulletCollisionObject* bco = (BulletCollisionObject*) bcop->getUserPointer();
		sgs_PushObjectPtr( C, bco->m_sgsObject ); }}
template<> struct sgs_GetVar<BulletCollisionObjectPointer> { BulletCollisionObjectPointer operator () ( SGS_CTX, sgs_StkIdx item ){
	if( sgs_ItemType( C, item ) == SGS_VT_OBJECT && BulletCollisionObject::Match( sgs_GetObjectIface( C, item ) ) )
		return ((BulletCollisionObject*)sgs_GetObjectData( C, item ))->m_colObj; else return NULL; }};

inline void BTCO_Acquire( SGS_CTX, btCollisionObject* colobj )
{
	if( !colobj ) return;
	BulletCollisionObject* bco = (BulletCollisionObject*) colobj->getUserPointer();
	sgs_ObjAcquire( C, bco->m_sgsObject );
}
inline void BTCO_Release( SGS_CTX, btCollisionObject* colobj )
{
	if( !colobj ) return;
	BulletCollisionObject* bco = (BulletCollisionObject*) colobj->getUserPointer();
	sgs_ObjRelease( C, bco->m_sgsObject );
}
inline void BTCO_GCMark( SGS_CTX, btCollisionObject* colobj )
{
	if( !colobj ) return;
	BulletCollisionObject* bco = (BulletCollisionObject*) colobj->getUserPointer();
	sgs_ObjGCMark( C, bco->m_sgsObject );
}


#define m_body rigidBody()
struct BulletRigidBody : BulletCollisionObject
{
	SGS_OBJECT_INHERIT( BulletCollisionObject );
	
	btRigidBody*& rigidBody(){ return *(btRigidBody**)&m_colObj; }
	
	BulletRigidBody( BulletRigidBodyCreationInfo* info );
	~BulletRigidBody();
	
	//
	// METHODS
	//
	// > proceedToTransform
	SGS_METHOD void proceedToTransform( const BulletTransform& tf ){ m_body->proceedToTransform( tf ); }
	// > predictIntegratedTransform
	SGS_METHOD BulletTransform predictIntegratedTransform( float step ){ btTransform tf; m_body->predictIntegratedTransform( step, tf ); return tf; }
	// > saveKinematicState
	SGS_METHOD void saveKinematicState( float timeStep ){ m_body->saveKinematicState( timeStep ); }
	// > setDamping
	SGS_METHOD void setDamping( float linearDamping, float angularDamping ){ m_body->setDamping( linearDamping, angularDamping ); }
	// > setSleepingThresholds
	SGS_METHOD void setSleepingThresholds( float linearST, float angularST ){ m_body->setSleepingThresholds( linearST, angularST ); }
	// > applyDamping
	SGS_METHOD void applyDamping( float timeStep ){ m_body->applyDamping( timeStep ); }
	// > setMassProps
	SGS_METHOD void setMassProps( float mass, const btVector3& inertia ){ m_body->setMassProps( mass, inertia ); }
	// > integrateVelocities
	SGS_METHOD void integrateVelocities( float timeStep ){ m_body->integrateVelocities( timeStep ); }
	// > setCenterOfMassTransform
	SGS_METHOD void setCenterOfMassTransform( const BulletTransform& tf ){ m_body->setCenterOfMassTransform( tf ); }
	// > applyCentralForce
	SGS_METHOD void applyCentralForce( const btVector3& v ){ m_body->applyCentralForce( v ); }
	// > applyTorque
	SGS_METHOD void applyTorque( const btVector3& v ){ m_body->applyTorque( v ); }
	// > applyForce
	SGS_METHOD void applyForce( const btVector3& v, const btVector3& pos ){ m_body->applyForce( v, pos ); }
	// > applyCentralImpulse
	SGS_METHOD void applyCentralImpulse( const btVector3& v ){ m_body->applyCentralImpulse( v ); }
	// > applyTorqueImpulse
	SGS_METHOD void applyTorqueImpulse( const btVector3& v ){ m_body->applyTorqueImpulse( v ); }
	// > applyImpulse
	SGS_METHOD void applyImpulse( const btVector3& v, const btVector3& pos ){ m_body->applyImpulse( v, pos ); }
	// > clearForces
	SGS_METHOD void clearForces(){ m_body->clearForces(); }
	// > updateInertiaTensor
	SGS_METHOD void updateInertiaTensor(){ m_body->updateInertiaTensor(); }
	// > getVelocityInLocalPoint
	SGS_METHOD btVector3 getVelocityInLocalPoint( const btVector3& v ){ return m_body->getVelocityInLocalPoint( v ); }
	// > translate
	SGS_METHOD void translate( const btVector3& v ){ m_body->translate( v ); }
	// > computeImpulseDenominator
	SGS_METHOD float computeImpulseDenominator( const btVector3& pos, const btVector3& normal ){ return m_body->computeImpulseDenominator( pos, normal ); }
	// > computeAngularImpulseDenominator
	SGS_METHOD float computeAngularImpulseDenominator( const btVector3& axis ){ return m_body->computeAngularImpulseDenominator( axis ); }
	// > updateDeactivation
	SGS_METHOD void updateDeactivation( float timeStep ){ m_body->updateDeactivation( timeStep ); }
	// > checkCollideWith
	// > addConstraintRef
	// > removeConstraintRef
	// > getConstraintRef
	// > computeGyroscopicForce
	SGS_METHOD btVector3 computeGyroscopicForce( float maxGyroscopicForce ){ return m_body->computeGyroscopicForce( maxGyroscopicForce ); }
	// > calculateSerializeBufferSize
	SGS_METHOD int calculateSerializeBufferSize(){ return m_body->calculateSerializeBufferSize(); }
	// > forceActivationState
	SGS_METHOD void forceActivationState( int state ){ return m_body->forceActivationState( state ); }
	// > activate
	SGS_METHOD void activate( bool force ){ return m_body->activate( force ); }
	
	//
	// PROPERTIES
	//
	// > gravity
	btVector3 _get_gravity(){ return m_body->getGravity(); }
	void _set_gravity( const btVector3& v ){ m_body->setGravity( v ); }
	SGS_PROPERTY_FUNC( READ _get_gravity WRITE _set_gravity ) SGS_ALIAS( btVector3 gravity );
	// > linearDamping
	float _get_linearDamping(){ return m_body->getLinearDamping(); }
	void _set_linearDamping( float f ){ m_body->setDamping( f, m_body->getAngularDamping() ); }
	SGS_PROPERTY_FUNC( READ _get_linearDamping WRITE _set_linearDamping ) SGS_ALIAS( float linearDamping );
	// > angularDamping
	float _get_angularDamping(){ return m_body->getAngularDamping(); }
	void _set_angularDamping( float f ){ m_body->setDamping( m_body->getLinearDamping(), f ); }
	SGS_PROPERTY_FUNC( READ _get_angularDamping WRITE _set_angularDamping ) SGS_ALIAS( float angularDamping );
	// > linearSleepingThreshold
	float _get_linearSleepingThreshold(){ return m_body->getLinearSleepingThreshold(); }
	void _set_linearSleepingThreshold( float f ){ m_body->setSleepingThresholds( f, m_body->getAngularSleepingThreshold() ); }
	SGS_PROPERTY_FUNC( READ _get_linearSleepingThreshold WRITE _set_linearSleepingThreshold ) SGS_ALIAS( float linearSleepingThreshold );
	// > angularSleepingThreshold
	float _get_angularSleepingThreshold(){ return m_body->getAngularSleepingThreshold(); }
	void _set_angularSleepingThreshold( float f ){ m_body->setSleepingThresholds( m_body->getLinearSleepingThreshold(), f ); }
	SGS_PROPERTY_FUNC( READ _get_angularSleepingThreshold WRITE _set_angularSleepingThreshold ) SGS_ALIAS( float angularSleepingThreshold );
	// > linearFactor
	btVector3 _get_linearFactor(){ return m_body->getLinearFactor(); }
	void _set_linearFactor( const btVector3& v ){ m_body->setLinearFactor( v ); }
	SGS_PROPERTY_FUNC( READ _get_linearFactor WRITE _set_linearFactor ) SGS_ALIAS( btVector3 linearFactor );
	// > angularFactor
	btVector3 _get_angularFactor(){ return m_body->getAngularFactor(); }
	void _set_angularFactor( const btVector3& v ){ m_body->setAngularFactor( v ); }
	SGS_PROPERTY_FUNC( READ _get_angularFactor WRITE _set_angularFactor ) SGS_ALIAS( btVector3 angularFactor );
	// > READONLY invMass
	float _get_invMass(){ return m_body->getInvMass(); }
	SGS_PROPERTY_FUNC( READ _get_invMass ) SGS_ALIAS( float invMass );
	// > READONLY invInertiaTensorWorld
	btMatrix3x3 _get_invInertiaTensorWorld(){ return m_body->getInvInertiaTensorWorld(); }
	SGS_PROPERTY_FUNC( READ _get_invInertiaTensorWorld ) SGS_ALIAS( btMatrix3x3 invInertiaTensorWorld );
	// > READONLY totalForce
	btVector3 _get_totalForce(){ return m_body->getTotalForce(); }
	SGS_PROPERTY_FUNC( READ _get_totalForce ) SGS_ALIAS( btVector3 totalForce );
	// > READONLY totalTorque
	btVector3 _get_totalTorque(){ return m_body->getTotalTorque(); }
	SGS_PROPERTY_FUNC( READ _get_totalTorque ) SGS_ALIAS( btVector3 totalTorque );
	// > invInertiaDiagLocal
	btVector3 _get_invInertiaDiagLocal(){ return m_body->getInvInertiaDiagLocal(); }
	void _set_invInertiaDiagLocal( const btVector3& v ){ m_body->setInvInertiaDiagLocal( v ); }
	SGS_PROPERTY_FUNC( READ _get_invInertiaDiagLocal WRITE _set_invInertiaDiagLocal ) SGS_ALIAS( btVector3 invInertiaDiagLocal );
	// > position
	btVector3 _get_position(){ return m_body->getCenterOfMassPosition(); }
	void _set_position( const btVector3& v )
	{
		m_body->getWorldTransform().setOrigin( v ); m_body->setWorldTransform( m_body->getWorldTransform() );
		if( m_body->isKinematicObject() )
			m_body->getMotionState()->setWorldTransform( m_body->getWorldTransform() );
	}
	SGS_PROPERTY_FUNC( READ _get_position WRITE _set_position ) SGS_ALIAS( btVector3 position );
	// > orientation
	btQuaternion _get_orientation(){ return m_body->getOrientation(); }
	void _set_orientation( const btQuaternion& q )
	{
		m_body->getWorldTransform().setRotation( q ); m_body->setWorldTransform( m_body->getWorldTransform() );
		if( m_body->isKinematicObject() )
			m_body->getMotionState()->setWorldTransform( m_body->getWorldTransform() );
	}
	SGS_PROPERTY_FUNC( READ _get_orientation WRITE _set_orientation ) SGS_ALIAS( btQuaternion orientation );
	// > transform
	SGS_PROPERTY_FUNC( READ _get_worldTransform WRITE _set_worldTransform ) SGS_ALIAS( BulletTransform transform );
	// > linearVelocity
	btVector3 _get_linearVelocity(){ return m_body->getLinearVelocity(); }
	void _set_linearVelocity( const btVector3& v ){ m_body->setLinearVelocity( v ); }
	SGS_PROPERTY_FUNC( READ _get_linearVelocity WRITE _set_linearVelocity ) SGS_ALIAS( btVector3 linearVelocity );
	// > angularVelocity
	btVector3 _get_angularVelocity(){ return m_body->getAngularVelocity(); }
	void _set_angularVelocity( const btVector3& v ){ m_body->setAngularVelocity( v ); }
	SGS_PROPERTY_FUNC( READ _get_angularVelocity WRITE _set_angularVelocity ) SGS_ALIAS( btVector3 angularVelocity );
	// > READONLY AABB
	BulletAABB3 _get_AABB(){ BulletAABB3 aabb; m_body->getAabb( aabb.v_min, aabb.v_max ); return aabb; }
	SGS_PROPERTY_FUNC( READ _get_AABB ) SGS_ALIAS( BulletAABB3 AABB );
	// > READONLY wantsSleeping
	bool _get_wantsSleeping(){ return m_body->wantsSleeping(); }
	SGS_PROPERTY_FUNC( READ _get_wantsSleeping ) SGS_ALIAS( bool wantsSleeping );
	// > READONLY isInWorld
	bool _get_isInWorld(){ return m_body->isInWorld(); }
	SGS_PROPERTY_FUNC( READ _get_isInWorld ) SGS_ALIAS( bool isInWorld );
	// > READONLY numConstraintRefs
	int _get_numConstraintRefs(){ return m_body->getNumConstraintRefs(); }
	SGS_PROPERTY_FUNC( READ _get_numConstraintRefs ) SGS_ALIAS( int numConstraintRefs );
	// > flags
	int _get_flags(){ return m_body->getFlags(); }
	void _set_flags( int flags ){ m_body->setFlags( flags ); }
	SGS_PROPERTY_FUNC( READ _get_flags WRITE _set_flags ) SGS_ALIAS( int flags );
};


#define m_ghobj ghostObject()
struct BulletGhostObject : BulletCollisionObject
{
	SGS_OBJECT_INHERIT( BulletCollisionObject );
	
	btGhostObject*& ghostObject(){ return *(btGhostObject**)&m_colObj; }
	
	BulletGhostObject();
	~BulletGhostObject();
	
	//
	// METHODS
	//
	// > convexSweepTest
	// > rayTest
//	SGS_METHOD void rayTest( const btVector3& from, const btVector3& to, sgsVariable callback );
	// > getOverlappingObject
	// > getOverlappingPairs
	
	//
	// PROPERTIES
	//
	// > READONLY numOverlappingObjects
	int _get_numOverlappingObjects(){ return m_ghobj->getNumOverlappingObjects(); }
	SGS_PROPERTY_FUNC( READ _get_numOverlappingObjects ) SGS_ALIAS( int numOverlappingObjects );
};


struct BulletDynamicsWorld
{
	SGS_OBJECT;
	
	BulletDynamicsWorld();
	~BulletDynamicsWorld();
	
	SGS_GCREF( userData );
	
	//
	// METHODS
	//
	// > stepSimulation
	SGS_METHOD int stepSimulation( float timeStep, int maxSubSteps, float fixedTimeStep )
	{
		int ssz = sgs_StackSize( C );
		if( ssz < 2 ) maxSubSteps = 1;
		if( ssz < 3 ) fixedTimeStep = 1.0f / 60.0f;
		return m_world->stepSimulation( timeStep, maxSubSteps, fixedTimeStep );
	}
	// > debugDrawWorld
	SGS_METHOD void debugDrawWorld(){ m_world->debugDrawWorld(); }
	// > addConstraint
	// > removeConstraint
	// > addAction
	// > removeAction
	// > synchronizeMotionStates
	SGS_METHOD void synchronizeMotionStates(){ m_world->synchronizeMotionStates(); }
	// > addRigidBody
	SGS_METHOD void addRigidBody( BulletRigidBodyHandle rbh, int group, int mask );
	// > removeRigidBody
	SGS_METHOD void removeRigidBody( BulletRigidBodyHandle rbh );
	// > getConstraint
	// > clearForces
	SGS_METHOD void clearForces(){ m_world->clearForces(); }
	// > addVehicle
	// > removeVehicle
	// > addCharacter
	// > removeCharacter
	// > updateSingleAABB
	SGS_METHOD void updateSingleAABB( sgsVariable colObj );
	// > updateAABBs
	SGS_METHOD void updateAABBs(){ m_world->updateAabbs(); }
	// > computeOverlappingPairs
	SGS_METHOD void computeOverlappingPairs(){ m_world->computeOverlappingPairs(); }
	// > rayTest
	SGS_METHOD SGS_MULTRET rayTestClosest( const btVector3& from, const btVector3& to, int group, int mask );
	SGS_METHOD sgsVariable rayTestAll( const btVector3& from, const btVector3& to, int group, int mask );
	SGS_METHOD void rayTestCustom( const btVector3& from, const btVector3& to, int group, int mask, sgsVariable callback );
	// > convexSweepTest
	SGS_METHOD SGS_MULTRET convexSweepTestClosest( BulletConvexShapePointer bcsp, const BulletTransform& from, const BulletTransform& to, int group, int mask, float alcp );
	SGS_METHOD void convexSweepTestCustom( BulletConvexShapePointer bcsp, const BulletTransform& from, const BulletTransform& to, int group, int mask, sgsVariable callback, float alcp );
	// > contactTest
	// > contactPairTest
	// > addCollisionObject
	SGS_METHOD void addCollisionObject( sgsVariable colObj, int group, int mask );
	// > getCollisionObjectArray
	// > removeCollisionObject
	SGS_METHOD void removeCollisionObject( sgsVariable colObj );
	// > performDiscreteCollisionDetection
	SGS_METHOD void performDiscreteCollisionDetection(){ m_world->performDiscreteCollisionDetection(); }
	
	//
	// PROPERTIES
	//
	// > gravity
	btVector3 _get_gravity(){ return m_world->getGravity(); }
	void _set_gravity( const btVector3& v ){ m_world->setGravity( v ); }
	SGS_PROPERTY_FUNC( READ _get_gravity WRITE _set_gravity ) SGS_ALIAS( btVector3 gravity );
	// > READONLY numConstraints
	int _get_numConstraints(){ return m_world->getNumConstraints(); }
	SGS_PROPERTY_FUNC( READ _get_numConstraints ) SGS_ALIAS( int numConstraints );
	// > debugDrawer
	// > READONLY numCollisionObjects
	int _get_numCollisionObjects(){ return m_world->getNumCollisionObjects(); }
	SGS_PROPERTY_FUNC( READ _get_numCollisionObjects ) SGS_ALIAS( int numCollisionObjects );
	// > forceUpdateAllAABBs
	bool _get_forceUpdateAllAABBs(){ return m_world->getForceUpdateAllAabbs(); }
	void _set_forceUpdateAllAABBs( bool v ){ m_world->setForceUpdateAllAabbs( v ); }
	SGS_PROPERTY_FUNC( READ _get_forceUpdateAllAABBs WRITE _set_forceUpdateAllAABBs ) SGS_ALIAS( bool forceUpdateAllAABBs );
	SGS_PROPERTY_FUNC( READ _get_forceUpdateAllAABBs WRITE _set_forceUpdateAllAABBs ) SGS_ALIAS( bool forceUpdateAllAabbs );
	// > userData
	SGS_PROPERTY sgsVariable userData;
	
	
	btBroadphaseInterface*
		m_broadphase;
	btDefaultCollisionConfiguration*
		m_collisionConfig;
	btCollisionDispatcher*
		m_collisionDispatcher;
	btSequentialImpulseConstraintSolver*
		m_constraintSolver;
	btDiscreteDynamicsWorld*
		m_world;
};
