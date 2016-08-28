
#pragma GCC diagnostic ignored "-Wreorder"


#include "ogg/ogg.h"
#include "vorbis/vorbisfile.h"


#include "sa_sound.hpp"


static float LerpF( float a, float b, float s ){ return a * (1-s) + b * s; }

static uint32_t Stream_U32LE( SGStream* S )
{
	uint32_t data = 0;
	S->Read( &data, 4 );
	return data;
}
static int16_t Stream_I16LE( SGStream* S )
{
	int16_t data = 0;
	S->Read( &data, 2 );
	return data;
}
static int Stream_CheckBytes( SGStream* S, const char* bytes, int count )
{
	int i = 0;
	while( count --> 0 )
	{
		if( S->GetChar() != bytes[ i++ ] )
			return 0;
	}
	return 1;
}


#define gSysInfo( text, cap ) printf( "%s: %s\n", cap, text )


#define STREAMBUF_SIZE 65536

/// Streaming emitter = emitter that has a file open..


const char* ALErrors[] = 
{
	"AL_INVALID_NAME",
	"AL_ILLEGAL_ENUM / AL_INVALID_ENUM",
	"AL_INVALID_VALUE",
	"AL_ILLEGAL_COMMAND / AL_INVALID_OPERATION",
	"AL_OUT_OF_MEMORY",
};
const char* ALCErrors[] = 
{
	"ALC_INVALID_DEVICE",
	"ALC_INVALID_CONTEXT",
	"ALC_INVALID_ENUM",
	"ALC_INVALID_VALUE",
	"ALC_OUT_OF_MEMORY",
};

// #define LOG_AL_CALLS 2
#define THROW_AL_ERRORS 1


#ifdef LOG_AL_CALLS
struct allog
{
	FILE* f;
	allog(){ f = fopen( "ALCalls.txt", "a" ); }
	~allog(){ fclose( f ); }
	void print( const char* str, ... )
	{
		va_list args;
		va_start( args, str );
		vfprintf( f, str, args );
		va_end( args );
		fflush( f );
	}
} allogi;
#endif

void LogALCall( const char* call, const char* file, int32_t line, uint32_t error, int alc )
{
#ifdef LOG_AL_CALLS
	const char* errstr = alc ? ALCErrors[ error - ALC_INVALID_DEVICE ] : ALErrors[ error - AL_INVALID_NAME ];
#if LOG_AL_CALLS == 2
	allogi.print( "%s -- GetError: %s\n", call, error == 0 ? "AL_NO_ERROR" : errstr );
#else
	allogi.print( "%s [%s, %d] -- GetError: %s\n", call, file, line, error == 0 ? "AL_NO_ERROR" : errstr );
#endif
#endif
}

void CheckALErrors( const char* call, const char* file, int32_t line, ALCdevice* dev, const char* data, ... )
{
	ALenum error = dev ? alcGetError( dev ) : alGetError();
	LogALCall( call, file, line, error, !!dev );

#if THROW_AL_ERRORS
	if( error )
	{
		char buf[ 4096 ];
		TString out;
		const char* errstr = dev ? ALCErrors[ error - ALC_INVALID_DEVICE ] : ALErrors[ error - AL_INVALID_NAME ];
		snprintf( buf, 4096, "OpenAL error - %s\nCall: %s\nFile: %s\nLine: %d", errstr, call, file, line );
		out = buf;
		if( data )
		{
			TString add;
			va_list args;
			va_start( args, data );
			vsnprintf( buf, 4096, data, args );
			add = buf;
			va_end( args );
			out += "\n\nAdditional data:\n";
			out += add;
		}
		gSysInfo( out.c_str(), "sgs-audio - OpenAL Error" );
	}
#endif
}


#ifdef _DEBUG
#define AL_CALL( c, ... ) c; CheckALErrors( #c, __FILE__, __LINE__, NULL, NULL, __VA_ARGS__ )
#define ALC_CALL( c, device, ... ) c; CheckALErrors( #c, __FILE__, __LINE__, device, NULL, __VA_ARGS__ );
#else
#define AL_CALL( c, ... ) c
#define ALC_CALL( c, device, ... ) c
#endif


