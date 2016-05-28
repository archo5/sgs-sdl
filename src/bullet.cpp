

#include <stdio.h>

#include "bullet.hpp"



bool BulletStridingMeshInterface::Match( sgs_ObjInterface* iface )
{
	return
		iface == BulletTriangleMesh::_sgs_interface
	;
}


BulletCollisionShape::~BulletCollisionShape()
{
	delete m_colShape;
}

bool BulletCollisionShape::Match( sgs_ObjInterface* iface )
{
	return
		iface == BulletSphereShape::_sgs_interface ||
		iface == BulletCapsuleShapeX::_sgs_interface ||
		iface == BulletCapsuleShapeY::_sgs_interface ||
		iface == BulletCapsuleShapeZ::_sgs_interface ||
		iface == BulletBoxShape::_sgs_interface ||
		iface == BulletConvexHullShape::_sgs_interface ||
		iface == BulletStaticPlaneShape::_sgs_interface ||
		iface == BulletBVHTriangleMeshShape::_sgs_interface
	;
}

bool BulletConvexShape::Match( sgs_ObjInterface* iface )
{
	return
		iface == BulletSphereShape::_sgs_interface ||
		iface == BulletCapsuleShapeX::_sgs_interface ||
		iface == BulletCapsuleShapeY::_sgs_interface ||
		iface == BulletCapsuleShapeZ::_sgs_interface ||
		iface == BulletBoxShape::_sgs_interface ||
		iface == BulletConvexHullShape::_sgs_interface
	;
}


bool BulletCollisionObject::Match( sgs_ObjInterface* iface )
{
	return
		iface == BulletRigidBody::_sgs_interface ||
		iface == BulletGhostObject::_sgs_interface
	;
}


BulletRigidBody::BulletRigidBody( BulletRigidBodyCreationInfo* info )
{
	m_world = NULL;
	info->m_motionState = new btDefaultMotionState( info->m_startWorldTransform );
	m_body = new btRigidBody( *info );
	m_body->setUserPointer( this );
	BTCS_Acquire( C, info->m_collisionShape );
}

BulletRigidBody::~BulletRigidBody()
{
	if( m_world )
	{
		m_world->m_world->removeRigidBody( m_body );
	}
	btMotionState* mstate = m_body->getMotionState();
	delete m_body;
	delete mstate;
}


BulletGhostObject::BulletGhostObject()
{
	m_world = NULL;
	m_ghobj = new btGhostObject();
}

BulletGhostObject::~BulletGhostObject()
{
	if( m_world )
		m_world->m_world->removeCollisionObject( m_ghobj );
	delete m_ghobj;
}


BulletDynamicsWorld::BulletDynamicsWorld()
{
	m_broadphase = new btDbvtBroadphase();
	m_collisionConfig = new btDefaultCollisionConfiguration();
	m_collisionDispatcher = new btCollisionDispatcher( m_collisionConfig );
	m_constraintSolver = new btSequentialImpulseConstraintSolver;
	m_world = new btDiscreteDynamicsWorld
	(
		m_collisionDispatcher,
		m_broadphase,
		m_constraintSolver,
		m_collisionConfig
	);
	m_world->setWorldUserInfo( this );
	m_world->setGravity( btVector3(0,0,0) );
}

BulletDynamicsWorld::~BulletDynamicsWorld()
{
	btCollisionObjectArray& coa = m_world->getCollisionObjectArray();
	for( int i = 0; i < coa.size(); ++i )
	{
		BulletCollisionObject* co = (BulletCollisionObject*) coa[i]->getUserPointer();
		co->m_world = NULL;
	}
	delete m_world;
	delete m_constraintSolver;
	delete m_collisionDispatcher;
	delete m_collisionConfig;
	delete m_broadphase;
}

void BulletDynamicsWorld::addRigidBody( BulletRigidBodyHandle rbh, int group, int mask )
{
	int ssz = sgs_StackSize( C );
	if( ssz < 2 ) group = btBroadphaseProxy::DefaultFilter;
	if( ssz < 3 ) mask = btBroadphaseProxy::AllFilter;
	if( !rbh.not_null() )
	{
		sgs_Msg( C, SGS_WARNING, "argument 1 must be a rigid body" );
		return;
	}
	if( rbh->m_world )
		m_world->removeRigidBody( rbh->rigidBody() );
	m_world->addRigidBody( rbh->rigidBody(), group, mask );
	rbh->m_world = this;
}

void BulletDynamicsWorld::removeRigidBody( BulletRigidBodyHandle rbh )
{
	if( !rbh.not_null() )
	{
		sgs_Msg( C, SGS_WARNING, "argument 1 must be a rigid body" );
		return;
	}
	if( rbh->m_world == this )
	{
		m_world->removeRigidBody( rbh->rigidBody() );
		rbh->m_world = NULL;
	}
}

