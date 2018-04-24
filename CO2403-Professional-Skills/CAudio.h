// CAudio.h 24-04-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

class CAudio
{
public:
	CAudio(ALbyte* fileName, bool loopAudio = false);
	~CAudio();

	void Play();
	void Stop();

private:
	bool InitAudio();

	static ALCdevice* device;
	static ALCcontext* context;

	ALuint source;
	ALuint buffer;
};