/*
	AUDIO DATA interfaces
*/

/* WAVE */

struct WAVAudioData : IAudioData
{
	~WAVAudioData()
	{
		delete File;
	}

	int32_t StreamIn( byte_t* out, int32_t max, int loop )
	{
		int32_t ret = 0;
		while( max && ( loop || !AtEnd() ) )
		{
			int32_t left2read;
			if( AtEnd() )
			{
				Seek( 0 );
				left2read = PCMSize;
			}
			else
				left2read = PCMSize - Tell();
			int32_t maxread = MIN( max, left2read );
			int32_t read = File->Read( out, maxread );
			if( read < 0 )
				return -1;
			out += read;
			max -= read;
			ret += read;
		}
		return ret;
	}

	void Seek( int32_t pos )
	{
		assert( pos <= PCMSize && pos >= 0 );
		int res = File->Seek( pos + DataOffset );
		assert( res );
	}

	int32_t Tell()
	{
		int32_t pos = File->Tell();
		if( pos < 0 )
			return -1;
		else
			return pos - DataOffset;
	}

	int AtEnd(){ return Tell() >= PCMSize; }

	float Pos2Time( int32_t pos ){ return float( pos ) / DataPerSec; }
	int32_t Time2Pos( float time ){ return time * DataPerSec; }
	
	float DataPerSec;
	uint32_t DataOffset;
	SGStream* File;
};

IAudioData* CreateWAVAudioData( SGDataSource* src, const char* file )
{
	const char* error = NULL;
	WAVAudioData* wad;
	SGStream* File = src->GetStream( file );
	if( !File ){ fprintf( stderr, "Could not load file: %s\n", file ); return NULL; }
	if( File->error > 0 ){ error = "File was not found"; goto invalid; }

	uint32_t file_size, chunk_size, sample_rate, byte_rate, data_size;
	int16_t audio_format, channel_count, block_align, bits_per_sample, extension;
	(void) byte_rate;
	(void) block_align;

	file_size = File->GetSize();
	if( !Stream_CheckBytes( File, "RIFF", 4 ) ){ error = "Expected 'RIFF' - not a WAV file"; goto invalid; }

	chunk_size = Stream_U32LE( File );
	if( chunk_size > file_size - 4 ){ error = "Main chunk size bigger than file - incomplete/damaged file"; goto invalid; }

	if( !Stream_CheckBytes( File, "WAVE", 4 ) ){ error = "Wrong audio format detected"; goto invalid; }

	// Subchunk 1: 'fmt '
	if( !Stream_CheckBytes( File, "fmt ", 4 ) ){ error = "Wrong chunk found, expected 'fmt '"; goto invalid; }
	chunk_size = Stream_U32LE( File );
	if( chunk_size != 16 && chunk_size != 18 ){ error = "Detected an incompatible non-PCM .wav file"; goto invalid; }

	audio_format = Stream_I16LE( File );
	if( audio_format != 1 ){ error = "Engine doesn't support compressed .wav files"; goto invalid; }

	channel_count = Stream_I16LE( File );
	if( channel_count != 1 && channel_count != 2 ){ error = "Unsupported number of channels, expected 1 or 2"; goto invalid; }

	sample_rate = Stream_U32LE( File );
	byte_rate = Stream_U32LE( File );
	block_align = Stream_I16LE( File );
	bits_per_sample = Stream_I16LE( File );
	if( bits_per_sample != 8 && bits_per_sample != 16 )
		{ error = "Unsupported number of bits per sample, expected 8 or 16"; goto invalid; }

	if( chunk_size >= 18 )
	{
		extension = Stream_I16LE( File );
		if( extension != 0 ){ error = "Extensions are not supported"; goto invalid; }
	}

	// Subchunk 2: 'data'
	if( !Stream_CheckBytes( File, "data", 4 ) ){ error = "Wrong chunk found, expected 'data'"; goto invalid; }
	data_size = Stream_U32LE( File );
	if( data_size > file_size - (uint32_t) File->Tell() )
		{ error = "Data chunk size bigger than actual - incomplete/damaged file"; goto invalid; }

	// everything checked, build the object
	wad = new WAVAudioData;
	wad->File = File;
	wad->DataOffset = File->Tell();
	wad->PCMSize = data_size;
	wad->BitsPerSample = bits_per_sample;
	wad->Channels = channel_count;
	wad->SampleRate = sample_rate;
	wad->DataPerSec = sample_rate * bits_per_sample * channel_count / 8;
	return wad;

invalid:
	if( error )
		fprintf( stderr, "Error loading file \"%s\": %s\n", file, error );
	delete File;
	return NULL;
}

