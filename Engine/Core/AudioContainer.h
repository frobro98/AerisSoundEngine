#pragma once

#include "CoreDefs.h"

class AerEffect;

class AudioContainer
{
public:
	AudioContainer(const TChar* name);
	virtual ~AudioContainer();

	void SetParent(AudioContainer* container);
	void SetChild(AudioContainer* container);
	void SetSibling(AudioContainer* container);

	AudioContainer* GetParent();
	AudioContainer* GetChild();
	AudioContainer* GetSibling();

	virtual void SetEffect(EffectID effectID) = 0;
	virtual void EnableEffects() = 0;
	virtual void DisableEffects() = 0;

	HierarchyID GetID() const
	{
		return containerID;
	}

protected:
	virtual void PostAdd() = 0;

	AudioContainer* parent;
	AudioContainer* sibling;
	AudioContainer* child;

	const TChar* containerName;
	HierarchyID containerID;

};