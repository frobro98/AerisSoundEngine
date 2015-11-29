#pragma once

#include "fnv.h"

namespace Aer
{
	namespace Utils
	{
		inline UInt32 GetHashIDFromString(const TChar* objName)
		{
			return fnvHash(objName);
		}
	}
}