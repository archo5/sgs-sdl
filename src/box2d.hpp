

#include <sgs_util.h>
#include "../sgscript/ext/sgs_cppbc.h"
#include "../sgscript/ext/sgsxgmath.h"

#include <Box2D/Box2D.h>


// b2Vec2 interface
template<> inline void sgs_PushVar<b2Vec2>( SGS_CTX, const b2Vec2& v ){ sgs_CreateVec2( C, NULL, v.x, v.y ); }
template<> struct sgs_GetVar<b2Vec2> { b2Vec2 operator () ( SGS_CTX, sgs_StkIdx item ){
	b2Vec2 v; if( sgs_ParseVec2( C, item, (float*) &v, 0 ) ) return v; return b2Vec2(0,0); }};

// b2AABB interface
template<> inline void sgs_PushVar<b2AABB>( SGS_CTX, const b2AABB& bb ){ sgs_CreateAABB2( C, NULL, bb.lowerBound.x, bb.lowerBound.y, bb.upperBound.x, bb.upperBound.y ); }
template<> struct sgs_GetVar<b2AABB> { b2AABB operator () ( SGS_CTX, sgs_StkIdx item ){
	b2AABB bb = { b2Vec2_zero, b2Vec2_zero }; sgs_ParseAABB2( C, item, (float*) &bb ); return bb; }};

// b2Color interface
template<> inline void sgs_PushVar< b2Color >( SGS_CTX, const b2Color& c ){ sgs_CreateColor( C, NULL, c.r, c.g, c.b, 1 ); }

// floatarray interface
struct FloatArray
{
	XGM_VT* data;
	sgs_SizeVal count;
};
template<> struct sgs_GetVar<FloatArray> { FloatArray operator () ( SGS_CTX, sgs_StkIdx item ){
	FloatArray arr = { NULL, 0 }; sgs_ParseFloatArray( C, item, &arr.data, &arr.count ); return arr; }};


struct Box2DRotation : b2Rot
{
	SGS_OBJECT_LITE;
	
	Box2DRotation(){ SetIdentity(); }
	Box2DRotation( const b2Rot& r ) : b2Rot( r ){}
	
	//
	// PROPERTIES
	//
	// > angle
	float32 _getAngle(){ return GetAngle(); }
	void _setAngle( float32 v ){ Set( v ); }
	SGS_PROPERTY_FUNC( READ _getAngle WRITE _setAngle ) SGS_ALIAS( float32 angle );
	// > READONLY xAxis
	b2Vec2 _getXAxis(){ return GetXAxis(); }
	SGS_PROPERTY_FUNC( READ _getXAxis ) SGS_ALIAS( b2Vec2 xAxis );
	// > READONLY yAxis
	b2Vec2 _getYAxis(){ return GetYAxis(); }
	SGS_PROPERTY_FUNC( READ _getYAxis ) SGS_ALIAS( b2Vec2 yAxis );
	
	//
	// METHODS
	//
	// > SetIdentity
	SGS_METHOD SGS_ALIAS( void SetIdentity() );
};
SGS_DEFAULT_LITE_OBJECT_INTERFACE( Box2DRotation );


struct Box2DTransform : b2Transform
{
	SGS_OBJECT_LITE;
	
	Box2DTransform(){}
	Box2DTransform( const b2Transform& t ) : b2Transform( t ){}
	
	//
	// PROPERTIES
	//
	// > p, position
	SGS_PROPERTY_FUNC( READ WRITE VARNAME p ) SGS_ALIAS( b2Vec2 p );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME position ) SGS_ALIAS( b2Vec2 p );
	// > q, rotation
	Box2DRotation _getRotation(){ return q; }
	void _setRotation( const Box2DRotation& r ){ q = r; }
	SGS_PROPERTY_FUNC( READ _getRotation WRITE _setRotation ) SGS_ALIAS( Box2DRotation q );
	SGS_PROPERTY_FUNC( READ _getRotation WRITE _setRotation ) SGS_ALIAS( Box2DRotation rotation );
	// > angle
	float32 _getAngle(){ return q.GetAngle(); }
	void _setAngle( float32 a ){ q.Set( a ); }
	SGS_PROPERTY_FUNC( READ _getAngle WRITE _setAngle ) SGS_ALIAS( float32 angle );
};
SGS_DEFAULT_LITE_OBJECT_INTERFACE( Box2DTransform );


struct Box2DMassData : b2MassData
{
	SGS_OBJECT_LITE;
	
	Box2DMassData(){ mass = 0; center = b2Vec2_zero; I = 0; }
	Box2DMassData( const b2MassData& md ) : b2MassData( md ){}
	
	//
	// PROPERTIES
	//
	// > mass
	SGS_PROPERTY SGS_ALIAS( float32 mass );
	// > center
	SGS_PROPERTY SGS_ALIAS( b2Vec2 center );
	// > I
	SGS_PROPERTY SGS_ALIAS( float32 I );
};
SGS_DEFAULT_LITE_OBJECT_INTERFACE( Box2DMassData );


struct Box2DFilterData : b2Filter
{
	SGS_OBJECT_LITE;
	
	Box2DFilterData(){}
	Box2DFilterData( const b2Filter& f ) : b2Filter( f ){}
	
	//
	// PROPERTIES
	//
	// > categoryBits
	SGS_PROPERTY SGS_ALIAS( uint16 categoryBits );
	// > maskBits
	SGS_PROPERTY SGS_ALIAS( uint16 maskBits );
	// > groupIndex
	SGS_PROPERTY SGS_ALIAS( int16 groupIndex );
};
SGS_DEFAULT_LITE_OBJECT_INTERFACE( Box2DFilterData );


struct Box2DShape;
struct Box2DFixtureDef;
struct Box2DFixture;
struct Box2DBodyDef;
struct Box2DBody;
struct Box2DJoint;
struct Box2DContact;
struct Box2DDraw;
struct Box2DWorld;

typedef sgsHandle< Box2DShape > Box2DShapeHandle;
typedef sgsHandle< Box2DFixture > Box2DFixtureHandle;
typedef sgsHandle< Box2DBody > Box2DBodyHandle;
typedef sgsHandle< Box2DJoint > Box2DJointHandle;
typedef sgsHandle< Box2DContact > Box2DContactHandle;
typedef sgsHandle< Box2DDraw > Box2DDrawHandle;
typedef sgsHandle< Box2DWorld > Box2DWorldHandle;


struct Box2DShape
{
	bool IsCircleShape(){ return m_shape && m_shape->GetType() == b2Shape::e_circle; }
	b2CircleShape* CircleShape(){ return (b2CircleShape*) m_shape; }
	bool IsEdgeShape(){ return m_shape && m_shape->GetType() == b2Shape::e_edge; }
	b2EdgeShape* EdgeShape(){ return (b2EdgeShape*) m_shape; }
	bool IsPolyShape(){ return m_shape && m_shape->GetType() == b2Shape::e_polygon; }
	b2PolygonShape* PolyShape(){ return (b2PolygonShape*) m_shape; }
	bool IsChainShape(){ return m_shape && m_shape->GetType() == b2Shape::e_chain; }
	b2ChainShape* ChainShape(){ return (b2ChainShape*) m_shape; }
	
	SGS_OBJECT;
	
	Box2DShape( b2Shape::Type t );
	Box2DShape( b2Shape* sh, Box2DFixture* fx );
	~Box2DShape(){ _cleanUp(); }
	
	void _cleanUp();
	
