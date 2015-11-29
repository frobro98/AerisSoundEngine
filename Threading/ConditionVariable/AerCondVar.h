#pragma once

#include <condition_variable>

#include "AerLock.h"

class AerCondVar final
{
public:
	AerCondVar()	{}
	~AerCondVar()	{}

	AerCondVar(const AerCondVar&) = delete;
	AerCondVar& operator=(const AerCondVar&) = delete;

	void wait(AerLock& lock);
	void signal();
	void signalAll();

private:
	std::condition_variable cv;

};