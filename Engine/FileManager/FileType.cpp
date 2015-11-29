
#include "FileType.h"
#include "string.h"

//////////////////////////////////////////////////////////////////////////
// FileExt struct
//////////////////////////////////////////////////////////////////////////

FileExt::FileExt(TChar* exten)
{
	extention = new TChar[MaxFileExtLength];
	strcpy(extention, exten);
}

FileExt::FileExt(const FileExt& fExt)
{
	extention = new TChar[MaxFileExtLength];
	strcpy(extention,fExt.extention);
}

FileExt& FileExt::operator=(const FileExt& fExt)
{
	if (this != &fExt)
	{
		if (extention == nullptr)
		{
			delete extention;
		}

		extention = new TChar[MaxFileExtLength];
		strcpy(extention, fExt.extention);
	}

	return *this;
}

Bool FileExt::operator==(const TChar* fileExt) const
{
	Bool result = FALSE;
	if (strcmp(extention, fileExt) == 0)
	{
		result = TRUE;
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////
// File class
//////////////////////////////////////////////////////////////////////////

File::File(const TChar* fname, const FileExt& extension)
	: fileName(fname),
	fHandle(nullptr),
	handleCount(0)
{
	ext = extension;
}

File::File(const File& file)
	: fileName(file.fileName), 
	fHandle(file.fHandle), 
	handleCount(file.handleCount),
	ext(file.ext)
{
}

File& File::operator=(const File& file)
{
	if (this != &file)
	{
		fileName = file.fileName;
		fHandle = file.fHandle;
		handleCount = file.handleCount;
		ext = file.ext;
	}

	return *this;
}

File::~File()
{
	fclose(fHandle);
}
