#pragma once

#include "AerEffect.h"
#include "EffectsDefinitions.h"

class AerEcho : public AerEffect
{
public:
	AerEcho(Aer::EchoDescription& effectDesc);
	~AerEcho();

	virtual HardwareEffect* GetHardwareEffect() override;
private:
	Aer::EchoDescription params;
	HardwareEffect* echoEffect;
};
