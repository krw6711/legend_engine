#ifndef MAP_H
#define MAP_H
#include "../global/globals.h"

#include <stdbool.h>

typedef struct {
    SDL_FRect sprite;
    SDL_FRect tile;
    int x;
    int y;
    // bool ground;
} Map_cell_ground;

typedef enum {UP, DOWN, RIGHT, LEFT} Face_t;

typedef struct {
   float start_x, start_y;
   float end_x, end_y;
} Collusion_Informtion_t;

typedef struct {
   Face_t face;
   Uint64 last_time;
   float target;
   float velocity;
   bool moving; 
} Moving_t;

typedef struct {
    Moving_t move;
    Collusion_Informtion_t border;
    float x, y;
} Object_t;

extern Map_cell_ground **map_info;
extern SDL_Texture *map_texture;
extern SDL_Texture *map_frame;
extern Object_t camera;

int map_init(void);
int map_mem_init(void);
void map_load(void);
int map_render(void);
int load_map_sprite(void);

#endif