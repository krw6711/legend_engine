#ifndef VELOCITY_H
#define VELOCITY_H

#include "../global/globals.h"
#include "../map/map.h"

float calc_new_distance(float velocity, float *last_time);
void start_moving(Object_t *object, float velocity, float delta_distance, Face_t face);
void stop_moving(Object_t *object);
void move(Object_t *object);
 

#endif