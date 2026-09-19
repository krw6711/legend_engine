#include "globals.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Joystick *joystick = NULL;
SDL_AudioStream *music = NULL;
SDL_AudioStream *sfx = NULL;
TTF_Font *font = NULL;
Menu_t current_screen;
bool fullscreen_mode = false;

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

SDL_Texture* text2texture(char* text, int width, SDL_Color* color)
{
    SDL_Surface *surf;

    if(!color) {
        SDL_Color default_color = {255, 255, 255, SDL_ALPHA_OPAQUE};
        color = &default_color;
    }

    surf = TTF_RenderText_Blended_Wrapped(font, text, 0, *color, width);
    if (!surf) {
        SDL_Log("Couldn't create text surface: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);
    if (!texture) {
        SDL_Log("Couldn't create text texture: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

// SDL_Rect camera = {-50, -50, WINDOW_WIDTH, WINDOW_HEIGHT};