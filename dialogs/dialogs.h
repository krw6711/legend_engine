#ifndef DIALOGS_H
#define DIALOGS_H

#include "../global/globals.h"

#define DIALOGS_AMOUNT 5
#define DIALOG_WIDTH 500

typedef struct {
    SDL_Texture *text_texture;
    SDL_FRect sprite;
    bool rendering, is_end;
} Current_Dialog_t;

extern char *dialogs;
extern long file_length;
extern Current_Dialog_t current_dialog;

int init_dialogs(void);
int get_dialog_cursor_by_id(int id);
int get_dialog_length_by_cursor(int cursor);
int redner_dialog_by_id(int id);
void destroy_dialog(void);
int dialog_to_texture(void);
void render_current_dialog(void);
void dialog_event_handler(void);

#endif