#pragma once

#include <vector>

#include "CoreDefs.h"

#define INITIAL_RESERVE 10

class XAudio2Sound;
class XAudio2Stream;
struct AudioPacket;

class AudioDataManager
{
public:
#ifdef _WIN32
	static XAudio2Sound* ParseAudioData(const TChar* filename);
	static XAudio2Sound* ParseAudioData(FileHandle fHnd);

	static XAudio2Stream* ParseAudioHeader(FileHandle fHnd);
#endif
private:
	AudioDataManager();
	~AudioDataManager();

	XAudio2Sound* ParseAudioDataInternal(FileHandle fHandle);

	XAudio2Stream* ParseAudioHeaderInternal(FileHandle fHandle);

	static AudioDataManager& instance();

#ifdef _WIN32
	std::vector<XAudio2Sound*> winSoundList;
#else

#endif
	std::vector<const AudioPacket*> packetList;
};