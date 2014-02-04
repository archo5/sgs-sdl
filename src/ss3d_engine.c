

#include "ss3d_engine.h"

#define FN( x ) { "SS3D_" #x, SS3D_##x }
#define CN( x ) { "SS3D" #x, SS3D##x }


SGSRESULT sgs_ParseObjectPtr( SGS_CTX, sgs_StkIdx item, sgs_ObjCallback* iface, sgs_VarObj** out, int strict )
{
	if( !strict && sgs_ItemType( C, item ) == SGS_VT_NULL )
	{
		if( *out )
			sgs_ObjRelease( C, *out );
		*out = NULL;
		return SGS_SUCCESS;
	}
	if( sgs_IsObject( C, item, iface ) )
	{
		if( *out )
			sgs_ObjRelease( C, *out );
		*out = sgs_GetObjectStruct( C, item );
		sgs_ObjAcquire( C, *out );
		return SGS_SUCCESS;
	}
	return SGS_EINVAL;
}


//
// MATH

void SS3D_Mtx_Transpose( MAT4 mtx )
{
	float tmp;
#define _MSWAP( a, b ) { tmp = a; a = b; b = tmp; }
	_MSWAP( mtx[0][1], mtx[1][0] );
	_MSWAP( mtx[0][2], mtx[2][0] );
	_MSWAP( mtx[0][3], mtx[3][0] );
	_MSWAP( mtx[1][2], mtx[2][1] );
	_MSWAP( mtx[1][3], mtx[3][1] );
	_MSWAP( mtx[2][3], mtx[3][2] );
#undef _MSWAP
}

void SS3D_Mtx_Multiply( MAT4 out, MAT4 A, MAT4 B )
{
	out[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0];
	out[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1];
	out[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2];
	out[0][3] = A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3];
	out[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0];
	out[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1];
	out[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2];
	out[1][3] = A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3];
	out[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0];
	out[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1];
	out[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2];
	out[2][3] = A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3];
	out[3][0] = A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0];
	out[3][1] = A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1];
	out[3][2] = A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2];
	out[3][3] = A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3];
};

void SS3D_Mtx_Transform( VEC4 out, VEC4 v, MAT4 mtx )
{
	VEC4 r_;
	int i, j;
	for(j=0; j<4; ++j) {
		r_[j] = 0.;
		for(i=0; i<4; ++i) {
			r_[j] += mtx[i][j] * v[i];
		}
	}
	memcpy(out, r_, sizeof(r_));
}

void SS3D_Mtx_TransformPos( VEC3 out, VEC3 pos, MAT4 mtx )
{
	VEC4 tmp, xpos = {pos[0],pos[1],pos[2],1};
	SS3D_Mtx_Transform( tmp, xpos, mtx );
	out[0] = tmp[0]; out[1] = tmp[1]; out[2] = tmp[2];
}

void SS3D_Mtx_Dump( MAT4 mtx )
{
	puts("{");
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[0][0], mtx[0][1], mtx[0][2], mtx[0][3] );
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[1][0], mtx[1][1], mtx[1][2], mtx[1][3] );
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[2][0], mtx[2][1], mtx[2][2], mtx[2][3] );
	printf( "%4.4g %4.4g %4.4g %4.4g\n", mtx[3][0], mtx[3][1], mtx[3][2], mtx[3][3] );
	puts("}");
}

void SS3D_Mtx_LookAt( MAT4 out, VEC3 pos, VEC3 dir, VEC3 up )
{
	VEC3 zaxis, xaxis, yaxis;
	VEC3_Normalized( zaxis, dir );
	VEC3_Cross( xaxis, up, zaxis );
	VEC3_Normalized( xaxis, xaxis );
	VEC3_Cross( yaxis, zaxis, xaxis );
	
	out[0][0] = xaxis[0]; out[0][1] = yaxis[0]; out[0][2] = zaxis[0]; out[0][3] = 0;
	out[1][0] = xaxis[1]; out[1][1] = yaxis[1]; out[1][2] = zaxis[1]; out[1][3] = 0;
	out[2][0] = xaxis[2]; out[2][1] = yaxis[2]; out[2][2] = zaxis[2]; out[2][3] = 0;
	out[3][0] = -VEC3_Dot( xaxis, pos );
	out[3][1] = -VEC3_Dot( yaxis, pos );
	out[3][2] = -VEC3_Dot( zaxis, pos );
	out[3][3] = 1;
}