/* OGG VORBIS */

struct OGGAudioData : IAudioData
{
	OGGAudioData() : File( NULL ){ memset( &ovFile, 0, sizeof( ovFile ) ); }
	~OGGAudioData()
	{
		if( File )
		{
			ov_clear( &ovFile );
			delete File;
		}
	}

	int32_t StreamIn( byte_t* out, int32_t max, int loop )
	{
		int32_t ret = 0;
		int section = 0;
		while( max )
		{
			int32_t read = ov_read( &ovFile, (char*) out, max, ISBIGENDIAN, BitsPerSample / 8, 1, &section );
			if( read < 0 )
				return 0;
			else if( read > 0 )
			{
				ret += read;
				max -= read;
				out += read;
			}
			else // read == 0, EOF
			{
				if( !loop )
					return ret;
				if( ov_pcm_seek( &ovFile, 0 ) != 0 )
					return -1;
			}
		}
		return ret;
	}

	void Seek( int32_t pos )
	{
		ov_pcm_seek( &ovFile, pos );
	}

	int32_t Tell()
	{
		return ov_pcm_tell( &ovFile );
	}

	int AtEnd()
	{
		return ov_pcm_tell( &ovFile ) == ov_pcm_total( &ovFile, -1 );
	}

	float Pos2Time( int32_t pos ){ return 0; }
	int32_t Time2Pos( float time ){ return 0; }
	
	SGStream* File;
	OggVorbis_File ovFile;
};

size_t ov_read_func( void* ptr, size_t size, size_t nmemb, void* datasource )
{
	SGStream* S = (SGStream*) datasource;
	return S->Read( (byte_t*) ptr, size * nmemb ) / size;
}
int	ov_seek_func( void* datasource, ogg_int64_t offset, int whence )
{
	SGStream* S = (SGStream*) datasource;
	return S->Seek( offset, whence ) ? 0 : -1;
}
long ov_tell_func( void* datasource )
{
	SGStream* S = (SGStream*) datasource;
	return S->Tell();
}

OGGAudioData* CreateOGGAudioData( SGDataSource* src, const char* file )
{
	int result;
	const char* error = NULL;
	OGGAudioData* oad;
	vorbis_info* I;
	SGStream* File = src->GetStream( file );
	ov_callbacks callbacks = { ov_read_func, ov_seek_func, NULL, ov_tell_func };
	if( !File ){ fprintf( stderr, "Could not load file: %s\n", file ); return NULL; }
	if( File->error > 0 ){ error = "File was not found"; goto invalid; }

	oad = new OGGAudioData;
	result = ov_open_callbacks( File, &oad->ovFile, NULL, 0, callbacks );
	if( result < 0 )
	{
		if( result == OV_EREAD ) error = "File read error";
		else if( result == OV_ENOTVORBIS ) error = "File does not contain Vorbis data (.ogg file without correctly encoded audio channels)";
		else if( result == OV_EVERSION ) error = "Vorbis version mismatch";
		else if( result == OV_EBADHEADER ) error = "Invalid Vorbis stream header";
		else if( result == OV_EFAULT ) error = "Internal logic fault";
		else error = "Unknown file read error";
		goto invalid2;
	}
	
	oad->File = File;
	I = ov_info( &oad->ovFile, -1 );
	if( I->channels != 1 && I->channels != 2 ){ error = "Unsupported number of channels, expected 1 or 2"; goto invalid2; }

	oad->BitsPerSample = 16;
	oad->Channels = I->channels;
	oad->PCMSize = ov_pcm_total( &oad->ovFile, -1 );
	oad->SampleRate = I->rate;
	return oad;

invalid2:
	if( error )
		fprintf( stderr, "Error loading file \"%s\": %s\n", file, error );
	delete oad;
	return NULL;
invalid:
	if( error )
		fprintf( stderr, "Error loading file \"%s\": %s\n", file, error );
	delete File;
	return NULL;
}

