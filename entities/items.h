#ifndef ITEMS_H
#define ITEMS_H

#include "../global/globals.h"

typedef enum { KEY, SHIELD, WEAPON, FLAG } Items_Types_t;

typedef struct {
    Items_Types_t type;
    SDL_FRect sprite;
    char name[32];
    char description[256];
    int HP; // Health Points
    int AT; // ATtack
    int DF; // DeFence
    int LK; // Luck
    unsigned int function_id;
} Items_t;

typedef struct {
    unsigned int id;
    unsigned int amount;
    bool active;
} Inventory_t;

#endif