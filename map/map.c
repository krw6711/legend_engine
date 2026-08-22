#include "map.h"
#include <stdlib.h>
#include "SDL3/SDL_log.h"
#include "camera.h"

// Make a large array for map meta info to access later
Map_cell_ground **map_info = NULL;
SDL_Texture *map_texture = NULL;
SDL_Texture *map_frame =  NULL;

// Object_t camera = {.x=0,.y=0, .border={0, 0, -(MAP_CELL_SIZE*MAP_COLS) - WINDOW_WIDTH, -(MAP_ROWS*MAP_CELL_SIZE) - WINDOW_HEIGHT}};

// initialize map array
int map_mem_init(void){
    map_info = malloc(MAP_ROWS * sizeof(Map_cell_ground *));
    if(!map_info){
        SDL_Log("Error Allocating Memory for map");
        return 1;
    }
    for(int i = 0; i < MAP_ROWS; i++){
        map_info[i] = malloc(MAP_COLS * sizeof(Map_cell_ground));
        if(!map_info[i]){
            SDL_Log("Error Allocating Memory for map");
            return 1;
        }
    }
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
    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLS; j++){

            if( i == 0 || i == MAP_ROWS - 1 || j == 0 || j == MAP_COLS -1 ){
                map_info[i][j] = (Map_cell_ground){
                    .sprite = {1*MAP_SPRITE_SIZE, 7*MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE},
                    .tile = {(j)*MAP_CELL_SIZE, (i)*MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE},
                    .x = j,
                    .y = i
                };
            }else if(i % 3 == 0 && j % 3 == 0){
                map_info[i][j] = (Map_cell_ground){
                    .sprite = {15*MAP_SPRITE_SIZE, 1*MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE},
                    .tile = {(j)*MAP_CELL_SIZE, (i)*MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE},
                    .x = j,
                    .y = i
                };
            }else{
                map_info[i][j] = (Map_cell_ground){
                    .sprite = {13*MAP_SPRITE_SIZE, 9*MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE},
                    .tile = {(j)*MAP_CELL_SIZE, (i)*MAP_CELL_SIZE, MAP_CELL_SIZE, MAP_CELL_SIZE},
                    .x = j,
                    .y = i
                };
            }

            // SDL_Log("loaded %d %d", j, i);
        }
    }
}

int map_render(void){
    SDL_FRect screen_position;

    int start_x = (int)camera.c_x;
    int start_y = (int)camera.c_y; 

    // SDL_Log("camera x,y: %f, %f", camera.c_x, camera.c_y);

    int end_x = start_x + camera.w_x + 1;
    int end_y = start_y + camera.w_y + 1;

    if(start_x < 0) start_x = 0;
    if(start_y < 0) start_y = 0;
    if(end_x > MAP_COLS) end_x = MAP_COLS;
    if(end_y > MAP_ROWS) end_y = MAP_ROWS; 

    for(int i = start_y; i < end_y ; i++){
        for(int j = start_x; j < end_x; j++){
            screen_position = (SDL_FRect){
                .x = map_info[i][j].tile.x - ((float)camera.c_x * MAP_CELL_SIZE),
                .y = map_info[i][j].tile.y - ((float)camera.c_y * MAP_CELL_SIZE),
                .h = map_info[i][j].tile.h,
                .w = map_info[i][j].tile.w
            };
            SDL_RenderTexture(renderer, map_texture, &map_info[i][j].sprite, &screen_position);
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