#ifndef SYSTEM_EVENTS_H
#define SYSTEM_EVENTS_H
#include "../global/globals.h"
#include "SDL3/SDL_init.h"

void joystick_connecting(SDL_Event *event);
SDL_AppResult general_inputs(SDL_Event *event);
int player_inputs(SDL_Event *event);
void inventory_inputs(SDL_Event *event);
void fight_input(SDL_Event *event);

#endif