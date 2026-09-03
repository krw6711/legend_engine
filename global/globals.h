#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define MAP_COLS 100
#define MAP_ROWS 100
#define MAP_CELL_SIZE 50
#define MAP_SPRITE_FILE "%sassets/map.png"
#define MAP_SPRITE_SIZE 32

#define CAMERA_X_CELLS 20
#define CAMERA_Y_CELLS 15

#define WINDOW_WIDTH (CAMERA_X_CELLS * MAP_CELL_SIZE)
#define WINDOW_HEIGHT (CAMERA_Y_CELLS * MAP_CELL_SIZE)

#define WINDOW_TITLE "The Legend 2D Engine"
#define APP_NAME "The Legend Engine"
#define APP_ID "com.legend.engine.2d"
#define APP_VERSION "0.1"

typedef enum {
    UP=1,
    DOWN=0, 
    RIGHT=3, 
    LEFT=2,
    NONE=4
}Face_t;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Joystick *joystick;
extern SDL_AudioStream *music;
extern SDL_AudioStream *sfx;
extern TTF_Font *font;

char* get_full_path(char* relativePath);

#endif 