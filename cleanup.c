#include "cleanup.h"
#include "globals.h"
#include "map.h"

int clean_heaps(void){
    // Free SDL Stuff
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    joystick = NULL;
    music = NULL;
    sfx = NULL;

    // Free Map
    for(int i = 0; i <= MAP_ROWS; i++){
        free(map_info[i]);
        map_info[i] = NULL;
    }
    free(map_info);
    map_info = NULL;

    return 0;
}