#pragma once

#include "Event.h"

class Pause : public Aer::Event
{
public:
	Pause(Aer::Handle* audioHandle);
	~Pause();

	virtual void Execute() override;
};