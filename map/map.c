#include "map.h"
#include <stdlib.h>
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "camera.h"
#include "../entities/entity.h"

// Make a large array for map meta info to access later
Map_cell *map_info = NULL;
SDL_Texture *map_texture = NULL;
SDL_Texture *map_frame =  NULL;

// initialize map array
int map_mem_init(void){
    map_info = malloc(MAP_ROWS * MAP_COLS * sizeof(Map_cell));
    return 0;
}

int load_map_sprite(void){
    SDL_Surface *surface = NULL;
    char *png_path = NULL;

    SDL_asprintf(&png_path, MAP_SPRITE_FILE, SDL_GetBasePath());  /* allocate a string of the full file path */

    surface = SDL_LoadPNG(png_path);
    SDL_free(png_path);  /* done with this, the file is loaded. */

    if (!surface) {
        SDL_Log("Couldn't load png: %s", SDL_GetError());
        return 1;
    }

    map_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);  /* done with this, the texture has a copy of the pixels now. */

    if (!map_texture) {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return 1;
    }
    
    return 0;
}

void map_load(void){
    // 14 20 21
    int x, y;
    for(int i = 0; i < (MAP_ROWS * MAP_COLS); i++){
        x = i % MAP_COLS;
        y = i / MAP_COLS;

        int sx = 4, sy = 4, id = -1;
        Entity_types_t type = GROUND;

        if(x ==  0 || y == 0 || x == (MAP_ROWS - 1) || y == (MAP_COLS - 1)){
            sx = 2; type = WALL;
        }
        
        if(x == 34 || x == 68 || y == 34 || y == 68)
        {
            sx = 5; type = WALL;
        }

        if(y == 34 || y == 68 ){
            sx = 4; sy = 5;
        }

        if(
            ( x == 34 && y == 17) || ( x == 68 && y == 17) || (x==85 && y==34) ||
            ( x == 34 && y == 51) || ( x == 68 && y == 51) ||
            ( x == 16 && y == 68) || ( x == 51 && y == 68) || (x==85 && y == 68) ||
            ( x == 34 && y == 85)
        ) {
            sx = 4; type = GROUND;
        }

        if((x == 52 && y ==52) || (x == 60 && y == 50) || (x == 40 && y == 55)){
            id = 0; type = ENTITY; sx = 4; sy = 4;
        }

        map_info[i] = (Map_cell){
            .sprite = {sx*MAP_SPRITE_SIZE, sy*MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE},
            .tile = {(x)*MAP_CELL_SIZE, (y)*MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE},
            .type = type,
            .id = id
        };

    }

}

int map_render(void){
    SDL_FRect screen_position;

    int start_x = (int)camera.c_x;
    int start_y = (int)camera.c_y; 

    int end_x = start_x + camera.w_x + 1;
    int end_y = start_y + camera.w_y + 1;

    if(start_x < 0) start_x = 0;
    if(start_y < 0) start_y = 0;
    if(end_x > MAP_COLS) end_x = MAP_COLS;
    if(end_y > MAP_ROWS) end_y = MAP_ROWS; 

    int x = start_x ,y = start_y, index, loop_length = (end_x - start_x) * (end_y - start_y);
    for(int i = 0; i < loop_length; i++){
        if(x == end_x){
            x = start_x; y++;
        }
        if(y == end_y) break;
        index = x + (MAP_COLS * y);
        screen_position = (SDL_FRect){
            .x = map_info[index].tile.x - ((float)camera.c_x * MAP_CELL_SIZE),
            .y = map_info[index].tile.y - ((float)camera.c_y * MAP_CELL_SIZE),
            .h = map_info[index].tile.h,
            .w = map_info[index].tile.w
        };
        x++;
        SDL_RenderTexture(renderer, map_texture, &map_info[index].sprite, &screen_position);
        if(map_info[index].type == ENTITY && map_info[index].id > -1)
        {
            SDL_RenderTexture(renderer, map_texture, &entities[map_info[index].id].sprite , &screen_position);
        }
    }
    return 0;
}

int map_init(void){
    if(map_mem_init() || load_map_sprite()){
        return 1;
    }
    map_load();

    return 0;
}