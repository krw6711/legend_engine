#ifndef VELOCITY_H
#define VELOCITY_H

#include "../global/globals.h"

float calc_move(float *coordinate, float distance, float time, Uint64 *last_time);
void do_move(float *coordinate, float target, float distance, float time, Uint64 *last_time);

#endif