/*
	END
*/



SSEmitter::SSEmitter() : Source( 0 ), Type( 0 ), Volume( 1 ), Pitch( 1 ), System( 0 ),
StreamLoop( FALSE ), StreamPreserve( FALSE ), LastStreamPos( 0 )
{
}

SSEmitter::~SSEmitter()
{
	if( System )
		System->ReleaseEmitter( this );
}

SSEmitter::SSEmitter( const SSEmitter& e ) : Source( 0 ), Type( 0 ), Volume( 1 ), System( 0 ),
StreamLoop( FALSE ), StreamPreserve( FALSE ), LastStreamPos( 0 )
{
	*this = e;
}

const SSEmitter& SSEmitter::operator = ( const SSEmitter& e )
{
	if( System )
		System->ReleaseEmitter( this );
	if( e.System )
		e.System->SetupEmitter( e.Name.c_str(), this );
	// Don't copy params since they will probably be changed anyway...
	// If that situation changes, the code will be changed too.
	return *this;
}

void SSEmitter::Play()
{
	if( StreamSource )
	{
		StreamPreserve = TRUE;
		ALint state = 0;
		AL_CALL( alGetSourcei( Source, AL_SOURCE_STATE, &state ), 0 );
		if( state != AL_PAUSED )
		{
			alSourceStop( Source );
			StreamSource->Seek( 0 );
		}
		Update();
		AL_CALL( alSourcePlay( Source ), 0 );
	}
	else
	{
		AL_CALL( alSourcePlay( Source ), 0 );
	}
}

void SSEmitter::Stop()
{
	StreamPreserve = FALSE;
	AL_CALL( alSourceStop( Source ), 0 );
}

void SSEmitter::Pause()
{
	StreamPreserve = FALSE;
	AL_CALL( alSourcePause( Source ), 0 );
}

int SSEmitter::IsPlaying()
{
	ALint v = 0;
	AL_CALL( alGetSourcei( Source, AL_SOURCE_STATE, &v ), 0 );
	return v == AL_PLAYING;
}

void SSEmitter::SetLooping( int on )
{
	StreamLoop = on;
	AL_CALL( alSourcei( Source, AL_LOOPING, StreamSource ? FALSE : on ), 0 );
}

void SSEmitter::SetPlayOffset( float secs )
{
	if( StreamSource )
	{
		int play = IsPlaying();
		Stop();
		StreamSource->Seek( StreamSource->Time2Pos( secs ) );
		if( play )
			Play();
	}
	else
	{
		AL_CALL( alSourcef( Source, AL_SEC_OFFSET, secs ), 0 );
	}
}

float SSEmitter::GetPlayOffset()
{
	float time;
	AL_CALL( alGetSourcef( Source, AL_SEC_OFFSET, &time ), 0 );
	if( StreamSource )
		time += StreamSource->Pos2Time( LastStreamPos );
	return time;
}

void SSEmitter::Set3DMode( int on )
{
	AL_CALL( alSourcef( Source, AL_REFERENCE_DISTANCE, on ? 1.0f : 0.0f ), 0 );
	AL_CALL( alSourcei( Source, AL_SOURCE_RELATIVE, !on ), 0 );
	if( !on )
	{
		AL_CALL( alSource3f( Source, AL_POSITION, 0.0f, 0.0f, 0.0f ), 0 );
	}
}

void SSEmitter::SetDistanceFactor( float f )
{
	AL_CALL( alSourcef( Source, AL_REFERENCE_DISTANCE, f ), 0 );
}

