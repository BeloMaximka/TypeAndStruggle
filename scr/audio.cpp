#include "main.h"

void InitAudio()
{
	
	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
		WriteInLog("[ERROR] Mix_Init error: %s", Mix_GetError());
		return;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096) == -1) {
		WriteInLog("[ERROR] Mix_OpenAudio error: %s", Mix_GetError());
		return;
	}
}

// ���� AdditionalTimes -1, �� ���� ����� ������������� ����������
void PlaySound(Mix_Chunk* Sound, int AdditionalTimes)
{
	if (Mix_PlayChannel(-1, Sound, AdditionalTimes) == -1) {
		WriteInLog("[ERROR] Mix_PlayChannel error: %s", Mix_GetError());
	}
}

void SetSFXVolume(double Volume)
{
	Mix_Volume(-1, MIX_MAX_VOLUME * Volume);
}

void PlayMusic(Mix_Music* Track)
{
	if (Mix_PlayMusic(Track, -1) == -1) {
		WriteInLog("[ERROR] Mix_PlayMusic error: %s", Mix_GetError());
	}
}

void SetMusicVolume(double Volume)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME * Volume);
}