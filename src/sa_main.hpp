

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




#ifdef _WIN32
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


inline float saturate( float v ){ return TCLAMP( v, 0.0f, 1.0f ); }
inline float lerp( float a, float b, float t ){ return a * ( 1 - t ) + b * t; }
inline float revlerp_oneway( float t, float a, float b ){ if( b == a ) return 1.0; return saturate( ( t - a ) / ( b - a ) ); }
inline float adsr( float curTime, float length, float attack, float decay, float sustain, float release )
{
	if( curTime > length ) // release
		return revlerp_oneway( curTime, length + release, length ) * sustain;
	if( curTime < attack ) // attack
		return revlerp_oneway( curTime, 0, attack );
	if( curTime < attack + decay ) // decay
		return lerp( 1, sustain, revlerp_oneway( curTime, attack, attack + decay ) );
	return sustain;
}


struct SGAudioGenerator
{
	SGS_OBJECT;
	
	typedef sgsHandle< SGAudioGenerator > Handle;
	Handle GetScrHandle(){ return Handle( this ); }
	
	virtual void Seek( float t ) = 0;
	virtual void Read( float* out, int samples, float time ) = 0;
};

struct SGAudioGenConstant : SGAudioGenerator
{
	SGS_OBJECT_INHERIT( SGAudioGenerator );
	
	SGAudioGenConstant() : value( 0 ){}
	virtual void Seek( float ){}
	virtual void Read( float* out, int samples, float )
	{
		for( int i = 0; i < samples; ++i )
			out[ i ] = value;
	}
	
	SGS_STATICMETHOD Handle create( sgs_Context* ctx ){ return SGS_CREATECLASS( ctx, NULL, SGAudioGenConstant, () )->GetScrHandle(); }
	
	SGS_PROPERTY float value;
};

struct SGAudioGenNoise : SGAudioGenerator
{
	SGS_OBJECT_INHERIT( SGAudioGenerator );
	
	SGAudioGenNoise() : power( 1 ){}
	virtual void Seek( float ){}
	virtual void Read( float* out, int samples, float )
	{
		for( int i = 0; i < samples; ++i )
			out[ i ] = ( float(rand()) / float(RAND_MAX) * 2 - 1 ) * power;
	}
	
	SGS_STATICMETHOD Handle create( sgs_Context* ctx ){ return SGS_CREATECLASS( ctx, NULL, SGAudioGenNoise, () )->GetScrHandle(); }
	
	SGS_PROPERTY float power;
};

struct SGAudioGenScale : SGAudioGenerator
{
	SGS_OBJECT_INHERIT( SGAudioGenerator );
	
	SGAudioGenScale() : value( 1 ){}
	virtual void Seek( float t ){ if( gen ) gen->Seek( t ); }
	virtual void Read( float* out, int samples, float time )
	{
		if( gen.not_null() )
		{
			gen->Read( out, samples, time );
			for( int i = 0; i < samples; ++i )
				out[ i ] *= value;
		}
		else
		{
			for( int i = 0; i < samples; ++i )
				out[ i ] = 0;
		}
	}
	
	SGS_STATICMETHOD Handle create( sgs_Context* ctx ){ return SGS_CREATECLASS( ctx, NULL, SGAudioGenScale, () )->GetScrHandle(); }
	
	SGS_PROPERTY Handle gen;
	SGS_PROPERTY float value;
};

struct SGAudioGenMultiply : SGAudioGenerator
{
	SGS_OBJECT_INHERIT( SGAudioGenerator );
	
	SGAudioGenMultiply() : value( 1 ){}
	virtual void Seek( float t )
	{
		if( gen1 ) gen1->Seek( t );
		if( gen2 ) gen2->Seek( t );
	}
	virtual void Read( float* out, int samples, float time )
	{
		if( gen1.not_null() && gen2.not_null() )
		{
			gen1->Read( out, samples, time );
			
			float tmp[ 1024 ];
			float timePerSample = time / samples;
			int s = 0;
			while( s < samples )
			{
				int cnt = MIN( samples - s, 1024 );
				gen2->Read( tmp, cnt, timePerSample * cnt );
				for( int i = 0; i < cnt; ++i )
					out[ s + i ] *= tmp[ i ] * value;
				s += cnt;
			}
		}
		else
		{
			for( int i = 0; i < samples; ++i )
				out[ i ] = 0;
		}
	}
	
