#ifndef DIALOGS_H
#define DIALOGS_H

#include "../global/globals.h"

#define DIALOGS_AMOUNT 5
#define DIALOG_WIDTH ((MAP_CELL_SIZE * CAMERA_X_CELLS) - 200)

typedef struct {
    SDL_Texture *text_texture;
    SDL_FRect sprite;
    SDL_FRect *icon_sprite;
    int *callback;
    bool rendering, is_end_page, is_end;
    int rendering_line, offset;
    float last_time;
} Current_Dialog_t;

extern char *dialogs;
extern Current_Dialog_t current_dialog;

int init_dialogs(void);

static int get_dialog_cursor_by_id(int id);
static int get_dialog_length_by_cursor(int cursor);

int redner_dialog_by_id(int id, SDL_FRect *icon_sprite, int *callback);

static void render_dialog_box();

static void output_dialog(SDL_FRect *dst);
static void render_letter_by_time(SDL_FRect *dst);
static void render_printed_lines();
static void render_current_line();
static void render_arrow();

static void destroy_dialog(void);
static void move_dialog_offset();

static int dialog_to_texture(void);
void render_current_dialog(void);
void dialog_event_handler(void);

#endif