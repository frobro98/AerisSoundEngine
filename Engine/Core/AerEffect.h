#pragma once

#include "CoreDefs.h"

class HardwareEffect;

class AerEffect
{
public:
	AerEffect(const TChar* name);
	virtual ~AerEffect();

	virtual HardwareEffect* GetHardwareEffect() = 0;

	const TChar* GetName() const
	{
		return effectName;
	}
	const UInt32 GetID() const
	{
		return effectID;
	}

	bool operator==(UInt32 audioID)
	{
		return effectID == audioID;
	}
	bool operator==(AerEffect& effect)
	{
		return effectID == effect.effectID;
	}

protected:
	const TChar* effectName;
	UInt32 effectID;
};