#ifndef LEVEL_H
#define LEVEL_H

typedef struct SDL_Renderer SDL_Renderer;

typedef struct player_t player_t;
typedef struct enemy_t enemy_t;

typedef struct level_t {
    player_t *player;

    unsigned int wave;
    unsigned int score;

    int enemy_count;
    enemy_t *enemies;

    SDL_Renderer *renderer;
} level_t;

void level_initialize(level_t *level, SDL_Renderer *renderer);
void level_deinitialize(level_t *level);
void level_start(level_t *level);
void level_event(level_t *level, void *event);
void level_update(level_t *level, float deltatime);
void level_render(level_t *level);

#endif // LEVEL_H
