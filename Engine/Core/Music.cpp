
#include "MusicStreamer.h"
#include "Music.h"
#include "System.h"
#include "fnv.h"
#include "Handles.h"
#include "OSInternalSound.h"
#include "XAudio2Stream.h"

namespace Aer
{
	Handle* CreateMusic(const TChar* filename, const TChar* name)
	{
		Music* mus = AerMusicStreamer::CreateStream(filename, name);
		Handle* mHandle = new MusicHandle(mus);
		return mHandle;
	}

	Music::Music(const TChar* name, OSInternalSound* mus)
		: musicName(name), musicID(fnvHash(name))
	{
		hardwareStream = mus;
		static_cast<XAudio2Stream*>(hardwareStream)->SetMusicRef(this);
	}

	Music::~Music()
	{
		musicName = nullptr;
		hardwareStream = nullptr;
	}

	void Music::StartStreaming()
	{
		AerMusicStreamer::StartLoadedStream(this);
	}

	void Music::EndStreaming()
	{
		hardwareStream->StopAudioProcessing();
	}

	void Music::BeginProcessing()
	{
		hardwareStream->StartAudioProcessing();
	}
	
	void Music::StopProcessing()
	{
		hardwareStream->StopAudioProcessing();
	}

	void Music::PushData(StreamBuffer* buffer, UInt32 amountBuffered, UINT32 offset, Bool endOfStream)
	{
		hardwareStream->PushData(buffer, amountBuffered, offset, endOfStream);
		offset += amountBuffered;
	}
}