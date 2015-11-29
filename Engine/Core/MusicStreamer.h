#pragma once

#include "CoreDefs.h"
#include "../FileManager/FileManager.h"
#include "AerCondVar.h"
#include "Thread.h"
#include "AerList.h"

struct AerStreamSettings
{

};

namespace Aer
{
	class Music;

	namespace Stream
	{
		void GetDefaultSettings(AerStreamSettings& settings);
		void Initialize(const AerStreamSettings& streamInitSettings);
		void Terminate();
	}
}

class XAudio2Stream;
class StreamService;

class AerMusicStreamer
{
public:
	AER_SINGLETON(AerMusicStreamer);

	static void Init(const AerStreamSettings& settings);
	static void Term();

	static void StartLoadedStream(Aer::Music* musicToStream);

	static Aer::Music* CreateStream(const TChar* const filename, const TChar* const streamName);

	// For StreamService use only:
	// Because it is the only object with a direct
	// reference to the internal MusicStreamer object
	void StreamEnded(StreamService* finishedStream);

private:

	void InitInternal(const AerStreamSettings& settings);
	void TermInternal();

	AerList<StreamService*> streamingMusic;

};