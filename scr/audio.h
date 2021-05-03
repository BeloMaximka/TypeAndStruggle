#pragma once

void InitAudio();
void PlaySound(Mix_Chunk* Sound, int AdditionalTimes = 0);
void SetSFXVolume(double Volume);
void PlayMusic(Mix_Music* Track);
void SetMusicVolume(double Volume);