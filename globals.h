#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>

#define MAP_COLS 5
#define MAP_ROWS 15
#define MAP_CELL_SIZE 50

#define WINDOW_WIDTH MAP_COLS * MAP_CELL_SIZE
#define WINDOW_HEIGHT MAP_ROWS * MAP_CELL_SIZE

#define APP_NAME "The Legend Engine"
#define APP_ID "com.legend.engine.2d"
#define APP_VERSION "0.1"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Joystick *joystick = NULL;
static SDL_AudioStream *music = NULL;
static SDL_AudioStream *sfx = NULL;

#endif 