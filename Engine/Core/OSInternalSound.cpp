
#include "OSInternalSound.h"

OSInternalSound::OSInternalSound(AudioPacket* audioDataPacket)
	: effectCount(0), 
	rawData(audioDataPacket)
{
}

OSInternalSound::OSInternalSound(const AudioFormat& fmt)
	: effectCount(0)
{
	rawData = new AudioPacket;
	rawData->format = fmt;
}

OSInternalSound::~OSInternalSound()
{
	rawData = nullptr;
}

Bool OSInternalSound::IsPlaying() const
{
	return isPlaying;
}