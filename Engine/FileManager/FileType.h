#pragma once

#include "../Core/CoreDefs.h"

// Supported file extention
#define WAV_FILE "wav"
#define OGG_FILE "ogg"

// File constants
static const UInt32 MaxFilePathLength = 128;
static const UInt32 MaxFileNameLength = 64;
static const UInt32 MaxFileExtLength = 8;

static const TChar* AssetPath = "../Assets/";

struct FileExt
{
	TChar* extention;

	FileExt(){ extention = nullptr; }
	FileExt(TChar* exten);
	FileExt(const FileExt& fExt);
	FileExt& operator=(const FileExt& fExt);
	~FileExt(){ delete extention; }

	Bool operator==(const TChar* ext) const;
};

struct File
{
	File(const TChar* fname, const FileExt& ext);
	~File();
	File(const File&);
	File& operator=(const File&);

	FileExt ext;
	FILE* fHandle;
	const TChar* fileName;
	UInt32 handleCount;
};