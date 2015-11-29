#pragma once

#include "AerList.h"
#include "OSInternalSound.h"
#include "StreamCallback.h"

namespace Aer
{
	class Music;
}

struct StreamBuffer;
class StreamService;

struct StreamingData
{
	Byte* streamData;
	UInt32 dataSize;

	StreamingData(Byte* dataBuffer, UInt32 size)
		: dataSize(size)
	{
		streamData = new Byte[dataSize];
		memcpy(streamData, dataBuffer, dataSize);
	}
};

class XAudio2Stream : public OSInternalSound
{
public:
	XAudio2Stream(AudioFormat audioDataPacket);
	~XAudio2Stream();

	virtual void PushData(const StreamBuffer* updatedData, UInt32 numBytesToPush, UInt32 offset, Bool endOfStream) override;
	virtual void SeekPosition(Float ms) override;
	virtual void StartAudioProcessing() override;
	virtual void StopAudioProcessing() override;

	virtual void SubmitAudioData() override{}
	virtual void ClearAudioBuffers() override{}
	virtual void ResetAudioBuffer() override{}

	virtual void AttachEffect(AerEffect* effect) override;
	virtual void EnableSoundEffects() override;
	virtual void DisableAttachedEffects() override;

	virtual void ConnectBus(OSInternalBus* otherBus) override;
	virtual OSSound* GetNativeSound() override;

	void SetMusicRef(Aer::Music* mus);
	void BufferFinished();
	void StreamFinished();
private:
	typedef AerList<StreamingData*> DataQueue;
	DataQueue bufferQueue;
	StreamCallback callback;
	UInt32 dataBufferIndex;

	StreamService* streamer;
	Aer::Music* musRef;
	IXAudio2SourceVoice* sourceVoice;
};