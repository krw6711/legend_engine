#include "system_events.h"
#include "../entities/player.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_log.h"
#include "globals.h"
#include "../dialogs/dialogs.h"
#include "../entities/items.h"

void joystick_connecting(SDL_Event *event)
{
    if (event->type == SDL_EVENT_JOYSTICK_ADDED) {
        const SDL_JoystickID which = event->jdevice.which;
        joystick = SDL_OpenJoystick(which);
        if (!joystick) {
            SDL_Log("Joystick #%u add, but not opened: %s", (unsigned int) which, SDL_GetError());
        } else {
            SDL_Log("Joystick #%u ('%s') added", (unsigned int) which, SDL_GetJoystickName(joystick));
        }
    } else if (event->type == SDL_EVENT_JOYSTICK_REMOVED) {
        const SDL_JoystickID which = event->jdevice.which;
        SDL_Joystick *joystick = SDL_GetJoystickFromID(which);
        if (joystick) {
            SDL_CloseJoystick(joystick);  /* the joystick was unplugged. */
        }
        SDL_Log( "Joystick #%u removed", (unsigned int) which);
    }

}

SDL_AppResult general_inputs(SDL_Event *event)
{
    if (event->type != SDL_EVENT_KEY_DOWN && event->type != SDL_EVENT_JOYSTICK_BUTTON_DOWN) return SDL_APP_CONTINUE;

    if((event->key.key == SDLK_Q || ((int)event->jbutton.button == 0))){
        save_player_status();
        SDL_Log("game statues saved!");
    }

    if(event->key.key == SDLK_F || ((int)event->jbutton.button == 8)){
        if(fullscreen_mode){
            SDL_SetWindowFullscreen(window,false);
            fullscreen_mode = false;
        }else{
            SDL_SetWindowFullscreen(window,true);
            fullscreen_mode = true;
        }
    }

    if(event->key.key == SDLK_ESCAPE || ((int)event->jbutton.button == 9))
    {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

int player_inputs(SDL_Event *event)
{
    if(current_screen != GAME) return 0;
    
    if(event->type == SDL_EVENT_JOYSTICK_BUTTON_DOWN){
        if(((int)event->jbutton.button == 2)){
            do_action();
        }   
    }

    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.key == SDLK_X){
            do_action();
        }
        if(event->key.key == SDLK_Z && current_screen == GAME && !current_dialog.rendering){
            SDL_Log("Start Inventory");
            if(start_render_inventory()){
                return 1;
            }
        }
    }

    return 0;
}

void inventory_inputs(SDL_Event *event)
{
    if(current_screen != INVENTORY) return;
    if (event->type != SDL_EVENT_KEY_DOWN && event->type != SDL_EVENT_JOYSTICK_BUTTON_DOWN) return;

    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.key == SDLK_C && current_screen == INVENTORY){
            SDL_Log("stop Inventory");
            stop_render_inventory();
        }
        if(event->key.key == SDLK_UP && current_screen == INVENTORY){
            change_selection(UP);
        }
        if(event->key.key == SDLK_DOWN && current_screen == INVENTORY){
            change_selection(DOWN);
        }
        if(event->key.key == SDLK_RETURN && current_screen == INVENTORY){
            equip_item();
            // SDL_Log("Equiped?");
        }
        // if(event->key.key == SDLK_C && current_screen == INVENTORY){
        //     SDL_Log("stop Inventory");
        //     stop_render_inventory();
        // }
        // if(event->key.key == SDLK_C && current_screen == INVENTORY){
        //     SDL_Log("stop Inventory");
        //     stop_render_inventory();
        // }
    }

    return;
}