void SS3D_Mtx_Perspective( MAT4 out, float angle, float aspect, float aamix, float znear, float zfar )
{
	float tha = tan( DEG2RAD( angle ) / 2.0f );
	if( tha < 0.001f ) tha = 0.001f;
	float itha = 1.0f / tha;
	float xscale = itha / pow( aspect, aamix );
	float yscale = itha * pow( aspect, 1 - aamix );
	
	out[0][0] = -xscale;
	out[0][1] = out[0][2] = out[0][3] = 0;
	out[1][1] = yscale;
	out[1][0] = out[1][2] = out[1][3] = 0;
	out[2][2] = zfar / ( zfar - znear );
	out[2][0] = out[2][1] = 0; out[2][3] = 1;
	out[3][2] = -znear * zfar / ( zfar - znear );
	out[3][0] = out[3][1] = out[3][3] = 0;
}


//
// MISC. UTILITY

void SS3D_CallDtor( SGS_CTX, sgs_VarObj* O )
{
	sgs_ObjCallback* cb = O->iface;
	while( cb[0] != SGS_OP_END )
	{
		if( cb[0] == SGS_OP_DESTRUCT )
		{
			cb[1]( C, O, 0 );
			break;
		}
		cb += 2;
	}
}

static void scene_poke_resource( SS3D_Scene* S, sgs_VHTable* which, sgs_VarObj* obj, int add )
{
	sgs_Variable K;
	
	if( !S->renderer || S->destroying )
		return;
	
	K.type = SGS_VT_PTR;
	K.data.P = obj;
	
	if( add )
		sgs_vht_set( &S->lights, S->renderer->C, &K, &K );
	else
		sgs_vht_unset( &S->lights, S->renderer->C, &K );
}


//
// CULL SCENE

sgs_ObjCallback SS3D_CullScene_iface[] =
{
	SGS_OP_END
};


//
// CAMERA

static void camera_recalc_viewmtx( SS3D_Camera* CAM )
{
	SS3D_Mtx_LookAt( CAM->mView, CAM->position, CAM->direction, CAM->up );
}

static void camera_recalc_projmtx( SS3D_Camera* CAM )
{
	SS3D_Mtx_Perspective( CAM->mProj, CAM->angle, CAM->aspect, CAM->aamix, CAM->znear, CAM->zfar );
}

#define CAM_HDR SS3D_Camera* CAM = (SS3D_Camera*) data->data;

static int camera_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	CAM_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" )  SGS_RETURN_VEC3( CAM->position )
		SGS_CASE( "direction" ) SGS_RETURN_VEC3( CAM->direction )
		SGS_CASE( "up" )        SGS_RETURN_VEC3( CAM->up )
		SGS_CASE( "angle" )     SGS_RETURN_REAL( CAM->angle )
		SGS_CASE( "aspect" )    SGS_RETURN_REAL( CAM->aspect )
		SGS_CASE( "aamix" )     SGS_RETURN_REAL( CAM->aamix )
		SGS_CASE( "znear" )     SGS_RETURN_REAL( CAM->znear )
		SGS_CASE( "zfar" )      SGS_RETURN_REAL( CAM->zfar )
	SGS_END_INDEXFUNC;
}

static int camera_setindex_( SGS_CTX, sgs_VarObj* data, int isprop )
{
	CAM_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" )  { return sgs_ParseVec3( C, 1, CAM->position, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "direction" ) { return sgs_ParseVec3( C, 1, CAM->direction, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "up" )        { return sgs_ParseVec3( C, 1, CAM->up, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "angle" )     { sgs_Real val; if( sgs_ParseReal( C, 1, &val ) ){ CAM->angle = val; return 2; } return SGS_EINVAL; }
		SGS_CASE( "aspect" )    { sgs_Real val; if( sgs_ParseReal( C, 1, &val ) ){ CAM->aspect = val; return 2; } return SGS_EINVAL; }
		SGS_CASE( "aamix" )     { sgs_Real val; if( sgs_ParseReal( C, 1, &val ) ){ CAM->aamix = val; return 2; } return SGS_EINVAL; }
		SGS_CASE( "znear" )     { sgs_Real val; if( sgs_ParseReal( C, 1, &val ) ){ CAM->znear = val; return 2; } return SGS_EINVAL; }
		SGS_CASE( "zfar" )      { sgs_Real val; if( sgs_ParseReal( C, 1, &val ) ){ CAM->zfar = val; return 2; } return SGS_EINVAL; }
	SGS_END_INDEXFUNC;
}

