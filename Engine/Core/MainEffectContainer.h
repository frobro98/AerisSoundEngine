#pragma once

#include "HierarchyContainer.h"

class MainEffectContainer : public HierarchyContainer
{
public:
	MainEffectContainer(const TChar* containerName, UInt32 processingStage);
	~MainEffectContainer();

	bool operator==(HierarchyID nodeID)
	{
		return containerID == nodeID;
	}

private:
	virtual void PostAdd() override
	{}
};