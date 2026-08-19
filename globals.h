#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>

#define MAP_COLS 20
#define MAP_ROWS 10
#define MAP_CELL_SIZE 50

#define WINDOW_WIDTH MAP_COLS * MAP_CELL_SIZE
#define WINDOW_HEIGHT MAP_ROWS * MAP_CELL_SIZE

#define APP_NAME "The Legend Engine"
#define APP_ID "com.legend.engine.2d"
#define APP_VERSION "0.1"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Joystick *joystick;
extern SDL_AudioStream *music;
extern SDL_AudioStream *sfx;

#endif 