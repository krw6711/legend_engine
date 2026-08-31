#include "./entity.h"
#include "../map/map.h"
#include "SDL3/SDL_rect.h"

Player_t player;

void init_player_coordinates()
{
    player = (Player_t){.x = 5, .y = 8};
}

void init_player()
{
    player = (Player_t){
        .x = player.x,
        .y = player.y,
        .tile = { player.x * MAP_CELL_SIZE, player.y * MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE },
        .sprite = { 
            .coordinates = {0, 0, 32, 32}
        },
        .move = {
            .moving = false,
            .queue = NONE
        },
        .face = DOWN,
        .index = (player.x + player.y * MAP_COLS)
    };
}

void render_player()
{
    SDL_RenderTexture(renderer, map_texture, &player.sprite.coordinates, &player.tile);
}

void move_player(Face_t face){
    switch (face) {
        case UP:
            player.y--;
            player.index = (player.x + player.y * MAP_COLS);
            player.face = UP;
            player.sprite.coordinates.y = 1 * 32;
            if(map_info[player.index].type == WALL){
                player.y++;
                player.index = (player.x + player.y * MAP_COLS);
                break;
            }
            player.tile = (SDL_FRect){player.x * MAP_CELL_SIZE, player.y * MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE };
            break;
        case DOWN:
            player.index = (player.x + player.y * MAP_COLS);
            player.y++;
            player.face = DOWN;
            player.sprite.coordinates.y = 0 * 32;
            player.index = (player.x + player.y * MAP_COLS);
            if(map_info[player.index].type == WALL){
                player.y--;
                player.index = (player.x + player.y * MAP_COLS);
                break;
            }
            player.tile = (SDL_FRect){player.x * MAP_CELL_SIZE, player.y * MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE };
            break;
        case RIGHT:
            player.x++;
            player.index = (player.x + player.y * MAP_COLS);
            player.face = RIGHT;
            player.sprite.coordinates.y = 3 * 32;
            if(map_info[player.index].type == WALL){
                player.x--;
                player.index = (player.x + player.y * MAP_COLS);
                break;
            }
            player.tile = (SDL_FRect){player.x * MAP_CELL_SIZE, player.y * MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE };
            break;
        case LEFT:
            player.x--;
            player.index = (player.x + player.y * MAP_COLS);
            player.face = LEFT;
            player.sprite.coordinates.y = 2 * 32;
            if(map_info[player.index].type == WALL){
                player.x++;
                player.index = (player.x + player.y * MAP_COLS);
                break;
            }
            player.tile = (SDL_FRect){player.x * MAP_CELL_SIZE, player.y * MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE };
            break;
        case NONE:
            break;
    }
}