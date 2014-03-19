

#include "lodepng.h"

#include "ss3d_engine.h"

#define FN( x ) { "SS3D_" #x, SS3D_##x }
#define CN( x ) { "SS3D" #x, SS3D##x }


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

static void scene_poke_resource( SS3D_Scene* S, sgs_VHTable* which, sgs_VarObj* obj, int add )
{
	sgs_Variable K;
	
	if( !S->renderer || S->destroying )
		return;
	
	sgs_InitPtr( &K, obj );
	if( add )
		sgs_vht_set( &S->lights, S->renderer->C, &K, &K );
	else
		sgs_vht_unset( &S->lights, S->renderer->C, &K );
}


//
// TEXTURE

static size_t divideup( size_t x, int d )
{
	return x / d + ( x % d ? 1 : 0 );
}

size_t SS3D_TextureInfo_GetTextureSideSize( SS3D_TextureInfo* TI )
{
	size_t width = TI->width, height = TI->height, depth = TI->depth;
	int bpu = 0;
	switch( TI->format )
	{
	/* bytes per pixel */
	case SS3DFORMAT_RGBA8: bpu = 4; break;
	case SS3DFORMAT_R5G6B5: bpu = 2; break;
	/* bytes per block */
	case SS3DFORMAT_DXT1: bpu = 8; break;
	case SS3DFORMAT_DXT3:
	case SS3DFORMAT_DXT5: bpu = 16; break;
	}
	if( SS3DFORMAT_ISBLOCK4FORMAT( TI->format ) )
	{
		width = divideup( width, 4 );
		height = divideup( height, 4 );
		depth = divideup( depth, 4 );
	}
	switch( TI->type )
	{
	case SS3DTEXTURE_2D: return width * height * bpu;
	case SS3DTEXTURE_CUBE: return width * width * bpu;
	case SS3DTEXTURE_VOLUME: return width * height * depth * bpu;
	}
	return 0;
}

void SS3D_TextureInfo_GetCopyDims( SS3D_TextureInfo* TI, size_t* outcopyrowsize, size_t* outcopyrowcount )
{
	size_t width = TI->width, height = TI->height, depth = TI->depth;
	int bpu = 0;
	switch( TI->format )
	{
	/* bytes per pixel */
	case SS3DFORMAT_RGBA8: bpu = 4; break;
	case SS3DFORMAT_R5G6B5: bpu = 2; break;
	/* bytes per block */
	case SS3DFORMAT_DXT1: bpu = 8; break;
	case SS3DFORMAT_DXT3:
	case SS3DFORMAT_DXT5: bpu = 16; break;
	}
	if( SS3DFORMAT_ISBLOCK4FORMAT( TI->format ) )
	{
		width = divideup( width, 4 );
		height = divideup( height, 4 );
		depth = divideup( depth, 4 );
	}
	switch( TI->type )
	{
	case SS3DTEXTURE_2D: *outcopyrowsize = width * bpu; *outcopyrowcount = height; break;
	case SS3DTEXTURE_CUBE: *outcopyrowsize = width * bpu; *outcopyrowcount = width; break;
	case SS3DTEXTURE_VOLUME: *outcopyrowsize = width * bpu; *outcopyrowcount = height * depth; break;
	default: *outcopyrowsize = 0; *outcopyrowcount = 0; break;
	}
}

SGSBOOL SS3D_TextureInfo_GetMipInfo( SS3D_TextureInfo* TI, int mip, SS3D_TextureInfo* outinfo )
{
	SS3D_TextureInfo info = *TI;
	if( mip >= TI->mipcount )
		return 0;
	info.width /= pow( 2, mip ); if( info.width < 1 ) info.width = 1;
	info.height /= pow( 2, mip ); if( info.height < 1 ) info.height = 1;
	info.depth /= pow( 2, mip ); if( info.depth < 1 ) info.depth = 1;
	info.mipcount -= mip;
	*outinfo = info;
	return 1;
}

SGSRESULT SS3D_TextureData_LoadFromFile( SS3D_TextureData* TD, const char* file )
{
	unsigned char* out;
	unsigned w, h;
	int err;
	
	memset( TD, 0, sizeof(*TD) );
	
	// Try to load PNG
	err = lodepng_decode32_file( &out, &w, &h, file );
	if( err == 78 ) return SGS_ENOTFND;
	if( err == 0 )
	{
		TD->info.type = SS3DTEXTURE_2D;
		TD->info.width = w;
		TD->info.height = h;
		TD->info.depth = 1;
		TD->info.format = SS3DFORMAT_RGBA8;
		TD->info.flags = 0;
		TD->info.mipcount = 1;
		goto success;
	}
	
	// type not supported
	goto failure;
	
success:
	TD->data = out;
	return SGS_SUCCESS;
failure:
	return SGS_ENOTSUP;
}

