
#include "XAudio2Bus.h"
#include "System.h"
#include "EffectsManager.h"
#include "AerEffect.h"
#include "HardwareEffect.h"


#define BUS_VOICE_CHANNELS 2
#define BUS_VOICE_SAMPLE_RATE 48000


XAudio2Bus::XAudio2Bus(UInt32 processingStage)
{
	InternalSystem::GetSoundEngineInstance()->CreateSubmixVoice(&busVoice, BUS_VOICE_CHANNELS, BUS_VOICE_SAMPLE_RATE, 0, processingStage);
	effectCount = 0;
}

XAudio2Bus::~XAudio2Bus()
{
	busVoice->DestroyVoice();
}

OSBus* XAudio2Bus::GetNativeBus()
{
	return busVoice;
}

void XAudio2Bus::ConnectBus(OSInternalBus* otherBus)
{
	IXAudio2SubmixVoice* submixVoice = otherBus->GetNativeBus();
	XAUDIO2_SEND_DESCRIPTOR desc = { 0, submixVoice };
	XAUDIO2_VOICE_SENDS sendList = { 1, &desc };
	busVoice->SetOutputVoices(&sendList);
}

void XAudio2Bus::SetBusEffect(UInt32 effectID)
{
	AerEffect* effect = EffectsManager::FindEffect(effectID);

	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	IXAPO* winEffect = (IXAPO*)(effect->GetHardwareEffect()->GetNativeEffect());
	descriptor.InitialState = TRUE;
	descriptor.OutputChannels = BUS_VOICE_CHANNELS;//this->rawData->format.numChannels;
	descriptor.pEffect = winEffect;

	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;

	busVoice->SetEffectChain(&chain);
	++effectCount;
}

void XAudio2Bus::EnableBusEffects()
{
	for (UInt32 i = 0; i < effectCount; ++effectCount)
	{
		busVoice->EnableEffect(i);
	}
}

void XAudio2Bus::DisableBusEffects()
{
	for (UInt32 i = 0; i < effectCount; ++effectCount)
	{
		busVoice->DisableEffect(i);
	}
}



