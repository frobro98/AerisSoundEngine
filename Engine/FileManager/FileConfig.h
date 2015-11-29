#pragma once

#include "../Core/CoreDefs.h"
#include "FileType.h"
#include "../Core/AudioFormat.h"

class XAudio2Sound;


class FileConfig
{
public:
	virtual AudioPacket* parse(FileHandle handle) = 0;
	virtual AudioFormat parseHeader(FileHandle handle) = 0;

	FileConfig();
	virtual ~FileConfig();

	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER xa2buff;
	Byte* fileData;
};

class WavFileConfig : public FileConfig
{
public:
	WavFileConfig()
	{}
	~WavFileConfig()
	{}

	virtual AudioPacket* parse(FileHandle handle) override;
	virtual AudioFormat parseHeader(FileHandle handle) override;

private:
	void findChunk(FileHandle fHandle, UInt32 charCode, UInt32& uChunckSize, UInt32& uChunkDataPos);

	void readRIFFHeader(FileHandle fHandle, UInt32* fileType, UInt32 headerOffset);
	void readAudioFormat(FileHandle fHandle, AudioFormat* format, UInt32 headerOffset);
	void readAudioData(FileHandle fHandle, Byte* const audioData, UInt32 dataSize, UInt32 bufferOffset);

	void readChunkData(FileHandle fHandle, void* const buffer, UInt32 buffSize, UInt32 bufferOffset);
};

class FileConfiguration
{
public:
	static FileConfig* IsFileFormatSupported(const FileExt& ext);

};