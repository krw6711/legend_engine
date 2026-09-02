#ifndef VELOCITY_H
#define VELOCITY_H
#include "../global/globals.h"
#include "../entities/entity.h"

float calc_new_distance(float velocity, float *last_time);
void start_moving(Player_t *object, float velocity, float delta_distance);
void stop_moving(Player_t *object);
void move(Player_t *object); 

#endif