#pragma once

#include "AerEffect.h"
#include "EffectsDefinitions.h"

class AerReverb : public AerEffect
{
public:
	AerReverb(Aer::ReverbDescription& effectDesc);
	~AerReverb();

	virtual HardwareEffect* GetHardwareEffect() override;

private:
	Aer::ReverbDescription params;
	HardwareEffect* reverbEffect;
};

class AerSimpleReverb : public AerEffect
{
public:
	AerSimpleReverb(Aer::SimpleReverbDescription& effectDesc);
	~AerSimpleReverb();

	virtual HardwareEffect* GetHardwareEffect() override;

private:
	Aer::SimpleReverbDescription params;
	HardwareEffect* reverbEffect;
};