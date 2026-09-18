#ifndef PLAYER_H
#define PLAYER_H

#include "../global/globals.h"
#include "SDL3/SDL_rect.h"
#include <stdbool.h>
#include "./items.h"

#define PLAYER_SAVE_FILE_PATH "/save.bin"

typedef struct {
    int HP;  // Health Points
    // int MP;  // Magic Points
    int ATK; // ATtaCk
    int DEF; // DEFence
    int LCK; // LuCK
    int ACC; // ACCurcy
    int EVA; // EVAsion
    int SPD; // SPeeD
} Static_Status_t;

typedef struct {
    int EXP; // EXPerince
    int LVL; // LeVeL
    int EQW; // EQuiped Weapon id
    int EQS; // EQuiped Shield id
    Inventory_t inventory[50];
    unsigned int inventory_cusor;
    unsigned int index; // player possition
} Dynamic_Status_t;

typedef struct{
    bool moving;
    Face_t queue;
    float last_time;
    float passed;
    int new_x;
    int new_y;
} Movement_t;

typedef struct {
    SDL_FRect coordinates;
    int count, start_x, start_y;
} Sprite_t;

typedef struct {
    int index, x, y;
} Coordinates_t;

typedef struct {
    int x, y;
    SDL_FRect tile;
    Sprite_t sprite;
    Movement_t move;
    Face_t face;
    Static_Status_t base;
    Dynamic_Status_t status;
} Player_t;

extern Player_t *player;

static int get_save_file(char* save_file_path);
static int init_player_struct(void);
static int creat_save_file(char* save_file_path);
int save_player_status(void);
static int load_save_file(void);

int init_player(void);
void render_player(void);
static void update_face(void);
static bool is_walkable(Coordinates_t new_coord);
static Face_t is_move_camera_with_player(Coordinates_t new_coord);
static Coordinates_t get_new_index(void);
static int update_position(void);
void move_player(Face_t face);
void do_action(void);

#endif