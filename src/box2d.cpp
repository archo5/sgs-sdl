

#include <stdio.h>

#include "box2d.hpp"


Box2DShape::Box2DShape( b2Shape::Type t ) : m_shape( NULL ), m_fixture( NULL ), m_prev( NULL ), m_next( NULL )
{
	switch( t )
	{
	case b2Shape::e_circle:
		m_shape = new b2CircleShape;
		break;
	case b2Shape::e_edge:
		m_shape = new b2EdgeShape;
		break;
	case b2Shape::e_polygon:
		m_shape = new b2PolygonShape;
		break;
	case b2Shape::e_chain:
		m_shape = new b2ChainShape;
		break;
	default:
		// invalid but usable shape object (type = -1)
		break;
	}
}

Box2DShape::Box2DShape( b2Shape* sh, struct Box2DFixture* fx ) : m_shape( sh ), m_fixture( fx ), m_prev( NULL ), m_next( NULL )
{
	m_next = m_fixture->m_shapeList;
	m_fixture->m_shapeList = this;
}

void Box2DShape::_cleanUp()
{
	if( !m_fixture )
		delete m_shape;
	else
	{
		if( m_fixture->m_shapeList == this )
			m_fixture->m_shapeList = m_next;
		else
		{
			if( m_prev ) m_prev->m_next = m_next;
			if( m_next ) m_next->m_prev = m_prev;
		}
	}
	m_fixture = NULL;
	m_shape = NULL;
	m_prev = NULL;
	m_next = NULL;
}

SGS_MULTRET Box2DShape::RayCast( b2Vec2 p1, b2Vec2 p2, float32 maxfract, Box2DTransform tf, int32 ci )
{
	if( m_shape )
	{
		b2RayCastInput rci = { p1, p2, maxfract };
		b2RayCastOutput rco;
		if( m_shape->RayCast( &rco, rci, tf, ci ) )
		{
			sgs_PushBool( C, 1 );
			sgs_PushReal( C, rco.fraction );
			sgs_PushVar( C, rco.normal );
			return 3;
		}
		sgs_PushBool( C, 0 );
		return 1;
	}
	return 0;
}

sgsVariable Box2DShape::ComputeAABB( Box2DTransform tf, int32 ci )
{
	if( m_shape )
	{
		b2AABB bb;
		m_shape->ComputeAABB( &bb, tf, ci );
		sgs_PushVar( C, bb );
		return sgsVariable( C, -1 );
	}
	return sgsVariable();
}

sgsVariable Box2DShape::ComputeMass( float32 density )
{
	if( m_shape )
	{
		b2MassData md;
		m_shape->ComputeMass( &md, density );
		sgs_PushVar( C, Box2DMassData( md ) );
		return sgsVariable( C, -1 );
	}
	return sgsVariable();
}

void Box2DShape::SetEdge( b2Vec2 v1, b2Vec2 v2 )
{
	if( !IsEdgeShape() )
	{
		sgs_Msg( C, SGS_WARNING, "only edge shape supports this operation" );
		return;
	}
	EdgeShape()->Set( v1, v2 );
}

SGS_MULTRET Box2DShape::GetVertexArray()
{
	if( IsPolyShape() )
	{
		b2PolygonShape* ps = PolyShape();
		int32 i, count = ps->m_count;
		for( i = 0; i < count; ++i )
			sgs_CreateVec2( C, NULL, ps->m_vertices[ i ].x, ps->m_vertices[ i ].y );
		sgs_CreateArray( C, NULL, count );
		return 1;
	}
	return 0;
}

SGS_MULTRET Box2DShape::GetVertexFloatArray()
{
	if( IsPolyShape() )
	{
		b2PolygonShape* ps = PolyShape();
		sgs_CreateFloatArray( C, NULL, &ps->m_vertices[0].x, ps->m_count * 2 );
		return 1;
	}
	return 0;
}

void Box2DShape::SetVertices()
{
	if( !IsPolyShape() ){ sgs_Msg( C, SGS_WARNING, "only polygon shape supports this operation" ); return; }
	
	b2Vec2 verts[ b2_maxPolygonVertices ];
	int count = sgs_StackSize( C );
	if( count < 3 || count > b2_maxPolygonVertices )
	{
		sgs_Msg( C, SGS_WARNING, "wrong vertex count (expected range: 3 - %d)", b2_maxPolygonVertices );
		return;
	}
	for( int i = 0; i < count; ++i )
		verts[ i ] = sgs_GetVar<b2Vec2>()( C, i );
	PolyShape()->Set( verts, count );
}

void Box2DShape::SetVerticesFromVec2Array( sgsVariable arr )
{
	if( !IsPolyShape() ){ sgs_Msg( C, SGS_WARNING, "only polygon shape supports this operation" ); return; }
	
	b2Vec2 verts[ b2_maxPolygonVertices ];
	int count = 0;
	
	sgs_PushIterator( C, arr.var );
	while( sgs_IterAdvance( C, sgs_StackItem( C, -1 ) ) > 0 )
	{
		if( count >= b2_maxPolygonVertices )
		{
			sgs_Msg( C, SGS_WARNING, "array too long (limit: %d items)", b2_maxPolygonVertices );
			return;
		}
		sgs_IterPushData( C, sgs_StackItem( C, -1 ), 0, 1 );
		if( !sgs_ParseVec2( C, -1, &verts[ count ].x, 0 ) )
		{
			sgs_Msg( C, SGS_WARNING, "could not parse item %d as vec2", count );
			return;
		}
		sgs_Pop( C, 1 );
	}
	if( count < 3 )
	{
		sgs_Msg( C, SGS_WARNING, "array too short (expected at least 3 items)" );
		return;
	}
	PolyShape()->Set( verts, count );
}

