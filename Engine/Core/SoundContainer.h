#pragma once

#include "AudioContainer.h"

namespace Aer
{
	class Sound;
}

class SoundContainer : public AudioContainer
{
public:
	SoundContainer(const TChar* containerName, const TChar* soundName);
	~SoundContainer();

	virtual void SetEffect(EffectID effectID) override;
	virtual void EnableEffects() override;
	virtual void DisableEffects() override;

private:
	virtual void PostAdd() override;

	Aer::Sound* sound;
};