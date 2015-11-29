#pragma once

#include <queue>

#include "Thread.h"
#include "AerCondVar.h"

class Task
{
public:
	virtual void execute() const = 0;
};

class AerWorkQueue
{
public:
	AerWorkQueue(unsigned int numThreads = 1);
	~AerWorkQueue();

	void enqueue(Task* queueTask);

private:
	std::queue<Task*> workQueue;
	AerCondVar cv;
	Thread* threadPool;
	int threadCount;

	void processQueue();
};