	//
	// PROPERTIES
	//
	// --- generic ---
	// > READONLY type
	int _getType(){ if( m_shape ) return m_shape->GetType(); return -1; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	// > READONLY childCount
	int32 _getChildCount(){ if( m_shape ) return m_shape->GetChildCount(); return 0; }
	SGS_PROPERTY_FUNC( READ _getChildCount ) SGS_ALIAS( int32 childCount );
	// --- circle ---
	// > position
	const b2Vec2& _getPosition(){ if( IsCircleShape() ) return CircleShape()->m_p; return b2Vec2_zero; }
	void _setPosition( const b2Vec2& r ){ if( IsCircleShape() ) CircleShape()->m_p = r; }
	SGS_PROPERTY_FUNC( READ _getPosition WRITE _setPosition ) SGS_ALIAS( b2Vec2 position );
	// > radius (technically generic but doesn't seem to be actively used anywhere else)
	float32 _getRadius(){ if( m_shape ) return m_shape->m_radius; return 0; }
	void _setRadius( float32 r ){ if( m_shape ) m_shape->m_radius = r; }
	SGS_PROPERTY_FUNC( READ _getRadius WRITE _setRadius ) SGS_ALIAS( float32 radius );
	// --- edge ---
	// > edgeVertex1
	b2Vec2 _getEdgeVertex1(){ if( IsEdgeShape() ) return EdgeShape()->m_vertex1; return b2Vec2_zero; }
	void _setEdgeVertex1( b2Vec2 v ){ if( IsEdgeShape() ) EdgeShape()->m_vertex1 = v; }
	SGS_PROPERTY_FUNC( READ _getEdgeVertex1 WRITE _setEdgeVertex1 ) SGS_ALIAS( b2Vec2 edgeVertex1 );
	// > edgeVertex2
	b2Vec2 _getEdgeVertex2(){ if( IsEdgeShape() ) return EdgeShape()->m_vertex2; return b2Vec2_zero; }
	void _setEdgeVertex2( b2Vec2 v ){ if( IsEdgeShape() ) EdgeShape()->m_vertex2 = v; }
	SGS_PROPERTY_FUNC( READ _getEdgeVertex2 WRITE _setEdgeVertex2 ) SGS_ALIAS( b2Vec2 edgeVertex2 );
	// > edgeVertex0
	b2Vec2 _getEdgeVertex0(){ if( IsEdgeShape() ) return EdgeShape()->m_vertex0; return b2Vec2_zero; }
	void _setEdgeVertex0( b2Vec2 v ){ if( IsEdgeShape() ) EdgeShape()->m_vertex0 = v; }
	SGS_PROPERTY_FUNC( READ _getEdgeVertex0 WRITE _setEdgeVertex0 ) SGS_ALIAS( b2Vec2 edgeVertex0 );
	// > edgeVertex3
	b2Vec2 _getEdgeVertex3(){ if( IsEdgeShape() ) return EdgeShape()->m_vertex3; return b2Vec2_zero; }
	void _setEdgeVertex3( b2Vec2 v ){ if( IsEdgeShape() ) EdgeShape()->m_vertex3 = v; }
	SGS_PROPERTY_FUNC( READ _getEdgeVertex3 WRITE _setEdgeVertex3 ) SGS_ALIAS( b2Vec2 edgeVertex3 );
	// > hasEdgeVertex0
	bool _getHasEdgeVertex0(){ if( IsEdgeShape() ) return EdgeShape()->m_hasVertex0; return false; }
	void _setHasEdgeVertex0( bool v ){ if( IsEdgeShape() ) EdgeShape()->m_hasVertex0 = v; }
	SGS_PROPERTY_FUNC( READ _getHasEdgeVertex0 WRITE _setHasEdgeVertex0 ) SGS_ALIAS( bool hasEdgeVertex0 );
	// > hasEdgeVertex3
	bool _getHasEdgeVertex3(){ if( IsEdgeShape() ) return EdgeShape()->m_hasVertex3; return false; }
	void _setHasEdgeVertex3( bool v ){ if( IsEdgeShape() ) EdgeShape()->m_hasVertex3 = v; }
	SGS_PROPERTY_FUNC( READ _getHasEdgeVertex3 WRITE _setHasEdgeVertex3 ) SGS_ALIAS( bool hasEdgeVertex3 );
	// --- poly / chain ---
	// > READONLY vertexCount
	int32 _getVertexCount(){ if( IsPolyShape() ) return PolyShape()->GetVertexCount(); return 0; }
	SGS_PROPERTY_FUNC( READ _getVertexCount ) SGS_ALIAS( int32 vertexCount );
	// --- chain ---
	// > chainPrevVertex
	b2Vec2 _getChainPrevVertex(){ if( IsChainShape() ) return ChainShape()->m_prevVertex; return b2Vec2_zero; }
	void _setChainPrevVertex( b2Vec2 v ){ if( IsChainShape() ) ChainShape()->m_prevVertex = v; }
	SGS_PROPERTY_FUNC( READ _getChainPrevVertex WRITE _setChainPrevVertex ) SGS_ALIAS( b2Vec2 chainPrevVertex );
	// > chainNextVertex
	b2Vec2 _getChainNextVertex(){ if( IsChainShape() ) return ChainShape()->m_nextVertex; return b2Vec2_zero; }
	void _setChainNextVertex( b2Vec2 v ){ if( IsChainShape() ) ChainShape()->m_nextVertex = v; }
	SGS_PROPERTY_FUNC( READ _getChainNextVertex WRITE _setChainNextVertex ) SGS_ALIAS( b2Vec2 chainNextVertex );
	// > hasChainPrevVertex
	bool _getHasChainPrevVertex(){ if( IsChainShape() ) return ChainShape()->m_hasPrevVertex; return false; }
	void _setHasChainPrevVertex( bool v ){ if( IsChainShape() ) ChainShape()->m_hasPrevVertex = v; }
	SGS_PROPERTY_FUNC( READ _getHasChainPrevVertex WRITE _setHasChainPrevVertex ) SGS_ALIAS( bool hasChainPrevVertex );
	// > hasChainNextVertex
	bool _getHasChainNextVertex(){ if( IsChainShape() ) return ChainShape()->m_hasNextVertex; return false; }
	void _setHasChainNextVertex( bool v ){ if( IsChainShape() ) ChainShape()->m_hasNextVertex = v; }
	SGS_PROPERTY_FUNC( READ _getHasChainNextVertex WRITE _setHasChainNextVertex ) SGS_ALIAS( bool hasChainNextVertex );
	
	//
	// METHODS
	//
	// --- generic ---
	// > TestPoint
	SGS_METHOD bool TestPoint( Box2DTransform tf, b2Vec2 p ){ if( m_shape ) return m_shape->TestPoint( tf, p ); return false; }
	// > RayCast
	SGS_METHOD SGS_MULTRET RayCast( b2Vec2 p1, b2Vec2 p2, float32 maxfract, Box2DTransform tf, int32 ci );
	// > ComputeAABB
	SGS_METHOD sgsVariable ComputeAABB( Box2DTransform tf, int32 ci );
	// > ComputeMass
	SGS_METHOD sgsVariable ComputeMass( float32 density );
	// --- circle ---
	// --- edge ---
	// > SetEdge
	SGS_METHOD void SetEdge( b2Vec2 v1, b2Vec2 v2 );
	// --- poly ---
	// > GetVertexArray
	SGS_METHOD SGS_MULTRET GetVertexArray();
	// > GetVertexFloatArray
	SGS_METHOD SGS_MULTRET GetVertexFloatArray();
	// > SetVertices
	SGS_METHOD void SetVertices( /* ... (vec2 list) */ );
	// > SetVerticesFromVec2Array
	SGS_METHOD void SetVerticesFromVec2Array( sgsVariable arr );
	// > SetVerticesFromFloatArray
	SGS_METHOD void SetVerticesFromFloatArray( FloatArray fa );
	// > SetAsBox
	SGS_METHOD void SetAsBox( float32 hx, float32 hy, b2Vec2 center, float32 angle ){ if( IsPolyShape() ) PolyShape()->SetAsBox( hx, hy, center, angle ); }
	// > GetVertex
	SGS_METHOD b2Vec2 GetVertex( int32 v ){ if( IsPolyShape() ) return PolyShape()->GetVertex( v ); return b2Vec2_zero; }
	// > Validate
	SGS_METHOD bool Validate(){ if( IsPolyShape() ) return PolyShape()->Validate(); return false; }
	// --- chain ---
	void _createLoopOrChain( bool chain );
	void _createLoopOrChainFromVec2Array( sgsVariable& arr, bool chain );
	void _createLoopOrChainFromFloatArray( FloatArray& fa, bool chain );
	// > CreateLoop
	SGS_METHOD void CreateLoop( /* ... (vec2 list) */ );
	// > CreateLoopFromVec2Array
	SGS_METHOD void CreateLoopFromVec2Array( sgsVariable arr );
	// > CreateLoopFromFloatArray
	SGS_METHOD void CreateLoopFromFloatArray( FloatArray fa );
	// > CreateChain
	SGS_METHOD void CreateChain( /* ... (vec2 list) */ );
	// > CreateChainFromVec2Array
	SGS_METHOD void CreateChainFromVec2Array( sgsVariable arr );
	// > CreateChainFromFloatArray
	SGS_METHOD void CreateChainFromFloatArray( FloatArray fa );
	// > SetPrevVertex
	SGS_METHOD void SetPrevVertex( b2Vec2 p ){ if( IsChainShape() ) ChainShape()->SetPrevVertex( p ); }
	// > SetNextVertex
	SGS_METHOD void SetNextVertex( b2Vec2 p ){ if( IsChainShape() ) ChainShape()->SetNextVertex( p ); }
	// > GetChildEdge
	SGS_METHOD SGS_MULTRET GetChildEdge( int32 i );
	
	b2Shape* m_shape;
	Box2DFixture* m_fixture;
	Box2DShape* m_prev;
	Box2DShape* m_next;
};


struct Box2DFixtureDef : b2FixtureDef
{
	typedef sgsHandle< Box2DFixtureDef > Handle;
	
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DFixtureDef* fd = (Box2DFixtureDef*) obj->data;
		fd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	//
	// PROPERTIES
	//
	// > shape
	SGS_PROPERTY_FUNC( READ WRITE VARNAME shape ) Box2DShapeHandle _shape;
	// > friction
	SGS_PROPERTY SGS_ALIAS( float32 friction );
	// > restitution
	SGS_PROPERTY SGS_ALIAS( float32 restitution );
	// > density
	SGS_PROPERTY SGS_ALIAS( float32 density );
	// > isSensor
	SGS_PROPERTY SGS_ALIAS( bool isSensor );
	// > userData
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	// > onDestroy
	SGS_PROPERTY sgsVariable onDestroy;
	// > filterData
	Box2DFilterData _getFilterData(){ return filter; }
	void _setFilterData( const Box2DFilterData& fd ){ filter = fd; }
	SGS_PROPERTY_FUNC( READ _getFilterData WRITE _setFilterData ) SGS_ALIAS( Box2DFilterData filterData );
	// > categoryBits (from filter)
	SGS_PROPERTY_FUNC( READ WRITE VARNAME categoryBits ) SGS_ALIAS( uint16 filter.categoryBits );
	// > maskBits (from filter)
	SGS_PROPERTY_FUNC( READ WRITE VARNAME maskBits ) SGS_ALIAS( uint16 filter.maskBits );
	// > groupIndex (from filter)
	SGS_PROPERTY_FUNC( READ WRITE VARNAME groupIndex ) SGS_ALIAS( int16 filter.groupIndex );
};


struct Box2DFixture
{
	static Box2DFixtureHandle HandleFromPtr( b2Fixture* fx )
	{
		if( fx )
			return Box2DFixtureHandle( (Box2DFixture*) fx->GetUserData() );
		return Box2DFixtureHandle();
	}
	
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DFixture* fx = (Box2DFixture*) obj->data;
		fx->userData.gcmark();
		fx->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	Box2DFixture( b2Fixture* fixture ) : m_fixture( fixture ), m_shapeList( NULL ){}
	~Box2DFixture(){ _cleanUp(); }
	
	void _cleanUp( bool destroy = true );
	
	//
	// PROPERTIES
	//
	// > READONLY shapeType
	int32 _getShapeType(){ if( m_fixture ) return m_fixture->GetType(); return -1; }
	SGS_PROPERTY_FUNC( READ _getShapeType ) SGS_ALIAS( int32 shapeType );
	// > READONLY shape
	sgsVariable _getShape(){ if( m_fixture ){ SGS_CREATECLASS( C, NULL, Box2DShape, ( m_fixture->GetShape(), this ) ); return sgsVariable( C, -1 ); } return sgsVariable(); }
	SGS_PROPERTY_FUNC( READ _getShape ) SGS_ALIAS( sgsVariable shape );
	// > READONLY next
	Box2DFixtureHandle _getNext(){ if( m_fixture ) return Box2DFixtureHandle( Box2DFixture::HandleFromPtr( m_fixture->GetNext() ) ); return Box2DFixtureHandle(); }
	SGS_PROPERTY_FUNC( READ _getNext ) SGS_ALIAS( Box2DFixtureHandle next );
	// > READONLY body
	Box2DBodyHandle _getBody();
	SGS_PROPERTY_FUNC( READ _getBody ) SGS_ALIAS( Box2DBodyHandle body );
	// > sensor
	bool _getSensor(){ if( m_fixture ) return m_fixture->IsSensor(); return 0; }
	void _setSensor( bool v ){ if( m_fixture ) return m_fixture->SetSensor( v ); }
	SGS_PROPERTY_FUNC( READ _getSensor WRITE _setSensor ) SGS_ALIAS( bool sensor );
	// > filterData
	Box2DFilterData _getFilterData(){ if( m_fixture ) return m_fixture->GetFilterData(); return Box2DFilterData(); }
	void _setFilterData( const Box2DFilterData& fd ){ if( m_fixture ) m_fixture->SetFilterData( fd ); }
	SGS_PROPERTY_FUNC( READ _getFilterData WRITE _setFilterData ) SGS_ALIAS( Box2DFilterData filterData );
	// > categoryBits
	uint16 _getCategoryBits(){ if( m_fixture ) return m_fixture->GetFilterData().categoryBits; return 0; }
	void _setCategoryBits( uint16 v ){ if( m_fixture ){ b2Filter fd = m_fixture->GetFilterData(); fd.categoryBits = v; m_fixture->SetFilterData( fd ); } }
	SGS_PROPERTY_FUNC( READ _getCategoryBits WRITE _setCategoryBits ) SGS_ALIAS( uint16 categoryBits );
	// > maskBits
	uint16 _getMaskBits(){ if( m_fixture ) return m_fixture->GetFilterData().maskBits; return 0; }
	void _setMaskBits( uint16 v ){ if( m_fixture ){ b2Filter fd = m_fixture->GetFilterData(); fd.maskBits = v; m_fixture->SetFilterData( fd ); } }
	SGS_PROPERTY_FUNC( READ _getMaskBits WRITE _setMaskBits ) SGS_ALIAS( uint16 maskBits );
	// > groupIndex
	int16 _getGroupIndex(){ if( m_fixture ) return m_fixture->GetFilterData().groupIndex; return 0; }
	void _setGroupIndex( int16 v ){ if( m_fixture ){ b2Filter fd = m_fixture->GetFilterData(); fd.groupIndex = v; m_fixture->SetFilterData( fd ); } }
	SGS_PROPERTY_FUNC( READ _getGroupIndex WRITE _setGroupIndex ) SGS_ALIAS( int16 groupIndex );
	// > userData
	SGS_PROPERTY sgsVariable userData;
	// > onDestroy
	SGS_PROPERTY sgsVariable onDestroy;
	// > density
	float32 _getDensity(){ if( m_fixture ) return m_fixture->GetDensity(); return 0; }
	void _setDensity( float32 v ){ if( m_fixture ) return m_fixture->SetDensity( v ); }
	SGS_PROPERTY_FUNC( READ _getDensity WRITE _setDensity ) SGS_ALIAS( float32 density );
	// > friction
	float32 _getFriction(){ if( m_fixture ) return m_fixture->GetFriction(); return 0; }
	void _setFriction( float32 v ){ if( m_fixture ) return m_fixture->SetFriction( v ); }
	SGS_PROPERTY_FUNC( READ _getFriction WRITE _setFriction ) SGS_ALIAS( float32 friction );
	// > restitution
	float32 _getRestitution(){ if( m_fixture ) return m_fixture->GetRestitution(); return 0; }
	void _setRestitution( float32 v ){ if( m_fixture ) return m_fixture->SetRestitution( v ); }
	SGS_PROPERTY_FUNC( READ _getRestitution WRITE _setRestitution ) SGS_ALIAS( float32 restitution );
	
