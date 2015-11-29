
#include "XAudio2Stream.h"
#include "System.h"
#include "StreamingService.h"
#include "StreamCallback.h"
#include "XAudio2Bus.h"
#include "AerEffect.h"
#include "HardwareEffect.h"
#include "Music.h"
#include "StreamingService.h"

XAudio2Stream::XAudio2Stream(AudioFormat format) 
	: OSInternalSound(format), callback(this)
{
	dataBufferIndex = 0;

	// ONLY FOR PCM!!
	WAVEFORMATEX wfx = { 0 };
	wfx.wFormatTag = FormatTagConversion(format.audioStructure);
	wfx.nChannels = format.numChannels;
	wfx.nSamplesPerSec = format.samplesPerSec;
	wfx.wBitsPerSample = format.bitsPerSample;
	wfx.nBlockAlign = (format.numChannels * format.bitsPerSample) / 8;
	wfx.nAvgBytesPerSec = format.samplesPerSec * wfx.nBlockAlign;
	wfx.cbSize = format.extraInfoSize;

	InternalSystem::GetSoundEngineInstance()->CreateSourceVoice(&sourceVoice,
		(WAVEFORMATEX*)&wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &callback, nullptr, nullptr);
}

XAudio2Stream::~XAudio2Stream()
{
	sourceVoice->DestroyVoice();
}

void XAudio2Stream::PushData(const StreamBuffer* updatedData, UInt32 numBytesToPush, UInt32 offset, Bool endOfStream)
{
	StreamingData* data = new StreamingData(updatedData->streamBuff + offset, numBytesToPush);
	XAUDIO2_BUFFER buff = { 0 };
	buff.AudioBytes = data->dataSize;
	buff.pAudioData = data->streamData;
	if (endOfStream)
	{
		buff.Flags = XAUDIO2_END_OF_STREAM;
	}
	buff.pContext = this;
	sourceVoice->SubmitSourceBuffer(&buff);
	bufferQueue.AddToBack(data);
}

void XAudio2Stream::SetMusicRef(Aer::Music* mus)
{
	musRef = mus;
}

void XAudio2Stream::BufferFinished()
{
	bufferQueue.RemoveFront();
	musRef->GetService()->BufferFinished();
}

void XAudio2Stream::StreamFinished()
{
	while (!bufferQueue.Empty())
	{
		bufferQueue.RemoveFront();
	}

	musRef->GetService()->StreamFinished();
}

void XAudio2Stream::AttachEffect(AerEffect* effect)
{
	AerAssert(effect != nullptr);
	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	IXAPO* winEffect = (IXAPO*)(effect->GetHardwareEffect()->GetNativeEffect());
	descriptor.InitialState = TRUE;
	descriptor.OutputChannels = this->rawData->format.numChannels;
	descriptor.pEffect = winEffect;

	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;

	sourceVoice->SetEffectChain(&chain);

	++effectCount;
}

void XAudio2Stream::EnableSoundEffects()
{
	for (UInt32 i = 0; i < effectCount; ++i)
	{
		sourceVoice->EnableEffect(i);
	}
}

void XAudio2Stream::DisableAttachedEffects()
{
	for (UInt32 i = 0; i < effectCount; ++i)
	{
		sourceVoice->DisableEffect(i);
	}
}

void XAudio2Stream::StartAudioProcessing()
{
	sourceVoice->Start(0);
}

void XAudio2Stream::StopAudioProcessing()
{
	sourceVoice->Stop(0);
}

void XAudio2Stream::SeekPosition(Float ms)
{
	UNUSED(ms);
}

void XAudio2Stream::ConnectBus(OSInternalBus* otherBus)
{
	IXAudio2SubmixVoice* submixVoice = otherBus->GetNativeBus();
	XAUDIO2_SEND_DESCRIPTOR desc = { 0, submixVoice };
	XAUDIO2_VOICE_SENDS sendList = { 1, &desc };
	sourceVoice->SetOutputVoices(&sendList);
}

OSSound* XAudio2Stream::GetNativeSound()
{
	return sourceVoice;
}