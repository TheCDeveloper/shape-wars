#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "ui.h"

#include <stdbool.h>

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct game {
    bool running;

    SDL_Window *window;
    SDL_Renderer *renderer;

    ui_t *ui;
    level_t level;
} game_t;

game_t *game_init(void);
void game_destroy(game_t *instance);
void game_run(game_t *instance);

#endif // GAME_H
