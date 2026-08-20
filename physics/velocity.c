#include "velocity.h"

float calc_move(float *coordinate, float distance, float time, Uint64 *last_time){
    Uint64 now = SDL_GetTicks();
    Uint64 delta_t = now - *last_time;
    *last_time = now;
    float velocity = distance / time;
    return (float)delta_t * velocity;
}

void do_move(float *coordinate, float target, float distance, float time, Uint64 *last_time){
    if(last_time){
        float delta_distance = calc_move(coordinate, distance, time, last_time);
        if((*coordinate + delta_distance) > target){
            *coordinate = target;
            last_time = NULL;
        }else{
            *coordinate += delta_distance;
        }
    }
}