#include "globals.h"
#include "iterate_event.h"
#include "../map/map.h"
#include "../map/camera.h"

void joystick_iterate_event(){
    // move up, get close to y = 0
    if (SDL_GetJoystickAxis(joystick, 1) < -30543){
        SDL_Log("up");
        start_moving_camera(UP);
    }

    // // move down, get far from y = 0
    if (SDL_GetJoystickAxis(joystick, 1) > 30543)
    {
        SDL_Log("down");
        start_moving_camera(DOWN);
    }
    // // move right, get far from x = 0
    if (SDL_GetJoystickAxis(joystick, 0) > 30543){
        SDL_Log("right");
        start_moving_camera(RIGHT);
    }

    // // move left, get close to x = 0
    if (SDL_GetJoystickAxis(joystick, 0) < -30543){
        SDL_Log("left");
        start_moving_camera(LEFT);
    }
}

void keyboard_iterate_events(){
    const bool *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
        start_moving_camera(UP);
    }
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
        start_moving_camera(DOWN);
    }
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
        start_moving_camera(LEFT);
    }
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
        start_moving_camera(RIGHT);
    }
}