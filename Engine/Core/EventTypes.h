#pragma once

enum PlayType
{
	PLAY = 0x10
};

enum StopType
{
	STOP = 0x20,
	STOP_ALL
};

enum PauseType
{
	PAUSE = 0x30,
	PAUSE_ALL
};

enum ResumeType
{
	RESUME = 0x40,
	RESUME_ALL
};

enum MuteType
{
	MUTE = 0x50,
	UNMUTE,
	UNMUTE_ALL
};

enum VolumeType
{
	SET_VOLUME = 0x60,
	RESET_VOLUME,
	RESET_VOLUME_ALL
};

enum SeekType
{
	SEEK = 0x70
};

enum PitchType
{
	SET_PITCH = 0x80,
	RESET_PITCH,
	RESET_PITCH_ALL
};
