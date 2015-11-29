
#include "StreamCallback.h"
#include "XAudio2Stream.h"

void StreamCallback::OnBufferEnd(THIS_ void* pBufferContext)
{
	UNUSED(pBufferContext);
	xa2Stream->BufferFinished();
}

void StreamCallback::OnStreamEnd()
{
	xa2Stream->StreamFinished();
}

StreamCallback::StreamCallback(XAudio2Stream* stream)
	: xa2Stream(stream)
{
}

StreamCallback::~StreamCallback()
{
}

