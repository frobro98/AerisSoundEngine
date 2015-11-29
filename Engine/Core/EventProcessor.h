#pragma once


#include "AerList.h"

namespace Aer
{
	class Event;
}


class EventProcessor
{
public:
	AER_SINGLETON(EventProcessor);

	static void AddEvent(Aer::Event* evt);

	static void ProcessEvents();

private:
	AerList<Aer::Event*> eventsQueue;
};
