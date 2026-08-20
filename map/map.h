#ifndef MAP_H
#define MAP_H
#include "../global/globals.h"

typedef struct {
    SDL_FRect sprite;
    SDL_FRect tile;
    int x;
    int y;
    // bool ground;
} Map_cell_ground;

typedef struct {
    float x, y;
    Uint64 last_time;
} Camera_t;

extern Map_cell_ground **map_info;
extern SDL_Texture *map_texture;
extern SDL_Texture *map_frame;
extern Camera_t camera;

int map_init(void);
int map_mem_init(void);
void map_load(void);
int map_render(void);
int load_map_sprite(void);

#endif