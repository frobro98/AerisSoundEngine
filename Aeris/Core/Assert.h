#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "CoreDefs.h"

/************************************************************************/
/*  MAKE ALL WINDOWS CALLS WRAPPED                                      */
/************************************************************************/

#define AERISFAIL(x, file, line, ...)					\
	do													\
	{													\
		if(IsDebuggerPresent())							\
			DebugBreak();								\
		std::abort();									\
	} while(0)
			
// Assert check for the internal system
#define AERISASSERT(x, ...)								\
	do													\
	{													\
		if( !((void)(sizeof(x) ) ? true : false) )		\
			AERISFAIL(#x,__FILE__,__LINE__,##VA_ARGS__);	\
														\
	} while(0)										
