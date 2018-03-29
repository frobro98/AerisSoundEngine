
#include "System.h"

using namespace Aer;
using namespace Aer::SoundEngine;

//////////////////////////////////////////////////////////////////////////
// Main Sound Engine Functions
//////////////////////////////////////////////////////////////////////////

void Aer::SoundEngine::Initialize(const AerEngineSettings& initSettings)
{
	CoInitializeEx(nullptr, 0);

	InternalSystem::Init(initSettings);
}

void Aer::SoundEngine::Terminate()
{
	InternalSystem::Term();
	CoUninitialize();
}

void Aer::SoundEngine::GetDefaultInitSettings(AerEngineSettings& settings)
{
	settings;
}

//////////////////////////////////////////////////////////////////////////
// Internal System class to which Aer::SoundEngine functions talk
//////////////////////////////////////////////////////////////////////////

InternalSystem* InternalSystem::isInstance = nullptr;

void InternalSystem::Init(const AerEngineSettings& initSettings)
{
	instance().InitInternal(initSettings);
}

void InternalSystem::InitInternal(const AerEngineSettings& initSettings)
{
	UNUSED(initSettings);

	HRESULT hr;
	UInt32 flags = 0;
#if (_WIN32_WINNT < 0x0602 /*Windows 8*/) && defined(_DEBUG)
	flags |= XAUDIO2_DEBUG_ENGINE;
#endif

	hr = XAudio2Create(&pSndEngine, flags, XAUDIO2_DEFAULT_PROCESSOR);

	if (FAILED(hr))
	{
		// Error handling
	}

	hr = pSndEngine->CreateMasteringVoice(&masteringVoice);

	if (FAILED(hr))
	{
		// Error handling
	}
}

void InternalSystem::Term()
{
	instance().pSndEngine->Release();
}

IXAudio2* InternalSystem::GetSoundEngineInstance()
{
	return instance().pSndEngine;
}

InternalSystem& InternalSystem::instance()
{
	if (isInstance == nullptr)
	{
		isInstance = new InternalSystem();
	}

	return *isInstance;
}