void Box2DShape::SetVerticesFromFloatArray( FloatArray fa )
{
	if( !IsPolyShape() ){ sgs_Msg( C, SGS_WARNING, "only polygon shape supports this operation" ); return; }
	
	int count = fa.count / 2;
	if( count < 3 || count > b2_maxPolygonVertices )
	{
		sgs_Msg( C, SGS_WARNING, "wrong vertex count (expected range: 3 - %d)", b2_maxPolygonVertices );
		return;
	}
	PolyShape()->Set( (b2Vec2*) fa.data, count );
}

void Box2DShape::_createLoopOrChain( bool chain )
{
	if( !IsChainShape() ){ sgs_Msg( C, SGS_WARNING, "only chain shape supports this operation" ); return; }
	
	int count = sgs_StackSize( C );
	if( count < (chain ? 2 : 3) )
	{
		sgs_Msg( C, SGS_WARNING, "wrong vertex count, expected at least %d", (chain ? 2 : 3) );
		return;
	}
	
	b2Vec2* verts = new b2Vec2[ count ];
	for( int i = 0; i < count; ++i )
		verts[ i ] = sgs_GetVar<b2Vec2>()( C, i );
	
	if( chain )
		ChainShape()->CreateChain( verts, count );
	else
		ChainShape()->CreateLoop( verts, count );
	
	delete [] verts;
}

void Box2DShape::_createLoopOrChainFromVec2Array( sgsVariable& arr, bool chain )
{
	if( !IsChainShape() ){ sgs_Msg( C, SGS_WARNING, "only chain shape supports this operation" ); return; }
	
	b2Vec2 vertbuf[ 32 ];
	b2Vec2* verts = vertbuf;
	int count = 0;
	int mem = 32;
	
	sgs_PushIterator( C, arr.var );
	while( sgs_IterAdvance( C, sgs_StackItem( C, -1 ) ) > 0 )
	{
		if( count >= mem )
		{
			int nmem = count * 2;
			b2Vec2* nbuf = new b2Vec2[ nmem ];
			memcpy( nbuf, verts, sizeof(b2Vec2) * count );
			if( verts != vertbuf )
				delete [] verts;
			verts = nbuf;
			mem = nmem;
		}
		sgs_IterPushData( C, sgs_StackItem( C, -1 ), 0, 1 );
		if( !sgs_ParseVec2( C, -1, &verts[ count ].x, 0 ) )
		{
			sgs_Msg( C, SGS_WARNING, "could not parse item %d as vec2", count );
			return;
		}
	}
	if( count < (chain ? 2 : 3) )
	{
		sgs_Msg( C, SGS_WARNING, "array too short (expected at least %d items)", (chain ? 2 : 3) );
		return;
	}
	
	if( chain )
		ChainShape()->CreateChain( verts, count );
	else
		ChainShape()->CreateLoop( verts, count );
	
	if( verts != vertbuf )
		delete [] verts;
}

void Box2DShape::_createLoopOrChainFromFloatArray( FloatArray& fa, bool chain )
{
	if( !IsChainShape() ){ sgs_Msg( C, SGS_WARNING, "only chain shape supports this operation" ); return; }
	
	int count = fa.count / 2;
	if( count < 2 )
	{
		sgs_Msg( C, SGS_WARNING, "wrong vertex count, expected at least 2" );
		return;
	}
	ChainShape()->CreateLoop( (b2Vec2*) fa.data, count );
}

void Box2DShape::CreateLoop()
{
	_createLoopOrChain( false );
}

void Box2DShape::CreateLoopFromVec2Array( sgsVariable arr )
{
	_createLoopOrChainFromVec2Array( arr, false );
}

void Box2DShape::CreateLoopFromFloatArray( FloatArray fa )
{
	_createLoopOrChainFromFloatArray( fa, false );
}

void Box2DShape::CreateChain()
{
	_createLoopOrChain( true );
}

void Box2DShape::CreateChainFromVec2Array( sgsVariable arr )
{
	_createLoopOrChainFromVec2Array( arr, true );
}

void Box2DShape::CreateChainFromFloatArray( FloatArray fa )
{
	_createLoopOrChainFromFloatArray( fa, true );
}

SGS_MULTRET Box2DShape::GetChildEdge( int32 i )
{
	if( !IsChainShape() )
		return sgs_Msg( C, SGS_WARNING, "only chain shape supports this operation" );
	
	b2ChainShape* cs = ChainShape();
	if( i < 0 || i >= cs->m_count - 1 )
		return sgs_Msg( C, SGS_WARNING, "child edge index out of bounds" );
	
	Box2DShape* nsh = SGS_CREATECLASS( C, NULL, Box2DShape, ( b2Shape::e_edge ) );
	cs->GetChildEdge( nsh->EdgeShape(), i );
	return 1;
}


void Box2DFixture::_cleanUp( bool destroy )
{
	if( m_fixture )
	{
		if( destroy )
		{
			while( m_shapeList )
				m_shapeList->_cleanUp();
			m_fixture->GetBody()->DestroyFixture( m_fixture );
		}
		m_fixture = NULL;
		if( sgs_IsCallableP( &onDestroy.var ) )
			onDestroy.call( C );
		sgs_ObjRelease( C, m_sgsObject );
	}
}

