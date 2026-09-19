#ifndef ITEMS_H
#define ITEMS_H

#include "../global/globals.h"
#include "./player.h"

typedef enum { SHEILD, WEAPON, KEY, FLAG, SKILL, POISON} Items_Types_t;

typedef struct {
    Items_Types_t type;
    SDL_FRect sprite;
    char name[64];
    char description[256];
    Static_Status_t status;
    int function_id;
} Items_t;

extern Items_t *item_list;
extern SDL_Texture **generated_textures;
extern int selection;

static int init_inventory_textures();
int clear_generated_textures();
int init_items(void);
static int generate_no_items();
static int generate_item_list(char* list_text);
static int init_inventory_text_textures();
int start_render_inventory();
int stop_render_inventory();
void equip_item();
void change_selection(Face_t dir);
static void render_inventory_screen(void);
static void render_player_inventory_menu(void);
void render_inventory_menu(void);
int give_item(int id);

#endif