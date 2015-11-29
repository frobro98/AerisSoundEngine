#pragma once

#include "AudioFormat.h"

#define NO_CALLBACK nullptr

class AerEffect;
class OSInternalBus;
struct StreamBuffer;

class OSInternalSound
{
public:

	virtual void PushData(const StreamBuffer* updatedData, UInt32 numBytesToPush, UInt32 offset, Bool endOfStream)
	{
		UNUSED(updatedData, numBytesToPush, offset, endOfStream);
	}
	virtual void SubmitAudioData() = 0;
	virtual void StartAudioProcessing() = 0;
	virtual void StopAudioProcessing() = 0;
	virtual void ClearAudioBuffers() = 0;
	virtual void ResetAudioBuffer() = 0;
	virtual void SeekPosition(Float ms) = 0;
	
	virtual void AttachEffect(AerEffect* effect) = 0;
	virtual void EnableSoundEffects() = 0;
	virtual void DisableAttachedEffects() = 0;

	AudioFormat GetSoundFormat() const
	{
		return rawData->format;
	}

	virtual void ConnectBus(OSInternalBus* otherBus) = 0;

	virtual OSSound* GetNativeSound() = 0;

	Bool IsPlaying() const;

	const AudioPacket* getAudioData() const
	{
		return rawData;
	}

protected:
	OSInternalSound(AudioPacket* audioDataPacket);
	OSInternalSound(const AudioFormat& fmt);
	virtual ~OSInternalSound();

	AudioPacket* rawData;
	UInt32 effectCount;
	Bool isPlaying;

};