SGS_MULTRET Box2DFixture::RayCast( b2Vec2 p1, b2Vec2 p2, float32 maxfract, int32 ci )
{
	if( m_fixture )
	{
		b2RayCastInput rci = { p1, p2, maxfract };
		b2RayCastOutput rco;
		if( m_fixture->RayCast( &rco, rci, ci ) )
		{
			sgs_PushBool( C, 1 );
			sgs_PushReal( C, rco.fraction );
			sgs_PushVar( C, rco.normal );
			return 3;
		}
		sgs_PushBool( C, 0 );
		return 1;
	}
	return 0;
}


void Box2DDistanceJointDef::Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchorA, const b2Vec2& anchorB )
{
	if( !bodyA.object || !bodyB.object || !bodyA->m_body || !bodyB->m_body )
	{
		sgs_Msg( C, SGS_WARNING, "expected bodies at arguments 1 and 2" );
		return;
	}
	this->b2DistanceJointDef::Initialize( bodyA->m_body, bodyB->m_body, anchorA, anchorB );
	_bodyA = bodyA;
	_bodyB = bodyB;
	this->bodyA = NULL;
	this->bodyB = NULL;
}

void Box2DFrictionJointDef::Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor )
{
	if( !bodyA.object || !bodyB.object || !bodyA->m_body || !bodyB->m_body )
	{
		sgs_Msg( C, SGS_WARNING, "expected bodies at arguments 1 and 2" );
		return;
	}
	this->b2FrictionJointDef::Initialize( bodyA->m_body, bodyB->m_body, anchor );
	_bodyA = bodyA;
	_bodyB = bodyB;
	this->bodyA = NULL;
	this->bodyB = NULL;
}

void Box2DMotorJointDef::Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB )
{
	if( !bodyA.object || !bodyB.object || !bodyA->m_body || !bodyB->m_body )
	{
		sgs_Msg( C, SGS_WARNING, "expected bodies at arguments 1 and 2" );
		return;
	}
	this->b2MotorJointDef::Initialize( bodyA->m_body, bodyB->m_body );
	_bodyA = bodyA;
	_bodyB = bodyB;
	this->bodyA = NULL;
	this->bodyB = NULL;
}

void Box2DPrismaticJointDef::Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor, const b2Vec2& axis )
{
	if( !bodyA.object || !bodyB.object || !bodyA->m_body || !bodyB->m_body )
	{
		sgs_Msg( C, SGS_WARNING, "expected bodies at arguments 1 and 2" );
		return;
	}
	this->b2PrismaticJointDef::Initialize( bodyA->m_body, bodyB->m_body, anchor, axis );
	_bodyA = bodyA;
	_bodyB = bodyB;
	this->bodyA = NULL;
	this->bodyB = NULL;
}

void Box2DPulleyJointDef::Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& groundAnchorA,
	const b2Vec2& groundAnchorB, const b2Vec2& anchorA, const b2Vec2& anchorB, float32 ratio )
{
	if( !bodyA.object || !bodyB.object || !bodyA->m_body || !bodyB->m_body )
	{
		sgs_Msg( C, SGS_WARNING, "expected bodies at arguments 1 and 2" );
		return;
	}
	
	b2Vec2 laA = anchorA, laB = anchorB;
	if( sgs_StackSize( C ) < 5 ) laA = bodyA->m_body->GetPosition();
	if( sgs_StackSize( C ) < 6 ) laB = bodyB->m_body->GetPosition();
	if( sgs_StackSize( C ) < 7 ) ratio = 1;
	
	if( ratio <= b2_epsilon )
	{
		sgs_Msg( C, SGS_WARNING, "ratio is too small (must be > b2_epsilon)" );
		return;
	}
	this->b2PulleyJointDef::Initialize( bodyA->m_body, bodyB->m_body, groundAnchorA, groundAnchorB, laA, laB, ratio );
	_bodyA = bodyA;
	_bodyB = bodyB;
	this->bodyA = NULL;
	this->bodyB = NULL;
}

void Box2DRevoluteJointDef::Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor )
{
	if( !bodyA.object || !bodyB.object || !bodyA->m_body || !bodyB->m_body )
	{
		sgs_Msg( C, SGS_WARNING, "expected bodies at arguments 1 and 2" );
		return;
	}
	this->b2RevoluteJointDef::Initialize( bodyA->m_body, bodyB->m_body, anchor );
	_bodyA = bodyA;
	_bodyB = bodyB;
	this->bodyA = NULL;
	this->bodyB = NULL;
}

void Box2DWheelJointDef::Initialize( Box2DBodyHandle bodyA, Box2DBodyHandle bodyB, const b2Vec2& anchor, const b2Vec2& axis )
{
	if( !bodyA.object || !bodyB.object || !bodyA->m_body || !bodyB->m_body )
	{
		sgs_Msg( C, SGS_WARNING, "expected bodies at arguments 1 and 2" );
		return;
	}
	this->b2WheelJointDef::Initialize( bodyA->m_body, bodyB->m_body, anchor, axis );
	_bodyA = bodyA;
	_bodyB = bodyB;
	this->bodyA = NULL;
	this->bodyB = NULL;
}


void Box2DBody::_cleanUp()
{
	if( m_body )
	{
		while( m_body->GetFixtureList() )
			DestroyFixture( Box2DFixture::HandleFromPtr( m_body->GetFixtureList() ) );
		m_body->GetWorld()->DestroyBody( m_body );
		m_body = NULL;
	}
}

