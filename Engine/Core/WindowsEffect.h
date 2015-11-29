#pragma once

#include "HardwareEffect.h"
#include "EffectsDefinitions.h"

class WindowsEffect : public HardwareEffect
{
public:
	WindowsEffect(Aer_EFFECTTYPE effectType);
	~WindowsEffect();

	virtual Effect* GetNativeEffect() override;

private:
	IUnknown* winEffect;
};