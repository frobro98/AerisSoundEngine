#pragma once

#include "CoreDefs.h"

namespace Aer
{
	namespace Constants
	{
		//////////////////////////////////////////////////////////////////////////
		// Aeris Echo Value Definitions
		//////////////////////////////////////////////////////////////////////////

		static const Float MinEchoWetDryRatio = 0.0f;
		static const Float MaxEchoWetDryRatio = 1.0f;
		static const Float DefaultEchoWetDryRatio = 0.5f;

		static const Float MinEchoFeedback = 0.0f;
		static const Float MaxEchoFeedback = 1.0f;
		static const Float DefaultEchoFeedback = 0.5f;

		static const Float MinEchoDelay = 1.0f;
		static const Float MaxEchoDelay = 2000.0f;
		static const Float DefaultEchoDelay = 500.0f;


		//////////////////////////////////////////////////////////////////////////
		// Aeris Reverb Value Definitions
		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////
		// Aeris EQ Value Definitions
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// Aeris Mastering Limiter Value Definitions
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// Aeris Volume Meter Value Definitions
		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////
		// Aeris Effect Description Structures
		//////////////////////////////////////////////////////////////////////////
	}

	struct ReverbDescription
	{
		// Wet Dry mix ratio
		Float WetDryRatio;

		// Delay time of the first reflection
		// Range from 0 to 300 milliseconds
		UInt32 ReflectionsDelay;

		// Delay of reverb relative to first reflection
		// Range from 0 to 85 milliseconds
		Byte ReverbDelay;

		// Delay  for left and right rear output
		// Range from 0 to 5 milliseconds
		Byte RearDelay;

#if (_WIN32_WINNT >= 0x0A00 )
		// Delay for the left and right side output
		// Range from 0 to 5 milliseconds
		Byte SideDelay;
#endif

		// Position for the left input within the simulated space
		// relavitve to the listener
		// Range from 0 to 30
		Byte PositionLeft;

		// Position for the right input within the simulated space
		// relavitve to the listener
		// Range from 0 to 30
		Byte PositionRight;

		// Gives a greater or lesser impression of distance from the
		// source to the listener
		// Range from 0 to 30
		Byte PositionMatrixLeft;

		// Gives a greater or lesser impression of distance from the
		// source to the listener
		// Range from 0 to 30
		// Ignored if in mono
		Byte PositionMatrixRight;

		// Controls the character of the individual wall reverberations
		// Minimum is hard flat surface, Max is diffuse surface
		// Range from 0 to 15
		Byte EarlyDiffusion;

		// Controls the character of the individual wall reverberations
		// Minimum is hard flat surface, Max is diffuse surface
		// Range from 0 to 15 
		Byte LateDiffusion;

		// Adjusts the decay time of low frequencies relative to the decay time
		// at 1 kHz
		// Range from 0 to 12
		//
		// Values correspond to dB of gain in the following table:
		// Value	 0	 1	 2	 3	 4	 5	 6	 7	 8	 9	10  11	12
		// Gain(dB) -8  -7  -6  -5  -4  -3  -2  -1	 0  +1	+2	+3	+4
		Byte LowEQGain;

		// Sets the corner frequency of the low pass filter that is 
		// controlled by the LowEQGain value
		// Range from 0 to 9
		// The values correspond to frequency in Hz as follows:
		// Value			0	1	2	3	4	5	6	7	8	9
		// Frequency(Hz)	50	100	150	200	250	300	350	400	450	500
		Byte LowEQCutoff;

		// Adjusts the decay time of high frequencies relative to the
		// decay time at 1 Hz. 
		// Range from 0 to 8
		// Value	0	1	2	3	4	5	6	7	8
		// Gain(dB) -8 -7  -6  -5  -4  -3  -2  -1	0
		Byte HighEQGain;

		// Sets the corner frequency of the high pass filter that is controlled
		// by the HighEQGain value
		// Range is from 0 to 14
		// The values correspond to frequency in kHz as follows:
		// Value			0	1	2	3	4	5	6	7	8	9	10	11	12	13	14
		// Frequency(kHz)	1  1.5	2  2.5	3  3.5	4  4.5	5  5.5	 6  6.5	 7	7.5  8
		Byte HighEQCutoff;

		// Sets the corner frequency of the low pass filter for the room effect
		// Range from 20 to 20,000 Hz
		Float RoomFilterFreq;

		// Sets the pass band intensity level of the low-pass filter for both the 
		// early reflections and the late field reverberation
		// Range from -100 to 0 dB
		Float RoomFilterMain;