Box2DFixtureHandle Box2DBody::CreateFixture( Box2DFixtureDef::Handle def )
{
	if( !def.object )
	{
		sgs_Msg( C, SGS_WARNING, "expected FixtureDef as argument 1" );
		return Box2DFixtureHandle();
	}
	if( m_body )
	{
		def->shape = def->_shape->m_shape;
		b2Fixture* fx = m_body->CreateFixture( def );
		def->shape = NULL;
		Box2DFixture* sgsfx = SGS_CREATECLASS( C, NULL, Box2DFixture, ( fx ) );
		sgsfx->userData = def->_userData;
		sgsfx->onDestroy = def->onDestroy;
		fx->SetUserData( sgsfx );
		sgs_ObjAcquire( C, sgsfx->m_sgsObject );
		return Box2DFixtureHandle( sgsfx );
	}
	return Box2DFixtureHandle();
}

Box2DFixtureHandle Box2DBody::CreateFixtureFromShape( Box2DShapeHandle shape, float32 density )
{
	if( !shape.object )
	{
		sgs_Msg( C, SGS_WARNING, "expected Shape as argument 1" );
		return Box2DFixtureHandle();
	}
	if( m_body )
	{
		b2Fixture* fx = m_body->CreateFixture( shape->m_shape, density );
		Box2DFixture* sgsfx = SGS_CREATECLASS( C, NULL, Box2DFixture, ( fx ) );
		fx->SetUserData( sgsfx );
		sgs_ObjAcquire( C, sgsfx->m_sgsObject );
		return Box2DFixtureHandle( sgsfx );
	}
	return Box2DFixtureHandle();
}

void Box2DBody::DestroyFixture( Box2DFixtureHandle fixture )
{
	if( !fixture.object )
	{
		sgs_Msg( C, SGS_WARNING, "expected Fixture as argument 1" );
		return;
	}
	fixture->_cleanUp();
}

sgsVariable Box2DBody::GetJointList( bool map )
{
	if( !m_body ){ return sgsVariable(); }
	b2JointEdge* edge = m_body->GetJointList();
	int count = 0;
	while( edge )
	{
		if( map )
			Box2DBody::HandleFromPtr( edge->other ).push( C );
		Box2DJoint::HandleFromPtr( edge->joint ).push( C );
		edge = edge->next;
		count++;
	}
	if( map )
		sgs_CreateMap( C, NULL, count * 2 );
	else
		sgs_CreateArray( C, NULL, count );
	return sgsVariable( C, -1 );
}

sgsVariable Box2DBody::GetContactList( bool map )
{
	if( !m_body ){ return sgsVariable(); }
	b2ContactEdge* edge = m_body->GetContactList();
	int count = 0;
	while( edge )
	{
		if( map )
			Box2DBody::HandleFromPtr( edge->other ).push( C );
		Box2DContact::HandleFromPtr( edge->contact, edge->other->GetWorld() ).push( C );
		edge = edge->next;
		count++;
	}
	if( map )
		sgs_CreateMap( C, NULL, count * 2 );
	else
		sgs_CreateArray( C, NULL, count );
	return sgsVariable( C, -1 );
}


void Box2DJoint::_cleanUp( bool destroy )
{
	if( m_joint )
	{
		if( destroy )
			m_joint->GetBodyA()->GetWorld()->DestroyJoint( m_joint );
		m_joint = NULL;
		if( sgs_IsCallableP( &onDestroy.var ) )
			onDestroy.call( C );
	}
}


Box2DContactHandle Box2DContact::HandleFromPtr( b2Contact* contact, b2World* world )
{
	sgs_Variable k = sgs_MakePtr( contact );
	Box2DWorldHandle wh = Box2DWorld::HandleFromPtr( world );
	sgs_VHTVar* pos = sgs_vht_get( &wh->m_contactSet, &k );
	if( pos )
	{
		return Box2DContactHandle( wh->C, &pos->val );
	}
	else
	{
		Box2DContact* cnobj = SGS_CREATECLASS( wh->C, NULL, Box2DContact, () );
		cnobj->m_contact = contact;
		wh->AddContactHandle( cnobj );
		return Box2DContactHandle( cnobj );
	}
}


Box2DWorld::~Box2DWorld()
{
	while( GetWorld().GetJointList() )
		DestroyJoint( Box2DJoint::HandleFromPtr( GetWorld().GetJointList() ) );
	while( GetWorld().GetBodyList() )
		DestroyBody( Box2DBody::HandleFromPtr( GetWorld().GetBodyList() ) );
	m_DL->~DL();
	sgs_vht_free( &m_contactSet, C );
}

void Box2DWorld::SayGoodbye( b2Joint* joint )
{
	Box2DJoint::HandleFromPtr( joint )->_cleanUp( false );
	if( sgs_IsCallableP( &destructionListener.var ) )
		destructionListener.tcall<void>( C, Box2DJoint::HandleFromPtr( joint ) );
}

void Box2DWorld::SayGoodbye( b2Fixture* fixture )
{
	Box2DFixture::HandleFromPtr( fixture )->_cleanUp( false );
	if( sgs_IsCallableP( &destructionListener.var ) )
		destructionListener.tcall<void>( C, Box2DFixture::HandleFromPtr( fixture ) );
}

void Box2DWorld::AddContactHandle( Box2DContact* contact )
{
	sgs_Variable k = sgs_MakePtr( contact->m_contact ), v = sgs_MakeObjPtrNoRef( contact->m_sgsObject );
	sgs_vht_set( &m_contactSet, C, &k, &v );
}

void Box2DWorld::BeginContact( b2Contact* contact )
{
}

void Box2DWorld::EndContact( b2Contact* contact )
{
	sgs_Variable k = sgs_MakePtr( contact );
	sgs_VHTVar* pos = sgs_vht_get( &m_contactSet, &k );
	if( pos )
	{
		Box2DContactHandle( C, pos->val.data.O )->m_contact = NULL;
		sgs_vht_unset( &m_contactSet, C, &k );
	}
}

