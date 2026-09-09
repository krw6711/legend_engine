#include "gameloop.h"
#include "../global/globals.h"

#include "../map/map.h"
#include "../map/camera.h"
#include "../global/iterate_event.h"
#include "../dialogs/dialogs.h"
#include "../entities/player.h"
#include "../physics/velocity.h"

void current_rendering_screen()
{
    switch(current_screen)
    {
        case TILE_SCREEN:
            tile_screen();
            break;
        
        case OPTIONS:
            options();
            break;
        
        case GAME:
            game();
            break;
        
        case INVENTORY:
            inventory();
            break;
            
        case PLAYER_STATUS:
            player_statues();
            break;
    }
}

static void tile_screen()
{
    return;
}

static void options()
{
    return;
}

static void game()
{
    if(!current_dialog.rendering){
        joystick_iterate_event();
        keyboard_iterate_events();
    }

    moving_camera();
    move(player);

    // render the built map
    map_render();

    // render player
    render_player();

    // render dialogs
    render_current_dialog();
}

static void inventory()
{
    return;
}

static void player_statues()
{
    return;
}
