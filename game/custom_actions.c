#include "./custom_actions.h"
#include "../dialogs/dialogs.h"
#include "../entities/entity.h"

void print_hello_world()
{
    redner_dialog_by_id(7, &entities[3].sprite, NULL); 
}