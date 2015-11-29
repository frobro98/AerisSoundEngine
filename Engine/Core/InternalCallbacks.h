#pragma once

#include "CoreDefs.h"

#ifdef _WIN32

class WinVoiceCallback : IXAudio2VoiceCallback
{
public:
	WinVoiceCallback();
	~WinVoiceCallback();

	virtual void _stdcall OnBufferStart(THIS_ void* pBufferContext) override;
	virtual void _stdcall OnBufferEnd(THIS_ void* pBufferContext) override;

	virtual void _stdcall OnVoiceProcessingPassStart(THIS_ UINT32 BytesRequired) override;
	virtual void _stdcall OnVoiceProcessingPassEnd(THIS) override;
	
	virtual void _stdcall OnVoiceError(THIS_ void* pBufferContext, HRESULT Error) override;

	virtual void _stdcall OnLoopEnd(THIS_ void* pBufferContext) override;
	virtual void _stdcall OnStreamEnd(THIS) override;
};

class AerisCallback : IXAudio2EngineCallback
{
public:
	AerisCallback();

	virtual void _stdcall OnProcessingPassStart() override;
	virtual void _stdcall OnProcessingPassEnd() override;

	virtual void _stdcall OnCriticalError(HRESULT Error) override;
};

#endif