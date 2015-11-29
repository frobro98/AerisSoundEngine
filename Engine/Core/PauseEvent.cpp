
#include "PauseEvent.h"
#include "Handles.h"
#include "EventTypes.h"

Pause::Pause(Aer::Handle* audioHandle)
	: Aer::Event(audioHandle, PAUSE)
{

}

Pause::~Pause()
{

}

void Pause::Execute()
{
	audioHandle->Pause();
}