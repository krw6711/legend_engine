#include "entity.h"
#include <stdlib.h>

Entity_t *entities = NULL;
#define ENTITY_AMOUNT 5;

int init_entites()
{
    entities = malloc(sizeof(Entity_t) * 5);
    if(entities == NULL)
    {
        SDL_Log("Error Allocating memory for Entites");
        return 1;
    }

    entities[0] = (Entity_t){
        .sprite = {5*MAP_SPRITE_SIZE, 5*MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE},
        .dialog_id = 0
    };
    return 0;
}