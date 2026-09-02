#include "camera.h"
#include "../global/globals.h"
#include "../physics/velocity.h"
#include <math.h>

Camera_t camera = {
    {0,0,0,false, NONE},
    0, 0,
    CAMERA_X_CELLS,CAMERA_Y_CELLS
};

void start_moving_camera(Face_t dir){
    if(!camera.move.moving){
        camera.move.moving = true;
        camera.move.dir = dir;
        camera.move.last_time = (float)SDL_GetTicks()/1000;
        camera.move.passed = 0;
        camera.move.queued = NONE;
        camera.c_x = roundf(camera.c_x);
        camera.c_y = roundf(camera.c_y);
    }
}
void stop_moving_camera(void){
    if(camera.move.moving){
        SDL_Log("no moves");
        camera.move.moving = false;
        camera.move.last_time = 0;
        camera.move.passed = 0;
    }
    if(camera.move.queued != NONE && !camera.move.moving){
        SDL_Log("a queued movment is moving");
        start_moving_camera(camera.move.queued);
    }
};

void moving_camera(){
    if(camera.move.moving){
        float delta_distance = calc_new_distance(2, &camera.move.last_time);
        if(camera.move.passed + delta_distance >= 1){
            delta_distance = 1 - camera.move.passed;
        }
        camera.move.passed += delta_distance;
        switch (camera.move.dir) {
            case UP:
                camera.c_y -= delta_distance;
                if(camera.c_y <= (-4)) stop_moving_camera();
                break;
            case DOWN:
                camera.c_y += delta_distance;
                if(camera.c_y >= (MAP_ROWS - CAMERA_Y_CELLS + 4)) stop_moving_camera();
                break;
            case RIGHT:
                camera.c_x += delta_distance;
                if(camera.c_x >= (MAP_COLS - CAMERA_X_CELLS + 4)) stop_moving_camera();
                break;
            case LEFT:
                camera.c_x -= delta_distance;
                if(camera.c_x <= (-4)) stop_moving_camera();
                break;
            case NONE:
                break;
        }
        if(camera.move.passed >= 1){
            stop_moving_camera();
        }
    }
}
