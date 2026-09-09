#include "items.h"
#include "../global/globals.h"
#include "../map/map.h"
#include "../global/text.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include <string.h>

Items_t *item_list;
SDL_Texture **generated_textures;

int init_items()
{
    item_list = SDL_malloc(sizeof(Items_t) * 5);
    if(!item_list) return 1;

    item_list[0] = (Items_t){
        .type = KEY,
        .name = "magic letter",
        .description = "a letter have magic effect on the shadow guy",
        .function_id = -1,
        .AT = 0,
        .DF = 0,
        .HP = 0,
        .LK = 0,
        .sprite = { 2 * MAP_SPRITE_SIZE, 8 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[1] = (Items_t){
        .type = WEAPON,
        .name = "great sowrd",
        .description = "sowrd increase your attack and luck",
        .function_id = -1,
        .AT = 10,
        .DF = 0,
        .HP = 0,
        .LK = 5,
        .sprite = { 1 * MAP_SPRITE_SIZE, 8 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[2] = (Items_t){
        .type = SHIELD,
        .name = "wierd Shield",
        .description = "a shield that have magic effect on your HP",
        .function_id = -1,
        .AT = 0,
        .DF = 10,
        .HP = 5,
        .LK = 10,
        .sprite = { 3 * MAP_SPRITE_SIZE, 8 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[3] = (Items_t){
        .type = UTIL,
        .name = "Potion",
        .description = "increase your heal",
        .function_id = -1,
        .AT = 0,
        .DF = 0,
        .HP = 10,
        .LK = 0,
        .sprite = { 0 * MAP_SPRITE_SIZE, 8 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    item_list[4] = (Items_t){
        .type = FLAG,
        .name = "Anvil of great warior",
        .description = "talk to a green guy to give it to you",
        .function_id = -1,
        .AT = 0,
        .DF = 0,
        .HP = 0,
        .LK = 0,
        .sprite = { 4 * MAP_SPRITE_SIZE, 6 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}
    };

    return 0;
}

static void render_inventory_screen()
{
    SDL_FRect dst, src;
    src = (SDL_FRect){0 * MAP_SPRITE_SIZE, 9 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE};
    dst = (SDL_FRect){0, 0, CAMERA_X_CELLS*MAP_CELL_SIZE, CAMERA_Y_CELLS*MAP_CELL_SIZE};
    SDL_RenderTexture(renderer, map_texture, &src, &dst);

    src = (SDL_FRect){1 * MAP_SPRITE_SIZE, 9 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE};
    dst.x = dst.y = 50;
    dst.w = ((CAMERA_X_CELLS - 2) *MAP_CELL_SIZE);
    dst.h = ((CAMERA_Y_CELLS - 2)*MAP_CELL_SIZE);

    SDL_RenderTexture(renderer, map_texture, &src, &dst);

    char* title = "Inventory";
    SDL_Texture *title_texture = generate_text_texture(title,100);
    generated_textures[0] = title_texture;
    dst = (SDL_FRect){150, 150, 100, TTF_GetFontLineSkip(font)};
    SDL_RenderTexture(renderer, title_texture, NULL, &dst);
}

static void render_player_inventory_menu()
{
    SDL_FRect dst, src;
    char menu_text[65*20];
    if(player->status.inventory_cusor <= 0)
    {
        const char* src_text = "there is no items in your inventory!";
        strcpy(menu_text, src_text);
        SDL_Texture *title_texture = generate_text_texture(menu_text,300);
        generated_textures[1] = title_texture;
        dst = (SDL_FRect){200, 200, 300, 50};
        SDL_RenderTexture(renderer, title_texture, NULL, &dst);
    }
}

void render_inventory_menu()
{
    generated_textures = SDL_malloc(sizeof(SDL_Texture*) * 40);
    if(!generated_textures) return;

   render_inventory_screen();
   render_player_inventory_menu();
}

void destroy_inventory_textures()
{
    SDL_free(generated_textures);
    generated_textures = NULL;
}

void give_player_item(int id)
{
    char* dialog_text = "You got a legend item! ";
}