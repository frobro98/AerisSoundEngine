
#include "WindowsEffect.h"

WindowsEffect::WindowsEffect(Aer_EFFECTTYPE effectType)
{
	switch (effectType)
	{
	case BASIC_REVERB:
	{
		HRESULT hr;
		hr = CreateFX(__uuidof(FXReverb), &winEffect);
		AerAssert(hr == S_OK);
	}break;
	case REVERB:
	{
		HRESULT hr;
		hr = XAudio2CreateReverb(&winEffect);
		AerAssert(hr == S_OK);
	}break;
	case ECHO:
	{
		HRESULT hr;
		hr = CreateFX(__uuidof(FXEcho), &winEffect);
		AerAssert(hr == S_OK);
	}break;
	case CUSTOM:
	{
		AerAssert(false);
	}break;
	default:
		break;
	}
}

WindowsEffect::~WindowsEffect()
{
	winEffect->Release();
}

Effect* WindowsEffect::GetNativeEffect()
{
	return winEffect;
}