void BulletDynamicsWorld::updateSingleAABB( sgsVariable colObj )
{
	BulletCollisionObject* coptr = NULL;
	if( colObj.is_handle< BulletRigidBody >() )
		coptr = colObj.get_object_data< BulletRigidBody >();
	else if( colObj.is_handle< BulletGhostObject >() )
		coptr = colObj.get_object_data< BulletGhostObject >();
	else
	{
		sgs_Msg( C, SGS_WARNING, "argument 1 must be a rigid body / ghost object" );
		return;
	}
	m_world->updateSingleAabb( coptr->m_colObj );
}

SGS_MULTRET BulletDynamicsWorld::rayTestClosest( const btVector3& from, const btVector3& to, int group, int mask )
{
	int ssz = sgs_StackSize( C );
	if( ssz < 3 ) group = btBroadphaseProxy::DefaultFilter;
	if( ssz < 4 ) mask = btBroadphaseProxy::AllFilter;
	btCollisionWorld::ClosestRayResultCallback crrc( from, to );
	crrc.m_collisionFilterGroup = group;
	crrc.m_collisionFilterMask = mask;
	m_world->rayTest( from, to, crrc );
	
	if( crrc.hasHit() )
	{
		sgs_PushVar( C, crrc.m_closestHitFraction );
		sgs_PushVar( C, (BulletCollisionObjectPointer) crrc.m_collisionObject );
		sgs_PushVar( C, crrc.m_hitNormalWorld );
		sgs_PushVar( C, crrc.m_hitPointWorld );
		return 4;
	}
	return 0;
}

sgsVariable BulletDynamicsWorld::rayTestAll( const btVector3& from, const btVector3& to, int group, int mask )
{
	if( from == to )
	{
		sgs_Msg( C, SGS_WARNING, "from / to positions cannot match" );
		return sgsVariable();
	}
	int ssz = sgs_StackSize( C );
	if( ssz < 3 ) group = btBroadphaseProxy::DefaultFilter;
	if( ssz < 4 ) mask = btBroadphaseProxy::AllFilter;
	btCollisionWorld::AllHitsRayResultCallback ahrrc( from, to );
	ahrrc.m_collisionFilterGroup = group;
	ahrrc.m_collisionFilterMask = mask;
	m_world->rayTest( from, to, ahrrc );
	
	if( ahrrc.hasHit() )
	{
		int i = 0;
		for( ; i < ahrrc.m_collisionObjects.size(); ++i )
		{
			sgs_PushVar( C, ahrrc.m_hitFractions[ i ] );
			sgs_PushVar( C, (BulletCollisionObjectPointer) ahrrc.m_collisionObjects[ i ] );
			sgs_PushVar( C, ahrrc.m_hitNormalWorld[ i ] );
			sgs_PushVar( C, ahrrc.m_hitPointWorld[ i ] );
			sgs_CreateArray( C, NULL, 4 );
		}
		sgs_CreateArray( C, NULL, i );
		return sgsVariable( C, -1 );
	}
	return sgsVariable();
}

void BulletDynamicsWorld::rayTestCustom( const btVector3& from, const btVector3& to, int group, int mask, sgsVariable callback )
{
}

SGS_MULTRET BulletDynamicsWorld::convexSweepTestClosest( BulletConvexShapePointer bcsp, const BulletTransform& from, const BulletTransform& to, int group, int mask, float alcp )
{
	if( !bcsp )
		return sgs_Msg( C, SGS_WARNING, "argument 1 must be a convex shape" );
	if( from.getOrigin() == to.getOrigin() )
		return sgs_Msg( C, SGS_WARNING, "from / to positions cannot match" );
	int ssz = sgs_StackSize( C );
	if( ssz < 4 ) group = btBroadphaseProxy::DefaultFilter;
	if( ssz < 5 ) mask = btBroadphaseProxy::AllFilter;
	btCollisionWorld::ClosestConvexResultCallback ccrc( from.getOrigin(), to.getOrigin() );
	ccrc.m_collisionFilterGroup = group;
	ccrc.m_collisionFilterMask = mask;
	m_world->convexSweepTest( bcsp, from, to, ccrc, alcp );
	
	if( ccrc.hasHit() )
	{
		sgs_PushVar( C, ccrc.m_closestHitFraction );
		sgs_PushVar( C, (BulletCollisionObjectPointer) ccrc.m_hitCollisionObject );
		sgs_PushVar( C, ccrc.m_hitNormalWorld );
		sgs_PushVar( C, ccrc.m_hitPointWorld );
		return 4;
	}
	return 0;
}

