#include "SDL3/SDL_log.h"
#include "globals.h"
#include "iterate_event.h"
#include "../map/map.h"
// #include "../physics/velocity.h"

void joystick_iterate_event(){
    // move up, get close to y = 0
    if (SDL_GetJoystickAxis(joystick, 1) < -24543 && (camera.y + MAP_CELL_SIZE) <= 0 && (camera.y + MAP_CELL_SIZE) >= ((MAP_ROWS * MAP_CELL_SIZE)*-1) + WINDOW_HEIGHT){
        SDL_Log("up");
    }

    // move down, get far from y = 0
    if (SDL_GetJoystickAxis(joystick, 1) > 24543  )
    {
        SDL_Log("down");
    }

    // move right, get far from x = 0
    if (SDL_GetJoystickAxis(joystick, 0) > 24543 ){
        SDL_Log("right");
    }

    // move left, get close to x = 0
    if (SDL_GetJoystickAxis(joystick, 0) < -24543){
        SDL_Log("left");
    }

}