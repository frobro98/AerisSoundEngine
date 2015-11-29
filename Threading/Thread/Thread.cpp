
// This is the way that the thread in the debugger will get named
#ifdef _WIN32
#include <windows.h>
const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType;
	LPCSTR szName;
	DWORD dwThreadID;
	DWORD dwFlags;
} THREADNAME_INFO;
#pragma pack(pop)

#else
#include <pthread.h>	
#endif

#include "Thread.h"

// This will be in the thread class (private) and will set up both the debug name and 
// a class name (thread_local variable)
void Thread::SetThreadName(std::thread& thr, const char* threadName)
{
#ifdef _WIN32
	DWORD dwThreadID = ::GetThreadId( static_cast<HANDLE>( thr.native_handle() ) );

	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}
#else
	auto tHandle = thr.native_handle();
	// May not work for all unix systems (hopefully it works on macs)
	pthread_setname_np(tHandle, threadName);
#endif
}