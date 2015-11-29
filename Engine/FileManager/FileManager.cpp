
#include "../Core/Assert.h"
#include "FileManager.h"

ASEFileManager* ASEFileManager::fmInstance = nullptr;

ASEFileManager& ASEFileManager::instance()
{
	if (fmInstance == nullptr)
	{
		fmInstance = new ASEFileManager();
	}

	return *fmInstance;
}

FileResult ASEFileManager::OpenFile(const TChar* filename, FileHandle& fHandle)
{
	FileResult result = FILE_SUCCESS;
	Int fileIndex = instance().FindFileInList(filename);

	if (fileIndex < 0)
	{
		FileExt extension = ExtractExtension(filename);
		File* file = new File(filename, extension);

		// Append the asset file path
		char relativePath[MaxFileNameLength];
		strcpy(relativePath, AssetPath);
		strcat(relativePath, filename);

		// Open file using full relative path
		file->fHandle = fopen(relativePath, "rb");
		AerAssert(file->fHandle);
		++file->handleCount;

		instance().fileList.push_back(file);
		fHandle = instance().fileList.size() - 1;
	}
	else
	{
		// Update reference count
		File* file = instance().fileList[fileIndex];
		++file->handleCount;

		fHandle = fileIndex;
	}

	return result;
}

Int ASEFileManager::FindFileInList(const TChar* fname)
{
	Int index = -1;

	for (UInt i = 0; i < fileList.size(); ++i)
	{
		File* file = fileList[i];
		if (file != nullptr && strcmp(file->fileName, fname) == 0)
		{
			index = i;
			break;
		}
	}

	return index;
}

FileExt ASEFileManager::ExtractExtension(const TChar* fname)
{
	char* prevStr = nullptr;
	char* currStr;
	char fnameCpy[MaxFilePathLength];

	strcpy(fnameCpy, fname);
	currStr = strtok(fnameCpy, ".");

	while (currStr != nullptr)
	{
		prevStr = currStr;
		currStr = strtok(nullptr, ".");
	}

	return FileExt(prevStr);
}

FileResult ASEFileManager::CloseFile(FileHandle fHandle)
{
	FileResult result = FILE_SUCCESS;
	File* file = instance().fileList[fHandle];

	--file->handleCount;
	if (file->handleCount == 0)
	{
		delete file;
		instance().fileList[fHandle] = nullptr;
	}
	else
	{
		result = FILE_CLOSE_HANDLE_STILL_OPEN;
	}

	return result;
}

FileExt ASEFileManager::GetFileExtention(FileHandle fHandle)
{
	File* file = instance().fileList[fHandle];

	return file->ext;
}

FileResult ASEFileManager::Seek(FileHandle fHandle, Int offset, SeekLocation seekOption)
{
	FileResult result = FILE_SUCCESS;
	File* file = instance().fileList[fHandle];

	fseek(file->fHandle, offset, seekOption);

	// Returns non-zero if there's an error
	if (ferror(file->fHandle))
	{
		result = FILE_SEEK_ERROR;
	}

	return result;
}

FileResult ASEFileManager::Write(FileHandle fHandle, const void* const data, UInt dataSize)
{
	FileResult result = FILE_SUCCESS;
	File* file = instance().fileList[fHandle];
	fwrite(data, sizeof(Byte), dataSize, file->fHandle);

	if (ferror(file->fHandle))
	{
		//AerFail("Couldn't write to the file");
		result = FILE_WRITE_ERROR;
	}

	return result;
}

FileResult ASEFileManager::Read(FileHandle fHandle, void* const data, UInt dataSize, UInt& bytesRead)
{
	FileResult result = FILE_SUCCESS;
	File* file = instance().fileList[fHandle];

	bytesRead = fread(data, sizeof(Byte), dataSize, file->fHandle);

	if (bytesRead != dataSize)
	{
		if (!feof(file->fHandle))
		{
			result = FILE_READ_ERROR;
		}
	}

	return result;
}

FileResult ASEFileManager::Flush(FileHandle fHandle)
{
	FileResult result = FILE_SUCCESS;
	File* file = instance().fileList[fHandle];

	Int flushResult = fflush(file->fHandle);

	if (flushResult == EOF)
	{
		//AerFail("Flush resulted in an error");
		result = FILE_FLUSH_ERROR;
	}

	return result;
}
