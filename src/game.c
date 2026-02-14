#include "game.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>


game *game_init(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL: %s\n", SDL_GetError());
        return NULL;
    }

    game *instance = malloc(sizeof(game));
    if (!instance) {
        return NULL;
    }

    instance->window = SDL_CreateWindow("ShapeWars",
                                        WINDOW_WIDTH, WINDOW_HEIGHT,
                                        0);
    if (!instance->window) {
        fprintf(stderr, "SDL: %s\n", SDL_GetError());
        free(instance);
        return NULL;
    }

    instance->renderer = SDL_CreateRenderer(instance->window, NULL);
    if (!instance->renderer) {
        fprintf(stderr, "SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(instance->window);
        free(instance);
        return NULL;
    }

    return instance;
}


void game_destroy(game *instance) {
    if (!instance) {
        return;
    }

    SDL_DestroyRenderer(instance->renderer);
    SDL_DestroyWindow(instance->window);
    free(instance);
}


static void handle_events(game *instance) {
    static SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                instance->running = false;
                break;

            default:
                break;
        }
    }
}


void game_run(game *instance) {
    if (!instance) {
        return;
    }

    instance->running = true;
    while (instance->running) {
        SDL_RenderClear(instance->renderer);
        SDL_RenderPresent(instance->renderer);

        handle_events(instance);
    }
}
