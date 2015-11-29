#pragma once

#include "CoreDefs.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// FNV hash only supports 32 bit numbers currently
//
// If 64 bit numbers are a necessity, consider the
// implementation AudioKinetic did at:
// https://www.audiokinetic.com/library/2015.1_5418/?source=SDK&id=_ak_f_n_v_hash_8h_source.html
////////////////////////////////////////////////////////////////////////////////////////////////

namespace Aer
{
	inline UInt32 fnv(const void* hashData, UInt32 dataSize)
	{
		Byte* byteData = (Byte *)hashData;

		// These numbers were gotten off of this website
		// http://www.isthe.com/chongo/tech/comp/fnv/#FNV-param
		const UInt32 offsetBasis = 2166136261;
		const UInt32 hashPrime = 16777619;

		UInt32 hash = offsetBasis;

		for (UInt32 i = 0; i < dataSize; ++i)
		{
			hash ^= *byteData++;
			hash *= hashPrime;
		}

		return hash;
	}

	template <class T>
	inline UInt32 fnvHash(const T& objToHash)
	{
		return fnv(&objToHash, sizeof(T));
	}
}