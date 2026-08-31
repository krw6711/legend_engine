#ifndef ENTITY_H
#define ENTITY_H

#include "../global/globals.h"
#include "SDL3/SDL_rect.h"

typedef enum {GROUND, WALL, ENTITY, ITEM, NPC, BOSS} Entity_types_t;

typedef struct{
    SDL_FRect coordinates;
    // int up, down, right, left;
} Sprite_t;

typedef struct{
    bool moving;
    Face_t queue;
} Movement_t;

typedef struct {
    int x, y, index;
    SDL_FRect tile;
    Sprite_t sprite;
    Movement_t move;
    Face_t face;
} Player_t;

extern Player_t player;

void init_player_coordinates();
void init_player();
void render_player();
void move_player(Face_t face);

#endif