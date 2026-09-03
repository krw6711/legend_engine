#include "cleanup.h"
#include "../global/globals.h"
#include "../map/map.h"
#include <stdlib.h>
#include "../entities/entity.h"
#include "../dialogs/dialogs.h"

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
    free(map_info);
    map_info = NULL;

    if(map_texture) SDL_DestroyTexture(map_texture);
    map_texture = NULL;

    if(player) free(player);
    player = NULL;

    if(entities) free(entities);
    entities = NULL;

    if(dialogs) free(dialogs);
    dialogs = NULL;
            
    if(current_dialog.text_texture) SDL_DestroyTexture(current_dialog.text_texture);
    current_dialog.text_texture = NULL;

    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
    
    if(window) SDL_DestroyWindow(window);
    if(renderer) SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    return 0;
}