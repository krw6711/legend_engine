#ifndef ITEMS_H
#define ITEMS_H

#include "../global/globals.h"
#include "SDL3/SDL_render.h"

typedef enum { KEY, SHIELD, WEAPON, FLAG, UTIL} Items_Types_t;

typedef struct {
    Items_Types_t type;
    SDL_FRect sprite;
    char name[64];
    char description[256];
    int HP; // Health Points
    int AT; // ATtack
    int DF; // DeFence
    int LK; // Luck
    int function_id;
} Items_t;

typedef struct {
    unsigned int id;
    unsigned int amount;
    bool active;
} Inventory_t;

extern Items_t *item_list;
extern SDL_Texture **generated_textures;

int init_items(void);
static void render_inventory_screen(void);
static void render_player_inventory_menu(void);
void render_inventory_menu(void);
void destroy_inventory_textures(void);

#endif