void BulletDynamicsWorld::convexSweepTestCustom( BulletConvexShapePointer bcsp, const BulletTransform& from, const BulletTransform& to, int group, int mask, sgsVariable callback, float alcp )
{
}

void BulletDynamicsWorld::addCollisionObject( sgsVariable colObj, int group, int mask )
{
	int ssz = sgs_StackSize( C );
	if( ssz < 2 ) group = btBroadphaseProxy::DefaultFilter;
	if( ssz < 3 ) mask = btBroadphaseProxy::AllFilter;
	BulletCollisionObject* coptr = NULL;
	if( colObj.is_handle< BulletRigidBody >() )
		coptr = colObj.get_object_data< BulletRigidBody >();
	else if( colObj.is_handle< BulletGhostObject >() )
		coptr = colObj.get_object_data< BulletGhostObject >();
	else
	{
		sgs_Msg( C, SGS_WARNING, "argument 1 must be a rigid body / ghost object" );
		return;
	}
	if( coptr->m_world )
		m_world->removeCollisionObject( coptr->m_colObj );
	m_world->addCollisionObject( coptr->m_colObj, group, mask );
	coptr->m_world = this;
}

void BulletDynamicsWorld::removeCollisionObject( sgsVariable colObj )
{
	BulletCollisionObject* coptr = NULL;
	if( colObj.is_handle< BulletRigidBody >() )
		coptr = colObj.get_object_data< BulletRigidBody >();
	else if( colObj.is_handle< BulletGhostObject >() )
		coptr = colObj.get_object_data< BulletGhostObject >();
	else
	{
		sgs_Msg( C, SGS_WARNING, "argument 1 must be a rigid body / ghost object" );
		return;
	}
	if( coptr->m_world == this )
	{
		m_world->removeCollisionObject( coptr->m_colObj );
		coptr->m_world = NULL;
	}
}


static int Bullet_CreateTransform( SGS_CTX )
{
	float pos[3] = {0,0,0};
	SGSFN( "Bullet_CreateTransform" );
	if( !sgs_LoadArgs( C, "|!x", sgs_ArgCheck_Vec3, pos ) )
		return 0;
	SGS_CREATELITECLASS( C, NULL, BulletTransform, ( btTransform( btQuaternion::getIdentity(), btVector3( pos[0], pos[1], pos[2] ) ) ) );
	return 1;
}

