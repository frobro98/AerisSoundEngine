
#include "Echo.h"
#include "WindowsEffect.h"

AerEcho::AerEcho(Aer::EchoDescription& effectDesc)
	:AerEffect(effectDesc.effectName)
{
#ifdef _WIN32
	echoEffect = new WindowsEffect(ECHO);
	params = effectDesc;
#endif
}

AerEcho::~AerEcho()
{
	delete echoEffect;
}

HardwareEffect* AerEcho::GetHardwareEffect()
{
	return echoEffect;
}