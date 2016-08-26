// SGS/CPP-BC
// warning: do not modify this file, it may be regenerated during any build

#include "sa_main.hpp"

static int _sgs_method__SGAudioEmitter__play( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, play ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->play(  ); return 0;
}

static int _sgs_method__SGAudioEmitter__stop( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, stop ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->stop(  ); return 0;
}

static int _sgs_method__SGAudioEmitter__pause( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, pause ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->pause(  ); return 0;
}

static int _sgs_method__SGAudioEmitter__load( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, load ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->load( sgs_GetVar<sgsString>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioEmitter__unload( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, unload ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->unload(  )); return 1;
}

static int _sgs_method__SGAudioEmitter__fade_volume( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, fade_volume ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->fade_volume( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1) ); return 0;
}

static int _sgs_method__SGAudioEmitter__set_position( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, set_position ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->set_position( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1), sgs_GetVar<float>()(C,2) ); return 0;
}

int SGAudioEmitter::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SGAudioEmitter*>( obj->data )->C = C;
	static_cast<SGAudioEmitter*>( obj->data )->~SGAudioEmitter();
	return SGS_SUCCESS;
}

int SGAudioEmitter::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioEmitter*>( obj->data )->C, C );
	sgs_GCMarkVar( C, static_cast<SGAudioEmitter*>( obj->data )->System );
	return SGS_SUCCESS;
}

