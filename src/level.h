#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "bullet.h"

#include <stddef.h>

typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

typedef struct player_t player_t;
typedef struct enemy_t enemy_t;

typedef struct bullet_t bullet_t;

typedef struct level_t {
    player_t player;

    bullet_manager_t bullet_manager;

    unsigned int wave;
    unsigned int score;

    size_t enemy_count;
    enemy_t *enemies;

    SDL_Renderer *renderer;
    SDL_Texture *background;
} level_t;

void level_initialize(level_t *level, SDL_Renderer *renderer);
void level_deinitialize(level_t *level);
void level_start(level_t *level);
void level_event(level_t *level, void *event);
void level_update(level_t *level, float deltatime);
void level_render(level_t *level);

#endif // LEVEL_H
