#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _WIN32
#include "WindowsModule.h"
#else
#include "OSXModule.h"
#endif

#include "ClassDefs.h"
#include "Assert.h"
#include "CoreWarningSuppression.h"

typedef unsigned char Byte;
typedef char SByte;

#ifdef UNICODE
typedef wchar_t TChar;
#else
typedef char TChar;
#endif

#ifdef _WIN32
typedef WORD UInt16;
typedef DWORD UInt32;
#else
typedef unsigned UInt16;
typedef unsigned int UInt32;
#endif
typedef int Int32;
typedef long long Int64;
typedef unsigned long long UInt64;

typedef int Bool; // TRUE(1) and FALSE(0)
#define TRUE 1
#define FALSE 0

typedef float Float;
typedef double Float64;

// File handle type
typedef Int32 FileHandle;

//////////////////////////////////////////////////////////////////////////
// Aeris Type Definitions
//////////////////////////////////////////////////////////////////////////

typedef UInt32 SoundID;
typedef UInt32 EffectID;
typedef UInt32 EventID;
typedef UInt32 BusID;
typedef UInt32 MusicID;
typedef UInt32 HierarchyID;

//////////////////////////////////////////////////////////////////////////
// Debug Utilities
// @TODO: move into separate file
//////////////////////////////////////////////////////////////////////////

#define UNUSED(...) (void)(__VA_ARGS__)

extern TChar debugBuffer[256];

#define Debugf(mess, ...) sprintf_s(debugBuffer, mess, ##__VA_ARGS__); OutputDebugString(debugBuffer);

