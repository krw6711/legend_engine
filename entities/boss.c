#include "boss.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "items.h"
#include "player.h"
#include "../map/map.h"
#include "../dialogs/dialogs.h"

Boss_t *bosses = NULL;
static SDL_Texture *player_info = NULL;
static SDL_Texture *boss_info = NULL;

int init_bosses()
{
    bosses = SDL_malloc(5 * sizeof(Boss_t));
    
    if(!bosses) return 1;

    bosses[0] = (Boss_t){
        "Boss?",
        (SDL_FRect){4 * MAP_SPRITE_SIZE, 9*MAP_SPRITE_SIZE , 32, 32},
        (Static_Status_t){50, 10, 5, 5, 5, 5, 5}
    };

    return 0;
}

int generate_info(int boss_id)
{
    if(boss_info) SDL_DestroyTexture(boss_info); boss_info = NULL;
    if(player_info) SDL_DestroyTexture(player_info); player_info = NULL;

    char text[32];
    text[0] = '\0';
    SDL_snprintf(text, 32, "Name %s \n HP: %d", bosses[boss_id].name, bosses[boss_id].base.HP);
    boss_info = text2texture(text, 200, NULL);
    
    char text2[64];
    int atk = player->base.ATK + ((player->status.EQW == -1) ? 0 : item_list[player->status.EQW].status.ATK);
    int def = player->base.DEF + ((player->status.EQS == -1) ? 0 : item_list[player->status.EQW].status.DEF);
    SDL_snprintf(
        text2, 32,
         "PLAYER\n HP: %d LCK: %d\nATK: %d DEF:%d", 
        player->status.CHP, player->base.LCK,
        atk, def 
    );
    player_info = text2texture(text2, 200, NULL);

    return 0;
}


void render_battel(int boss_id)
{
    SDL_FRect dst, src;
    src = (SDL_FRect){0 * MAP_SPRITE_SIZE, 7* MAP_SPRITE_SIZE, 3*MAP_SPRITE_SIZE, 3*MAP_SPRITE_SIZE};
    dst = (SDL_FRect){0, 0, CAMERA_X_CELLS*MAP_CELL_SIZE, CAMERA_Y_CELLS*MAP_CELL_SIZE};
    SDL_RenderTexture(renderer, map_texture, &src, &dst);

    dst = (SDL_FRect){(CAMERA_X_CELLS - 10)*50, 200, 300, 300};
    SDL_RenderTexture(renderer, map_texture, &bosses[boss_id].sprite, &dst);
    src = (SDL_FRect){0, 0, 32, 32};
    dst = (SDL_FRect){(2)*50, 200, 300, 300};
    SDL_RenderTexture(renderer, map_texture, &src, &dst);
    
    dst = (SDL_FRect){(2)*50, 500, 200, TTF_GetFontLineSkip(font) * 2};
    SDL_RenderTexture(renderer, player_info, NULL, &dst);
    
    dst = (SDL_FRect){(CAMERA_X_CELLS - 10)*50, 500, 200, TTF_GetFontLineSkip(font) * 2};
    SDL_RenderTexture(renderer, boss_info, NULL, &dst);
}

void fight(int boss_id)
{
    int atk = player->base.ATK + ((player->status.EQW == -1) ? 0 : item_list[player->status.EQW].status.ATK);
    int def = player->base.DEF + ((player->status.EQS == -1) ? 0 : item_list[player->status.EQW].status.DEF);

    int player_atk = SDL_rand(player->base.LCK) * (atk/2);
    int player_def = (SDL_rand(player->base.LCK) * (def/2)) / 2;

    int comp_atk = SDL_rand(bosses[boss_id].base.LCK) * (bosses[boss_id].base.ATK/2);
    int comp_def = (SDL_rand(bosses[boss_id].base.LCK) * (bosses[boss_id].base.DEF/2)) / 2;

    int player_dmg = comp_atk - player_def;
    int comp_dmg = player_atk - comp_def;

    char text[64]; text[0] = '\0';
    SDL_snprintf(text, 64, "Player made attack with %d damage", comp_dmg);

    char text2[64]; text2[0] = '\0';
    SDL_snprintf(text2, 64, "%s made made attack %d damage", bosses[boss_id].name, player_dmg);
    
    SDL_FRect src = {0, 0, 32, 32};
    redner_dialog_by_id(-1, &src, 0, text);
    player->status.CHP -= player_dmg;

    redner_dialog_by_id(-1, &bosses[boss_id].sprite, 0, text2);
    bosses[boss_id].base.HP -= comp_dmg;

    generate_info(boss_id);

    if(player->status.CHP <= 0){
        char *text = "Boss Win!";
        redner_dialog_by_id(-1, &src, 0, text);
        current_screen = GAME;
        if(boss_info) SDL_DestroyTexture(boss_info); boss_info = NULL;
        if(player_info) SDL_DestroyTexture(boss_info); player_info = NULL;
    }
    if(bosses[boss_id].base.HP <= 0){
        char *text = "Player Win!";
        redner_dialog_by_id(-1, &src, 0, text);
        current_screen = GAME;
        if(boss_info) SDL_DestroyTexture(boss_info); boss_info = NULL;
        if(player_info) SDL_DestroyTexture(boss_info); player_info = NULL;
    }
}