
#include "Reverb.h"
#include "WindowsEffect.h"
//////////////////////////////////////////////////////////////////////////
// Simple Reverb
//////////////////////////////////////////////////////////////////////////

AerSimpleReverb::AerSimpleReverb(Aer::SimpleReverbDescription& effectDesc)
	: AerEffect(effectDesc.effectName)
{
#ifdef _WIN32
	reverbEffect = new WindowsEffect(BASIC_REVERB);
	params = effectDesc;
#endif
}

AerSimpleReverb::~AerSimpleReverb()
{
	delete reverbEffect;
}

HardwareEffect* AerSimpleReverb::GetHardwareEffect()
{
	return reverbEffect;
}

//////////////////////////////////////////////////////////////////////////
// Reverb
//////////////////////////////////////////////////////////////////////////

AerReverb::AerReverb(Aer::ReverbDescription& effectDesc)
	: AerEffect(effectDesc.effectName)
{
#ifdef _WIN32
	reverbEffect = new WindowsEffect(REVERB);
	params = effectDesc;
#endif
}

AerReverb::~AerReverb()
{
	delete reverbEffect;
}

HardwareEffect* AerReverb::GetHardwareEffect()
{
	return reverbEffect;
}