static int camera_setindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	CAM_HDR;
	int ret = camera_setindex_( C, data, isprop );
	if( ret < 0 )
		return ret;
	if( ret == 1 ) camera_recalc_viewmtx( CAM );
	if( ret == 2 ) camera_recalc_projmtx( CAM );
	return SGS_SUCCESS;
}

static int camera_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	if( type == SGS_VT_STRING || type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "SS3D_Camera" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int camera_dump( SGS_CTX, sgs_VarObj* data, int maxdepth )
{
	char bfr[ 2048 ];
	CAM_HDR;
	UNUSED( maxdepth );
	
	sprintf( bfr,
		"\nposition=(%g;%g;%g)"
		"\ndirection=(%g;%g;%g)"
		"\nup=(%g;%g;%g)"
		"\nangle=%g"
		"\naspect=%g"
		"\naamix=%g"
		"\nznear=%g"
		"\nzfar=%g",
		CAM->position[0], CAM->position[1], CAM->position[2],
		CAM->direction[0], CAM->direction[1], CAM->direction[2],
		CAM->up[0], CAM->up[1], CAM->up[2],
		CAM->angle,
		CAM->aspect,
		CAM->aamix,
		CAM->znear,
		CAM->zfar
	);
	sgs_PushString( C, "SS3D_Camera\n{" );
	sgs_PushString( C, bfr );
	sgs_PadString( C );
	sgs_PushString( C, "\n}" );
	sgs_StringMultiConcat( C, 3 );
	return SGS_SUCCESS;
}

sgs_ObjCallback SS3D_Camera_iface[9] =
{
	SGS_OP_GETINDEX, camera_getindex,
	SGS_OP_SETINDEX, camera_setindex,
	SGS_OP_CONVERT, camera_convert,
	SGS_OP_DUMP, camera_dump,
	SGS_OP_END
};

int SS3D_CreateCamera( SGS_CTX )
{
	SS3D_Camera* CAM = (SS3D_Camera*) sgs_PushObjectIPA( C, sizeof(*CAM), SS3D_Camera_iface );
	VEC3_Set( CAM->position, 0, 0, 0 );
	VEC3_Set( CAM->direction, 0, 1, 0 );
	VEC3_Set( CAM->up, 0, 0, 1 );
	CAM->angle = 90;
	CAM->aspect = 1;
	CAM->aamix = 0.5;
	CAM->znear = 1;
	CAM->zfar = 1000;
	
	camera_recalc_viewmtx( CAM );
	camera_recalc_projmtx( CAM );
	
	return 1;
}


//
// LIGHT

#define L_HDR SS3D_Light* L = (SS3D_Light*) data->data;

static int light_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	L_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" )          SGS_RETURN_INT( L->type )
		SGS_CASE( "isEnabled" )     SGS_RETURN_BOOL( L->isEnabled )
		SGS_CASE( "position" )      SGS_RETURN_VEC3( L->position )
		SGS_CASE( "direction" )     SGS_RETURN_VEC3( L->direction )
		SGS_CASE( "color" )         SGS_RETURN_VEC3( L->color )
		SGS_CASE( "range" )         SGS_RETURN_REAL( L->range )
		SGS_CASE( "power" )         SGS_RETURN_REAL( L->power )
		SGS_CASE( "minangle" )      SGS_RETURN_REAL( L->minangle )
		SGS_CASE( "maxangle" )      SGS_RETURN_REAL( L->maxangle )
		SGS_CASE( "cookieTexture" ) SGS_RETURN_OBJECT( L->cookieTexture )
		SGS_CASE( "projMatrix" )    SGS_RETURN_MAT4( *L->projMatrix )
		SGS_CASE( "hasShadows" )    SGS_RETURN_BOOL( L->hasShadows )
	SGS_END_INDEXFUNC;
}

