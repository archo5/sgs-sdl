// SGS/CPP-BC
// warning: do not modify this file, it may be regenerated during any build

#include "sa_main.hpp"

int SGAudioGenerator::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SGAudioGenerator*>( obj->data )->C = C;
	static_cast<SGAudioGenerator*>( obj->data )->~SGAudioGenerator();
	return SGS_SUCCESS;
}

int SGAudioGenerator::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenerator*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int SGAudioGenerator::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenerator*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SGAudioGenerator::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenerator*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SGAudioGenerator::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenerator*>( obj->data )->C, C );
	char bfr[ 48 ];
	sprintf( bfr, "SGAudioGenerator (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
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

static sgs_RegFuncConst SGAudioGenerator__sgs_funcs[] =
{
	{ NULL, NULL },
};

static int SGAudioGenerator__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SGAudioGenerator__sgs_funcs,
		-1, "SGAudioGenerator." );
	return 1;
}

static sgs_ObjInterface SGAudioGenerator__sgs_interface =
{
	"SGAudioGenerator",
	SGAudioGenerator::_sgs_destruct, SGAudioGenerator::_sgs_gcmark, SGAudioGenerator::_sgs_getindex, SGAudioGenerator::_sgs_setindex, NULL, NULL, SGAudioGenerator::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SGAudioGenerator::_sgs_interface(SGAudioGenerator__sgs_interface, SGAudioGenerator__sgs_ifn);


static int _sgs_method__SGAudioGenConstant__create( SGS_CTX )
{
	SGSFN( "SGAudioGenConstant.create" );
	sgs_PushVar(C,SGAudioGenConstant::create( C )); return 1;
}

int SGAudioGenConstant::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SGAudioGenConstant*>( obj->data )->C = C;
	static_cast<SGAudioGenConstant*>( obj->data )->~SGAudioGenConstant();
	return SGS_SUCCESS;
}

int SGAudioGenConstant::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenConstant*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int SGAudioGenConstant::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenConstant*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "value" ){ sgs_PushVar( C, static_cast<SGAudioGenConstant*>( obj->data )->value ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioGenConstant::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenConstant*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "value" ){ static_cast<SGAudioGenConstant*>( obj->data )->value = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioGenConstant::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenConstant*>( obj->data )->C, C );
	char bfr[ 50 ];
	sprintf( bfr, "SGAudioGenConstant (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nvalue = " ); sgs_DumpData( C, static_cast<SGAudioGenConstant*>( obj->data )->value, depth ).push( C ); }
		sgs_StringConcat( C, 2 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst SGAudioGenConstant__sgs_funcs[] =
{
	{ "create", _sgs_method__SGAudioGenConstant__create },
	{ NULL, NULL },
};

static int SGAudioGenConstant__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SGAudioGenConstant__sgs_funcs,
		-1, "SGAudioGenConstant." );
	return 1;
}

static sgs_ObjInterface SGAudioGenConstant__sgs_interface =
{
	"SGAudioGenConstant",
	SGAudioGenConstant::_sgs_destruct, SGAudioGenConstant::_sgs_gcmark, SGAudioGenConstant::_sgs_getindex, SGAudioGenConstant::_sgs_setindex, NULL, NULL, SGAudioGenConstant::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SGAudioGenConstant::_sgs_interface(SGAudioGenConstant__sgs_interface, SGAudioGenConstant__sgs_ifn, &SGAudioGenerator::_sgs_interface);


static int _sgs_method__SGAudioGenNoise__create( SGS_CTX )
{
	SGSFN( "SGAudioGenNoise.create" );
	sgs_PushVar(C,SGAudioGenNoise::create( C )); return 1;
}

int SGAudioGenNoise::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SGAudioGenNoise*>( obj->data )->C = C;
	static_cast<SGAudioGenNoise*>( obj->data )->~SGAudioGenNoise();
	return SGS_SUCCESS;
}

