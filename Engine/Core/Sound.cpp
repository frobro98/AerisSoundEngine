
#include "../FileManager/FileManager.h"
#include "../FileManager/FileConfig.h"
#include "SoundManager.h"
#include "System.h"
#include "XAudio2Sound.h"
#include "fnv.h"

namespace Aer
{
	//////////////////////////////////////////////////////////////////////////
	// Called to actually create a sound
	//////////////////////////////////////////////////////////////////////////

	Handle* CreateSound(const TChar* const filename, const TChar* soundName)
	{
		Sound* sndRef = SoundManager::CreateSound(filename, soundName);
		Handle* sndHdl = new SoundHandle(sndRef);
		return sndHdl;
	}

	Handle* CreateSound(const TChar* const filename, const TChar* soundName, Aer::SimpleReverbDescription& reverbDesc)
	{
		Sound* sndRef = SoundManager::CreateSound(filename, soundName, reverbDesc);
		Handle* sndHdl = new SoundHandle(sndRef);
		return sndHdl;
	}
	Handle* CreateSound(const TChar* const filename, const TChar* soundName, Aer::ReverbDescription& reverbDesc)
	{
		Sound* sndRef = SoundManager::CreateSound(filename, soundName, reverbDesc);
		Handle* sndHdl = new SoundHandle(sndRef);
		return sndHdl;
	}

	Handle* CreateSound(const TChar* const filename, const TChar* soundName, Aer::EchoDescription& echoDesc)
	{
		Sound* sndRef = SoundManager::CreateSound(filename, soundName, echoDesc);
		Handle* sndHdl = new SoundHandle(sndRef);
		return sndHdl;
	}



	//////////////////////////////////////////////////////////////////////////
	// Sound methods
	//////////////////////////////////////////////////////////////////////////

	void Sound::Play()
	{
		//hardwareSnd->SubmitAudioData();
		hardwareSnd->StartAudioProcessing();
	}

	void Sound::Pause()
	{
		hardwareSnd->StopAudioProcessing();
	}

	void Sound::Stop()
	{
		hardwareSnd->StopAudioProcessing();
		hardwareSnd->ResetAudioBuffer();
	}

	void Sound::Seek(Float ms)
	{
		hardwareSnd->SeekPosition(ms);
	}

	void Sound::Reset()
	{
		hardwareSnd->ResetAudioBuffer();
	}

	OSInternalSound* Sound::GetInternalSound()
	{
		return hardwareSnd;
	}

	Sound::Sound(const TChar* soundName, XAudio2Sound* snd)
		: name(soundName), hardwareSnd(snd)
	{
		soundID = fnvHash(soundName);
		hardwareSnd->SubmitAudioData();
	}

	Sound::~Sound()
	{

	}
}