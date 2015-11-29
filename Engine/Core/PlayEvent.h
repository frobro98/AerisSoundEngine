#pragma once

#include "Event.h"

class Play : public Aer::Event
{
public:
	Play(Aer::Handle* audioHandle);
	~Play();

	virtual void Execute() override;
};