	//
	// METHODS
	//
	// > Refilter
	SGS_METHOD void Refilter(){ if( m_fixture ) m_fixture->Refilter(); }
	// > TestPoint
	SGS_METHOD bool TestPoint( b2Vec2 p ){ if( m_fixture ) return m_fixture->TestPoint( p ); return false; }
	// > RayCast
	SGS_METHOD SGS_MULTRET RayCast( b2Vec2 p1, b2Vec2 p2, float32 maxfract, int32 ci );
	// > GetAABB
	SGS_METHOD sgsVariable GetAABB( int32 ci ){ if( m_fixture ){ sgs_PushVar( C, m_fixture->GetAABB( ci ) ); return sgsVariable( C, -1 ); } return sgsVariable(); }
	// > Dump
	SGS_METHOD void Dump( int32 bi ){ if( m_fixture ) m_fixture->Dump( bi ); }
	
	b2Fixture* m_fixture;
	Box2DShape* m_shapeList;
};


struct Box2DBodyDef : b2BodyDef
{
	typedef sgsHandle< Box2DBodyDef > Handle;
	
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DBodyDef* bd = (Box2DBodyDef*) obj->data;
		bd->_userData.gcmark();
		return SGS_SUCCESS;
	}
	
	//
	// PROPERTIES
	//
	// > type
	int _getType(){ return type; };
	void _setType( int ty ){ type = (b2BodyType) ty; };
	SGS_PROPERTY_FUNC( READ _getType WRITE _setType ) SGS_ALIAS( int type );
	// > position
	SGS_PROPERTY SGS_ALIAS( b2Vec2 position );
	// > angle
	SGS_PROPERTY SGS_ALIAS( float angle );
	// > linearVelocity
	SGS_PROPERTY SGS_ALIAS( b2Vec2 linearVelocity );
	// > angularVelocity
	SGS_PROPERTY SGS_ALIAS( float angularVelocity );
	// > linearDamping
	SGS_PROPERTY SGS_ALIAS( float linearDamping );
	// > angularDamping
	SGS_PROPERTY SGS_ALIAS( float angularDamping );
	// > allowSleep
	SGS_PROPERTY SGS_ALIAS( bool allowSleep );
	// > awake
	SGS_PROPERTY SGS_ALIAS( bool awake );
	// > fixedRotation
	SGS_PROPERTY SGS_ALIAS( bool fixedRotation );
	// > bullet
	SGS_PROPERTY SGS_ALIAS( bool bullet );
	// > active
	SGS_PROPERTY SGS_ALIAS( bool active );
	// > gravityScale
	SGS_PROPERTY SGS_ALIAS( float gravityScale );
	// > userData
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
};


struct Box2DBody
{
	static Box2DBodyHandle HandleFromPtr( b2Body* body )
	{
		if( body )
			return Box2DBodyHandle( (Box2DBody*) body->GetUserData() );
		return Box2DBodyHandle();
	}
	
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DBody* bd = (Box2DBody*) obj->data;
		bd->userData.gcmark();
		if( bd->m_body )
		{
			b2Fixture* pfx = bd->m_body->GetFixtureList();
			while( pfx )
			{
				Box2DFixture::HandleFromPtr( pfx ).gcmark();
				pfx = pfx->GetNext();
			}
		}
		return SGS_SUCCESS;
	}
	
	Box2DBody( b2Body* body ) : m_body( body ){}
	~Box2DBody(){ _cleanUp(); }
	
	void _cleanUp();
	
	//
	// METHODS
	//
	// > CreateFixture
	SGS_METHOD Box2DFixtureHandle CreateFixture( Box2DFixtureDef::Handle def );
	// > CreateFixtureFromShape
	SGS_METHOD Box2DFixtureHandle CreateFixtureFromShape( Box2DShapeHandle shape, float32 density );
	// > DestroyFixture
	SGS_METHOD void DestroyFixture( Box2DFixtureHandle fixture );
	// > SetTransform
	SGS_METHOD void SetTransform( b2Vec2 position, float32 angle ){ if( m_body ) m_body->SetTransform( position, angle ); }
	// > ApplyForce
	SGS_METHOD void ApplyForce( b2Vec2 force, b2Vec2 point, bool wake ){ if( m_body ) m_body->ApplyForce( force, point, wake ); }
	// > ApplyForceToCenter
	SGS_METHOD void ApplyForceToCenter( b2Vec2 force, bool wake ){ if( m_body ) m_body->ApplyForceToCenter( force, wake ); }
	// > ApplyTorque
	SGS_METHOD void ApplyTorque( float32 torque, bool wake ){ if( m_body ) m_body->ApplyTorque( torque, wake ); }
	// > ApplyLinearImpulse
	SGS_METHOD void ApplyLinearImpulse( b2Vec2 impulse, b2Vec2 point, bool wake ){ if( m_body ) m_body->ApplyLinearImpulse( impulse, point, wake ); }
	// > ApplyLinearImpulseToCenter
	SGS_METHOD void ApplyLinearImpulseToCenter( b2Vec2 impulse, bool wake ){ if( m_body ) m_body->ApplyLinearImpulse( impulse, m_body->GetPosition(), wake ); }
	// > ApplyAngularImpulse
	SGS_METHOD void ApplyAngularImpulse( float32 impulse, bool wake ){ if( m_body ) m_body->ApplyAngularImpulse( impulse, wake ); }
	// > ResetMassData
	SGS_METHOD void ResetMassData(){ if( m_body ) m_body->ResetMassData(); }
	// > GetWorldPoint
	SGS_METHOD b2Vec2 GetWorldPoint( b2Vec2 localPoint ){ if( m_body ) return m_body->GetWorldPoint( localPoint ); else return b2Vec2_zero; }
	// > GetWorldVector
	SGS_METHOD b2Vec2 GetWorldVector( b2Vec2 localVector ){ if( m_body ) return m_body->GetWorldVector( localVector ); else return b2Vec2_zero; }
	// > GetLocalPoint
	SGS_METHOD b2Vec2 GetLocalPoint( b2Vec2 worldPoint ){ if( m_body ) return m_body->GetLocalPoint( worldPoint ); else return b2Vec2_zero; }
	// > GetLocalVector
	SGS_METHOD b2Vec2 GetLocalVector( b2Vec2 worldVector ){ if( m_body ) return m_body->GetLocalVector( worldVector ); else return b2Vec2_zero; }
	// > GetLinearVelocityFromWorldPoint
	SGS_METHOD b2Vec2 GetLinearVelocityFromWorldPoint( b2Vec2 worldPoint ){ if( m_body ) return m_body->GetLinearVelocityFromWorldPoint( worldPoint ); else return b2Vec2_zero; }
	// > GetLinearVelocityFromLocalPoint
	SGS_METHOD b2Vec2 GetLinearVelocityFromLocalPoint( b2Vec2 localPoint ){ if( m_body ) return m_body->GetLinearVelocityFromLocalPoint( localPoint ); else return b2Vec2_zero; }
	// > GetJointList
	SGS_METHOD sgsVariable GetJointList( bool map );
	// > GetContactList
	SGS_METHOD sgsVariable GetContactList( bool map );
	
	//
	// PROPERTIES
	//
	// > position
	const b2Vec2& _getPosition(){ return m_body ? m_body->GetPosition() : b2Vec2_zero; }
	void _setPosition( const b2Vec2& pos ){ if( m_body ) m_body->SetTransform( pos, m_body->GetAngle() ); }
	SGS_PROPERTY_FUNC( READ _getPosition WRITE _setPosition ) SGS_ALIAS( b2Vec2 position );
	// > angle
	float _getAngle(){ return m_body ? m_body->GetAngle() : 0; }
	void _setAngle( float angle ){ if( m_body ) m_body->SetTransform( m_body->GetPosition(), angle ); }
	SGS_PROPERTY_FUNC( READ _getAngle WRITE _setAngle ) SGS_ALIAS( float angle );
	// > transform
	Box2DTransform _getTransform(){ return m_body ? m_body->GetTransform() : Box2DTransform(); }
	void _setTransform( const Box2DTransform& t ){ if( m_body ) m_body->SetTransform( t.p, t.q.GetAngle() ); }
	SGS_PROPERTY_FUNC( READ _getTransform WRITE _setTransform ) SGS_ALIAS( Box2DTransform transform );
	// > worldCenter
	const b2Vec2& _getWorldCenter(){ return m_body ? m_body->GetWorldCenter() : b2Vec2_zero; }
	void _setWorldCenter( const b2Vec2& v ){ if( m_body ){ b2MassData md; m_body->GetMassData( &md ); md.center = m_body->GetLocalPoint( v ); m_body->SetMassData( &md ); } }
	SGS_PROPERTY_FUNC( READ _getWorldCenter WRITE _setWorldCenter ) SGS_ALIAS( b2Vec2 worldCenter );
	// > localCenter
	const b2Vec2& _getLocalCenter(){ return m_body ? m_body->GetLocalCenter() : b2Vec2_zero; }
	void _setLocalCenter( const b2Vec2& v ){ if( m_body ){ b2MassData md; m_body->GetMassData( &md ); md.center = v; m_body->SetMassData( &md ); } }
	SGS_PROPERTY_FUNC( READ _getLocalCenter WRITE _setLocalCenter ) SGS_ALIAS( b2Vec2 localCenter );
	// > linearVelocity
	const b2Vec2& _getLinearVelocity(){ return m_body ? m_body->GetLinearVelocity() : b2Vec2_zero; }
	void _setLinearVelocity( const b2Vec2& vel ){ if( m_body ) m_body->SetLinearVelocity( vel ); }
	SGS_PROPERTY_FUNC( READ _getLinearVelocity WRITE _setLinearVelocity ) SGS_ALIAS( b2Vec2 linearVelocity );
	// > angularVelocity
	float _getAngularVelocity(){ return m_body ? m_body->GetAngularVelocity() : 0; }
	void _setAngularVelocity( float f ){ if( m_body ) m_body->SetAngularVelocity( f ); }
	SGS_PROPERTY_FUNC( READ _getAngularVelocity WRITE _setAngularVelocity ) SGS_ALIAS( float angularVelocity );
	// > massData
	Box2DMassData _getMassData(){ if( m_body ){ b2MassData md; m_body->GetMassData( &md ); return md; } return Box2DMassData(); }
	void _setMassData( const Box2DMassData& md ){ if( m_body ) m_body->SetMassData( &md ); }
	SGS_PROPERTY_FUNC( READ _getMassData WRITE _setMassData ) SGS_ALIAS( Box2DMassData massData );
	// > mass
	float _getMass(){ return m_body ? m_body->GetMass() : 0; }
	void _setMass( float mass ){ if( m_body ){ b2MassData md; m_body->GetMassData( &md ); md.mass = mass; m_body->SetMassData( &md ); } }
	SGS_PROPERTY_FUNC( READ _getMass WRITE _setMass ) SGS_ALIAS( float mass );
	// > inertia
	float _getInertia(){ return m_body ? m_body->GetInertia() : 0; }
	void _setInertia( float inertia ){ if( m_body ){ b2MassData md; m_body->GetMassData( &md ); md.I = inertia; m_body->SetMassData( &md ); } }
	SGS_PROPERTY_FUNC( READ _getInertia WRITE _setInertia ) SGS_ALIAS( float inertia );
	// > linearDamping
	float _getLinearDamping(){ return m_body ? m_body->GetLinearDamping() : 0; }
	void _setLinearDamping( float f ){ if( m_body ) m_body->SetLinearDamping( f ); }
	SGS_PROPERTY_FUNC( READ _getLinearDamping WRITE _setLinearDamping ) SGS_ALIAS( float linearDamping );
	// > angularDamping
	float _getAngularDamping(){ return m_body ? m_body->GetAngularDamping() : 0; }
	void _setAngularDamping( float f ){ if( m_body ) m_body->SetAngularDamping( f ); }
	SGS_PROPERTY_FUNC( READ _getAngularDamping WRITE _setAngularDamping ) SGS_ALIAS( float angularDamping );
	// > gravityScale
	float _getGravityScale(){ return m_body ? m_body->GetGravityScale() : 0; }
	void _setGravityScale( float f ){ if( m_body ) m_body->SetGravityScale( f ); }
	SGS_PROPERTY_FUNC( READ _getGravityScale WRITE _setGravityScale ) SGS_ALIAS( float gravityScale );
	// > type
	bool _getType(){ return m_body ? m_body->GetType() : 0; }
	void _setType( int ty ){ if( m_body ) m_body->SetType( (b2BodyType) ty ); }
	SGS_PROPERTY_FUNC( READ _getType WRITE _setType ) SGS_ALIAS( int type );
	// > isBullet
	bool _getIsBullet(){ return m_body ? m_body->IsBullet() : 0; }
	void _setIsBullet( bool b ){ if( m_body ) m_body->SetBullet( b ); }
	SGS_PROPERTY_FUNC( READ _getIsBullet WRITE _setIsBullet ) SGS_ALIAS( bool isBullet );
	// > allowSleeping
	bool _getAllowSleeping(){ return m_body ? m_body->IsSleepingAllowed() : 0; }
	void _setAllowSleeping( bool b ){ if( m_body ) m_body->SetSleepingAllowed( b ); }
	SGS_PROPERTY_FUNC( READ _getAllowSleeping WRITE _setAllowSleeping ) SGS_ALIAS( bool allowSleeping );
	// > isAwake
	bool _getIsAwake(){ return m_body ? m_body->IsAwake() : 0; }
	void _setIsAwake( bool b ){ if( m_body ) m_body->SetAwake( b ); }
	SGS_PROPERTY_FUNC( READ _getIsAwake WRITE _setIsAwake ) SGS_ALIAS( bool isAwake );
	// > isActive
	bool _getIsActive(){ return m_body ? m_body->IsActive() : 0; }
	void _setIsActive( bool b ){ if( m_body ) m_body->SetActive( b ); }
	SGS_PROPERTY_FUNC( READ _getIsActive WRITE _setIsActive ) SGS_ALIAS( bool isActive );
	// > hasFixedRotation
	bool _getHasFixedRotation(){ return m_body ? m_body->IsFixedRotation() : 0; }
	void _setHasFixedRotation( bool b ){ if( m_body ) m_body->SetFixedRotation( b ); }
	SGS_PROPERTY_FUNC( READ _getHasFixedRotation WRITE _setHasFixedRotation ) SGS_ALIAS( bool hasFixedRotation );
	// > userData
	SGS_PROPERTY sgsVariable userData;
	// > READONLY fixtureList
	Box2DFixtureHandle _getFixtureList(){ if( m_body ) return Box2DFixture::HandleFromPtr( m_body->GetFixtureList() ); return Box2DFixtureHandle(); }
	SGS_PROPERTY_FUNC( READ _getFixtureList ) SGS_ALIAS( Box2DFixtureHandle fixtureList );
	// > READONLY next
	Box2DBodyHandle _getNext(){ if( m_body ) return Box2DBody::HandleFromPtr( m_body->GetNext() ); return Box2DBodyHandle(); }
	SGS_PROPERTY_FUNC( READ _getNext ) SGS_ALIAS( Box2DBodyHandle next );
	// > READONLY world
	Box2DWorldHandle _getWorld();
	SGS_PROPERTY_FUNC( READ _getWorld ) SGS_ALIAS( Box2DWorldHandle world );
	
	b2Body* m_body;
};


