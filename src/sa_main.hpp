

#include "sa_sound.hpp"

#include <sgs_cppbc.h>


struct SGFileStream : SGStream
{
	SGFileStream( const char* file )
	{
		f = fopen( file, "rb" );
		error = f ? 0 : 1;
		size = 0;
		if( f )
		{
			fseek( f, SEEK_END, 0 );
			size = ftell( f );
			fseek( f, SEEK_SET, 0 );
		}
	}
	~SGFileStream()
	{
		if( f )
			fclose( f );
	}
	int32_t Read( void* to, int32_t max )
	{
		if( !f )
			return 0;
		return fread( to, 1, max, f );
	}
	int Seek( int32_t pos, int mode = SEEK_SET )
	{
		return fseek( f, pos, mode ) == 0;
	}
	int32_t Tell()
	{
		return ftell( f );
	}
	int32_t GetSize()
	{
		return size;
	}
	
	FILE* f;
	int32_t size;
};

struct SGFileSource : SGDataSource
{
	SGStream* GetStream( const char* filename )
	{
		return new SGFileStream( filename );
	}
};




#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>

#define sgsthread_sleep( ms ) Sleep( ms )

#define sgsmutex_t CRITICAL_SECTION
#define sgsthread_t HANDLE
#define threadret_t DWORD __stdcall

#define sgsthread_create( toT, func, data ) toT = CreateThread( NULL, 1024, func, data, 0, NULL )
#define sgsthread_self( toT ) toT = GetCurrentThread()
#define sgsthread_join( T ) WaitForMultipleObjects( 1, &T, TRUE, INFINITE )
#define sgsthread_equal( T1, T2 ) (T1 == T2)

#define sgsmutex_init( M ) InitializeCriticalSection( &M )
#define sgsmutex_destroy( M ) DeleteCriticalSection( &M )
#define sgsmutex_lock( M ) EnterCriticalSection( &M )
#define sgsmutex_unlock( M ) LeaveCriticalSection( &M )


#else

#  include <unistd.h>
#  include <pthread.h>

static void sgsthread_sleep( int ms )
{
	if( ms >= 1000 )
	{
		sleep( ms / 1000 );
		ms %= 1000;
	}
	if( ms > 0 )
	{
		usleep( ms * 1000 );
	}
}

#define sgsmutex_t pthread_mutex_t
#define sgsthread_t pthread_t
#define threadret_t void*

#define sgsthread_create( toT, func, data ) pthread_create( &toT, NULL, func, data )
#define sgsthread_self( toT ) toT = pthread_self()
#define sgsthread_join( T ) pthread_join( T, NULL )
#define sgsthread_equal( T1, T2 ) pthread_equal( T1, T2 )

#define sgsmutex_init( M ) pthread_mutex_init( &M, NULL )
#define sgsmutex_destroy( M ) pthread_mutex_destroy( &M )
#define sgsmutex_lock( M ) pthread_mutex_lock( &M )
#define sgsmutex_unlock( M ) pthread_mutex_unlock( &M )

#endif



struct SGAudioSystem;
struct SGAudioEmitter
{
	SGS_OBJECT;
	
	~SGAudioEmitter()
	{
		unload();
	}
	
	struct SGLock
	{
		SGLock( sgsmutex_t* mtx ) : mutex( mtx ), locked( 1 )
		{ sgsmutex_lock( *mutex ); }
		~SGLock(){ sgsmutex_unlock( *mutex ); }
		sgsmutex_t* mutex;
		int locked;
	};
#define SGLOCK SGLock LOCK(Mutex)
	
	SGS_METHOD void play(){ SGLOCK; Emitter.Play(); }
	SGS_METHOD void stop(){ SGLOCK; Emitter.Stop(); }
	SGS_METHOD void pause(){ SGLOCK; Emitter.Pause(); }
	
	SGAudioSystem* GetSystem(){ return System; }
	
	SGS_METHOD bool load( sgsString file );
	
	SGS_METHOD bool unload()
	{
		SGLOCK;
		bool ret = Emitter.System != NULL;
		if( Emitter.System )
			Emitter.System->ReleaseEmitter( &Emitter );
		return ret;
	}
	
	SGS_METHOD void fade_volume( float vol, float tm )
	{
		SGLOCK;
		Emitter.FadeVolume( vol, tm );
	}
	
	SGS_METHOD void set_position( float x, float y, float z )
	{
		SGLOCK;
		float pos[3] = { x, y, z };
		Emitter.SetPosition( pos );
	}
	
	bool _get_playing(){ SGLOCK; return Emitter.IsPlaying(); }
	SGS_PROPERTY_FUNC( READ _get_playing ) SGS_ALIAS( bool playing );
	
