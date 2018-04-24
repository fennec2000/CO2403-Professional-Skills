// CAudio.cpp 24-04-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

// Allocates memory for the static pointers
ALCcontext* CAudio::context = nullptr;
ALCdevice* CAudio::device = nullptr;

CAudio::CAudio(ALbyte* fileName, bool loopAudio)
{
	if (context == nullptr)
	{
		InitAudio();
	}

	// Sets up the source with some hardcoded default variables for now
	// untill we need to change them
	alGenSources((ALuint)1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(source, AL_LOOPING, loopAudio);

	// Generates a buffer for this sound
	alGenBuffers((ALuint)1, &buffer);

	// loads the audio stream into the buffer
	ALsizei size, freq;
	ALenum format;
	ALvoid* data;
	ALboolean loop = AL_FALSE;
	alutLoadWAVFile(fileName, &format, &data, &size, &freq, &loop);

	// Binds the source to a buffer
	alBufferData(buffer, format, data, size, freq);
	alSourcei(source, AL_BUFFER, buffer);
}

CAudio::~CAudio()
{
	// Cleanup
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void CAudio::Play()
{
	// Plays the sound source
	alSourcePlay(source);
}

void CAudio::Stop()
{
	// Stops the sound source
	alSourceStop(source);
}

bool CAudio::InitAudio()
{
	// Initialization
	device = alcOpenDevice(NULL); // select the "preferred device"
	if (!device)
	{
		// Put error handling here
		return false;
	}

	// Checks if the runtime AL supports device enumeration
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration != AL_FALSE)
	{
		// Enumeration is supported

	}

	// Creates the context
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
	{
		// Failed to make context current
		printf("Failed to make context current");
		return false;
	}

	// Sets up a listener
	ALfloat listernerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0.0f, 0.0f, 1.0f);
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, listernerOri);

	return true;
}