struct Box2DDistanceJointDef : b2DistanceJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DDistanceJointDef* jd = (Box2DDistanceJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( float32 length );
	SGS_PROPERTY SGS_ALIAS( float32 frequencyHz );
	SGS_PROPERTY SGS_ALIAS( float32 dampingRatio );
	
	SGS_METHOD void Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchorA, const b2Vec2& anchorB );
};

struct Box2DFrictionJointDef : b2FrictionJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DFrictionJointDef* jd = (Box2DFrictionJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( float32 maxForce );
	SGS_PROPERTY SGS_ALIAS( float32 maxTorque );
	
	SGS_METHOD void Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor );
};

struct Box2DGearJointDef : b2GearJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DGearJointDef* jd = (Box2DGearJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY_FUNC( READ WRITE VARNAME jointA ) Box2DJointHandle _jointA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME jointB ) Box2DJointHandle _jointB;
	SGS_PROPERTY SGS_ALIAS( float32 ratio );
};

struct Box2DMotorJointDef : b2MotorJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DMotorJointDef* jd = (Box2DMotorJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 linearOffset );
	SGS_PROPERTY SGS_ALIAS( float32 angularOffset );
	SGS_PROPERTY SGS_ALIAS( float32 maxForce );
	SGS_PROPERTY SGS_ALIAS( float32 maxTorque );
	SGS_PROPERTY SGS_ALIAS( float32 correctionFactor );
	
	SGS_METHOD void Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB );
};

struct Box2DMouseJointDef : b2MouseJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DMouseJointDef* jd = (Box2DMouseJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 target );
	SGS_PROPERTY SGS_ALIAS( float32 maxForce );
	SGS_PROPERTY SGS_ALIAS( float32 frequencyHz );
	SGS_PROPERTY SGS_ALIAS( float32 dampingRatio );
};

struct Box2DPrismaticJointDef : b2PrismaticJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DPrismaticJointDef* jd = (Box2DPrismaticJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAxisA );
	SGS_PROPERTY SGS_ALIAS( float32 referenceAngle );
	SGS_PROPERTY SGS_ALIAS( bool enableLimit );
	SGS_PROPERTY SGS_ALIAS( float32 lowerTranslation );
	SGS_PROPERTY SGS_ALIAS( float32 upperTranslation );
	SGS_PROPERTY SGS_ALIAS( bool enableMotor );
	SGS_PROPERTY SGS_ALIAS( float32 motorSpeed );
	SGS_PROPERTY SGS_ALIAS( float32 maxMotorForce );
	
	SGS_METHOD void Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor, const b2Vec2& axis );
};

struct Box2DPulleyJointDef : b2PulleyJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DPulleyJointDef* jd = (Box2DPulleyJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 groundAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 groundAnchorB );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( float32 lengthA );
	SGS_PROPERTY SGS_ALIAS( float32 lengthB );
	SGS_PROPERTY SGS_ALIAS( float32 ratio );
	
	SGS_METHOD void Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& groundAnchorA,
		const b2Vec2& groundAnchorB, const b2Vec2& anchorA, const b2Vec2& anchorB, float32 ratio );
};

struct Box2DRevoluteJointDef : b2RevoluteJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DRevoluteJointDef* jd = (Box2DRevoluteJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( float32 referenceAngle );
	SGS_PROPERTY SGS_ALIAS( bool enableLimit );
	SGS_PROPERTY SGS_ALIAS( float32 lowerAngle );
	SGS_PROPERTY SGS_ALIAS( float32 upperAngle );
	SGS_PROPERTY SGS_ALIAS( bool enableMotor );
	SGS_PROPERTY SGS_ALIAS( float32 motorSpeed );
	SGS_PROPERTY SGS_ALIAS( float32 maxMotorTorque );
	
	SGS_METHOD void Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor );
};

struct Box2DRopeJointDef : b2RopeJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DRopeJointDef* jd = (Box2DRopeJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( float32 maxLength );
};

struct Box2DWeldJointDef : b2WeldJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DWeldJointDef* jd = (Box2DWeldJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( float32 referenceAngle );
	SGS_PROPERTY SGS_ALIAS( float32 frequencyHz );
	SGS_PROPERTY SGS_ALIAS( float32 dampingRatio );
};

