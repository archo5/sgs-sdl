

#include "sa_main.hpp"


bool SGAudioEmitter::load( sgsString file )
{
	SGLOCK;
	return file.size() ? GetSystem()->Sound.SetupEmitter( file.c_str(), &Emitter ) : false;
}


threadret_t SGA_Ticker( void* ss )
{
	SGAudioSystem* sys = (SGAudioSystem*) ss;
	alcMakeContextCurrent( sys->Sound.Context );
	while( sys->ThreadEnable )
	{
		sgsmutex_lock( sys->MutexObj );
		sys->Sound.Tick( 1.0f / 30.0f );
		sgsmutex_unlock( sys->MutexObj );
		sgsthread_sleep( 33 );
	}
	return 0;
}

SGAudioSystem* SGAudioSystem::create()
{
	SGAudioSystem* sys = new SGAudioSystem;
	sys->ThreadEnable = TRUE;
	sys->Source = new SGFileSource;
	if( !sys->Sound.Init( sys->Source ) )
	{
		delete sys->Source;
		sys->Source = NULL;
		delete sys;
		return NULL;
	}
	sgsmutex_init( sys->MutexObj );
	sys->Mutex = &sys->MutexObj;
	sgsthread_create( sys->Thread, SGA_Ticker, sys );
	return sys;
}

SGAudioSystem::~SGAudioSystem()
{
	if( Source )
	{
		ThreadEnable = FALSE;
		sgsthread_join( Thread );
		sgsmutex_destroy( MutexObj );
		Sound.Destroy();
		delete Source;
	}
}


int sgs_audio_create( SGS_CTX )
{
	SGSFN( "sgs_audio_create" );
	SGAudioSystem* sys = SGAudioSystem::create();
	if( !sys )
		return 0;
	sgs_CreateClass( C, NULL, sys );
	return 1;
}

int sgs_audio_get_devices( SGS_CTX )
{
	SGSFN( "sgs_audio_get_devices" );
	TString str;
	int good = SSoundSystem::GetDevices( str );
	if( !good )
		return sgs_Msg( C, SGS_WARNING, "Failed to retrieve OpenAL devices" );
	sgs_PushStringBuf( C, str.c_str(), str.size() );
	return 1;
}

static sgs_RegFuncConst rfc[] =
{
	{ "sgs_audio_create", sgs_audio_create },
	{ "sgs_audio_get_devices", sgs_audio_get_devices },
	{ NULL, NULL },
};


extern "C" int sgscript_main( SGS_CTX )
{
	sgs_RegFuncConsts( C, rfc, -1 );
	sgsVariable env = sgsEnv( C );
	env.setprop( "SGAudioEmitter", sgs_GetClassInterface<SGAudioEmitter>( C ) );
	env.setprop( "SGAudioSystem", sgs_GetClassInterface<SGAudioSystem>( C ) );
	return SGS_SUCCESS;
}


