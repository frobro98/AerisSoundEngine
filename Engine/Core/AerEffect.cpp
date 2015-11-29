
#include "AerEffect.h"
#include "fnv.h"

AerEffect::AerEffect(const TChar* name)
	: effectName(name), 
	 effectID(Aer::fnvHash(name))
{
}

AerEffect::~AerEffect()
{

}