struct Box2DWheelJointDef : b2WheelJointDef
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DWheelJointDef* jd = (Box2DWheelJointDef*) obj->data;
		jd->_userData.gcmark();
		jd->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	// --- inherited ---
	int _getType(){ return type; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( int type );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyA ) Box2DBodyHandle _bodyA;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME bodyB ) Box2DBodyHandle _bodyB;
	SGS_PROPERTY SGS_ALIAS( bool collideConnected );
	SGS_PROPERTY_FUNC( READ WRITE VARNAME userData ) sgsVariable _userData;
	SGS_PROPERTY sgsVariable onDestroy;
	
	// --- specific ---
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorA );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAnchorB );
	SGS_PROPERTY SGS_ALIAS( b2Vec2 localAxisA );
	SGS_PROPERTY SGS_ALIAS( bool enableMotor );
	SGS_PROPERTY SGS_ALIAS( float32 maxMotorTorque );
	SGS_PROPERTY SGS_ALIAS( float32 motorSpeed );
	SGS_PROPERTY SGS_ALIAS( float32 frequencyHz );
	SGS_PROPERTY SGS_ALIAS( float32 dampingRatio );
	
	SGS_METHOD void Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor, const b2Vec2& axis );
};


struct Box2DJoint
{
	static Box2DJointHandle HandleFromPtr( b2Joint* joint )
	{
		if( joint )
			return Box2DJointHandle( (Box2DJoint*) joint->GetUserData() );
		return Box2DJointHandle();
	}
	
