// SGS/CPP-BC
// warning: do not modify this file, it may be regenerated during any build
// generated: 11/09/14 21:45:26

#include "src/ss3dcull.hpp"

static int _sgs_method__SS3D_OcclusionTest__ClearWorld( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, ClearWorld ) ) return 0;
	data->ClearWorld(  ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__AddWorldBox( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, AddWorldBox ) ) return 0;
	data->AddWorldBox( sgs_GetVar<Vec3>()(C,0), sgs_GetVar<Vec3>()(C,1), sgs_GetVar<Mat4>()(C,2) ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__AddWorldTriangle( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, AddWorldTriangle ) ) return 0;
	data->AddWorldTriangle( sgs_GetVar<Vec3>()(C,0), sgs_GetVar<Vec3>()(C,1), sgs_GetVar<Vec3>()(C,2), sgs_GetVar<bool>()(C,3) ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__CreateCullScene( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, CreateCullScene ) ) return 0;
	sgs_PushVar(C,data->CreateCullScene(  )); return 1;
}

static int _sgs_method__SS3D_OcclusionTest__DumpBuffer( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, DumpBuffer ) ) return 0;
	data->DumpBuffer( sgs_GetVar<sgsString>()(C,0) ); return 0;
}

static int _sgs_method__SS3D_OcclusionTest__DumpImage( SGS_CTX )
{
	SS3D_OcclusionTest* data; if( !SGS_PARSE_METHOD( C, SS3D_OcclusionTest::_sgs_interface, data, SS3D_OcclusionTest, DumpImage ) ) return 0;
	return data->DumpImage( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1) );
}

int SS3D_OcclusionTest::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SS3D_OcclusionTest*>( obj->data )->~SS3D_OcclusionTest();
	return SGS_SUCCESS;
}

int SS3D_OcclusionTest::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	return SGS_SUCCESS;
}

int SS3D_OcclusionTest::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "ClearWorld" ){ sgs_PushCFunction( C, _sgs_method__SS3D_OcclusionTest__ClearWorld ); return SGS_SUCCESS; }
		SGS_CASE( "AddWorldBox" ){ sgs_PushCFunction( C, _sgs_method__SS3D_OcclusionTest__AddWorldBox ); return SGS_SUCCESS; }
		SGS_CASE( "AddWorldTriangle" ){ sgs_PushCFunction( C, _sgs_method__SS3D_OcclusionTest__AddWorldTriangle ); return SGS_SUCCESS; }
		SGS_CASE( "CreateCullScene" ){ sgs_PushCFunction( C, _sgs_method__SS3D_OcclusionTest__CreateCullScene ); return SGS_SUCCESS; }
		SGS_CASE( "DumpBuffer" ){ sgs_PushCFunction( C, _sgs_method__SS3D_OcclusionTest__DumpBuffer ); return SGS_SUCCESS; }
		SGS_CASE( "DumpImage" ){ sgs_PushCFunction( C, _sgs_method__SS3D_OcclusionTest__DumpImage ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SS3D_OcclusionTest::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SS3D_OcclusionTest::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
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

sgs_ObjInterface SS3D_OcclusionTest::_sgs_interface[1] =
{{
	"SS3D_OcclusionTest",
	SS3D_OcclusionTest::_sgs_destruct, SS3D_OcclusionTest::_sgs_gcmark, SS3D_OcclusionTest::_sgs_getindex, SS3D_OcclusionTest::_sgs_setindex, NULL, NULL, SS3D_OcclusionTest::_sgs_dump, NULL, NULL, NULL, 
}};
