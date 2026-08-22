#include "camera.h"
#include "../global/globals.h"
#include "../physics/velocity.h"
#include "map.h"

Camera_t camera = {
    {0,0,0,false},
    0, 0,
    CAMERA_X_CELLS,CAMERA_Y_CELLS
};

void start_moving_camera(Face_t dir){
    if(!camera.move.moving){
        camera.move.moving = true;
        camera.move.dir = dir;
        camera.move.last_time = (float)SDL_GetTicks()/1000;
        camera.move.passed = 0;
    }
}
void stop_moving_camera(void){
    if(camera.move.moving){
        camera.move.moving = false;
        camera.move.last_time = 0;
        camera.move.passed = 0;
    }
};

void moving_camera(){
    if(camera.move.passed >= 1 || is_camera_collusion()){
        stop_moving_camera();
    }
    if(camera.move.moving){
        float delta_distance = calc_new_distance(4, &camera.move.last_time);
        if(camera.move.passed + delta_distance >= 1){
            delta_distance = 1 - camera.move.passed;
        }
        camera.move.passed += delta_distance;
        switch (camera.move.dir) {
            case UP:
                camera.c_y -= delta_distance;
                break;
            case DOWN:
                camera.c_y += delta_distance;
                break;
            case RIGHT:
                camera.c_x += delta_distance;
                break;
            case LEFT:
                camera.c_x -= delta_distance;
                break;
        }
    }
}

bool is_camera_collusion(){
    switch (camera.move.dir) {
        case UP:
            if(camera.c_y <= (camera.w_y - 3)) return true;
        case DOWN:
            if(camera.c_y >= (camera.w_y + 3)) return true;
        case RIGHT:
            if(camera.c_x >= (camera.w_x + 3)) return true;
        case LEFT:
            if(camera.c_x <= (camera.w_x - 3)) return true;
    }
    return false;
}