int SGAudioGenNoise::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenNoise*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int SGAudioGenNoise::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenNoise*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "power" ){ sgs_PushVar( C, static_cast<SGAudioGenNoise*>( obj->data )->power ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioGenNoise::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenNoise*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "power" ){ static_cast<SGAudioGenNoise*>( obj->data )->power = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioGenNoise::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenNoise*>( obj->data )->C, C );
	char bfr[ 47 ];
	sprintf( bfr, "SGAudioGenNoise (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\npower = " ); sgs_DumpData( C, static_cast<SGAudioGenNoise*>( obj->data )->power, depth ).push( C ); }
		sgs_StringConcat( C, 2 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst SGAudioGenNoise__sgs_funcs[] =
{
	{ "create", _sgs_method__SGAudioGenNoise__create },
	{ NULL, NULL },
};

static int SGAudioGenNoise__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SGAudioGenNoise__sgs_funcs,
		-1, "SGAudioGenNoise." );
	return 1;
}

static sgs_ObjInterface SGAudioGenNoise__sgs_interface =
{
	"SGAudioGenNoise",
	SGAudioGenNoise::_sgs_destruct, SGAudioGenNoise::_sgs_gcmark, SGAudioGenNoise::_sgs_getindex, SGAudioGenNoise::_sgs_setindex, NULL, NULL, SGAudioGenNoise::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SGAudioGenNoise::_sgs_interface(SGAudioGenNoise__sgs_interface, SGAudioGenNoise__sgs_ifn, &SGAudioGenerator::_sgs_interface);


static int _sgs_method__SGAudioGenScale__create( SGS_CTX )
{
	SGSFN( "SGAudioGenScale.create" );
	sgs_PushVar(C,SGAudioGenScale::create( C )); return 1;
}

int SGAudioGenScale::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SGAudioGenScale*>( obj->data )->C = C;
	static_cast<SGAudioGenScale*>( obj->data )->~SGAudioGenScale();
	return SGS_SUCCESS;
}

int SGAudioGenScale::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenScale*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int SGAudioGenScale::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenScale*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "gen" ){ sgs_PushVar( C, static_cast<SGAudioGenScale*>( obj->data )->gen ); return SGS_SUCCESS; }
		SGS_CASE( "value" ){ sgs_PushVar( C, static_cast<SGAudioGenScale*>( obj->data )->value ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioGenScale::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenScale*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "gen" ){ static_cast<SGAudioGenScale*>( obj->data )->gen = sgs_GetVar<Handle>()( C, 1 ); return SGS_SUCCESS; }
		SGS_CASE( "value" ){ static_cast<SGAudioGenScale*>( obj->data )->value = sgs_GetVar<float>()( C, 1 ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioGenScale::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioGenScale*>( obj->data )->C, C );
	char bfr[ 47 ];
	sprintf( bfr, "SGAudioGenScale (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\ngen = " ); sgs_DumpData( C, static_cast<SGAudioGenScale*>( obj->data )->gen, depth ).push( C ); }
		{ sgs_PushString( C, "\nvalue = " ); sgs_DumpData( C, static_cast<SGAudioGenScale*>( obj->data )->value, depth ).push( C ); }
		sgs_StringConcat( C, 4 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst SGAudioGenScale__sgs_funcs[] =
{
	{ "create", _sgs_method__SGAudioGenScale__create },
	{ NULL, NULL },
};

static int SGAudioGenScale__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SGAudioGenScale__sgs_funcs,
		-1, "SGAudioGenScale." );
	return 1;
}

