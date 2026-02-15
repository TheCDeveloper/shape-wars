#include "level.h"
#include "player.h"
#include "enemy.h"

#include <stdlib.h>


void level_initialize(level_t *level, SDL_Renderer *renderer) {
    level->player = player_create(renderer);
    
    level->wave = 1;
    level->score = 0;

    level->enemy_count = 0;
    level->enemies = 0;

    level->renderer = renderer;
}


void level_deinitialize(level_t *level) {
    if (level->enemies) {
        free(level->enemies);
    }

    player_destroy(level->player);
}


static inline int calculate_difficulty(unsigned int wave) {
    return wave * 2 + 5;
}


void level_start(level_t *level) {
    level->enemy_count = calculate_difficulty(level->wave); 
    level->enemies = calloc(level->enemy_count, sizeof(enemy_t));

    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        enemy_initialize(enemy, level->renderer, 10, 1);
    }
}


void level_event(level_t *level, void *event) {
    player_event(level->player, event);
}


void level_update(level_t *level, float deltatime) {
    player_update(level->player, deltatime);

    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        // TODO: add enemy AI
    }
}


void level_render(level_t *level) {
    sprite_render(&level->player->sprite, level->renderer);

    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        sprite_render(&enemy->sprite, level->renderer);
    }
}
