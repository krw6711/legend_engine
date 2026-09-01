#include "./entity.h"
#include "../map/map.h"
#include "../map/camera.h"
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
    player->face = face;
    update_face();
    update_position();
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

int update_position()
{
    Coordinates_t new_coord = get_new_index();    
    if(!is_walkable(new_coord))
    {   
        return 1;
    }

    player->x = new_coord.x;
    player->y = new_coord.y;

    // start_moving_camera(player->face);
    player->tile = (SDL_FRect){ 
        player->x * MAP_CELL_SIZE,
        player->y * MAP_CELL_SIZE,
        MAP_CELL_SIZE,
        MAP_CELL_SIZE    
    };
    return 0;
}

void render_player()
{
    SDL_RenderTexture(renderer, map_texture, &player->sprite.coordinates, &player->tile);
}