static int Bullet_CreateTriangleMesh( SGS_CTX )
{
	sgs_Bool i32 = 0, v4c = 1;
	SGSFN( "Bullet_CreateTriangleMesh" );
	if( !sgs_LoadArgs( C, "b|b", &i32, &v4c ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletTriangleMesh, ( i32, v4c ) );
	return 1;
}

static int Bullet_CreateSphereShape( SGS_CTX )
{
	float radius = 1.0f;
	SGSFN( "Bullet_CreateSphereShape" );
	if( !sgs_LoadArgs( C, "f", &radius ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletSphereShape, ( radius ) );
	return 1;
}

static int Bullet_CreateBoxShape( SGS_CTX )
{
	float he[3] = {1,1,1};
	SGSFN( "Bullet_CreateBoxShape" );
	if( !sgs_LoadArgs( C, "fff", he+0, he+1, he+2 ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletBoxShape, ( btVector3( he[0], he[1], he[2] ) ) );
	return 1;
}

static int Bullet_CreateBoxShapeV3( SGS_CTX )
{
	float he[3] = {1,1,1};
	SGSFN( "Bullet_CreateBoxShapeV3" );
	if( !sgs_LoadArgs( C, "!x", sgs_ArgCheck_Vec3, he ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletBoxShape, ( btVector3( he[0], he[1], he[2] ) ) );
	return 1;
}

static int Bullet_CreateCapsuleShapeX( SGS_CTX )
{
	float radius = 1.0f, height = 1.0f;
	SGSFN( "Bullet_CreateCapsuleShapeX" );
	if( !sgs_LoadArgs( C, "ff", &radius, &height ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletCapsuleShapeX, ( radius, height ) );
	return 1;
}

static int Bullet_CreateCapsuleShapeY( SGS_CTX )
{
	float radius = 1.0f, height = 1.0f;
	SGSFN( "Bullet_CreateCapsuleShapeY" );
	if( !sgs_LoadArgs( C, "ff", &radius, &height ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletCapsuleShapeY, ( radius, height ) );
	return 1;
}

static int Bullet_CreateCapsuleShapeZ( SGS_CTX )
{
	float radius = 1.0f, height = 1.0f;
	SGSFN( "Bullet_CreateCapsuleShapeZ" );
	if( !sgs_LoadArgs( C, "ff", &radius, &height ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletCapsuleShapeZ, ( radius, height ) );
	return 1;
}

static int Bullet_CreateConvexHullShape( SGS_CTX )
{
	SGSFN( "Bullet_CreateConvexHullShape" );
	SGS_CREATECLASS( C, NULL, BulletConvexHullShape, () );
	return 1;
}

static int Bullet_CreateBVHTriangleMeshShape( SGS_CTX )
{
	sgs_Bool qbbc = 0, build = 1;
	SGSFN( "Bullet_CreateBVHTriangleMeshShape" );
	if( !sgs_LoadArgs( C, ">|bb", &qbbc, &build ) )
		return 0;
	BulletStridingMeshInterfaceHandle bsmih = sgs_GetVar<BulletStridingMeshInterfaceHandle>()( C, 0 );
	if( !bsmih.obj )
		return sgs_Msg( C, SGS_WARNING, "argument 1 must be a striding mesh interface object" );
	SGS_CREATECLASS( C, NULL, BulletBVHTriangleMeshShape, ( bsmih, qbbc, build ) );
	return 1;
}

static int Bullet_CreateRigidBodyCreationInfo( SGS_CTX )
{
	SGSFN( "Bullet_CreateRigidBodyCreationInfo" );
	SGS_CREATECLASS( C, NULL, BulletRigidBodyCreationInfo, () );
	return 1;
}

static int Bullet_CreateRigidBody( SGS_CTX )
{
	BulletRigidBodyCreationInfo* rbci;
	SGSFN( "Bullet_CreateRigidBody" );
	if( !sgs_LoadArgs( C, "!o", &BulletRigidBodyCreationInfo::_sgs_interface.iface, &rbci ) )
		return 0;
	SGS_CREATECLASS( C, NULL, BulletRigidBody, ( rbci ) );
	return 1;
}

static int Bullet_CreateGhostObject( SGS_CTX )
{
	SGSFN( "Bullet_CreateGhostObject" );
	SGS_CREATECLASS( C, NULL, BulletGhostObject, () );
	return 1;
}

static int Bullet_CreateWorld( SGS_CTX )
{
	SGSFN( "Bullet_CreateWorld" );
	SGS_CREATECLASS( C, NULL, BulletDynamicsWorld, () );
	return 1;
}


static sgs_RegFuncConst g_fc[] =
{
	{ "Bullet_CreateTransform", Bullet_CreateTransform },
	{ "Bullet_CreateTriangleMesh", Bullet_CreateTriangleMesh },
	
	{ "Bullet_CreateSphereShape", Bullet_CreateSphereShape },
	{ "Bullet_CreateBoxShape", Bullet_CreateBoxShape },
	{ "Bullet_CreateBoxShapeV3", Bullet_CreateBoxShapeV3 },
	{ "Bullet_CreateCapsuleShapeX", Bullet_CreateCapsuleShapeX },
	{ "Bullet_CreateCapsuleShapeY", Bullet_CreateCapsuleShapeY },
	{ "Bullet_CreateCapsuleShapeZ", Bullet_CreateCapsuleShapeZ },
	{ "Bullet_CreateConvexHullShape", Bullet_CreateConvexHullShape },
	{ "Bullet_CreateBVHTriangleMeshShape", Bullet_CreateBVHTriangleMeshShape },
	
	{ "Bullet_CreateRigidBodyCreationInfo", Bullet_CreateRigidBodyCreationInfo },
	{ "Bullet_CreateRigidBody", Bullet_CreateRigidBody },
	{ "Bullet_CreateGhostObject", Bullet_CreateGhostObject },
	{ "Bullet_CreateWorld", Bullet_CreateWorld },
};

static sgs_RegIntConst g_ic[] =
{
	{ "Bullet_ACTIVE_TAG", ACTIVE_TAG },
	{ "Bullet_WANTS_DEACTIVATION", WANTS_DEACTIVATION },
	{ "Bullet_DISABLE_DEACTIVATION", DISABLE_DEACTIVATION },
	{ "Bullet_DISABLE_SIMULATION", DISABLE_SIMULATION },
};

extern "C" int sgscript_main( SGS_CTX )
{
	SGS_MODULE_CHECK_VERSION( C );
	sgs_RegFuncConsts( C, g_fc, sizeof(g_fc) / sizeof(g_fc[0]) );
	sgs_RegIntConsts( C, g_ic, sizeof(g_ic) / sizeof(g_ic[0]) );
	return SGS_SUCCESS;
}
