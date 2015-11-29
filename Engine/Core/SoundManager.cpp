
#include "SoundManager.h"
#include "XAudio2Sound.h"
#include "AudioDataManager.h"
#include "EffectsManager.h"
#include "fnv.h"
//////////////////////////////////////////////////////////////////////////
// Methods that create the sound object
//////////////////////////////////////////////////////////////////////////

AER_DEFINE_INSTANCE(SoundManager);

Aer::Sound* SoundManager::CreateSound(const TChar* filename, const TChar* soundName)
{
	XAudio2Sound* xa2snd = AudioDataManager::ParseAudioData(filename);

	Aer::Sound* snd = new Aer::Sound(soundName, xa2snd);
	//snd->SetupAudioData(config->wfx, config->xa2buff);
	instance().soundList.AddToFront(snd);

	return snd;
}

Aer::Sound* SoundManager::CreateSound(const TChar* filename, const TChar* soundName, Aer::SimpleReverbDescription& reverbDesc)
{
	AerEffect* effect = EffectsManager::CreateEffect(reverbDesc);
	XAudio2Sound* xa2snd = AudioDataManager::ParseAudioData(filename);
	xa2snd->AttachEffect(effect);

	Aer::Sound* snd = new Aer::Sound(soundName, xa2snd);
	instance().soundList.AddToFront(snd);

	return snd;
}

Aer::Sound* SoundManager::CreateSound(const TChar* filename, const TChar* soundName, Aer::ReverbDescription& reverbDesc)
{
	AerEffect* effect = EffectsManager::CreateEffect(reverbDesc);
	XAudio2Sound* xa2snd = AudioDataManager::ParseAudioData(filename);
	xa2snd->AttachEffect(effect);

	Aer::Sound* snd = new Aer::Sound(soundName, xa2snd);
	instance().soundList.AddToFront(snd);

	return snd;
}

Aer::Sound* SoundManager::CreateSound(const TChar* filename, const TChar* soundName, Aer::EchoDescription& echoDesc)
{
	AerEffect* effect = EffectsManager::CreateEffect(echoDesc);
	XAudio2Sound* xa2snd = AudioDataManager::ParseAudioData(filename);
	xa2snd->AttachEffect(effect);

	Aer::Sound* snd = new Aer::Sound(soundName, xa2snd);
	instance().soundList.AddToFront(snd);

	return snd;
}

Aer::Sound* SoundManager::FindSound(SoundID soundID)
{
	Aer::Sound* snd = instance().soundList.Find(soundID);
	return snd;
}

//////////////////////////////////////////////////////////////////////////
// SoundManager internal methods
//////////////////////////////////////////////////////////////////////////

SoundManager::SoundManager()
{
	//soundList.reserve(10);
}

SoundManager::~SoundManager()
{
	while (!soundList.Empty())
	{
		soundList.RemoveFront();
		/*Aer::Sound* snd = soundList.back();
		soundList.pop_back();
		delete snd;*/
	}
}