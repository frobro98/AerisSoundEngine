
#include "SoundContainer.h"
#include "Sound.h"
#include "SoundManager.h"
#include "fnv.h"
#include "EffectsManager.h"
#include "AerEffect.h"
#include "HardwareEffect.h"
#include "XAudio2Sound.h"
#include "HierarchyContainer.h"
#include "AudioBus.h"

SoundContainer::SoundContainer(const TChar* containerName, const TChar* soundName)
	: AudioContainer(containerName)
{
	SoundID sndID = Aer::fnvHash(soundName);
	sound = SoundManager::FindSound(sndID);
}

SoundContainer::~SoundContainer()
{
	sound = nullptr;
}

void SoundContainer::SetEffect(EffectID effectID)
{
	AerEffect* effect = EffectsManager::FindEffect(effectID);
	AerAssert(effect != nullptr);

	sound->GetInternalSound()->AttachEffect(effect);
}

void SoundContainer::EnableEffects()
{
	sound->GetInternalSound()->EnableSoundEffects();
}

void SoundContainer::DisableEffects()
{
	sound->GetInternalSound()->DisableAttachedEffects();
}

void SoundContainer::PostAdd()
{
	HierarchyContainer* node = static_cast<HierarchyContainer*>(parent);
	AudioBus* otherBus = node->GetBus();
	sound->GetInternalSound()->ConnectBus(otherBus->GetOSBus());
}