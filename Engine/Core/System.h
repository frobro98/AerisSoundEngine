#pragma once

#include "CoreDefs.h"

struct AerEngineSettings
{

};


namespace Aer
{
	class Sound;

	namespace SoundEngine
	{

		void Initialize(const AerEngineSettings& initSettings);
		void Terminate();

		void GetDefaultInitSettings(AerEngineSettings& settings);
	}
}

class InternalSystem
{
public:
	static void Init(const AerEngineSettings& initSettings);
	static void Term();

	static IXAudio2* GetSoundEngineInstance();

private:
	// There has to be a better way of going about this
	friend class XAudio2Sound;

	IXAudio2* pSndEngine;
	IXAudio2MasteringVoice* masteringVoice;


	void InitInternal(const AerEngineSettings& initSettings);

	static InternalSystem* isInstance;
	static InternalSystem& instance();
};