#include "map.h"
#include "globals.h"

// Make a large array for map meta info to access later
Map_cell_ground **map_info = NULL;
SDL_Texture *map_texture = NULL;

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

void map_draw(void){
    // 14 20 21
    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLS; j++){

            if( i == 0 || i == MAP_ROWS - 1 || j == 0 || j == MAP_COLS -1 ){
                map_info[i][j] = (Map_cell_ground){
                    .sprite = {25*16, 0, 16, 16},
                    .tile = {j*50, i*50, 50, 50},
                    .x = j,
                    .y = i
                };
            }else{
                map_info[i][j] = (Map_cell_ground){
                    .sprite = {40*16, 0, 16, 16},
                    .tile = {j*50, i*50, 50, 50},
                    .x = j,
                    .y = i
                };
            }
        }
    }
    // return 0;
}

void map_render(void){
    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLS; j++){
            SDL_RenderTexture(renderer, map_texture, &map_info[i][j].sprite, &map_info[i][j].tile);
        }
    }
}

int map_init(void){
    if(map_mem_init() || load_map_sprite()){
        return 1;
    }
    map_draw();

    return 0;
}