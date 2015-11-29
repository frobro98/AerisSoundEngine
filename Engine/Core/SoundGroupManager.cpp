
#include "SoundGroupManager.h"
#include "MainEffectContainer.h"
#include "fnv.h"

AER_DEFINE_INSTANCE(SoundGroupManager);

UInt32 SoundGroupManager::processStage = 0xFFFFFFFF;

MainEffectContainer* SoundGroupManager::CreateGroup(const TChar* groupName)
{
	MainEffectContainer* groupRoot = new MainEffectContainer(groupName, processStage--);
	instance().groupList.AddToBack(groupRoot);

	return groupRoot;
}

void SoundGroupManager::AddContainer(AudioContainer* container, AudioContainer* parentNode)
{
	container->SetParent(parentNode);
	container->SetSibling(parentNode->GetChild());
	parentNode->SetChild(container);
}

MainEffectContainer* SoundGroupManager::Find(const TChar* groupName)
{
	UInt32 hash = Aer::fnvHash(groupName);
	MainEffectContainer* container = instance().groupList.Find(hash);
	return container;
}

SoundGroupManager::SoundGroupManager()
{
}

SoundGroupManager::~SoundGroupManager()
{
}
