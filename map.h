#ifndef MAP_H
#define MAP_H
#include <stdbool.h>
#include <stdlib.h>

#ifndef GLOBALS_H
#include "globals.h"
#endif

typedef struct {
    SDL_FRect sprite;
    SDL_FRect tile;
    int x;
    int y;
    bool ground;
} Map_cell_ground;

extern Map_cell_ground **map_info;

int map_init(void);

#endif