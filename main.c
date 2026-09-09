#include "./global/globals.h"
#include "./global/system_events.h"

#include "./mem/cleanup.h"

#include "./map/map.h"

#include "entities/items.h"
#include "entities/npc.h"
#include "entities/player.h"
#include "entities/entity.h"

#include "dialogs/dialogs.h"

#include "game/actions.h"
#include "./game/gameloop.h"

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata(APP_NAME, APP_VERSION, APP_ID);

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    
    SDL_SetRenderVSync(renderer, 1);
    
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    float font_size = 18.0;
    /* Open the font */
    char* font_path = get_full_path("/assets/osifont.ttf");
    if(font_path == NULL) return SDL_APP_FAILURE;
    font = TTF_OpenFont(font_path, font_size);
    if (!font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_free(font_path); font_path = NULL;
    
    current_screen = GAME;
    
    if(map_init()) return SDL_APP_FAILURE;

    if(init_player()) return SDL_APP_FAILURE;
    if(init_entites()) return SDL_APP_FAILURE;
    if(init_npcs()) return SDL_APP_FAILURE;

    if(init_dialogs()) return SDL_APP_FAILURE;

    if(init_functions()) return SDL_APP_FAILURE;

    if(init_items()) return SDL_APP_FAILURE;

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    joystick_connecting(event);
    inventory_inputs(event);
    player_inputs(event);
    
    return general_inputs(event);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // make a black-gray background
    SDL_RenderClear(renderer); // clear the canvas
    
    current_rendering_screen();

    // output on the screen
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if(clean_heaps()){
        SDL_Log("Error in SDL_freeing up memory, happy memory leak!");
    }

    /* SDL will clean up the window/renderer for us. */
}