
#include "System.h"
#include "XAudio2Sound.h"
#include "../FileManager/FileType.h"
#include "AerEffect.h"
#include "WindowsEffect.h"
#include "OSInternalBus.h"

XAudio2Sound::XAudio2Sound(AudioPacket* audioDataPacket, const TChar* filename)
	: OSInternalSound(audioDataPacket, filename)
{
	// ONLY FOR PCM!!
	WAVEFORMATEX wfx = { 0 };
	AudioFormat format = audioDataPacket->format;
	wfx.wFormatTag = FormatTagConversion(format.audioStructure);
	wfx.nChannels = format.numChannels;
	wfx.nSamplesPerSec = format.samplesPerSec;
	wfx.wBitsPerSample = format.bitsPerSample;
	wfx.nBlockAlign = (format.numChannels * format.bitsPerSample) / 8;
	wfx.nAvgBytesPerSec = format.samplesPerSec * wfx.nBlockAlign;
	wfx.cbSize = format.extraInfoSize;

	InternalSystem::isInstance->pSndEngine->CreateSourceVoice(&sourceVoice,
		(WAVEFORMATEX*)&wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NO_CALLBACK, nullptr, nullptr);
}

XAudio2Sound::XAudio2Sound(AudioPacket* audioDataPacket, AerEffect* effect, const TChar* filename, UInt32 effectCount)
	: OSInternalSound(audioDataPacket, filename)
{
	// ONLY FOR PCM!!
	WAVEFORMATEX wfx = { 0 };
	AudioFormat format = audioDataPacket->format;
	wfx.wFormatTag = FormatTagConversion(format.audioStructure);
	wfx.nChannels = format.numChannels;
	wfx.nSamplesPerSec = format.samplesPerSec;
	wfx.wBitsPerSample = format.bitsPerSample;
	wfx.nBlockAlign = (format.numChannels * format.bitsPerSample) / 8;
	wfx.nAvgBytesPerSec = format.samplesPerSec * wfx.nBlockAlign;
	wfx.cbSize = format.extraInfoSize;

	AerAssert(effect != nullptr);
	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	for (UInt32 i = 0; i < effectCount; ++i)
	{
		AerEffect* currEffect = &effect[i];
		IXAPO* winEffect = (IXAPO*)(currEffect->GetHardwareEffect()->GetNativeEffect());
		descriptor.InitialState = TRUE;
		descriptor.OutputChannels = wfx.nChannels;
		descriptor.pEffect = winEffect;
	}
	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = effectCount;
	chain.pEffectDescriptors = &descriptor;

	InternalSystem::isInstance->pSndEngine->CreateSourceVoice(&sourceVoice,
		(WAVEFORMATEX*)&wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NO_CALLBACK, nullptr, &chain);
}

XAudio2Sound::~XAudio2Sound()
{
}

void XAudio2Sound::SubmitAudioData()
{
	XAUDIO2_BUFFER xa2buff = { 0 };
	xa2buff.AudioBytes = rawData->data.audioDataSize;
	xa2buff.pAudioData = rawData->data.audioData;
	sourceVoice->SubmitSourceBuffer(&xa2buff);
}

void XAudio2Sound::StartAudioProcessing()
{
	sourceVoice->Start(0);
	isPlaying = TRUE;
}

void XAudio2Sound::StopAudioProcessing()
{
	if (isPlaying)
	{
		sourceVoice->Stop(0);
		isPlaying = FALSE;
	}
}

void XAudio2Sound::ClearAudioBuffers()
{
	sourceVoice->Stop(0);
	sourceVoice->FlushSourceBuffers();
}

void XAudio2Sound::ResetAudioBuffer()
{
	sourceVoice->Stop(0);
	sourceVoice->FlushSourceBuffers();
	SubmitAudioData();
}

void XAudio2Sound::SeekPosition(Float ms)
{
	sourceVoice->Stop(0);
	sourceVoice->FlushSourceBuffers();

	const AudioPacket* packet = this->getAudioData();
	Float samplePerSec = static_cast<Float>(packet->format.samplesPerSec);
	
	// Convert millisecond position to seconds
	Float secondsPos = ms / 1000.f;
	Float startPos = secondsPos * samplePerSec;

	UInt32 startSample = static_cast<UInt32>(startPos);

	//if (pCacheEntry->gwf.adpcm.wfx.wFormatTag == WAVE_FORMAT_ADPCM) {
	//	// Integer rounding
	//	startSample /= pCacheEntry->gwf.adpcm.wSamplesPerBlock;
	//	startSample *= pCacheEntry->gwf.adpcm.wSamplesPerBlock;
	//}

	XAUDIO2_BUFFER voiceBuff = { 0 };
	voiceBuff.Flags = XAUDIO2_END_OF_STREAM;
	voiceBuff.AudioBytes = packet->data.audioDataSize;
	voiceBuff.pAudioData = packet->data.audioData;
	voiceBuff.PlayBegin = startSample;
	voiceBuff.LoopBegin = XAUDIO2_NO_LOOP_REGION;

	sourceVoice->SubmitSourceBuffer(&voiceBuff);

	if (isPlaying)
	{
		StartAudioProcessing();
	}
}

void XAudio2Sound::ConnectBus(OSInternalBus* otherBus)
{
	IXAudio2SubmixVoice* submixVoice = otherBus->GetNativeBus();
	XAUDIO2_SEND_DESCRIPTOR desc = { 0, submixVoice };
	XAUDIO2_VOICE_SENDS sendList = { 1, &desc };
	sourceVoice->SetOutputVoices(&sendList);
}

OSSound* XAudio2Sound::GetNativeSound()
{
	return sourceVoice;
}

void XAudio2Sound::AttachEffect(AerEffect* effect)
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

void XAudio2Sound::EnableSoundEffects()
{
	for (UInt32 i = 0; i < effectCount; ++i)
	{
		sourceVoice->EnableEffect(i);
	}
}

void XAudio2Sound::DisableAttachedEffects()
{
	for (UInt32 i = 0; i < effectCount; ++i)
	{
		sourceVoice->DisableEffect(i);
	}
}
