#pragma once

#include "AudioContainer.h"

class AudioBus;

class HierarchyContainer : public AudioContainer
{
public:
	HierarchyContainer(const TChar* containerName, UInt32 processingStage);
	~HierarchyContainer();

	virtual void SetEffect(EffectID effectID) override;
	virtual void EnableEffects() override;
	virtual void DisableEffects() override;
	
	AudioBus* GetBus() const
	{
		return bus;
	}

protected:
	virtual void PostAdd() override;

	AudioBus* bus;
};