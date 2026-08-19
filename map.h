#ifndef MAP_H
#define MAP_H
#include <SDL3/SDL_render.h>
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
    // bool ground;
} Map_cell_ground;

extern Map_cell_ground **map_info;
extern SDL_Texture *map_texture;

int map_init(void);
int map_mem_init(void);
void map_draw(void);
void map_render(void);
int load_map_sprite(void);


#endif