
#include "AudioFormat.h"
#include "Assert.h"

AerFormatStructure AudioFormatStructureConversion(UInt16 formatTag)
{
	AerFormatStructure format;
	switch (formatTag)
	{
	case WAVE_FORMAT_PCM:
	{
		format = AUDIO_FORMAT_PCM;
	}break;
	case WAVE_FORMAT_EXTENSIBLE:
	{
		format = AUDIO_FORMAT_HIGH_RES;
	}break;
	case WAVE_FORMAT_OGG_VORBIS_MODE_1:
	{
		format = AUDIO_FORMAT_OGG_VORBIS;
	}break;
	default:
	{
		AerAssert(false);
	}break;
	}

	return format;
}

UInt16 FormatTagConversion(AerFormatStructure format)
{
	UInt16 formatTag;
	switch (format)
	{
	case AUDIO_FORMAT_PCM:
	{
		formatTag = WAVE_FORMAT_PCM;
	}break;
	case AUDIO_FORMAT_HIGH_RES:
	{
		formatTag = WAVE_FORMAT_EXTENSIBLE;
	}break;
	case AUDIO_FORMAT_OGG_VORBIS:
	{
//		formatTag = WAVE_FORMAT_OGG_VORBIS_MODE_1;
	}break;
	default:
		AerAssert(FALSE);
		break;
	}

	return formatTag;
}