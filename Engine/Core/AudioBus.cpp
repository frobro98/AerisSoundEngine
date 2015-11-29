
#include "AudioBus.h"
#include "XAudio2Bus.h"

AudioBus::AudioBus(const TChar* busName, UInt32 processingStage)
	: name(busName)
{
#ifdef _WIN32
	soundBus = new XAudio2Bus(processingStage);
#else

#endif
}

AudioBus::~AudioBus()
{
	delete soundBus;
}

void AudioBus::ConnectBus(AudioBus* bus)
{
	soundBus->ConnectBus(bus->soundBus);
}

void AudioBus::SetEffect(EffectID effectID)
{
	soundBus->SetBusEffect(effectID);
}

void AudioBus::EnableEffects()
{
	soundBus->EnableBusEffects();
}

void AudioBus::DisableEffects()
{
	soundBus->DisableBusEffects();
}