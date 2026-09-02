#ifndef ENTITY_H
#define ENTITY_H
#include "../global/globals.h"

typedef struct {
    SDL_FRect sprite;
    int dialog_id;
} Entity_t;

extern Entity_t *entities;

int init_entites();

#endif