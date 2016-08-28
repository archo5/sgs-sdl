
#pragma once

#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include <AL/al.h>
#include <AL/alc.h>

typedef unsigned char byte_t;
typedef std::string TString;
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
template< class T > T TCLAMP( const T& v, const T& min, const T& max ){ return MIN( MAX( v, min ), max ); }
#define ISBIGENDIAN 0
#define TRUE 1
#define FALSE 0
#define PI 3.14159265358979323846


struct SGStream
{
	virtual ~SGStream(){}
	virtual int32_t Read( void* to, int32_t max ) = 0;
	virtual int Seek( int32_t pos, int mode = SEEK_SET ) = 0;
	virtual int32_t Tell() = 0;
	virtual int32_t GetSize() = 0;
	byte_t GetChar()
	{
		byte_t b = 0;
		Read( &b, 1 );
		return b;
	}
	int error;
};

struct SGDataSource
{
	virtual ~SGDataSource(){}
	virtual SGStream* GetStream( const char* filename ) = 0;
};



#ifndef AL_AL_H
typedef unsigned int ALuint;
#endif
#ifndef AL_ALC_H
typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;
#endif


struct SSBuffer
{
	TString Name;
	ALuint Buffer;
	int RefCount;
};
typedef std::map< TString, SSBuffer* > BufNameMap;
typedef std::map< ALuint, SSBuffer* > BufIDMap;


struct SSFader
{
	struct SSEmitter* Emitter;
	float From;
	float Target;
	float Time;
	float Length;
};
typedef std::vector< SSFader > SSFaderMap;


struct IAudioData
{
	int32_t BitsPerSample, Channels, SampleRate, PCMSize;

	virtual ~IAudioData(){}
	virtual int32_t StreamIn( byte_t* out, int32_t max, int loop )=0;
	virtual void Seek( int32_t pos )=0;
	virtual int32_t Tell()=0;
	virtual int AtEnd()=0;
	virtual float Pos2Time( int32_t pos )=0;
	virtual int32_t Time2Pos( float time )=0;
};


struct SSEmitter
{
	SSEmitter();
	~SSEmitter();

	SSEmitter( const SSEmitter& e );
	const SSEmitter& operator = ( const SSEmitter& e );

	void Play();
	void Stop();
	void Pause();
	int IsPlaying();

	void SetLooping( int on );
	void SetPlayOffset( float secs );
	float GetPlayOffset();

	void Set3DMode( int on );
	void SetDistanceFactor( float f );
	void SetPosition( float pos[3] );
	void SetPanning( float pan );

	void SetType( uint32_t ty );
	uint32_t GetType(){ return Type; }
	void SetVolume( float vol );
	float GetVolume(){ return Volume; }
	void SetPitch( float pitch );
	float GetPitch(){ return Pitch; }
	void FadeVolume( float vol, float time );

	void _Init( struct SSoundSystem* sys, IAudioData* stream );
	void _Destroy();
	
	// INTERNAL
	TString Name;
	float Volume, Pitch;
	uint32_t Type;

	ALuint Source;
	struct SSoundSystem* System;
	
	// streaming
	IAudioData* StreamSource;
	ALuint Buffers[ 2 ];

	int StreamLoop;
	int StreamPreserve;
	int32_t LastStreamPos;

	int Update();
	int32_t Stream( ALuint buf );
};
typedef std::vector< SSEmitter* > SSEmitterVec;


struct SSoundSystem
{
	SSoundSystem();
	~SSoundSystem();

	int Init( SGDataSource* source, const char* DeviceName = NULL, int32_t Frequency = 44100, int32_t SyncFreq = 30 );
	void Destroy();
	void Tick( float Delta );

	static int GetDevices( TString& devices );

	int SetupEmitter( const char* sound, SSEmitter* e );
	int SetupEmitter( const std::vector<float>& data, int sampleRate, SSEmitter* e );
	void ReleaseEmitter( SSEmitter* e );

	void SetVolume( float Volume, uint32_t Group );
	float GetVolume( uint32_t Group );
	void SetPitch( float Pitch, uint32_t Group );
	float GetPitch( uint32_t Group );

	void SetListenerPosition( float pos[3] );
	void SetListenerDirection( float dir[3], float up[3] );

	void ChangeState( int suspended );

	// INTERNAL
	void UpdateVolume( SSEmitter* e );
	void UpdatePitch( SSEmitter* e );

	int Working;
	BufNameMap Names;
	BufIDMap IDs;
	
	SSFaderMap Faders;

	float VolumeData[ 33 ];
	float PitchData[ 33 ];
	SSEmitterVec Emitters;
	SSEmitterVec Streaming;
	
	ALCdevice* Device;
	ALCcontext* Context;
	SGDataSource* DataSource;
};

