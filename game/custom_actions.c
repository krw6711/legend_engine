#include "./custom_actions.h"
#include "../dialogs/dialogs.h"
#include "../entities/entity.h"
#include "../entities/items.h"

void print_hello_world()
{
    redner_dialog_by_id(7, &entities[3].sprite,1 , NULL);
}

void give_legend_letter()
{
    give_item(1);
}

void give_the_posion()
{
    give_item(3);
}