		// Sets the intensity of the low-pass filter for both the early reflections
		// and late field reverberation at corner frequency (RoomFilterFreq)
		// Range from -100 to 0 dB
		Float RoomFilterHF;

		// Adjusts the intesity of early reflections
		// Range from -100 to 20 dB
		Float ReflectionsGain;

		// Adjusts the intesity of the reverberations
		// Range from -100 to 20 dB
		Float ReverbGain;

		// Reverberation decay time at 1 kHz. This is the time that a full scale
		// input signal decays by 60 dB
		// Range from 0.1 to infinity seconds
		Float DecayTime;

		// Controls the modal density in the late field reverberation.
		// Colorless space = 100 (max value)
		// As density decreases, the sound becomes hollow (comb filtered). This effect
		// can be useful if you are trying to model a silo
		// Range from 0 to 100
		Float Density;

		// The apparent size of the acoustic space
		// Range from 0 to 100 feet
		Float RoomSize;
#if (_WIN32_WINNT >= 0x0603 )
		// If set to True, disables late field reflection calculations. Disabling
		// late field calculations result in a significant CPU time savings
		Bool DiableLateField;
#endif

		// Name of the effect
		TChar* effectName;
	};

	struct SimpleReverbDescription
	{
		// Controls the character of the individual wall reflections
		// Minimum simulates a hard flat surface, Max simulates diffuse surface
		Float Diffusion;

		// Size of the room
		Float RoomSize;

		// Name of the effect
		TChar* effectName;
	};

	struct EchoDescription
	{
		// Wet Dry mix ratio
		Float WetDryRatio;

		// Amount of output to feed back into the input
		Float Feedback;

		// Delay to all channels in milliseconds
		// Value must be between MinEchoDelay and MaxEchoDelay
		Float Delay;

		// Name of the effect
		TChar* effectName;
	};

	inline void DefaultEffectSettings(SimpleReverbDescription* desc)
	{
		desc->Diffusion = FXREVERB_DEFAULT_DIFFUSION;
		desc->RoomSize = FXREVERB_DEFAULT_ROOMSIZE;
	}
	inline void DefaultEffectSettings(ReverbDescription* desc)
	{
		/*
		desc->ReflectionsDelay = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_DELAY;
		desc->ReverbDelay = XAUDIO2FX_REVERB_DEFAULT_REVERB_DELAY;
		desc->RearDelay = XAUDIO2FX_REVERB_DEFAULT_REAR_DELAY;
		desc->PositionLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION;
		desc->PositionRight = XAUDIO2FX_REVERB_DEFAULT_POSITION;
		desc->PositionMatrixLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
		desc->PositionMatrixRight = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
		desc->EarlyDiffusion = XAUDIO2FX_REVERB_DEFAULT_EARLY_DIFFUSION;
		desc->LateDiffusion = XAUDIO2FX_REVERB_DEFAULT_LATE_DIFFUSION;
		desc->LowEQGain = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_GAIN;
		desc->LowEQCutoff = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_CUTOFF;
		desc->HighEQGain = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_GAIN;
		desc->HighEQCutoff = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_CUTOFF;
		desc->RoomFilterFreq = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_FREQ;
		desc->RoomFilterMain = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_MAIN;
		desc->RoomFilterHF = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_HF;
		desc->ReflectionsGain = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_GAIN;
		desc->ReverbGain = XAUDIO2FX_REVERB_DEFAULT_REVERB_GAIN;
		desc->DecayTime = XAUDIO2FX_REVERB_DEFAULT_DECAY_TIME;
		desc->Density = XAUDIO2FX_REVERB_DEFAULT_DENSITY;
		desc->RoomSize = XAUDIO2FX_REVERB_DEFAULT_ROOM_SIZE;
		desc->WetDryRatio = XAUDIO2FX_REVERB_DEFAULT_WET_DRY_MIX;
		//*/
		XAUDIO2FX_REVERB_I3DL2_PARAMETERS i3dl2 = XAUDIO2FX_I3DL2_PRESET_DEFAULT;
		ReverbConvertI3DL2ToNative(&i3dl2, reinterpret_cast<XAUDIO2FX_REVERB_PARAMETERS*>(desc));
	}
	inline void DefaultEffectSettings(EchoDescription* desc)
	{
		desc->WetDryRatio = Constants::DefaultEchoWetDryRatio;
		desc->Feedback = Constants::DefaultEchoFeedback;
		desc->Delay = Constants::DefaultEchoDelay;
	}
}

enum Aer_EFFECTTYPE
{
	BASIC_REVERB,
	REVERB,
	ECHO,
	CUSTOM
};