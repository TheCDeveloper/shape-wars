#include "level.h"
#include "player.h"
#include "enemy.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL_rect.h>


void level_initialize(level_t *level, SDL_Renderer *renderer) {
    level->player = player_create(renderer);
    
    level->bullet_count = 0;
    level->bullets = NULL;
    
    level->wave = 1;
    level->score = 0;

    level->enemy_count = 0;
    level->enemies = NULL;

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
        enemy->alive = true;

        enemy->sprite.position.x = ((float) rand() / RAND_MAX) * WINDOW_WIDTH;
        enemy->sprite.position.y = ((float) rand() / RAND_MAX) * WINDOW_HEIGHT;
    }
}


void level_event(level_t *level, void *event) {
    player_event(level->player, event);
}


static inline float sprite_distance(const sprite_t *a, const sprite_t *b) {
    return hypot(a->position.x - b->position.x,
                 a->position.y - b->position.y);
}


static inline void uncollide(sprite_t *a, sprite_t *b) {
    float distance = sprite_distance(a, b);
    if (distance > 100.0f) {
        return;
    }

    float angle = atan2(b->position.y - a->position.y,
                        b->position.x - a->position.x);

    a->position.x += cos(angle) * -((100.0f - distance) / 2.0f);
    a->position.y += sin(angle) * -((100.0f - distance) / 2.0f);
    b->position.x += cos(angle) * ((100.0f - distance) / 2.0f);
    b->position.y += sin(angle) * ((100.0f - distance) / 2.0f);
}


void level_update(level_t *level, float deltatime) {
    player_update(level->player, deltatime);

    bool found_alive_enemies = false;
    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        if (!enemy->alive) {
            continue;
        }

        found_alive_enemies = true;
        
        vec2 enemy_pos = enemy->sprite.position;
        vec2 player_pos = level->player->sprite.position;
        float distance = hypot(player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y);

        float dx = (player_pos.x - enemy_pos.x) / distance;
        float dy = (player_pos.y - enemy_pos.y) / distance;
        enemy->sprite.position.x += dx;
        enemy->sprite.position.y += dy;

        // Handle collisions
        uncollide(&level->player->sprite, &enemy->sprite);
        for (size_t j = 0; j < level->enemy_count; j++) {
            enemy_t *other = &level->enemies[j];
            uncollide(&enemy->sprite, &other->sprite);
        }
    }

    if (!found_alive_enemies) {
        // Continue to next wave
        level->wave++;
        free(level->enemies);
        level->enemies = NULL;
        level_start(level);
    }
}


void level_render(level_t *level) {
    sprite_render(&level->player->sprite, level->renderer);

    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        sprite_render(&enemy->sprite, level->renderer);
    }
}
