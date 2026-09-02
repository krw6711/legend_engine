#ifndef VELOCITY_H
#define VELOCITY_H
#include "../entities/player.h"

float calc_new_distance(float velocity, float *last_time);
void start_moving(Player_t *object, Coordinates_t new_coord);
void stop_moving(Player_t *object);
void move(Player_t *object); 

#endif