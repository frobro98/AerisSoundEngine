#pragma once

/************************************************************************/
/*	                                                                    */
/************************************************************************/

#include <thread>

class Thread final
{
public:
	Thread()
		: threadName("")
	{}

	~Thread()
	{
		if(thread.joinable())
		{
			thread.join();
		}
	}

	explicit Thread(char* threadName)
		: threadName(threadName)
	{}

	Thread(Thread&& moveThread)
		: thread(std::move(moveThread.thread)), 
		threadName(std::move(moveThread.threadName))
	{
		moveThread.threadName = nullptr;
	}
	Thread& operator=(Thread&& moveThread);

	template <typename Func, typename X0>
	void startThread(Func func, X0 param0)
	{
		thread = std::thread(func, param0);
	}

	template <typename Func, typename X0, typename X1>
	void startThread(Func func, X0 param0, X1 param1)
	{
		thread = std::thread(func, param0, param1);
	}

	template <typename Func, typename X0, typename X1, typename X2>
	void startThread(Func func, X0 param0, X1 param1, X2 param2)
	{
		thread = std::thread(func, param0, param1, param2);
	}

	template <typename Func, typename X0, typename X1, typename X2, typename X3>
	void startThread(Func func, X0 param0, X1 param1, X2 param2, X3 param3)
	{
		thread = std::thread(func, param0, param1, param2, param3);
	}

	void join()
	{ 
		if(thread.joinable())
			thread.join(); 
	}

	void detach()
	{
		if(thread.joinable())
			thread.detach();
	}

	const std::thread* getThread() const { return &thread; }

private:

	std::thread thread;
	/*thread_local*/ char* threadName;
	
	static void SetThreadName(std::thread& thread, const char* threadName);

	Thread(const Thread&);
	Thread& operator=(const Thread&);

};