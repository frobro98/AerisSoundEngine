#pragma once

#include "OSInternalSound.h"

class XAudio2Sound : public OSInternalSound
{
public:
	XAudio2Sound(AudioPacket* audioDataPacket, const TChar* filename);
	XAudio2Sound(AudioPacket* audioDataPacket, AerEffect* effect, const TChar* filename, UInt32 effectCount = 1);
	~XAudio2Sound();

	virtual void SubmitAudioData() override;
	virtual void StartAudioProcessing() override;
	virtual void StopAudioProcessing() override;
	virtual void ClearAudioBuffers() override;
	virtual void ResetAudioBuffer() override;
	virtual void SeekPosition(Float ms) override;

	virtual void AttachEffect(AerEffect* effect) override;
	virtual void EnableSoundEffects() override;
	virtual void DisableAttachedEffects() override;

	virtual void ConnectBus(OSInternalBus* otherBus) override;
	virtual OSSound* GetNativeSound() override;

private:
	IXAudio2SourceVoice* sourceVoice;

};