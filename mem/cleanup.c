#include "cleanup.h"

int clean_heaps(void){
    // Free SDL Stuff
    if(music){
        SDL_DestroyAudioStream(music);
    }
    if(sfx) SDL_DestroyAudioStream(sfx);
    
    music = NULL;
    sfx = NULL;

    if(joystick) SDL_CloseJoystick(joystick);
    joystick = NULL;

    // Free Map
    for(int i = 0; i < MAP_ROWS; i++){
        free(map_info[i]);
        map_info[i] = NULL;
    }
    free(map_info);
    map_info = NULL;

    if(map_texture) SDL_DestroyTexture(map_texture);
    map_texture = NULL;

    if(window) SDL_DestroyWindow(window);
    if(renderer) SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    return 0;
}