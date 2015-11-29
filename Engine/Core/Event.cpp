
#include "Event.h"

namespace Aer
{
	Event::Event(Handle* audHandle, int eventValue)
		: audioHandle(audHandle), value(eventValue)
	{

	}

	Event::~Event()
	{
		audioHandle = nullptr;
	}
}