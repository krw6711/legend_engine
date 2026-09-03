#include "dialogs.h"
#include "SDL3/SDL_log.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *dialogs;
long file_length;

int init_dialogs(void)
{
    FILE *pFile = fopen("./assets/dialogs.txt", "r");

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

    return 0;
}