	SGS_STATICMETHOD Handle create( sgs_Context* ctx ){ return SGS_CREATECLASS( ctx, NULL, SGAudioGenMultiply, () )->GetScrHandle(); }
	
	SGS_PROPERTY Handle gen1;
	SGS_PROPERTY Handle gen2;
	SGS_PROPERTY float value;
};

struct SGAudioGenSine : SGAudioGenerator
{
	SGS_OBJECT_INHERIT( SGAudioGenerator );
	
	SGAudioGenSine() : power( 1 ), frequency( 440 ), phase( 0 ), curTime( 0 ){}
	virtual void Seek( float t ){ curTime = t; }
	virtual void Read( float* out, int samples, float time )
	{
		phase *= M_PI * 2;
		float q = M_PI * 2 * frequency * time / samples;
		for( int i = 0; i < samples; ++i )
		{
			out[ i ] = sin( i * q - phase ) * power;
		}
		curTime += time;
	}
	
	SGS_STATICMETHOD Handle create( sgs_Context* ctx ){ return SGS_CREATECLASS( ctx, NULL, SGAudioGenSine, () )->GetScrHandle(); }
	
	SGS_PROPERTY float power;
	SGS_PROPERTY float frequency;
	SGS_PROPERTY float phase;
	float curTime;
};

struct SGAudioGenADSR : SGAudioGenerator
{
	SGS_OBJECT_INHERIT( SGAudioGenerator );
	
	SGAudioGenADSR() : t0( 0 ), length( 1 ), power( 1 ), attack( 0.1 ), decay( 0.1 ), sustain( 0.8 ), release( 0.5 ), curTime( 0 ){}
	virtual void Seek( float t ){ curTime = t; }
	virtual void Read( float* out, int samples, float time )
	{
		float q = time / samples;
		for( int i = 0; i < samples; ++i )
		{
			out[ i ] = adsr( curTime + i * q - t0, length, attack, decay, sustain, release ) * power;
		}
		curTime += time;
	}
	
	SGS_STATICMETHOD Handle create( sgs_Context* ctx ){ return SGS_CREATECLASS( ctx, NULL, SGAudioGenADSR, () )->GetScrHandle(); }
	
	SGS_PROPERTY float t0;
	SGS_PROPERTY float length;
	SGS_PROPERTY float power;
	SGS_PROPERTY float attack;
	SGS_PROPERTY float decay;
	SGS_PROPERTY float sustain;
	SGS_PROPERTY float release;
	float curTime;
};


struct SGAudioBuffer
{
	SGS_OBJECT;
	
	typedef sgsHandle< SGAudioBuffer > Handle;
	Handle GetScrHandle(){ return Handle( this ); }
	
	
	SGAudioBuffer( int sz, int sr ) : sampleRate( sr )
	{
		data.resize( sz, 0.0f );
	}
	
	
	SGS_METHOD Handle resize( int sz ){ data.resize( sz ); return GetScrHandle(); }
	
	SGS_METHOD Handle append( SGAudioBuffer::Handle other )
	{
		if( other )
			data.insert( data.end(), other->data.begin(), other->data.end() );
		return GetScrHandle();
	}
	
	SGS_METHOD Handle set_sample_rate( int sr ){ sampleRate = sr; return GetScrHandle(); }
	