void SS3D_TextureData_Free( SS3D_TextureData* TD )
{
	if( TD->data )
		free( TD->data );
}

size_t SS3D_TextureData_GetMipDataOffset( SS3D_TextureData* TD, int side, int mip )
{
	size_t off = 0;
	int mipit = mip, numsides = TD->info.type == SS3DTEXTURE_CUBE ? 6 : 1;
	while( mipit --> 0 )
		off += SS3D_TextureData_GetMipDataSize( TD, mipit ) * numsides;
	if( side && TD->info.type == SS3DTEXTURE_CUBE )
	{
		size_t curlev = SS3D_TextureData_GetMipDataSize( TD, mip );
		off += curlev * side;
	}
	return off;
}

size_t SS3D_TextureData_GetMipDataSize( SS3D_TextureData* TD, int mip )
{
	SS3D_TextureInfo mipTI;
	if( !SS3D_TextureInfo_GetMipInfo( &TD->info, mip, &mipTI ) )
		return 0;
	return SS3D_TextureInfo_GetTextureSideSize( &mipTI );
}


//
// LIGHT

#define L_HDR SS3D_Light* L = (SS3D_Light*) obj->data;

static int light_getindex( SGS_ARGS_GETINDEXFUNC )
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

static int light_setindex( SGS_ARGS_SETINDEXFUNC )
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

static int light_convert( SGS_CTX, sgs_VarObj* obj, int type )
{
	L_HDR;
	if( type == SGS_VT_STRING )
	{
		char bfr[ 32 ];
		sprintf( bfr, "SS3D_Light (%.10s)", L->scene && L->scene->renderer ? L->scene->renderer->API : "unloaded" );
		sgs_PushString( C, bfr );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int light_dump( SGS_CTX, sgs_VarObj* obj, int maxdepth )
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
	sgs_StringConcat( C, 3 );
	return SGS_SUCCESS;
}

static int light_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	L_HDR;
	if( L->cookieTexture )
		sgs_ObjGCMark( C, L->cookieTexture );
	return SGS_SUCCESS;
}

static int light_destruct( SGS_CTX, sgs_VarObj* obj )
{
	L_HDR;
	if( L->scene )
	{
		scene_poke_resource( L->scene, &L->scene->lights, obj, 0 );
		L->scene = NULL;
		if( L->cookieTexture )
		{
			sgs_ObjRelease( C, L->cookieTexture );
			L->cookieTexture = NULL;
		}
	}
	return SGS_SUCCESS;
}

sgs_ObjInterface SS3D_Light_iface[1] =
{{
	"SS3D_Light",
	light_destruct, light_gcmark,
	light_getindex, light_setindex,
	light_convert, NULL, light_dump, NULL,
	NULL, NULL
}};


//
// CULL SCENE

sgs_ObjInterface SS3D_CullScene_iface[1] =
{{
	"SS3D_CullScene",
	NULL, NULL,
	NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL,
}};


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

#define CAM_HDR SS3D_Camera* CAM = (SS3D_Camera*) obj->data;

static int camera_getindex( SGS_ARGS_GETINDEXFUNC )
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

static int camera_setindex_( SGS_ARGS_SETINDEXFUNC )
{
	CAM_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "position" )  { return sgs_ParseVec3P( C, val, CAM->position, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "direction" ) { return sgs_ParseVec3P( C, val, CAM->direction, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "up" )        { return sgs_ParseVec3P( C, val, CAM->up, 0 ) ? 1 : SGS_EINVAL; }
		SGS_CASE( "angle" )     { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->angle = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "aspect" )    { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->aspect = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "aamix" )     { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->aamix = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "znear" )     { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->znear = V; return 2; } return SGS_EINVAL; }
		SGS_CASE( "zfar" )      { sgs_Real V; if( sgs_ParseRealP( C, val, &V ) ){ CAM->zfar = V; return 2; } return SGS_EINVAL; }
	SGS_END_INDEXFUNC;
}

