#pragma once

#include <vector>

#include "FileType.h"

enum FileResult
{
	FILE_SUCCESS,

	FILE_OPEN_UNSUPPORTED_FILE,
	FILE_OPEN_ERROR,

	FILE_WRITE_ERROR,
	FILE_READ_ERROR,

	FILE_CLOSE_HANDLE_STILL_OPEN,
	FILE_CLOSE_ERROR,

	FILE_SEEK_ERROR,

	FILE_FLUSH_ERROR
};

enum SeekLocation
{
	SEEK_FILE_START		= SEEK_SET,
	SEEK_FILE_CURRENT	= SEEK_CUR,
	SEEK_FILE			= SEEK_END
};

class ASEFileManager
{
public:
	static FileResult OpenFile(const TChar* filename, FileHandle& fHandle);
	static FileResult CloseFile(FileHandle fHandle);

	static FileExt GetFileExtention(FileHandle fHandle);
	
	static FileResult Seek(FileHandle fHandle, Int32 offset, SeekLocation seekOption);

	static FileResult Write(FileHandle fHandle, const void* const data, UInt32 dataSize);
	static FileResult Read(FileHandle fHandle, void* const data, UInt32 dataSize, UInt32& bytesRead);
	static FileResult Flush(FileHandle fHandle);

protected:
	static ASEFileManager* fmInstance;

	Int32 FindFileInList(const TChar* fname);
	static FileExt ExtractExtension(const TChar* fname);

	static ASEFileManager& instance();

	std::vector<struct File *> fileList;

	ASEFileManager() {}
	~ASEFileManager() {}
};

