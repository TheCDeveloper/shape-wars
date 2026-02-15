#include "sprite.h"

#include <stdio.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>


SDL_Texture *util_load_texture(SDL_Renderer *renderer, const char *filename) {
    SDL_Surface *surface = SDL_LoadSurface(filename);
    if (!surface) {
        fprintf(stderr,
                "util_load_texture, sprite.c: file not found (%s)\n",
                filename);
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}


void sprite_render(sprite_t *sprite, SDL_Renderer *renderer) {
#ifndef NDEBUG
    if (!sprite || !renderer) {
        fprintf(stderr, "sprite_render, sprite.c: sprite or renderer is NULL\n");
        return;
    }
#endif

    SDL_FRect dst = {
        sprite->position.x, sprite->position.y,
        sprite->size.x, sprite->size.y
    };

    SDL_FPoint center = {
        dst.w / 2.0f, dst.h / 2.0f
    };

    SDL_RenderTextureRotated(renderer,
                             sprite->texture,
                             NULL,
                             &dst,
                             sprite->rotation,
                             &center,
                             SDL_FLIP_NONE);
}