static int camera_setindex( SGS_ARGS_SETINDEXFUNC )
{
	CAM_HDR;
	int ret = camera_setindex_( C, obj, key, val, isprop );
	if( ret < 0 )
		return ret;
	if( ret == 1 ) camera_recalc_viewmtx( CAM );
	if( ret == 2 ) camera_recalc_projmtx( CAM );
	return SGS_SUCCESS;
}

static int camera_dump( SGS_CTX, sgs_VarObj* obj, int maxdepth )
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
	sgs_StringConcat( C, 3 );
	return SGS_SUCCESS;
}

sgs_ObjInterface SS3D_Camera_iface[1] =
{{
	"SS3D_Camera",
	NULL, NULL,
	camera_getindex, camera_setindex,
	NULL, NULL, camera_dump, NULL,
	NULL, NULL,
}};

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
// VIEWPORT

#define VP_HDR SS3D_Viewport* VP = (SS3D_Viewport*) obj->data;

static int viewport_getindex( SGS_ARGS_GETINDEXFUNC )
{
	VP_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "x1" )  SGS_RETURN_INT( VP->x1 )
		SGS_CASE( "y1" )  SGS_RETURN_INT( VP->y1 )
		SGS_CASE( "x2" )  SGS_RETURN_INT( VP->x2 )
		SGS_CASE( "y2" )  SGS_RETURN_INT( VP->y2 )
	SGS_END_INDEXFUNC;
}

static int viewport_setindex( SGS_ARGS_SETINDEXFUNC )
{
	VP_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "x1" )  SGS_PARSE_INT( VP->x1 )
		SGS_CASE( "y1" )  SGS_PARSE_INT( VP->y1 )
		SGS_CASE( "x2" )  SGS_PARSE_INT( VP->x2 )
		SGS_CASE( "y2" )  SGS_PARSE_INT( VP->y2 )
	SGS_END_INDEXFUNC;
}

static int viewport_dump( SGS_CTX, sgs_VarObj* obj, int maxdepth )
{
	char bfr[ 2048 ];
	VP_HDR;
	UNUSED( maxdepth );
	
	sprintf( bfr,
		"\nx1=%d"
		"\ny1=%d"
		"\nx2=%d"
		"\ny2=%d",
		VP->x1,
		VP->y1,
		VP->x2,
		VP->y2
	);
	sgs_PushString( C, "SS3D_Viewport\n{" );
	sgs_PushString( C, bfr );
	sgs_PadString( C );
	sgs_PushString( C, "\n}" );
	sgs_StringConcat( C, 3 );
	return SGS_SUCCESS;
}

sgs_ObjInterface SS3D_Viewport_iface[1] =
{{
	"SS3D_Viewport",
	NULL, NULL,
	viewport_getindex, viewport_setindex,
	NULL, NULL, viewport_dump, NULL,
	NULL, NULL,
}};

int SS3D_CreateViewport( SGS_CTX )
{
	SS3D_Viewport* VP = (SS3D_Viewport*) sgs_PushObjectIPA( C, sizeof(*VP), SS3D_Viewport_iface );
	VP->x1 = 0;
	VP->y1 = 0;
	VP->x2 = 100;
	VP->y2 = 100;
	
	return 1;
}


//
// SCENE

#define SC_HDR SS3D_Scene* S = (SS3D_Scene*) obj->data;
#define SC_IHDR( funcname ) SS3D_Scene* S; \
	if( !SGS_PARSE_METHOD( C, SS3D_Scene_iface, S, SS3D_Scene, funcname ) ) return 0;

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
	if( !sgs_LoadArgs( C, "?o", SS3D_Light_iface ) )
		return 0;
	
	sgs_ObjCallDtor( C, sgs_GetObjectStruct( C, 0 ) );
	return 0;
}

static int scene_getindex( SGS_ARGS_GETINDEXFUNC )
{
	SC_HDR;
	SGS_BEGIN_INDEXFUNC
		// methods
		SGS_CASE( "createMeshInstance" )  SGS_RETURN_CFUNC( scenei_createMeshInstance )
		SGS_CASE( "destroyMeshInstance" ) SGS_RETURN_CFUNC( scenei_destroyMeshInstance )
		SGS_CASE( "createLight" )         SGS_RETURN_CFUNC( scenei_createLight )
		SGS_CASE( "destroyLight" )        SGS_RETURN_CFUNC( scenei_destroyLight )
		
		// properties
		SGS_CASE( "cullScene" ) SGS_RETURN_OBJECT( S->cullScene )
		SGS_CASE( "camera" )    SGS_RETURN_OBJECT( S->camera )
		SGS_CASE( "viewport" )  SGS_RETURN_OBJECT( S->viewport )
	SGS_END_INDEXFUNC;
}

