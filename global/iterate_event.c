#include "globals.h"
#include "iterate_event.h"
#include "../map/map.h"
#include "../physics/velocity.h"
#include <asm-generic/errno.h>

void joystick_iterate_event(){
    // move up, get close to y = 0
    if (SDL_GetJoystickAxis(joystick, 1) < -24543){
        SDL_Log("up");
        start_moving(&camera, 0.05 , 50, UP);
    }

    // move down, get far from y = 0
    if (SDL_GetJoystickAxis(joystick, 1) > 24543 )
    {
        SDL_Log("down");
        start_moving(&camera, 0.05 , 50, DOWN);
    }
    // move right, get far from x = 0
    if (SDL_GetJoystickAxis(joystick, 0) > 24543){
        SDL_Log("right");
        start_moving(&camera, 0.5 , 50, RIGHT);
    }

    // move left, get close to x = 0
    if (SDL_GetJoystickAxis(joystick, 0) < -24543 ){
        SDL_Log("left");
        start_moving(&camera, 0.5 , 50, LEFT);
    }

}

void moving_items(void){
    if(camera.move.moving) move(&camera);
}