#ifndef BOSS_H
#define BOSS_H
#include "../global/globals.h"
#include "player.h"

typedef struct {
    char name[16];
    SDL_FRect sprite;
    Static_Status_t base;
} Boss_t;

extern Boss_t *bosses;

int init_bosses();
int generate_info(int boss_id);
void render_battel(int boss_id);
void fight(int boss_id);


#endif