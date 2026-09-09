#include "text.h"
#include "SDL3/SDL_render.h"

SDL_Texture *generate_text_texture(char *text, int width)
{
    SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};
    SDL_Surface *text_surf;

    text_surf = TTF_RenderText_Blended_Wrapped(font, text, 0, color, width);

    if (!text_surf) return NULL;

    SDL_Texture *new_text_texture = SDL_CreateTextureFromSurface(renderer, text_surf);
    
    SDL_DestroySurface(text_surf);
    if(!new_text_texture) return NULL;

    return new_text_texture;
}