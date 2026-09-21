#include "dialogs.h"
#include "../global/globals.h"
#include "../map/map.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../game/actions.h"

#include "../audio/audio.h"

char *dialogs;
static long file_length;
Current_Dialog_t current_dialog;

int init_dialogs(void) {
  char *full_path = get_full_path("/assets/dialogs.txt");

  FILE *pFile = fopen(full_path, "r");

  SDL_free(full_path);
  full_path = NULL;

  if (pFile == NULL) {
    return 1;
  }

  fseek(pFile, 0, SEEK_END);             // seek to end of file
  unsigned long fileSize = ftell(pFile); // get current file pointer
  fseek(pFile, 0, SEEK_SET);             // seek back to beginning of file

  dialogs = SDL_malloc(fileSize + 1);

  if (dialogs == NULL) {
    fclose(pFile);
    return 1;
  }

  size_t bytesRead = fread(dialogs, 1, fileSize, pFile);
  dialogs[bytesRead] = '\0';

  file_length = fileSize + 1;

  fclose(pFile);

  current_dialog =
      (Current_Dialog_t){.is_end = false,
                         .rendering = false,
                         .sprite = {0, 0, 0, 0},
                         .text_texture = NULL,
                         .rendering_line = 0,
                         .last_time = (float)SDL_GetTicks() / 1000.0f,
                         .is_end_page = false,
                         .offset = 0,
                         .callback = -1
                        };

  return 0;
}

int get_dialog_cursor_by_id(int id) {
  int new_lines = 0;

  for (int i = 0; i < file_length; i++) {
    if (id == new_lines) {
      return i;
      break;
    }
    if (dialogs[i] == '\n') {
      new_lines++;
    }
  }
  return -1;
}

int get_dialog_length_by_cursor(int cursor) {
  int len = 0;
  while (cursor < file_length) {
    if (dialogs[cursor] == '\n') {
      return len;
    }
    cursor++;
    len++;
  }
  return len;
}

int get_dialog_len_by_id(int id)
{
    int cursor = get_dialog_cursor_by_id(id);
    if (cursor == -1) return 0;
    
    int len = get_dialog_length_by_cursor(cursor);
    if (len == -1) return 0;
    
    return len;
}

int load_dialog_from_file(int id, char* text)
{
    int cursor = get_dialog_cursor_by_id(id);
    if (cursor == -1) return 0;
    
    int len = get_dialog_length_by_cursor(cursor);
    if (len == -1) return 0;
    
    // char* dialog = SDL_calloc(sizeof(char), len + 1);

    for (int i = 0; i < len; i++) {
        text[i] = dialogs[i + cursor];
    }
    text[len] = '\0';

    // SDL_Log("from file: %s", text);
    // return dialog;
    return len;
}

int redner_dialog_by_id(int id, SDL_FRect *icon_sprite, int callback, char* text)
{
    int len;
    if(id >= 0 && !text)
    {
        len = get_dialog_len_by_id(id) + 1;
    }else{
        len = SDL_strlen(text) + 1;
    }
    char dialog[len];

    if(id >= 0) load_dialog_from_file(id, dialog);
    if(text) SDL_strlcpy(dialog, text, len);

    SDL_Texture* new_texture = text2texture(dialog, DIALOG_WIDTH, NULL);

    if (current_dialog.text_texture) {
        SDL_DestroyTexture(current_dialog.text_texture);
    }
    current_dialog.text_texture = new_texture;

    if (icon_sprite) current_dialog.rendering = true;
    if (callback != -1) current_dialog.callback = callback;

    current_dialog.icon_sprite = icon_sprite;

    current_dialog.sprite = (SDL_FRect){
        .x = 0,
        .y = 0,
        .w = 0,
        .h = TTF_GetFontLineSkip(font),
    };

    play_sfx(3);
    return 0;
}

void render_dialog_box()
{
  SDL_FRect dst;
  int h = TTF_GetFontLineSkip(font) * 3 + 100;
  int w = CAMERA_X_CELLS * MAP_CELL_SIZE;
  SDL_FRect src = {0*MAP_SPRITE_SIZE, 7*MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE * 3};
  dst.x = dst.y = 0;
  dst.w = MAP_CELL_SIZE; dst.h = h;
  SDL_RenderTexture(renderer, map_texture, &src, &dst);
  dst.y = 0; dst.x = dst.w;
  src.x = 1 * MAP_SPRITE_SIZE;
  dst.w = w - MAP_CELL_SIZE * 2;
  SDL_RenderTexture(renderer, map_texture, &src, &dst);
  dst.x = w - MAP_CELL_SIZE; dst.y = 0;
  src.x = 2 * MAP_SPRITE_SIZE;
  dst.w = MAP_CELL_SIZE; dst.h = h;
  SDL_RenderTexture(renderer, map_texture, &src, &dst);
  dst.x = dst.y = (int)MAP_CELL_SIZE / 2;
  dst.w = dst.h = 2 * MAP_CELL_SIZE;
  SDL_RenderTexture(renderer, map_texture, current_dialog.icon_sprite, &dst);
}

