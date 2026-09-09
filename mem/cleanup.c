#include "cleanup.h"
#include "../global/globals.h"
#include "../map/map.h"
#include <stdlib.h>
#include "../entities/entity.h"
#include "../dialogs/dialogs.h"
#include "../global/dynamic_array.h"
#include "../game/actions.h"
#include "../entities/npc.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_stdinc.h"

int clean_heaps(void){
    // SDL_free SDL Stuff
    if(music){
        SDL_DestroyAudioStream(music);
    }
    if(sfx) SDL_DestroyAudioStream(sfx);
    
    music = NULL;
    sfx = NULL;

    if(joystick) SDL_CloseJoystick(joystick);
    joystick = NULL;

    // SDL_free Map
    SDL_free(map_info);
    map_info = NULL;

    if(map_texture) SDL_DestroyTexture(map_texture);
    map_texture = NULL;

    if(save_player_status()) SDL_Log("You lost your progress now you can cry XD");
    if(player) SDL_free(player);
    player = NULL;

    if(entities) SDL_free(entities);
    entities = NULL;

    if(dialogs) SDL_free(dialogs);
    dialogs = NULL;
            
    if(current_dialog.text_texture) SDL_DestroyTexture(current_dialog.text_texture);
    current_dialog.text_texture = NULL;

    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
    
    // SDL_free_darray(&functions);

    if(npcs) SDL_free(npcs);
    npcs = NULL;

    if(functions) SDL_free(functions);
    functions = NULL;

    if(item_list) SDL_free(item_list);
    item_list = NULL;

    if(generated_textures) SDL_free(generated_textures);
    generated_textures = NULL;

    if(window) SDL_DestroyWindow(window);
    if(renderer) SDL_DestroyRenderer(renderer);

    window = NULL;
    renderer = NULL;

    SDL_Log("cleaned up everything! happy memory free!");
    return 0;
}