#pragma once

#include "CoreDefs.h"

namespace Aer
{
	class Sound;
	class Music;

	class Handle
	{
	public:
		virtual void Play() = 0;
		virtual void Pause() = 0;
		virtual void Stop() = 0;
		virtual void Restart() = 0;
		virtual void SeekPosition(Float milliseconds) = 0;
	};

	class SoundHandle : public Handle
	{
	public:
		virtual void Play() override;
		
		// TODO: Needs to be implemented
		virtual void Pause() override;
		virtual void Stop() override;
		virtual void Restart() override;
		virtual void SeekPosition(Float milliseconds) override;

		SoundHandle(Sound* sndRef);
		~SoundHandle();
		SoundHandle(const SoundHandle& sh);
		SoundHandle& operator=(const SoundHandle& sh);
	private:
		Sound* sndRef;
	};

	class MusicHandle : public Handle
	{
	public:
		virtual void Play() override;

		// TODO: Needs to be implemented
		virtual void Pause() override {}
		virtual void Stop() override {}
		virtual void Restart() override {}
		virtual void SeekPosition(Float milliseconds) override { UNUSED(milliseconds); };

		MusicHandle(Music* musRef);
		~MusicHandle();
		MusicHandle(const MusicHandle& mh);
		MusicHandle& operator=(const MusicHandle& mh);
	private:
		Music* musRef;
	};
}