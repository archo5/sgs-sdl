// SGS/CPP-BC
// warning: do not modify this file, it may be regenerated during any build

#include "box2d.hpp"

static int _sgs_method__Box2DRotation__SetIdentity( SGS_CTX )
{
	Box2DRotation* data; if( !SGS_PARSE_METHOD( C, Box2DRotation::_sgs_interface, data, Box2DRotation, SetIdentity ) ) return 0;
	data->SetIdentity(  ); return 0;
}

int Box2DRotation::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DRotation*>( obj->data )->~Box2DRotation();
	return SGS_SUCCESS;
}

int Box2DRotation::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	return SGS_SUCCESS;
}

int Box2DRotation::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "angle" ){ sgs_PushVar( C, static_cast<Box2DRotation*>( obj->data )->_getAngle() ); return SGS_SUCCESS; }
		SGS_CASE( "xAxis" ){ sgs_PushVar( C, static_cast<Box2DRotation*>( obj->data )->_getXAxis() ); return SGS_SUCCESS; }
		SGS_CASE( "yAxis" ){ sgs_PushVar( C, static_cast<Box2DRotation*>( obj->data )->_getYAxis() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DRotation::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "angle" ){ static_cast<Box2DRotation*>( obj->data )->_setAngle( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DRotation::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	char bfr[ 45 ];
	sprintf( bfr, "Box2DRotation (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nangle = " ); sgs_DumpData( C, static_cast<Box2DRotation*>( obj->data )->_getAngle(), depth ).push( C ); }
		{ sgs_PushString( C, "\nxAxis = " ); sgs_DumpData( C, static_cast<Box2DRotation*>( obj->data )->_getXAxis(), depth ).push( C ); }
		{ sgs_PushString( C, "\nyAxis = " ); sgs_DumpData( C, static_cast<Box2DRotation*>( obj->data )->_getYAxis(), depth ).push( C ); }
		sgs_StringConcat( C, 6 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DRotation__sgs_funcs[] =
{
	{ "SetIdentity", _sgs_method__Box2DRotation__SetIdentity },
	{ NULL, NULL },
};

static int Box2DRotation__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DRotation__sgs_funcs,
		-1, "Box2DRotation." );
	return 1;
}

static sgs_ObjInterface Box2DRotation__sgs_interface =
{
	"Box2DRotation",
	Box2DRotation::_sgs_destruct, Box2DRotation::_sgs_gcmark, Box2DRotation::_sgs_getindex, Box2DRotation::_sgs_setindex, NULL, NULL, Box2DRotation::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DRotation::_sgs_interface(Box2DRotation__sgs_interface, Box2DRotation__sgs_ifn);


int Box2DTransform::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DTransform*>( obj->data )->~Box2DTransform();
	return SGS_SUCCESS;
}

int Box2DTransform::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	return SGS_SUCCESS;
}

