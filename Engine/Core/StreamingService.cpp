
#include "StreamingService.h"
#include "XAudio2Stream.h"
#include "Music.h"
#include "Thread.h"
#include "MusicStreamer.h"

#include "../FileManager/FileManager.h"

static const UInt32 ByteSubmissionAmount = 2048;
static const UInt32 TotalInitialPushes = 3;

StreamService::StreamService(AerMusicStreamer* streamManager, Aer::Music* mus, FileHandle fHnd)
	: streamer(streamManager), musicRef(mus), loader(this, fHnd),
	LastBuffer(FALSE)
{
}

StreamService::~StreamService()
{
}

void StreamService::operator()()
{
	Thread loadThread("Loader");
	loadThread.startThread(std::ref(loader));

	currentBuffer = &streamBufferA;

	UInt32 bufferOffset = 0;
	loader.ReadyForData();
	InitialDataMove(bufferOffset);
	StartProcessing();

	while (IsStreaming())
	{
		coordCV.wait(lock);

		StreamBuffer* currBuff = GetActiveBuffer();
		
		musicRef->PushData(currBuff, ByteSubmissionAmount, bufferOffset);

		bufferOffset += ByteSubmissionAmount;

		if (bufferOffset >= currBuff->numBytesInBuffer)
		{
			if (LastBuffer)
			{
				musicRef->StopProcessing();
				SetStreaming(FALSE);
			}
			currBuff->hasData = FALSE;
			SwapActiveBuffer();
			bufferOffset = 0;
			loader.ReadyForData();
		}
	}

	loadThread.join();

	streamer->StreamEnded(this);
}

void StreamService::StartProcessing()
{
	isStreaming = TRUE;
	musicRef->BeginProcessing();
}

void StreamService::InitialDataMove(UInt32& offset)
{
	coordCV.wait(lock);

	StreamBuffer* currBuff = GetActiveBuffer();

	for (int i = 0; i < TotalInitialPushes; ++i)
	{
		musicRef->PushData(currBuff, ByteSubmissionAmount, offset);
		offset += ByteSubmissionAmount;
	}

}

void StreamService::FillEmptyBuffer(const StreamBuffer& buffer)
{
	StreamBuffer* emptyBuff = EmptyBuffer();
	AerAssert(emptyBuff != nullptr);
	*emptyBuff = buffer;
}

void StreamService::BufferFinished()
{
	coordCV.signal();
}

void StreamService::StreamFinished()
{
	SetStreaming(FALSE);

}

StreamBuffer* StreamService::EmptyBuffer()
{
	StreamBuffer* emptyBuff = nullptr;

	if (!streamBufferA.hasData)
	{
		emptyBuff = &streamBufferA;
	}
	else if (!streamBufferB.hasData)
	{
		emptyBuff = &streamBufferB;
	}

	return emptyBuff;
}

StreamBuffer* StreamService::GetActiveBuffer()
{
	AerScopedLock scopeLock;
	return currentBuffer;
}

void StreamService::SwapActiveBuffer()
{
	AerScopedLock scopeLock;
	if (currentBuffer == &streamBufferA)
	{
		currentBuffer = &streamBufferB;
	}
	else if (currentBuffer == &streamBufferB)
	{
		currentBuffer = &streamBufferA;
	}

}

//////////////////////////////////////////////////////////////////////////
// Stream Service overloaded operators
//////////////////////////////////////////////////////////////////////////

Bool StreamService::operator==(const StreamService& other) const
{
	return musicRef->GetID() == other.musicRef->GetID();
}

Bool StreamService::operator==(MusicID musID) const
{
	return (*musicRef) == musID;
}

//////////////////////////////////////////////////////////////////////////
// StreamLoader definitions
//////////////////////////////////////////////////////////////////////////

void StreamService::StreamLoader::InitialRead()
{
	cv.wait(lock);

	LoadNextChunk();
	coordinator->FillEmptyBuffer(loadBuffer);
	LoadNextChunk();
	coordinator->FillEmptyBuffer(loadBuffer);
	// Signals coord thread to do work
	coordinator->BufferFinished();
}

void StreamService::StreamLoader::ReadChunksOnDisk()
{
	while (coordinator->IsStreaming())
	{
		cv.wait(lock);

		coordinator->FillEmptyBuffer(loadBuffer);
		Bool eof = LoadNextChunk();
		if (eof)
		{
			break;
		}
	}

	coordinator->LastBuffer = TRUE;
}

Bool StreamService::StreamLoader::LoadNextChunk()
{
	Byte* buff = loadBuffer.streamBuff;
	ASEFileManager::Read(fHandle, buff, StreamBuffer::StreamBufferSize, loadBuffer.numBytesInBuffer);
	return loadBuffer.numBytesInBuffer <= 0;
}

void StreamService::StreamLoader::ReadyForData()
{
	cv.signal();
}