void Box2DWorld::PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{
}

void Box2DWorld::PostSolve( b2Contact* contact, const b2ContactImpulse* impulse )
{
}

bool Box2DWorld::ShouldCollide( b2Fixture* fixtureA, b2Fixture* fixtureB )
{
	return contactFilter.tcall<bool>( C,
		Box2DFixture::HandleFromPtr( fixtureA ),
		Box2DFixture::HandleFromPtr( fixtureB ) );
}

Box2DBodyHandle Box2DWorld::CreateBody( Box2DBodyDef::Handle bodyDef )
{
	if( !bodyDef.object )
	{
		sgs_Msg( C, SGS_WARNING, "expected BodyDef as argument 1" );
		return Box2DBodyHandle();
	}
	b2Body* body = GetWorld().CreateBody( bodyDef );
	Box2DBody* sgsbody = SGS_CREATECLASS( C, NULL, Box2DBody, ( body ) );
	sgsbody->userData = bodyDef->_userData;
	body->SetUserData( sgsbody );
	return Box2DBodyHandle( sgsbody );
}

void Box2DWorld::DestroyBody( Box2DBodyHandle body )
{
	if( !body.object )
	{
		sgs_Msg( C, SGS_WARNING, "expected body as argument 1" );
		return;
	}
	body->_cleanUp();
}


template< class T > static int sgsb2d_CreateJoint( SGS_CTX, b2World& world, b2Joint*& joint, Box2DJoint*& sgsjoint, T* jdef )
{
	jdef->bodyA = jdef->_bodyA->m_body;
	jdef->bodyB = jdef->_bodyB->m_body;
	
	if( !jdef->bodyA || !jdef->bodyB )
		return sgs_Msg( C, SGS_WARNING, "both bodies must be set for a joint" );
	if( jdef->bodyA == jdef->bodyB )
		return sgs_Msg( C, SGS_WARNING, "same body cannot be used twice in a joint" );
	
	joint = world.CreateJoint( jdef );
	jdef->bodyA = NULL;
	jdef->bodyB = NULL;
	
	sgsjoint = SGS_CREATECLASS( C, NULL, Box2DJoint, ( joint ) );
	sgsjoint->userData = jdef->_userData;
	sgsjoint->onDestroy = jdef->onDestroy;
	return 1;
}

