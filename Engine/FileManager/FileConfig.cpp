
#include "FileConfig.h"
#include "FileManager.h"
#include "../Core/Assert.h"
#include "../Core/XAudio2Sound.h"

#ifdef _WIN32
// RIFF chunk headers (Little-Endian)
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif // _WIN32


FileConfig::FileConfig()
{
	wfx = { 0 };
	xa2buff = { 0 };
	fileData = nullptr;
}

FileConfig::~FileConfig()
{

}

//////////////////////////////////////////////////////////////////////////
// WavFileConfig
//////////////////////////////////////////////////////////////////////////

AudioFormat WavFileConfig::parseHeader(FileHandle handle)
{
	UInt32 chunkSize, chunkPos;
	UInt32 filetype;
	findChunk(handle, fourccRIFF, chunkSize, chunkPos);
	readRIFFHeader(handle, &filetype, chunkPos);
	AerAssert(filetype == fourccWAVE);

	AudioFormat format;
	findChunk(handle, fourccFMT, chunkSize, chunkPos);
	readAudioFormat(handle, &format, chunkPos);

	return format;
}

AudioPacket* WavFileConfig::parse(FileHandle handle)
{
	UInt32 chunkSize, chunkPos;
	UInt32 filetype;
	findChunk(handle, fourccRIFF, chunkSize, chunkPos);
	readRIFFHeader(handle, &filetype, chunkPos);
	AerAssert(filetype == fourccWAVE);

	AudioFormat format;
	findChunk(handle, fourccFMT, chunkSize, chunkPos);
	readAudioFormat(handle, &format, chunkPos);

	// fill out the audio data buffer with the contents of the fourData chunk
	AudioPacket* pack = new AudioPacket();
	pack->format = format;
	AudioData* data = &pack->data;
	findChunk(handle, fourccDATA, chunkSize, chunkPos);
	data->audioData = new Byte[chunkSize];
	readChunkData(handle, data->audioData, chunkSize, chunkPos);
	data->audioDataSize = chunkSize;

	return pack;
}

void WavFileConfig::readRIFFHeader(FileHandle fHandle, UInt32* fileType, UInt32 headerOffset)
{
	FileResult result = FILE_SUCCESS;
	result = ASEFileManager::Seek(fHandle, headerOffset, SEEK_FILE_START);
	UInt32 numBytesRead;
	ASEFileManager::Read(fHandle, fileType, sizeof(UInt32), numBytesRead);
}

void WavFileConfig::readAudioFormat(FileHandle fHandle, AudioFormat* format, UInt32 headerOffset)
{
	UNUSED(format);
	UNUSED(headerOffset);
//	WAVEFORMATEXTENSIBLE wfx = { 0 };
	FileResult result = FILE_SUCCESS;
	result = ASEFileManager::Seek(fHandle, headerOffset, SEEK_FILE_START);
	UInt32 numBytesRead;
	UInt16 formatTag;
	// Format tag
	result = ASEFileManager::Read(fHandle, &formatTag, sizeof(UInt16), numBytesRead);
	format->audioStructure = AudioFormatStructureConversion(formatTag);
	
	// Get number of channels
	result = ASEFileManager::Read(fHandle, &format->numChannels, sizeof(UInt16), numBytesRead);
	
	// Get the samples per second
	result = ASEFileManager::Read(fHandle, &format->samplesPerSec, sizeof(UInt32), numBytesRead);
	
	// Skip irrelevant data
	result = ASEFileManager::Seek(fHandle, sizeof(UInt32) + sizeof(UInt16), SEEK_FILE_CURRENT);
	
	// Bits per sample
	result = ASEFileManager::Read(fHandle, &format->bitsPerSample, sizeof(UInt16), numBytesRead);
}

void WavFileConfig::readAudioData(FileHandle fHandle, Byte* const audioData, UInt32 dataSize, UInt32 bufferOffset)
{
	FileResult result = FILE_SUCCESS;
	result = ASEFileManager::Seek(fHandle, bufferOffset, SEEK_FILE_START);
	UInt32 numBytesRead;
	ASEFileManager::Read(fHandle, audioData, dataSize, numBytesRead);
}

void WavFileConfig::findChunk(FileHandle fHandle, UInt32 charCode, UInt32& uChunckSize, UInt32& uChunkDataPos)
{
	AerAssert(ASEFileManager::Seek(fHandle, 0, SEEK_FILE_START) == FILE_SUCCESS);

	UInt32 chunkType;
	UInt32 RIFFDataSize = 0;
	UInt32 chunkDataSize;
	UInt32 offset = 0;
	FileResult result = FILE_SUCCESS;

	do
	{
		UInt32 numBytesRead;

		result = ASEFileManager::Read(fHandle, &chunkType, sizeof(UInt32), numBytesRead);
		result = ASEFileManager::Read(fHandle, &chunkDataSize, sizeof(UInt32), numBytesRead);

		switch (chunkType)
		{
		case fourccRIFF:
		{
			RIFFDataSize = chunkDataSize;
			chunkDataSize = 4;
			ASEFileManager::Seek(fHandle, chunkDataSize, SEEK_FILE_CURRENT);
		}
			break;
		default:
		{
			ASEFileManager::Seek(fHandle, chunkDataSize, SEEK_FILE_CURRENT);
		}
			break;
		}

		offset += sizeof(UInt32) * 2;

		if (chunkType == charCode)
		{
			uChunckSize = chunkDataSize;
			uChunkDataPos = offset;
			return;
		}

		offset += chunkDataSize;

		if (numBytesRead >= RIFFDataSize)
			return;

	} while (result == FILE_SUCCESS);

	return;
}

void WavFileConfig::readChunkData(FileHandle fHandle, void* const buffer, UInt32 buffSize, UInt32 bufferOffset)
{
	FileResult result = FILE_SUCCESS;
	result = ASEFileManager::Seek(fHandle, bufferOffset, SEEK_FILE_START);
	UInt32 numBytesRead;
	ASEFileManager::Read(fHandle, buffer, buffSize, numBytesRead);
}

//////////////////////////////////////////////////////////////////////////
// FileConfiguration
//////////////////////////////////////////////////////////////////////////

FileConfig* FileConfiguration::IsFileFormatSupported(const FileExt& ext)
{
	FileConfig* fConfig = nullptr;
	if (ext == WAV_FILE)
	{
		fConfig = new WavFileConfig();
	}
	else if (ext == OGG_FILE)
	{

	}
	
	return fConfig;
}