void SSEmitter::SetPosition( float pos[3] )
{
	AL_CALL( alSourcefv( Source, AL_POSITION, pos ), 0 );
}

void SSEmitter::SetPanning( float pan )
{
	Set3DMode( FALSE );
	pan = MIN( 1, MAX( -1, pan ) );
	float pv[3] = { sinf( pan * PI ), 0, cosf( pan * PI ) };
	SetPosition( pv );
}

void SSEmitter::SetType( uint32_t ty )
{
	Type = ty;
	System->UpdateVolume( this );
	System->UpdatePitch( this );
}

void SSEmitter::SetVolume( float vol )
{
	Volume = vol;
	System->UpdateVolume( this );
}

void SSEmitter::SetPitch( float pitch )
{
	Pitch = pitch;
	System->UpdatePitch( this );
}

void SSEmitter::FadeVolume( float vol, float time )
{
	for( uint32_t i = 0; i < System->Faders.size(); ++i )
	{
		SSFader& f = System->Faders[ i ];
		if( f.Emitter == this )
		{
			// modify the current fader
			f.From = GetVolume();
			f.Target = vol;
			f.Time = 0;
			f.Length = time;
			return;
		}
	}

	// otherwise add a new one
	SSFader f;
	f.Emitter = this;
	f.From = GetVolume();
	f.Target = vol;
	f.Time = 0;
	f.Length = time;
	System->Faders.push_back( f );
}

int SSEmitter::Update()
{
	ALint proc = 0, que = 0;
	int active = FALSE;
	AL_CALL( alGetSourcei( Source, AL_BUFFERS_PROCESSED, &proc ), 0 );
	AL_CALL( alGetSourcei( Source, AL_BUFFERS_QUEUED, &que ), 0 );

	LastStreamPos = StreamSource ? StreamSource->Tell() : 0;

	if( proc + que == 0 && StreamPreserve )
	{
		int32_t read = Stream( Buffers[ 0 ] );
		active |= read;
		if( read ){ AL_CALL( alSourceQueueBuffers( Source, 1, Buffers ), 0 ); }
		read = Stream( Buffers[ 1 ] );
		active |= read;
		if( read ){ AL_CALL( alSourceQueueBuffers( Source, 1, Buffers + 1 ), 0 ); }
	}

	while( proc-- )
	{
		ALuint buf = 0;
		AL_CALL( alSourceUnqueueBuffers( Source, 1, &buf ), 0 );
		if( !buf )
			break;

		int32_t read = Stream( buf );
		active |= read;

		if( read )
		{
			AL_CALL( alSourceQueueBuffers( Source, 1, &buf ), 0 );
		}
	}
	
	if( StreamPreserve && active )
	{
		ALint v = 0;
		AL_CALL( alGetSourcei( Source, AL_SOURCE_STATE, &v ), 0 );
		if( v != AL_PLAYING )
		{
			AL_CALL( alSourcePlay( Source ), 0 );
		}
	}

	return active;
}

int32_t SSEmitter::Stream( ALuint buf )
{
	byte_t data[ STREAMBUF_SIZE ];
	
	int32_t size = StreamSource->StreamIn( data, STREAMBUF_SIZE, StreamLoop );
	if( size <= 0 )
		return FALSE;

	ALuint format = StreamSource->Channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	AL_CALL( alBufferData( buf, format, data, size, StreamSource->SampleRate ), 0 );
	return TRUE;
}

void SSEmitter::_Init( struct SSoundSystem* sys, IAudioData* stream )
{
	System = sys;
	Volume = 1;
	Pitch = 1;
	Type = 0;
	StreamSource = stream;
	alGenSources( 1, &Source );
	if( stream )
		alGenBuffers( 2, Buffers );
}

void SSEmitter::_Destroy()
{
	alDeleteSources( 1, &Source );
	if( StreamSource )
	{
		delete StreamSource;
		alDeleteBuffers( 2, Buffers );
	}
	StreamSource = NULL;
	System = NULL;
}



SSoundSystem::SSoundSystem() : Device( 0 ), Context( 0 ), Working( FALSE )
{
}