int SGAudioEmitter::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioEmitter*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "playing" ){ sgs_PushVar( C, static_cast<SGAudioEmitter*>( obj->data )->_get_playing() ); return SGS_SUCCESS; }
		SGS_CASE( "loop" ){ sgs_PushVar( C, static_cast<SGAudioEmitter*>( obj->data )->_get_loop() ); return SGS_SUCCESS; }
		SGS_CASE( "volume" ){ sgs_PushVar( C, static_cast<SGAudioEmitter*>( obj->data )->_get_volume() ); return SGS_SUCCESS; }
		SGS_CASE( "pitch" ){ sgs_PushVar( C, static_cast<SGAudioEmitter*>( obj->data )->_get_pitch() ); return SGS_SUCCESS; }
		SGS_CASE( "groups" ){ sgs_PushVar( C, static_cast<SGAudioEmitter*>( obj->data )->_get_groups() ); return SGS_SUCCESS; }
		SGS_CASE( "offset" ){ sgs_PushVar( C, static_cast<SGAudioEmitter*>( obj->data )->_get_offset() ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioEmitter::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioEmitter*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "loop" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_loop( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "volume" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_volume( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "pitch" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_pitch( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "groups" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_groups( sgs_GetVar<int>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "offset" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_offset( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "mode3d" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_mode3d( sgs_GetVar<bool>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "panning" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_panning( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
		SGS_CASE( "factor" ){ static_cast<SGAudioEmitter*>( obj->data )->_set_factor( sgs_GetVar<float>()( C, 1 ) ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioEmitter::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioEmitter*>( obj->data )->C, C );
	char bfr[ 46 ];
	sprintf( bfr, "SGAudioEmitter (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nplaying = " ); sgs_DumpData( C, static_cast<SGAudioEmitter*>( obj->data )->_get_playing(), depth ).push( C ); }
		{ sgs_PushString( C, "\nloop = " ); sgs_DumpData( C, static_cast<SGAudioEmitter*>( obj->data )->_get_loop(), depth ).push( C ); }
		{ sgs_PushString( C, "\nvolume = " ); sgs_DumpData( C, static_cast<SGAudioEmitter*>( obj->data )->_get_volume(), depth ).push( C ); }
		{ sgs_PushString( C, "\npitch = " ); sgs_DumpData( C, static_cast<SGAudioEmitter*>( obj->data )->_get_pitch(), depth ).push( C ); }
		{ sgs_PushString( C, "\ngroups = " ); sgs_DumpData( C, static_cast<SGAudioEmitter*>( obj->data )->_get_groups(), depth ).push( C ); }
		{ sgs_PushString( C, "\noffset = " ); sgs_DumpData( C, static_cast<SGAudioEmitter*>( obj->data )->_get_offset(), depth ).push( C ); }
		sgs_StringConcat( C, 12 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst SGAudioEmitter__sgs_funcs[] =
{
	{ "play", _sgs_method__SGAudioEmitter__play },
	{ "stop", _sgs_method__SGAudioEmitter__stop },
	{ "pause", _sgs_method__SGAudioEmitter__pause },
	{ "load", _sgs_method__SGAudioEmitter__load },
	{ "unload", _sgs_method__SGAudioEmitter__unload },
	{ "fade_volume", _sgs_method__SGAudioEmitter__fade_volume },
	{ "set_position", _sgs_method__SGAudioEmitter__set_position },
	{ NULL, NULL },
};

static int SGAudioEmitter__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SGAudioEmitter__sgs_funcs,
		-1, "SGAudioEmitter." );
	return 1;
}

static sgs_ObjInterface SGAudioEmitter__sgs_interface =
{
	"SGAudioEmitter",
	SGAudioEmitter::_sgs_destruct, SGAudioEmitter::_sgs_gcmark, SGAudioEmitter::_sgs_getindex, SGAudioEmitter::_sgs_setindex, NULL, NULL, SGAudioEmitter::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SGAudioEmitter::_sgs_interface(SGAudioEmitter__sgs_interface, SGAudioEmitter__sgs_ifn);


static int _sgs_method__SGAudioSystem__set_volume( SGS_CTX )
{
	SGAudioSystem* data; if( !SGS_PARSE_METHOD( C, SGAudioSystem::_sgs_interface, data, SGAudioSystem, set_volume ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->set_volume( sgs_GetVar<float>()(C,0), sgs_GetVar<int>()(C,1) ); return 0;
}

static int _sgs_method__SGAudioSystem__get_volume( SGS_CTX )
{
	SGAudioSystem* data; if( !SGS_PARSE_METHOD( C, SGAudioSystem::_sgs_interface, data, SGAudioSystem, get_volume ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->get_volume( sgs_GetVar<int>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioSystem__set_listener_position( SGS_CTX )
{
	SGAudioSystem* data; if( !SGS_PARSE_METHOD( C, SGAudioSystem::_sgs_interface, data, SGAudioSystem, set_listener_position ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->set_listener_position( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1), sgs_GetVar<float>()(C,2) ); return 0;
}

static int _sgs_method__SGAudioSystem__set_listener_orientation( SGS_CTX )
{
	SGAudioSystem* data; if( !SGS_PARSE_METHOD( C, SGAudioSystem::_sgs_interface, data, SGAudioSystem, set_listener_orientation ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->set_listener_orientation( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1), sgs_GetVar<float>()(C,2), sgs_GetVar<float>()(C,3), sgs_GetVar<float>()(C,4), sgs_GetVar<float>()(C,5) ); return 0;
}

static int _sgs_method__SGAudioSystem__suspend( SGS_CTX )
{
	SGAudioSystem* data; if( !SGS_PARSE_METHOD( C, SGAudioSystem::_sgs_interface, data, SGAudioSystem, suspend ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->suspend(  ); return 0;
}

static int _sgs_method__SGAudioSystem__resume( SGS_CTX )
{
	SGAudioSystem* data; if( !SGS_PARSE_METHOD( C, SGAudioSystem::_sgs_interface, data, SGAudioSystem, resume ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	data->resume(  ); return 0;
}

static int _sgs_method__SGAudioSystem__create_emitter( SGS_CTX )
{
	SGAudioSystem* data; if( !SGS_PARSE_METHOD( C, SGAudioSystem::_sgs_interface, data, SGAudioSystem, create_emitter ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->create_emitter( sgs_GetVar<sgsString>()(C,0) );
}

int SGAudioSystem::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SGAudioSystem*>( obj->data )->C = C;
	static_cast<SGAudioSystem*>( obj->data )->~SGAudioSystem();
	return SGS_SUCCESS;
}

int SGAudioSystem::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioSystem*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int SGAudioSystem::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioSystem*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SGAudioSystem::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioSystem*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SGAudioSystem::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioSystem*>( obj->data )->C, C );
	char bfr[ 45 ];
	sprintf( bfr, "SGAudioSystem (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
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

static sgs_RegFuncConst SGAudioSystem__sgs_funcs[] =
{
	{ "set_volume", _sgs_method__SGAudioSystem__set_volume },
	{ "get_volume", _sgs_method__SGAudioSystem__get_volume },
	{ "set_listener_position", _sgs_method__SGAudioSystem__set_listener_position },
	{ "set_listener_orientation", _sgs_method__SGAudioSystem__set_listener_orientation },
	{ "suspend", _sgs_method__SGAudioSystem__suspend },
	{ "resume", _sgs_method__SGAudioSystem__resume },
	{ "create_emitter", _sgs_method__SGAudioSystem__create_emitter },
	{ NULL, NULL },
};

static int SGAudioSystem__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SGAudioSystem__sgs_funcs,
		-1, "SGAudioSystem." );
	return 1;
}

static sgs_ObjInterface SGAudioSystem__sgs_interface =
{
	"SGAudioSystem",
	SGAudioSystem::_sgs_destruct, SGAudioSystem::_sgs_gcmark, SGAudioSystem::_sgs_getindex, SGAudioSystem::_sgs_setindex, NULL, NULL, SGAudioSystem::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SGAudioSystem::_sgs_interface(SGAudioSystem__sgs_interface, SGAudioSystem__sgs_ifn);

