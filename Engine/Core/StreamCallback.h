#pragma once

#include "WindowsModule.h"
#include "CoreDefs.h"

class XAudio2Stream;

class StreamCallback : public IXAudio2VoiceCallback
{
public:
	StreamCallback(XAudio2Stream* stream);
	~StreamCallback();

	//Called when the voice has just finished playing a contiguous audio stream.
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext);
	STDMETHOD_(void, OnStreamEnd) (THIS);

	//Unused methods are stubs
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {}
	STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired)
	{
		UNUSED(BytesRequired);
	}
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext)
	{
		UNUSED(pBufferContext);
	}
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext)
	{
		UNUSED(pBufferContext);
	}
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error)
	{
		UNUSED(pBufferContext, Error);
	}

private:
	XAudio2Stream* xa2Stream;
};