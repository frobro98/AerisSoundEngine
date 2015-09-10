#pragma once

#include "CoreDefs.h"

enum SupportedFiles : Int
{
	FILE_EXT_VORB = 0,
	FILE_EXT_FLAC, // Double check this is cross-platform
#ifdef _WIN32
	FILE_EXT_WAV,
#else
	FILE_EXT_M4A,
#endif
	FILE_EXT_MP4
};

struct FileExt
{
	const TChar* extention;
};

class File // RAII
{
public:
	File();
	~File();

	void getData(const Byte* buffer, size_t bufferSize);
private:
	void privOpen();


	FileExt ext;
	const char* fileName;
	FILE* fHandle;
};