#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"

#include <stdbool.h>

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

SDL_Texture *util_load_texture(SDL_Renderer *renderer, const char *filename); 

typedef struct sprite_t {
    SDL_Texture *texture;
    bool visible;
    float alpha;
    
    vec2 position;
    vec2 size;

    double rotation;
} sprite_t;

void sprite_render(sprite_t *sprite, SDL_Renderer *renderer);

#endif // SPRITE_H