int Box2DTransform::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "p" ){ sgs_PushVar( C, static_cast<Box2DTransform*>( obj->data )->p ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ sgs_PushVar( C, static_cast<Box2DTransform*>( obj->data )->p ); return SGS_SUCCESS; }
		SGS_CASE( "q" ){ sgs_PushVar( C, static_cast<Box2DTransform*>( obj->data )->_getRotation() ); return SGS_SUCCESS; }
		SGS_CASE( "rotation" ){ sgs_PushVar( C, static_cast<Box2DTransform*>( obj->data )->_getRotation() ); return SGS_SUCCESS; }
		SGS_CASE( "angle" ){ sgs_PushVar( C, static_cast<Box2DTransform*>( obj->data )->_getAngle() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DTransform::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "p" ){ static_cast<Box2DTransform*>( obj->data )->p = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ static_cast<Box2DTransform*>( obj->data )->p = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "q" ){ static_cast<Box2DTransform*>( obj->data )->_setRotation( sgs_GetVar<Box2DRotation>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "rotation" ){ static_cast<Box2DTransform*>( obj->data )->_setRotation( sgs_GetVar<Box2DRotation>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angle" ){ static_cast<Box2DTransform*>( obj->data )->_setAngle( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DTransform::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	char bfr[ 46 ];
	sprintf( bfr, "Box2DTransform (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\np = " ); sgs_DumpData( C, static_cast<Box2DTransform*>( obj->data )->p, depth ).push( C ); }
		{ sgs_PushString( C, "\nposition = " ); sgs_DumpData( C, static_cast<Box2DTransform*>( obj->data )->p, depth ).push( C ); }
		{ sgs_PushString( C, "\nq = " ); sgs_DumpData( C, static_cast<Box2DTransform*>( obj->data )->_getRotation(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrotation = " ); sgs_DumpData( C, static_cast<Box2DTransform*>( obj->data )->_getRotation(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangle = " ); sgs_DumpData( C, static_cast<Box2DTransform*>( obj->data )->_getAngle(), depth ).push( C ); }
		sgs_StringConcat( C, 10 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DTransform__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DTransform__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DTransform__sgs_funcs,
		-1, "Box2DTransform." );
	return 1;
}

static sgs_ObjInterface Box2DTransform__sgs_interface =
{
	"Box2DTransform",
	Box2DTransform::_sgs_destruct, Box2DTransform::_sgs_gcmark, Box2DTransform::_sgs_getindex, Box2DTransform::_sgs_setindex, NULL, NULL, Box2DTransform::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DTransform::_sgs_interface(Box2DTransform__sgs_interface, Box2DTransform__sgs_ifn);


int Box2DMassData::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DMassData*>( obj->data )->~Box2DMassData();
	return SGS_SUCCESS;
}

int Box2DMassData::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	return SGS_SUCCESS;
}

int Box2DMassData::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mass" ){ sgs_PushVar( C, static_cast<Box2DMassData*>( obj->data )->mass ); return SGS_SUCCESS; }
		SGS_CASE( "center" ){ sgs_PushVar( C, static_cast<Box2DMassData*>( obj->data )->center ); return SGS_SUCCESS; }
		SGS_CASE( "I" ){ sgs_PushVar( C, static_cast<Box2DMassData*>( obj->data )->I ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DMassData::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "mass" ){ static_cast<Box2DMassData*>( obj->data )->mass = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "center" ){ static_cast<Box2DMassData*>( obj->data )->center = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "I" ){ static_cast<Box2DMassData*>( obj->data )->I = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DMassData::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	char bfr[ 45 ];
	sprintf( bfr, "Box2DMassData (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nmass = " ); sgs_DumpData( C, static_cast<Box2DMassData*>( obj->data )->mass, depth ).push( C ); }
		{ sgs_PushString( C, "\ncenter = " ); sgs_DumpData( C, static_cast<Box2DMassData*>( obj->data )->center, depth ).push( C ); }
		{ sgs_PushString( C, "\nI = " ); sgs_DumpData( C, static_cast<Box2DMassData*>( obj->data )->I, depth ).push( C ); }
		sgs_StringConcat( C, 6 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DMassData__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DMassData__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DMassData__sgs_funcs,
		-1, "Box2DMassData." );
	return 1;
}

static sgs_ObjInterface Box2DMassData__sgs_interface =
{
	"Box2DMassData",
	Box2DMassData::_sgs_destruct, Box2DMassData::_sgs_gcmark, Box2DMassData::_sgs_getindex, Box2DMassData::_sgs_setindex, NULL, NULL, Box2DMassData::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DMassData::_sgs_interface(Box2DMassData__sgs_interface, Box2DMassData__sgs_ifn);


int Box2DFilterData::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DFilterData*>( obj->data )->~Box2DFilterData();
	return SGS_SUCCESS;
}

int Box2DFilterData::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	return SGS_SUCCESS;
}

int Box2DFilterData::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "categoryBits" ){ sgs_PushVar( C, static_cast<Box2DFilterData*>( obj->data )->categoryBits ); return SGS_SUCCESS; }
		SGS_CASE( "maskBits" ){ sgs_PushVar( C, static_cast<Box2DFilterData*>( obj->data )->maskBits ); return SGS_SUCCESS; }
		SGS_CASE( "groupIndex" ){ sgs_PushVar( C, static_cast<Box2DFilterData*>( obj->data )->groupIndex ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFilterData::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "categoryBits" ){ static_cast<Box2DFilterData*>( obj->data )->categoryBits = sgs_GetVar<uint16>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maskBits" ){ static_cast<Box2DFilterData*>( obj->data )->maskBits = sgs_GetVar<uint16>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "groupIndex" ){ static_cast<Box2DFilterData*>( obj->data )->groupIndex = sgs_GetVar<int16>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFilterData::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	char bfr[ 47 ];
	sprintf( bfr, "Box2DFilterData (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ncategoryBits = " ); sgs_DumpData( C, static_cast<Box2DFilterData*>( obj->data )->categoryBits, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaskBits = " ); sgs_DumpData( C, static_cast<Box2DFilterData*>( obj->data )->maskBits, depth ).push( C ); }
		{ sgs_PushString( C, "\ngroupIndex = " ); sgs_DumpData( C, static_cast<Box2DFilterData*>( obj->data )->groupIndex, depth ).push( C ); }
		sgs_StringConcat( C, 6 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DFilterData__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DFilterData__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DFilterData__sgs_funcs,
		-1, "Box2DFilterData." );
	return 1;
}

static sgs_ObjInterface Box2DFilterData__sgs_interface =
{
	"Box2DFilterData",
	Box2DFilterData::_sgs_destruct, Box2DFilterData::_sgs_gcmark, Box2DFilterData::_sgs_getindex, Box2DFilterData::_sgs_setindex, NULL, NULL, Box2DFilterData::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DFilterData::_sgs_interface(Box2DFilterData__sgs_interface, Box2DFilterData__sgs_ifn);


static int _sgs_method__Box2DShape__TestPoint( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, TestPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->TestPoint( sgs_GetVar<Box2DTransform>()(C,0), sgs_GetVar<b2Vec2>()(C,1) )); return 1;
}

static int _sgs_method__Box2DShape__RayCast( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, RayCast ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->RayCast( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<b2Vec2>()(C,1), sgs_GetVar<float32>()(C,2), sgs_GetVar<Box2DTransform>()(C,3), sgs_GetVar<int32>()(C,4) );
}

static int _sgs_method__Box2DShape__ComputeAABB( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, ComputeAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->ComputeAABB( sgs_GetVar<Box2DTransform>()(C,0), sgs_GetVar<int32>()(C,1) )); return 1;
}

static int _sgs_method__Box2DShape__ComputeMass( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, ComputeMass ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->ComputeMass( sgs_GetVar<float32>()(C,0) )); return 1;
}

static int _sgs_method__Box2DShape__SetEdge( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, SetEdge ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetEdge( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<b2Vec2>()(C,1) ); return 0;
}

static int _sgs_method__Box2DShape__GetVertexArray( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, GetVertexArray ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->GetVertexArray(  );
}

static int _sgs_method__Box2DShape__GetVertexFloatArray( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, GetVertexFloatArray ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->GetVertexFloatArray(  );
}

static int _sgs_method__Box2DShape__SetVertices( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, SetVertices ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetVertices(  ); return 0;
}

static int _sgs_method__Box2DShape__SetVerticesFromVec2Array( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, SetVerticesFromVec2Array ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetVerticesFromVec2Array( sgs_GetVar<sgsVariable>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__SetVerticesFromFloatArray( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, SetVerticesFromFloatArray ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetVerticesFromFloatArray( sgs_GetVar<FloatArray>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__SetAsBox( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, SetAsBox ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetAsBox( sgs_GetVar<float32>()(C,0), sgs_GetVar<float32>()(C,1), sgs_GetVar<b2Vec2>()(C,2), sgs_GetVar<float32>()(C,3) ); return 0;
}

static int _sgs_method__Box2DShape__GetVertex( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, GetVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetVertex( sgs_GetVar<int32>()(C,0) )); return 1;
}

static int _sgs_method__Box2DShape__Validate( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, Validate ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->Validate(  )); return 1;
}

static int _sgs_method__Box2DShape__CreateLoop( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, CreateLoop ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->CreateLoop(  ); return 0;
}

static int _sgs_method__Box2DShape__CreateLoopFromVec2Array( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, CreateLoopFromVec2Array ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->CreateLoopFromVec2Array( sgs_GetVar<sgsVariable>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__CreateLoopFromFloatArray( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, CreateLoopFromFloatArray ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->CreateLoopFromFloatArray( sgs_GetVar<FloatArray>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__CreateChain( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, CreateChain ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->CreateChain(  ); return 0;
}

static int _sgs_method__Box2DShape__CreateChainFromVec2Array( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, CreateChainFromVec2Array ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->CreateChainFromVec2Array( sgs_GetVar<sgsVariable>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__CreateChainFromFloatArray( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, CreateChainFromFloatArray ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->CreateChainFromFloatArray( sgs_GetVar<FloatArray>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__SetPrevVertex( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, SetPrevVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetPrevVertex( sgs_GetVar<b2Vec2>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__SetNextVertex( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, SetNextVertex ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetNextVertex( sgs_GetVar<b2Vec2>()(C,0) ); return 0;
}

static int _sgs_method__Box2DShape__GetChildEdge( SGS_CTX )
{
	Box2DShape* data; if( !SGS_PARSE_METHOD( C, Box2DShape::_sgs_interface, data, Box2DShape, GetChildEdge ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->GetChildEdge( sgs_GetVar<int32>()(C,0) );
}

int Box2DShape::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DShape*>( obj->data )->C = C;
	static_cast<Box2DShape*>( obj->data )->~Box2DShape();
	return SGS_SUCCESS;
}

int Box2DShape::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DShape*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DShape::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "childCount" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getChildCount() ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getPosition() ); return SGS_SUCCESS; }
		SGS_CASE( "radius" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getRadius() ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex1" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex1() ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex2" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex2() ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex0" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex0() ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex3" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex3() ); return SGS_SUCCESS; }
		SGS_CASE( "hasEdgeVertex0" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getHasEdgeVertex0() ); return SGS_SUCCESS; }
		SGS_CASE( "hasEdgeVertex3" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getHasEdgeVertex3() ); return SGS_SUCCESS; }
		SGS_CASE( "vertexCount" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getVertexCount() ); return SGS_SUCCESS; }
		SGS_CASE( "chainPrevVertex" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getChainPrevVertex() ); return SGS_SUCCESS; }
		SGS_CASE( "chainNextVertex" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getChainNextVertex() ); return SGS_SUCCESS; }
		SGS_CASE( "hasChainPrevVertex" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getHasChainPrevVertex() ); return SGS_SUCCESS; }
		SGS_CASE( "hasChainNextVertex" ){ sgs_PushVar( C, static_cast<Box2DShape*>( obj->data )->_getHasChainNextVertex() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DShape::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DShape*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" ){ static_cast<Box2DShape*>( obj->data )->_setPosition( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "radius" ){ static_cast<Box2DShape*>( obj->data )->_setRadius( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex1" ){ static_cast<Box2DShape*>( obj->data )->_setEdgeVertex1( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex2" ){ static_cast<Box2DShape*>( obj->data )->_setEdgeVertex2( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex0" ){ static_cast<Box2DShape*>( obj->data )->_setEdgeVertex0( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "edgeVertex3" ){ static_cast<Box2DShape*>( obj->data )->_setEdgeVertex3( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hasEdgeVertex0" ){ static_cast<Box2DShape*>( obj->data )->_setHasEdgeVertex0( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hasEdgeVertex3" ){ static_cast<Box2DShape*>( obj->data )->_setHasEdgeVertex3( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "chainPrevVertex" ){ static_cast<Box2DShape*>( obj->data )->_setChainPrevVertex( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "chainNextVertex" ){ static_cast<Box2DShape*>( obj->data )->_setChainNextVertex( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hasChainPrevVertex" ){ static_cast<Box2DShape*>( obj->data )->_setHasChainPrevVertex( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hasChainNextVertex" ){ static_cast<Box2DShape*>( obj->data )->_setHasChainNextVertex( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DShape::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DShape*>( obj->data )->C, C );
	char bfr[ 42 ];
	sprintf( bfr, "Box2DShape (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nchildCount = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getChildCount(), depth ).push( C ); }
		{ sgs_PushString( C, "\nposition = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getPosition(), depth ).push( C ); }
		{ sgs_PushString( C, "\nradius = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getRadius(), depth ).push( C ); }
		{ sgs_PushString( C, "\nedgeVertex1 = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex1(), depth ).push( C ); }
		{ sgs_PushString( C, "\nedgeVertex2 = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex2(), depth ).push( C ); }
		{ sgs_PushString( C, "\nedgeVertex0 = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex0(), depth ).push( C ); }
		{ sgs_PushString( C, "\nedgeVertex3 = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getEdgeVertex3(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasEdgeVertex0 = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getHasEdgeVertex0(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasEdgeVertex3 = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getHasEdgeVertex3(), depth ).push( C ); }
		{ sgs_PushString( C, "\nvertexCount = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getVertexCount(), depth ).push( C ); }
		{ sgs_PushString( C, "\nchainPrevVertex = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getChainPrevVertex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nchainNextVertex = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getChainNextVertex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasChainPrevVertex = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getHasChainPrevVertex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasChainNextVertex = " ); sgs_DumpData( C, static_cast<Box2DShape*>( obj->data )->_getHasChainNextVertex(), depth ).push( C ); }
		sgs_StringConcat( C, 30 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DShape__sgs_funcs[] =
{
	{ "TestPoint", _sgs_method__Box2DShape__TestPoint },
	{ "RayCast", _sgs_method__Box2DShape__RayCast },
	{ "ComputeAABB", _sgs_method__Box2DShape__ComputeAABB },
	{ "ComputeMass", _sgs_method__Box2DShape__ComputeMass },
	{ "SetEdge", _sgs_method__Box2DShape__SetEdge },
	{ "GetVertexArray", _sgs_method__Box2DShape__GetVertexArray },
	{ "GetVertexFloatArray", _sgs_method__Box2DShape__GetVertexFloatArray },
	{ "SetVertices", _sgs_method__Box2DShape__SetVertices },
	{ "SetVerticesFromVec2Array", _sgs_method__Box2DShape__SetVerticesFromVec2Array },
	{ "SetVerticesFromFloatArray", _sgs_method__Box2DShape__SetVerticesFromFloatArray },
	{ "SetAsBox", _sgs_method__Box2DShape__SetAsBox },
	{ "GetVertex", _sgs_method__Box2DShape__GetVertex },
	{ "Validate", _sgs_method__Box2DShape__Validate },
	{ "CreateLoop", _sgs_method__Box2DShape__CreateLoop },
	{ "CreateLoopFromVec2Array", _sgs_method__Box2DShape__CreateLoopFromVec2Array },
	{ "CreateLoopFromFloatArray", _sgs_method__Box2DShape__CreateLoopFromFloatArray },
	{ "CreateChain", _sgs_method__Box2DShape__CreateChain },
	{ "CreateChainFromVec2Array", _sgs_method__Box2DShape__CreateChainFromVec2Array },
	{ "CreateChainFromFloatArray", _sgs_method__Box2DShape__CreateChainFromFloatArray },
	{ "SetPrevVertex", _sgs_method__Box2DShape__SetPrevVertex },
	{ "SetNextVertex", _sgs_method__Box2DShape__SetNextVertex },
	{ "GetChildEdge", _sgs_method__Box2DShape__GetChildEdge },
	{ NULL, NULL },
};

static int Box2DShape__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DShape__sgs_funcs,
		-1, "Box2DShape." );
	return 1;
}

static sgs_ObjInterface Box2DShape__sgs_interface =
{
	"Box2DShape",
	Box2DShape::_sgs_destruct, Box2DShape::_sgs_gcmark, Box2DShape::_sgs_getindex, Box2DShape::_sgs_setindex, NULL, NULL, Box2DShape::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DShape::_sgs_interface(Box2DShape__sgs_interface, Box2DShape__sgs_ifn);


int Box2DFixtureDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DFixtureDef*>( obj->data )->C = C;
	static_cast<Box2DFixtureDef*>( obj->data )->~Box2DFixtureDef();
	return SGS_SUCCESS;
}

int Box2DFixtureDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixtureDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DFixtureDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixtureDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "shape" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->_shape ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->friction ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->restitution ); return SGS_SUCCESS; }
		SGS_CASE( "density" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->density ); return SGS_SUCCESS; }
		SGS_CASE( "isSensor" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->isSensor ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "filterData" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->_getFilterData() ); return SGS_SUCCESS; }
		SGS_CASE( "categoryBits" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->filter.categoryBits ); return SGS_SUCCESS; }
		SGS_CASE( "maskBits" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->filter.maskBits ); return SGS_SUCCESS; }
		SGS_CASE( "groupIndex" ){ sgs_PushVar( C, static_cast<Box2DFixtureDef*>( obj->data )->filter.groupIndex ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFixtureDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixtureDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "shape" ){ static_cast<Box2DFixtureDef*>( obj->data )->_shape = sgs_GetVar<Box2DShapeHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ static_cast<Box2DFixtureDef*>( obj->data )->friction = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ static_cast<Box2DFixtureDef*>( obj->data )->restitution = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "density" ){ static_cast<Box2DFixtureDef*>( obj->data )->density = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "isSensor" ){ static_cast<Box2DFixtureDef*>( obj->data )->isSensor = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DFixtureDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DFixtureDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "filterData" ){ static_cast<Box2DFixtureDef*>( obj->data )->_setFilterData( sgs_GetVar<Box2DFilterData>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "categoryBits" ){ static_cast<Box2DFixtureDef*>( obj->data )->filter.categoryBits = sgs_GetVar<uint16>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maskBits" ){ static_cast<Box2DFixtureDef*>( obj->data )->filter.maskBits = sgs_GetVar<uint16>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "groupIndex" ){ static_cast<Box2DFixtureDef*>( obj->data )->filter.groupIndex = sgs_GetVar<int16>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFixtureDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixtureDef*>( obj->data )->C, C );
	char bfr[ 47 ];
	sprintf( bfr, "Box2DFixtureDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nshape = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->_shape, depth ).push( C ); }
		{ sgs_PushString( C, "\nfriction = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->friction, depth ).push( C ); }
		{ sgs_PushString( C, "\nrestitution = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->restitution, depth ).push( C ); }
		{ sgs_PushString( C, "\ndensity = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->density, depth ).push( C ); }
		{ sgs_PushString( C, "\nisSensor = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->isSensor, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nfilterData = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->_getFilterData(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncategoryBits = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->filter.categoryBits, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaskBits = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->filter.maskBits, depth ).push( C ); }
		{ sgs_PushString( C, "\ngroupIndex = " ); sgs_DumpData( C, static_cast<Box2DFixtureDef*>( obj->data )->filter.groupIndex, depth ).push( C ); }
		sgs_StringConcat( C, 22 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DFixtureDef__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DFixtureDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DFixtureDef__sgs_funcs,
		-1, "Box2DFixtureDef." );
	return 1;
}

static sgs_ObjInterface Box2DFixtureDef__sgs_interface =
{
	"Box2DFixtureDef",
	Box2DFixtureDef::_sgs_destruct, Box2DFixtureDef::gcmark, Box2DFixtureDef::_sgs_getindex, Box2DFixtureDef::_sgs_setindex, NULL, NULL, Box2DFixtureDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DFixtureDef::_sgs_interface(Box2DFixtureDef__sgs_interface, Box2DFixtureDef__sgs_ifn);


static int _sgs_method__Box2DFixture__Refilter( SGS_CTX )
{
	Box2DFixture* data; if( !SGS_PARSE_METHOD( C, Box2DFixture::_sgs_interface, data, Box2DFixture, Refilter ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Refilter(  ); return 0;
}

static int _sgs_method__Box2DFixture__TestPoint( SGS_CTX )
{
	Box2DFixture* data; if( !SGS_PARSE_METHOD( C, Box2DFixture::_sgs_interface, data, Box2DFixture, TestPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->TestPoint( sgs_GetVar<b2Vec2>()(C,0) )); return 1;
}

static int _sgs_method__Box2DFixture__RayCast( SGS_CTX )
{
	Box2DFixture* data; if( !SGS_PARSE_METHOD( C, Box2DFixture::_sgs_interface, data, Box2DFixture, RayCast ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->RayCast( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<b2Vec2>()(C,1), sgs_GetVar<float32>()(C,2), sgs_GetVar<int32>()(C,3) );
}

static int _sgs_method__Box2DFixture__GetAABB( SGS_CTX )
{
	Box2DFixture* data; if( !SGS_PARSE_METHOD( C, Box2DFixture::_sgs_interface, data, Box2DFixture, GetAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetAABB( sgs_GetVar<int32>()(C,0) )); return 1;
}

static int _sgs_method__Box2DFixture__Dump( SGS_CTX )
{
	Box2DFixture* data; if( !SGS_PARSE_METHOD( C, Box2DFixture::_sgs_interface, data, Box2DFixture, Dump ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Dump( sgs_GetVar<int32>()(C,0) ); return 0;
}

int Box2DFixture::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DFixture*>( obj->data )->C = C;
	static_cast<Box2DFixture*>( obj->data )->~Box2DFixture();
	return SGS_SUCCESS;
}

int Box2DFixture::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixture*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DFixture::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixture*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "shapeType" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getShapeType() ); return SGS_SUCCESS; }
		SGS_CASE( "shape" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getShape() ); return SGS_SUCCESS; }
		SGS_CASE( "next" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getNext() ); return SGS_SUCCESS; }
		SGS_CASE( "body" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getBody() ); return SGS_SUCCESS; }
		SGS_CASE( "sensor" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getSensor() ); return SGS_SUCCESS; }
		SGS_CASE( "filterData" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getFilterData() ); return SGS_SUCCESS; }
		SGS_CASE( "categoryBits" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getCategoryBits() ); return SGS_SUCCESS; }
		SGS_CASE( "maskBits" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getMaskBits() ); return SGS_SUCCESS; }
		SGS_CASE( "groupIndex" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getGroupIndex() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "density" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getDensity() ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getFriction() ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ sgs_PushVar( C, static_cast<Box2DFixture*>( obj->data )->_getRestitution() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFixture::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixture*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "sensor" ){ static_cast<Box2DFixture*>( obj->data )->_setSensor( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "filterData" ){ static_cast<Box2DFixture*>( obj->data )->_setFilterData( sgs_GetVar<Box2DFilterData>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "categoryBits" ){ static_cast<Box2DFixture*>( obj->data )->_setCategoryBits( sgs_GetVar<uint16>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "maskBits" ){ static_cast<Box2DFixture*>( obj->data )->_setMaskBits( sgs_GetVar<uint16>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "groupIndex" ){ static_cast<Box2DFixture*>( obj->data )->_setGroupIndex( sgs_GetVar<int16>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DFixture*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DFixture*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "density" ){ static_cast<Box2DFixture*>( obj->data )->_setDensity( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ static_cast<Box2DFixture*>( obj->data )->_setFriction( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ static_cast<Box2DFixture*>( obj->data )->_setRestitution( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFixture::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFixture*>( obj->data )->C, C );
	char bfr[ 44 ];
	sprintf( bfr, "Box2DFixture (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nshapeType = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getShapeType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nshape = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getShape(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnext = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getNext(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbody = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getBody(), depth ).push( C ); }
		{ sgs_PushString( C, "\nsensor = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getSensor(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfilterData = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getFilterData(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncategoryBits = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getCategoryBits(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmaskBits = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getMaskBits(), depth ).push( C ); }
		{ sgs_PushString( C, "\ngroupIndex = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getGroupIndex(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\ndensity = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getDensity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfriction = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getFriction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrestitution = " ); sgs_DumpData( C, static_cast<Box2DFixture*>( obj->data )->_getRestitution(), depth ).push( C ); }
		sgs_StringConcat( C, 28 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DFixture__sgs_funcs[] =
{
	{ "Refilter", _sgs_method__Box2DFixture__Refilter },
	{ "TestPoint", _sgs_method__Box2DFixture__TestPoint },
	{ "RayCast", _sgs_method__Box2DFixture__RayCast },
	{ "GetAABB", _sgs_method__Box2DFixture__GetAABB },
	{ "Dump", _sgs_method__Box2DFixture__Dump },
	{ NULL, NULL },
};

static int Box2DFixture__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DFixture__sgs_funcs,
		-1, "Box2DFixture." );
	return 1;
}

static sgs_ObjInterface Box2DFixture__sgs_interface =
{
	"Box2DFixture",
	Box2DFixture::_sgs_destruct, Box2DFixture::gcmark, Box2DFixture::_sgs_getindex, Box2DFixture::_sgs_setindex, NULL, NULL, Box2DFixture::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DFixture::_sgs_interface(Box2DFixture__sgs_interface, Box2DFixture__sgs_ifn);


int Box2DBodyDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DBodyDef*>( obj->data )->C = C;
	static_cast<Box2DBodyDef*>( obj->data )->~Box2DBodyDef();
	return SGS_SUCCESS;
}

int Box2DBodyDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBodyDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DBodyDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBodyDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->position ); return SGS_SUCCESS; }
		SGS_CASE( "angle" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->angle ); return SGS_SUCCESS; }
		SGS_CASE( "linearVelocity" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->linearVelocity ); return SGS_SUCCESS; }
		SGS_CASE( "angularVelocity" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->angularVelocity ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->linearDamping ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->angularDamping ); return SGS_SUCCESS; }
		SGS_CASE( "allowSleep" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->allowSleep ); return SGS_SUCCESS; }
		SGS_CASE( "awake" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->awake ); return SGS_SUCCESS; }
		SGS_CASE( "fixedRotation" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->fixedRotation ); return SGS_SUCCESS; }
		SGS_CASE( "bullet" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->bullet ); return SGS_SUCCESS; }
		SGS_CASE( "active" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->active ); return SGS_SUCCESS; }
		SGS_CASE( "gravityScale" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->gravityScale ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DBodyDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DBodyDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBodyDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ static_cast<Box2DBodyDef*>( obj->data )->_setType( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "position" ){ static_cast<Box2DBodyDef*>( obj->data )->position = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "angle" ){ static_cast<Box2DBodyDef*>( obj->data )->angle = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "linearVelocity" ){ static_cast<Box2DBodyDef*>( obj->data )->linearVelocity = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "angularVelocity" ){ static_cast<Box2DBodyDef*>( obj->data )->angularVelocity = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ static_cast<Box2DBodyDef*>( obj->data )->linearDamping = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ static_cast<Box2DBodyDef*>( obj->data )->angularDamping = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "allowSleep" ){ static_cast<Box2DBodyDef*>( obj->data )->allowSleep = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "awake" ){ static_cast<Box2DBodyDef*>( obj->data )->awake = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "fixedRotation" ){ static_cast<Box2DBodyDef*>( obj->data )->fixedRotation = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bullet" ){ static_cast<Box2DBodyDef*>( obj->data )->bullet = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "active" ){ static_cast<Box2DBodyDef*>( obj->data )->active = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "gravityScale" ){ static_cast<Box2DBodyDef*>( obj->data )->gravityScale = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DBodyDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DBodyDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBodyDef*>( obj->data )->C, C );
	char bfr[ 44 ];
	sprintf( bfr, "Box2DBodyDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nposition = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->position, depth ).push( C ); }
		{ sgs_PushString( C, "\nangle = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->angle, depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearVelocity = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->linearVelocity, depth ).push( C ); }
		{ sgs_PushString( C, "\nangularVelocity = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->angularVelocity, depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearDamping = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->linearDamping, depth ).push( C ); }
		{ sgs_PushString( C, "\nangularDamping = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->angularDamping, depth ).push( C ); }
		{ sgs_PushString( C, "\nallowSleep = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->allowSleep, depth ).push( C ); }
		{ sgs_PushString( C, "\nawake = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->awake, depth ).push( C ); }
		{ sgs_PushString( C, "\nfixedRotation = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->fixedRotation, depth ).push( C ); }
		{ sgs_PushString( C, "\nbullet = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->bullet, depth ).push( C ); }
		{ sgs_PushString( C, "\nactive = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->active, depth ).push( C ); }
		{ sgs_PushString( C, "\ngravityScale = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->gravityScale, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DBodyDef*>( obj->data )->_userData, depth ).push( C ); }
		sgs_StringConcat( C, 28 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DBodyDef__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DBodyDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DBodyDef__sgs_funcs,
		-1, "Box2DBodyDef." );
	return 1;
}

static sgs_ObjInterface Box2DBodyDef__sgs_interface =
{
	"Box2DBodyDef",
	Box2DBodyDef::_sgs_destruct, Box2DBodyDef::gcmark, Box2DBodyDef::_sgs_getindex, Box2DBodyDef::_sgs_setindex, NULL, NULL, Box2DBodyDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DBodyDef::_sgs_interface(Box2DBodyDef__sgs_interface, Box2DBodyDef__sgs_ifn);


static int _sgs_method__Box2DBody__CreateFixture( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, CreateFixture ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->CreateFixture( sgs_GetVar<Box2DFixtureDef::Handle>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__CreateFixtureFromShape( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, CreateFixtureFromShape ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->CreateFixtureFromShape( sgs_GetVar<Box2DShapeHandle>()(C,0), sgs_GetVar<float32>()(C,1) )); return 1;
}

static int _sgs_method__Box2DBody__DestroyFixture( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, DestroyFixture ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->DestroyFixture( sgs_GetVar<Box2DFixtureHandle>()(C,0) ); return 0;
}

static int _sgs_method__Box2DBody__SetTransform( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, SetTransform ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->SetTransform( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<float32>()(C,1) ); return 0;
}

static int _sgs_method__Box2DBody__ApplyForce( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, ApplyForce ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ApplyForce( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<b2Vec2>()(C,1), sgs_GetVar<bool>()(C,2) ); return 0;
}

static int _sgs_method__Box2DBody__ApplyForceToCenter( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, ApplyForceToCenter ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ApplyForceToCenter( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<bool>()(C,1) ); return 0;
}

static int _sgs_method__Box2DBody__ApplyTorque( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, ApplyTorque ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ApplyTorque( sgs_GetVar<float32>()(C,0), sgs_GetVar<bool>()(C,1) ); return 0;
}

static int _sgs_method__Box2DBody__ApplyLinearImpulse( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, ApplyLinearImpulse ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ApplyLinearImpulse( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<b2Vec2>()(C,1), sgs_GetVar<bool>()(C,2) ); return 0;
}

static int _sgs_method__Box2DBody__ApplyLinearImpulseToCenter( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, ApplyLinearImpulseToCenter ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ApplyLinearImpulseToCenter( sgs_GetVar<b2Vec2>()(C,0), sgs_GetVar<bool>()(C,1) ); return 0;
}

static int _sgs_method__Box2DBody__ApplyAngularImpulse( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, ApplyAngularImpulse ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ApplyAngularImpulse( sgs_GetVar<float32>()(C,0), sgs_GetVar<bool>()(C,1) ); return 0;
}

static int _sgs_method__Box2DBody__ResetMassData( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, ResetMassData ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ResetMassData(  ); return 0;
}

static int _sgs_method__Box2DBody__GetWorldPoint( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetWorldPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetWorldPoint( sgs_GetVar<b2Vec2>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__GetWorldVector( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetWorldVector ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetWorldVector( sgs_GetVar<b2Vec2>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__GetLocalPoint( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetLocalPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetLocalPoint( sgs_GetVar<b2Vec2>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__GetLocalVector( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetLocalVector ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetLocalVector( sgs_GetVar<b2Vec2>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__GetLinearVelocityFromWorldPoint( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetLinearVelocityFromWorldPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetLinearVelocityFromWorldPoint( sgs_GetVar<b2Vec2>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__GetLinearVelocityFromLocalPoint( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetLinearVelocityFromLocalPoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetLinearVelocityFromLocalPoint( sgs_GetVar<b2Vec2>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__GetJointList( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetJointList ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetJointList( sgs_GetVar<bool>()(C,0) )); return 1;
}

static int _sgs_method__Box2DBody__GetContactList( SGS_CTX )
{
	Box2DBody* data; if( !SGS_PARSE_METHOD( C, Box2DBody::_sgs_interface, data, Box2DBody, GetContactList ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetContactList( sgs_GetVar<bool>()(C,0) )); return 1;
}

int Box2DBody::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DBody*>( obj->data )->C = C;
	static_cast<Box2DBody*>( obj->data )->~Box2DBody();
	return SGS_SUCCESS;
}

int Box2DBody::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBody*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DBody::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBody*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getPosition() ); return SGS_SUCCESS; }
		SGS_CASE( "angle" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getAngle() ); return SGS_SUCCESS; }
		SGS_CASE( "transform" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getTransform() ); return SGS_SUCCESS; }
		SGS_CASE( "worldCenter" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getWorldCenter() ); return SGS_SUCCESS; }
		SGS_CASE( "localCenter" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getLocalCenter() ); return SGS_SUCCESS; }
		SGS_CASE( "linearVelocity" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getLinearVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "angularVelocity" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getAngularVelocity() ); return SGS_SUCCESS; }
		SGS_CASE( "massData" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getMassData() ); return SGS_SUCCESS; }
		SGS_CASE( "mass" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getMass() ); return SGS_SUCCESS; }
		SGS_CASE( "inertia" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getInertia() ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getLinearDamping() ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getAngularDamping() ); return SGS_SUCCESS; }
		SGS_CASE( "gravityScale" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getGravityScale() ); return SGS_SUCCESS; }
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "isBullet" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getIsBullet() ); return SGS_SUCCESS; }
		SGS_CASE( "allowSleeping" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getAllowSleeping() ); return SGS_SUCCESS; }
		SGS_CASE( "isAwake" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getIsAwake() ); return SGS_SUCCESS; }
		SGS_CASE( "isActive" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getIsActive() ); return SGS_SUCCESS; }
		SGS_CASE( "hasFixedRotation" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getHasFixedRotation() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "fixtureList" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getFixtureList() ); return SGS_SUCCESS; }
		SGS_CASE( "next" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getNext() ); return SGS_SUCCESS; }
		SGS_CASE( "world" ){ sgs_PushVar( C, static_cast<Box2DBody*>( obj->data )->_getWorld() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DBody::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBody*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" ){ static_cast<Box2DBody*>( obj->data )->_setPosition( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angle" ){ static_cast<Box2DBody*>( obj->data )->_setAngle( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "transform" ){ static_cast<Box2DBody*>( obj->data )->_setTransform( sgs_GetVar<Box2DTransform>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "worldCenter" ){ static_cast<Box2DBody*>( obj->data )->_setWorldCenter( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "localCenter" ){ static_cast<Box2DBody*>( obj->data )->_setLocalCenter( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "linearVelocity" ){ static_cast<Box2DBody*>( obj->data )->_setLinearVelocity( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angularVelocity" ){ static_cast<Box2DBody*>( obj->data )->_setAngularVelocity( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "massData" ){ static_cast<Box2DBody*>( obj->data )->_setMassData( sgs_GetVar<Box2DMassData>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "mass" ){ static_cast<Box2DBody*>( obj->data )->_setMass( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "inertia" ){ static_cast<Box2DBody*>( obj->data )->_setInertia( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "linearDamping" ){ static_cast<Box2DBody*>( obj->data )->_setLinearDamping( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angularDamping" ){ static_cast<Box2DBody*>( obj->data )->_setAngularDamping( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "gravityScale" ){ static_cast<Box2DBody*>( obj->data )->_setGravityScale( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "type" ){ static_cast<Box2DBody*>( obj->data )->_setType( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "isBullet" ){ static_cast<Box2DBody*>( obj->data )->_setIsBullet( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "allowSleeping" ){ static_cast<Box2DBody*>( obj->data )->_setAllowSleeping( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "isAwake" ){ static_cast<Box2DBody*>( obj->data )->_setIsAwake( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "isActive" ){ static_cast<Box2DBody*>( obj->data )->_setIsActive( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "hasFixedRotation" ){ static_cast<Box2DBody*>( obj->data )->_setHasFixedRotation( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DBody*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DBody::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DBody*>( obj->data )->C, C );
	char bfr[ 41 ];
	sprintf( bfr, "Box2DBody (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nposition = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getPosition(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangle = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getAngle(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntransform = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getTransform(), depth ).push( C ); }
		{ sgs_PushString( C, "\nworldCenter = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getWorldCenter(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalCenter = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getLocalCenter(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearVelocity = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getLinearVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangularVelocity = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getAngularVelocity(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmassData = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getMassData(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmass = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getMass(), depth ).push( C ); }
		{ sgs_PushString( C, "\ninertia = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getInertia(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearDamping = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getLinearDamping(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangularDamping = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getAngularDamping(), depth ).push( C ); }
		{ sgs_PushString( C, "\ngravityScale = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getGravityScale(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisBullet = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getIsBullet(), depth ).push( C ); }
		{ sgs_PushString( C, "\nallowSleeping = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getAllowSleeping(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisAwake = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getIsAwake(), depth ).push( C ); }
		{ sgs_PushString( C, "\nisActive = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getIsActive(), depth ).push( C ); }
		{ sgs_PushString( C, "\nhasFixedRotation = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getHasFixedRotation(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nfixtureList = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getFixtureList(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnext = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getNext(), depth ).push( C ); }
		{ sgs_PushString( C, "\nworld = " ); sgs_DumpData( C, static_cast<Box2DBody*>( obj->data )->_getWorld(), depth ).push( C ); }
		sgs_StringConcat( C, 46 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DBody__sgs_funcs[] =
{
	{ "CreateFixture", _sgs_method__Box2DBody__CreateFixture },
	{ "CreateFixtureFromShape", _sgs_method__Box2DBody__CreateFixtureFromShape },
	{ "DestroyFixture", _sgs_method__Box2DBody__DestroyFixture },
	{ "SetTransform", _sgs_method__Box2DBody__SetTransform },
	{ "ApplyForce", _sgs_method__Box2DBody__ApplyForce },
	{ "ApplyForceToCenter", _sgs_method__Box2DBody__ApplyForceToCenter },
	{ "ApplyTorque", _sgs_method__Box2DBody__ApplyTorque },
	{ "ApplyLinearImpulse", _sgs_method__Box2DBody__ApplyLinearImpulse },
	{ "ApplyLinearImpulseToCenter", _sgs_method__Box2DBody__ApplyLinearImpulseToCenter },
	{ "ApplyAngularImpulse", _sgs_method__Box2DBody__ApplyAngularImpulse },
	{ "ResetMassData", _sgs_method__Box2DBody__ResetMassData },
	{ "GetWorldPoint", _sgs_method__Box2DBody__GetWorldPoint },
	{ "GetWorldVector", _sgs_method__Box2DBody__GetWorldVector },
	{ "GetLocalPoint", _sgs_method__Box2DBody__GetLocalPoint },
	{ "GetLocalVector", _sgs_method__Box2DBody__GetLocalVector },
	{ "GetLinearVelocityFromWorldPoint", _sgs_method__Box2DBody__GetLinearVelocityFromWorldPoint },
	{ "GetLinearVelocityFromLocalPoint", _sgs_method__Box2DBody__GetLinearVelocityFromLocalPoint },
	{ "GetJointList", _sgs_method__Box2DBody__GetJointList },
	{ "GetContactList", _sgs_method__Box2DBody__GetContactList },
	{ NULL, NULL },
};

static int Box2DBody__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DBody__sgs_funcs,
		-1, "Box2DBody." );
	return 1;
}

static sgs_ObjInterface Box2DBody__sgs_interface =
{
	"Box2DBody",
	Box2DBody::_sgs_destruct, Box2DBody::gcmark, Box2DBody::_sgs_getindex, Box2DBody::_sgs_setindex, NULL, NULL, Box2DBody::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DBody::_sgs_interface(Box2DBody__sgs_interface, Box2DBody__sgs_ifn);


static int _sgs_method__Box2DDistanceJointDef__Initialize( SGS_CTX )
{
	Box2DDistanceJointDef* data; if( !SGS_PARSE_METHOD( C, Box2DDistanceJointDef::_sgs_interface, data, Box2DDistanceJointDef, Initialize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Initialize( sgs_GetVar<Box2DBodyHandle>()(C,0), sgs_GetVar<Box2DBodyHandle>()(C,1), sgs_GetVar<b2Vec2>()(C,2), sgs_GetVar<b2Vec2>()(C,3) ); return 0;
}

int Box2DDistanceJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DDistanceJointDef*>( obj->data )->C = C;
	static_cast<Box2DDistanceJointDef*>( obj->data )->~Box2DDistanceJointDef();
	return SGS_SUCCESS;
}

int Box2DDistanceJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDistanceJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DDistanceJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDistanceJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "length" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->length ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->frequencyHz ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ sgs_PushVar( C, static_cast<Box2DDistanceJointDef*>( obj->data )->dampingRatio ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DDistanceJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDistanceJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "length" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->length = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->frequencyHz = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ static_cast<Box2DDistanceJointDef*>( obj->data )->dampingRatio = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DDistanceJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDistanceJointDef*>( obj->data )->C, C );
	char bfr[ 53 ];
	sprintf( bfr, "Box2DDistanceJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nlength = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->length, depth ).push( C ); }
		{ sgs_PushString( C, "\nfrequencyHz = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->frequencyHz, depth ).push( C ); }
		{ sgs_PushString( C, "\ndampingRatio = " ); sgs_DumpData( C, static_cast<Box2DDistanceJointDef*>( obj->data )->dampingRatio, depth ).push( C ); }
		sgs_StringConcat( C, 22 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DDistanceJointDef__sgs_funcs[] =
{
	{ "Initialize", _sgs_method__Box2DDistanceJointDef__Initialize },
	{ NULL, NULL },
};

static int Box2DDistanceJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DDistanceJointDef__sgs_funcs,
		-1, "Box2DDistanceJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DDistanceJointDef__sgs_interface =
{
	"Box2DDistanceJointDef",
	Box2DDistanceJointDef::_sgs_destruct, Box2DDistanceJointDef::gcmark, Box2DDistanceJointDef::_sgs_getindex, Box2DDistanceJointDef::_sgs_setindex, NULL, NULL, Box2DDistanceJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DDistanceJointDef::_sgs_interface(Box2DDistanceJointDef__sgs_interface, Box2DDistanceJointDef__sgs_ifn);


static int _sgs_method__Box2DFrictionJointDef__Initialize( SGS_CTX )
{
	Box2DFrictionJointDef* data; if( !SGS_PARSE_METHOD( C, Box2DFrictionJointDef::_sgs_interface, data, Box2DFrictionJointDef, Initialize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Initialize( sgs_GetVar<Box2DBodyHandle>()(C,0), sgs_GetVar<Box2DBodyHandle>()(C,1), sgs_GetVar<b2Vec2>()(C,2) ); return 0;
}

int Box2DFrictionJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DFrictionJointDef*>( obj->data )->C = C;
	static_cast<Box2DFrictionJointDef*>( obj->data )->~Box2DFrictionJointDef();
	return SGS_SUCCESS;
}

int Box2DFrictionJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFrictionJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DFrictionJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFrictionJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->maxForce ); return SGS_SUCCESS; }
		SGS_CASE( "maxTorque" ){ sgs_PushVar( C, static_cast<Box2DFrictionJointDef*>( obj->data )->maxTorque ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFrictionJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFrictionJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->maxForce = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxTorque" ){ static_cast<Box2DFrictionJointDef*>( obj->data )->maxTorque = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DFrictionJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DFrictionJointDef*>( obj->data )->C, C );
	char bfr[ 53 ];
	sprintf( bfr, "Box2DFrictionJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxForce = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->maxForce, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxTorque = " ); sgs_DumpData( C, static_cast<Box2DFrictionJointDef*>( obj->data )->maxTorque, depth ).push( C ); }
		sgs_StringConcat( C, 20 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DFrictionJointDef__sgs_funcs[] =
{
	{ "Initialize", _sgs_method__Box2DFrictionJointDef__Initialize },
	{ NULL, NULL },
};

static int Box2DFrictionJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DFrictionJointDef__sgs_funcs,
		-1, "Box2DFrictionJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DFrictionJointDef__sgs_interface =
{
	"Box2DFrictionJointDef",
	Box2DFrictionJointDef::_sgs_destruct, Box2DFrictionJointDef::gcmark, Box2DFrictionJointDef::_sgs_getindex, Box2DFrictionJointDef::_sgs_setindex, NULL, NULL, Box2DFrictionJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DFrictionJointDef::_sgs_interface(Box2DFrictionJointDef__sgs_interface, Box2DFrictionJointDef__sgs_ifn);


int Box2DGearJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DGearJointDef*>( obj->data )->C = C;
	static_cast<Box2DGearJointDef*>( obj->data )->~Box2DGearJointDef();
	return SGS_SUCCESS;
}

int Box2DGearJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DGearJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DGearJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DGearJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DGearJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DGearJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DGearJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "jointA" ){ sgs_PushVar( C, static_cast<Box2DGearJointDef*>( obj->data )->_jointA ); return SGS_SUCCESS; }
		SGS_CASE( "jointB" ){ sgs_PushVar( C, static_cast<Box2DGearJointDef*>( obj->data )->_jointB ); return SGS_SUCCESS; }
		SGS_CASE( "ratio" ){ sgs_PushVar( C, static_cast<Box2DGearJointDef*>( obj->data )->ratio ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DGearJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DGearJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "userData" ){ static_cast<Box2DGearJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DGearJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "jointA" ){ static_cast<Box2DGearJointDef*>( obj->data )->_jointA = sgs_GetVar<Box2DJointHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "jointB" ){ static_cast<Box2DGearJointDef*>( obj->data )->_jointB = sgs_GetVar<Box2DJointHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "ratio" ){ static_cast<Box2DGearJointDef*>( obj->data )->ratio = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DGearJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DGearJointDef*>( obj->data )->C, C );
	char bfr[ 49 ];
	sprintf( bfr, "Box2DGearJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DGearJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DGearJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DGearJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\njointA = " ); sgs_DumpData( C, static_cast<Box2DGearJointDef*>( obj->data )->_jointA, depth ).push( C ); }
		{ sgs_PushString( C, "\njointB = " ); sgs_DumpData( C, static_cast<Box2DGearJointDef*>( obj->data )->_jointB, depth ).push( C ); }
		{ sgs_PushString( C, "\nratio = " ); sgs_DumpData( C, static_cast<Box2DGearJointDef*>( obj->data )->ratio, depth ).push( C ); }
		sgs_StringConcat( C, 12 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DGearJointDef__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DGearJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DGearJointDef__sgs_funcs,
		-1, "Box2DGearJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DGearJointDef__sgs_interface =
{
	"Box2DGearJointDef",
	Box2DGearJointDef::_sgs_destruct, Box2DGearJointDef::gcmark, Box2DGearJointDef::_sgs_getindex, Box2DGearJointDef::_sgs_setindex, NULL, NULL, Box2DGearJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DGearJointDef::_sgs_interface(Box2DGearJointDef__sgs_interface, Box2DGearJointDef__sgs_ifn);


static int _sgs_method__Box2DMotorJointDef__Initialize( SGS_CTX )
{
	Box2DMotorJointDef* data; if( !SGS_PARSE_METHOD( C, Box2DMotorJointDef::_sgs_interface, data, Box2DMotorJointDef, Initialize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Initialize( sgs_GetVar<Box2DBodyHandle>()(C,0), sgs_GetVar<Box2DBodyHandle>()(C,1) ); return 0;
}

int Box2DMotorJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DMotorJointDef*>( obj->data )->C = C;
	static_cast<Box2DMotorJointDef*>( obj->data )->~Box2DMotorJointDef();
	return SGS_SUCCESS;
}

int Box2DMotorJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMotorJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DMotorJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMotorJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "linearOffset" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->linearOffset ); return SGS_SUCCESS; }
		SGS_CASE( "angularOffset" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->angularOffset ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->maxForce ); return SGS_SUCCESS; }
		SGS_CASE( "maxTorque" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->maxTorque ); return SGS_SUCCESS; }
		SGS_CASE( "correctionFactor" ){ sgs_PushVar( C, static_cast<Box2DMotorJointDef*>( obj->data )->correctionFactor ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DMotorJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMotorJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DMotorJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DMotorJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DMotorJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DMotorJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DMotorJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "linearOffset" ){ static_cast<Box2DMotorJointDef*>( obj->data )->linearOffset = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "angularOffset" ){ static_cast<Box2DMotorJointDef*>( obj->data )->angularOffset = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ static_cast<Box2DMotorJointDef*>( obj->data )->maxForce = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxTorque" ){ static_cast<Box2DMotorJointDef*>( obj->data )->maxTorque = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "correctionFactor" ){ static_cast<Box2DMotorJointDef*>( obj->data )->correctionFactor = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DMotorJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMotorJointDef*>( obj->data )->C, C );
	char bfr[ 50 ];
	sprintf( bfr, "Box2DMotorJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearOffset = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->linearOffset, depth ).push( C ); }
		{ sgs_PushString( C, "\nangularOffset = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->angularOffset, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxForce = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->maxForce, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxTorque = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->maxTorque, depth ).push( C ); }
		{ sgs_PushString( C, "\ncorrectionFactor = " ); sgs_DumpData( C, static_cast<Box2DMotorJointDef*>( obj->data )->correctionFactor, depth ).push( C ); }
		sgs_StringConcat( C, 22 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DMotorJointDef__sgs_funcs[] =
{
	{ "Initialize", _sgs_method__Box2DMotorJointDef__Initialize },
	{ NULL, NULL },
};

static int Box2DMotorJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DMotorJointDef__sgs_funcs,
		-1, "Box2DMotorJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DMotorJointDef__sgs_interface =
{
	"Box2DMotorJointDef",
	Box2DMotorJointDef::_sgs_destruct, Box2DMotorJointDef::gcmark, Box2DMotorJointDef::_sgs_getindex, Box2DMotorJointDef::_sgs_setindex, NULL, NULL, Box2DMotorJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DMotorJointDef::_sgs_interface(Box2DMotorJointDef__sgs_interface, Box2DMotorJointDef__sgs_ifn);


int Box2DMouseJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DMouseJointDef*>( obj->data )->C = C;
	static_cast<Box2DMouseJointDef*>( obj->data )->~Box2DMouseJointDef();
	return SGS_SUCCESS;
}

int Box2DMouseJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMouseJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DMouseJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMouseJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "target" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->target ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->maxForce ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->frequencyHz ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ sgs_PushVar( C, static_cast<Box2DMouseJointDef*>( obj->data )->dampingRatio ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DMouseJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMouseJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DMouseJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DMouseJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DMouseJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DMouseJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DMouseJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "target" ){ static_cast<Box2DMouseJointDef*>( obj->data )->target = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ static_cast<Box2DMouseJointDef*>( obj->data )->maxForce = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ static_cast<Box2DMouseJointDef*>( obj->data )->frequencyHz = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ static_cast<Box2DMouseJointDef*>( obj->data )->dampingRatio = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DMouseJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DMouseJointDef*>( obj->data )->C, C );
	char bfr[ 50 ];
	sprintf( bfr, "Box2DMouseJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\ntarget = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->target, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxForce = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->maxForce, depth ).push( C ); }
		{ sgs_PushString( C, "\nfrequencyHz = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->frequencyHz, depth ).push( C ); }
		{ sgs_PushString( C, "\ndampingRatio = " ); sgs_DumpData( C, static_cast<Box2DMouseJointDef*>( obj->data )->dampingRatio, depth ).push( C ); }
		sgs_StringConcat( C, 20 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DMouseJointDef__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DMouseJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DMouseJointDef__sgs_funcs,
		-1, "Box2DMouseJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DMouseJointDef__sgs_interface =
{
	"Box2DMouseJointDef",
	Box2DMouseJointDef::_sgs_destruct, Box2DMouseJointDef::gcmark, Box2DMouseJointDef::_sgs_getindex, Box2DMouseJointDef::_sgs_setindex, NULL, NULL, Box2DMouseJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DMouseJointDef::_sgs_interface(Box2DMouseJointDef__sgs_interface, Box2DMouseJointDef__sgs_ifn);


static int _sgs_method__Box2DPrismaticJointDef__Initialize( SGS_CTX )
{
	Box2DPrismaticJointDef* data; if( !SGS_PARSE_METHOD( C, Box2DPrismaticJointDef::_sgs_interface, data, Box2DPrismaticJointDef, Initialize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Initialize( sgs_GetVar<Box2DBodyHandle>()(C,0), sgs_GetVar<Box2DBodyHandle>()(C,1), sgs_GetVar<b2Vec2>()(C,2), sgs_GetVar<b2Vec2>()(C,3) ); return 0;
}

int Box2DPrismaticJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DPrismaticJointDef*>( obj->data )->C = C;
	static_cast<Box2DPrismaticJointDef*>( obj->data )->~Box2DPrismaticJointDef();
	return SGS_SUCCESS;
}

int Box2DPrismaticJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPrismaticJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DPrismaticJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPrismaticJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "localAxisA" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->localAxisA ); return SGS_SUCCESS; }
		SGS_CASE( "referenceAngle" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->referenceAngle ); return SGS_SUCCESS; }
		SGS_CASE( "enableLimit" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->enableLimit ); return SGS_SUCCESS; }
		SGS_CASE( "lowerTranslation" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->lowerTranslation ); return SGS_SUCCESS; }
		SGS_CASE( "upperTranslation" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->upperTranslation ); return SGS_SUCCESS; }
		SGS_CASE( "enableMotor" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->enableMotor ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->motorSpeed ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorForce" ){ sgs_PushVar( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->maxMotorForce ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DPrismaticJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPrismaticJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAxisA" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->localAxisA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "referenceAngle" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->referenceAngle = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "enableLimit" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->enableLimit = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "lowerTranslation" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->lowerTranslation = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "upperTranslation" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->upperTranslation = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "enableMotor" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->enableMotor = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->motorSpeed = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorForce" ){ static_cast<Box2DPrismaticJointDef*>( obj->data )->maxMotorForce = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DPrismaticJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPrismaticJointDef*>( obj->data )->C, C );
	char bfr[ 54 ];
	sprintf( bfr, "Box2DPrismaticJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAxisA = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->localAxisA, depth ).push( C ); }
		{ sgs_PushString( C, "\nreferenceAngle = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->referenceAngle, depth ).push( C ); }
		{ sgs_PushString( C, "\nenableLimit = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->enableLimit, depth ).push( C ); }
		{ sgs_PushString( C, "\nlowerTranslation = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->lowerTranslation, depth ).push( C ); }
		{ sgs_PushString( C, "\nupperTranslation = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->upperTranslation, depth ).push( C ); }
		{ sgs_PushString( C, "\nenableMotor = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->enableMotor, depth ).push( C ); }
		{ sgs_PushString( C, "\nmotorSpeed = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->motorSpeed, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxMotorForce = " ); sgs_DumpData( C, static_cast<Box2DPrismaticJointDef*>( obj->data )->maxMotorForce, depth ).push( C ); }
		sgs_StringConcat( C, 32 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DPrismaticJointDef__sgs_funcs[] =
{
	{ "Initialize", _sgs_method__Box2DPrismaticJointDef__Initialize },
	{ NULL, NULL },
};

static int Box2DPrismaticJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DPrismaticJointDef__sgs_funcs,
		-1, "Box2DPrismaticJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DPrismaticJointDef__sgs_interface =
{
	"Box2DPrismaticJointDef",
	Box2DPrismaticJointDef::_sgs_destruct, Box2DPrismaticJointDef::gcmark, Box2DPrismaticJointDef::_sgs_getindex, Box2DPrismaticJointDef::_sgs_setindex, NULL, NULL, Box2DPrismaticJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DPrismaticJointDef::_sgs_interface(Box2DPrismaticJointDef__sgs_interface, Box2DPrismaticJointDef__sgs_ifn);


static int _sgs_method__Box2DPulleyJointDef__Initialize( SGS_CTX )
{
	Box2DPulleyJointDef* data; if( !SGS_PARSE_METHOD( C, Box2DPulleyJointDef::_sgs_interface, data, Box2DPulleyJointDef, Initialize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Initialize( sgs_GetVar<Box2DBodyHandle>()(C,0), sgs_GetVar<Box2DBodyHandle>()(C,1), sgs_GetVar<b2Vec2>()(C,2), sgs_GetVar<b2Vec2>()(C,3), sgs_GetVar<b2Vec2>()(C,4), sgs_GetVar<b2Vec2>()(C,5), sgs_GetVar<float32>()(C,6) ); return 0;
}

int Box2DPulleyJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DPulleyJointDef*>( obj->data )->C = C;
	static_cast<Box2DPulleyJointDef*>( obj->data )->~Box2DPulleyJointDef();
	return SGS_SUCCESS;
}

int Box2DPulleyJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPulleyJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DPulleyJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPulleyJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "groundAnchorA" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->groundAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "groundAnchorB" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->groundAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "lengthA" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->lengthA ); return SGS_SUCCESS; }
		SGS_CASE( "lengthB" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->lengthB ); return SGS_SUCCESS; }
		SGS_CASE( "ratio" ){ sgs_PushVar( C, static_cast<Box2DPulleyJointDef*>( obj->data )->ratio ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DPulleyJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPulleyJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "groundAnchorA" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->groundAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "groundAnchorB" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->groundAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "lengthA" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->lengthA = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "lengthB" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->lengthB = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "ratio" ){ static_cast<Box2DPulleyJointDef*>( obj->data )->ratio = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DPulleyJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DPulleyJointDef*>( obj->data )->C, C );
	char bfr[ 51 ];
	sprintf( bfr, "Box2DPulleyJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\ngroundAnchorA = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->groundAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\ngroundAnchorB = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->groundAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nlengthA = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->lengthA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlengthB = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->lengthB, depth ).push( C ); }
		{ sgs_PushString( C, "\nratio = " ); sgs_DumpData( C, static_cast<Box2DPulleyJointDef*>( obj->data )->ratio, depth ).push( C ); }
		sgs_StringConcat( C, 26 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DPulleyJointDef__sgs_funcs[] =
{
	{ "Initialize", _sgs_method__Box2DPulleyJointDef__Initialize },
	{ NULL, NULL },
};

static int Box2DPulleyJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DPulleyJointDef__sgs_funcs,
		-1, "Box2DPulleyJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DPulleyJointDef__sgs_interface =
{
	"Box2DPulleyJointDef",
	Box2DPulleyJointDef::_sgs_destruct, Box2DPulleyJointDef::gcmark, Box2DPulleyJointDef::_sgs_getindex, Box2DPulleyJointDef::_sgs_setindex, NULL, NULL, Box2DPulleyJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DPulleyJointDef::_sgs_interface(Box2DPulleyJointDef__sgs_interface, Box2DPulleyJointDef__sgs_ifn);


static int _sgs_method__Box2DRevoluteJointDef__Initialize( SGS_CTX )
{
	Box2DRevoluteJointDef* data; if( !SGS_PARSE_METHOD( C, Box2DRevoluteJointDef::_sgs_interface, data, Box2DRevoluteJointDef, Initialize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Initialize( sgs_GetVar<Box2DBodyHandle>()(C,0), sgs_GetVar<Box2DBodyHandle>()(C,1), sgs_GetVar<b2Vec2>()(C,2) ); return 0;
}

int Box2DRevoluteJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DRevoluteJointDef*>( obj->data )->C = C;
	static_cast<Box2DRevoluteJointDef*>( obj->data )->~Box2DRevoluteJointDef();
	return SGS_SUCCESS;
}

int Box2DRevoluteJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRevoluteJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DRevoluteJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRevoluteJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "referenceAngle" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->referenceAngle ); return SGS_SUCCESS; }
		SGS_CASE( "enableLimit" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->enableLimit ); return SGS_SUCCESS; }
		SGS_CASE( "lowerAngle" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->lowerAngle ); return SGS_SUCCESS; }
		SGS_CASE( "upperAngle" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->upperAngle ); return SGS_SUCCESS; }
		SGS_CASE( "enableMotor" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->enableMotor ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->motorSpeed ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorTorque" ){ sgs_PushVar( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->maxMotorTorque ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DRevoluteJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRevoluteJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "referenceAngle" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->referenceAngle = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "enableLimit" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->enableLimit = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "lowerAngle" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->lowerAngle = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "upperAngle" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->upperAngle = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "enableMotor" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->enableMotor = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->motorSpeed = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorTorque" ){ static_cast<Box2DRevoluteJointDef*>( obj->data )->maxMotorTorque = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DRevoluteJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRevoluteJointDef*>( obj->data )->C, C );
	char bfr[ 53 ];
	sprintf( bfr, "Box2DRevoluteJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nreferenceAngle = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->referenceAngle, depth ).push( C ); }
		{ sgs_PushString( C, "\nenableLimit = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->enableLimit, depth ).push( C ); }
		{ sgs_PushString( C, "\nlowerAngle = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->lowerAngle, depth ).push( C ); }
		{ sgs_PushString( C, "\nupperAngle = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->upperAngle, depth ).push( C ); }
		{ sgs_PushString( C, "\nenableMotor = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->enableMotor, depth ).push( C ); }
		{ sgs_PushString( C, "\nmotorSpeed = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->motorSpeed, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxMotorTorque = " ); sgs_DumpData( C, static_cast<Box2DRevoluteJointDef*>( obj->data )->maxMotorTorque, depth ).push( C ); }
		sgs_StringConcat( C, 30 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DRevoluteJointDef__sgs_funcs[] =
{
	{ "Initialize", _sgs_method__Box2DRevoluteJointDef__Initialize },
	{ NULL, NULL },
};

static int Box2DRevoluteJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DRevoluteJointDef__sgs_funcs,
		-1, "Box2DRevoluteJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DRevoluteJointDef__sgs_interface =
{
	"Box2DRevoluteJointDef",
	Box2DRevoluteJointDef::_sgs_destruct, Box2DRevoluteJointDef::gcmark, Box2DRevoluteJointDef::_sgs_getindex, Box2DRevoluteJointDef::_sgs_setindex, NULL, NULL, Box2DRevoluteJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DRevoluteJointDef::_sgs_interface(Box2DRevoluteJointDef__sgs_interface, Box2DRevoluteJointDef__sgs_ifn);


int Box2DRopeJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DRopeJointDef*>( obj->data )->C = C;
	static_cast<Box2DRopeJointDef*>( obj->data )->~Box2DRopeJointDef();
	return SGS_SUCCESS;
}

int Box2DRopeJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRopeJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DRopeJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRopeJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "maxLength" ){ sgs_PushVar( C, static_cast<Box2DRopeJointDef*>( obj->data )->maxLength ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DRopeJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRopeJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DRopeJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DRopeJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DRopeJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DRopeJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DRopeJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DRopeJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DRopeJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxLength" ){ static_cast<Box2DRopeJointDef*>( obj->data )->maxLength = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DRopeJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DRopeJointDef*>( obj->data )->C, C );
	char bfr[ 49 ];
	sprintf( bfr, "Box2DRopeJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxLength = " ); sgs_DumpData( C, static_cast<Box2DRopeJointDef*>( obj->data )->maxLength, depth ).push( C ); }
		sgs_StringConcat( C, 18 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DRopeJointDef__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DRopeJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DRopeJointDef__sgs_funcs,
		-1, "Box2DRopeJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DRopeJointDef__sgs_interface =
{
	"Box2DRopeJointDef",
	Box2DRopeJointDef::_sgs_destruct, Box2DRopeJointDef::gcmark, Box2DRopeJointDef::_sgs_getindex, Box2DRopeJointDef::_sgs_setindex, NULL, NULL, Box2DRopeJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DRopeJointDef::_sgs_interface(Box2DRopeJointDef__sgs_interface, Box2DRopeJointDef__sgs_ifn);


int Box2DWeldJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DWeldJointDef*>( obj->data )->C = C;
	static_cast<Box2DWeldJointDef*>( obj->data )->~Box2DWeldJointDef();
	return SGS_SUCCESS;
}

int Box2DWeldJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWeldJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DWeldJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWeldJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "referenceAngle" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->referenceAngle ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->frequencyHz ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ sgs_PushVar( C, static_cast<Box2DWeldJointDef*>( obj->data )->dampingRatio ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DWeldJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWeldJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DWeldJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DWeldJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DWeldJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DWeldJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DWeldJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DWeldJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DWeldJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "referenceAngle" ){ static_cast<Box2DWeldJointDef*>( obj->data )->referenceAngle = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ static_cast<Box2DWeldJointDef*>( obj->data )->frequencyHz = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ static_cast<Box2DWeldJointDef*>( obj->data )->dampingRatio = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DWeldJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWeldJointDef*>( obj->data )->C, C );
	char bfr[ 49 ];
	sprintf( bfr, "Box2DWeldJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nreferenceAngle = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->referenceAngle, depth ).push( C ); }
		{ sgs_PushString( C, "\nfrequencyHz = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->frequencyHz, depth ).push( C ); }
		{ sgs_PushString( C, "\ndampingRatio = " ); sgs_DumpData( C, static_cast<Box2DWeldJointDef*>( obj->data )->dampingRatio, depth ).push( C ); }
		sgs_StringConcat( C, 22 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DWeldJointDef__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DWeldJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DWeldJointDef__sgs_funcs,
		-1, "Box2DWeldJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DWeldJointDef__sgs_interface =
{
	"Box2DWeldJointDef",
	Box2DWeldJointDef::_sgs_destruct, Box2DWeldJointDef::gcmark, Box2DWeldJointDef::_sgs_getindex, Box2DWeldJointDef::_sgs_setindex, NULL, NULL, Box2DWeldJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DWeldJointDef::_sgs_interface(Box2DWeldJointDef__sgs_interface, Box2DWeldJointDef__sgs_ifn);


static int _sgs_method__Box2DWheelJointDef__Initialize( SGS_CTX )
{
	Box2DWheelJointDef* data; if( !SGS_PARSE_METHOD( C, Box2DWheelJointDef::_sgs_interface, data, Box2DWheelJointDef, Initialize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Initialize( sgs_GetVar<Box2DBodyHandle>()(C,0), sgs_GetVar<Box2DBodyHandle>()(C,1), sgs_GetVar<b2Vec2>()(C,2), sgs_GetVar<b2Vec2>()(C,3) ); return 0;
}

int Box2DWheelJointDef::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DWheelJointDef*>( obj->data )->C = C;
	static_cast<Box2DWheelJointDef*>( obj->data )->~Box2DWheelJointDef();
	return SGS_SUCCESS;
}

int Box2DWheelJointDef::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWheelJointDef*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DWheelJointDef::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWheelJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->_bodyA ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->_bodyB ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->collideConnected ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->_userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->localAnchorA ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->localAnchorB ); return SGS_SUCCESS; }
		SGS_CASE( "localAxisA" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->localAxisA ); return SGS_SUCCESS; }
		SGS_CASE( "enableMotor" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->enableMotor ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorTorque" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->maxMotorTorque ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->motorSpeed ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->frequencyHz ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ sgs_PushVar( C, static_cast<Box2DWheelJointDef*>( obj->data )->dampingRatio ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DWheelJointDef::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWheelJointDef*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "bodyA" ){ static_cast<Box2DWheelJointDef*>( obj->data )->_bodyA = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ static_cast<Box2DWheelJointDef*>( obj->data )->_bodyB = sgs_GetVar<Box2DBodyHandle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ static_cast<Box2DWheelJointDef*>( obj->data )->collideConnected = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ static_cast<Box2DWheelJointDef*>( obj->data )->_userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DWheelJointDef*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ static_cast<Box2DWheelJointDef*>( obj->data )->localAnchorA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ static_cast<Box2DWheelJointDef*>( obj->data )->localAnchorB = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "localAxisA" ){ static_cast<Box2DWheelJointDef*>( obj->data )->localAxisA = sgs_GetVar<b2Vec2>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "enableMotor" ){ static_cast<Box2DWheelJointDef*>( obj->data )->enableMotor = sgs_GetVar<bool>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorTorque" ){ static_cast<Box2DWheelJointDef*>( obj->data )->maxMotorTorque = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ static_cast<Box2DWheelJointDef*>( obj->data )->motorSpeed = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "frequencyHz" ){ static_cast<Box2DWheelJointDef*>( obj->data )->frequencyHz = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ static_cast<Box2DWheelJointDef*>( obj->data )->dampingRatio = sgs_GetVar<float32>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DWheelJointDef::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWheelJointDef*>( obj->data )->C, C );
	char bfr[ 50 ];
	sprintf( bfr, "Box2DWheelJointDef (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->_bodyA, depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->_bodyB, depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->collideConnected, depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->_userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->localAnchorA, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->localAnchorB, depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAxisA = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->localAxisA, depth ).push( C ); }
		{ sgs_PushString( C, "\nenableMotor = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->enableMotor, depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxMotorTorque = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->maxMotorTorque, depth ).push( C ); }
		{ sgs_PushString( C, "\nmotorSpeed = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->motorSpeed, depth ).push( C ); }
		{ sgs_PushString( C, "\nfrequencyHz = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->frequencyHz, depth ).push( C ); }
		{ sgs_PushString( C, "\ndampingRatio = " ); sgs_DumpData( C, static_cast<Box2DWheelJointDef*>( obj->data )->dampingRatio, depth ).push( C ); }
		sgs_StringConcat( C, 28 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DWheelJointDef__sgs_funcs[] =
{
	{ "Initialize", _sgs_method__Box2DWheelJointDef__Initialize },
	{ NULL, NULL },
};

static int Box2DWheelJointDef__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DWheelJointDef__sgs_funcs,
		-1, "Box2DWheelJointDef." );
	return 1;
}

static sgs_ObjInterface Box2DWheelJointDef__sgs_interface =
{
	"Box2DWheelJointDef",
	Box2DWheelJointDef::_sgs_destruct, Box2DWheelJointDef::gcmark, Box2DWheelJointDef::_sgs_getindex, Box2DWheelJointDef::_sgs_setindex, NULL, NULL, Box2DWheelJointDef::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DWheelJointDef::_sgs_interface(Box2DWheelJointDef__sgs_interface, Box2DWheelJointDef__sgs_ifn);


static int _sgs_method__Box2DJoint__GetReactionForce( SGS_CTX )
{
	Box2DJoint* data; if( !SGS_PARSE_METHOD( C, Box2DJoint::_sgs_interface, data, Box2DJoint, GetReactionForce ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetReactionForce( sgs_GetVar<float32>()(C,0) )); return 1;
}

static int _sgs_method__Box2DJoint__GetReactionTorque( SGS_CTX )
{
	Box2DJoint* data; if( !SGS_PARSE_METHOD( C, Box2DJoint::_sgs_interface, data, Box2DJoint, GetReactionTorque ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetReactionTorque( sgs_GetVar<float32>()(C,0) )); return 1;
}

static int _sgs_method__Box2DJoint__Dump( SGS_CTX )
{
	Box2DJoint* data; if( !SGS_PARSE_METHOD( C, Box2DJoint::_sgs_interface, data, Box2DJoint, Dump ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Dump(  ); return 0;
}

static int _sgs_method__Box2DJoint__ShiftOrigin( SGS_CTX )
{
	Box2DJoint* data; if( !SGS_PARSE_METHOD( C, Box2DJoint::_sgs_interface, data, Box2DJoint, ShiftOrigin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ShiftOrigin( sgs_GetVar<b2Vec2>()(C,0) ); return 0;
}

static int _sgs_method__Box2DJoint__GetMotorTorque( SGS_CTX )
{
	Box2DJoint* data; if( !SGS_PARSE_METHOD( C, Box2DJoint::_sgs_interface, data, Box2DJoint, GetMotorTorque ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetMotorTorque( sgs_GetVar<float32>()(C,0) )); return 1;
}

static int _sgs_method__Box2DJoint__GetMotorForce( SGS_CTX )
{
	Box2DJoint* data; if( !SGS_PARSE_METHOD( C, Box2DJoint::_sgs_interface, data, Box2DJoint, GetMotorForce ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->GetMotorForce( sgs_GetVar<float32>()(C,0) )); return 1;
}

int Box2DJoint::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DJoint*>( obj->data )->C = C;
	static_cast<Box2DJoint*>( obj->data )->~Box2DJoint();
	return SGS_SUCCESS;
}

int Box2DJoint::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DJoint*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DJoint::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DJoint*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getType() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyA" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getBodyA() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyB" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getBodyB() ); return SGS_SUCCESS; }
		SGS_CASE( "worldAnchorA" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getWorldAnchorA() ); return SGS_SUCCESS; }
		SGS_CASE( "worldAnchorB" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getWorldAnchorB() ); return SGS_SUCCESS; }
		SGS_CASE( "next" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getNext() ); return SGS_SUCCESS; }
		SGS_CASE( "userData" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->userData ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->onDestroy ); return SGS_SUCCESS; }
		SGS_CASE( "active" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getActive() ); return SGS_SUCCESS; }
		SGS_CASE( "collideConnected" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getCollideConnected() ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorA" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLocalAnchorA() ); return SGS_SUCCESS; }
		SGS_CASE( "localAnchorB" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLocalAnchorB() ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getMaxForce() ); return SGS_SUCCESS; }
		SGS_CASE( "maxTorque" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getMaxTorque() ); return SGS_SUCCESS; }
		SGS_CASE( "frequency" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getFrequency() ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getDampingRatio() ); return SGS_SUCCESS; }
		SGS_CASE( "referenceAngle" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getReferenceAngle() ); return SGS_SUCCESS; }
		SGS_CASE( "jointTranslation" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getJointTranslation() ); return SGS_SUCCESS; }
		SGS_CASE( "jointSpeed" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getJointSpeed() ); return SGS_SUCCESS; }
		SGS_CASE( "jointLinearSpeed" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getJointLinearSpeed() ); return SGS_SUCCESS; }
		SGS_CASE( "jointAngularSpeed" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getJointAngularSpeed() ); return SGS_SUCCESS; }
		SGS_CASE( "limit" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLimit() ); return SGS_SUCCESS; }
		SGS_CASE( "lowerLimit" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLowerLimit() ); return SGS_SUCCESS; }
		SGS_CASE( "upperLimit" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getUpperLimit() ); return SGS_SUCCESS; }
		SGS_CASE( "motor" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getMotor() ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getMotorSpeed() ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorTorque" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getMaxMotorTorque() ); return SGS_SUCCESS; }
		SGS_CASE( "ratio" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getRatio() ); return SGS_SUCCESS; }
		SGS_CASE( "length" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLength() ); return SGS_SUCCESS; }
		SGS_CASE( "joint1" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getJoint1() ); return SGS_SUCCESS; }
		SGS_CASE( "joint2" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getJoint2() ); return SGS_SUCCESS; }
		SGS_CASE( "linearOffset" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLinearOffset() ); return SGS_SUCCESS; }
		SGS_CASE( "angularOffset" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getAngularOffset() ); return SGS_SUCCESS; }
		SGS_CASE( "correctionFactor" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getCorrectionFactor() ); return SGS_SUCCESS; }
		SGS_CASE( "target" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getTarget() ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorForce" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getMaxMotorForce() ); return SGS_SUCCESS; }
		SGS_CASE( "groundAnchorA" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getGroundAnchorA() ); return SGS_SUCCESS; }
		SGS_CASE( "groundAnchorB" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getGroundAnchorB() ); return SGS_SUCCESS; }
		SGS_CASE( "lengthA" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLengthA() ); return SGS_SUCCESS; }
		SGS_CASE( "lengthB" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLengthB() ); return SGS_SUCCESS; }
		SGS_CASE( "currentLengthA" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getCurrentLengthA() ); return SGS_SUCCESS; }
		SGS_CASE( "currentLengthB" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getCurrentLengthB() ); return SGS_SUCCESS; }
		SGS_CASE( "jointAngle" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getJointAngle() ); return SGS_SUCCESS; }
		SGS_CASE( "maxLength" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getMaxLength() ); return SGS_SUCCESS; }
		SGS_CASE( "limitState" ){ sgs_PushVar( C, static_cast<Box2DJoint*>( obj->data )->_getLimitState() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DJoint::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DJoint*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "userData" ){ static_cast<Box2DJoint*>( obj->data )->userData = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "onDestroy" ){ static_cast<Box2DJoint*>( obj->data )->onDestroy = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "maxForce" ){ static_cast<Box2DJoint*>( obj->data )->_setMaxForce( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "maxTorque" ){ static_cast<Box2DJoint*>( obj->data )->_setMaxTorque( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "frequency" ){ static_cast<Box2DJoint*>( obj->data )->_setFrequency( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "dampingRatio" ){ static_cast<Box2DJoint*>( obj->data )->_setDampingRatio( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "limit" ){ static_cast<Box2DJoint*>( obj->data )->_setLimit( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "lowerLimit" ){ static_cast<Box2DJoint*>( obj->data )->_setLowerLimit( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "upperLimit" ){ static_cast<Box2DJoint*>( obj->data )->_setUpperLimit( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "motor" ){ static_cast<Box2DJoint*>( obj->data )->_setMotor( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "motorSpeed" ){ static_cast<Box2DJoint*>( obj->data )->_setMotorSpeed( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorTorque" ){ static_cast<Box2DJoint*>( obj->data )->_setMaxMotorTorque( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "ratio" ){ static_cast<Box2DJoint*>( obj->data )->_setRatio( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "length" ){ static_cast<Box2DJoint*>( obj->data )->_setLength( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "linearOffset" ){ static_cast<Box2DJoint*>( obj->data )->_setLinearOffset( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "angularOffset" ){ static_cast<Box2DJoint*>( obj->data )->_setAngularOffset( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "correctionFactor" ){ static_cast<Box2DJoint*>( obj->data )->_setCorrectionFactor( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "target" ){ static_cast<Box2DJoint*>( obj->data )->_setTarget( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "maxMotorForce" ){ static_cast<Box2DJoint*>( obj->data )->_setMaxMotorForce( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "maxLength" ){ static_cast<Box2DJoint*>( obj->data )->_setMaxLength( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DJoint::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DJoint*>( obj->data )->C, C );
	char bfr[ 42 ];
	sprintf( bfr, "Box2DJoint (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ntype = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getType(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyA = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getBodyA(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyB = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getBodyB(), depth ).push( C ); }
		{ sgs_PushString( C, "\nworldAnchorA = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getWorldAnchorA(), depth ).push( C ); }
		{ sgs_PushString( C, "\nworldAnchorB = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getWorldAnchorB(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnext = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getNext(), depth ).push( C ); }
		{ sgs_PushString( C, "\nuserData = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->userData, depth ).push( C ); }
		{ sgs_PushString( C, "\nonDestroy = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->onDestroy, depth ).push( C ); }
		{ sgs_PushString( C, "\nactive = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getActive(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncollideConnected = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getCollideConnected(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorA = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLocalAnchorA(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlocalAnchorB = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLocalAnchorB(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxForce = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getMaxForce(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxTorque = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getMaxTorque(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfrequency = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getFrequency(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndampingRatio = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getDampingRatio(), depth ).push( C ); }
		{ sgs_PushString( C, "\nreferenceAngle = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getReferenceAngle(), depth ).push( C ); }
		{ sgs_PushString( C, "\njointTranslation = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getJointTranslation(), depth ).push( C ); }
		{ sgs_PushString( C, "\njointSpeed = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getJointSpeed(), depth ).push( C ); }
		{ sgs_PushString( C, "\njointLinearSpeed = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getJointLinearSpeed(), depth ).push( C ); }
		{ sgs_PushString( C, "\njointAngularSpeed = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getJointAngularSpeed(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlimit = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLimit(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlowerLimit = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLowerLimit(), depth ).push( C ); }
		{ sgs_PushString( C, "\nupperLimit = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getUpperLimit(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmotor = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getMotor(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmotorSpeed = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getMotorSpeed(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxMotorTorque = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getMaxMotorTorque(), depth ).push( C ); }
		{ sgs_PushString( C, "\nratio = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getRatio(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlength = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLength(), depth ).push( C ); }
		{ sgs_PushString( C, "\njoint1 = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getJoint1(), depth ).push( C ); }
		{ sgs_PushString( C, "\njoint2 = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getJoint2(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlinearOffset = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLinearOffset(), depth ).push( C ); }
		{ sgs_PushString( C, "\nangularOffset = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getAngularOffset(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncorrectionFactor = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getCorrectionFactor(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntarget = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getTarget(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxMotorForce = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getMaxMotorForce(), depth ).push( C ); }
		{ sgs_PushString( C, "\ngroundAnchorA = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getGroundAnchorA(), depth ).push( C ); }
		{ sgs_PushString( C, "\ngroundAnchorB = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getGroundAnchorB(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlengthA = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLengthA(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlengthB = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLengthB(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncurrentLengthA = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getCurrentLengthA(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncurrentLengthB = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getCurrentLengthB(), depth ).push( C ); }
		{ sgs_PushString( C, "\njointAngle = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getJointAngle(), depth ).push( C ); }
		{ sgs_PushString( C, "\nmaxLength = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getMaxLength(), depth ).push( C ); }
		{ sgs_PushString( C, "\nlimitState = " ); sgs_DumpData( C, static_cast<Box2DJoint*>( obj->data )->_getLimitState(), depth ).push( C ); }
		sgs_StringConcat( C, 90 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DJoint__sgs_funcs[] =
{
	{ "GetReactionForce", _sgs_method__Box2DJoint__GetReactionForce },
	{ "GetReactionTorque", _sgs_method__Box2DJoint__GetReactionTorque },
	{ "Dump", _sgs_method__Box2DJoint__Dump },
	{ "ShiftOrigin", _sgs_method__Box2DJoint__ShiftOrigin },
	{ "GetMotorTorque", _sgs_method__Box2DJoint__GetMotorTorque },
	{ "GetMotorForce", _sgs_method__Box2DJoint__GetMotorForce },
	{ NULL, NULL },
};

static int Box2DJoint__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DJoint__sgs_funcs,
		-1, "Box2DJoint." );
	return 1;
}

static sgs_ObjInterface Box2DJoint__sgs_interface =
{
	"Box2DJoint",
	Box2DJoint::_sgs_destruct, Box2DJoint::gcmark, Box2DJoint::_sgs_getindex, Box2DJoint::_sgs_setindex, NULL, NULL, Box2DJoint::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DJoint::_sgs_interface(Box2DJoint__sgs_interface, Box2DJoint__sgs_ifn);


static int _sgs_method__Box2DContact__ResetFriction( SGS_CTX )
{
	Box2DContact* data; if( !SGS_PARSE_METHOD( C, Box2DContact::_sgs_interface, data, Box2DContact, ResetFriction ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ResetFriction(  ); return 0;
}

static int _sgs_method__Box2DContact__ResetRestitution( SGS_CTX )
{
	Box2DContact* data; if( !SGS_PARSE_METHOD( C, Box2DContact::_sgs_interface, data, Box2DContact, ResetRestitution ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ResetRestitution(  ); return 0;
}

int Box2DContact::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DContact*>( obj->data )->C = C;
	static_cast<Box2DContact*>( obj->data )->~Box2DContact();
	return SGS_SUCCESS;
}

int Box2DContact::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DContact*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DContact::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DContact*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "isTouching" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_isTouching() ); return SGS_SUCCESS; }
		SGS_CASE( "enabled" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_enabled() ); return SGS_SUCCESS; }
		SGS_CASE( "next" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_next() ); return SGS_SUCCESS; }
		SGS_CASE( "fixtureA" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_fixtureA() ); return SGS_SUCCESS; }
		SGS_CASE( "fixtureB" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_fixtureB() ); return SGS_SUCCESS; }
		SGS_CASE( "childIndexA" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_childIndexA() ); return SGS_SUCCESS; }
		SGS_CASE( "childIndexB" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_childIndexB() ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_friction() ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_restitution() ); return SGS_SUCCESS; }
		SGS_CASE( "tangentSpeed" ){ sgs_PushVar( C, static_cast<Box2DContact*>( obj->data )->_get_tangentSpeed() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DContact::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DContact*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "enabled" ){ static_cast<Box2DContact*>( obj->data )->_set_enabled( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "friction" ){ static_cast<Box2DContact*>( obj->data )->_set_friction( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "restitution" ){ static_cast<Box2DContact*>( obj->data )->_set_restitution( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "tangentSpeed" ){ static_cast<Box2DContact*>( obj->data )->_set_tangentSpeed( sgs_GetVar<float32>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DContact::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DContact*>( obj->data )->C, C );
	char bfr[ 44 ];
	sprintf( bfr, "Box2DContact (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nisTouching = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_isTouching(), depth ).push( C ); }
		{ sgs_PushString( C, "\nenabled = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_enabled(), depth ).push( C ); }
		{ sgs_PushString( C, "\nnext = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_next(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfixtureA = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_fixtureA(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfixtureB = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_fixtureB(), depth ).push( C ); }
		{ sgs_PushString( C, "\nchildIndexA = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_childIndexA(), depth ).push( C ); }
		{ sgs_PushString( C, "\nchildIndexB = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_childIndexB(), depth ).push( C ); }
		{ sgs_PushString( C, "\nfriction = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_friction(), depth ).push( C ); }
		{ sgs_PushString( C, "\nrestitution = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_restitution(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntangentSpeed = " ); sgs_DumpData( C, static_cast<Box2DContact*>( obj->data )->_get_tangentSpeed(), depth ).push( C ); }
		sgs_StringConcat( C, 20 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DContact__sgs_funcs[] =
{
	{ "ResetFriction", _sgs_method__Box2DContact__ResetFriction },
	{ "ResetRestitution", _sgs_method__Box2DContact__ResetRestitution },
	{ NULL, NULL },
};

static int Box2DContact__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DContact__sgs_funcs,
		-1, "Box2DContact." );
	return 1;
}

static sgs_ObjInterface Box2DContact__sgs_interface =
{
	"Box2DContact",
	Box2DContact::_sgs_destruct, Box2DContact::_sgs_gcmark, Box2DContact::_sgs_getindex, Box2DContact::_sgs_setindex, NULL, NULL, Box2DContact::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DContact::_sgs_interface(Box2DContact__sgs_interface, Box2DContact__sgs_ifn);


int Box2DDraw::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DDraw*>( obj->data )->C = C;
	static_cast<Box2DDraw*>( obj->data )->~Box2DDraw();
	return SGS_SUCCESS;
}

int Box2DDraw::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDraw*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DDraw::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDraw*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "flags" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->GetFlags() ); return SGS_SUCCESS; }
		SGS_CASE( "drawShapes" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->_getDrawShapes() ); return SGS_SUCCESS; }
		SGS_CASE( "drawJoints" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->_getDrawJoints() ); return SGS_SUCCESS; }
		SGS_CASE( "drawAABBs" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->_getDrawAABBs() ); return SGS_SUCCESS; }
		SGS_CASE( "drawPairs" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->_getDrawPairs() ); return SGS_SUCCESS; }
		SGS_CASE( "drawCenters" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->_getDrawCenters() ); return SGS_SUCCESS; }
		SGS_CASE( "data" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->data ); return SGS_SUCCESS; }
		SGS_CASE( "DrawPolygon" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->fnDrawPolygon ); return SGS_SUCCESS; }
		SGS_CASE( "DrawSolidPolygon" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->fnDrawSolidPolygon ); return SGS_SUCCESS; }
		SGS_CASE( "DrawCircle" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->fnDrawCircle ); return SGS_SUCCESS; }
		SGS_CASE( "DrawSolidCircle" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->fnDrawSolidCircle ); return SGS_SUCCESS; }
		SGS_CASE( "DrawSegment" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->fnDrawSegment ); return SGS_SUCCESS; }
		SGS_CASE( "DrawTransform" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->fnDrawTransform ); return SGS_SUCCESS; }
		SGS_CASE( "DrawPoint" ){ sgs_PushVar( C, static_cast<Box2DDraw*>( obj->data )->fnDrawPoint ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DDraw::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDraw*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "flags" ){ static_cast<Box2DDraw*>( obj->data )->SetFlags( sgs_GetVar<uint32_t>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "drawShapes" ){ static_cast<Box2DDraw*>( obj->data )->_setDrawShapes( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "drawJoints" ){ static_cast<Box2DDraw*>( obj->data )->_setDrawJoints( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "drawAABBs" ){ static_cast<Box2DDraw*>( obj->data )->_setDrawAABBs( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "drawPairs" ){ static_cast<Box2DDraw*>( obj->data )->_setDrawPairs( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "drawCenters" ){ static_cast<Box2DDraw*>( obj->data )->_setDrawCenters( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "data" ){ static_cast<Box2DDraw*>( obj->data )->data = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "DrawPolygon" ){ static_cast<Box2DDraw*>( obj->data )->fnDrawPolygon = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "DrawSolidPolygon" ){ static_cast<Box2DDraw*>( obj->data )->fnDrawSolidPolygon = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "DrawCircle" ){ static_cast<Box2DDraw*>( obj->data )->fnDrawCircle = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "DrawSolidCircle" ){ static_cast<Box2DDraw*>( obj->data )->fnDrawSolidCircle = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "DrawSegment" ){ static_cast<Box2DDraw*>( obj->data )->fnDrawSegment = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "DrawTransform" ){ static_cast<Box2DDraw*>( obj->data )->fnDrawTransform = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "DrawPoint" ){ static_cast<Box2DDraw*>( obj->data )->fnDrawPoint = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DDraw::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DDraw*>( obj->data )->C, C );
	char bfr[ 41 ];
	sprintf( bfr, "Box2DDraw (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nflags = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->GetFlags(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndrawShapes = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->_getDrawShapes(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndrawJoints = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->_getDrawJoints(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndrawAABBs = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->_getDrawAABBs(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndrawPairs = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->_getDrawPairs(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndrawCenters = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->_getDrawCenters(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndata = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->data, depth ).push( C ); }
		{ sgs_PushString( C, "\nDrawPolygon = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->fnDrawPolygon, depth ).push( C ); }
		{ sgs_PushString( C, "\nDrawSolidPolygon = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->fnDrawSolidPolygon, depth ).push( C ); }
		{ sgs_PushString( C, "\nDrawCircle = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->fnDrawCircle, depth ).push( C ); }
		{ sgs_PushString( C, "\nDrawSolidCircle = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->fnDrawSolidCircle, depth ).push( C ); }
		{ sgs_PushString( C, "\nDrawSegment = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->fnDrawSegment, depth ).push( C ); }
		{ sgs_PushString( C, "\nDrawTransform = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->fnDrawTransform, depth ).push( C ); }
		{ sgs_PushString( C, "\nDrawPoint = " ); sgs_DumpData( C, static_cast<Box2DDraw*>( obj->data )->fnDrawPoint, depth ).push( C ); }
		sgs_StringConcat( C, 28 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DDraw__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int Box2DDraw__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DDraw__sgs_funcs,
		-1, "Box2DDraw." );
	return 1;
}

static sgs_ObjInterface Box2DDraw__sgs_interface =
{
	"Box2DDraw",
	Box2DDraw::_sgs_destruct, Box2DDraw::gcmark, Box2DDraw::_sgs_getindex, Box2DDraw::_sgs_setindex, NULL, NULL, Box2DDraw::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DDraw::_sgs_interface(Box2DDraw__sgs_interface, Box2DDraw__sgs_ifn);


static int _sgs_method__Box2DWorld__CreateBody( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, CreateBody ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->CreateBody( sgs_GetVar<Box2DBodyDef::Handle>()(C,0) )); return 1;
}

static int _sgs_method__Box2DWorld__DestroyBody( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, DestroyBody ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->DestroyBody( sgs_GetVar<Box2DBodyHandle>()(C,0) ); return 0;
}

static int _sgs_method__Box2DWorld__CreateJoint( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, CreateJoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->CreateJoint( sgs_GetVar<sgsVariable>()(C,0) )); return 1;
}

static int _sgs_method__Box2DWorld__DestroyJoint( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, DestroyJoint ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->DestroyJoint( sgs_GetVar<Box2DJointHandle>()(C,0) ); return 0;
}

static int _sgs_method__Box2DWorld__Step( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, Step ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Step( sgs_GetVar<float32>()(C,0), sgs_GetVar<int32>()(C,1), sgs_GetVar<int32>()(C,2) ); return 0;
}

static int _sgs_method__Box2DWorld__ClearForces( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, ClearForces ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ClearForces(  ); return 0;
}

static int _sgs_method__Box2DWorld__DrawDebugData( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, DrawDebugData ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->DrawDebugData(  ); return 0;
}

static int _sgs_method__Box2DWorld__QueryAABB( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, QueryAABB ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->QueryAABB( sgs_GetVar<sgsVariable>()(C,0), sgs_GetVar<b2AABB>()(C,1) ); return 0;
}

static int _sgs_method__Box2DWorld__RayCast( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, RayCast ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->RayCast( sgs_GetVar<sgsVariable>()(C,0), sgs_GetVar<b2Vec2>()(C,1), sgs_GetVar<b2Vec2>()(C,2) ); return 0;
}

static int _sgs_method__Box2DWorld__ShiftOrigin( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, ShiftOrigin ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ShiftOrigin( sgs_GetVar<b2Vec2>()(C,0) ); return 0;
}

static int _sgs_method__Box2DWorld__Dump( SGS_CTX )
{
	Box2DWorld* data; if( !SGS_PARSE_METHOD( C, Box2DWorld::_sgs_interface, data, Box2DWorld, Dump ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->Dump(  ); return 0;
}

int Box2DWorld::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<Box2DWorld*>( obj->data )->C = C;
	static_cast<Box2DWorld*>( obj->data )->~Box2DWorld();
	return SGS_SUCCESS;
}

int Box2DWorld::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWorld*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int Box2DWorld::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWorld*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "debugDraw" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getDebugDraw() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyList" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getBodyList() ); return SGS_SUCCESS; }
		SGS_CASE( "contactList" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getContactList() ); return SGS_SUCCESS; }
		SGS_CASE( "jointList" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getJointList() ); return SGS_SUCCESS; }
		SGS_CASE( "allowSleeping" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getAllowSleeping() ); return SGS_SUCCESS; }
		SGS_CASE( "warmStarting" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getWarmStarting() ); return SGS_SUCCESS; }
		SGS_CASE( "continuousPhysics" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getContinuousPhysics() ); return SGS_SUCCESS; }
		SGS_CASE( "subStepping" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getSubStepping() ); return SGS_SUCCESS; }
		SGS_CASE( "autoClearForces" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getAutoClearForces() ); return SGS_SUCCESS; }
		SGS_CASE( "proxyCount" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getProxyCount() ); return SGS_SUCCESS; }
		SGS_CASE( "bodyCount" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getBodyCount() ); return SGS_SUCCESS; }
		SGS_CASE( "jointCount" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getJointCount() ); return SGS_SUCCESS; }
		SGS_CASE( "contactCount" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getContactCount() ); return SGS_SUCCESS; }
		SGS_CASE( "treeHeight" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getTreeHeight() ); return SGS_SUCCESS; }
		SGS_CASE( "treeBalance" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getTreeBalance() ); return SGS_SUCCESS; }
		SGS_CASE( "treeQuality" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getTreeQuality() ); return SGS_SUCCESS; }
		SGS_CASE( "gravity" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->_getGravity() ); return SGS_SUCCESS; }
		SGS_CASE( "destructionListener" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->destructionListener ); return SGS_SUCCESS; }
		SGS_CASE( "contactFilter" ){ sgs_PushVar( C, static_cast<Box2DWorld*>( obj->data )->contactFilter ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DWorld::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWorld*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "debugDraw" ){ static_cast<Box2DWorld*>( obj->data )->_setDebugDraw( sgs_GetVar<Box2DDrawHandle>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "allowSleeping" ){ static_cast<Box2DWorld*>( obj->data )->_setAllowSleeping( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "warmStarting" ){ static_cast<Box2DWorld*>( obj->data )->_setWarmStarting( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "continuousPhysics" ){ static_cast<Box2DWorld*>( obj->data )->_setContinuousPhysics( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "subStepping" ){ static_cast<Box2DWorld*>( obj->data )->_setSubStepping( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "autoClearForces" ){ static_cast<Box2DWorld*>( obj->data )->_setAutoClearForces( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "gravity" ){ static_cast<Box2DWorld*>( obj->data )->_setGravity( sgs_GetVar<b2Vec2>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "destructionListener" ){ static_cast<Box2DWorld*>( obj->data )->destructionListener = sgs_GetVar<sgsVariable>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "contactFilter" ){ static_cast<Box2DWorld*>( obj->data )->contactFilter = sgs_GetVar<sgsVariable>()( C, 1 );
			static_cast<Box2DWorld*>( obj->data )->_changeContactFilter(); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int Box2DWorld::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<Box2DWorld*>( obj->data )->C, C );
	char bfr[ 42 ];
	sprintf( bfr, "Box2DWorld (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ndebugDraw = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getDebugDraw(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyList = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getBodyList(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncontactList = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getContactList(), depth ).push( C ); }
		{ sgs_PushString( C, "\njointList = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getJointList(), depth ).push( C ); }
		{ sgs_PushString( C, "\nallowSleeping = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getAllowSleeping(), depth ).push( C ); }
		{ sgs_PushString( C, "\nwarmStarting = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getWarmStarting(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncontinuousPhysics = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getContinuousPhysics(), depth ).push( C ); }
		{ sgs_PushString( C, "\nsubStepping = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getSubStepping(), depth ).push( C ); }
		{ sgs_PushString( C, "\nautoClearForces = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getAutoClearForces(), depth ).push( C ); }
		{ sgs_PushString( C, "\nproxyCount = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getProxyCount(), depth ).push( C ); }
		{ sgs_PushString( C, "\nbodyCount = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getBodyCount(), depth ).push( C ); }
		{ sgs_PushString( C, "\njointCount = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getJointCount(), depth ).push( C ); }
		{ sgs_PushString( C, "\ncontactCount = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getContactCount(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntreeHeight = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getTreeHeight(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntreeBalance = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getTreeBalance(), depth ).push( C ); }
		{ sgs_PushString( C, "\ntreeQuality = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getTreeQuality(), depth ).push( C ); }
		{ sgs_PushString( C, "\ngravity = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->_getGravity(), depth ).push( C ); }
		{ sgs_PushString( C, "\ndestructionListener = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->destructionListener, depth ).push( C ); }
		{ sgs_PushString( C, "\ncontactFilter = " ); sgs_DumpData( C, static_cast<Box2DWorld*>( obj->data )->contactFilter, depth ).push( C ); }
		sgs_StringConcat( C, 38 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst Box2DWorld__sgs_funcs[] =
{
	{ "CreateBody", _sgs_method__Box2DWorld__CreateBody },
	{ "DestroyBody", _sgs_method__Box2DWorld__DestroyBody },
	{ "CreateJoint", _sgs_method__Box2DWorld__CreateJoint },
	{ "DestroyJoint", _sgs_method__Box2DWorld__DestroyJoint },
	{ "Step", _sgs_method__Box2DWorld__Step },
	{ "ClearForces", _sgs_method__Box2DWorld__ClearForces },
	{ "DrawDebugData", _sgs_method__Box2DWorld__DrawDebugData },
	{ "QueryAABB", _sgs_method__Box2DWorld__QueryAABB },
	{ "RayCast", _sgs_method__Box2DWorld__RayCast },
	{ "ShiftOrigin", _sgs_method__Box2DWorld__ShiftOrigin },
	{ "Dump", _sgs_method__Box2DWorld__Dump },
	{ NULL, NULL },
};

static int Box2DWorld__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		Box2DWorld__sgs_funcs,
		-1, "Box2DWorld." );
	return 1;
}

static sgs_ObjInterface Box2DWorld__sgs_interface =
{
	"Box2DWorld",
	Box2DWorld::_sgs_destruct, Box2DWorld::gcmark, Box2DWorld::_sgs_getindex, Box2DWorld::_sgs_setindex, NULL, NULL, Box2DWorld::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface Box2DWorld::_sgs_interface(Box2DWorld__sgs_interface, Box2DWorld__sgs_ifn);