static int light_setindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	L_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "type" )          SGS_PARSE_INT( L->type )
		SGS_CASE( "isEnabled" )     SGS_PARSE_BOOL( L->isEnabled )
		SGS_CASE( "position" )      SGS_PARSE_VEC3( L->position, 0 )
		SGS_CASE( "direction" )     SGS_PARSE_VEC3( L->direction, 0 )
		SGS_CASE( "color" )         SGS_PARSE_VEC3( L->color, 0 )
		SGS_CASE( "range" )         SGS_PARSE_REAL( L->range )
		SGS_CASE( "power" )         SGS_PARSE_REAL( L->power )
		SGS_CASE( "minangle" )      SGS_PARSE_REAL( L->minangle )
		SGS_CASE( "maxangle" )      SGS_PARSE_REAL( L->maxangle )
		SGS_CASE( "cookieTexture" ) { if( !L->scene || !L->scene->renderer ) return SGS_EINPROC; SGS_PARSE_OBJECT( L->scene->renderer->ifTexture, L->cookieTexture, 0 ) }
		SGS_CASE( "projMatrix" )    SGS_PARSE_MAT4( *L->projMatrix )
		SGS_CASE( "hasShadows" )    SGS_PARSE_BOOL( L->hasShadows )
	SGS_END_INDEXFUNC;
}

