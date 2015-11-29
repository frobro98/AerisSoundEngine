

#include "InternalCallbacks.h"

//////////////////////////////////////////////////////////////////////////
//	Windows Callback
//////////////////////////////////////////////////////////////////////////

WinVoiceCallback::WinVoiceCallback()
{

}

WinVoiceCallback::~WinVoiceCallback()
{

}

void WinVoiceCallback::OnBufferStart(THIS_ void* pBufferContext)
{
	UNUSED(pBufferContext);
}

void WinVoiceCallback::OnBufferEnd(THIS_ void* pBufferContext)
{
	UNUSED(pBufferContext);
}

void WinVoiceCallback::OnVoiceProcessingPassStart(THIS_ UINT32 BytesRequired)
{
	UNUSED(BytesRequired);
}

void WinVoiceCallback::OnVoiceProcessingPassEnd(THIS)
{

}

void WinVoiceCallback::OnVoiceError(THIS_ void* pBufferContext, HRESULT Error)
{
	UNUSED(pBufferContext, Error);
}

void WinVoiceCallback::OnLoopEnd(THIS_ void* pBufferContext)
{
	UNUSED(pBufferContext);
}

void WinVoiceCallback::OnStreamEnd(THIS)
{

}

//////////////////////////////////////////////////////////////////////////
//	Aeris Engine Callback
//////////////////////////////////////////////////////////////////////////

AerisCallback::AerisCallback()
{

}

void AerisCallback::OnCriticalError(HRESULT Error)
{
	AerAssert(FALSE);
	UNUSED(Error);
}

void AerisCallback::OnProcessingPassStart()
{

}

void AerisCallback::OnProcessingPassEnd()
{

}