void output_dialog(SDL_FRect *dst)
{
    SDL_RenderTexture(renderer, current_dialog.text_texture, &current_dialog.sprite, dst);
}

void render_letter_by_time(SDL_FRect *dst)
{
    float now = (float)SDL_GetTicks() / 1000.0f;
    if (now - current_dialog.last_time >= 0.05){
        current_dialog.sprite.w += 20;
        dst->w += 20;
        current_dialog.last_time = now;
    }
}

void render_printed_lines()
{
    SDL_FRect src = {0,0,current_dialog.text_texture->w,TTF_GetFontLineSkip(font)}, dst = src;
    dst.x = 150; dst.y = 25;
    // SDL_Log("render last lines");
    for(int i = 0; i < current_dialog.rendering_line; i++)
    {
        src.y = current_dialog.offset +  i * TTF_GetFontLineSkip(font);
        dst.y = i * TTF_GetFontLineSkip(font) + 25;
        // SDL_Log("printing the old line %d at y %f, w %f", i,dst.y , dst.w);
        SDL_RenderTexture(renderer, current_dialog.text_texture, &src, &dst);
    }
}

void render_current_line()
{
    SDL_FRect dst = current_dialog.sprite;
    dst.x = 150;
    current_dialog.sprite.y = current_dialog.offset +  current_dialog.rendering_line * TTF_GetFontLineSkip(font);
    dst.y = current_dialog.rendering_line * TTF_GetFontLineSkip(font) + 25;
    render_letter_by_time(&dst);
    // SDL_Log("printing current line %d a line at y %f, w %f", current_dialog.rendering_line ,dst.y, dst.w);
    output_dialog(&dst);
}

void render_arrow()
{
    SDL_FRect src = {0*MAP_SPRITE_SIZE, 6*MAP_SPRITE_SIZE, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}, 
    dst = {150, 3 * TTF_GetFontLineSkip(font) + 45, MAP_CELL_SIZE, MAP_CELL_SIZE};
    SDL_RenderTexture(renderer, map_texture, &src, &dst);
}

void render_current_dialog()
{
    if (!current_dialog.rendering) return;
    // SDL_Log("Rendering Box!");
    
    render_dialog_box();
    render_printed_lines();
    
    if(current_dialog.sprite.w >= current_dialog.text_texture->w){
        // SDL_Log("we hit the end of the width!");
        current_dialog.sprite.w = 0;
        // SDL_Log("we reset the dst width to zero");
        current_dialog.rendering_line++;
        // SDL_Log("we increase the rendered lines");
    }
    if(current_dialog.sprite.y + TTF_GetFontLineSkip(font) > current_dialog.text_texture->h){
        current_dialog.is_end = true;
        render_arrow();
        // SDL_Log("there is no more height lets end this now!");
        return;
    }
    if(current_dialog.rendering_line > 2){
        // SDL_Log("there is more height but we hit the third line, lets move the offeset, arrow rendered");
        current_dialog.is_end_page = true;
        render_arrow();
        return;
    }
    // SDL_Log("start printing current line: %d", current_dialog.rendering_line);
    render_current_line();
}

void destroy_dialog()
{
    current_dialog.rendering = false;
    current_dialog.is_end = false;
    current_dialog.sprite = (SDL_FRect){0, 0, 0, 0};
    current_dialog.is_end_page = false;
    current_dialog.rendering_line = 0;
    current_dialog.offset = 0;
    SDL_DestroyTexture(current_dialog.text_texture);
    current_dialog.text_texture = NULL;
    current_dialog.icon_sprite = NULL;

    int callback = current_dialog.callback; 
    current_dialog.callback = -1;
    
    if(callback != -1){
        functions[callback]();
    }
}

void move_dialog_offset()
{
    current_dialog.sprite.w = 0;
    current_dialog.offset += current_dialog.rendering_line * TTF_GetFontLineSkip(font);
    current_dialog.rendering_line = 0;
    current_dialog.is_end_page = false;
}

void dialog_event_handler() 
{
    if (current_dialog.is_end) {
    //   SDL_Log("Destroying!");
        destroy_dialog();
    }
    if(current_dialog.is_end_page){
        move_dialog_offset();
    }
}