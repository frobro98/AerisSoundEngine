#pragma once

#include "Handles.h"
#include "EffectsDefinitions.h"

class XAudio2Sound;
class AerReverb;
class AerSimpleReverb;
class OSInternalSound;

namespace Aer
{
	// Creates and returns a handle to a sound with no added effects
	Handle* CreateSound(const TChar* const filename, const TChar* soundName);

	// Creates and returns a handle to a sound with a reverb effect(s) to it
	Handle* CreateSound(const TChar* const filename, const TChar* soundName, Aer::SimpleReverbDescription& reverbDesc);
	Handle* CreateSound(const TChar* const filename, const TChar* soundName, Aer::ReverbDescription& reverbDesc);
	Handle* CreateSound(const TChar* const filename, const TChar* soundName, Aer::EchoDescription& echoDesc);

	class Sound
	{
	public:
		void Play();
		void Stop();
		void Pause();
		void Reset();
		void Seek(Float ms);

		OSInternalSound* GetInternalSound();

		Sound(const TChar* soundName, XAudio2Sound* snd);
		~Sound();

		Sound(const Sound&) = delete;
		Sound& operator=(const Sound&) = delete;

		bool operator==(Sound& snd)
		{
			return soundID == snd.soundID;
		}
		bool operator==(SoundID sndID)
		{
			return soundID == sndID;
		}

	protected:
#ifdef _WIN32
		XAudio2Sound* hardwareSnd;
#endif
		const TChar* name;
		SoundID soundID;

		Bool isPlaying;
	};

}