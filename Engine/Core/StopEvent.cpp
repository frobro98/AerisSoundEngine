
#include "StopEvent.h"
#include "EventTypes.h"
#include "Handles.h"

Stop::Stop(Aer::Handle* audHandle)
	: Aer::Event(audHandle, STOP)
{
}

Stop::~Stop()
{
}

void Stop::Execute()
{
	audioHandle->Stop();
}