	// assume: vector<float> data, int AA; give: float SAMPLE_ID;
	#define SGSAB_SAMPLE_WAVEFORM( waveform ) \
		if( AA == 0 ){ \
			for( size_t i = 0; i < data.size(); ++i ){ \
				float SAMPLE_ID = i; \
				data[ i ] = waveform; \
			} \
		} else { \
			float invAA = 1.0f / AA; \
			for( size_t i = 0; i < data.size(); ++i ){ \
				float v = 0; \
				for( int j = 0; j < AA; ++j ){ \
					float SAMPLE_ID = i + float(j) * invAA - 0.5f; \
					v += waveform; \
				} \
				data[ i ] = v * invAA; \
			} \
		}
	
	inline float sample_adsr( float sample, float t, float attack, float decay, float sustain, float release )
	{
		sample /= sampleRate;
		if( sample > t ) // release
			return revlerp_oneway( sample, t + release, t ) * sustain;
		if( sample < attack ) // attack
			return revlerp_oneway( sample, 0, attack );
		if( sample < attack + decay ) // decay
			return lerp( 1, sustain, revlerp_oneway( sample, attack, attack + decay ) );
		return sustain;
	}
	inline float sample_adsr_aa( float sample, float t, float attack, float decay, float sustain, float release, int AA )
	{
		if( AA == 0 )
			return sample_adsr( sample, t, attack, decay, sustain, release );
		
		float v = 0;
		float invAA = 1.0f / AA;
		for( int i = 0; i < AA; ++i )
			v += sample_adsr( sample + i * invAA - 0.5f, t, attack, decay, sustain, release );
		return v * invAA;
	}
	
	SGS_METHOD Handle silence()
	{
		for( size_t i = 0; i < data.size(); ++i )
			data[ i ] = 0;
		return GetScrHandle();
	}
	
	SGS_METHOD Handle add_silence( int samples )
	{
		size_t i = data.size();
		data.resize( i + samples );
		for( ; i < data.size(); ++i )
			data[ i ] = 0;
		return GetScrHandle();
	}
	
	SGS_METHOD Handle sine( float power, float period, float phase, int AA )
	{
		if( sgs_StackSize( C ) < 4 )
			AA = 8;
		
		phase *= M_PI * 2;
		float q = M_PI * 2 / ( float(sampleRate) * period );
		SGSAB_SAMPLE_WAVEFORM( sin( SAMPLE_ID * q - phase ) * power );
		return GetScrHandle();
	}
	
	SGS_METHOD Handle triangle( float power, float period, float phase, int AA )
	{
		if( sgs_StackSize( C ) < 4 )
			AA = 8;
		
		float q = 4.0f / ( sampleRate * period );
		phase -= 1.75f;
		SGSAB_SAMPLE_WAVEFORM( ( fabsf( fmodf( SAMPLE_ID * q - phase * 4, 4.0f ) - 2 ) - 1 ) * power );
		return GetScrHandle();
	}
	
	SGS_METHOD Handle saw( float power, float period, float phase, int AA )
	{
		if( sgs_StackSize( C ) < 4 )
			AA = 8;
		
		float q = 1.0f / ( sampleRate * period );
		SGSAB_SAMPLE_WAVEFORM( ( fmodf( SAMPLE_ID * q - phase, 1.0f ) * 2 - 1 ) * power );
		return GetScrHandle();
	}
	
	SGS_METHOD Handle noise( float power )
	{
		if( sgs_StackSize( C ) < 1 )
			power = 1;
		
		for( size_t i = 0; i < data.size(); ++i )
		{
			data[ i ] = ( float(rand()) / float(RAND_MAX) - 0.5f ) * 2 * power;
		}
		return GetScrHandle();
	}
	
	SGS_METHOD Handle scale( float power )
	{
		for( size_t i = 0; i < data.size(); ++i )
		{
			data[ i ] *= power;
		}
		return GetScrHandle();
	}
	SGS_METHOD SGS_MULTRET scaled( float power )
	{
		SGAudioBuffer* buf = SGS_CREATECLASS( C, NULL, SGAudioBuffer, ( data.size(), sampleRate ) );
		for( size_t i = 0; i < data.size(); ++i )
		{
			buf->data[ i ] = data[ i ] * power;
		}
		return 1;
	}
	
