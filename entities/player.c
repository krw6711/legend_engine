#include "./player.h"
#include "../map/camera.h"
#include "../map/map.h"
#include "../physics/velocity.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../dialogs/dialogs.h"
#include "entity.h"
#include "./npc.h"
#include "items.h"

#include "../audio/audio.h"

Player_t *player = NULL;

int get_save_file(char* save_file_path)
{
    FILE *pFile = fopen(save_file_path, "rb");

    if(pFile == NULL){
        SDL_Log("error reading the words file");
        return 1;
    }
    
    fseek(pFile, 0, SEEK_END); // seek to end of file
    int fileSize = ftell(pFile); // get current file pointer
    fseek(pFile, 0, SEEK_SET); // seek back to beginning of file

    player = malloc(fileSize);

    if(player == NULL){
        SDL_Log("error in loading the words file into the memory");
        fclose(pFile);
        return 1;
    }

    size_t bytesRead = fread(player, 1, fileSize, pFile);

    fclose(pFile);

    return 0;
}

int init_player_struct()
{
    player = SDL_malloc(sizeof(Player_t));

    if(player == NULL){
        return 1;
    }

    player->x = 50;
    player->y = 50;
    player->face = DOWN;
    player->tile = (SDL_FRect){
        player->x * MAP_CELL_SIZE,
        player->y * MAP_CELL_SIZE,
        MAP_CELL_SIZE,
        MAP_CELL_SIZE    
    };
    player->sprite.count = 5;
    player->sprite.start_x = 0;
    player->sprite.start_y = 0;
    player->sprite.coordinates = (SDL_FRect){
        player->sprite.start_x * MAP_SPRITE_SIZE,
        player->sprite.start_y + (MAP_SPRITE_SIZE * player->face),
        MAP_SPRITE_SIZE,
        MAP_SPRITE_SIZE
    };
    
    player->status.EXP = 0;
    player->status.LVL = 1;

    player->base.HP = 30;
    player->base.ATK = 10;
    player->base.DEF= 10;
    player->base.LCK = 10;

    player->base.ACC = 5;
    player->base.EVA = 5;
    player->base.SPD = 5;

    player->status.CHP = 30;

    player->status.EQS = -1;
    player->status.EQW = -1;

    player->status.inventory_cusor = 0;
    player->status.index = player->x + player->y * MAP_ROWS;

    return 0;
}

int creat_save_file(char* save_file_path)
{
    if(!player) init_player_struct();

    FILE *pFile = fopen(save_file_path, "wb+");
    if(!pFile){
        SDL_Log("error creating save file");
        return 1;
    }

    fwrite(player, sizeof(Player_t), 1, pFile);
    rewind(pFile);
    fclose(pFile);

    return 0;
}

int save_player_status()
{
    char* save_file_path = get_full_path(PLAYER_SAVE_FILE_PATH);
    if(save_file_path == NULL){
        SDL_Log("Error out of memory XP");
        return 1;
    }

    FILE *pFile = fopen(save_file_path, "wb+");
    SDL_free(save_file_path); save_file_path = NULL;
    if(!pFile){
        SDL_Log("error creating save file");
        return 1;
    }

    fwrite(player, sizeof(Player_t), 1, pFile);
    rewind(pFile);
    fclose(pFile);

    return 0;

}

int load_save_file()
{
    char* save_file_path = get_full_path(PLAYER_SAVE_FILE_PATH);
    if(save_file_path == NULL){
        SDL_Log("Error out of memory XP");
        return 1;
    } 
    
    if(!access(save_file_path, F_OK)){
        if(get_save_file(save_file_path)) return 1;
    }else{
        if(creat_save_file(save_file_path)) return 1;
    }

    SDL_free(save_file_path); save_file_path = NULL;
    return 0;
}

int init_player()
{
    if(load_save_file()) return 1;
    camera.c_x = player->x - 10;
    camera.c_y = player->y - 10;
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
    if(new_coord.index > (MAP_COLS * MAP_ROWS)) return false;

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

void do_action()
{
    Coordinates_t new_coord = get_new_index();

    if(current_dialog.rendering){
        dialog_event_handler();
    }else if(new_coord.index >= 0 && new_coord.index < (MAP_COLS * MAP_ROWS)){
        if(map_info[new_coord.index].type == ENTITY && map_info[new_coord.index].id != -1)
        {
            redner_dialog_by_id(entities[map_info[new_coord.index].id].dialog_id, &entities[map_info[new_coord.index].id].sprite, -1, NULL);
        }
        if(map_info[new_coord.index].type == NPC && map_info[new_coord.index].id != -1)
        {
            redner_dialog_by_id(npcs[map_info[new_coord.index].id].dialog_id, &npcs[map_info[new_coord.index].id].sprite, npcs[map_info[new_coord.index].id].callback, NULL);
            //  functions[npcs[map_info[new_coord.index].id].callback]
        }
        if(map_info[new_coord.index].type == ITEM)
        {
            give_item(map_info[new_coord.index].id);
            play_sfx(2);
            map_info[new_coord.index].type = GROUND;
        }
        if(map_info[new_coord.index].type == BOSS)
        {
            play_sfx(2);
            // map_info[new_coord.index].type = GROUND;
            current_screen = FIGHT;
        }
    // }else{
        // char* text = "Hello World!";
        // redner_dialog_by_id(0, &item_list[0].sprite, NULL, text, SDL_strlen(text));
    }
}