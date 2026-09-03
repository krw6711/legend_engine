#include "globals.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Joystick *joystick = NULL;
SDL_AudioStream *music = NULL;
SDL_AudioStream *sfx = NULL;

char* get_full_path(char* relativePath)
{
    const char* basePath = SDL_GetBasePath();

    if (!basePath) {
        SDL_Log("Failed to get base path: %s", SDL_GetError());
        return NULL;
    }

    size_t len = SDL_strlen(basePath) + SDL_strlen(relativePath) + 1;

    char* fullPath = (char*)SDL_malloc(len);
    if(fullPath == NULL) return NULL;

    if (fullPath) {
        SDL_snprintf(fullPath, len, "%s%s", basePath, relativePath);
    }

    return fullPath;
}

// SDL_Rect camera = {-50, -50, WINDOW_WIDTH, WINDOW_HEIGHT};