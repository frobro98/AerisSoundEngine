

#include "Handles.h"
#include "Sound.h"
#include "Music.h"

using namespace Aer;

//////////////////////////////////////////////////////////////////////////
// Sound handle control methods
//////////////////////////////////////////////////////////////////////////

void SoundHandle::Play()
{
	sndRef->Play();
}

void SoundHandle::Stop()
{
	sndRef->Stop();
}

void SoundHandle::Pause()
{
	sndRef->Pause();
}

void SoundHandle::Restart()
{
	sndRef->Reset();
	sndRef->Play();
}

void SoundHandle::SeekPosition(Float milliseconds)
{
	sndRef->Seek(milliseconds);
}

void MusicHandle::Play()
{
	musRef->StartStreaming();
}

//////////////////////////////////////////////////////////////////////////
// Sound handle construction
//////////////////////////////////////////////////////////////////////////

SoundHandle::SoundHandle(Sound* sndRef)
{
	this->sndRef = sndRef;
}

SoundHandle::SoundHandle(const SoundHandle& sh)
{
	sndRef = sh.sndRef;
}

SoundHandle& SoundHandle::operator=(const SoundHandle& sh)
{
	if (this != &sh)
	{
		sndRef = sh.sndRef;
	}

	return *this;
}

SoundHandle::~SoundHandle()
{
	sndRef = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Music handle construction
//////////////////////////////////////////////////////////////////////////

Aer::MusicHandle::MusicHandle(Music* musRef)
{
	this->musRef = musRef;
}

MusicHandle::MusicHandle(const MusicHandle& mh)
{
	musRef = mh.musRef;
}

MusicHandle& MusicHandle::operator=(const MusicHandle& mh)
{
	if (this != &mh)
	{
		musRef = mh.musRef;
	}

	return *this;
}

MusicHandle::~MusicHandle()
{
	musRef = nullptr;
}