	bool _get_loop(){ SGLOCK; return Emitter.StreamLoop; }
	void _set_loop( bool v ){ SGLOCK; Emitter.SetLooping( v ); }
	SGS_PROPERTY_FUNC( READ _get_loop WRITE _set_loop ) SGS_ALIAS( bool loop );
	
	float _get_volume(){ SGLOCK; return Emitter.GetVolume(); }
	void _set_volume( float v ){ SGLOCK; Emitter.SetVolume( v ); }
	SGS_PROPERTY_FUNC( READ _get_volume WRITE _set_volume ) SGS_ALIAS( float volume );
	
	float _get_pitch(){ SGLOCK; return Emitter.GetPitch(); }
	void _set_pitch( float v ){ SGLOCK; Emitter.SetPitch( v ); }
	SGS_PROPERTY_FUNC( READ _get_pitch WRITE _set_pitch ) SGS_ALIAS( float pitch );
	
	int _get_groups(){ SGLOCK; return Emitter.GetType(); }
	void _set_groups( int v ){ SGLOCK; Emitter.SetType( v ); }
	SGS_PROPERTY_FUNC( READ _get_groups WRITE _set_groups ) SGS_ALIAS( int groups );
	
	float _get_offset(){ SGLOCK; return Emitter.GetPlayOffset(); }
	void _set_offset( float v ){ SGLOCK; Emitter.SetPlayOffset( v ); }
	SGS_PROPERTY_FUNC( READ _get_offset WRITE _set_offset ) SGS_ALIAS( float offset );
	
	void _set_mode3d( bool v ){ SGLOCK; Emitter.Set3DMode( v ); }
	SGS_PROPERTY_FUNC( WRITE _set_mode3d ) SGS_ALIAS( bool mode3d );
	
	void _set_panning( float v ){ SGLOCK; Emitter.SetPanning( v ); }
	SGS_PROPERTY_FUNC( WRITE _set_panning ) SGS_ALIAS( float panning );
	
	void _set_factor( float v ){ SGLOCK; Emitter.SetDistanceFactor( v ); }
	SGS_PROPERTY_FUNC( WRITE _set_factor ) SGS_ALIAS( float factor );
	
	sgsHandle< SGAudioSystem > System; SGS_GCREF( System );
	SSEmitter Emitter;
	sgsmutex_t* Mutex;
};



threadret_t SGA_Ticker( void* );

struct SGAudioSystem
{
	SGS_OBJECT;
	
	static SGAudioSystem* create();
	~SGAudioSystem();
	
	struct SGLock
	{
		SGLock( sgsmutex_t* mtx ) : mutex( mtx ), locked( 1 )
		{ sgsmutex_lock( *mutex ); }
		~SGLock(){ sgsmutex_unlock( *mutex ); }
		sgsmutex_t* mutex;
		int locked;
	};
	
	SGS_METHOD void set_volume( float vol, int grp )
	{
		if( grp < 0 || grp > 32 )
		{
			sgs_Msg( C, SGS_WARNING, "group ID expected between 0 and 32" );
			return;
		}
		
		SGLOCK;
		Sound.SetVolume( vol, grp );
	}
	
	SGS_METHOD float get_volume( int grp )
	{
		if( grp < 0 || grp > 32 )
		{
			sgs_Msg( C, SGS_WARNING, "group ID expected between 0 and 32" );
			return 0;
		}
		
		SGLOCK;
		return Sound.GetVolume( grp );
	}
	
	SGS_METHOD void set_listener_position( float x, float y, float z )
	{
		SGLOCK;
		float lp[3] = { x, y, z };
		Sound.SetListenerPosition( lp );
	}
	
	SGS_METHOD void set_listener_orientation( float dx, float dy, float dz, float ux, float uy, float uz )
	{
		SGLOCK;
		float ld[3] = { dx, dy, dz };
		float lu[3] = { ux, uy, uz };
		Sound.SetListenerDirection( ld, lu );
	}
	
	SGS_METHOD void suspend(){ SGLOCK; Sound.ChangeState( 1 ); }
	SGS_METHOD void resume(){ SGLOCK; Sound.ChangeState( 0 ); }
	
	SGS_METHOD SGS_MULTRET create_emitter( sgsString file )
	{
		SGLOCK;
		SGAudioEmitter* em = SGS_CREATECLASS( C, NULL, SGAudioEmitter, () );
		em->System = this;
		em->Mutex = Mutex;
		if( file.size() )
			Sound.SetupEmitter( file.c_str(), &em->Emitter );
		return 1;
	}
	
	SGDataSource* Source;
	SSoundSystem Sound;
	sgsthread_t Thread;
	sgsmutex_t* Mutex;
	sgsmutex_t MutexObj;
	int ThreadEnable;
};