	SGS_METHOD Handle lowpass( float factor )
	{
		float invfactor = 1 - factor;
		for( size_t i = 1; i < data.size(); ++i )
		{
			data[ i ] = invfactor * data[ i ] + factor * data[ i - 1 ];
		}
		return GetScrHandle();
	}
	
	SGS_METHOD Handle taper( float tt )
	{
		float mintt = 1.0f / sampleRate;
		tt = MAX( tt, mintt );
		float invTT2 = 1.0f / ( tt * tt );
		float invSampleRate = 1.0f / sampleRate;
		for( size_t i = 0; i < data.size(); ++i )
		{
			float st = i * invSampleRate;
			float et = ( data.size() - i - 1 ) * invSampleRate;
			data[ i ] *= TCLAMP( st, 0.0f, tt ) * TCLAMP( et, 0.0f, tt ) * invTT2;
		}
		return GetScrHandle();
	}
	
	SGS_METHOD Handle add_note( SGAudioBuffer::Handle pattern, float t0, float t1, float attack, float decay, float sustain, float release, int AA )
	{
		if( sgs_StackSize( C ) < 4 )
			AA = 8;
		
		if( !pattern.not_null() )
		{
			sgs_Msg( C, SGS_WARNING, "pattern cannot be null" );
			return GetScrHandle();
		}
		if( sampleRate != pattern->sampleRate )
		{
			sgs_Msg( C, SGS_WARNING, "incompatible sample rate (source=%d target=%d)", pattern->sampleRate, sampleRate );
			return GetScrHandle();
		}
		size_t i0 = TCLAMP( size_t(t0 * sampleRate), size_t(0), data.size() );
		size_t i1 = TCLAMP( size_t((t1 + release) * sampleRate), size_t(0), data.size() );
		for( size_t i = i0; i < i1; ++i )
		{
			size_t srci = ( i - i0 ) % pattern->data.size();
			data[ i ] += pattern->data[ srci ] * sample_adsr_aa( i - i0, t1 - t0, attack, decay, sustain, release, AA );
		}
		return GetScrHandle();
	}
	
	SGS_METHOD Handle render( SGAudioGenerator::Handle gen, float t )
	{
		if( sgs_StackSize( C ) < 2 )
			t = 0;
		
		if( !gen.not_null() )
		{
			sgs_Msg( C, SGS_WARNING, "generator cannot be null" );
			return GetScrHandle();
		}
		if( data.size() == 0 )
		{
			sgs_Msg( C, SGS_WARNING, "size of buffer cannot be 0" );
			return GetScrHandle();
		}
		gen->Seek( t );
		gen->Read( &data[0], data.size(), float(data.size()) / float(sampleRate) );
		return GetScrHandle();
	}
	
	
	SGS_IFUNC( GETINDEX ) int _getindex( SGS_ARGS_GETINDEXFUNC )
	{
		if( sgs_ObjectArg( C ) == 0 )
		{
			// index lookup
			SGAudioBuffer* buf = (SGAudioBuffer*) obj->data;
			int i = sgs_GetVar<int>()( C, 0 );
			if( i < 0 || i >= int(buf->data.size()) )
				return SGS_EBOUNDS;
			sgs_PushReal( C, buf->data[ i ] );
			return SGS_SUCCESS;
		}
		return _sgs_getindex( C, obj );
	}
	
	size_t _get_size(){ return data.size(); }
	SGS_PROPERTY_FUNC( READ _get_size ) SGS_ALIAS( size_t size );
	
	float _get_seconds(){ return data.size() / float(sampleRate); }
	SGS_PROPERTY_FUNC( READ _get_seconds ) SGS_ALIAS( float seconds );
	
	
	std::vector< float > data;
	SGS_PROPERTY_FUNC( READ ) int sampleRate;
};



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
	SGS_METHOD bool load_buffer( SGAudioBuffer::Handle buf );
	
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


