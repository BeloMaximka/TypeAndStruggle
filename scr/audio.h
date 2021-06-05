#pragma once

#define CHANNEL_SHIFT 1

void InitAudio();
void PlaySound(int SoundID, int AdditionalTimes = 0);
void SetSFXVolume(double Volume);
void PlayMusic(Mix_Music* Track);
void SetMusicVolume(double Volume);