Box2DJointHandle Box2DWorld::CreateJoint( sgsVariable jointDef )
{
	b2Joint* joint;
	Box2DJoint* sgsjoint;
	
	if( jointDef.is_handle< Box2DDistanceJointDef >() )
	{
		Box2DDistanceJointDef* jdef = jointDef.get_object_data< Box2DDistanceJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DFrictionJointDef >() )
	{
		Box2DFrictionJointDef* jdef = jointDef.get_object_data< Box2DFrictionJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DGearJointDef >() )
	{
		sgs_Msg( C, SGS_WARNING, "gear joint is not yet supported" );
		return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DMotorJointDef >() )
	{
		Box2DMotorJointDef* jdef = jointDef.get_object_data< Box2DMotorJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DMouseJointDef >() )
	{
		sgs_Msg( C, SGS_WARNING, "mouse joint is not yet supported" );
		return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DPrismaticJointDef >() )
	{
		Box2DPrismaticJointDef* jdef = jointDef.get_object_data< Box2DPrismaticJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DPulleyJointDef >() )
	{
		Box2DPulleyJointDef* jdef = jointDef.get_object_data< Box2DPulleyJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DRevoluteJointDef >() )
	{
		Box2DRevoluteJointDef* jdef = jointDef.get_object_data< Box2DRevoluteJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DRopeJointDef >() )
	{
		Box2DRopeJointDef* jdef = jointDef.get_object_data< Box2DRopeJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DWeldJointDef >() )
	{
		Box2DWeldJointDef* jdef = jointDef.get_object_data< Box2DWeldJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else if( jointDef.is_handle< Box2DWheelJointDef >() )
	{
		Box2DWheelJointDef* jdef = jointDef.get_object_data< Box2DWheelJointDef >();
		if( !sgsb2d_CreateJoint( C, GetWorld(), joint, sgsjoint, jdef ) )
			return Box2DJointHandle();
	}
	else
	{
		sgs_Msg( C, SGS_WARNING, "expected some jointDef as argument 1" );
		return Box2DJointHandle();
	}
	
	joint->SetUserData( sgsjoint );
	return Box2DJointHandle( sgsjoint );
}

void Box2DWorld::DestroyJoint( Box2DJointHandle joint )
{
	if( !joint.object )
	{
		sgs_Msg( C, SGS_WARNING, "expected joint as argument 1" );
		return;
	}
	joint->_cleanUp();
}

class sgs_b2QueryCallback : public b2QueryCallback
{
public:
	SGS_CTX;
	sgsVariable* var;
	bool ReportFixture( b2Fixture* fixture )
	{
		return var->tcall<bool>( C, Box2DFixture::HandleFromPtr( fixture ) );
	}
};
void Box2DWorld::QueryAABB( sgsVariable func, b2AABB aabb )
{
	sgs_b2QueryCallback cb;
	cb.C = C;
	cb.var = &func;
	GetWorld().QueryAABB( &cb, aabb );
}

class sgs_b2RayCastCallback : public b2RayCastCallback
{
public:
	SGS_CTX;
	sgsVariable* var;
	float32 ReportFixture( b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction )
	{
		return var->tcall<float32>( C, Box2DFixture::HandleFromPtr( fixture ), point, normal, fraction );
	}
};
void Box2DWorld::RayCast( sgsVariable func, b2Vec2 p1, b2Vec2 p2 )
{
	sgs_b2RayCastCallback cb;
	cb.C = C;
	cb.var = &func;
	GetWorld().RayCast( &cb, p1, p2 );
}


static int sgsBox2DRotation( SGS_CTX )
{
	float32 angle;
	SGSFN( "Box2DRotation" );
	if( !sgs_LoadArgs( C, "|f", &angle ) )
		return 0;
	SGS_CREATELITECLASS( C, NULL, Box2DRotation, ( b2Rot( angle ) ) );
	return 1;
}
static int sgsBox2DTransform( SGS_CTX )
{
	b2Vec2 pos(0,0);
	float32 angle;
	SGSFN( "Box2DTransform" );
	if( !sgs_LoadArgs( C, "|xf", sgs_ArgCheck_Vec2, &pos, &angle ) )
		return 0;
	SGS_CREATELITECLASS( C, NULL, Box2DTransform, ( b2Transform( pos, b2Rot( angle ) ) ) );
	return 1;
}

static int Box2D_CreateCircleShape( SGS_CTX ){ SGSFN( "Box2D_CreateCircleShape" ); SGS_CREATECLASS( C, NULL, Box2DShape, ( b2Shape::e_circle ) ); return 1; }
static int Box2D_CreateEdgeShape( SGS_CTX ){ SGSFN( "Box2D_CreateEdgeShape" ); SGS_CREATECLASS( C, NULL, Box2DShape, ( b2Shape::e_edge ) ); return 1; }
static int Box2D_CreatePolygonShape( SGS_CTX ){ SGSFN( "Box2D_CreatePolygonShape" ); SGS_CREATECLASS( C, NULL, Box2DShape, ( b2Shape::e_polygon ) ); return 1; }
static int Box2D_CreateChainShape( SGS_CTX ){ SGSFN( "Box2D_CreateChainShape" ); SGS_CREATECLASS( C, NULL, Box2DShape, ( b2Shape::e_chain ) ); return 1; }

static int Box2D_CreateFixtureDef( SGS_CTX ){ SGSFN( "Box2D_CreateFixtureDef" ); SGS_CREATECLASS( C, NULL, Box2DFixtureDef, () ); return 1; }
static int Box2D_CreateBodyDef( SGS_CTX ){ SGSFN( "Box2D_CreateBodyDef" ); SGS_CREATECLASS( C, NULL, Box2DBodyDef, () ); return 1; }
static int Box2D_CreateDistanceJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateDistanceJointDef" ); SGS_CREATECLASS( C, NULL, Box2DDistanceJointDef, () ); return 1; }
static int Box2D_CreateFrictionJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateFrictionJointDef" ); SGS_CREATECLASS( C, NULL, Box2DFrictionJointDef, () ); return 1; }
static int Box2D_CreateGearJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateGearJointDef" ); SGS_CREATECLASS( C, NULL, Box2DGearJointDef, () ); return 1; }
static int Box2D_CreateMotorJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateMotorJointDef" ); SGS_CREATECLASS( C, NULL, Box2DMotorJointDef, () ); return 1; }
static int Box2D_CreateMouseJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateMouseJointDef" ); SGS_CREATECLASS( C, NULL, Box2DMouseJointDef, () ); return 1; }
static int Box2D_CreatePrismaticJointDef( SGS_CTX ){ SGSFN( "Box2D_CreatePrismaticJointDef" ); SGS_CREATECLASS( C, NULL, Box2DPrismaticJointDef, () ); return 1; }
static int Box2D_CreatePulleyJointDef( SGS_CTX ){ SGSFN( "Box2D_CreatePulleyJointDef" ); SGS_CREATECLASS( C, NULL, Box2DPulleyJointDef, () ); return 1; }
static int Box2D_CreateRevoluteJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateRevoluteJointDef" ); SGS_CREATECLASS( C, NULL, Box2DRevoluteJointDef, () ); return 1; }
static int Box2D_CreateRopeJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateRopeJointDef" ); SGS_CREATECLASS( C, NULL, Box2DRopeJointDef, () ); return 1; }
static int Box2D_CreateWeldJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateWeldJointDef" ); SGS_CREATECLASS( C, NULL, Box2DWeldJointDef, () ); return 1; }
static int Box2D_CreateWheelJointDef( SGS_CTX ){ SGSFN( "Box2D_CreateWheelJointDef" ); SGS_CREATECLASS( C, NULL, Box2DWheelJointDef, () ); return 1; }

static int Box2D_CreateDraw( SGS_CTX ){ SGSFN( "Box2D_CreateDraw" ); SGS_CREATECLASS( C, NULL, Box2DDraw, () ); return 1; }


#define Box2D_TypeID_Unknown    0
#define Box2D_TypeID_Vec2       1
#define Box2D_TypeID_AABB       2
#define Box2D_TypeID_FloatArray 3
#define Box2D_TypeID_Rotation   4
#define Box2D_TypeID_Transform  5
#define Box2D_TypeID_Draw       31
#define Box2D_TypeID_Contact    32
#define Box2D_TypeID_MassData   51
#define Box2D_TypeID_FilterData 52
#define Box2D_TypeID_FixtureDef 101
#define Box2D_TypeID_DistanceJointDef   121
#define Box2D_TypeID_FrictionJointDef   122
#define Box2D_TypeID_GearJointDef       123
#define Box2D_TypeID_MotorJointDef      124
#define Box2D_TypeID_MouseJointDef      125
#define Box2D_TypeID_PrismaticJointDef  126
#define Box2D_TypeID_PulleyJointDef     127
#define Box2D_TypeID_RevoluteJointDef   128
#define Box2D_TypeID_RopeJointDef       129
#define Box2D_TypeID_WeldJointDef       130
#define Box2D_TypeID_WheelJointDef      131
#define Box2D_TypeID_Shape      151
#define Box2D_TypeID_Fixture    152
#define Box2D_TypeID_Body       153
#define Box2D_TypeID_Joint      154
#define Box2D_TypeID_World      155

static int _box2d_ifp2tid( sgs_ObjInterface* oi )
{
	if( oi == xgm_vec2_iface ) return Box2D_TypeID_Vec2;
	if( oi == xgm_aabb2_iface ) return Box2D_TypeID_AABB;
	if( oi == xgm_floatarr_iface ) return Box2D_TypeID_FloatArray;
	if( oi == Box2DRotation::_sgs_interface ) return Box2D_TypeID_Rotation;
	if( oi == Box2DTransform::_sgs_interface ) return Box2D_TypeID_Transform;
	if( oi == Box2DMassData::_sgs_interface ) return Box2D_TypeID_MassData;
	if( oi == Box2DFilterData::_sgs_interface ) return Box2D_TypeID_FilterData;
	if( oi == Box2DFixtureDef::_sgs_interface ) return Box2D_TypeID_FixtureDef;
	if( oi == Box2DDistanceJointDef::_sgs_interface ) return Box2D_TypeID_DistanceJointDef;
	if( oi == Box2DFrictionJointDef::_sgs_interface ) return Box2D_TypeID_FrictionJointDef;
	if( oi == Box2DGearJointDef::_sgs_interface ) return Box2D_TypeID_GearJointDef;
	if( oi == Box2DMotorJointDef::_sgs_interface ) return Box2D_TypeID_MotorJointDef;
	if( oi == Box2DMouseJointDef::_sgs_interface ) return Box2D_TypeID_MouseJointDef;
	if( oi == Box2DPrismaticJointDef::_sgs_interface ) return Box2D_TypeID_PrismaticJointDef;
	if( oi == Box2DPulleyJointDef::_sgs_interface ) return Box2D_TypeID_PulleyJointDef;
	if( oi == Box2DRevoluteJointDef::_sgs_interface ) return Box2D_TypeID_RevoluteJointDef;
	if( oi == Box2DRopeJointDef::_sgs_interface ) return Box2D_TypeID_RopeJointDef;
	if( oi == Box2DWeldJointDef::_sgs_interface ) return Box2D_TypeID_WeldJointDef;
	if( oi == Box2DWheelJointDef::_sgs_interface ) return Box2D_TypeID_WheelJointDef;
	if( oi == Box2DShape::_sgs_interface ) return Box2D_TypeID_Shape;
	if( oi == Box2DFixture::_sgs_interface ) return Box2D_TypeID_Fixture;
	if( oi == Box2DBody::_sgs_interface ) return Box2D_TypeID_Body;
	if( oi == Box2DJoint::_sgs_interface ) return Box2D_TypeID_Joint;
	if( oi == Box2DContact::_sgs_interface ) return Box2D_TypeID_Contact;
	if( oi == Box2DDraw::_sgs_interface ) return Box2D_TypeID_Draw;
	if( oi == Box2DWorld::_sgs_interface ) return Box2D_TypeID_World;
	return Box2D_TypeID_Unknown;
}

static int Box2D_TypeID( SGS_CTX )
{
	SGSFN( "Box2D_TypeID" );
	sgs_PushInt( C, _box2d_ifp2tid( sgs_ItemType( C, 0 ) == SGS_VT_OBJECT ? sgs_GetObjectIface( C, 0 ) : NULL ) );
	return 1;
}

static int Box2D_CreateWorld( SGS_CTX )
{
	b2Vec2 gravity(0,0);
	
	SGSFN( "Box2D_CreateWorld" );
	if( !sgs_LoadArgs( C, "|x", sgs_ArgCheck_Vec2, &gravity ) )
		return 0;
	
	SGS_CREATECLASS( C, NULL, Box2DWorld, ( gravity ) );
	return 1;
}


static sgs_RegFuncConst g_fc[] =
{
	{ "Box2DRotation", sgsBox2DRotation },
	{ "Box2DTransform", sgsBox2DTransform },
	
	{ "Box2D_CreateCircleShape", Box2D_CreateCircleShape },
	{ "Box2D_CreateEdgeShape", Box2D_CreateEdgeShape },
	{ "Box2D_CreatePolygonShape", Box2D_CreatePolygonShape },
	{ "Box2D_CreateChainShape", Box2D_CreateChainShape },
	
	{ "Box2D_CreateFixtureDef", Box2D_CreateFixtureDef },
	{ "Box2D_CreateBodyDef", Box2D_CreateBodyDef },
	{ "Box2D_CreateDistanceJointDef", Box2D_CreateDistanceJointDef },
	{ "Box2D_CreateFrictionJointDef", Box2D_CreateFrictionJointDef },
	{ "Box2D_CreateGearJointDef", Box2D_CreateGearJointDef },
	{ "Box2D_CreateMotorJointDef", Box2D_CreateMotorJointDef },
	{ "Box2D_CreateMouseJointDef", Box2D_CreateMouseJointDef },
	{ "Box2D_CreatePrismaticJointDef", Box2D_CreatePrismaticJointDef },
	{ "Box2D_CreatePulleyJointDef", Box2D_CreatePulleyJointDef },
	{ "Box2D_CreateRevoluteJointDef", Box2D_CreateRevoluteJointDef },
	{ "Box2D_CreateRopeJointDef", Box2D_CreateRopeJointDef },
	{ "Box2D_CreateWeldJointDef", Box2D_CreateWeldJointDef },
	{ "Box2D_CreateWheelJointDef", Box2D_CreateWheelJointDef },
	
	{ "Box2D_CreateDraw", Box2D_CreateDraw },
	
	{ "Box2D_CreateWorld", Box2D_CreateWorld },
	{ "Box2D_TypeID", Box2D_TypeID },
};

static sgs_RegIntConst g_ic[] =
{
	{ "Box2D_TypeID_Unknown", Box2D_TypeID_Unknown },
	{ "Box2D_TypeID_Vec2", Box2D_TypeID_Vec2 },
	{ "Box2D_TypeID_AABB", Box2D_TypeID_AABB },
	{ "Box2D_TypeID_FloatArray", Box2D_TypeID_FloatArray },
	{ "Box2D_TypeID_Rotation", Box2D_TypeID_Rotation },
	{ "Box2D_TypeID_Transform", Box2D_TypeID_Transform },
	{ "Box2D_TypeID_MassData", Box2D_TypeID_MassData },
	{ "Box2D_TypeID_FilterData", Box2D_TypeID_FilterData },
	{ "Box2D_TypeID_FixtureDef", Box2D_TypeID_FixtureDef },
	{ "Box2D_TypeID_DistanceJointDef", Box2D_TypeID_DistanceJointDef },
	{ "Box2D_TypeID_FrictionJointDef", Box2D_TypeID_FrictionJointDef },
	{ "Box2D_TypeID_GearJointDef", Box2D_TypeID_GearJointDef },
	{ "Box2D_TypeID_MotorJointDef", Box2D_TypeID_MotorJointDef },
	{ "Box2D_TypeID_MouseJointDef", Box2D_TypeID_MouseJointDef },
	{ "Box2D_TypeID_PrismaticJointDef", Box2D_TypeID_PrismaticJointDef },
	{ "Box2D_TypeID_PulleyJointDef", Box2D_TypeID_PulleyJointDef },
	{ "Box2D_TypeID_RevoluteJointDef", Box2D_TypeID_RevoluteJointDef },
	{ "Box2D_TypeID_RopeJointDef", Box2D_TypeID_RopeJointDef },
	{ "Box2D_TypeID_WeldJointDef", Box2D_TypeID_WeldJointDef },
	{ "Box2D_TypeID_WheelJointDef", Box2D_TypeID_WheelJointDef },
	{ "Box2D_TypeID_Shape", Box2D_TypeID_Shape },
	{ "Box2D_TypeID_Fixture", Box2D_TypeID_Fixture },
	{ "Box2D_TypeID_Body", Box2D_TypeID_Body },
	{ "Box2D_TypeID_Joint", Box2D_TypeID_Joint },
	{ "Box2D_TypeID_World", Box2D_TypeID_World },
	
	{ "Box2D_BodyType_Static", b2_staticBody },
	{ "Box2D_BodyType_Kinematic", b2_kinematicBody },
	{ "Box2D_BodyType_Dynamic", b2_dynamicBody },
	
	{ "Box2D_ShapeType_Circle", b2Shape::e_circle },
	{ "Box2D_ShapeType_Edge", b2Shape::e_edge },
	{ "Box2D_ShapeType_Polygon", b2Shape::e_polygon },
	{ "Box2D_ShapeType_Chain", b2Shape::e_chain },
	
	{ "Box2D_JointType_UnknownJoint", e_unknownJoint },
	{ "Box2D_JointType_RevoluteJoint", e_revoluteJoint },
	{ "Box2D_JointType_PrismaticJoint", e_prismaticJoint },
	{ "Box2D_JointType_DistanceJoint", e_distanceJoint },
	{ "Box2D_JointType_PulleyJoint", e_pulleyJoint },
	{ "Box2D_JointType_MouseJoint", e_mouseJoint },
	{ "Box2D_JointType_GearJoint", e_gearJoint },
	{ "Box2D_JointType_WheelJoint", e_wheelJoint },
	{ "Box2D_JointType_WeldJoint", e_weldJoint },
	{ "Box2D_JointType_FrictionJoint", e_frictionJoint },
	{ "Box2D_JointType_RopeJoint", e_ropeJoint },
	{ "Box2D_JointType_MotorJoint", e_motorJoint },
	
	{ "Box2D_LimitState_InactiveLimit", e_inactiveLimit },
	{ "Box2D_LimitState_AtLowerLimit", e_atLowerLimit },
	{ "Box2D_LimitState_AtUpperLimit", e_atUpperLimit },
	{ "Box2D_LimitState_EqualLimits", e_equalLimits },
	
	{ "Box2D_Draw_Shape", b2Draw::e_shapeBit },
	{ "Box2D_Draw_Joint", b2Draw::e_jointBit },
	{ "Box2D_Draw_AABB", b2Draw::e_aabbBit },
	{ "Box2D_Draw_Pair", b2Draw::e_pairBit },
	{ "Box2D_Draw_CenterOfMass", b2Draw::e_centerOfMassBit },
};


extern "C" int sgscript_main( SGS_CTX )
{
	SGS_MODULE_CHECK_VERSION( C );
	sgs_RegFuncConsts( C, g_fc, sizeof(g_fc) / sizeof(g_fc[0]) );
	sgs_RegIntConsts( C, g_ic, sizeof(g_ic) / sizeof(g_ic[0]) );
	return SGS_SUCCESS;
}

