#include "map.h"
#include "globals.h"

// Make a large array for map meta info to access later
Map_cell_ground **map_info= NULL;

// initialize map array
int map_init(){
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