static sgs_ObjInterface SGAudioGenScale__sgs_interface =
{
	"SGAudioGenScale",
	SGAudioGenScale::_sgs_destruct, SGAudioGenScale::_sgs_gcmark, SGAudioGenScale::_sgs_getindex, SGAudioGenScale::_sgs_setindex, NULL, NULL, SGAudioGenScale::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SGAudioGenScale::_sgs_interface(SGAudioGenScale__sgs_interface, SGAudioGenScale__sgs_ifn, &SGAudioGenerator::_sgs_interface);


static int _sgs_method__SGAudioBuffer__resize( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, resize ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->resize( sgs_GetVar<int>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__append( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, append ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->append( sgs_GetVar<SGAudioBuffer::Handle>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__set_sample_rate( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, set_sample_rate ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->set_sample_rate( sgs_GetVar<int>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__silence( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, silence ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->silence(  )); return 1;
}

static int _sgs_method__SGAudioBuffer__add_silence( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, add_silence ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->add_silence( sgs_GetVar<int>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__sine( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, sine ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->sine( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1), sgs_GetVar<float>()(C,2), sgs_GetVar<int>()(C,3) )); return 1;
}

static int _sgs_method__SGAudioBuffer__triangle( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, triangle ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->triangle( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1), sgs_GetVar<float>()(C,2), sgs_GetVar<int>()(C,3) )); return 1;
}

static int _sgs_method__SGAudioBuffer__saw( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, saw ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->saw( sgs_GetVar<float>()(C,0), sgs_GetVar<float>()(C,1), sgs_GetVar<float>()(C,2), sgs_GetVar<int>()(C,3) )); return 1;
}

static int _sgs_method__SGAudioBuffer__noise( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, noise ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->noise( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__scale( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, scale ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->scale( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__scaled( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, scaled ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	return data->scaled( sgs_GetVar<float>()(C,0) );
}

static int _sgs_method__SGAudioBuffer__lowpass( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, lowpass ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->lowpass( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__taper( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, taper ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->taper( sgs_GetVar<float>()(C,0) )); return 1;
}

static int _sgs_method__SGAudioBuffer__add_note( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, add_note ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->add_note( sgs_GetVar<SGAudioBuffer::Handle>()(C,0), sgs_GetVar<float>()(C,1), sgs_GetVar<float>()(C,2), sgs_GetVar<float>()(C,3), sgs_GetVar<float>()(C,4), sgs_GetVar<float>()(C,5), sgs_GetVar<float>()(C,6), sgs_GetVar<int>()(C,7) )); return 1;
}

static int _sgs_method__SGAudioBuffer__render( SGS_CTX )
{
	SGAudioBuffer* data; if( !SGS_PARSE_METHOD( C, SGAudioBuffer::_sgs_interface, data, SGAudioBuffer, render ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->render( sgs_GetVar<SGAudioGenerator::Handle>()(C,0), sgs_GetVar<float>()(C,1) )); return 1;
}

int SGAudioBuffer::_sgs_destruct( SGS_CTX, sgs_VarObj* obj )
{
	static_cast<SGAudioBuffer*>( obj->data )->C = C;
	static_cast<SGAudioBuffer*>( obj->data )->~SGAudioBuffer();
	return SGS_SUCCESS;
}

int SGAudioBuffer::_sgs_gcmark( SGS_CTX, sgs_VarObj* obj )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioBuffer*>( obj->data )->C, C );
	return SGS_SUCCESS;
}

int SGAudioBuffer::_sgs_getindex( SGS_ARGS_GETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioBuffer*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
		SGS_CASE( "size" ){ sgs_PushVar( C, static_cast<SGAudioBuffer*>( obj->data )->_get_size() ); return SGS_SUCCESS; }
		SGS_CASE( "seconds" ){ sgs_PushVar( C, static_cast<SGAudioBuffer*>( obj->data )->_get_seconds() ); return SGS_SUCCESS; }
		SGS_CASE( "sampleRate" ){ sgs_PushVar( C, static_cast<SGAudioBuffer*>( obj->data )->sampleRate ); return SGS_SUCCESS; }
	SGS_END_INDEXFUNC;
}

int SGAudioBuffer::_sgs_setindex( SGS_ARGS_SETINDEXFUNC )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioBuffer*>( obj->data )->C, C );
	SGS_BEGIN_INDEXFUNC
	SGS_END_INDEXFUNC;
}

int SGAudioBuffer::_sgs_dump( SGS_CTX, sgs_VarObj* obj, int depth )
{
	_sgsTmpChanger<sgs_Context*> _tmpchg( static_cast<SGAudioBuffer*>( obj->data )->C, C );
	char bfr[ 45 ];
	sprintf( bfr, "SGAudioBuffer (%p) %s", obj->data, depth > 0 ? "\n{" : " ..." );
	sgs_PushString( C, bfr );
	if( depth > 0 )
	{
		{ sgs_PushString( C, "\nsize = " ); sgs_DumpData( C, static_cast<SGAudioBuffer*>( obj->data )->_get_size(), depth ).push( C ); }
		{ sgs_PushString( C, "\nseconds = " ); sgs_DumpData( C, static_cast<SGAudioBuffer*>( obj->data )->_get_seconds(), depth ).push( C ); }
		{ sgs_PushString( C, "\nsampleRate = " ); sgs_DumpData( C, static_cast<SGAudioBuffer*>( obj->data )->sampleRate, depth ).push( C ); }
		sgs_StringConcat( C, 6 );
		sgs_PadString( C );
		sgs_PushString( C, "\n}" );
		sgs_StringConcat( C, 3 );
	}
	return SGS_SUCCESS;
}

static sgs_RegFuncConst SGAudioBuffer__sgs_funcs[] =
{
	{ "resize", _sgs_method__SGAudioBuffer__resize },
	{ "append", _sgs_method__SGAudioBuffer__append },
	{ "set_sample_rate", _sgs_method__SGAudioBuffer__set_sample_rate },
	{ "silence", _sgs_method__SGAudioBuffer__silence },
	{ "add_silence", _sgs_method__SGAudioBuffer__add_silence },
	{ "sine", _sgs_method__SGAudioBuffer__sine },
	{ "triangle", _sgs_method__SGAudioBuffer__triangle },
	{ "saw", _sgs_method__SGAudioBuffer__saw },
	{ "noise", _sgs_method__SGAudioBuffer__noise },
	{ "scale", _sgs_method__SGAudioBuffer__scale },
	{ "scaled", _sgs_method__SGAudioBuffer__scaled },
	{ "lowpass", _sgs_method__SGAudioBuffer__lowpass },
	{ "taper", _sgs_method__SGAudioBuffer__taper },
	{ "add_note", _sgs_method__SGAudioBuffer__add_note },
	{ "render", _sgs_method__SGAudioBuffer__render },
	{ NULL, NULL },
};

static int SGAudioBuffer__sgs_ifn( SGS_CTX )
{
	sgs_CreateDict( C, NULL, 0 );
	sgs_StoreFuncConsts( C, sgs_StackItem( C, -1 ),
		SGAudioBuffer__sgs_funcs,
		-1, "SGAudioBuffer." );
	return 1;
}

static sgs_ObjInterface SGAudioBuffer__sgs_interface =
{
	"SGAudioBuffer",
	SGAudioBuffer::_sgs_destruct, SGAudioBuffer::_sgs_gcmark, SGAudioBuffer::_getindex, SGAudioBuffer::_sgs_setindex, NULL, NULL, SGAudioBuffer::_sgs_dump, NULL, NULL, NULL, 
};
_sgsInterface SGAudioBuffer::_sgs_interface(SGAudioBuffer__sgs_interface, SGAudioBuffer__sgs_ifn);


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

static int _sgs_method__SGAudioEmitter__load_buffer( SGS_CTX )
{
	SGAudioEmitter* data; if( !SGS_PARSE_METHOD( C, SGAudioEmitter::_sgs_interface, data, SGAudioEmitter, load_buffer ) ) return 0;
	_sgsTmpChanger<sgs_Context*> _tmpchg( data->C, C );
	sgs_PushVar(C,data->load_buffer( sgs_GetVar<SGAudioBuffer::Handle>()(C,0) )); return 1;
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
	{ "load_buffer", _sgs_method__SGAudioEmitter__load_buffer },
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