static int scene_setindex( SGS_ARGS_SETINDEXFUNC )
{
	SC_HDR;
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "cullScene" )
		{
			if( val->type == SGS_VT_NULL )
			{
				if( S->cullScene )
					sgs_ObjRelease( C, S->cullScene );
				S->cullScene = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObjectP( val, SS3D_CullScene_iface ) )
			{
				if( S->cullScene )
					sgs_ObjRelease( C, S->cullScene );
				S->cullScene = sgs_GetObjectStructP( val );
				sgs_ObjAcquire( C, S->cullScene );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		SGS_CASE( "camera" )
		{
			if( val->type == SGS_VT_NULL )
			{
				if( S->camera )
					sgs_ObjRelease( C, S->camera );
				S->camera = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObjectP( val, SS3D_Camera_iface ) )
			{
				if( S->camera )
					sgs_ObjRelease( C, S->camera );
				S->camera = sgs_GetObjectStructP( val );
				sgs_ObjAcquire( C, S->camera );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
		SGS_CASE( "viewport" )
		{
			if( val->type == SGS_VT_NULL )
			{
				if( S->viewport )
					sgs_ObjRelease( C, S->viewport );
				S->viewport = NULL;
				return SGS_SUCCESS;
			}
			if( sgs_IsObjectP( val, SS3D_Viewport_iface ) )
			{
				if( S->viewport )
					sgs_ObjRelease( C, S->viewport );
				S->viewport = sgs_GetObjectStructP( val );
				sgs_ObjAcquire( C, S->viewport );
				return SGS_SUCCESS;
			}
			return SGS_EINVAL;
		}
	SGS_END_INDEXFUNC;
}

static int scene_convert( SGS_CTX, sgs_VarObj* obj, int type )
{
	SC_HDR;
	if( type == SGS_VT_STRING )
	{
		char bfr[ 32 ];
		sprintf( bfr, "SS3D_Scene (%.10s)", S->renderer ? S->renderer->API : "unloaded" );
		sgs_PushString( C, bfr );
		return SGS_SUCCESS;
	}
	return SGS_ENOTSUP;
}

static int scene_destruct( SGS_CTX, sgs_VarObj* obj )
{
	sgs_SizeVal i;
	SC_HDR;
	if( S->renderer )
	{
		SS3D_Renderer_PokeResource( S->renderer, obj, 0 );
		S->renderer = NULL;
		S->destroying = 1;
		for( i = 0; i < S->meshInstances.size; ++i )
		{
			sgs_VarObj* obj = (sgs_VarObj*) S->meshInstances.vars[ i ].val.data.P;
			sgs_ObjCallDtor( C, obj );
		}
		for( i = 0; i < S->lights.size; ++i )
		{
			sgs_VarObj* obj = (sgs_VarObj*) S->lights.vars[ i ].val.data.P;
			sgs_ObjCallDtor( C, obj );
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

sgs_ObjInterface SS3D_Scene_iface[1] =
{{
	"SS3D_Scene",
	scene_destruct, NULL,
	scene_getindex, scene_setindex,
	scene_convert, NULL, NULL, NULL,
	NULL, NULL
}};


//
// RENDERER

void SS3D_Renderer_Construct( SS3D_Renderer* R, SGS_CTX )
{
	memset( R, 0, sizeof(*R) );
	R->C = C;
	R->destroying = 0;
	sgs_vht_init( &R->resources, C, 128, 128 );
	sgs_vht_init( &R->shaders, C, 128, 128 );
	sgs_vht_init( &R->textures, C, 128, 128 );
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
		sgs_ObjCallDtor( R->C, obj );
	}
	sgs_vht_free( &R->resources, R->C );
	sgs_vht_free( &R->shaders, R->C );
	sgs_vht_free( &R->textures, R->C );
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
	S->viewport = NULL;
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
		return sgs_Msg( C, SGS_WARNING, "Direct3D requires a device pointer (argument 3)" );
	
	if( !strcmp( rendererType, "D3D9" ) )
		return SS3D_PushRenderer_D3D9( C, device );
	else if( !strcmp( rendererType, "GL" ) )
		return SS3D_PushRenderer_GL( C, version );
	else
		return sgs_Msg( C, SGS_WARNING, "unsupported renderer type" );
}


static sgs_RegFuncConst ss3d_fconsts[] =
{
	FN( CreateCamera ),
	FN( CreateViewport ),
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

