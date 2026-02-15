#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct player_t player_t;

typedef struct game {
    bool running;

    SDL_Window *window;
    SDL_Renderer *renderer;

    player_t *player;
} game_t;

game_t *game_init(void);
void game_destroy(game_t *instance);
void game_run(game_t *instance);

#endif // GAME_H
