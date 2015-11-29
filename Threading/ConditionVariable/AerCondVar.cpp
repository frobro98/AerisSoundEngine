
#include "AerCondVar.h"

void AerCondVar::wait(AerLock& lock)
{
	std::unique_lock<std::mutex> uLock(lock._mut);
	cv.wait(uLock);
}

void AerCondVar::signal()
{
	cv.notify_one();
}

void AerCondVar::signalAll()
{
	cv.notify_all();
}
