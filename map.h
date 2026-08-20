#ifndef MAP_H
#define MAP_H
#include "globals.h"
#include <SDL3/SDL_render.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    SDL_FRect sprite;
    SDL_FRect tile;
    int x;
    int y;
    // bool ground;
} Map_cell_ground;

typedef struct {
    int x;
    int y;
} Camera_t;

extern Map_cell_ground **map_info;
extern SDL_Texture *map_texture;
extern SDL_Texture *map_frame;
extern Camera_t camera;

int map_init(void);
int map_mem_init(void);
void map_draw(void);
int map_render(void);
int load_map_sprite(void);


#endif