#pragma once

class OSInternalSound;
struct StreamBuffer;

class StreamService;

namespace Aer
{
	class Handle;

	Handle* CreateMusic(const TChar* filename, const TChar* name);

	class Music
	{
	public:
		void StartStreaming();
		void EndStreaming();

		void BeginProcessing();
		void StopProcessing();

		void PushData(StreamBuffer* buffer, UInt32 amountBuffered, UINT32 offset, Bool endOfStream = FALSE);

		Music(const TChar* const name, OSInternalSound* mus);
		~Music();

		Music(const Music&) = delete;
		Music& operator=(const Music&) = delete;

		MusicID GetID() const
		{
			return musicID;
		}
		void SetService(StreamService* serv)
		{
			serviceRef = serv;
		}
		StreamService* GetService()
		{
			return serviceRef;
		}

		bool operator==(Music& mus) const
		{
			return musicID == mus.musicID;
		}
		bool operator==(const MusicID mus) const
		{
			return musicID == mus;
		}

	protected:
		OSInternalSound* hardwareStream;

		FileHandle fHandle;
		const TChar* musicName;
		StreamService* serviceRef;
		const MusicID musicID;

	};
}