SSoundSystem::~SSoundSystem()
{
	Destroy();
}

int SSoundSystem::Init( SGDataSource* source, const char* DeviceName, int32_t Frequency, int32_t SyncFreq )
{
	if( DeviceName == NULL )
#ifdef _WIN32
		DeviceName = "Generic Software";
#else
		DeviceName = "OpenAL Soft";
#endif
	DataSource = source;
	Device = alcOpenDevice( DeviceName );
	ALCint attrs[ 5 ] = { ALC_FREQUENCY, Frequency, ALC_REFRESH, SyncFreq, ALC_INVALID };
	if( Device == NULL )
		goto SSI_Error;

	Context = alcCreateContext( Device, attrs );
	if( Context == NULL )
		goto SSI_Error;

	if( !alcMakeContextCurrent( Context ) )
		goto SSI_Error;

	ALC_CALL( alcProcessContext( Context ), Device, 0 );

	Working = TRUE;
	for( uint32_t i = 0; i < 33; ++i )
	{
		VolumeData[ i ] = 1;
		PitchData[ i ] = 1;
	}

	return TRUE;

SSI_Error:
	
	{
		char bfr[ 128 ];
		if( Context )
		{
			snprintf( bfr, 128, "alcMakeContextCurrent failed with error %d\n", alcGetError( Device ) );
			alcDestroyContext( Context );
		}
		else if( Device )
		{
			snprintf( bfr, 128, "alcCreateContext failed with error %d\n", alcGetError( Device ) );
			alcCloseDevice( Device );
		}
		else if( DeviceName ) snprintf( bfr, 128, "alcOpenDevice failed - device \"%s\" could not be opened\n", DeviceName );
		else snprintf( bfr, 128, "alcOpenDevice failed - default device could not be opened\n" );
	
		gSysInfo( bfr, "Sound system error" );
	}

	return FALSE;
}

void SSoundSystem::Destroy()
{
	if( Context )
	{
		alcMakeContextCurrent( Context );
		alcDestroyContext( Context );
		Context = NULL;
	}
	if( Device )
	{
		alcCloseDevice( Device );
		Device = NULL;
	}
	Working = FALSE;
}

void SSoundSystem::Tick( float Delta )
{
	if( !Working )
		return;
	
	for( uint32_t i = 0; i < Faders.size(); ++i )
	{
		SSFader& f = Faders[ i ];
		f.Time += Delta;
		float q = f.Time / f.Length;
		f.Emitter->SetVolume( LerpF( f.From, f.Target, MAX( MIN( 1, q ), 0 ) ) );
		if( f.Time >= f.Length )
		{
			f.Emitter->SetVolume( f.Target );
			Faders.erase( Faders.begin() + i );
			i--;
		}
	}
	
	for( size_t i = 0; i < Streaming.size(); ++i )
		Streaming[ i ]->Update();
}

int SSoundSystem::GetDevices( TString& devices )
{
	if( !alcGetString( NULL, ALC_DEFAULT_DEVICE_SPECIFIER ) )
		return FALSE;
	devices = alcGetString( NULL, ALC_DEVICE_SPECIFIER );
	return TRUE;
}

// Static WAV Buffers

ALuint SS_CreateBufferFromFile( SGDataSource* src, const char* file )
{
	IAudioData* data = CreateWAVAudioData( src, file );
	if( !data )
		return 0;
	
	byte_t* wavedata = new byte_t[ data->PCMSize ];
	if( data->StreamIn( wavedata, data->PCMSize, FALSE ) < 0 )
	{
		delete data;
		return 0;
	}
	
	ALuint buffer;
	AL_CALL( alGenBuffers( 1, &buffer ), 0 );
	ALenum format = ( data->BitsPerSample == 8 ) ? ( data->Channels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8 ) : 
		( data->Channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16 );
	AL_CALL( alBufferData( buffer, format, wavedata, data->PCMSize, data->SampleRate ), 0 );
	ALenum err = alGetError();
	if( err != AL_NO_ERROR )
		fprintf( stderr, "WAV load error: AL error in alBufferData (programmer error)\n" );

	delete [] wavedata;
	delete data;
	return buffer;
}

