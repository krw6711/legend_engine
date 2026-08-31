#include "./entity.h"
#include "../map/map.h"
#include "../map/camera.h"
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

int get_new_index()
{
    switch (player->face) {
        case UP:
            return player->x + ((player->y - 1) * MAP_COLS);            
            break;
        case DOWN:
            return player->x + ((player->y + 1) * MAP_COLS);            
            break;
        case RIGHT:
            return (player->x + 1) + ((player->y) * MAP_COLS);            
            break;
        case LEFT:
            return (player->x - 1) + ((player->y) * MAP_COLS);            
            break;
        case NONE:
            return player->x + ((player->y + 1) * MAP_COLS);            
            break;
    }
    return 0;
}

int update_position()
{
    int index = get_new_index();
    if(map_info[index].type != GROUND && (index >= 0 || index < (MAP_ROWS * MAP_COLS))){
        return 1;
    }
    player->x = index % MAP_COLS;
    player->y = index / MAP_COLS;

    // if(player->x < 0 || player->x >= MAP_COLS) return 1; 
    // if(player->y < 0 || player->y >= MAP_ROWS) return 1; 

    // int cam_x_offset = camera.w_x - player->x;
    // int cam_y_offset = camera.w_y - player->y;

    // if( cam_x_offset > 5 || cam_x_offset >= cam_x_offset - 5 ) {
    //     start_moving_camera(player->face);
    // }

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
