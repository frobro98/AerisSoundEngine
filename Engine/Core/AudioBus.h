#pragma once

#include "CoreDefs.h"

class OSInternalBus;

class AudioBus 
{
public:
	AudioBus(const TChar* busName, UInt32 processingStage);
	~AudioBus();

	void SetEffect(EffectID effectID);
	void EnableEffects();
	void DisableEffects();

	void ConnectBus(AudioBus* bus);

	OSInternalBus* GetOSBus()
	{
		return soundBus;
	}

	const TChar* GetName() const
	{
		return name;
	}
	BusID GetBusID() const
	{
		return busID;
	}
	
private:
	OSInternalBus* soundBus;
	const TChar* name;
	BusID busID;
};