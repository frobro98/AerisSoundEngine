
#include "PlayEvent.h"
#include "EventTypes.h"
#include "Handles.h"

Play::Play(Aer::Handle* audioHandle)
	: Aer::Event(audioHandle, PLAY)
{

}

Play::~Play()
{
}

void Play::Execute()
{
	audioHandle->Play();
}
