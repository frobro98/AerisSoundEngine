#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <mmreg.h>

#include "LibraryHookup.h"

#if (_WIN32_WINNT < 0x0602  /*Windows 8*/)
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>
#include <xapobase.h>
#include <xapofx.h>

#pragma comment(lib,"x3daudio.lib")
#pragma comment(lib,"xapofx.lib")
#pragma comment(lib,"xaudio2.lib")
#else
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\x3daudio.h>
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2fx.h>
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xapobase.h>
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xapofx.h>

#pragma comment(lib,"c:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\lib\\x86\\xapofx.lib")
#pragma comment(lib,"c:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\lib\\x86\\x3daudio.lib")
#pragma comment(lib,"xapobase.lib")
#endif

#pragma comment(lib,"ole32.lib")

#ifdef _WIN32
#define WHILE(X) __pragma(warning(push))			\
				__pragma(warning(disable:4127))		\
				while((X))							\
				__pragma(warning(pop))	
#else
#define WHILE(X) while(X)
#endif

typedef IXAudio2SourceVoice OSSound;
typedef IXAudio2SubmixVoice OSBus;