#pragma once

//#include "Handles.h"

namespace Aer
{
	class Handle;

	class Event
	{
	public:
		Event(Handle* audHandle, int eventType);
		virtual ~Event();
		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		virtual void Execute() = 0;
	protected:
		Handle* audioHandle;
		int value;
	};
}