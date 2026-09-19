#include "./actions.h"
// #include "../global/dynamic_array.h"
#include "./custom_actions.h"
#include <stdlib.h>

void (**functions)(void);

int init_functions(void)
{
    functions = SDL_malloc(sizeof(void(*)(void)) * 3);
    if(!functions) return 1;
    functions[0] = print_hello_world;
    functions[1] = give_legend_letter;
    functions[2] = give_the_posion;

    return 0;
}