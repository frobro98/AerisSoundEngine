
#include "Reverb.h"
#include "Echo.h"
#include "EffectsManager.h"

AER_DEFINE_INSTANCE(EffectsManager);
/*
AerEffect* EffectsManager::CreateEffect(Aer_EFFECTTYPE type)
{
	switch (type)
	{
	case REVERB:
	{

	}break;
	case ECHO:
	{

	}break;
	case CUSTOM:
	{

	}break;
	default:
	{
		AerAssert(FALSE);
	}
	}

	return nullptr;
}
//*/

AerEffect* EffectsManager::CreateEffect(Aer::SimpleReverbDescription& params)
{
	AerSimpleReverb* reverb = new AerSimpleReverb(params);
	instance().effectsList.AddToBack(reverb);
	return reverb;
}

AerEffect* EffectsManager::CreateEffect(Aer::ReverbDescription& params)
{
	AerReverb* reverb = new AerReverb(params);
	instance().effectsList.AddToBack(reverb);
	return reverb;
}

AerEffect* EffectsManager::CreateEffect(Aer::EchoDescription& params)
{
	AerEcho* echo = new AerEcho(params);
	instance().effectsList.AddToBack(echo);
	return echo;
}

AerEffect* EffectsManager::FindEffect(EffectID effectID)
{
	return instance().effectsList.Find(effectID);
}

EffectsManager::EffectsManager()
{

}

EffectsManager::~EffectsManager()
{

}