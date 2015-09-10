#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Byte;
typedef char SByte;

#ifdef UNICODE
typedef wchar_t TChar;
#else
typedef char TChar;
#endif

typedef int Int;
typedef unsigned int UInt;
typedef long long Int64;
typedef unsigned long long UInt64;

typedef int Bool; // TRUE(1) and FALSE(0)
#define TRUE 1
#define FALSE 0

typedef float Float;
