#ifndef ENTITY_H
#define ENTITY_H

#include "../global/globals.h"
#include "SDL3/SDL_rect.h"

typedef enum {GROUND, WALL, ENTITY, ITEM, NPC, BOSS} Entity_types_t;

typedef struct{
    bool moving;
    Face_t queue;
} Movement_t;

typedef struct {
    SDL_FRect coordinates;
    int count, start_x, start_y;
} Sprite_t;

typedef struct {
    int x, y;
    SDL_FRect tile;
    Sprite_t sprite;
    Movement_t move;
    Face_t face;
} Player_t;

extern Player_t *player;

int init_player();
void render_player();
void update_face();
int get_new_index();
int update_position();
void move_player(Face_t face);

#endif