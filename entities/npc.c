#include "./npc.h"
#include "../global/globals.h"

NPC_t *npcs;

int init_npcs()
{
    npcs = SDL_malloc(sizeof(NPC_t) * 3);

    if(!npcs){
        return 1;
    }

    npcs[0] = (NPC_t){
        .sprite = { 3 * MAP_SPRITE_SIZE, 5 * MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE},
        .dialog_id = 6,
        .callback = 0
    };

    return 0;
}