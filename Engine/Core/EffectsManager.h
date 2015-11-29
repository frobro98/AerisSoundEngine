#pragma once

#include "EffectsDefinitions.h"
#include "AerList.h"
#include "AerEffect.h"

class EffectsManager
{
public:
	AER_SINGLETON(EffectsManager);

	//static AerEffect* CreateEffect(Aer_EFFECTTYPE type);
	static AerEffect* CreateEffect(Aer::SimpleReverbDescription& params);
	static AerEffect* CreateEffect(Aer::ReverbDescription& params);
	static AerEffect* CreateEffect(Aer::EchoDescription& params);

	static AerEffect* FindEffect(EffectID effectID);

private:
	AerList<AerEffect*> effectsList;

};
