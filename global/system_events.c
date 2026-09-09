#include "system_events.h"
#include "../entities/player.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_log.h"
#include "globals.h"

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
    if (event->type != SDL_EVENT_KEY_DOWN) return SDL_APP_CONTINUE;

    if(event->key.key == SDLK_Q || (event->type == SDL_EVENT_JOYSTICK_BUTTON_DOWN && event->jbutton.button == 0)){
        save_player_status();
        SDL_Log("game statues saved!");
    }

    if(event->key.key == SDLK_F || (event->type == SDL_EVENT_JOYSTICK_BUTTON_DOWN && event->jbutton.button == 8)){
        if(fullscreen_mode){
            SDL_SetWindowFullscreen(window,false);
            fullscreen_mode = false;
        }else{
            SDL_SetWindowFullscreen(window,true);
            fullscreen_mode = true;
        }
    }

    if(event->key.key == SDLK_ESCAPE)
    {
        return SDL_APP_SUCCESS;
    }
    
    return SDL_APP_CONTINUE;
}

void player_inputs(SDL_Event *event)
{
    if(current_screen != GAME) return;
    if (event->type != SDL_EVENT_KEY_DOWN) return;

    if(event->key.key == SDLK_X || (event->type == SDL_EVENT_JOYSTICK_BUTTON_DOWN && event->jbutton.button == 2)){
        do_action();
    }
}

void inventory_inputs(SDL_Event *event)
{
    if(current_screen != INVENTORY) return;

    return;
}