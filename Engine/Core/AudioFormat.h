#pragma once

#include "CoreDefs.h"

enum AerFormatStructure
{
	// Pulse Code Modulation format
	AUDIO_FORMAT_PCM = 0x1000,

	// Higher resolution format
	AUDIO_FORMAT_HIGH_RES,

	// Vorbis format
	AUDIO_FORMAT_OGG_VORBIS,
};

// Converts WaveFormatEx format tag to engine flag
AerFormatStructure AudioFormatStructureConversion(UInt16 formatTag);
// Converts engine flag to WaveFormatEx format tag
UInt16 FormatTagConversion(AerFormatStructure format);

struct AudioFormat
{
	// Extra data used for more complex audio data
	struct ComplexAudioData* complexData;

	// samples per second of audio
	UInt32 samplesPerSec;

	// number of channels
	UInt16 numChannels;

	// number of bits per sample, for specified audio structure
	UInt16 bitsPerSample;

	// Size, in bytes, of extra data
	UInt16 extraInfoSize;

	// Declaring the structure used
	AerFormatStructure audioStructure;

	AudioFormat()
		: complexData(nullptr),
		samplesPerSec(0),
		numChannels(0),
		bitsPerSample(0),
		extraInfoSize(0),
		audioStructure(AUDIO_FORMAT_PCM)
	{}
};

struct ComplexAudioData
{

};

struct AudioData
{
	// Size of raw data
	UInt32 audioDataSize;

	// audio data buffer
	Byte* audioData;

	AudioData(){}
	~AudioData()
	{
		delete audioData;
	}
};

struct AudioPacket
{
	AudioFormat format;
	AudioData data;
};