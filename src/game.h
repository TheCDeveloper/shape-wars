#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct game {
    bool running;

    SDL_Window *window;
    SDL_Renderer *renderer;
} game;

game *game_init(void);
void game_destroy(game *instance);
void game_run(game *instance);

#endif // GAME_H
