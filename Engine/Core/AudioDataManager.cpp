
#include "AudioDataManager.h"
#include "XAudio2Sound.h"
#include "XAudio2Stream.h"
#include "AudioFormat.h"

#include "../FileManager/FileManager.h"
#include "../FileManager/FileConfig.h"
#include "../FileManager/FileType.h"

XAudio2Sound* AudioDataManager::ParseAudioData(const TChar* filename)
{
	FileHandle fHnd;
	ASEFileManager::OpenFile(filename, fHnd);
	return instance().ParseAudioDataInternal(fHnd);
}

XAudio2Sound* AudioDataManager::ParseAudioData(FileHandle fHnd)
{
	return instance().ParseAudioDataInternal(fHnd);
}

XAudio2Sound* AudioDataManager::ParseAudioDataInternal(FileHandle fHandle)
{
	FileExt extension = ASEFileManager::GetFileExtention(fHandle);

	FileConfig* config = FileConfiguration::IsFileFormatSupported(extension);
	AudioPacket* packet = config->parse(fHandle);
	packetList.push_back(packet);

	ASEFileManager::CloseFile(fHandle);

	XAudio2Sound* hardwareSnd = new XAudio2Sound(packet, nullptr);
	winSoundList.push_back(hardwareSnd);

	return hardwareSnd;
}

XAudio2Stream* AudioDataManager::ParseAudioHeader(FileHandle fHnd)
{
	return instance().ParseAudioHeaderInternal(fHnd);
}

XAudio2Stream* AudioDataManager::ParseAudioHeaderInternal(FileHandle fHandle)
{
	FileExt extension = ASEFileManager::GetFileExtention(fHandle);

	FileConfig* config = FileConfiguration::IsFileFormatSupported(extension);
	AudioFormat format = config->parseHeader(fHandle);

	XAudio2Stream* hardwareSnd = new XAudio2Stream(format);

	return hardwareSnd;
}

//////////////////////////////////////////////////////////////////////////
// AudioDataManager Singleton methods
//////////////////////////////////////////////////////////////////////////

AudioDataManager& AudioDataManager::instance()
{
	static AudioDataManager admInstance;

	return admInstance;
}

AudioDataManager::AudioDataManager()
{
#ifdef _WIN32
	winSoundList.reserve(INITIAL_RESERVE);
#else

#endif
	packetList.reserve(INITIAL_RESERVE);
}

AudioDataManager::~AudioDataManager()
{
	while (!packetList.empty())
	{
		const AudioPacket* pack = packetList.back();
		packetList.pop_back();
		delete pack;

#ifdef _WIN32
		XAudio2Sound* snd = winSoundList.back();
		winSoundList.pop_back();
		delete snd;
#else

#endif
	}
}
