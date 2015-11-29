
#include "HierarchyContainer.h"
#include "AudioBus.h"

HierarchyContainer::HierarchyContainer(const TChar* containerName, UInt32 processingStage)
	: AudioContainer(containerName)
{
	bus = new AudioBus(containerName, processingStage);
}

HierarchyContainer::~HierarchyContainer()
{
	delete bus;
}

void HierarchyContainer::SetEffect(EffectID effectID)
{
	bus->SetEffect(effectID);
}

void HierarchyContainer::EnableEffects()
{
	bus->EnableEffects();
}

void HierarchyContainer::DisableEffects()
{
	bus->DisableEffects();
}

void HierarchyContainer::PostAdd()
{
	HierarchyContainer* node = static_cast<HierarchyContainer*>(parent);
	AudioBus* otherBus = node->GetBus();
	bus->ConnectBus(otherBus);
}