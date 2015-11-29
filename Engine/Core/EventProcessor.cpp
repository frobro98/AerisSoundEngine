
#include "EventProcessor.h"
#include "Event.h"

AER_DEFINE_INSTANCE(EventProcessor);

void EventProcessor::AddEvent(Aer::Event* evt)
{
	instance().eventsQueue.AddToBack(evt);
}

void EventProcessor::ProcessEvents()
{
	while (instance().eventsQueue.Size() > 0)
	{
		Aer::Event* evt = instance().eventsQueue.RemoveFront();
		evt->Execute();
	}
}

EventProcessor::EventProcessor()
{

}

EventProcessor::~EventProcessor()
{

}