ALuint SS_CreateBuffer( const std::vector<float>& data, int sampleRate )
{
	int16_t* idata = new int16_t[ data.size() ];
	for( size_t i = 0; i < data.size(); ++i )
	{
		float v = data[ i ];
		if( v < -1 )
			v = -1;
		else if( v > 1 )
			v = 1;
		idata[ i ] = v * 32767;
	}
	
	ALuint buffer;
	AL_CALL( alGenBuffers( 1, &buffer ), 0 );
	AL_CALL( alBufferData( buffer, AL_FORMAT_MONO16, idata, data.size() * 2, sampleRate ), 0 );
	
	delete [] idata;
	return buffer;
}

ALuint GetBuffer( SGDataSource* src, BufNameMap& names, BufIDMap& ids, const TString& nn )
{
	BufNameMap::iterator n = names.find( nn );
	if( n != names.end() )
	{
		n->second->RefCount++;
		return n->second->Buffer;
	}
	
	ALuint b = SS_CreateBufferFromFile( src, nn.c_str() );

	SSBuffer* bf = new SSBuffer;
	bf->Name = nn;
	bf->Buffer = b;
	bf->RefCount = 1;
	names[ nn ] = bf;
	ids[ b ] = bf;
	return b;
}

void ReleaseBuffer( BufNameMap& names, BufIDMap& ids, ALuint buf )
{
	BufIDMap::iterator n = ids.find( buf );
	if( n != ids.end() )
	{
		n->second->RefCount--;
		if( n->second->RefCount > 0 )
			return;

		SSBuffer* b = n->second;
		names.erase( b->Name );
		ids.erase( b->Buffer );
		AL_CALL( alDeleteBuffers( 1, &b->Buffer ), 0 );
		delete b;
	}
	else fprintf( stderr, "An AL buffer with id %d is not found\n", buf );
}



int SSoundSystem::SetupEmitter( const char* sound, SSEmitter* e )
{
	int ret = TRUE;
	if( e->System )
	{
		ReleaseEmitter( e );
		ret = FALSE;
	}

	e->Name = sound;
	size_t off = e->Name.find_last_of( '.' ) + 1;
	TString ext = e->Name.substr( off, e->Name.size() - off );
	if( ext.size() != 3 )
	{
		return FALSE;
	}
	ext[0] = tolower( ext[0] );
	ext[1] = tolower( ext[1] );
	ext[2] = tolower( ext[2] );
	if( !strcmp( ext.c_str(), "wav" ) )
	{
		e->_Init( this, NULL );

		ALuint buf = GetBuffer( DataSource, Names, IDs, e->Name );
		AL_CALL( alSourcei( e->Source, AL_BUFFER, buf ), 0 );
	}
	else if( !strcmp( ext.c_str(), "ogg" ) )
	{
		OGGAudioData* oad = CreateOGGAudioData( DataSource, sound );
		if( !oad )
			fprintf( stderr, "Failed to load .ogg file: %s\n", sound );
		e->_Init( this, oad );

		Streaming.push_back( e );
	}
	else
		fprintf( stderr, "Unknown file format - file cannot be loaded - %s\n", sound );

	Emitters.push_back( e );

	return ret;
}

int SSoundSystem::SetupEmitter( const std::vector<float>& data, int sampleRate, SSEmitter* e )
{
	int ret = TRUE;
	if( e->System )
	{
		ReleaseEmitter( e );
		ret = FALSE;
	}
	
	e->Name = ":BUFFER";
	e->_Init( this, NULL );
	ALuint buf = SS_CreateBuffer( data, sampleRate );
	AL_CALL( alSourcei( e->Source, AL_BUFFER, buf ), 0 );
	Emitters.push_back( e );
	
	return ret;
}

