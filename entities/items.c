#include "items.h"
#include "../global/globals.h"
#include "../map/map.h"
#include "../dialogs/dialogs.h"
#include "player.h"
#include <stdlib.h>
#include <string.h>

Items_t *item_list;
SDL_Texture **generated_textures;

static int init_inventory_textures(){
    int len = player->status.inventory_cusor + 2;
    generated_textures = SDL_calloc(len , sizeof(Inventory_t* ));

    if(!generated_textures){
        return 1;
    }

    return 0;
}

int clear_generated_textures()
{
    int len = player->status.inventory_cusor + 2;
    for(int i = 0; i < len; i++)
    {
        SDL_DestroyTexture(generated_textures[i]);
        generated_textures[i] = NULL; 
    }

    SDL_free(generated_textures);
    generated_textures = NULL;

    return 0;
}

int init_items()
{
    item_list = SDL_malloc(sizeof(Items_t) * 5);
    if(!item_list) return 1;
    Static_Status_t example = {0, 0, 0, 0, 0, 0, 0};

    item_list[0] = (Items_t){
        .type = KEY,
        .name = "magic letter",
        .description = "a letter have magic effect on the shadow guy",
        .function_id = -1,
        .status = example,
        .sprite = { 3 * MAP_SPRITE_SIZE, 7 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[1] = (Items_t){
        .type = EQUIOPMENT,
        .name = "great sowrd",
        .description = "sowrd increase your attack and luck",
        .function_id = -1,
        .status = example,
        .sprite = { 3 * MAP_SPRITE_SIZE, 8 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[2] = (Items_t){
        .type = EQUIOPMENT,
        .name = "wierd Shield",
        .description = "a shield that have magic effect on your HP",
        .function_id = -1,
        .status = example,
        .sprite = { 3 * MAP_SPRITE_SIZE, 8 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[3] = (Items_t){
        .type = KEY,
        .name = "Potion",
        .description = "increase your heal",
        .function_id = -1,
        .status = example,
        .sprite = { 4 * MAP_SPRITE_SIZE, 7 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[4] = (Items_t){
        .type = FLAG,
        .name = "Anvil of great warior",
        .description = "talk to a green guy to give it to you",
        .function_id = -1,
        .status = example,
        .sprite = { 4 * MAP_SPRITE_SIZE, 6 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    return 0;
}

static int generate_no_items()
{
    char* title = "There is no Items Homie";
    generated_textures[1] = text2texture(title, 200, NULL);
    if(!generated_textures[1]){
        return 1;
    }

    return 0;
}

static int generate_item_list(char* list_text)
{
    int len = player->status.inventory_cusor;
    if(len == 0){
        SDL_Log("player is poor");
        return 1;
    }

    char full_text[((64 + 1) * len) + 1];
    full_text[0] = '\0';

    for (int i = 0; i < len; i++) {
        int item_id = player->status.inventory[i].id;

        SDL_strlcat(full_text, item_list[item_id].name, sizeof(full_text));
        SDL_strlcat(full_text, "\n", sizeof(full_text));
    }

    SDL_strlcat(list_text, full_text, sizeof(full_text));

    return 0;
}

static int init_inventory_text_textures()
{
    char* title = "Inventory";
    generated_textures[0] = text2texture(title, 200, NULL);
    
    if(!generated_textures[0]){
        return 1;
    }
    
    if(player->status.inventory_cusor == 0)
    {
        if(generate_no_items()) return 1;
        return 0;
    }

    int len = player->status.inventory_cusor;
    char list_text[((64 + 1) * len) + 1];
    list_text[0] = '\n';
    generate_item_list(list_text);
    SDL_Log("%s", list_text);

    return 0;
}

int start_render_inventory()
{
    if(init_inventory_textures()) {
        SDL_Log("failed to allocate textures pool");    
        return 1;
    }

    init_inventory_text_textures();

    current_screen = INVENTORY;
    return 0;
}

int stop_render_inventory()
{
    current_screen = GAME;
    if(clear_generated_textures()) {
        SDL_Log("failed to free textures pool");    
        return 1;
    }
    return 0;
}

static void render_inventory_screen()
{
    SDL_FRect dst, src;
    src = (SDL_FRect){0 * MAP_SPRITE_SIZE, 7* MAP_SPRITE_SIZE, 3*MAP_SPRITE_SIZE, 3*MAP_SPRITE_SIZE};
    dst = (SDL_FRect){0, 0, CAMERA_X_CELLS*MAP_CELL_SIZE, CAMERA_Y_CELLS*MAP_CELL_SIZE};
    SDL_RenderTexture(renderer, map_texture, &src, &dst);
}

static void render_player_inventory_menu()
{
    SDL_FRect dst = {50, 50, 200, TTF_GetFontLineSkip(font)};
    SDL_RenderTexture(renderer,generated_textures[0], NULL, &dst);
    dst.y += 30;
    SDL_RenderTexture(renderer, generated_textures[1], NULL, &dst);
}

// Inventory Rendering Loop
void render_inventory_menu()
{
   render_inventory_screen();
   render_player_inventory_menu();
}

int is_item_inventory(int id)
{
    for(int i = 0; i < player->status.inventory_cusor; i++)
    {
        if(player->status.inventory[i].id == id){
            return i;
        }
    }
    return -1;
}

void start_dialog_for_item(const char *sentance, int id)
{
    int len = SDL_strlen(sentance) + SDL_strlen(item_list[id].name) + 1;
    char full_msg[len];
    full_msg[0] = '\0';
    SDL_strlcat(full_msg, sentance, len);
    SDL_strlcat(full_msg, item_list[id].name, len);
    // SDL_Log("%s", full_msg);
    
    redner_dialog_by_id(-1, &item_list[id].sprite, -1, full_msg);
}

int give_item(int id)
{
    int item = is_item_inventory(id);

    char* sentance = NULL; 
    if(item != -1 && item_list[id].type != EQUIOPMENT)
    {
        player->status.inventory[item].amount++;
        sentance = "You got another ";
    }else if(item != -1 && item_list[id].type == EQUIOPMENT){
        sentance = "Nah you have it already, you can not carry many Equipments at the same Time, Item: ";
    }else if(item == -1){
        player->status.inventory[player->status.inventory_cusor] = (Inventory_t){id, 1, false};
        player->status.inventory_cusor++;
        sentance = "You obtained ";
    }else{
    }

    if(sentance) start_dialog_for_item(sentance, id);

    return 0;
}
