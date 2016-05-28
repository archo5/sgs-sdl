// SGS/CPP-BC
// warning: do not modify this file, it may be regenerated during any build

#include "bullet.hpp"

int BulletTransform::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletTransform*>( obj->data )->~BulletTransform();
	return SGS_SUCCESS;
}

int BulletTransform::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	return SGS_SUCCESS;
}

int BulletTransform::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "origin" ){ sgs_PushVar( C, static_cast<BulletTransform*>( obj->data )->getOrigin() ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ sgs_PushVar( C, static_cast<BulletTransform*>( obj->data )->getOrigin() ); return SGS_SUCCESS; }
		SGS_CASE( "basis" ){ sgs_PushVar( C, static_cast<BulletTransform*>( obj->data )->getBasis() ); return SGS_SUCCESS; }
		SGS_CASE( "orientation" ){ sgs_PushVar( C, static_cast<BulletTransform*>( obj->data )->getRotation() ); return SGS_SUCCESS; }
		SGS_CASE( "rotation" ){ sgs_PushVar( C, static_cast<BulletTransform*>( obj->data )->getRotation() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTransform::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "origin" ){ static_cast<BulletTransform*>( obj->data )->setOrigin( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ static_cast<BulletTransform*>( obj->data )->setOrigin( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "basis" ){ static_cast<BulletTransform*>( obj->data )->setBasis( sgs_GetVar<btMatrix3x3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "orientation" ){ static_cast<BulletTransform*>( obj->data )->setRotation( sgs_GetVar<btQuaternion>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "rotation" ){ static_cast<BulletTransform*>( obj->data )->setRotation( sgs_GetVar<btQuaternion>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTransform::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	char bfr[ 47 ];
	sprintf( bfr, "BulletTransform (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\norigin = " ); sgs_DumpData( C, static_cast<BulletTransform*>( obj->data )->getOrigin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nposition = " ); sgs_DumpData( C, static_cast<BulletTransform*>( obj->data )->getOrigin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbasis = " ); sgs_DumpData( C, static_cast<BulletTransform*>( obj->data )->getBasis(), depth ).push( C ); }
		{ sgs_PushString( C, "\norientation = " ); sgs_DumpData( C, static_cast<BulletTransform*>( obj->data )->getRotation(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrotation = " ); sgs_DumpData( C, static_cast<BulletTransform*>( obj->data )->getRotation(), depth ).push( C ); }
		sgs_StringConcat( C, 10 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletTransform__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int BulletTransform__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletTransform__sgs_funcs,
		-1, "BulletTransform." );
	return 1;
}

static sgs_ObjInterface BulletTransform__sgs_interface =
{
	"BulletTransform",
	BulletTransform::_sgs_destruct, BulletTransform::_sgs_gcmark, BulletTransform::_sgs_getindex, BulletTransform::_sgs_setindex, NULL, NULL, BulletTransform::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletTransform::_sgs_interface(BulletTransform__sgs_interface, BulletTransform__sgs_ifn);


int BulletStridingMeshInterface::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletStridingMeshInterface*>( obj->data )->C = C;
	static_cast<BulletStridingMeshInterface*>( obj->data )->~BulletStridingMeshInterface();
	return SGS_SUCCESS;
}

int BulletStridingMeshInterface::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStridingMeshInterface*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int BulletStridingMeshInterface::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStridingMeshInterface*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "scaling" ){ sgs_PushVar( C, static_cast<BulletStridingMeshInterface*>( obj->data )->_get_scaling() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletStridingMeshInterface::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStridingMeshInterface*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "scaling" ){ static_cast<BulletStridingMeshInterface*>( obj->data )->_set_scaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletStridingMeshInterface::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStridingMeshInterface*>( obj->data )->C, C );
	char bfr[ 59 ];
	sprintf( bfr, "BulletStridingMeshInterface (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nscaling = " ); sgs_DumpData( C, static_cast<BulletStridingMeshInterface*>( obj->data )->_get_scaling(), depth ).push( C ); }
		sgs_StringConcat( C, 2 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletStridingMeshInterface__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int BulletStridingMeshInterface__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletStridingMeshInterface__sgs_funcs,
		-1, "BulletStridingMeshInterface." );
	return 1;
}

static sgs_ObjInterface BulletStridingMeshInterface__sgs_interface =
{
	"BulletStridingMeshInterface",
	BulletStridingMeshInterface::_sgs_destruct, BulletStridingMeshInterface::_sgs_gcmark, BulletStridingMeshInterface::_sgs_getindex, BulletStridingMeshInterface::_sgs_setindex, NULL, NULL, BulletStridingMeshInterface::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletStridingMeshInterface::_sgs_interface(BulletStridingMeshInterface__sgs_interface, BulletStridingMeshInterface__sgs_ifn);


static int _sgs_method__BulletTriangleIndexVertexArray__preallocateVertices( SGS_CTX )
{
	BulletTriangleIndexVertexArray* data; if( !SGS_PARSE_METHOD( C, BulletTriangleIndexVertexArray::_sgs_interface, data, BulletTriangleIndexVertexArray, preallocateVertices ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->preallocateVertices( sgs_GetVar<int>()(C,0) ); return 0;
}

static int _sgs_method__BulletTriangleIndexVertexArray__preallocateIndices( SGS_CTX )
{
	BulletTriangleIndexVertexArray* data; if( !SGS_PARSE_METHOD( C, BulletTriangleIndexVertexArray::_sgs_interface, data, BulletTriangleIndexVertexArray, preallocateIndices ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->preallocateIndices( sgs_GetVar<int>()(C,0) ); return 0;
}

int BulletTriangleIndexVertexArray::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletTriangleIndexVertexArray*>( obj->data )->C = C;
	static_cast<BulletTriangleIndexVertexArray*>( obj->data )->~BulletTriangleIndexVertexArray();
	return SGS_SUCCESS;
}

int BulletTriangleIndexVertexArray::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleIndexVertexArray*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int BulletTriangleIndexVertexArray::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleIndexVertexArray*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "scaling" ){ sgs_PushVar( C, static_cast<BulletTriangleIndexVertexArray*>( obj->data )->_get_scaling() ); return SGS_SUCCESS; }
		SGS_CASE( "numSubParts" ){ sgs_PushVar( C, static_cast<BulletTriangleIndexVertexArray*>( obj->data )->_get_numSubParts() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTriangleIndexVertexArray::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleIndexVertexArray*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "scaling" ){ static_cast<BulletTriangleIndexVertexArray*>( obj->data )->_set_scaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTriangleIndexVertexArray::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleIndexVertexArray*>( obj->data )->C, C );
	char bfr[ 62 ];
	sprintf( bfr, "BulletTriangleIndexVertexArray (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nscaling = " ); sgs_DumpData( C, static_cast<BulletTriangleIndexVertexArray*>( obj->data )->_get_scaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumSubParts = " ); sgs_DumpData( C, static_cast<BulletTriangleIndexVertexArray*>( obj->data )->_get_numSubParts(), depth ).push( C ); }
		sgs_StringConcat( C, 4 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletTriangleIndexVertexArray__sgs_funcs[] =
{
	{ "preallocateVertices", _sgs_method__BulletTriangleIndexVertexArray__preallocateVertices },
	{ "preallocateIndices", _sgs_method__BulletTriangleIndexVertexArray__preallocateIndices },
	{ NULL, NULL },
};

static int BulletTriangleIndexVertexArray__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletTriangleIndexVertexArray__sgs_funcs,
		-1, "BulletTriangleIndexVertexArray." );
	return 1;
}

static sgs_ObjInterface BulletTriangleIndexVertexArray__sgs_interface =
{
	"BulletTriangleIndexVertexArray",
	BulletTriangleIndexVertexArray::_sgs_destruct, BulletTriangleIndexVertexArray::_sgs_gcmark, BulletTriangleIndexVertexArray::_sgs_getindex, BulletTriangleIndexVertexArray::_sgs_setindex, NULL, NULL, BulletTriangleIndexVertexArray::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletTriangleIndexVertexArray::_sgs_interface(BulletTriangleIndexVertexArray__sgs_interface, BulletTriangleIndexVertexArray__sgs_ifn, &BulletStridingMeshInterface::_sgs_interface);


static int _sgs_method__BulletTriangleMesh__preallocateVertices( SGS_CTX )
{
	BulletTriangleMesh* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMesh::_sgs_interface, data, BulletTriangleMesh, preallocateVertices ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->preallocateVertices( sgs_GetVar<int>()(C,0) ); return 0;
}

static int _sgs_method__BulletTriangleMesh__preallocateIndices( SGS_CTX )
{
	BulletTriangleMesh* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMesh::_sgs_interface, data, BulletTriangleMesh, preallocateIndices ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->preallocateIndices( sgs_GetVar<int>()(C,0) ); return 0;
}

static int _sgs_method__BulletTriangleMesh__addTriangle( SGS_CTX )
{
	BulletTriangleMesh* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMesh::_sgs_interface, data, BulletTriangleMesh, addTriangle ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->addTriangle( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<btVector3>()(C,1), sgs_GetVar<btVector3>()(C,2), sgs_GetVar<bool>()(C,3) ); return 0;
}

static int _sgs_method__BulletTriangleMesh__findOrAddVertex( SGS_CTX )
{
	BulletTriangleMesh* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMesh::_sgs_interface, data, BulletTriangleMesh, findOrAddVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->findOrAddVertex( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<bool>()(C,1) )); return 1;
}

static int _sgs_method__BulletTriangleMesh__addIndex( SGS_CTX )
{
	BulletTriangleMesh* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMesh::_sgs_interface, data, BulletTriangleMesh, addIndex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->addIndex( sgs_GetVar<uint32_t>()(C,0) ); return 0;
}

int BulletTriangleMesh::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletTriangleMesh*>( obj->data )->C = C;
	static_cast<BulletTriangleMesh*>( obj->data )->~BulletTriangleMesh();
	return SGS_SUCCESS;
}

int BulletTriangleMesh::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMesh*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int BulletTriangleMesh::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMesh*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "scaling" ){ sgs_PushVar( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_scaling() ); return SGS_SUCCESS; }
		SGS_CASE( "numSubParts" ){ sgs_PushVar( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numSubParts() ); return SGS_SUCCESS; }
		SGS_CASE( "numTriangles" ){ sgs_PushVar( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numTriangles() ); return SGS_SUCCESS; }
		SGS_CASE( "numVertices" ){ sgs_PushVar( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numVertices() ); return SGS_SUCCESS; }
		SGS_CASE( "numIndices" ){ sgs_PushVar( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numIndices() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTriangleMesh::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMesh*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "scaling" ){ static_cast<BulletTriangleMesh*>( obj->data )->_set_scaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTriangleMesh::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMesh*>( obj->data )->C, C );
	char bfr[ 50 ];
	sprintf( bfr, "BulletTriangleMesh (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nscaling = " ); sgs_DumpData( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_scaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumSubParts = " ); sgs_DumpData( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numSubParts(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumTriangles = " ); sgs_DumpData( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numTriangles(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumVertices = " ); sgs_DumpData( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numVertices(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumIndices = " ); sgs_DumpData( C, static_cast<BulletTriangleMesh*>( obj->data )->_get_numIndices(), depth ).push( C ); }
		sgs_StringConcat( C, 10 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletTriangleMesh__sgs_funcs[] =
{
	{ "preallocateVertices", _sgs_method__BulletTriangleMesh__preallocateVertices },
	{ "preallocateIndices", _sgs_method__BulletTriangleMesh__preallocateIndices },
	{ "addTriangle", _sgs_method__BulletTriangleMesh__addTriangle },
	{ "findOrAddVertex", _sgs_method__BulletTriangleMesh__findOrAddVertex },
	{ "addIndex", _sgs_method__BulletTriangleMesh__addIndex },
	{ NULL, NULL },
};

static int BulletTriangleMesh__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletTriangleMesh__sgs_funcs,
		-1, "BulletTriangleMesh." );
	return 1;
}

static sgs_ObjInterface BulletTriangleMesh__sgs_interface =
{
	"BulletTriangleMesh",
	BulletTriangleMesh::_sgs_destruct, BulletTriangleMesh::_sgs_gcmark, BulletTriangleMesh::_sgs_getindex, BulletTriangleMesh::_sgs_setindex, NULL, NULL, BulletTriangleMesh::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletTriangleMesh::_sgs_interface(BulletTriangleMesh__sgs_interface, BulletTriangleMesh__sgs_ifn, &BulletTriangleIndexVertexArray::_sgs_interface);


static int _sgs_method__BulletCollisionShape__getBoundingSphere( SGS_CTX )
{
	BulletCollisionShape* data; if( !SGS_PARSE_METHOD( C, BulletCollisionShape::_sgs_interface, data, BulletCollisionShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletCollisionShape__getAngularMotionDisc( SGS_CTX )
{
	BulletCollisionShape* data; if( !SGS_PARSE_METHOD( C, BulletCollisionShape::_sgs_interface, data, BulletCollisionShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletCollisionShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletCollisionShape* data; if( !SGS_PARSE_METHOD( C, BulletCollisionShape::_sgs_interface, data, BulletCollisionShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCollisionShape__calculateLocalInertia( SGS_CTX )
{
	BulletCollisionShape* data; if( !SGS_PARSE_METHOD( C, BulletCollisionShape::_sgs_interface, data, BulletCollisionShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCollisionShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletCollisionShape* data; if( !SGS_PARSE_METHOD( C, BulletCollisionShape::_sgs_interface, data, BulletCollisionShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletCollisionShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletCollisionShape* data; if( !SGS_PARSE_METHOD( C, BulletCollisionShape::_sgs_interface, data, BulletCollisionShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

int BulletCollisionShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletCollisionShape*>( obj->data )->C = C;
	static_cast<BulletCollisionShape*>( obj->data )->~BulletCollisionShape();
	return SGS_SUCCESS;
}

int BulletCollisionShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletCollisionShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletCollisionShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletCollisionShape*>( obj->data )->userData ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCollisionShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletCollisionShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletCollisionShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletCollisionShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCollisionShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionShape*>( obj->data )->C, C );
	char bfr[ 52 ];
	sprintf( bfr, "BulletCollisionShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletCollisionShape*>( obj->data )->userData, depth ).push( C ); }
		sgs_StringConcat( C, 26 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletCollisionShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletCollisionShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletCollisionShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletCollisionShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletCollisionShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletCollisionShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletCollisionShape__calculateSerializeBufferSize },
	{ NULL, NULL },
};

static int BulletCollisionShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletCollisionShape__sgs_funcs,
		-1, "BulletCollisionShape." );
	return 1;
}

static sgs_ObjInterface BulletCollisionShape__sgs_interface =
{
	"BulletCollisionShape",
	BulletCollisionShape::_sgs_destruct, BulletCollisionShape::_sgs_gcmark, BulletCollisionShape::_sgs_getindex, BulletCollisionShape::_sgs_setindex, NULL, NULL, BulletCollisionShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletCollisionShape::_sgs_interface(BulletCollisionShape__sgs_interface, BulletCollisionShape__sgs_ifn);


static int _sgs_method__BulletConvexShape__getBoundingSphere( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletConvexShape__getAngularMotionDisc( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletConvexShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexShape__calculateLocalInertia( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletConvexShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletConvexShape__localGetSupportingVertex( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexShape__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexShape__getMarginNonVirtual( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletConvexShape__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexShape::_sgs_interface, data, BulletConvexShape, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletConvexShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletConvexShape*>( obj->data )->C = C;
	static_cast<BulletConvexShape*>( obj->data )->~BulletConvexShape();
	return SGS_SUCCESS;
}

int BulletConvexShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletConvexShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletConvexShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletConvexShape*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConvexShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletConvexShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletConvexShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletConvexShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConvexShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexShape*>( obj->data )->C, C );
	char bfr[ 49 ];
	sprintf( bfr, "BulletConvexShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletConvexShape*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		sgs_StringConcat( C, 28 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletConvexShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletConvexShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletConvexShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletConvexShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletConvexShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletConvexShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletConvexShape__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletConvexShape__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletConvexShape__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletConvexShape__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletConvexShape__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletConvexShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletConvexShape__sgs_funcs,
		-1, "BulletConvexShape." );
	return 1;
}

static sgs_ObjInterface BulletConvexShape__sgs_interface =
{
	"BulletConvexShape",
	BulletConvexShape::_sgs_destruct, BulletConvexShape::_sgs_gcmark, BulletConvexShape::_sgs_getindex, BulletConvexShape::_sgs_setindex, NULL, NULL, BulletConvexShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletConvexShape::_sgs_interface(BulletConvexShape__sgs_interface, BulletConvexShape__sgs_ifn, &BulletCollisionShape::_sgs_interface);


static int _sgs_method__BulletConvexInternalShape__getBoundingSphere( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletConvexInternalShape__getAngularMotionDisc( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__calculateLocalInertia( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__localGetSupportingVertex( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__getMarginNonVirtual( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletConvexInternalShape__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletConvexInternalShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexInternalShape::_sgs_interface, data, BulletConvexInternalShape, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletConvexInternalShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletConvexInternalShape*>( obj->data )->C = C;
	static_cast<BulletConvexInternalShape*>( obj->data )->~BulletConvexInternalShape();
	return SGS_SUCCESS;
}

int BulletConvexInternalShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexInternalShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletConvexInternalShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexInternalShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConvexInternalShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexInternalShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletConvexInternalShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletConvexInternalShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletConvexInternalShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletConvexInternalShape*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConvexInternalShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexInternalShape*>( obj->data )->C, C );
	char bfr[ 57 ];
	sprintf( bfr, "BulletConvexInternalShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletConvexInternalShape*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		sgs_StringConcat( C, 34 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletConvexInternalShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletConvexInternalShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletConvexInternalShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletConvexInternalShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletConvexInternalShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletConvexInternalShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletConvexInternalShape__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletConvexInternalShape__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletConvexInternalShape__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletConvexInternalShape__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletConvexInternalShape__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletConvexInternalShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletConvexInternalShape__sgs_funcs,
		-1, "BulletConvexInternalShape." );
	return 1;
}

static sgs_ObjInterface BulletConvexInternalShape__sgs_interface =
{
	"BulletConvexInternalShape",
	BulletConvexInternalShape::_sgs_destruct, BulletConvexInternalShape::_sgs_gcmark, BulletConvexInternalShape::_sgs_getindex, BulletConvexInternalShape::_sgs_setindex, NULL, NULL, BulletConvexInternalShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletConvexInternalShape::_sgs_interface(BulletConvexInternalShape__sgs_interface, BulletConvexInternalShape__sgs_ifn, &BulletConvexShape::_sgs_interface);


static int _sgs_method__BulletSphereShape__getBoundingSphere( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletSphereShape__getAngularMotionDisc( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletSphereShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletSphereShape__calculateLocalInertia( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletSphereShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletSphereShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletSphereShape__localGetSupportingVertex( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletSphereShape__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletSphereShape__getMarginNonVirtual( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletSphereShape__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletSphereShape* data; if( !SGS_PARSE_METHOD( C, BulletSphereShape::_sgs_interface, data, BulletSphereShape, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletSphereShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletSphereShape*>( obj->data )->C = C;
	static_cast<BulletSphereShape*>( obj->data )->~BulletSphereShape();
	return SGS_SUCCESS;
}

int BulletSphereShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletSphereShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletSphereShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletSphereShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletSphereShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "radius" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_radius() ); return SGS_SUCCESS; }
		SGS_CASE( "scaledRadius" ){ sgs_PushVar( C, static_cast<BulletSphereShape*>( obj->data )->_get_scaledRadius() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletSphereShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletSphereShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletSphereShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletSphereShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletSphereShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletSphereShape*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "radius" ){ static_cast<BulletSphereShape*>( obj->data )->_set_radius( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletSphereShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletSphereShape*>( obj->data )->C, C );
	char bfr[ 49 ];
	sprintf( bfr, "BulletSphereShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nradius = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_radius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nscaledRadius = " ); sgs_DumpData( C, static_cast<BulletSphereShape*>( obj->data )->_get_scaledRadius(), depth ).push( C ); }
		sgs_StringConcat( C, 38 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletSphereShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletSphereShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletSphereShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletSphereShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletSphereShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletSphereShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletSphereShape__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletSphereShape__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletSphereShape__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletSphereShape__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletSphereShape__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletSphereShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletSphereShape__sgs_funcs,
		-1, "BulletSphereShape." );
	return 1;
}

static sgs_ObjInterface BulletSphereShape__sgs_interface =
{
	"BulletSphereShape",
	BulletSphereShape::_sgs_destruct, BulletSphereShape::_sgs_gcmark, BulletSphereShape::_sgs_getindex, BulletSphereShape::_sgs_setindex, NULL, NULL, BulletSphereShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletSphereShape::_sgs_interface(BulletSphereShape__sgs_interface, BulletSphereShape__sgs_ifn, &BulletConvexInternalShape::_sgs_interface);


static int _sgs_method__BulletCapsuleShapeY__getBoundingSphere( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletCapsuleShapeY__getAngularMotionDisc( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__getContactBreakingThreshold( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__calculateLocalInertia( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__calculateSerializeBufferSize( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__localGetSupportingVertex( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__getMarginNonVirtual( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeY__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletCapsuleShapeY* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeY::_sgs_interface, data, BulletCapsuleShapeY, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletCapsuleShapeY::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletCapsuleShapeY*>( obj->data )->C = C;
	static_cast<BulletCapsuleShapeY*>( obj->data )->~BulletCapsuleShapeY();
	return SGS_SUCCESS;
}

int BulletCapsuleShapeY::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeY*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletCapsuleShapeY::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeY*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "upAxis" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_upAxis() ); return SGS_SUCCESS; }
		SGS_CASE( "upAxisIndex" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_upAxisIndex() ); return SGS_SUCCESS; }
		SGS_CASE( "radius" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_radius() ); return SGS_SUCCESS; }
		SGS_CASE( "height" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_height() ); return SGS_SUCCESS; }
		SGS_CASE( "halfHeight" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_halfHeight() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCapsuleShapeY::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeY*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletCapsuleShapeY*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletCapsuleShapeY*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletCapsuleShapeY*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletCapsuleShapeY*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCapsuleShapeY::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeY*>( obj->data )->C, C );
	char bfr[ 51 ];
	sprintf( bfr, "BulletCapsuleShapeY (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nupAxis = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_upAxis(), depth ).push( C ); }
		{ sgs_PushString( C, "\nupAxisIndex = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_upAxisIndex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nradius = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_radius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nheight = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_height(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhalfHeight = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeY*>( obj->data )->_get_halfHeight(), depth ).push( C ); }
		sgs_StringConcat( C, 44 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletCapsuleShapeY__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletCapsuleShapeY__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletCapsuleShapeY__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletCapsuleShapeY__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletCapsuleShapeY__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletCapsuleShapeY__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletCapsuleShapeY__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletCapsuleShapeY__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletCapsuleShapeY__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletCapsuleShapeY__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletCapsuleShapeY__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletCapsuleShapeY__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletCapsuleShapeY__sgs_funcs,
		-1, "BulletCapsuleShapeY." );
	return 1;
}

static sgs_ObjInterface BulletCapsuleShapeY__sgs_interface =
{
	"BulletCapsuleShapeY",
	BulletCapsuleShapeY::_sgs_destruct, BulletCapsuleShapeY::_sgs_gcmark, BulletCapsuleShapeY::_sgs_getindex, BulletCapsuleShapeY::_sgs_setindex, NULL, NULL, BulletCapsuleShapeY::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletCapsuleShapeY::_sgs_interface(BulletCapsuleShapeY__sgs_interface, BulletCapsuleShapeY__sgs_ifn, &BulletConvexInternalShape::_sgs_interface);


static int _sgs_method__BulletCapsuleShapeX__getBoundingSphere( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletCapsuleShapeX__getAngularMotionDisc( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__getContactBreakingThreshold( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__calculateLocalInertia( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__calculateSerializeBufferSize( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__localGetSupportingVertex( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__getMarginNonVirtual( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeX__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletCapsuleShapeX* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeX::_sgs_interface, data, BulletCapsuleShapeX, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletCapsuleShapeX::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletCapsuleShapeX*>( obj->data )->C = C;
	static_cast<BulletCapsuleShapeX*>( obj->data )->~BulletCapsuleShapeX();
	return SGS_SUCCESS;
}

int BulletCapsuleShapeX::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeX*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletCapsuleShapeX::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeX*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "upAxis" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_upAxis() ); return SGS_SUCCESS; }
		SGS_CASE( "upAxisIndex" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_upAxisIndex() ); return SGS_SUCCESS; }
		SGS_CASE( "radius" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_radius() ); return SGS_SUCCESS; }
		SGS_CASE( "height" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_height() ); return SGS_SUCCESS; }
		SGS_CASE( "halfHeight" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_halfHeight() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCapsuleShapeX::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeX*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletCapsuleShapeX*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletCapsuleShapeX*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletCapsuleShapeX*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletCapsuleShapeX*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCapsuleShapeX::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeX*>( obj->data )->C, C );
	char bfr[ 51 ];
	sprintf( bfr, "BulletCapsuleShapeX (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nupAxis = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_upAxis(), depth ).push( C ); }
		{ sgs_PushString( C, "\nupAxisIndex = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_upAxisIndex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nradius = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_radius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nheight = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_height(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhalfHeight = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeX*>( obj->data )->_get_halfHeight(), depth ).push( C ); }
		sgs_StringConcat( C, 44 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletCapsuleShapeX__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletCapsuleShapeX__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletCapsuleShapeX__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletCapsuleShapeX__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletCapsuleShapeX__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletCapsuleShapeX__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletCapsuleShapeX__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletCapsuleShapeX__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletCapsuleShapeX__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletCapsuleShapeX__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletCapsuleShapeX__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletCapsuleShapeX__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletCapsuleShapeX__sgs_funcs,
		-1, "BulletCapsuleShapeX." );
	return 1;
}

static sgs_ObjInterface BulletCapsuleShapeX__sgs_interface =
{
	"BulletCapsuleShapeX",
	BulletCapsuleShapeX::_sgs_destruct, BulletCapsuleShapeX::_sgs_gcmark, BulletCapsuleShapeX::_sgs_getindex, BulletCapsuleShapeX::_sgs_setindex, NULL, NULL, BulletCapsuleShapeX::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletCapsuleShapeX::_sgs_interface(BulletCapsuleShapeX__sgs_interface, BulletCapsuleShapeX__sgs_ifn, &BulletCapsuleShapeY::_sgs_interface);


static int _sgs_method__BulletCapsuleShapeZ__getBoundingSphere( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletCapsuleShapeZ__getAngularMotionDisc( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__getContactBreakingThreshold( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__calculateLocalInertia( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__calculateSerializeBufferSize( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__localGetSupportingVertex( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__getMarginNonVirtual( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletCapsuleShapeZ__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletCapsuleShapeZ* data; if( !SGS_PARSE_METHOD( C, BulletCapsuleShapeZ::_sgs_interface, data, BulletCapsuleShapeZ, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletCapsuleShapeZ::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletCapsuleShapeZ*>( obj->data )->C = C;
	static_cast<BulletCapsuleShapeZ*>( obj->data )->~BulletCapsuleShapeZ();
	return SGS_SUCCESS;
}

int BulletCapsuleShapeZ::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeZ*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletCapsuleShapeZ::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeZ*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "upAxis" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_upAxis() ); return SGS_SUCCESS; }
		SGS_CASE( "upAxisIndex" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_upAxisIndex() ); return SGS_SUCCESS; }
		SGS_CASE( "radius" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_radius() ); return SGS_SUCCESS; }
		SGS_CASE( "height" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_height() ); return SGS_SUCCESS; }
		SGS_CASE( "halfHeight" ){ sgs_PushVar( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_halfHeight() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCapsuleShapeZ::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeZ*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletCapsuleShapeZ*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletCapsuleShapeZ*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletCapsuleShapeZ*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletCapsuleShapeZ*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCapsuleShapeZ::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCapsuleShapeZ*>( obj->data )->C, C );
	char bfr[ 51 ];
	sprintf( bfr, "BulletCapsuleShapeZ (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nupAxis = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_upAxis(), depth ).push( C ); }
		{ sgs_PushString( C, "\nupAxisIndex = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_upAxisIndex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nradius = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_radius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nheight = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_height(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhalfHeight = " ); sgs_DumpData( C, static_cast<BulletCapsuleShapeZ*>( obj->data )->_get_halfHeight(), depth ).push( C ); }
		sgs_StringConcat( C, 44 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletCapsuleShapeZ__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletCapsuleShapeZ__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletCapsuleShapeZ__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletCapsuleShapeZ__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletCapsuleShapeZ__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletCapsuleShapeZ__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletCapsuleShapeZ__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletCapsuleShapeZ__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletCapsuleShapeZ__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletCapsuleShapeZ__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletCapsuleShapeZ__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletCapsuleShapeZ__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletCapsuleShapeZ__sgs_funcs,
		-1, "BulletCapsuleShapeZ." );
	return 1;
}

static sgs_ObjInterface BulletCapsuleShapeZ__sgs_interface =
{
	"BulletCapsuleShapeZ",
	BulletCapsuleShapeZ::_sgs_destruct, BulletCapsuleShapeZ::_sgs_gcmark, BulletCapsuleShapeZ::_sgs_getindex, BulletCapsuleShapeZ::_sgs_setindex, NULL, NULL, BulletCapsuleShapeZ::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletCapsuleShapeZ::_sgs_interface(BulletCapsuleShapeZ__sgs_interface, BulletCapsuleShapeZ__sgs_ifn, &BulletCapsuleShapeY::_sgs_interface);


static int _sgs_method__BulletPolyhedralConvexShape__getBoundingSphere( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletPolyhedralConvexShape__getAngularMotionDisc( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__calculateLocalInertia( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__localGetSupportingVertex( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__getMarginNonVirtual( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexShape__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletPolyhedralConvexShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexShape::_sgs_interface, data, BulletPolyhedralConvexShape, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletPolyhedralConvexShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletPolyhedralConvexShape*>( obj->data )->C = C;
	static_cast<BulletPolyhedralConvexShape*>( obj->data )->~BulletPolyhedralConvexShape();
	return SGS_SUCCESS;
}

int BulletPolyhedralConvexShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletPolyhedralConvexShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "numVertices" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numVertices() ); return SGS_SUCCESS; }
		SGS_CASE( "numEdges" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numEdges() ); return SGS_SUCCESS; }
		SGS_CASE( "numPlanes" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numPlanes() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletPolyhedralConvexShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletPolyhedralConvexShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletPolyhedralConvexShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletPolyhedralConvexShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletPolyhedralConvexShape*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletPolyhedralConvexShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexShape*>( obj->data )->C, C );
	char bfr[ 59 ];
	sprintf( bfr, "BulletPolyhedralConvexShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumVertices = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numVertices(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumEdges = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numEdges(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPlanes = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexShape*>( obj->data )->_get_numPlanes(), depth ).push( C ); }
		sgs_StringConcat( C, 40 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletPolyhedralConvexShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletPolyhedralConvexShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletPolyhedralConvexShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletPolyhedralConvexShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletPolyhedralConvexShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletPolyhedralConvexShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletPolyhedralConvexShape__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletPolyhedralConvexShape__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletPolyhedralConvexShape__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletPolyhedralConvexShape__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletPolyhedralConvexShape__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletPolyhedralConvexShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletPolyhedralConvexShape__sgs_funcs,
		-1, "BulletPolyhedralConvexShape." );
	return 1;
}

static sgs_ObjInterface BulletPolyhedralConvexShape__sgs_interface =
{
	"BulletPolyhedralConvexShape",
	BulletPolyhedralConvexShape::_sgs_destruct, BulletPolyhedralConvexShape::_sgs_gcmark, BulletPolyhedralConvexShape::_sgs_getindex, BulletPolyhedralConvexShape::_sgs_setindex, NULL, NULL, BulletPolyhedralConvexShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletPolyhedralConvexShape::_sgs_interface(BulletPolyhedralConvexShape__sgs_interface, BulletPolyhedralConvexShape__sgs_ifn, &BulletConvexInternalShape::_sgs_interface);


static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__getBoundingSphere( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__getAngularMotionDisc( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__calculateLocalInertia( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__localGetSupportingVertex( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__getMarginNonVirtual( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

static int _sgs_method__BulletPolyhedralConvexAabbCachingShape__recalcLocalAABB( SGS_CTX )
{
	BulletPolyhedralConvexAabbCachingShape* data; if( !SGS_PARSE_METHOD( C, BulletPolyhedralConvexAabbCachingShape::_sgs_interface, data, BulletPolyhedralConvexAabbCachingShape, recalcLocalAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->recalcLocalAABB(  ); return 0;
}

int BulletPolyhedralConvexAabbCachingShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->C = C;
	static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->~BulletPolyhedralConvexAabbCachingShape();
	return SGS_SUCCESS;
}

int BulletPolyhedralConvexAabbCachingShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletPolyhedralConvexAabbCachingShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "numVertices" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numVertices() ); return SGS_SUCCESS; }
		SGS_CASE( "numEdges" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numEdges() ); return SGS_SUCCESS; }
		SGS_CASE( "numPlanes" ){ sgs_PushVar( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numPlanes() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletPolyhedralConvexAabbCachingShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletPolyhedralConvexAabbCachingShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->C, C );
	char bfr[ 70 ];
	sprintf( bfr, "BulletPolyhedralConvexAabbCachingShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumVertices = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numVertices(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumEdges = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numEdges(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPlanes = " ); sgs_DumpData( C, static_cast<BulletPolyhedralConvexAabbCachingShape*>( obj->data )->_get_numPlanes(), depth ).push( C ); }
		sgs_StringConcat( C, 40 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletPolyhedralConvexAabbCachingShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletPolyhedralConvexAabbCachingShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletPolyhedralConvexAabbCachingShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletPolyhedralConvexAabbCachingShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletPolyhedralConvexAabbCachingShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletPolyhedralConvexAabbCachingShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletPolyhedralConvexAabbCachingShape__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletPolyhedralConvexAabbCachingShape__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletPolyhedralConvexAabbCachingShape__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletPolyhedralConvexAabbCachingShape__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletPolyhedralConvexAabbCachingShape__getPreferredPenetrationDirection },
	{ "recalcLocalAABB", _sgs_method__BulletPolyhedralConvexAabbCachingShape__recalcLocalAABB },
	{ NULL, NULL },
};

static int BulletPolyhedralConvexAabbCachingShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletPolyhedralConvexAabbCachingShape__sgs_funcs,
		-1, "BulletPolyhedralConvexAabbCachingShape." );
	return 1;
}

static sgs_ObjInterface BulletPolyhedralConvexAabbCachingShape__sgs_interface =
{
	"BulletPolyhedralConvexAabbCachingShape",
	BulletPolyhedralConvexAabbCachingShape::_sgs_destruct, BulletPolyhedralConvexAabbCachingShape::_sgs_gcmark, BulletPolyhedralConvexAabbCachingShape::_sgs_getindex, BulletPolyhedralConvexAabbCachingShape::_sgs_setindex, NULL, NULL, BulletPolyhedralConvexAabbCachingShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletPolyhedralConvexAabbCachingShape::_sgs_interface(BulletPolyhedralConvexAabbCachingShape__sgs_interface, BulletPolyhedralConvexAabbCachingShape__sgs_ifn, &BulletPolyhedralConvexShape::_sgs_interface);


static int _sgs_method__BulletConvexHullShape__getBoundingSphere( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletConvexHullShape__getAngularMotionDisc( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletConvexHullShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexHullShape__calculateLocalInertia( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexHullShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletConvexHullShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletConvexHullShape__localGetSupportingVertex( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexHullShape__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexHullShape__getMarginNonVirtual( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletConvexHullShape__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

static int _sgs_method__BulletConvexHullShape__recalcLocalAABB( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, recalcLocalAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->recalcLocalAABB(  ); return 0;
}

static int _sgs_method__BulletConvexHullShape__addPoint( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, addPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->addPoint( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<bool>()(C,1) ); return 0;
}

static int _sgs_method__BulletConvexHullShape__getUnscaledPoint( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getUnscaledPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getUnscaledPoint( sgs_GetVar<int>()(C,0) );
}

static int _sgs_method__BulletConvexHullShape__getScaledPoint( SGS_CTX )
{
	BulletConvexHullShape* data; if( !SGS_PARSE_METHOD( C, BulletConvexHullShape::_sgs_interface, data, BulletConvexHullShape, getScaledPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getScaledPoint( sgs_GetVar<int>()(C,0) );
}

int BulletConvexHullShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletConvexHullShape*>( obj->data )->C = C;
	static_cast<BulletConvexHullShape*>( obj->data )->~BulletConvexHullShape();
	return SGS_SUCCESS;
}

int BulletConvexHullShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexHullShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletConvexHullShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletConvexHullShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexHullShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "numVertices" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numVertices() ); return SGS_SUCCESS; }
		SGS_CASE( "numEdges" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numEdges() ); return SGS_SUCCESS; }
		SGS_CASE( "numPlanes" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numPlanes() ); return SGS_SUCCESS; }
		SGS_CASE( "numPoints" ){ sgs_PushVar( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numPoints() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConvexHullShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexHullShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletConvexHullShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletConvexHullShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletConvexHullShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletConvexHullShape*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConvexHullShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConvexHullShape*>( obj->data )->C, C );
	char bfr[ 53 ];
	sprintf( bfr, "BulletConvexHullShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumVertices = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numVertices(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumEdges = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numEdges(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPlanes = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numPlanes(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPoints = " ); sgs_DumpData( C, static_cast<BulletConvexHullShape*>( obj->data )->_get_numPoints(), depth ).push( C ); }
		sgs_StringConcat( C, 42 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletConvexHullShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletConvexHullShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletConvexHullShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletConvexHullShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletConvexHullShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletConvexHullShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletConvexHullShape__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletConvexHullShape__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletConvexHullShape__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletConvexHullShape__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletConvexHullShape__getPreferredPenetrationDirection },
	{ "recalcLocalAABB", _sgs_method__BulletConvexHullShape__recalcLocalAABB },
	{ "addPoint", _sgs_method__BulletConvexHullShape__addPoint },
	{ "getUnscaledPoint", _sgs_method__BulletConvexHullShape__getUnscaledPoint },
	{ "getScaledPoint", _sgs_method__BulletConvexHullShape__getScaledPoint },
	{ NULL, NULL },
};

static int BulletConvexHullShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletConvexHullShape__sgs_funcs,
		-1, "BulletConvexHullShape." );
	return 1;
}

static sgs_ObjInterface BulletConvexHullShape__sgs_interface =
{
	"BulletConvexHullShape",
	BulletConvexHullShape::_sgs_destruct, BulletConvexHullShape::_sgs_gcmark, BulletConvexHullShape::_sgs_getindex, BulletConvexHullShape::_sgs_setindex, NULL, NULL, BulletConvexHullShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletConvexHullShape::_sgs_interface(BulletConvexHullShape__sgs_interface, BulletConvexHullShape__sgs_ifn, &BulletPolyhedralConvexAabbCachingShape::_sgs_interface);


static int _sgs_method__BulletBoxShape__getBoundingSphere( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletBoxShape__getAngularMotionDisc( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletBoxShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletBoxShape__calculateLocalInertia( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletBoxShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletBoxShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletBoxShape__localGetSupportingVertex( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, localGetSupportingVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertex( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletBoxShape__localGetSupportingVertexWithoutMargin( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, localGetSupportingVertexWithoutMargin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->localGetSupportingVertexWithoutMargin( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletBoxShape__getMarginNonVirtual( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, getMarginNonVirtual ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getMarginNonVirtual(  )); return 1;
}

static int _sgs_method__BulletBoxShape__getPreferredPenetrationDirection( SGS_CTX )
{
	BulletBoxShape* data; if( !SGS_PARSE_METHOD( C, BulletBoxShape::_sgs_interface, data, BulletBoxShape, getPreferredPenetrationDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getPreferredPenetrationDirection( sgs_GetVar<int>()(C,0) )); return 1;
}

int BulletBoxShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletBoxShape*>( obj->data )->C = C;
	static_cast<BulletBoxShape*>( obj->data )->~BulletBoxShape();
	return SGS_SUCCESS;
}

int BulletBoxShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBoxShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletBoxShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletBoxShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBoxShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numPreferredPenetrationDirections" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_numPreferredPenetrationDirections() ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_implicitShapeDimensions() ); return SGS_SUCCESS; }
		SGS_CASE( "localScalingNV" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_localScalingNV() ); return SGS_SUCCESS; }
		SGS_CASE( "marginNV" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_marginNV() ); return SGS_SUCCESS; }
		SGS_CASE( "numVertices" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_numVertices() ); return SGS_SUCCESS; }
		SGS_CASE( "numEdges" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_numEdges() ); return SGS_SUCCESS; }
		SGS_CASE( "numPlanes" ){ sgs_PushVar( C, static_cast<BulletBoxShape*>( obj->data )->_get_numPlanes() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletBoxShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBoxShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletBoxShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletBoxShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletBoxShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "implicitShapeDimensions" ){ static_cast<BulletBoxShape*>( obj->data )->_set_implicitShapeDimensions( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletBoxShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBoxShape*>( obj->data )->C, C );
	char bfr[ 46 ];
	sprintf( bfr, "BulletBoxShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPreferredPenetrationDirections = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_numPreferredPenetrationDirections(), depth ).push( C ); }
		{ sgs_PushString( C, "\nimplicitShapeDimensions = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_implicitShapeDimensions(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScalingNV = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_localScalingNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmarginNV = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_marginNV(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumVertices = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_numVertices(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumEdges = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_numEdges(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumPlanes = " ); sgs_DumpData( C, static_cast<BulletBoxShape*>( obj->data )->_get_numPlanes(), depth ).push( C ); }
		sgs_StringConcat( C, 40 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletBoxShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletBoxShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletBoxShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletBoxShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletBoxShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletBoxShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletBoxShape__calculateSerializeBufferSize },
	{ "localGetSupportingVertex", _sgs_method__BulletBoxShape__localGetSupportingVertex },
	{ "localGetSupportingVertexWithoutMargin", _sgs_method__BulletBoxShape__localGetSupportingVertexWithoutMargin },
	{ "getMarginNonVirtual", _sgs_method__BulletBoxShape__getMarginNonVirtual },
	{ "getPreferredPenetrationDirection", _sgs_method__BulletBoxShape__getPreferredPenetrationDirection },
	{ NULL, NULL },
};

static int BulletBoxShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletBoxShape__sgs_funcs,
		-1, "BulletBoxShape." );
	return 1;
}

static sgs_ObjInterface BulletBoxShape__sgs_interface =
{
	"BulletBoxShape",
	BulletBoxShape::_sgs_destruct, BulletBoxShape::_sgs_gcmark, BulletBoxShape::_sgs_getindex, BulletBoxShape::_sgs_setindex, NULL, NULL, BulletBoxShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletBoxShape::_sgs_interface(BulletBoxShape__sgs_interface, BulletBoxShape__sgs_ifn, &BulletPolyhedralConvexShape::_sgs_interface);


static int _sgs_method__BulletConcaveShape__getBoundingSphere( SGS_CTX )
{
	BulletConcaveShape* data; if( !SGS_PARSE_METHOD( C, BulletConcaveShape::_sgs_interface, data, BulletConcaveShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletConcaveShape__getAngularMotionDisc( SGS_CTX )
{
	BulletConcaveShape* data; if( !SGS_PARSE_METHOD( C, BulletConcaveShape::_sgs_interface, data, BulletConcaveShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletConcaveShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletConcaveShape* data; if( !SGS_PARSE_METHOD( C, BulletConcaveShape::_sgs_interface, data, BulletConcaveShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConcaveShape__calculateLocalInertia( SGS_CTX )
{
	BulletConcaveShape* data; if( !SGS_PARSE_METHOD( C, BulletConcaveShape::_sgs_interface, data, BulletConcaveShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletConcaveShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletConcaveShape* data; if( !SGS_PARSE_METHOD( C, BulletConcaveShape::_sgs_interface, data, BulletConcaveShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletConcaveShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletConcaveShape* data; if( !SGS_PARSE_METHOD( C, BulletConcaveShape::_sgs_interface, data, BulletConcaveShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

int BulletConcaveShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletConcaveShape*>( obj->data )->C = C;
	static_cast<BulletConcaveShape*>( obj->data )->~BulletConcaveShape();
	return SGS_SUCCESS;
}

int BulletConcaveShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConcaveShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletConcaveShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletConcaveShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConcaveShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletConcaveShape*>( obj->data )->userData ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConcaveShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConcaveShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletConcaveShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletConcaveShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletConcaveShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletConcaveShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletConcaveShape*>( obj->data )->C, C );
	char bfr[ 50 ];
	sprintf( bfr, "BulletConcaveShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletConcaveShape*>( obj->data )->userData, depth ).push( C ); }
		sgs_StringConcat( C, 26 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletConcaveShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletConcaveShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletConcaveShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletConcaveShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletConcaveShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletConcaveShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletConcaveShape__calculateSerializeBufferSize },
	{ NULL, NULL },
};

static int BulletConcaveShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletConcaveShape__sgs_funcs,
		-1, "BulletConcaveShape." );
	return 1;
}

static sgs_ObjInterface BulletConcaveShape__sgs_interface =
{
	"BulletConcaveShape",
	BulletConcaveShape::_sgs_destruct, BulletConcaveShape::_sgs_gcmark, BulletConcaveShape::_sgs_getindex, BulletConcaveShape::_sgs_setindex, NULL, NULL, BulletConcaveShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletConcaveShape::_sgs_interface(BulletConcaveShape__sgs_interface, BulletConcaveShape__sgs_ifn, &BulletCollisionShape::_sgs_interface);


static int _sgs_method__BulletStaticPlaneShape__getBoundingSphere( SGS_CTX )
{
	BulletStaticPlaneShape* data; if( !SGS_PARSE_METHOD( C, BulletStaticPlaneShape::_sgs_interface, data, BulletStaticPlaneShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletStaticPlaneShape__getAngularMotionDisc( SGS_CTX )
{
	BulletStaticPlaneShape* data; if( !SGS_PARSE_METHOD( C, BulletStaticPlaneShape::_sgs_interface, data, BulletStaticPlaneShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletStaticPlaneShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletStaticPlaneShape* data; if( !SGS_PARSE_METHOD( C, BulletStaticPlaneShape::_sgs_interface, data, BulletStaticPlaneShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletStaticPlaneShape__calculateLocalInertia( SGS_CTX )
{
	BulletStaticPlaneShape* data; if( !SGS_PARSE_METHOD( C, BulletStaticPlaneShape::_sgs_interface, data, BulletStaticPlaneShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletStaticPlaneShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletStaticPlaneShape* data; if( !SGS_PARSE_METHOD( C, BulletStaticPlaneShape::_sgs_interface, data, BulletStaticPlaneShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletStaticPlaneShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletStaticPlaneShape* data; if( !SGS_PARSE_METHOD( C, BulletStaticPlaneShape::_sgs_interface, data, BulletStaticPlaneShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

int BulletStaticPlaneShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletStaticPlaneShape*>( obj->data )->C = C;
	static_cast<BulletStaticPlaneShape*>( obj->data )->~BulletStaticPlaneShape();
	return SGS_SUCCESS;
}

int BulletStaticPlaneShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStaticPlaneShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletStaticPlaneShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStaticPlaneShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "planeNormal" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_planeNormal() ); return SGS_SUCCESS; }
		SGS_CASE( "planeConstant" ){ sgs_PushVar( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_planeConstant() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletStaticPlaneShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStaticPlaneShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletStaticPlaneShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletStaticPlaneShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletStaticPlaneShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletStaticPlaneShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletStaticPlaneShape*>( obj->data )->C, C );
	char bfr[ 54 ];
	sprintf( bfr, "BulletStaticPlaneShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nplaneNormal = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_planeNormal(), depth ).push( C ); }
		{ sgs_PushString( C, "\nplaneConstant = " ); sgs_DumpData( C, static_cast<BulletStaticPlaneShape*>( obj->data )->_get_planeConstant(), depth ).push( C ); }
		sgs_StringConcat( C, 30 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletStaticPlaneShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletStaticPlaneShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletStaticPlaneShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletStaticPlaneShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletStaticPlaneShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletStaticPlaneShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletStaticPlaneShape__calculateSerializeBufferSize },
	{ NULL, NULL },
};

static int BulletStaticPlaneShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletStaticPlaneShape__sgs_funcs,
		-1, "BulletStaticPlaneShape." );
	return 1;
}

static sgs_ObjInterface BulletStaticPlaneShape__sgs_interface =
{
	"BulletStaticPlaneShape",
	BulletStaticPlaneShape::_sgs_destruct, BulletStaticPlaneShape::_sgs_gcmark, BulletStaticPlaneShape::_sgs_getindex, BulletStaticPlaneShape::_sgs_setindex, NULL, NULL, BulletStaticPlaneShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletStaticPlaneShape::_sgs_interface(BulletStaticPlaneShape__sgs_interface, BulletStaticPlaneShape__sgs_ifn, &BulletConcaveShape::_sgs_interface);


static int _sgs_method__BulletTriangleMeshShape__getBoundingSphere( SGS_CTX )
{
	BulletTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMeshShape::_sgs_interface, data, BulletTriangleMeshShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletTriangleMeshShape__getAngularMotionDisc( SGS_CTX )
{
	BulletTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMeshShape::_sgs_interface, data, BulletTriangleMeshShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletTriangleMeshShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMeshShape::_sgs_interface, data, BulletTriangleMeshShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletTriangleMeshShape__calculateLocalInertia( SGS_CTX )
{
	BulletTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMeshShape::_sgs_interface, data, BulletTriangleMeshShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletTriangleMeshShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMeshShape::_sgs_interface, data, BulletTriangleMeshShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletTriangleMeshShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMeshShape::_sgs_interface, data, BulletTriangleMeshShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletTriangleMeshShape__recalcLocalAABB( SGS_CTX )
{
	BulletTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletTriangleMeshShape::_sgs_interface, data, BulletTriangleMeshShape, recalcLocalAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->recalcLocalAABB(  ); return 0;
}

int BulletTriangleMeshShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletTriangleMeshShape*>( obj->data )->C = C;
	static_cast<BulletTriangleMeshShape*>( obj->data )->~BulletTriangleMeshShape();
	return SGS_SUCCESS;
}

int BulletTriangleMeshShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMeshShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->userData );
	sgs_GCMarkVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->meshInterface );
	return SGS_SUCCESS;
}

int BulletTriangleMeshShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMeshShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "meshInterface" ){ sgs_PushVar( C, static_cast<BulletTriangleMeshShape*>( obj->data )->meshInterface ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTriangleMeshShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMeshShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletTriangleMeshShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletTriangleMeshShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletTriangleMeshShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletTriangleMeshShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletTriangleMeshShape*>( obj->data )->C, C );
	char bfr[ 55 ];
	sprintf( bfr, "BulletTriangleMeshShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nmeshInterface = " ); sgs_DumpData( C, static_cast<BulletTriangleMeshShape*>( obj->data )->meshInterface, depth ).push( C ); }
		sgs_StringConcat( C, 28 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletTriangleMeshShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletTriangleMeshShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletTriangleMeshShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletTriangleMeshShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletTriangleMeshShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletTriangleMeshShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletTriangleMeshShape__calculateSerializeBufferSize },
	{ "recalcLocalAABB", _sgs_method__BulletTriangleMeshShape__recalcLocalAABB },
	{ NULL, NULL },
};

static int BulletTriangleMeshShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletTriangleMeshShape__sgs_funcs,
		-1, "BulletTriangleMeshShape." );
	return 1;
}

static sgs_ObjInterface BulletTriangleMeshShape__sgs_interface =
{
	"BulletTriangleMeshShape",
	BulletTriangleMeshShape::_sgs_destruct, BulletTriangleMeshShape::_sgs_gcmark, BulletTriangleMeshShape::_sgs_getindex, BulletTriangleMeshShape::_sgs_setindex, NULL, NULL, BulletTriangleMeshShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletTriangleMeshShape::_sgs_interface(BulletTriangleMeshShape__sgs_interface, BulletTriangleMeshShape__sgs_ifn, &BulletConcaveShape::_sgs_interface);


static int _sgs_method__BulletBVHTriangleMeshShape__getBoundingSphere( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, getBoundingSphere ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->getBoundingSphere(  );
}

static int _sgs_method__BulletBVHTriangleMeshShape__getAngularMotionDisc( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, getAngularMotionDisc ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAngularMotionDisc(  )); return 1;
}

static int _sgs_method__BulletBVHTriangleMeshShape__getContactBreakingThreshold( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, getContactBreakingThreshold ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getContactBreakingThreshold( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletBVHTriangleMeshShape__calculateLocalInertia( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, calculateLocalInertia ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateLocalInertia( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletBVHTriangleMeshShape__getAnisotropicRollingFrictionDirection( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, getAnisotropicRollingFrictionDirection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getAnisotropicRollingFrictionDirection(  )); return 1;
}

static int _sgs_method__BulletBVHTriangleMeshShape__calculateSerializeBufferSize( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletBVHTriangleMeshShape__recalcLocalAABB( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, recalcLocalAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->recalcLocalAABB(  ); return 0;
}

static int _sgs_method__BulletBVHTriangleMeshShape__buildOptimizedBVH( SGS_CTX )
{
	BulletBVHTriangleMeshShape* data; if( !SGS_PARSE_METHOD( C, BulletBVHTriangleMeshShape::_sgs_interface, data, BulletBVHTriangleMeshShape, buildOptimizedBVH ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->buildOptimizedBVH(  ); return 0;
}

int BulletBVHTriangleMeshShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletBVHTriangleMeshShape*>( obj->data )->C = C;
	static_cast<BulletBVHTriangleMeshShape*>( obj->data )->~BulletBVHTriangleMeshShape();
	return SGS_SUCCESS;
}

int BulletBVHTriangleMeshShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBVHTriangleMeshShape*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->userData );
	sgs_GCMarkVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->meshInterface );
	return SGS_SUCCESS;
}

int BulletBVHTriangleMeshShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBVHTriangleMeshShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isPolyhedral" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isPolyhedral() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex2D" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isConvex2D() ); return SGS_SUCCESS; }
		SGS_CASE( "isConvex" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isConvex() ); return SGS_SUCCESS; }
		SGS_CASE( "isNonMoving" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isNonMoving() ); return SGS_SUCCESS; }
		SGS_CASE( "isConcave" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isConcave() ); return SGS_SUCCESS; }
		SGS_CASE( "isCompound" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isCompound() ); return SGS_SUCCESS; }
		SGS_CASE( "isSoftBody" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isSoftBody() ); return SGS_SUCCESS; }
		SGS_CASE( "isInfinite" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isInfinite() ); return SGS_SUCCESS; }
		SGS_CASE( "localScaling" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_localScaling() ); return SGS_SUCCESS; }
		SGS_CASE( "name" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_name() ); return SGS_SUCCESS; }
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_shapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_margin() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "meshInterface" ){ sgs_PushVar( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->meshInterface ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletBVHTriangleMeshShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBVHTriangleMeshShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "localScaling" ){ static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_set_localScaling( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "margin" ){ static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_set_margin( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletBVHTriangleMeshShape*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletBVHTriangleMeshShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletBVHTriangleMeshShape*>( obj->data )->C, C );
	char bfr[ 58 ];
	sprintf( bfr, "BulletBVHTriangleMeshShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisPolyhedral = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isPolyhedral(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex2D = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isConvex2D(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConvex = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isConvex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisNonMoving = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isNonMoving(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisConcave = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isConcave(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisCompound = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isCompound(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisSoftBody = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isSoftBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInfinite = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_isInfinite(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalScaling = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_localScaling(), depth ).push( C ); }
		{ sgs_PushString( C, "\nname = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_name(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_shapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmargin = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->_get_margin(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nmeshInterface = " ); sgs_DumpData( C, static_cast<BulletBVHTriangleMeshShape*>( obj->data )->meshInterface, depth ).push( C ); }
		sgs_StringConcat( C, 28 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletBVHTriangleMeshShape__sgs_funcs[] =
{
	{ "getBoundingSphere", _sgs_method__BulletBVHTriangleMeshShape__getBoundingSphere },
	{ "getAngularMotionDisc", _sgs_method__BulletBVHTriangleMeshShape__getAngularMotionDisc },
	{ "getContactBreakingThreshold", _sgs_method__BulletBVHTriangleMeshShape__getContactBreakingThreshold },
	{ "calculateLocalInertia", _sgs_method__BulletBVHTriangleMeshShape__calculateLocalInertia },
	{ "getAnisotropicRollingFrictionDirection", _sgs_method__BulletBVHTriangleMeshShape__getAnisotropicRollingFrictionDirection },
	{ "calculateSerializeBufferSize", _sgs_method__BulletBVHTriangleMeshShape__calculateSerializeBufferSize },
	{ "recalcLocalAABB", _sgs_method__BulletBVHTriangleMeshShape__recalcLocalAABB },
	{ "buildOptimizedBVH", _sgs_method__BulletBVHTriangleMeshShape__buildOptimizedBVH },
	{ NULL, NULL },
};

static int BulletBVHTriangleMeshShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletBVHTriangleMeshShape__sgs_funcs,
		-1, "BulletBVHTriangleMeshShape." );
	return 1;
}

static sgs_ObjInterface BulletBVHTriangleMeshShape__sgs_interface =
{
	"BulletBVHTriangleMeshShape",
	BulletBVHTriangleMeshShape::_sgs_destruct, BulletBVHTriangleMeshShape::_sgs_gcmark, BulletBVHTriangleMeshShape::_sgs_getindex, BulletBVHTriangleMeshShape::_sgs_setindex, NULL, NULL, BulletBVHTriangleMeshShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletBVHTriangleMeshShape::_sgs_interface(BulletBVHTriangleMeshShape__sgs_interface, BulletBVHTriangleMeshShape__sgs_ifn, &BulletTriangleMeshShape::_sgs_interface);


int BulletRigidBodyCreationInfo::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletRigidBodyCreationInfo*>( obj->data )->C = C;
	static_cast<BulletRigidBodyCreationInfo*>( obj->data )->~BulletRigidBodyCreationInfo();
	return SGS_SUCCESS;
}

int BulletRigidBodyCreationInfo::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBodyCreationInfo*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int BulletRigidBodyCreationInfo::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBodyCreationInfo*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "additionalAngularDampingFactor" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalAngularDampingFactor ); return SGS_SUCCESS; }
		SGS_CASE( "additionalAngularDampingThresholdSqr" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalAngularDampingThresholdSqr ); return SGS_SUCCESS; }
		SGS_CASE( "additionalDamping" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalDamping ); return SGS_SUCCESS; }
		SGS_CASE( "additionalDampingFactor" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalDampingFactor ); return SGS_SUCCESS; }
		SGS_CASE( "additionalLinearDampingThresholdSqr" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalLinearDampingThresholdSqr ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_angularDamping ); return SGS_SUCCESS; }
		SGS_CASE( "angularSleepingThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_angularSleepingThreshold ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_collisionShape ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_friction ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_linearDamping ); return SGS_SUCCESS; }
		SGS_CASE( "linearSleepingThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_linearSleepingThreshold ); return SGS_SUCCESS; }
		SGS_CASE( "localInertia" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_localInertia ); return SGS_SUCCESS; }
		SGS_CASE( "mass" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_mass ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_restitution ); return SGS_SUCCESS; }
		SGS_CASE( "startWorldTransform" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_startWorldTransform ); return SGS_SUCCESS; }
		SGS_CASE( "transform" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_startWorldTransform ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ sgs_PushVar( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->_get_position() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletRigidBodyCreationInfo::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBodyCreationInfo*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "additionalAngularDampingFactor" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalAngularDampingFactor = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "additionalAngularDampingThresholdSqr" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalAngularDampingThresholdSqr = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "additionalDamping" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalDamping = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "additionalDampingFactor" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalDampingFactor = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "additionalLinearDampingThresholdSqr" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalLinearDampingThresholdSqr = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_angularDamping = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "angularSleepingThreshold" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_angularSleepingThreshold = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->_set_collisionShape( sgs_GetVar<BulletCollisionShapePointer>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_friction = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_linearDamping = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "linearSleepingThreshold" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_linearSleepingThreshold = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localInertia" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_localInertia = sgs_GetVar<btVector3>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "mass" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_mass = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_restitution = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "startWorldTransform" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_startWorldTransform = sgs_GetVar<BulletTransform>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "transform" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_startWorldTransform = sgs_GetVar<BulletTransform>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ static_cast<BulletRigidBodyCreationInfo*>( obj->data )->_set_position( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletRigidBodyCreationInfo::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBodyCreationInfo*>( obj->data )->C, C );
	char bfr[ 59 ];
	sprintf( bfr, "BulletRigidBodyCreationInfo (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nadditionalAngularDampingFactor = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalAngularDampingFactor, depth ).push( C ); }
		{ sgs_PushString( C, "\nadditionalAngularDampingThresholdSqr = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalAngularDampingThresholdSqr, depth ).push( C ); }
		{ sgs_PushString( C, "\nadditionalDamping = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalDamping, depth ).push( C ); }
		{ sgs_PushString( C, "\nadditionalDampingFactor = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalDampingFactor, depth ).push( C ); }
		{ sgs_PushString( C, "\nadditionalLinearDampingThresholdSqr = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_additionalLinearDampingThresholdSqr, depth ).push( C ); }
		{ sgs_PushString( C, "\nangularDamping = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_angularDamping, depth ).push( C ); }
		{ sgs_PushString( C, "\nangularSleepingThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_angularSleepingThreshold, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollisionShape = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_collisionShape, depth ).push( C ); }
		{ sgs_PushString( C, "\nfriction = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_friction, depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearDamping = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_linearDamping, depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearSleepingThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_linearSleepingThreshold, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalInertia = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_localInertia, depth ).push( C ); }
		{ sgs_PushString( C, "\nmass = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_mass, depth ).push( C ); }
		{ sgs_PushString( C, "\nrestitution = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_restitution, depth ).push( C ); }
		{ sgs_PushString( C, "\nstartWorldTransform = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_startWorldTransform, depth ).push( C ); }
		{ sgs_PushString( C, "\ntransform = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->m_startWorldTransform, depth ).push( C ); }
		{ sgs_PushString( C, "\nposition = " ); sgs_DumpData( C, static_cast<BulletRigidBodyCreationInfo*>( obj->data )->_get_position(), depth ).push( C ); }
		sgs_StringConcat( C, 34 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletRigidBodyCreationInfo__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int BulletRigidBodyCreationInfo__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletRigidBodyCreationInfo__sgs_funcs,
		-1, "BulletRigidBodyCreationInfo." );
	return 1;
}

static sgs_ObjInterface BulletRigidBodyCreationInfo__sgs_interface =
{
	"BulletRigidBodyCreationInfo",
	BulletRigidBodyCreationInfo::_sgs_destruct, BulletRigidBodyCreationInfo::gcmark, BulletRigidBodyCreationInfo::_sgs_getindex, BulletRigidBodyCreationInfo::_sgs_setindex, NULL, NULL, BulletRigidBodyCreationInfo::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletRigidBodyCreationInfo::_sgs_interface(BulletRigidBodyCreationInfo__sgs_interface, BulletRigidBodyCreationInfo__sgs_ifn);


int BulletCollisionObject::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletCollisionObject*>( obj->data )->C = C;
	static_cast<BulletCollisionObject*>( obj->data )->~BulletCollisionObject();
	return SGS_SUCCESS;
}

int BulletCollisionObject::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionObject*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int BulletCollisionObject::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionObject*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mergesSimulationIslands" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_mergesSimulationIslands() ); return SGS_SUCCESS; }
		SGS_CASE( "anisotropicFriction" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_anisotropicFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "hasAnisotropicFriction" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_hasAnisotropicFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "contactProcessingThreshold" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_contactProcessingThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "isStaticObject" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isStaticObject() ); return SGS_SUCCESS; }
		SGS_CASE( "isKinematicObject" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isKinematicObject() ); return SGS_SUCCESS; }
		SGS_CASE( "isStaticOrKinematicObject" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isStaticOrKinematicObject() ); return SGS_SUCCESS; }
		SGS_CASE( "hasContactResponse" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_hasContactResponse() ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_collisionShape() ); return SGS_SUCCESS; }
		SGS_CASE( "activationState" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_activationState() ); return SGS_SUCCESS; }
		SGS_CASE( "deactivationTime" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_deactivationTime() ); return SGS_SUCCESS; }
		SGS_CASE( "isActive" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isActive() ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_restitution() ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_friction() ); return SGS_SUCCESS; }
		SGS_CASE( "rollingFriction" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_rollingFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "worldTransform" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_worldTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationWorldTransform" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_interpolationWorldTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationLinearVelocity" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_interpolationLinearVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationAngularVelocity" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_interpolationAngularVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "islandTag" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_islandTag() ); return SGS_SUCCESS; }
		SGS_CASE( "companionID" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_companionID() ); return SGS_SUCCESS; }
		SGS_CASE( "companionId" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_companionID() ); return SGS_SUCCESS; }
		SGS_CASE( "hitFraction" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_hitFraction() ); return SGS_SUCCESS; }
		SGS_CASE( "collisionFlags" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_collisionFlags() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSweptSphereRadius" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSweptSphereRadius() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSweptSphereRadius" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSweptSphereRadius() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSquareMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSquareMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSquareMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSquareMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletCollisionObject*>( obj->data )->userData ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCollisionObject::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionObject*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "anisotropicFriction" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_anisotropicFriction( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "contactProcessingThreshold" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_contactProcessingThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "isKinematicObject" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_isKinematicObject( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_collisionShape( sgs_GetVar<BulletCollisionShapePointer>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "activationState" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_activationState( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "deactivationTime" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_deactivationTime( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_restitution( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_friction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "rollingFriction" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_rollingFriction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "worldTransform" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_worldTransform( sgs_GetVar<BulletTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationWorldTransform" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_interpolationWorldTransform( sgs_GetVar<BulletTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationLinearVelocity" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_interpolationLinearVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationAngularVelocity" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_interpolationAngularVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "islandTag" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_islandTag( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "companionID" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_companionID( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "companionId" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_companionID( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hitFraction" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_hitFraction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "collisionFlags" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_collisionFlags( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSweptSphereRadius" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_CCDSweptSphereRadius( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSweptSphereRadius" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_CCDSweptSphereRadius( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "CCDMotionThreshold" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_CCDMotionThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "ccdMotionThreshold" ){ static_cast<BulletCollisionObject*>( obj->data )->_set_CCDMotionThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletCollisionObject*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletCollisionObject::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletCollisionObject*>( obj->data )->C, C );
	char bfr[ 53 ];
	sprintf( bfr, "BulletCollisionObject (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nmergesSimulationIslands = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_mergesSimulationIslands(), depth ).push( C ); }
		{ sgs_PushString( C, "\nanisotropicFriction = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_anisotropicFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasAnisotropicFriction = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_hasAnisotropicFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncontactProcessingThreshold = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_contactProcessingThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisStaticObject = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isStaticObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisKinematicObject = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isKinematicObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisStaticOrKinematicObject = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isStaticOrKinematicObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasContactResponse = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_hasContactResponse(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncollisionShape = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_collisionShape(), depth ).push( C ); }
		{ sgs_PushString( C, "\nactivationState = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_activationState(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndeactivationTime = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_deactivationTime(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisActive = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_isActive(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrestitution = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_restitution(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfriction = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_friction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrollingFriction = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_rollingFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nworldTransform = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_worldTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationWorldTransform = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_interpolationWorldTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationLinearVelocity = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_interpolationLinearVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationAngularVelocity = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_interpolationAngularVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nislandTag = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_islandTag(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncompanionID = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_companionID(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncompanionId = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_companionID(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhitFraction = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_hitFraction(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncollisionFlags = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_collisionFlags(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDSweptSphereRadius = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSweptSphereRadius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdSweptSphereRadius = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSweptSphereRadius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDSquareMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSquareMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdSquareMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->_get_CCDSquareMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletCollisionObject*>( obj->data )->userData, depth ).push( C ); }
		sgs_StringConcat( C, 62 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletCollisionObject__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int BulletCollisionObject__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletCollisionObject__sgs_funcs,
		-1, "BulletCollisionObject." );
	return 1;
}

static sgs_ObjInterface BulletCollisionObject__sgs_interface =
{
	"BulletCollisionObject",
	BulletCollisionObject::_sgs_destruct, BulletCollisionObject::gcmark_co, BulletCollisionObject::_sgs_getindex, BulletCollisionObject::_sgs_setindex, NULL, NULL, BulletCollisionObject::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletCollisionObject::_sgs_interface(BulletCollisionObject__sgs_interface, BulletCollisionObject__sgs_ifn);


static int _sgs_method__BulletRigidBody__proceedToTransform( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, proceedToTransform ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->proceedToTransform( sgs_GetVar<BulletTransform>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__predictIntegratedTransform( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, predictIntegratedTransform ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->predictIntegratedTransform( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletRigidBody__saveKinematicState( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, saveKinematicState ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->saveKinematicState( sgs_GetVar<float>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__setDamping( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, setDamping ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->setDamping( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1) ); return 0;
}

static int _sgs_method__BulletRigidBody__setSleepingThresholds( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, setSleepingThresholds ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->setSleepingThresholds( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1) ); return 0;
}

static int _sgs_method__BulletRigidBody__applyDamping( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, applyDamping ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->applyDamping( sgs_GetVar<float>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__setMassProps( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, setMassProps ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->setMassProps( sgs_GetVar<float>()(C,0), sgs_GetVar<btVector3>()(C,1) ); return 0;
}

static int _sgs_method__BulletRigidBody__integrateVelocities( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, integrateVelocities ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->integrateVelocities( sgs_GetVar<float>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__setCenterOfMassTransform( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, setCenterOfMassTransform ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->setCenterOfMassTransform( sgs_GetVar<BulletTransform>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__applyCentralForce( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, applyCentralForce ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->applyCentralForce( sgs_GetVar<btVector3>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__applyTorque( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, applyTorque ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->applyTorque( sgs_GetVar<btVector3>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__applyForce( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, applyForce ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->applyForce( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<btVector3>()(C,1) ); return 0;
}

static int _sgs_method__BulletRigidBody__applyCentralImpulse( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, applyCentralImpulse ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->applyCentralImpulse( sgs_GetVar<btVector3>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__applyTorqueImpulse( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, applyTorqueImpulse ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->applyTorqueImpulse( sgs_GetVar<btVector3>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__applyImpulse( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, applyImpulse ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->applyImpulse( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<btVector3>()(C,1) ); return 0;
}

static int _sgs_method__BulletRigidBody__clearForces( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, clearForces ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->clearForces(  ); return 0;
}

static int _sgs_method__BulletRigidBody__updateInertiaTensor( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, updateInertiaTensor ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->updateInertiaTensor(  ); return 0;
}

static int _sgs_method__BulletRigidBody__getVelocityInLocalPoint( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, getVelocityInLocalPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->getVelocityInLocalPoint( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletRigidBody__translate( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, translate ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->translate( sgs_GetVar<btVector3>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__computeImpulseDenominator( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, computeImpulseDenominator ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->computeImpulseDenominator( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<btVector3>()(C,1) )); return 1;
}

static int _sgs_method__BulletRigidBody__computeAngularImpulseDenominator( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, computeAngularImpulseDenominator ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->computeAngularImpulseDenominator( sgs_GetVar<btVector3>()(C,0) )); return 1;
}

static int _sgs_method__BulletRigidBody__updateDeactivation( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, updateDeactivation ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->updateDeactivation( sgs_GetVar<float>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__computeGyroscopicForce( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, computeGyroscopicForce ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->computeGyroscopicForce( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__BulletRigidBody__calculateSerializeBufferSize( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, calculateSerializeBufferSize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->calculateSerializeBufferSize(  )); return 1;
}

static int _sgs_method__BulletRigidBody__forceActivationState( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, forceActivationState ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->forceActivationState( sgs_GetVar<int>()(C,0) ); return 0;
}

static int _sgs_method__BulletRigidBody__activate( SGS_CTX )
{
	BulletRigidBody* data; if( !SGS_PARSE_METHOD( C, BulletRigidBody::_sgs_interface, data, BulletRigidBody, activate ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->activate( sgs_GetVar<bool>()(C,0) ); return 0;
}

int BulletRigidBody::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletRigidBody*>( obj->data )->C = C;
	static_cast<BulletRigidBody*>( obj->data )->~BulletRigidBody();
	return SGS_SUCCESS;
}

int BulletRigidBody::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBody*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int BulletRigidBody::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBody*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mergesSimulationIslands" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_mergesSimulationIslands() ); return SGS_SUCCESS; }
		SGS_CASE( "anisotropicFriction" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_anisotropicFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "hasAnisotropicFriction" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_hasAnisotropicFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "contactProcessingThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_contactProcessingThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "isStaticObject" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_isStaticObject() ); return SGS_SUCCESS; }
		SGS_CASE( "isKinematicObject" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_isKinematicObject() ); return SGS_SUCCESS; }
		SGS_CASE( "isStaticOrKinematicObject" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_isStaticOrKinematicObject() ); return SGS_SUCCESS; }
		SGS_CASE( "hasContactResponse" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_hasContactResponse() ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_collisionShape() ); return SGS_SUCCESS; }
		SGS_CASE( "activationState" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_activationState() ); return SGS_SUCCESS; }
		SGS_CASE( "deactivationTime" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_deactivationTime() ); return SGS_SUCCESS; }
		SGS_CASE( "isActive" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_isActive() ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_restitution() ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_friction() ); return SGS_SUCCESS; }
		SGS_CASE( "rollingFriction" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_rollingFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "worldTransform" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_worldTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationWorldTransform" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_interpolationWorldTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationLinearVelocity" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_interpolationLinearVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationAngularVelocity" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_interpolationAngularVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "islandTag" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_islandTag() ); return SGS_SUCCESS; }
		SGS_CASE( "companionID" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_companionID() ); return SGS_SUCCESS; }
		SGS_CASE( "companionId" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_companionID() ); return SGS_SUCCESS; }
		SGS_CASE( "hitFraction" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_hitFraction() ); return SGS_SUCCESS; }
		SGS_CASE( "collisionFlags" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_collisionFlags() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSweptSphereRadius" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSweptSphereRadius() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSweptSphereRadius" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSweptSphereRadius() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSquareMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSquareMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSquareMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSquareMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "gravity" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_gravity() ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearDamping() ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularDamping() ); return SGS_SUCCESS; }
		SGS_CASE( "linearSleepingThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearSleepingThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "angularSleepingThreshold" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularSleepingThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "linearFactor" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearFactor() ); return SGS_SUCCESS; }
		SGS_CASE( "angularFactor" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularFactor() ); return SGS_SUCCESS; }
		SGS_CASE( "invMass" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_invMass() ); return SGS_SUCCESS; }
		SGS_CASE( "invInertiaTensorWorld" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_invInertiaTensorWorld() ); return SGS_SUCCESS; }
		SGS_CASE( "totalForce" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_totalForce() ); return SGS_SUCCESS; }
		SGS_CASE( "totalTorque" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_totalTorque() ); return SGS_SUCCESS; }
		SGS_CASE( "invInertiaDiagLocal" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_invInertiaDiagLocal() ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_position() ); return SGS_SUCCESS; }
		SGS_CASE( "orientation" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_orientation() ); return SGS_SUCCESS; }
		SGS_CASE( "transform" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_worldTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "linearVelocity" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "angularVelocity" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "AABB" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_AABB() ); return SGS_SUCCESS; }
		SGS_CASE( "wantsSleeping" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_wantsSleeping() ); return SGS_SUCCESS; }
		SGS_CASE( "isInWorld" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_isInWorld() ); return SGS_SUCCESS; }
		SGS_CASE( "numConstraintRefs" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_numConstraintRefs() ); return SGS_SUCCESS; }
		SGS_CASE( "flags" ){ sgs_PushVar( C, static_cast<BulletRigidBody*>( obj->data )->_get_flags() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletRigidBody::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBody*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "anisotropicFriction" ){ static_cast<BulletRigidBody*>( obj->data )->_set_anisotropicFriction( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "contactProcessingThreshold" ){ static_cast<BulletRigidBody*>( obj->data )->_set_contactProcessingThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "isKinematicObject" ){ static_cast<BulletRigidBody*>( obj->data )->_set_isKinematicObject( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ static_cast<BulletRigidBody*>( obj->data )->_set_collisionShape( sgs_GetVar<BulletCollisionShapePointer>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "activationState" ){ static_cast<BulletRigidBody*>( obj->data )->_set_activationState( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "deactivationTime" ){ static_cast<BulletRigidBody*>( obj->data )->_set_deactivationTime( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ static_cast<BulletRigidBody*>( obj->data )->_set_restitution( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ static_cast<BulletRigidBody*>( obj->data )->_set_friction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "rollingFriction" ){ static_cast<BulletRigidBody*>( obj->data )->_set_rollingFriction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "worldTransform" ){ static_cast<BulletRigidBody*>( obj->data )->_set_worldTransform( sgs_GetVar<BulletTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationWorldTransform" ){ static_cast<BulletRigidBody*>( obj->data )->_set_interpolationWorldTransform( sgs_GetVar<BulletTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationLinearVelocity" ){ static_cast<BulletRigidBody*>( obj->data )->_set_interpolationLinearVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationAngularVelocity" ){ static_cast<BulletRigidBody*>( obj->data )->_set_interpolationAngularVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "islandTag" ){ static_cast<BulletRigidBody*>( obj->data )->_set_islandTag( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "companionID" ){ static_cast<BulletRigidBody*>( obj->data )->_set_companionID( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "companionId" ){ static_cast<BulletRigidBody*>( obj->data )->_set_companionID( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hitFraction" ){ static_cast<BulletRigidBody*>( obj->data )->_set_hitFraction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "collisionFlags" ){ static_cast<BulletRigidBody*>( obj->data )->_set_collisionFlags( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSweptSphereRadius" ){ static_cast<BulletRigidBody*>( obj->data )->_set_CCDSweptSphereRadius( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSweptSphereRadius" ){ static_cast<BulletRigidBody*>( obj->data )->_set_CCDSweptSphereRadius( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "CCDMotionThreshold" ){ static_cast<BulletRigidBody*>( obj->data )->_set_CCDMotionThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "ccdMotionThreshold" ){ static_cast<BulletRigidBody*>( obj->data )->_set_CCDMotionThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletRigidBody*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "gravity" ){ static_cast<BulletRigidBody*>( obj->data )->_set_gravity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ static_cast<BulletRigidBody*>( obj->data )->_set_linearDamping( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ static_cast<BulletRigidBody*>( obj->data )->_set_angularDamping( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "linearSleepingThreshold" ){ static_cast<BulletRigidBody*>( obj->data )->_set_linearSleepingThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angularSleepingThreshold" ){ static_cast<BulletRigidBody*>( obj->data )->_set_angularSleepingThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "linearFactor" ){ static_cast<BulletRigidBody*>( obj->data )->_set_linearFactor( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angularFactor" ){ static_cast<BulletRigidBody*>( obj->data )->_set_angularFactor( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "invInertiaDiagLocal" ){ static_cast<BulletRigidBody*>( obj->data )->_set_invInertiaDiagLocal( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ static_cast<BulletRigidBody*>( obj->data )->_set_position( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "orientation" ){ static_cast<BulletRigidBody*>( obj->data )->_set_orientation( sgs_GetVar<btQuaternion>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "transform" ){ static_cast<BulletRigidBody*>( obj->data )->_set_worldTransform( sgs_GetVar<BulletTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "linearVelocity" ){ static_cast<BulletRigidBody*>( obj->data )->_set_linearVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angularVelocity" ){ static_cast<BulletRigidBody*>( obj->data )->_set_angularVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "flags" ){ static_cast<BulletRigidBody*>( obj->data )->_set_flags( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletRigidBody::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletRigidBody*>( obj->data )->C, C );
	char bfr[ 47 ];
	sprintf( bfr, "BulletRigidBody (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nmergesSimulationIslands = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_mergesSimulationIslands(), depth ).push( C ); }
		{ sgs_PushString( C, "\nanisotropicFriction = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_anisotropicFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasAnisotropicFriction = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_hasAnisotropicFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncontactProcessingThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_contactProcessingThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisStaticObject = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_isStaticObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisKinematicObject = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_isKinematicObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisStaticOrKinematicObject = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_isStaticOrKinematicObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasContactResponse = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_hasContactResponse(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncollisionShape = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_collisionShape(), depth ).push( C ); }
		{ sgs_PushString( C, "\nactivationState = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_activationState(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndeactivationTime = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_deactivationTime(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisActive = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_isActive(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrestitution = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_restitution(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfriction = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_friction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrollingFriction = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_rollingFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nworldTransform = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_worldTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationWorldTransform = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_interpolationWorldTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationLinearVelocity = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_interpolationLinearVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationAngularVelocity = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_interpolationAngularVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nislandTag = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_islandTag(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncompanionID = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_companionID(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncompanionId = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_companionID(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhitFraction = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_hitFraction(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncollisionFlags = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_collisionFlags(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDSweptSphereRadius = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSweptSphereRadius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdSweptSphereRadius = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSweptSphereRadius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDSquareMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSquareMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdSquareMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_CCDSquareMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\ngravity = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_gravity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearDamping = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearDamping(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangularDamping = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularDamping(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearSleepingThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearSleepingThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangularSleepingThreshold = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularSleepingThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearFactor = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearFactor(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangularFactor = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularFactor(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninvMass = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_invMass(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninvInertiaTensorWorld = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_invInertiaTensorWorld(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntotalForce = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_totalForce(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntotalTorque = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_totalTorque(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninvInertiaDiagLocal = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_invInertiaDiagLocal(), depth ).push( C ); }
		{ sgs_PushString( C, "\nposition = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_position(), depth ).push( C ); }
		{ sgs_PushString( C, "\norientation = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_orientation(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntransform = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_worldTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearVelocity = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_linearVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangularVelocity = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_angularVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nAABB = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_AABB(), depth ).push( C ); }
		{ sgs_PushString( C, "\nwantsSleeping = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_wantsSleeping(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisInWorld = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_isInWorld(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumConstraintRefs = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_numConstraintRefs(), depth ).push( C ); }
		{ sgs_PushString( C, "\nflags = " ); sgs_DumpData( C, static_cast<BulletRigidBody*>( obj->data )->_get_flags(), depth ).push( C ); }
		sgs_StringConcat( C, 106 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletRigidBody__sgs_funcs[] =
{
	{ "proceedToTransform", _sgs_method__BulletRigidBody__proceedToTransform },
	{ "predictIntegratedTransform", _sgs_method__BulletRigidBody__predictIntegratedTransform },
	{ "saveKinematicState", _sgs_method__BulletRigidBody__saveKinematicState },
	{ "setDamping", _sgs_method__BulletRigidBody__setDamping },
	{ "setSleepingThresholds", _sgs_method__BulletRigidBody__setSleepingThresholds },
	{ "applyDamping", _sgs_method__BulletRigidBody__applyDamping },
	{ "setMassProps", _sgs_method__BulletRigidBody__setMassProps },
	{ "integrateVelocities", _sgs_method__BulletRigidBody__integrateVelocities },
	{ "setCenterOfMassTransform", _sgs_method__BulletRigidBody__setCenterOfMassTransform },
	{ "applyCentralForce", _sgs_method__BulletRigidBody__applyCentralForce },
	{ "applyTorque", _sgs_method__BulletRigidBody__applyTorque },
	{ "applyForce", _sgs_method__BulletRigidBody__applyForce },
	{ "applyCentralImpulse", _sgs_method__BulletRigidBody__applyCentralImpulse },
	{ "applyTorqueImpulse", _sgs_method__BulletRigidBody__applyTorqueImpulse },
	{ "applyImpulse", _sgs_method__BulletRigidBody__applyImpulse },
	{ "clearForces", _sgs_method__BulletRigidBody__clearForces },
	{ "updateInertiaTensor", _sgs_method__BulletRigidBody__updateInertiaTensor },
	{ "getVelocityInLocalPoint", _sgs_method__BulletRigidBody__getVelocityInLocalPoint },
	{ "translate", _sgs_method__BulletRigidBody__translate },
	{ "computeImpulseDenominator", _sgs_method__BulletRigidBody__computeImpulseDenominator },
	{ "computeAngularImpulseDenominator", _sgs_method__BulletRigidBody__computeAngularImpulseDenominator },
	{ "updateDeactivation", _sgs_method__BulletRigidBody__updateDeactivation },
	{ "computeGyroscopicForce", _sgs_method__BulletRigidBody__computeGyroscopicForce },
	{ "calculateSerializeBufferSize", _sgs_method__BulletRigidBody__calculateSerializeBufferSize },
	{ "forceActivationState", _sgs_method__BulletRigidBody__forceActivationState },
	{ "activate", _sgs_method__BulletRigidBody__activate },
	{ NULL, NULL },
};

static int BulletRigidBody__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletRigidBody__sgs_funcs,
		-1, "BulletRigidBody." );
	return 1;
}

static sgs_ObjInterface BulletRigidBody__sgs_interface =
{
	"BulletRigidBody",
	BulletRigidBody::_sgs_destruct, BulletRigidBody::gcmark_co, BulletRigidBody::_sgs_getindex, BulletRigidBody::_sgs_setindex, NULL, NULL, BulletRigidBody::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletRigidBody::_sgs_interface(BulletRigidBody__sgs_interface, BulletRigidBody__sgs_ifn, &BulletCollisionObject::_sgs_interface);


int BulletGhostObject::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletGhostObject*>( obj->data )->C = C;
	static_cast<BulletGhostObject*>( obj->data )->~BulletGhostObject();
	return SGS_SUCCESS;
}

int BulletGhostObject::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletGhostObject*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int BulletGhostObject::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletGhostObject*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mergesSimulationIslands" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_mergesSimulationIslands() ); return SGS_SUCCESS; }
		SGS_CASE( "anisotropicFriction" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_anisotropicFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "hasAnisotropicFriction" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_hasAnisotropicFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "contactProcessingThreshold" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_contactProcessingThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "isStaticObject" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_isStaticObject() ); return SGS_SUCCESS; }
		SGS_CASE( "isKinematicObject" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_isKinematicObject() ); return SGS_SUCCESS; }
		SGS_CASE( "isStaticOrKinematicObject" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_isStaticOrKinematicObject() ); return SGS_SUCCESS; }
		SGS_CASE( "hasContactResponse" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_hasContactResponse() ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_collisionShape() ); return SGS_SUCCESS; }
		SGS_CASE( "activationState" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_activationState() ); return SGS_SUCCESS; }
		SGS_CASE( "deactivationTime" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_deactivationTime() ); return SGS_SUCCESS; }
		SGS_CASE( "isActive" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_isActive() ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_restitution() ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_friction() ); return SGS_SUCCESS; }
		SGS_CASE( "rollingFriction" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_rollingFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "worldTransform" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_worldTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationWorldTransform" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_interpolationWorldTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationLinearVelocity" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_interpolationLinearVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationAngularVelocity" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_interpolationAngularVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "islandTag" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_islandTag() ); return SGS_SUCCESS; }
		SGS_CASE( "companionID" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_companionID() ); return SGS_SUCCESS; }
		SGS_CASE( "companionId" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_companionID() ); return SGS_SUCCESS; }
		SGS_CASE( "hitFraction" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_hitFraction() ); return SGS_SUCCESS; }
		SGS_CASE( "collisionFlags" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_collisionFlags() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSweptSphereRadius" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSweptSphereRadius() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSweptSphereRadius" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSweptSphereRadius() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSquareMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSquareMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSquareMotionThreshold" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSquareMotionThreshold() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "numOverlappingObjects" ){ sgs_PushVar( C, static_cast<BulletGhostObject*>( obj->data )->_get_numOverlappingObjects() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletGhostObject::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletGhostObject*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "anisotropicFriction" ){ static_cast<BulletGhostObject*>( obj->data )->_set_anisotropicFriction( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "contactProcessingThreshold" ){ static_cast<BulletGhostObject*>( obj->data )->_set_contactProcessingThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "isKinematicObject" ){ static_cast<BulletGhostObject*>( obj->data )->_set_isKinematicObject( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "collisionShape" ){ static_cast<BulletGhostObject*>( obj->data )->_set_collisionShape( sgs_GetVar<BulletCollisionShapePointer>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "activationState" ){ static_cast<BulletGhostObject*>( obj->data )->_set_activationState( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "deactivationTime" ){ static_cast<BulletGhostObject*>( obj->data )->_set_deactivationTime( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ static_cast<BulletGhostObject*>( obj->data )->_set_restitution( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ static_cast<BulletGhostObject*>( obj->data )->_set_friction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "rollingFriction" ){ static_cast<BulletGhostObject*>( obj->data )->_set_rollingFriction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "worldTransform" ){ static_cast<BulletGhostObject*>( obj->data )->_set_worldTransform( sgs_GetVar<BulletTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationWorldTransform" ){ static_cast<BulletGhostObject*>( obj->data )->_set_interpolationWorldTransform( sgs_GetVar<BulletTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationLinearVelocity" ){ static_cast<BulletGhostObject*>( obj->data )->_set_interpolationLinearVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "interpolationAngularVelocity" ){ static_cast<BulletGhostObject*>( obj->data )->_set_interpolationAngularVelocity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "islandTag" ){ static_cast<BulletGhostObject*>( obj->data )->_set_islandTag( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "companionID" ){ static_cast<BulletGhostObject*>( obj->data )->_set_companionID( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "companionId" ){ static_cast<BulletGhostObject*>( obj->data )->_set_companionID( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hitFraction" ){ static_cast<BulletGhostObject*>( obj->data )->_set_hitFraction( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "collisionFlags" ){ static_cast<BulletGhostObject*>( obj->data )->_set_collisionFlags( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "CCDSweptSphereRadius" ){ static_cast<BulletGhostObject*>( obj->data )->_set_CCDSweptSphereRadius( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "ccdSweptSphereRadius" ){ static_cast<BulletGhostObject*>( obj->data )->_set_CCDSweptSphereRadius( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "CCDMotionThreshold" ){ static_cast<BulletGhostObject*>( obj->data )->_set_CCDMotionThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "ccdMotionThreshold" ){ static_cast<BulletGhostObject*>( obj->data )->_set_CCDMotionThreshold( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletGhostObject*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletGhostObject::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletGhostObject*>( obj->data )->C, C );
	char bfr[ 49 ];
	sprintf( bfr, "BulletGhostObject (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nmergesSimulationIslands = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_mergesSimulationIslands(), depth ).push( C ); }
		{ sgs_PushString( C, "\nanisotropicFriction = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_anisotropicFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasAnisotropicFriction = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_hasAnisotropicFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncontactProcessingThreshold = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_contactProcessingThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisStaticObject = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_isStaticObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisKinematicObject = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_isKinematicObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisStaticOrKinematicObject = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_isStaticOrKinematicObject(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasContactResponse = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_hasContactResponse(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncollisionShape = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_collisionShape(), depth ).push( C ); }
		{ sgs_PushString( C, "\nactivationState = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_activationState(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndeactivationTime = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_deactivationTime(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisActive = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_isActive(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrestitution = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_restitution(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfriction = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_friction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrollingFriction = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_rollingFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nworldTransform = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_worldTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationWorldTransform = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_interpolationWorldTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationLinearVelocity = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_interpolationLinearVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninterpolationAngularVelocity = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_interpolationAngularVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nislandTag = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_islandTag(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncompanionID = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_companionID(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncompanionId = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_companionID(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhitFraction = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_hitFraction(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncollisionFlags = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_collisionFlags(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDSweptSphereRadius = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSweptSphereRadius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdSweptSphereRadius = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSweptSphereRadius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nCCDSquareMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSquareMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nccdSquareMotionThreshold = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_CCDSquareMotionThreshold(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nnumOverlappingObjects = " ); sgs_DumpData( C, static_cast<BulletGhostObject*>( obj->data )->_get_numOverlappingObjects(), depth ).push( C ); }
		sgs_StringConcat( C, 64 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletGhostObject__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int BulletGhostObject__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletGhostObject__sgs_funcs,
		-1, "BulletGhostObject." );
	return 1;
}

static sgs_ObjInterface BulletGhostObject__sgs_interface =
{
	"BulletGhostObject",
	BulletGhostObject::_sgs_destruct, BulletGhostObject::gcmark_co, BulletGhostObject::_sgs_getindex, BulletGhostObject::_sgs_setindex, NULL, NULL, BulletGhostObject::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletGhostObject::_sgs_interface(BulletGhostObject__sgs_interface, BulletGhostObject__sgs_ifn, &BulletCollisionObject::_sgs_interface);


static int _sgs_method__BulletDynamicsWorld__stepSimulation( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, stepSimulation ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->stepSimulation( sgs_GetVar<float>()(C,0), sgs_GetVar<int>()(C,1), sgs_GetVar<float>()(C,2) )); return 1;
}

static int _sgs_method__BulletDynamicsWorld__debugDrawWorld( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, debugDrawWorld ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->debugDrawWorld(  ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__synchronizeMotionStates( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, synchronizeMotionStates ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->synchronizeMotionStates(  ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__addRigidBody( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, addRigidBody ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->addRigidBody( sgs_GetVar<BulletRigidBodyHandle>()(C,0), sgs_GetVar<int>()(C,1), sgs_GetVar<int>()(C,2) ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__removeRigidBody( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, removeRigidBody ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->removeRigidBody( sgs_GetVar<BulletRigidBodyHandle>()(C,0) ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__clearForces( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, clearForces ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->clearForces(  ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__updateSingleAABB( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, updateSingleAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->updateSingleAABB( sgs_GetVar<sgsVariable>()(C,0) ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__updateAABBs( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, updateAABBs ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->updateAABBs(  ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__computeOverlappingPairs( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, computeOverlappingPairs ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->computeOverlappingPairs(  ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__rayTestClosest( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, rayTestClosest ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->rayTestClosest( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<btVector3>()(C,1), sgs_GetVar<int>()(C,2), sgs_GetVar<int>()(C,3) );
}

static int _sgs_method__BulletDynamicsWorld__rayTestAll( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, rayTestAll ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->rayTestAll( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<btVector3>()(C,1), sgs_GetVar<int>()(C,2), sgs_GetVar<int>()(C,3) )); return 1;
}

static int _sgs_method__BulletDynamicsWorld__rayTestCustom( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, rayTestCustom ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->rayTestCustom( sgs_GetVar<btVector3>()(C,0), sgs_GetVar<btVector3>()(C,1), sgs_GetVar<int>()(C,2), sgs_GetVar<int>()(C,3), sgs_GetVar<sgsVariable>()(C,4) ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__convexSweepTestClosest( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, convexSweepTestClosest ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->convexSweepTestClosest( sgs_GetVar<BulletConvexShapePointer>()(C,0), sgs_GetVar<BulletTransform>()(C,1), sgs_GetVar<BulletTransform>()(C,2), sgs_GetVar<int>()(C,3), sgs_GetVar<int>()(C,4), sgs_GetVar<float>()(C,5) );
}

static int _sgs_method__BulletDynamicsWorld__convexSweepTestCustom( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, convexSweepTestCustom ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->convexSweepTestCustom( sgs_GetVar<BulletConvexShapePointer>()(C,0), sgs_GetVar<BulletTransform>()(C,1), sgs_GetVar<BulletTransform>()(C,2), sgs_GetVar<int>()(C,3), sgs_GetVar<int>()(C,4), sgs_GetVar<sgsVariable>()(C,5), sgs_GetVar<float>()(C,6) ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__addCollisionObject( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, addCollisionObject ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->addCollisionObject( sgs_GetVar<sgsVariable>()(C,0), sgs_GetVar<int>()(C,1), sgs_GetVar<int>()(C,2) ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__removeCollisionObject( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, removeCollisionObject ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->removeCollisionObject( sgs_GetVar<sgsVariable>()(C,0) ); return 0;
}

static int _sgs_method__BulletDynamicsWorld__performDiscreteCollisionDetection( SGS_CTX )
{
	BulletDynamicsWorld* data; if( !SGS_PARSE_METHOD( C, BulletDynamicsWorld::_sgs_interface, data, BulletDynamicsWorld, performDiscreteCollisionDetection ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->performDiscreteCollisionDetection(  ); return 0;
}

int BulletDynamicsWorld::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<BulletDynamicsWorld*>( obj->data )->C = C;
	static_cast<BulletDynamicsWorld*>( obj->data )->~BulletDynamicsWorld();
	return SGS_SUCCESS;
}

int BulletDynamicsWorld::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletDynamicsWorld*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<BulletDynamicsWorld*>( obj->data )->userData );
	return SGS_SUCCESS;
}

int BulletDynamicsWorld::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletDynamicsWorld*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "gravity" ){ sgs_PushVar( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_gravity() ); return SGS_SUCCESS; }
		SGS_CASE( "numConstraints" ){ sgs_PushVar( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_numConstraints() ); return SGS_SUCCESS; }
		SGS_CASE( "numCollisionObjects" ){ sgs_PushVar( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_numCollisionObjects() ); return SGS_SUCCESS; }
		SGS_CASE( "forceUpdateAllAABBs" ){ sgs_PushVar( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_forceUpdateAllAABBs() ); return SGS_SUCCESS; }
		SGS_CASE( "forceUpdateAllAabbs" ){ sgs_PushVar( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_forceUpdateAllAABBs() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<BulletDynamicsWorld*>( obj->data )->userData ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletDynamicsWorld::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletDynamicsWorld*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "gravity" ){ static_cast<BulletDynamicsWorld*>( obj->data )->_set_gravity( sgs_GetVar<btVector3>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "forceUpdateAllAABBs" ){ static_cast<BulletDynamicsWorld*>( obj->data )->_set_forceUpdateAllAABBs( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "forceUpdateAllAabbs" ){ static_cast<BulletDynamicsWorld*>( obj->data )->_set_forceUpdateAllAABBs( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<BulletDynamicsWorld*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int BulletDynamicsWorld::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<BulletDynamicsWorld*>( obj->data )->C, C );
	char bfr[ 51 ];
	sprintf( bfr, "BulletDynamicsWorld (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ngravity = " ); sgs_DumpData( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_gravity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumConstraints = " ); sgs_DumpData( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_numConstraints(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnumCollisionObjects = " ); sgs_DumpData( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_numCollisionObjects(), depth ).push( C ); }
		{ sgs_PushString( C, "\nforceUpdateAllAABBs = " ); sgs_DumpData( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_forceUpdateAllAABBs(), depth ).push( C ); }
		{ sgs_PushString( C, "\nforceUpdateAllAabbs = " ); sgs_DumpData( C, static_cast<BulletDynamicsWorld*>( obj->data )->_get_forceUpdateAllAABBs(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<BulletDynamicsWorld*>( obj->data )->userData, depth ).push( C ); }
		sgs_StringConcat( C, 12 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst BulletDynamicsWorld__sgs_funcs[] =
{
	{ "stepSimulation", _sgs_method__BulletDynamicsWorld__stepSimulation },
	{ "debugDrawWorld", _sgs_method__BulletDynamicsWorld__debugDrawWorld },
	{ "synchronizeMotionStates", _sgs_method__BulletDynamicsWorld__synchronizeMotionStates },
	{ "addRigidBody", _sgs_method__BulletDynamicsWorld__addRigidBody },
	{ "removeRigidBody", _sgs_method__BulletDynamicsWorld__removeRigidBody },
	{ "clearForces", _sgs_method__BulletDynamicsWorld__clearForces },
	{ "updateSingleAABB", _sgs_method__BulletDynamicsWorld__updateSingleAABB },
	{ "updateAABBs", _sgs_method__BulletDynamicsWorld__updateAABBs },
	{ "computeOverlappingPairs", _sgs_method__BulletDynamicsWorld__computeOverlappingPairs },
	{ "rayTestClosest", _sgs_method__BulletDynamicsWorld__rayTestClosest },
	{ "rayTestAll", _sgs_method__BulletDynamicsWorld__rayTestAll },
	{ "rayTestCustom", _sgs_method__BulletDynamicsWorld__rayTestCustom },
	{ "convexSweepTestClosest", _sgs_method__BulletDynamicsWorld__convexSweepTestClosest },
	{ "convexSweepTestCustom", _sgs_method__BulletDynamicsWorld__convexSweepTestCustom },
	{ "addCollisionObject", _sgs_method__BulletDynamicsWorld__addCollisionObject },
	{ "removeCollisionObject", _sgs_method__BulletDynamicsWorld__removeCollisionObject },
	{ "performDiscreteCollisionDetection", _sgs_method__BulletDynamicsWorld__performDiscreteCollisionDetection },
	{ NULL, NULL },
};

static int BulletDynamicsWorld__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		BulletDynamicsWorld__sgs_funcs,
		-1, "BulletDynamicsWorld." );
	return 1;
}

static sgs_ObjInterface BulletDynamicsWorld__sgs_interface =
{
	"BulletDynamicsWorld",
	BulletDynamicsWorld::_sgs_destruct, BulletDynamicsWorld::_sgs_gcmark, BulletDynamicsWorld::_sgs_getindex, BulletDynamicsWorld::_sgs_setindex, NULL, NULL, BulletDynamicsWorld::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface BulletDynamicsWorld::_sgs_interface(BulletDynamicsWorld__sgs_interface, BulletDynamicsWorld__sgs_ifn);

