#pragma once

#include "CoreDefs.h"

/************************************************************************/
/*  MAKE ALL WINDOWS CALLS WRAPPED                                      */
/************************************************************************/

//#define AerFail(x)											\
//	do															\
//	{															\
//		if(IsDebuggerPresent())									\
//			DebugBreak();										\
//		std::abort();											\
//	} while(0)

#define AerFail(x, file, line, ...)								\
	do															\
	{															\
		if(IsDebuggerPresent())									\
			DebugBreak();										\
		fprintf(stderr, "Error in %s at %d\n", file, line);		\
		fflush(stdout);											\
		fflush(stderr);											\
		abort();												\
	} WHILE(0)
			
// Assert check for the internal system
#define AerAssert(x, ...)										\
	do															\
	{															\
		if(!internalExpressionCheck(x))							\
			AerFail(#x,__FILE__,__LINE__,##VA_ARGS__);			\
																\
	} WHILE(0)										


// Gets rid of the warning: conditional expression is constant
template<class T>
inline bool internalExpressionCheck(const T& exprCheck)
{
	return (exprCheck) ? true : false;
}

template <>
inline bool internalExpressionCheck(const bool& boolExpr)
{
	return boolExpr;
}