	bool IsDistanceJoint(){ return m_joint && m_joint->GetType() == e_distanceJoint; }
	b2DistanceJoint* DistanceJoint(){ return (b2DistanceJoint*) m_joint; }
	bool IsFrictionJoint(){ return m_joint && m_joint->GetType() == e_frictionJoint; }
	b2FrictionJoint* FrictionJoint(){ return (b2FrictionJoint*) m_joint; }
	bool IsGearJoint(){ return m_joint && m_joint->GetType() == e_gearJoint; }
	b2GearJoint* GearJoint(){ return (b2GearJoint*) m_joint; }
	bool IsMotorJoint(){ return m_joint && m_joint->GetType() == e_motorJoint; }
	b2MotorJoint* MotorJoint(){ return (b2MotorJoint*) m_joint; }
	bool IsMouseJoint(){ return m_joint && m_joint->GetType() == e_mouseJoint; }
	b2MouseJoint* MouseJoint(){ return (b2MouseJoint*) m_joint; }
	bool IsPrismaticJoint(){ return m_joint && m_joint->GetType() == e_prismaticJoint; }
	b2PrismaticJoint* PrismaticJoint(){ return (b2PrismaticJoint*) m_joint; }
	bool IsPulleyJoint(){ return m_joint && m_joint->GetType() == e_pulleyJoint; }
	b2PulleyJoint* PulleyJoint(){ return (b2PulleyJoint*) m_joint; }
	bool IsRevoluteJoint(){ return m_joint && m_joint->GetType() == e_revoluteJoint; }
	b2RevoluteJoint* RevoluteJoint(){ return (b2RevoluteJoint*) m_joint; }
	bool IsRopeJoint(){ return m_joint && m_joint->GetType() == e_ropeJoint; }
	b2RopeJoint* RopeJoint(){ return (b2RopeJoint*) m_joint; }
	bool IsWeldJoint(){ return m_joint && m_joint->GetType() == e_weldJoint; }
	b2WeldJoint* WeldJoint(){ return (b2WeldJoint*) m_joint; }
	bool IsWheelJoint(){ return m_joint && m_joint->GetType() == e_wheelJoint; }
	b2WheelJoint* WheelJoint(){ return (b2WheelJoint*) m_joint; }
	
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DJoint* jn = (Box2DJoint*) obj->data;
		jn->userData.gcmark();
		jn->onDestroy.gcmark();
		return SGS_SUCCESS;
	}
	
	Box2DJoint( b2Joint* joint ) : m_joint( joint ){}
	~Box2DJoint(){ _cleanUp(); }
	
	void _cleanUp( bool destroy = true );
	
	//
	// PROPERTIES
	//
	
	// --- generic ---
	// > READONLY type
	bool _getType(){ return m_joint ? m_joint->GetType() : false; }
	SGS_PROPERTY_FUNC( READ _getType ) SGS_ALIAS( bool type );
	// > READONLY bodyA
	Box2DBodyHandle _getBodyA(){ return m_joint ? Box2DBody::HandleFromPtr( m_joint->GetBodyA() ) : Box2DBodyHandle(); }
	SGS_PROPERTY_FUNC( READ _getBodyA ) SGS_ALIAS( Box2DBodyHandle bodyA );
	// > READONLY bodyB
	Box2DBodyHandle _getBodyB(){ return m_joint ? Box2DBody::HandleFromPtr( m_joint->GetBodyB() ) : Box2DBodyHandle(); }
	SGS_PROPERTY_FUNC( READ _getBodyB ) SGS_ALIAS( Box2DBodyHandle bodyB );
	// > READONLY worldAnchorA
	b2Vec2 _getWorldAnchorA(){ return m_joint ? m_joint->GetAnchorA() : b2Vec2_zero; }
	SGS_PROPERTY_FUNC( READ _getWorldAnchorA ) SGS_ALIAS( b2Vec2 worldAnchorA );
	// > READONLY worldAnchorB
	b2Vec2 _getWorldAnchorB(){ return m_joint ? m_joint->GetAnchorB() : b2Vec2_zero; }
	SGS_PROPERTY_FUNC( READ _getWorldAnchorB ) SGS_ALIAS( b2Vec2 worldAnchorB );
	// > READONLY next
	Box2DJointHandle _getNext(){ return m_joint ? Box2DJoint::HandleFromPtr( m_joint->GetNext() ) : Box2DJointHandle(); }
	SGS_PROPERTY_FUNC( READ _getNext ) SGS_ALIAS( Box2DJointHandle next );
	// > userData
	SGS_PROPERTY sgsVariable userData;
	// > onDestroy
	SGS_PROPERTY sgsVariable onDestroy;
	// > READONLY active
	bool _getActive(){ return m_joint ? m_joint->IsActive() : false; }
	SGS_PROPERTY_FUNC( READ _getActive ) SGS_ALIAS( bool active );
	// > READONLY collideConnected
	bool _getCollideConnected(){ return m_joint ? m_joint->GetCollideConnected() : false; }
	SGS_PROPERTY_FUNC( READ _getCollideConnected ) SGS_ALIAS( bool collideConnected );
	
	// --- multi-joint ---
	// > READONLY localAnchorA
	b2Vec2 _getLocalAnchorA()
	{
		if( IsDistanceJoint() ) return DistanceJoint()->GetLocalAnchorA();
		if( IsFrictionJoint() ) return FrictionJoint()->GetLocalAnchorA();
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetLocalAnchorA();
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetLocalAnchorA();
		if( IsRopeJoint() ) return RopeJoint()->GetLocalAnchorA();
		if( IsWeldJoint() ) return WeldJoint()->GetLocalAnchorA();
		if( IsWheelJoint() ) return WheelJoint()->GetLocalAnchorA();
		return b2Vec2_zero;
	}
	SGS_PROPERTY_FUNC( READ _getLocalAnchorA ) SGS_ALIAS( b2Vec2 localAnchorA );
	// > READONLY localAnchorB
	b2Vec2 _getLocalAnchorB()
	{
		if( IsDistanceJoint() ) return DistanceJoint()->GetLocalAnchorB();
		if( IsFrictionJoint() ) return FrictionJoint()->GetLocalAnchorB();
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetLocalAnchorB();
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetLocalAnchorB();
		if( IsRopeJoint() ) return RopeJoint()->GetLocalAnchorB();
		if( IsWeldJoint() ) return WeldJoint()->GetLocalAnchorB();
		if( IsWheelJoint() ) return WheelJoint()->GetLocalAnchorB();
		return b2Vec2_zero;
	}
	SGS_PROPERTY_FUNC( READ _getLocalAnchorB ) SGS_ALIAS( b2Vec2 localAnchorB );
	// > maxForce
	float32 _getMaxForce()
	{
		if( IsFrictionJoint() ) return FrictionJoint()->GetMaxForce();
		if( IsMotorJoint() ) return MotorJoint()->GetMaxForce();
		if( IsMouseJoint() ) return MouseJoint()->GetMaxForce();
		return 0.0f;
	}
	void _setMaxForce( float32 v )
	{
		if( IsFrictionJoint() ) FrictionJoint()->SetMaxForce( v );
		if( IsMotorJoint() ) MotorJoint()->SetMaxForce( v );
		if( IsMouseJoint() ) MouseJoint()->SetMaxForce( v );
	}
	SGS_PROPERTY_FUNC( READ _getMaxForce WRITE _setMaxForce ) SGS_ALIAS( float32 maxForce );
	// > maxTorque
	float32 _getMaxTorque()
	{
		if( IsFrictionJoint() ) return FrictionJoint()->GetMaxTorque();
		if( IsMotorJoint() ) return MotorJoint()->GetMaxTorque();
		return 0.0f;
	}
	void _setMaxTorque( float32 v )
	{
		if( IsFrictionJoint() ) FrictionJoint()->SetMaxTorque( v );
		if( IsMotorJoint() ) MotorJoint()->SetMaxTorque( v );
	}
	SGS_PROPERTY_FUNC( READ _getMaxTorque WRITE _setMaxTorque ) SGS_ALIAS( float32 maxTorque );
	// > frequency
	float32 _getFrequency()
	{
		if( IsDistanceJoint() ) return DistanceJoint()->GetFrequency();
		if( IsMouseJoint() ) return MouseJoint()->GetFrequency();
		if( IsWeldJoint() ) return WeldJoint()->GetFrequency();
		if( IsWheelJoint() ) return WheelJoint()->GetSpringFrequencyHz();
		return 0.0f;
	}
	void _setFrequency( float32 v )
	{
		if( IsDistanceJoint() ) DistanceJoint()->SetFrequency( v );
		if( IsMouseJoint() ) MouseJoint()->SetFrequency( v );
		if( IsWeldJoint() ) WeldJoint()->SetFrequency( v );
		if( IsWheelJoint() ) WheelJoint()->SetSpringFrequencyHz( v );
	}
	SGS_PROPERTY_FUNC( READ _getFrequency WRITE _setFrequency ) SGS_ALIAS( float32 frequency );
	// > dampingRatio
	float32 _getDampingRatio()
	{
		if( IsDistanceJoint() ) return DistanceJoint()->GetDampingRatio();
		if( IsMouseJoint() ) return MouseJoint()->GetDampingRatio();
		if( IsWeldJoint() ) return WeldJoint()->GetDampingRatio();
		if( IsWheelJoint() ) return WheelJoint()->GetSpringDampingRatio();
		return 0.0f;
	}
	void _setDampingRatio( float32 v )
	{
		if( IsDistanceJoint() ) DistanceJoint()->SetDampingRatio( v );
		if( IsMouseJoint() ) MouseJoint()->SetDampingRatio( v );
		if( IsWeldJoint() ) WeldJoint()->SetDampingRatio( v );
		if( IsWheelJoint() ) WheelJoint()->SetSpringDampingRatio( v );
	}
	SGS_PROPERTY_FUNC( READ _getDampingRatio WRITE _setDampingRatio ) SGS_ALIAS( float32 dampingRatio );
	// > READONLY referenceAngle
	float32 _getReferenceAngle()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetReferenceAngle();
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetReferenceAngle();
		if( IsWeldJoint() ) return WeldJoint()->GetReferenceAngle();
		return 0.0f;
	}
	SGS_PROPERTY_FUNC( READ _getReferenceAngle ) SGS_ALIAS( float32 referenceAngle );
	// > READONLY jointTranslation
	float32 _getJointTranslation()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetJointTranslation();
		if( IsWheelJoint() ) return WheelJoint()->GetJointTranslation();
		return 0.0f;
	}
	SGS_PROPERTY_FUNC( READ _getJointTranslation ) SGS_ALIAS( float32 jointTranslation );
	// > READONLY jointSpeed
	float32 _getJointSpeed()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetJointSpeed();
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetJointSpeed();
		if( IsWheelJoint() ) return WheelJoint()->GetJointSpeed();
		return 0.0f;
	}
	SGS_PROPERTY_FUNC( READ _getJointSpeed ) SGS_ALIAS( float32 jointSpeed );
	// > limit
	bool _getLimit()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->IsLimitEnabled();
		if( IsRevoluteJoint() ) return RevoluteJoint()->IsLimitEnabled();
		return false;
	}
	void _setLimit( bool v )
	{
		if( IsPrismaticJoint() ) PrismaticJoint()->EnableLimit( v );
		if( IsRevoluteJoint() ) RevoluteJoint()->EnableLimit( v );
	}
	SGS_PROPERTY_FUNC( READ _getLimit WRITE _setLimit ) SGS_ALIAS( bool limit );
	// > lowerLimit
	float32 _getLowerLimit()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetLowerLimit();
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetLowerLimit();
		return 0.0f;
	}
	void _setLowerLimit( float32 v )
	{
		if( IsPrismaticJoint() ) PrismaticJoint()->SetLimits( v, PrismaticJoint()->GetUpperLimit() );
		if( IsRevoluteJoint() ) RevoluteJoint()->SetLimits( v, RevoluteJoint()->GetUpperLimit() );
	}
	SGS_PROPERTY_FUNC( READ _getLowerLimit WRITE _setLowerLimit ) SGS_ALIAS( float32 lowerLimit );
	// > upperLimit
	float32 _getUpperLimit()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetUpperLimit();
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetUpperLimit();
		return 0.0f;
	}
	void _setUpperLimit( float32 v )
	{
		if( IsPrismaticJoint() ) PrismaticJoint()->SetLimits( PrismaticJoint()->GetLowerLimit(), v );
		if( IsRevoluteJoint() ) RevoluteJoint()->SetLimits( RevoluteJoint()->GetLowerLimit(), v );
	}
	SGS_PROPERTY_FUNC( READ _getUpperLimit WRITE _setUpperLimit ) SGS_ALIAS( float32 upperLimit );
	// > motor
	bool _getMotor()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->IsMotorEnabled();
		if( IsRevoluteJoint() ) return RevoluteJoint()->IsMotorEnabled();
		if( IsWheelJoint() ) return WheelJoint()->IsMotorEnabled();
		return false;
	}
	void _setMotor( bool v )
	{
		if( IsPrismaticJoint() ) PrismaticJoint()->EnableMotor( v );
		if( IsRevoluteJoint() ) RevoluteJoint()->EnableMotor( v );
		if( IsWheelJoint() ) WheelJoint()->EnableMotor( v );
	}
	SGS_PROPERTY_FUNC( READ _getMotor WRITE _setMotor ) SGS_ALIAS( bool motor );
	// > motorSpeed
	float32 _getMotorSpeed()
	{
		if( IsPrismaticJoint() ) return PrismaticJoint()->GetMotorSpeed();
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetMotorSpeed();
		if( IsWheelJoint() ) return WheelJoint()->GetMotorSpeed();
		return 0.0f;
	}
	void _setMotorSpeed( float32 v )
	{
		if( IsPrismaticJoint() ) PrismaticJoint()->SetMotorSpeed( v );
		if( IsRevoluteJoint() ) RevoluteJoint()->SetMotorSpeed( v );
		if( IsWheelJoint() ) WheelJoint()->SetMotorSpeed( v );
	}
	SGS_PROPERTY_FUNC( READ _getMotorSpeed WRITE _setMotorSpeed ) SGS_ALIAS( float32 motorSpeed );
	// > maxMotorTorque
	float32 _getMaxMotorTorque()
	{
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetMaxMotorTorque();
		if( IsWheelJoint() ) return WheelJoint()->GetMaxMotorTorque();
		return 0.0f;
	}
	void _setMaxMotorTorque( float32 v )
	{
		if( IsRevoluteJoint() ) RevoluteJoint()->SetMaxMotorTorque( v );
		if( IsWheelJoint() ) WheelJoint()->SetMaxMotorTorque( v );
	}
	SGS_PROPERTY_FUNC( READ _getMaxMotorTorque WRITE _setMaxMotorTorque ) SGS_ALIAS( float32 maxMotorTorque );
	// > ratio (READONLY for PULLEY JOINT)
	float32 _getRatio()
	{
		if( IsGearJoint() ) return GearJoint()->GetRatio();
		if( IsPulleyJoint() ) return PulleyJoint()->GetRatio();
		return 0.0f;
	}
	void _setRatio( float32 v ){ if( IsGearJoint() ) GearJoint()->SetRatio( v ); }
	SGS_PROPERTY_FUNC( READ _getRatio WRITE _setRatio ) SGS_ALIAS( float32 ratio );
	
	// --- distance joint ---
	// > length
	float32 _getLength(){ return IsDistanceJoint() ? DistanceJoint()->GetLength() : 0.0f; }
	void _setLength( float32 v ){ if( IsDistanceJoint() ) DistanceJoint()->SetLength( v ); }
	SGS_PROPERTY_FUNC( READ _getLength WRITE _setLength ) SGS_ALIAS( float32 length );
	
	// --- friction joint ---
	
	// --- gear joint ---
	// > READONLY joint1
	Box2DJointHandle _getJoint1(){ return IsGearJoint() ? Box2DJoint::HandleFromPtr( GearJoint()->GetJoint1() ) : Box2DJointHandle(); }
	SGS_PROPERTY_FUNC( READ _getJoint1 ) SGS_ALIAS( Box2DJointHandle joint1 );
	// > READONLY joint2
	Box2DJointHandle _getJoint2(){ return IsGearJoint() ? Box2DJoint::HandleFromPtr( GearJoint()->GetJoint2() ) : Box2DJointHandle(); }
	SGS_PROPERTY_FUNC( READ _getJoint2 ) SGS_ALIAS( Box2DJointHandle joint2 );
	
	// --- motor joint ---
	// > linearOffset
	b2Vec2 _getLinearOffset(){ return IsMotorJoint() ? MotorJoint()->GetLinearOffset() : b2Vec2_zero; }
	void _setLinearOffset( const b2Vec2& v ){ if( IsMotorJoint() ) MotorJoint()->SetLinearOffset( v ); }
	SGS_PROPERTY_FUNC( READ _getLinearOffset WRITE _setLinearOffset ) SGS_ALIAS( b2Vec2 linearOffset );
	// > angularOffset
	float32 _getAngularOffset(){ return IsMotorJoint() ? MotorJoint()->GetAngularOffset() : 0.0f; }
	void _setAngularOffset( float32 v ){ if( IsMotorJoint() ) MotorJoint()->SetAngularOffset( v ); }
	SGS_PROPERTY_FUNC( READ _getAngularOffset WRITE _setAngularOffset ) SGS_ALIAS( float32 angularOffset );
	// > correctionFactor
	float32 _getCorrectionFactor(){ return IsMotorJoint() ? MotorJoint()->GetCorrectionFactor() : 0.0f; }
	void _setCorrectionFactor( float32 v ){ if( IsMotorJoint() ) MotorJoint()->SetCorrectionFactor( v ); }
	SGS_PROPERTY_FUNC( READ _getCorrectionFactor WRITE _setCorrectionFactor ) SGS_ALIAS( float32 correctionFactor );
	
	// --- mouse joint ---
	// > target
	b2Vec2 _getTarget(){ return IsMouseJoint() ? MouseJoint()->GetTarget() : b2Vec2_zero; }
	void _setTarget( const b2Vec2& v ){ if( IsMouseJoint() ) MouseJoint()->SetTarget( v ); }
	SGS_PROPERTY_FUNC( READ _getTarget WRITE _setTarget ) SGS_ALIAS( b2Vec2 target );
	
	// --- prismatic joint ---
	// > maxMotorForce
	float32 _getMaxMotorForce(){ return IsPrismaticJoint() ? PrismaticJoint()->GetMaxMotorForce() : 0.0f; }
	void _setMaxMotorForce( float32 v ){ if( IsPrismaticJoint() ) PrismaticJoint()->SetMaxMotorForce( v ); }
	SGS_PROPERTY_FUNC( READ _getMaxMotorForce WRITE _setMaxMotorForce ) SGS_ALIAS( float32 maxMotorForce );
	
	// --- pulley joint ---
	// > READONLY groundAnchorA
	b2Vec2 _getGroundAnchorA(){ return IsPulleyJoint() ? PulleyJoint()->GetGroundAnchorA() : b2Vec2_zero; }
	SGS_PROPERTY_FUNC( READ _getGroundAnchorA ) SGS_ALIAS( b2Vec2 groundAnchorA );
	// > READONLY groundAnchorB
	b2Vec2 _getGroundAnchorB(){ return IsPulleyJoint() ? PulleyJoint()->GetGroundAnchorB() : b2Vec2_zero; }
	SGS_PROPERTY_FUNC( READ _getGroundAnchorB ) SGS_ALIAS( b2Vec2 groundAnchorB );
	// > READONLY lengthA
	float32 _getLengthA(){ return IsPulleyJoint() ? PulleyJoint()->GetLengthA() : 0.0f; }
	SGS_PROPERTY_FUNC( READ _getLengthA ) SGS_ALIAS( float32 lengthA );
	// > READONLY lengthB
	float32 _getLengthB(){ return IsPulleyJoint() ? PulleyJoint()->GetLengthB() : 0.0f; }
	SGS_PROPERTY_FUNC( READ _getLengthB ) SGS_ALIAS( float32 lengthB );
	// > READONLY currentLengthA
	float32 _getCurrentLengthA(){ return IsPulleyJoint() ? PulleyJoint()->GetCurrentLengthA() : 0.0f; }
	SGS_PROPERTY_FUNC( READ _getCurrentLengthA ) SGS_ALIAS( float32 currentLengthA );
	// > READONLY currentLengthB
	float32 _getCurrentLengthB(){ return IsPulleyJoint() ? PulleyJoint()->GetCurrentLengthB() : 0.0f; }
	SGS_PROPERTY_FUNC( READ _getCurrentLengthB ) SGS_ALIAS( float32 currentLengthB );
	
	// --- revolute joint ---
	// > READONLY jointAngle
	float32 _getJointAngle(){ return IsRevoluteJoint() ? RevoluteJoint()->GetJointAngle() : 0.0f; }
	SGS_PROPERTY_FUNC( READ _getJointAngle ) SGS_ALIAS( float32 jointAngle );
	
	// --- rope joint ---
	// > maxLength
	float32 _getMaxLength(){ return IsRopeJoint() ? RopeJoint()->GetMaxLength() : 0.0f; }
	void _setMaxLength( float32 v ){ if( IsRopeJoint() ) RopeJoint()->SetMaxLength( v ); }
	SGS_PROPERTY_FUNC( READ _getMaxLength WRITE _setMaxLength ) SGS_ALIAS( float32 maxLength );
	// > READONLY limitState
	int _getLimitState(){ return IsRopeJoint() ? RopeJoint()->GetLimitState() : e_inactiveLimit; }
	SGS_PROPERTY_FUNC( READ _getLimitState ) SGS_ALIAS( int limitState );
	
	// --- weld joint ---
	
	// --- wheel joint ---
	
	//
	// METHODS
	//
	// --- generic ---
	// > GetReactionForce
	SGS_METHOD b2Vec2 GetReactionForce( float32 inv_dt ){ return m_joint ? m_joint->GetReactionForce( inv_dt ) : b2Vec2_zero; }
	// > GetReactionTorque
	SGS_METHOD float32 GetReactionTorque( float32 inv_dt ){ return m_joint ? m_joint->GetReactionTorque( inv_dt ) : 0.0f; }
	// > Dump
	SGS_METHOD void Dump(){ if( m_joint ) m_joint->Dump(); }
	// > ShiftOrigin
	SGS_METHOD void ShiftOrigin( const b2Vec2& off ){ if( m_joint ) m_joint->ShiftOrigin( off ); }
	// > GetMotorTorque
	SGS_METHOD float32 GetMotorTorque( float32 inv_dt )
	{
		if( IsRevoluteJoint() ) return RevoluteJoint()->GetMotorTorque( inv_dt );
		if( IsWheelJoint() ) return WheelJoint()->GetMotorTorque( inv_dt );
		return 0.0f;
	}
	// --- distance joint ---
	// --- friction joint ---
	// --- gear joint ---
	// --- motor joint ---
	// --- mouse joint ---
	// --- prismatic joint ---
	// > GetMotorForce
	SGS_METHOD float32 GetMotorForce( float32 inv_dt ){ return IsPrismaticJoint() ? PrismaticJoint()->GetMotorForce( inv_dt ) : 0.0f; }
	// --- pulley joint ---
	// --- revolute joint ---
	// --- rope joint ---
	// --- weld joint ---
	// --- wheel joint ---
	
	b2Joint* m_joint;
};


