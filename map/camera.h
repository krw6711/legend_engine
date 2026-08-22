#ifndef CAMERA_H
#define CAMERA_H
#include "map.h"
#include <stdbool.h>

typedef struct{
    float last_time;
    float passed;
    Face_t dir;
    bool moving;
} Camera_move_t;

typedef struct {
    Camera_move_t move;
    float c_x,c_y;// c-> coordinates
    int w_x, w_y; // b -> borders, the end coordinates of borders 
} Camera_t;

extern Camera_t camera;

bool is_camera_collusion();
void start_moving_camera(Face_t dir);
void stop_moving_camera(void);
void moving_camera(void);

#endif