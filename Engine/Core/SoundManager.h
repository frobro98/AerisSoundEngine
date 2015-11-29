#pragma once

#include "CoreDefs.h"
#include "Sound.h"
#include "EffectsDefinitions.h"
#include "AerList.h"

class SoundManager
{
public:
	AER_SINGLETON(SoundManager);

	static Aer::Sound* CreateSound(const TChar* filename, const TChar* soundName);
	static Aer::Sound* CreateSound(const TChar* filename, const TChar* soundName, Aer::SimpleReverbDescription& reverbDesc);
	static Aer::Sound* CreateSound(const TChar* filename, const TChar* soundName, Aer::ReverbDescription& reverbDesc);
	static Aer::Sound* CreateSound(const TChar* filename, const TChar* soundName, Aer::EchoDescription& echoDesc);

	static Aer::Sound* FindSound(SoundID soundID);

private:
	AerList<Aer::Sound*> soundList;
};