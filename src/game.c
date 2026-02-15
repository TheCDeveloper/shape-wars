#include "game.h"
#include "player.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>


static bool initialize_graphics(game_t *game) {
    game->window = SDL_CreateWindow("ShapeWars",
                                        WINDOW_WIDTH, WINDOW_HEIGHT,
                                        0);
    if (!game->window) {
        fprintf(stderr, "SDL: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, NULL);
    if (!game->renderer) {
        fprintf(stderr, "SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(game->window);
        return false;
    }

    SDL_SetRenderVSync(game->renderer, 1);
    return true;
}


game_t *game_init(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL: %s\n", SDL_GetError());
        return NULL;
    }

    game_t *game = malloc(sizeof(game_t));
    if (!game) {
        return NULL;
    }

    if (!initialize_graphics(game)) {
        return NULL;
    }

    game->player = player_create(game->renderer);

    return game;
}


void game_destroy(game_t *game) {
    if (!game) {
        return;
    }

    player_destroy(game->player);

    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
}


static void handle_events(game_t *game) {
    static SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                game->running = false;
                break;

            default:
                player_event(game->player, &event);
                break;
        }
    }
}


void game_run(game_t *game) {
    if (!game) {
        return;
    }

    game->running = true;
    while (game->running) {
        player_update(game->player, 0.167f);

        SDL_RenderClear(game->renderer);
        sprite_render(&game->player->sprite, game->renderer);
        SDL_RenderPresent(game->renderer);

        handle_events(game);
    }
}
