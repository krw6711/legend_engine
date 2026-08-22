#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>

#define MAP_COLS 30
#define MAP_ROWS 20
#define MAP_CELL_SIZE 50
#define MAP_SPRITE_FILE "%sassets/map.png"
#define MAP_SPRITE_SIZE 32

#define CAMERA_X_CELLS (MAP_COLS - 5)
#define CAMERA_Y_CELLS (MAP_ROWS - 5)

#define WINDOW_WIDTH (CAMERA_X_CELLS * MAP_CELL_SIZE)
#define WINDOW_HEIGHT (CAMERA_Y_CELLS * MAP_CELL_SIZE)

#define WINDOW_TITLE "The Legend 2D Engine"
#define APP_NAME "The Legend Engine"
#define APP_ID "com.legend.engine.2d"
#define APP_VERSION "0.1"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Joystick *joystick;
extern SDL_AudioStream *music;
extern SDL_AudioStream *sfx;
// extern SDL_Rect camera;

// typedef enum {UP, DOWN, RIGHT, LEFT, NONE} Face_t;

#endif 