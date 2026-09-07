#ifndef NPC_H
#define NPC_H
#include "../global/globals.h"

typedef struct {
    SDL_FRect sprite;
    int dialog_id;
    int callback;
} NPC_t;

extern NPC_t *npcs;

int init_npcs();

#endif