static int light_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	L_HDR;
	if( type == SGS_VT_STRING )
	{
		char bfr[ 32 ];
		sprintf( bfr, "SS3D_Light (%.10s)", L->scene && L->scene->renderer ? L->scene->renderer->API : "unloaded" );
		sgs_PushString( C, bfr );
		return SGS_SUCCESS;
	}
	else if( type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "SS3D_Light" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int light_dump( SGS_CTX, sgs_VarObj* data, int maxdepth )
{
	char bfr[ 2048 ];
	L_HDR;
	UNUSED( maxdepth );
	
	sprintf( bfr,
		"\ntype=%d"
		"\nisEnabled=%s"
		"\nposition=(%g;%g;%g)"
		"\ndirection=(%g;%g;%g)"
		"\ncolor=(%g;%g;%g)"
		"\nrange=%g"
		"\npower=%g"
		"\nminangle=%g"
		"\nmaxangle=%g"
		"\ncookieTexture=%p"
		"\nprojMatrix=..."
		"\nhasShadows=%s",
		L->type,
		L->isEnabled ? "true" : "false",
		L->position[0], L->position[1], L->position[2],
		L->direction[0], L->direction[1], L->direction[2],
		L->color[0], L->color[1], L->color[2],
		L->range,
		L->power,
		L->minangle,
		L->maxangle,
		L->cookieTexture,
		// projMatrix ...
		L->hasShadows ? "true" : "false"
	);
	sgs_PushString( C, "SS3D_Light\n{" );
	sgs_PushString( C, bfr );
	sgs_PadString( C );
	sgs_PushString( C, "\n}" );
	sgs_StringMultiConcat( C, 3 );
	return SGS_SUCCESS;
}

static int light_gcmark( SGS_CTX, sgs_VarObj* data, int unused )
{
	L_HDR;
	if( L->cookieTexture )
		sgs_ObjGCMark( C, L->cookieTexture );
	return SGS_SUCCESS;
}

static int light_destruct( SGS_CTX, sgs_VarObj* data, int unused )
{
	L_HDR;
	UNUSED( unused );
	if( L->scene )
	{
		scene_poke_resource( L->scene, &L->scene->lights, data, 0 );
		L->scene = NULL;
		if( L->cookieTexture )
		{
			sgs_ObjRelease( C, L->cookieTexture );
			L->cookieTexture = NULL;
		}
	}
	return SGS_SUCCESS;
}

sgs_ObjCallback SS3D_Light_iface[13] =
{
	SGS_OP_GETINDEX, light_getindex,
	SGS_OP_SETINDEX, light_setindex,
	SGS_OP_CONVERT, light_convert,
	SGS_OP_DESTRUCT, light_destruct,
	SGS_OP_GCMARK, light_gcmark,
	SGS_OP_DUMP, light_dump,
	SGS_OP_END
};


//
// SCENE

#define SC_HDR SS3D_Scene* S = (SS3D_Scene*) data->data;
#define SC_IHDR( funcname ) \
	int method_call = sgs_Method( C ); \
	sgs_FuncName( C, method_call ? "SS3D_Scene." #funcname : "SS3D_Scene_" #funcname ); \
	if( !sgs_IsObject( C, 0, SS3D_Scene_iface ) ) \
		return sgs_ArgErrorExt( C, 0, method_call, "SS3D_Scene", "" ); \
	SS3D_Scene* S = (SS3D_Scene*) sgs_GetObjectData( C, 0 ); UNUSED( S );

static int scenei_createMeshInstance( SGS_CTX )
{
	SC_IHDR( createMeshInstance );
	return 0;
}

static int scenei_destroyMeshInstance( SGS_CTX )
{
	SC_IHDR( destroyMeshInstance );
	return 0;
}

static int scenei_createLight( SGS_CTX )
{
	SS3D_Light* L;
	SC_IHDR( createLight );
	L = (SS3D_Light*) sgs_PushObjectIPA( C, sizeof(*L), SS3D_Light_iface );
	memset( L, 0, sizeof(*L) );
	L->scene = S;
	scene_poke_resource( S, &S->lights, sgs_GetObjectStruct( C, -1 ), 1 );
	return 1;
}

static int scenei_destroyLight( SGS_CTX )
{
	SC_IHDR( destroyLight );
	if( !sgs_LoadArgs( C, "@>?o", SS3D_Light_iface ) )
		return 0;
	
	SS3D_CallDtor( C, sgs_GetObjectStruct( C, 1 ) );
	return 0;
}

static int scene_getindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	SC_HDR;
	SGS_BEGIN_INDEXFUNC
		// methods
		SGS_CASE( "createMeshInstance" )  SGS_RETURN_CFUNC( scenei_createMeshInstance )
		SGS_CASE( "destroyMeshInstance" ) SGS_RETURN_CFUNC( scenei_destroyMeshInstance )
		SGS_CASE( "createLight" )         SGS_RETURN_CFUNC( scenei_createLight )
		SGS_CASE( "destroyLight" )        SGS_RETURN_CFUNC( scenei_destroyLight )
		
		// properties
		SGS_CASE( "camera" )    SGS_RETURN_OBJECT( S->camera )
		SGS_CASE( "cullScene" ) SGS_RETURN_OBJECT( S->cullScene )
	SGS_END_INDEXFUNC;
}

static int scene_setindex( SGS_CTX, sgs_VarObj* data, int isprop )
{
	char* str;
	SC_HDR;
	UNUSED( isprop );
	if( sgs_ParseString( C, 0, &str, NULL ) )
	{
		if( !strcmp( str, "cullScene" ) )
		{
			if( sgs_ItemType( C, 1 ) == SGS_VT_NULL )
			{
				if( S->cullScene )
					sgs_ObjRelease( C, S->cullScene );
				S->cullScene = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObject( C, 1, SS3D_CullScene_iface ) )
			{
				if( S->cullScene )
					sgs_ObjRelease( C, S->cullScene );
				S->cullScene = sgs_GetObjectStruct( C, 1 );
				sgs_ObjAcquire( C, S->cullScene );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		if( !strcmp( str, "camera" ) )
		{
			if( sgs_ItemType( C, 1 ) == SGS_VT_NULL )
			{
				if( S->camera )
					sgs_ObjRelease( C, S->camera );
				S->camera = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObject( C, 1, SS3D_Camera_iface ) )
			{
				if( S->camera )
					sgs_ObjRelease( C, S->camera );
				S->camera = sgs_GetObjectStruct( C, 1 );
				sgs_ObjAcquire( C, S->camera );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
	}
	return SGS_ENOTFND;
}

static int scene_convert( SGS_CTX, sgs_VarObj* data, int type )
{
	SC_HDR;
	if( type == SGS_VT_STRING )
	{
		char bfr[ 32 ];
		sprintf( bfr, "SS3D_Scene (%.10s)", S->renderer ? S->renderer->API : "unloaded" );
		sgs_PushString( C, bfr );
		return SGS_SUCCESS;
	}
	else if( type == SGS_CONVOP_TOTYPE )
	{
		sgs_PushString( C, "SS3D_Scene" );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int scene_destruct( SGS_CTX, sgs_VarObj* data, int unused )
{
	sgs_SizeVal i;
	SC_HDR;
	UNUSED( unused );
	if( S->renderer )
	{
		SS3D_Renderer_PokeResource( S->renderer, data, 0 );
		S->renderer = NULL;
		S->destroying = 1;
		for( i = 0; i < S->meshInstances.size; ++i )
		{
			sgs_VarObj* obj = (sgs_VarObj*) S->meshInstances.vars[ i ].val.data.P;
			SS3D_CallDtor( C, obj );
		}
		for( i = 0; i < S->lights.size; ++i )
		{
			sgs_VarObj* obj = (sgs_VarObj*) S->lights.vars[ i ].val.data.P;
			SS3D_CallDtor( C, obj );
		}
		sgs_vht_free( &S->meshInstances, C );
		sgs_vht_free( &S->lights, C );
		if( S->cullScene )
		{
			sgs_ObjRelease( C, S->cullScene );
			S->cullScene = NULL;
		}
	}
	return SGS_SUCCESS;
}

sgs_ObjCallback SS3D_Scene_iface[9] =
{
	SGS_OP_GETINDEX, scene_getindex,
	SGS_OP_SETINDEX, scene_setindex,
	SGS_OP_CONVERT, scene_convert,
	SGS_OP_DESTRUCT, scene_destruct,
	SGS_OP_END
};


//
// RENDERER

void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX )
{
	memset( R, 0, sizeof(*R) );
	R->C = C;
	R->destroying = 0;
	sgs_vht_init( &R->resources, C, 128, 128 );
	sgs_vht_init( &R->shaders, C, 128, 128 );
	sgs_vht_init( &R->materials, C, 128, 128 );
	R->currentScene = NULL;
	R->enableDeferredShading = 0;
}

void SS3D_Renderer_Destruct( SS3D_Renderer* R )
{
	sgs_SizeVal i;
	R->destroying = 1;
	for( i = 0; i < R->resources.size; ++i )
	{
		sgs_VarObj* obj = (sgs_VarObj*) R->resources.vars[ i ].val.data.P;
		SS3D_CallDtor( R->C, obj );
	}
	sgs_vht_free( &R->resources, R->C );
	sgs_vht_free( &R->shaders, R->C );
	sgs_vht_free( &R->materials, R->C );
	if( R->currentScene )
		sgs_ObjRelease( R->C, R->currentScene );
}

void SS3D_Renderer_Update( SS3D_Renderer* R, float dt )
{
}

void SS3D_Renderer_Resize( SS3D_Renderer* R, int w, int h )
{
	R->width = w;
	R->height = h;
}

void SS3D_Renderer_PokeResource( SS3D_Renderer* R, sgs_VarObj* obj, int add )
{
	sgs_Variable K;
	if( R->destroying )
		return;
	
	K.type = SGS_VT_PTR;
	K.data.P = obj;
	if( add )
		sgs_vht_set( &R->resources, R->C, &K, &K );
	else
		sgs_vht_unset( &R->resources, R->C, &K );
}

void SS3D_Renderer_PushScene( SS3D_Renderer* R )
{
	SS3D_Scene* S = (SS3D_Scene*) sgs_PushObjectIPA( R->C, sizeof(*S), SS3D_Scene_iface );
	S->renderer = R;
	S->destroying = 0;
	sgs_vht_init( &S->meshInstances, R->C, 128, 128 );
	sgs_vht_init( &S->lights, R->C, 128, 128 );
	S->camera = NULL;
	S->cullScene = NULL;
	SS3D_Renderer_PokeResource( R, sgs_GetObjectStruct( R->C, -1 ), 1 );
}


static int SS3D_CreateRenderer( SGS_CTX )
{
	char* rendererType;
	sgs_Int version = 0;
	void* device = NULL;
	
	SGSFN( "SS3D_CreateRenderer" );
	if( !sgs_LoadArgs( C, "s|i&", &rendererType, &version, &device ) )
		return 0;
	
	if( !strcmp( rendererType, "D3D9" ) && !device )
		return sgs_Printf( C, SGS_WARNING, "Direct3D requires a device pointer (argument 3)" );
	
	if( !strcmp( rendererType, "D3D9" ) )
		return SS3D_PushRenderer_D3D9( C, device );
	else if( !strcmp( rendererType, "GL" ) )
		return SS3D_PushRenderer_GL( C, version );
	else
		return sgs_Printf( C, SGS_WARNING, "unsupported renderer type" );
}


static sgs_RegFuncConst ss3d_fconsts[] =
{
	FN( CreateCamera ),
	FN( CreateRenderer ),
};

static sgs_RegIntConst ss3d_iconsts[] =
{
	CN( LIGHT_POINT ), CN( LIGHT_DIRECT ), CN( LIGHT_SPOT ),
};


SGS_APIFUNC int sgscript_main( SGS_CTX )
{
	sgs_RegFuncConsts( C, ss3d_fconsts, sizeof(ss3d_fconsts) / sizeof(ss3d_fconsts[0]) );
	sgs_RegIntConsts( C, ss3d_iconsts, sizeof(ss3d_iconsts) / sizeof(ss3d_iconsts[0]) );
	if( !sgs_Include( C, "ss3d/engine" ) )
		return SGS_EINPROC;
	return SGS_SUCCESS;
}

