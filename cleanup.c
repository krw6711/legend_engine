#include "cleanup.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_render.h"
#include "globals.h"
#include "map.h"

int clean_heaps(void){
    // Free SDL Stuff
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    SDL_DestroyAudioStream(music);
    SDL_DestroyAudioStream(sfx);
    music = NULL;
    sfx = NULL;

    joystick = NULL;

    // Free Map
    for(int i = 0; i <= MAP_ROWS; i++){
        free(map_info[i]);
        map_info[i] = NULL;
    }
    free(map_info);
    map_info = NULL;

    SDL_DestroyTexture(map_texture);
    map_texture = NULL;

    return 0;
}