struct Box2DContact
{
	SGS_OBJECT;
	
	static Box2DContactHandle HandleFromPtr( b2Contact* contact, b2World* world );
	
	//
	// METHODS
	//
	// > ResetFriction
	SGS_METHOD void ResetFriction(){ if( m_contact ){ m_contact->ResetFriction(); } }
	// > ResetRestitution
	SGS_METHOD void ResetRestitution(){ if( m_contact ){ m_contact->ResetRestitution(); } }
	
	//
	// PROPERTIES
	//
	// > READONLY getManifold
	// > READONLY getWorldManifold
	// > READONLY isTouching
	bool _get_isTouching(){ return m_contact ? m_contact->IsTouching() : false; }
	SGS_PROPERTY_FUNC( READ _get_isTouching ) SGS_ALIAS( bool isTouching );
	// > enabled
	bool _get_enabled(){ return m_contact ? m_contact->IsEnabled() : false; }
	void _set_enabled( bool v ){ if( m_contact ){ m_contact->SetEnabled( v ); } }
	SGS_PROPERTY_FUNC( READ _get_enabled WRITE _set_enabled ) SGS_ALIAS( bool enabled );
	// > READONLY next
	Box2DContactHandle _get_next(){ return m_contact ? Box2DContact::HandleFromPtr( m_contact->GetNext(), m_contact->GetFixtureA()->GetBody()->GetWorld() ) : Box2DContactHandle(); }
	SGS_PROPERTY_FUNC( READ _get_next ) SGS_ALIAS( Box2DContactHandle next );
	// > READONLY fixtureA
	Box2DFixtureHandle _get_fixtureA(){ return m_contact ? Box2DFixture::HandleFromPtr( m_contact->GetFixtureA() ) : Box2DFixtureHandle(); }
	SGS_PROPERTY_FUNC( READ _get_fixtureA ) SGS_ALIAS( Box2DFixtureHandle fixtureA );
	// > READONLY fixtureB
	Box2DFixtureHandle _get_fixtureB(){ return m_contact ? Box2DFixture::HandleFromPtr( m_contact->GetFixtureB() ) : Box2DFixtureHandle(); }
	SGS_PROPERTY_FUNC( READ _get_fixtureB ) SGS_ALIAS( Box2DFixtureHandle fixtureB );
	// > READONLY childIndexA
	int32 _get_childIndexA(){ return m_contact ? m_contact->GetChildIndexA() : 0; }
	SGS_PROPERTY_FUNC( READ _get_childIndexA ) SGS_ALIAS( int32 childIndexA );
	// > READONLY childIndexB
	int32 _get_childIndexB(){ return m_contact ? m_contact->GetChildIndexB() : 0; }
	SGS_PROPERTY_FUNC( READ _get_childIndexB ) SGS_ALIAS( int32 childIndexB );
	// > friction
	float32 _get_friction(){ return m_contact ? m_contact->GetFriction() : 0.0f; }
	void _set_friction( float32 x ){ if( m_contact ){ m_contact->SetFriction( x ); } }
	SGS_PROPERTY_FUNC( READ _get_friction WRITE _set_friction ) SGS_ALIAS( float32 friction );
	// > restitution
	float32 _get_restitution(){ return m_contact ? m_contact->GetRestitution() : 0.0f; }
	void _set_restitution( float32 x ){ if( m_contact ){ m_contact->SetRestitution( x ); } }
	SGS_PROPERTY_FUNC( READ _get_restitution WRITE _set_restitution ) SGS_ALIAS( float32 restitution );
	// > tangentSpeed
	float32 _get_tangentSpeed(){ return m_contact ? m_contact->GetTangentSpeed() : 0.0f; }
	void _set_tangentSpeed( float32 x ){ if( m_contact ){ m_contact->SetTangentSpeed( x ); } }
	SGS_PROPERTY_FUNC( READ _get_tangentSpeed WRITE _set_tangentSpeed ) SGS_ALIAS( float32 tangentSpeed );
	
	b2Contact* m_contact;
};


struct Box2DDraw : b2Draw
{
	SGS_OBJECT;
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DDraw* dw = (Box2DDraw*) obj->data;
		dw->data.gcmark();
		dw->fnDrawPolygon.gcmark();
		dw->fnDrawSolidPolygon.gcmark();
		dw->fnDrawCircle.gcmark();
		dw->fnDrawSolidCircle.gcmark();
		dw->fnDrawSegment.gcmark();
		dw->fnDrawTransform.gcmark();
		return SGS_SUCCESS;
	}
	
	sgsVariable GetScriptedObject(){ return sgsHandle< Box2DDraw >( this ).get_variable(); }
	SGS_PROPERTY_FUNC( READ GetFlags WRITE SetFlags ) SGS_ALIAS( uint32_t flags );
	
	bool _getDrawShapes(){ return !!( GetFlags() & e_shapeBit ); }
	bool _getDrawJoints(){ return !!( GetFlags() & e_jointBit ); }
	bool _getDrawAABBs(){ return !!( GetFlags() & e_aabbBit ); }
	bool _getDrawPairs(){ return !!( GetFlags() & e_pairBit ); }
	bool _getDrawCenters(){ return !!( GetFlags() & e_centerOfMassBit ); }
	void _setDrawShapes( bool v ){ if( v ) AppendFlags( e_shapeBit ); else ClearFlags( e_shapeBit ); }
	void _setDrawJoints( bool v ){ if( v ) AppendFlags( e_jointBit ); else ClearFlags( e_jointBit ); }
	void _setDrawAABBs( bool v ){ if( v ) AppendFlags( e_aabbBit ); else ClearFlags( e_aabbBit ); }
	void _setDrawPairs( bool v ){ if( v ) AppendFlags( e_pairBit ); else ClearFlags( e_pairBit ); }
	void _setDrawCenters( bool v ){ if( v ) AppendFlags( e_centerOfMassBit ); else ClearFlags( e_centerOfMassBit ); }
	SGS_PROPERTY_FUNC( READ _getDrawShapes WRITE _setDrawShapes ) SGS_ALIAS( bool drawShapes );
	SGS_PROPERTY_FUNC( READ _getDrawJoints WRITE _setDrawJoints ) SGS_ALIAS( bool drawJoints );
	SGS_PROPERTY_FUNC( READ _getDrawAABBs WRITE _setDrawAABBs ) SGS_ALIAS( bool drawAABBs );
	SGS_PROPERTY_FUNC( READ _getDrawPairs WRITE _setDrawPairs ) SGS_ALIAS( bool drawPairs );
	SGS_PROPERTY_FUNC( READ _getDrawCenters WRITE _setDrawCenters ) SGS_ALIAS( bool drawCenters );
	
	SGS_PROPERTY sgsVariable data;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME DrawPolygon ) sgsVariable fnDrawPolygon;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME DrawSolidPolygon ) sgsVariable fnDrawSolidPolygon;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME DrawCircle ) sgsVariable fnDrawCircle;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME DrawSolidCircle ) sgsVariable fnDrawSolidCircle;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME DrawSegment ) sgsVariable fnDrawSegment;
	SGS_PROPERTY_FUNC( READ WRITE VARNAME DrawTransform ) sgsVariable fnDrawTransform;
	
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if( fnDrawPolygon.not_null() )
		{
			SGS_SCOPE;
			for( int32 i = 0; i < vertexCount; ++i )
				sgs_PushVar( C, vertices[i] );
			sgs_CreateArray( C, NULL, vertexCount );
			sgs_PushVar( C, color );
			GetScriptedObject().thiscall( C, fnDrawPolygon, 2 );
		}
	}
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		if( fnDrawSolidPolygon.not_null() )
		{
			SGS_SCOPE;
			for( int32 i = 0; i < vertexCount; ++i )
				sgs_PushVar( C, vertices[i] );
			sgs_CreateArray( C, NULL, vertexCount );
			sgs_PushVar( C, color );
			GetScriptedObject().thiscall( C, fnDrawSolidPolygon, 2 );
		}
	}
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		if( fnDrawCircle.not_null() )
		{
			SGS_SCOPE;
			sgs_PushVar( C, center );
			sgs_PushVar( C, radius );
			sgs_PushVar( C, color );
			GetScriptedObject().thiscall( C, fnDrawCircle, 3 );
		}
	}
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		if( fnDrawSolidCircle.not_null() )
		{
			SGS_SCOPE;
			sgs_PushVar( C, center );
			sgs_PushVar( C, radius );
			sgs_PushVar( C, axis );
			sgs_PushVar( C, color );
			GetScriptedObject().thiscall( C, fnDrawSolidCircle, 4 );
		}
	}
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		if( fnDrawSegment.not_null() )
		{
			SGS_SCOPE;
			sgs_PushVar( C, p1 );
			sgs_PushVar( C, p2 );
			sgs_PushVar( C, color );
			GetScriptedObject().thiscall( C, fnDrawSegment, 4 );
		}
	}
	void DrawTransform(const b2Transform& xf)
	{
		if( fnDrawTransform.not_null() )
		{
			SGS_SCOPE;
			sgs_PushVar( C, Box2DTransform( xf ) );
			GetScriptedObject().thiscall( C, fnDrawTransform, 1 );
		}
	}
};


