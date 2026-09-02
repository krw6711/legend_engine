#include "./entity.h"
#include "../map/map.h"
#include "../map/camera.h"
#include "../physics/velocity.h"
#include <stdbool.h>
#include <stdlib.h>

Player_t *player = NULL;

int init_player()
{
    player = malloc(sizeof(Player_t));
    if(player == NULL){
        return 1;
    }
    player->x = 5;
    player->y = 8;
    player->face = DOWN;
    player->tile = (SDL_FRect){
        player->x * MAP_CELL_SIZE,
        player->y * MAP_CELL_SIZE,
        MAP_CELL_SIZE,
        MAP_CELL_SIZE    
    };
    player->sprite.start_x = 0;
    player->sprite.start_y = 0;
    player->sprite.coordinates = (SDL_FRect){
        player->sprite.start_x * MAP_SPRITE_SIZE,
        player->sprite.start_y + (MAP_SPRITE_SIZE * player->face),
        MAP_SPRITE_SIZE,
        MAP_SPRITE_SIZE
    };
    return 0;
}

void move_player(Face_t face)
{
    if(!player->move.moving){
        player->face = face;
        update_face();
        update_position();
    }
}

void update_face()
{
    player->sprite.coordinates = (SDL_FRect){
        player->sprite.start_x * MAP_SPRITE_SIZE,
        player->sprite.start_y + (MAP_SPRITE_SIZE * player->face),
        MAP_SPRITE_SIZE,
        MAP_SPRITE_SIZE
    };
}

Coordinates_t get_new_index()
{
    int index, x, y;
    x = player->x;
    y = player->y;

    switch (player->face) {
        case UP:
            y--;        
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        case LEFT:
            x--;
            break;
        case NONE:
            break;
    }

    index = x + ((y) * MAP_COLS);            
    return (Coordinates_t){index, x, y};
}

bool is_walkable(Coordinates_t new_coord)
{
    if(new_coord.x < 0) return false;
    if(new_coord.x >= MAP_COLS) return false;
    if(new_coord.y < 0) return false;
    if(new_coord.y >= MAP_ROWS) return false;

    if(new_coord.index < 0) return false;

    if(map_info[new_coord.index].type != GROUND) return false;

    return true;
}

Face_t is_move_camera_with_player(Coordinates_t new_coord)
{
    int start_x = (int)camera.c_x + 3;
    int start_y = (int)camera.c_y + 3; 

    int end_x = (int)camera.c_x + (int)camera.w_x - 3;
    int end_y = (int)camera.c_y + (int)camera.w_y - 3;

    if(new_coord.x < start_x) return LEFT;
    if(new_coord.x >= (end_x)) return RIGHT;
    if(new_coord.y < start_y) return UP;
    if(new_coord.y >= (end_y)) return DOWN;

    return NONE;
}

int update_position()
{
    Coordinates_t new_coord = get_new_index();    
    if(!is_walkable(new_coord))
    {   
        return 1;
    }

    if(is_move_camera_with_player(new_coord) != NONE){
        start_moving_camera(player->face);
    }

    start_moving(player, new_coord);

    return 0;
}

void render_player()
{
    SDL_FRect screen_position;
    screen_position = (SDL_FRect){
        .x = player->tile.x - ((float)camera.c_x * MAP_CELL_SIZE),
        .y = player->tile.y - ((float)camera.c_y * MAP_CELL_SIZE),
        .h = player->tile.h,
        .w = player->tile.w
    };
    SDL_RenderTexture(renderer, map_texture, &player->sprite.coordinates, &screen_position);
}
