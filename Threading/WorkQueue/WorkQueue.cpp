
#include "AerWorkQueue.h"

AerWorkQueue::AerWorkQueue(unsigned int numThreads)
	: threadCount(numThreads)
{
	threadPool = new Thread[numThreads];

	for (int i = 0; i < threadCount; ++i)
	{
		threadPool[i].startThread(&AerWorkQueue::processQueue, this);
	}
}

void AerWorkQueue::enqueue(Task* queueTask)
{
	workQueue.push(queueTask);
}

void AerWorkQueue::processQueue()
{
	AerLock lock;

	for (;;)
	{
		cv.wait(lock);

		Task* task = workQueue.back();
		workQueue.pop();
		task->execute();
	}
}

AerWorkQueue::~AerWorkQueue()
{

}