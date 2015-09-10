#pragma once


enum FileResult
{
	FILE_OPEN_SUCCESS				= 0x0,
	FILE_OPEN_UNSUPPORTED_FILE		= 0x1,
	FILE_OPEN_FAIL					= 0x2,

	FILE_READ_BUFFER_TOO_SMALL		= 0x4,
	FILE_READ_NO_IMPLEMENTATION		= 0x8,

	FILE_WRITE_NO_IMPLEMENTATION	= 0x10,
};

class ASEFileManager
{
public:
	static FileResult OpenFile(/* Params here */);
	static FileResult CloseFile(/* Params here */);
	
	static FileResult WriteFileToDisk(/* Params here */);
	static FileResult ReadFileFromDisk(/* Params here */);

protected:
	static ASEFileManager* fmInstance;

	virtual FileResult privWriteFileToDisk(/* Params here */);
	virtual FileResult privReadFileFromDisk(/* Params here */);

	virtual FileResult privOpenFile(/* Params here */);
	virtual FileResult privCloseFile(/* Params here */);

	ASEFileManager() {}
	virtual ~ASEFileManager() {}
};

