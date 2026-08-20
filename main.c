#include "./global/globals.h"
#include "./mem/cleanup.h"
#include "./map/map.h"
#include "./global/iterate_event.h"
#include "./physics/velocity.h"

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

    if(map_init()){
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(renderer, 1);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
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
    if (event->type == SDL_EVENT_KEY_DOWN) {
        // camera moving events
        // SDL_Log("camera %d %d", camera.x, camera.y);
        if (event->key.key == SDLK_UP && (camera.y + MAP_CELL_SIZE) <= 0 && (camera.y + MAP_CELL_SIZE) >= ((MAP_ROWS * MAP_CELL_SIZE)*-1) + WINDOW_HEIGHT){
            camera.y+= MAP_CELL_SIZE;
        }
        if (event->key.key == SDLK_DOWN && (camera.y - MAP_CELL_SIZE) <= 0 && (camera.y - MAP_CELL_SIZE) >= ((MAP_ROWS * MAP_CELL_SIZE)*-1) + WINDOW_HEIGHT)
        {
            camera.y-= MAP_CELL_SIZE;
        }
        if (event->key.key == SDLK_RIGHT && (camera.x - MAP_CELL_SIZE) <= 0 && (camera.x - MAP_CELL_SIZE) >= ((MAP_COLS * MAP_CELL_SIZE)*-1) + WINDOW_WIDTH){
            camera.x-= MAP_CELL_SIZE;
        }
        if (event->key.key == SDLK_LEFT && (camera.x + MAP_CELL_SIZE) <= 0 && (camera.x + MAP_CELL_SIZE) >= ((MAP_COLS * MAP_CELL_SIZE)*-1) + WINDOW_WIDTH){
            camera.x+= MAP_CELL_SIZE;
        }
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    // do_move(&camera.y, camera.y + MAP_CELL_SIZE , MAP_CELL_SIZE, 0.5, &camera.last_time);

    joystick_iterate_event();

    SDL_SetRenderDrawColor(renderer, 60, 60, 60, SDL_ALPHA_OPAQUE); // make a black-gray background
    SDL_RenderClear(renderer); // clear the canvas
    
    // render the built map
    map_render();

    // camera coordinates
    // SDL_SetRenderViewport(renderer, &camera);

    // output on the screen
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if(clean_heaps()){
        SDL_Log("Error in freeing up memory, happy memory leak!");
    }

    /* SDL will clean up the window/renderer for us. */
}