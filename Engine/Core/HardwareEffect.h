#pragma once

#include "CoreDefs.h"

#ifdef _WIN32
typedef IUnknown Effect;
#endif

class HardwareEffect
{
public:
	HardwareEffect();
	~HardwareEffect();

	virtual  Effect* GetNativeEffect() = 0;
};