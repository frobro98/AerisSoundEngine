#pragma once

#include "OSInternalBus.h"

class XAudio2Bus : public OSInternalBus
{
public:
	XAudio2Bus(UInt32 processingStage);
	~XAudio2Bus();

	virtual void SetBusEffect(UInt32 effectID) override;
	virtual void EnableBusEffects() override;
	virtual void DisableBusEffects() override;

	virtual void ConnectBus(OSInternalBus* otherBus) override;
	virtual OSBus* GetNativeBus() override;
private:
	IXAudio2SubmixVoice* busVoice;
	UInt32 effectCount;
};