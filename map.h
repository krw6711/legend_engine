#ifndef MAP_H
#define MAP_H
#include <stdbool.h>

#ifndef GLOBALS_H
#include "globals.h"
#endif

typedef struct {
    bool ground;
    int x;
    int y;
    SDL_FRect sprite;
    SDL_FRect tile;
} Map_cell_ground;



#endif