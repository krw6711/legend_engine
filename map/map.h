#ifndef MAP_H
#define MAP_H
#include "../global/globals.h"

#include <stdbool.h>

typedef enum {GROUND, WALL, ENTITY, ITEM, NPC, BOSS} Entity_types_t;

typedef struct {
    SDL_FRect sprite;
    SDL_FRect tile;
    Entity_types_t type;
    int id;
} Map_cell;

extern Map_cell *map_info;
extern SDL_Texture *map_texture;
extern SDL_Texture *map_frame;

int map_init(void);
int map_mem_init(void);
void map_load(void);
int map_render(void);
int load_map_sprite(void);

#endif