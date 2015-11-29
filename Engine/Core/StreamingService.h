#pragma once

#include "CoreDefs.h"
#include "AerCondVar.h"

namespace Aer
{
	class Music;
}

class AerMusicStreamer;

struct StreamBuffer
{
	// Size of stream chunk
	static const UInt32 StreamBufferSize = 8192;
	UInt32 numBytesInBuffer;
	Bool hasData;
	Byte* streamBuff;

	StreamBuffer()
		: numBytesInBuffer(0),
		hasData(FALSE)
	{
		streamBuff = new Byte[StreamBufferSize];
	}

	StreamBuffer(const StreamBuffer& buff)
		: hasData(TRUE), 
		numBytesInBuffer(buff.numBytesInBuffer)
	{
		memcpy(streamBuff, buff.streamBuff, buff.numBytesInBuffer);
	}

	StreamBuffer& operator=(const StreamBuffer& other)
	{
		if (this != &other)
		{
			hasData = TRUE;
			numBytesInBuffer = other.numBytesInBuffer;
			memcpy(streamBuff, other.streamBuff, other.numBytesInBuffer);
		}

		return *this;

	}
};

class StreamService
{
public:
	StreamService(AerMusicStreamer* streamManager, Aer::Music* mus, FileHandle fHnd);
	~StreamService();

	void InitialDataMove(UInt32& offset);
	void FillEmptyBuffer(const StreamBuffer& buffer);

	StreamBuffer* GetActiveBuffer();
	void SwapActiveBuffer();
	StreamBuffer* EmptyBuffer();
	
	void SetStreaming(Bool streaming)
	{ 
		AerScopedLock scopeLock;
		isStreaming = streaming; 
	}
	Bool IsStreaming() const
	{ 
		AerScopedLock scopeLock;
		return isStreaming; 
	}
	void StartProcessing();
	void BufferFinished();

	void StreamFinished();

	void operator()();
	Bool operator==(const StreamService& otherService) const;
	Bool operator==(MusicID musID) const;

private:
	struct StreamLoader
	{
		void operator()()
		{
			InitialRead();
			ReadChunksOnDisk();
		}
		
		void InitialRead();
		void ReadChunksOnDisk();

		// Return something to signal EOF
		Bool LoadNextChunk();

		void ReadyForData();

		AerCondVar cv;
		AerLock lock;

		StreamBuffer loadBuffer;

		StreamService* coordinator;

		FileHandle fHandle;

		StreamLoader(StreamService* coord, FileHandle fHnd)
			: coordinator(coord), fHandle(fHnd)
		{
		}
	};

	AerCondVar coordCV;
	AerLock lock;

	// Object that will do all of the file reading and 
	// loading for the streaming system
	StreamLoader loader;
	// First read buffer for sound data
	StreamBuffer streamBufferA;
	// Second read buffer for sound data
	StreamBuffer streamBufferB;
	// Pointer to the current buffer
	StreamBuffer* currentBuffer;

	AerMusicStreamer* streamer;

	Aer::Music* musicRef;

	Bool isStreaming;
	Bool LastBuffer;
};