#ifndef TEXT_H
#define TEXT_H

#include "../global/globals.h"
#include "SDL3/SDL_render.h"

SDL_Texture* generate_text_texture(char *text, int width);

#endif