struct Box2DWorld : b2World
{
	static Box2DWorldHandle HandleFromPtr( b2World* w )
	{
		if( w )
		{
			return Box2DWorldHandle( (Box2DWorld*) w );
		}
		return Box2DWorldHandle();
	}
	
	struct DL : b2DestructionListener
	{
		DL( Box2DWorld* w ) : m_world( w ){}
		void SayGoodbye( b2Joint* joint ){ m_world->SayGoodbye( joint ); }
		void SayGoodbye( b2Fixture* fixture ){ m_world->SayGoodbye( fixture ); }
		Box2DWorld* m_world;
	}
	*m_DL;
	char m_DLmem[ sizeof( DL ) ];
	
	struct CL : b2ContactListener
	{
		CL( Box2DWorld* w ) : m_world( w ){}
		void BeginContact( b2Contact* contact ){ m_world->BeginContact( contact ); }
		void EndContact( b2Contact* contact ){ m_world->EndContact( contact ); }
		void PreSolve( b2Contact* contact, const b2Manifold* oldManifold ){ m_world->PreSolve( contact, oldManifold ); }
		void PostSolve( b2Contact* contact, const b2ContactImpulse* impulse ){ m_world->PostSolve( contact, impulse ); }
		Box2DWorld* m_world;
	}
	*m_CL;
	char m_CLmem[ sizeof( CL ) ];
	
	struct CF : b2ContactFilter
	{
		CF( Box2DWorld* w ) : m_world( w ){}
		bool ShouldCollide( b2Fixture* fixtureA, b2Fixture* fixtureB ){ return m_world->ShouldCollide( fixtureA, fixtureB ); }
		Box2DWorld* m_world;
	}
	*m_CF;
	char m_CFmem[ sizeof( CF ) ];
	
	SGS_OBJECT;
	
	Box2DWorld( const b2Vec2& gravity ) : b2World( gravity )
	{
		m_DL = new (m_DLmem) DL( this );
		GetWorld().SetDestructionListener( m_DL );
		m_CF = new (m_CFmem) CF( this );
		sgs_vht_init( &m_contactSet, C, 4, 4 );
	}
	~Box2DWorld();
	
	SGS_IFUNC( GCMARK ) int gcmark( SGS_CTX, sgs_VarObj* obj )
	{
		Box2DWorld* W = (Box2DWorld*) obj->data;
		W->_debugDraw.gcmark();
		W->destructionListener.gcmark();
		W->contactFilter.gcmark();
		for( sgs_VHTVar* pos = W->m_contactSet.vars, *end = W->m_contactSet.vars + W->m_contactSet.size; pos < end; ++pos )
		{
			sgs_GCMark( C, &pos->key );
			sgs_GCMark( C, &pos->val );
		}
		return SGS_SUCCESS;
	}
	
	void SayGoodbye( b2Joint* joint );
	void SayGoodbye( b2Fixture* fixture );
	void AddContactHandle( Box2DContact* contact );
	void BeginContact( b2Contact* contact );
	void EndContact( b2Contact* contact );
	void PreSolve( b2Contact* contact, const b2Manifold* oldManifold );
	void PostSolve( b2Contact* contact, const b2ContactImpulse* impulse );
	bool ShouldCollide( b2Fixture* fixtureA, b2Fixture* fixtureB );
	
	//
	// METHODS
	//
	// > SetContactListener
	// > SetDebugDraw (AS PROPERTY debugDraw)
	// > CreateBody : returns Box2DBody object
	SGS_METHOD Box2DBodyHandle CreateBody( Box2DBodyDef::Handle bodyDef );
	// > DestroyBody
	SGS_METHOD void DestroyBody( Box2DBodyHandle body );
	// > CreateJoint : returns Box2DJoint object
	SGS_METHOD Box2DJointHandle CreateJoint( sgsVariable jointDef );
	// > DestroyJoint
	SGS_METHOD void DestroyJoint( Box2DJointHandle joint );
	// > Step
	SGS_METHOD void Step( float32 t, int32 vi, int32 pi ){ GetWorld().Step( t, vi, pi ); }
	// > ClearForces
	SGS_METHOD void ClearForces(){ GetWorld().ClearForces(); }
	// > DrawDebugData
	SGS_METHOD void DrawDebugData(){ GetWorld().DrawDebugData(); }
	// > QueryAABB (callback args [1]: fixture)
	SGS_METHOD void QueryAABB( sgsVariable func, b2AABB aabb );
	// > RayCast (callback args [4]: fixture, vec2 point, vec2 normal, real fraction)
	SGS_METHOD void RayCast( sgsVariable func, b2Vec2 p1, b2Vec2 p2 );
	// > ShiftOrigin
	SGS_METHOD void ShiftOrigin( b2Vec2 origin ){ GetWorld().ShiftOrigin( origin ); }
	// > Dump
	SGS_METHOD void Dump(){ GetWorld().Dump(); }
	
	//
	// PROPERTIES
	//
	// > debugDraw
	Box2DDrawHandle _debugDraw;
	Box2DDrawHandle _getDebugDraw(){ return _debugDraw; }
	void _setDebugDraw( Box2DDrawHandle h ){ _debugDraw = h; GetWorld().SetDebugDraw( h ); }
	SGS_PROPERTY_FUNC( READ _getDebugDraw WRITE _setDebugDraw ) SGS_ALIAS( Box2DDrawHandle debugDraw );
	// > READONLY bodyList
	Box2DBodyHandle _getBodyList(){ return Box2DBody::HandleFromPtr( GetWorld().GetBodyList() ); }
	SGS_PROPERTY_FUNC( READ _getBodyList ) SGS_ALIAS( Box2DBodyHandle bodyList );
	// > READONLY contactList
	Box2DContactHandle _getContactList(){ return Box2DContact::HandleFromPtr( GetWorld().GetContactList(), &GetWorld() ); }
	SGS_PROPERTY_FUNC( READ _getContactList ) SGS_ALIAS( Box2DContactHandle contactList );
	// > READONLY jointList
	Box2DJointHandle _getJointList(){ return Box2DJoint::HandleFromPtr( GetWorld().GetJointList() ); }
	SGS_PROPERTY_FUNC( READ _getJointList ) SGS_ALIAS( Box2DJointHandle jointList );
	// > allowSleeping
	bool _getAllowSleeping(){ return GetWorld().GetAllowSleeping(); }
	void _setAllowSleeping( bool b ){ GetWorld().SetAllowSleeping( b ); }
	SGS_PROPERTY_FUNC( READ _getAllowSleeping WRITE _setAllowSleeping ) SGS_ALIAS( bool allowSleeping );
	// > warmStarting
	bool _getWarmStarting(){ return GetWorld().GetWarmStarting(); }
	void _setWarmStarting( bool b ){ GetWorld().SetWarmStarting( b ); }
	SGS_PROPERTY_FUNC( READ _getWarmStarting WRITE _setWarmStarting ) SGS_ALIAS( bool warmStarting );
	// > continuousPhysics
	bool _getContinuousPhysics(){ return GetWorld().GetContinuousPhysics(); }
	void _setContinuousPhysics( bool b ){ GetWorld().SetContinuousPhysics( b ); }
	SGS_PROPERTY_FUNC( READ _getContinuousPhysics WRITE _setContinuousPhysics ) SGS_ALIAS( bool continuousPhysics );
	// > subStepping
	bool _getSubStepping(){ return GetWorld().GetSubStepping(); }
	void _setSubStepping( bool b ){ GetWorld().SetSubStepping( b ); }
	SGS_PROPERTY_FUNC( READ _getSubStepping WRITE _setSubStepping ) SGS_ALIAS( bool subStepping );
	// > autoClearForces
	bool _getAutoClearForces(){ return GetWorld().GetAutoClearForces(); }
	void _setAutoClearForces( bool b ){ GetWorld().SetAutoClearForces( b ); }
	SGS_PROPERTY_FUNC( READ _getAutoClearForces WRITE _setAutoClearForces ) SGS_ALIAS( bool autoClearForces );
	// > READONLY proxyCount
	int32 _getProxyCount(){ return GetWorld().GetProxyCount(); }
	SGS_PROPERTY_FUNC( READ _getProxyCount ) SGS_ALIAS( int32 proxyCount );
	// > READONLY bodyCount
	int32 _getBodyCount(){ return GetWorld().GetBodyCount(); }
	SGS_PROPERTY_FUNC( READ _getBodyCount ) SGS_ALIAS( int32 bodyCount );
	// > READONLY jointCount
	int32 _getJointCount(){ return GetWorld().GetJointCount(); }
	SGS_PROPERTY_FUNC( READ _getJointCount ) SGS_ALIAS( int32 jointCount );
	// > READONLY contactCount
	int32 _getContactCount(){ return GetWorld().GetContactCount(); }
	SGS_PROPERTY_FUNC( READ _getContactCount ) SGS_ALIAS( int32 contactCount );
	// > READONLY treeHeight
	int32 _getTreeHeight(){ return GetWorld().GetTreeHeight(); }
	SGS_PROPERTY_FUNC( READ _getTreeHeight ) SGS_ALIAS( int32 treeHeight );
	// > READONLY treeBalance
	int32 _getTreeBalance(){ return GetWorld().GetTreeBalance(); }
	SGS_PROPERTY_FUNC( READ _getTreeBalance ) SGS_ALIAS( int32 treeBalance );
	// > READONLY treeQuality
	float32 _getTreeQuality(){ return GetWorld().GetTreeQuality(); }
	SGS_PROPERTY_FUNC( READ _getTreeQuality ) SGS_ALIAS( float32 treeQuality );
	// > gravity
	b2Vec2 _getGravity(){ return GetWorld().GetGravity(); }
	void _setGravity( const b2Vec2& v ){ GetWorld().SetGravity( v ); }
	SGS_PROPERTY_FUNC( READ _getGravity WRITE _setGravity ) SGS_ALIAS( b2Vec2 gravity );
	
	// > destructionListener
	SGS_PROPERTY sgsVariable destructionListener;
	// > contactFilter
	void _changeContactFilter(){ GetWorld().SetContactFilter( sgs_IsCallableP( &contactFilter.var ) ? m_CF : NULL ); }
	SGS_PROPERTY_FUNC( READ WRITE WRITE_CALLBACK _changeContactFilter ) sgsVariable contactFilter;
	
	b2World& GetWorld(){ return *this; }
	
	sgs_VHTable m_contactSet;
};



// functions that depend on types declared after their declarations
inline Box2DBodyHandle Box2DFixture::_getBody(){ if( m_fixture ) return Box2DBody::HandleFromPtr( m_fixture->GetBody() ); return Box2DBodyHandle(); }
inline Box2DWorldHandle Box2DBody::_getWorld(){ if( m_body ) return Box2DWorld::HandleFromPtr( m_body->GetWorld() ); return Box2DWorldHandle(); }

