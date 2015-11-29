
#include "MusicStreamer.h"
#include "Music.h"
#include "Assert.h"
#include "XAudio2Stream.h"
#include "StreamingService.h"
#include "AudioDataManager.h"
#include "Thread.h"

AER_DEFINE_INSTANCE(AerMusicStreamer);

//////////////////////////////////////////////////////////////////////////
// Main Streaming Engine Functions
//////////////////////////////////////////////////////////////////////////

void Aer::Stream::Initialize(const AerStreamSettings& streamInitSettings)
{
	AerMusicStreamer::Init(streamInitSettings);
}

void Aer::Stream::Terminate()
{
	AerMusicStreamer::Term();
}

void Aer::Stream::GetDefaultSettings(AerStreamSettings& settings)
{
	UNUSED(settings);
}

//////////////////////////////////////////////////////////////////////////
// Internal Music Streaming class to which Aer::Stream functions talk 
//////////////////////////////////////////////////////////////////////////

void AerMusicStreamer::Init(const AerStreamSettings& settings)
{
	instance().InitInternal(settings);
}

void AerMusicStreamer::InitInternal(const AerStreamSettings& settings)
{
	UNUSED(settings);
}

void AerMusicStreamer::Term()
{
	instance().TermInternal();
}

void AerMusicStreamer::TermInternal()
{
	
}

//////////////////////////////////////////////////////////////////////////
// Non-static methods for StreamService objects
//////////////////////////////////////////////////////////////////////////

void AerMusicStreamer::StreamEnded(StreamService* finishedStream)
{
	streamingMusic.Remove(finishedStream);
}

//////////////////////////////////////////////////////////////////////////
// Creating Streaming objects
//////////////////////////////////////////////////////////////////////////

Aer::Music* AerMusicStreamer::CreateStream(const TChar* const filename, const TChar* const streamName)
{
	FileHandle fHandle;
	ASEFileManager::OpenFile(filename, fHandle);
	XAudio2Stream* stream = AudioDataManager::ParseAudioHeader(fHandle);
	Aer::Music* music = new Aer::Music(streamName, stream);
	StreamService* serv = new StreamService(&instance(), music, fHandle);
	music->SetService(serv);
	instance().streamingMusic.AddToBack(serv);

	return music;
}

void AerMusicStreamer::StartLoadedStream(Aer::Music* musicToStream)
{
	Thread thr("TestStreamingThread");
	StreamService* serv = instance().streamingMusic.Find(musicToStream->GetID());
	AerAssert(serv != nullptr);

	thr.startThread(std::ref(*serv));
	thr.detach();
}

//////////////////////////////////////////////////////////////////////////
// Singleton private methods
//////////////////////////////////////////////////////////////////////////

AerMusicStreamer::AerMusicStreamer()
{

}

AerMusicStreamer::~AerMusicStreamer()
{

}