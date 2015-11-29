#pragma once

#include "Event.h"

class Stop : public Aer::Event
{
public:
	Stop(Aer::Handle* audHandle);
	~Stop();

	virtual void Execute() override;
};