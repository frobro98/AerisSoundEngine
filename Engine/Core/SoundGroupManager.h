#pragma once

#include "CoreDefs.h"
#include "AerList.h"

class AudioContainer;
class MainEffectContainer;

class SoundGroupManager
{
public:
	AER_SINGLETON(SoundGroupManager);

	static MainEffectContainer* CreateGroup(const TChar* groupName);
	static void AddContainer(AudioContainer* container, AudioContainer* parentNode);

	static MainEffectContainer* Find(const TChar* groupName);

private:
	AerList<MainEffectContainer*> groupList;

	static UInt32 processStage;
};