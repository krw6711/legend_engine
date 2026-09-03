#include "dialogs.h"
#include "../global/globals.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *dialogs;
long file_length;
Current_Dialog_t current_dialog;

int init_dialogs(void)
{
    char* full_path = get_full_path("/assets/dialogs.txt");
    
    FILE *pFile = fopen(full_path, "r");

    free(full_path);
    full_path = NULL;

    if(pFile == NULL){
        return 1;
    }
    
    fseek(pFile, 0, SEEK_END); // seek to end of file
    unsigned long fileSize = ftell(pFile); // get current file pointer
    fseek(pFile, 0, SEEK_SET); // seek back to beginning of file

    dialogs = malloc(fileSize + 1);

    if(dialogs == NULL){
        fclose(pFile);
        return 1;
    }

    size_t bytesRead = fread(dialogs, 1, fileSize, pFile);
    dialogs[bytesRead] = '\0';

    file_length = fileSize + 1;

    fclose(pFile);

    current_dialog = (Current_Dialog_t){
        .is_end = false,
        .rendering = false,
        .sprite = {0, 0, 0, 0},
        .text_texture = NULL
    };

    return 0;
}

int get_dialog_cursor_by_id(int id)
{
    int new_lines = 0;

    for(int i = 0; i < file_length; i++)
    {
        if(id == new_lines){
            return i;
            break;
        }
        if(dialogs[i] == '\n'){
            new_lines++;
        }
    }
    return -1;
}

int get_dialog_length_by_cursor(int cursor)
{
    int len = 0;
    while(cursor < file_length){
        if(dialogs[cursor] == '\n'){
            return len;
        }
        cursor++;
        len++;
    }
    return len;
}

int redner_dialog_by_id(int id)
{
    int cursor = get_dialog_cursor_by_id(id);
    if(cursor == -1) return 1;
        
    int len = get_dialog_length_by_cursor(cursor);
    if(len == -1) return 1;

    char dialog[len + 1];
    for(int i = 0; i < len; i++)
    {
        dialog[i] = dialogs[i + cursor];
    }
    dialog[len] = '\0';

    SDL_Log("dialog: %s", dialog);

    SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Surface *text;

    text = TTF_RenderText_Blended_Wrapped(font, dialog, 0, color, DIALOG_WIDTH);
    if (text) {
        current_dialog.text_texture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_DestroySurface(text);
    }
    if (!current_dialog.text_texture) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
        return 1;
    }

    current_dialog.rendering = true;
    if((current_dialog.sprite.y + current_dialog.sprite.h) >= current_dialog.text_texture->h ){
        current_dialog.is_end = true;
    }

    current_dialog.sprite = (SDL_FRect){
        .x = 0, .y = 0,
        .w = current_dialog.text_texture->w,
        .h = TTF_GetFontLineSkip(font)*3
    };
    return 0;
}

void render_current_dialog()
{
    if(current_dialog.rendering){
        SDL_FRect dst = {
            .x = 0, .y = 0,
            .w = DIALOG_WIDTH + 300 , .h = TTF_GetFontLineSkip(font)*3 + 100
        };
        SDL_SetRenderDrawColor( renderer,90, 90, 90, 90);
        SDL_RenderFillRect(renderer, &dst);
        dst.x += 200;
        dst.y += 50;
        dst.w = current_dialog.sprite.w;
        if(TTF_GetFontLineSkip(font)*3 > current_dialog.text_texture->h){
            dst.h = current_dialog.text_texture->h;
        }else{
            dst.h = TTF_GetFontLineSkip(font)*3;
        }
        SDL_RenderTexture(renderer, current_dialog.text_texture, &current_dialog.sprite, &dst);
    }
}

void destroy_dialog()
{
    current_dialog.rendering = false;
    current_dialog.is_end = false;
    current_dialog.sprite = (SDL_FRect){0, 0, 0, 0};
    SDL_DestroyTexture(current_dialog.text_texture);
    current_dialog.text_texture = NULL;
}

void dialog_event_handler(){
    if(current_dialog.rendering){
        if((current_dialog.sprite.y + current_dialog.sprite.h) >= current_dialog.text_texture->h ){
            current_dialog.is_end = true;
        }
    }
    if(current_dialog.is_end){
        destroy_dialog();
    }
    current_dialog.sprite.y += current_dialog.sprite.h;
}