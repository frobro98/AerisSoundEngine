#pragma once

#include "CoreDefs.h"

class OSInternalSound;

class OSInternalBus
{
public:
	OSInternalBus();
	virtual ~OSInternalBus();

	virtual void SetBusEffect(UInt32 effectID) = 0;
	virtual void EnableBusEffects() = 0;
	virtual void DisableBusEffects() = 0;

	virtual void ConnectBus(OSInternalBus* otherBus) = 0;
	virtual OSBus* GetNativeBus() = 0;

protected:
	const TChar* name;
};