void SSoundSystem::ReleaseEmitter( SSEmitter* e )
{
	if( e == NULL || e->System == NULL || e->System != this )
		fprintf( stderr, "Damaged Sound Emitter found or emitter is released twice...\n" );
	
	for( uint32_t i = 0; i < Faders.size(); ++i )
	{
		SSFader& f = Faders[ i ];
		if( f.Emitter == e )
		{
			Faders.erase( Faders.begin() + i );
			i--;
		}
	}

	if( e->StreamSource )
	{
		for( uint32_t i = 0; i < Streaming.size(); ++i )
		{
			if( Streaming[ i ] == e )
			{
				Streaming.erase( Streaming.begin() + i );
				break;
			}
		}
		e->_Destroy();
	}
	else
	{
		ALint bufid = 0;
		alGetSourcei( e->Source, AL_BUFFER, &bufid );
		e->_Destroy();
		if( e->Name == ":BUFFER" )
		{
			ALuint lol = bufid;
			AL_CALL( alDeleteBuffers( 1, &lol ), 0 );
		}
		else
		{
			ReleaseBuffer( Names, IDs, bufid );
		}
	}
	
	for( uint32_t i = 0; i < Emitters.size(); ++i )
	{
		if( Emitters[ i ] == e )
		{
			Emitters.erase( Emitters.begin() + i );
			break;
		}
	}
}

void SSoundSystem::SetVolume( float Volume, uint32_t Group )
{
	assert( Group < 33 );
	VolumeData[ Group ] = Volume;
	if( Group == 0 )
	{
		AL_CALL( alListenerf( AL_GAIN, Volume ), 0 );
	}
	else
	{
		uint32_t Flag = 0x00000001 << ( Group - 1 );
		for( uint32_t i = 0; i < Emitters.size(); ++i )
		{
			if( Emitters[ i ]->Type & Flag )
				UpdateVolume( Emitters[ i ] );
		}
	}
}

float SSoundSystem::GetVolume( uint32_t Group )
{
	return VolumeData[ Group ];
}

void SSoundSystem::SetPitch( float Pitch, uint32_t Group )
{
	assert( Group < 33 );
	PitchData[ Group ] = Pitch;
	if( Group == 0 )
		alListenerf( AL_PITCH, Pitch );
	else
	{
		uint32_t Flag = 0x00000001 << ( Group - 1 );
		for( uint32_t i = 0; i < Emitters.size(); ++i )
		{
			if( Emitters[ i ]->Type & Flag || !Group )
				UpdatePitch( Emitters[ i ] );
		}
	}
}

float SSoundSystem::GetPitch( uint32_t Group )
{
	return PitchData[ Group ];
}

void SSoundSystem::SetListenerPosition( float pos[3] )
{
	AL_CALL( alListenerfv( AL_POSITION, pos ), 0 );
}

void SSoundSystem::SetListenerDirection( float dir[3], float up[3] )
{
	float f[ 6 ];
	memcpy( f, dir, sizeof( float ) * 3 );
	memcpy( &f[ 3 ], up, sizeof( float ) * 3 );
	AL_CALL( alListenerfv( AL_ORIENTATION, f ), 0 );
}

void SSoundSystem::ChangeState( int Suspended )
{
	Working = !Suspended;
	if( Suspended )
	{
		ALC_CALL( alcSuspendContext( Context ), Device, 0 );
	}
	else
	{
		ALC_CALL( alcProcessContext( Context ), Device, 0 );
	}
}

void SSoundSystem::UpdateVolume( SSEmitter* e )
{
	float vol = e->Volume;
	for( uint32_t i = 0; i < 32; ++i )
	{
		uint32_t flag = 0x00000001 << i;
		if( flag & e->Type )
			vol *= VolumeData[ i + 1 ];
	}
	AL_CALL( alSourcef( e->Source, AL_GAIN, vol ), 0 );
}

void SSoundSystem::UpdatePitch( SSEmitter* e )
{
	float pitch = e->Pitch;
	for( uint32_t i = 0; i < 32; ++i )
	{
		uint32_t flag = 0x00000001 << i;
		if( flag & e->Type )
			pitch *= PitchData[ i + 1 ];
	}
	pitch *= PitchData[ 0 ]; // <<
	AL_CALL( alSourcef( e->Source, AL_PITCH, pitch ), 0 );
}

