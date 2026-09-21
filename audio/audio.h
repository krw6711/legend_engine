#ifndef AUDIO_H
#define AUDIO_H
#include "../global/globals.h"

int init_stearms(void);
int init_audio_files(void);
void cleanup_audio(void);
void play_music(int id);
void stop_music();
void play_sfx(int id);
#endif