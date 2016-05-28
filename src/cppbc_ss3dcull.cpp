// SGS/CPP-BC
// warning: do not modify this file, it may be regenerated during any build

#include "src/ss3dcull.hpp"

static int _sgs_method__SS3D_OcclusionTest__ClearWorld( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, ClearWorld ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->ClearWorld(  ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__AddWorldBox( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, AddWorldBox ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->AddWorldBox( sgs_GetVar<Vec3>()(C,0), sgs_GetVar<Vec3>()(C,1), sgs_GetVar<Mat4>()(C,2) ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__AddWorldTriangle( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, AddWorldTriangle ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->AddWorldTriangle( sgs_GetVar<Vec3>()(C,0), sgs_GetVar<Vec3>()(C,1), sgs_GetVar<Vec3>()(C,2), sgs_GetVar<bool>()(C,3) ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__CreateCullScene( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, CreateCullScene ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->CreateCullScene(  )); return 1;
}

static int _sgs_method__SS3D_OcclusionTest__DumpBuffer( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, DumpBuffer ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->DumpBuffer( sgs_GetVar<sgsString>()(C,0) ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__DumpImage( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, DumpImage ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->DumpImage( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1) );
}

int SS3D_OcclusionTest::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SS3D_OcclusionTest*>( obj->data )->C = C;
	static_cast<SS3D_OcclusionTest*>( obj->data )->~SS3D_OcclusionTest();
	return SGS_SUCCESS;
}

int SS3D_OcclusionTest::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SS3D_OcclusionTest*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int SS3D_OcclusionTest::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SS3D_OcclusionTest*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SS3D_OcclusionTest::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SS3D_OcclusionTest*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SS3D_OcclusionTest::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SS3D_OcclusionTest*>( obj->data )->C, C );
	char bfr[ 50 ];
	sprintf( bfr, "SS3D_OcclusionTest (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		sgs_StringConcat( C, 0 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst SS3D_OcclusionTest__sgs_funcs[] =
{
	{ "ClearWorld", _sgs_method__SS3D_OcclusionTest__ClearWorld },
	{ "AddWorldBox", _sgs_method__SS3D_OcclusionTest__AddWorldBox },
	{ "AddWorldTriangle", _sgs_method__SS3D_OcclusionTest__AddWorldTriangle },
	{ "CreateCullScene", _sgs_method__SS3D_OcclusionTest__CreateCullScene },
	{ "DumpBuffer", _sgs_method__SS3D_OcclusionTest__DumpBuffer },
	{ "DumpImage", _sgs_method__SS3D_OcclusionTest__DumpImage },
	{ NULL, NULL },
};

static int SS3D_OcclusionTest__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SS3D_OcclusionTest__sgs_funcs,
		-1, "SS3D_OcclusionTest." );
	return 1;
}

static sgs_ObjInterface SS3D_OcclusionTest__sgs_interface =
{
	"SS3D_OcclusionTest",
	SS3D_OcclusionTest::_sgs_destruct, SS3D_OcclusionTest::_sgs_gcmark, SS3D_OcclusionTest::_sgs_getindex, SS3D_OcclusionTest::_sgs_setindex, NULL, NULL, SS3D_OcclusionTest::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SS3D_OcclusionTest::_sgs_interface(SS3D_OcclusionTest__sgs_interface, SS3D_OcclusionTest__sgs_ifn);

