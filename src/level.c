#include "level.h"
#include "enemy.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>


void level_initialize(level_t *level, SDL_Renderer *renderer) {
    player_init(&level->player, renderer);
    
    bullet_engine_init(&level->bullet_engine, renderer);
    
    level->wave = 1;
    level->score = 0;

    level->enemy_count = 0;
    level->enemies = NULL;

    level->renderer = renderer;
    level->background = util_load_texture(renderer, "res/background.png");
}


void level_deinitialize(level_t *level) {
    if (level->enemies) {
        free(level->enemies);
    }

    bullet_engine_cleanup(&level->bullet_engine);
    player_cleanup(&level->player);
    SDL_DestroyTexture(level->background);
}


static inline int calculate_difficulty(unsigned int wave) {
    return wave * 2 + 5;
}


static inline float rand_rangef(float min, float max) {
    return (rand() / (float) RAND_MAX) * (max - min) + min;
}


void level_start(level_t *level) {
    level->enemy_count = calculate_difficulty(level->wave); 
    level->enemies = calloc(level->enemy_count, sizeof(enemy_t));

    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        enemy_init(enemy, level->renderer, 10, 1);
        enemy->entity.alive = true;

        enemy->entity.sprite.position.x = rand_rangef(-2000,
                                                      WINDOW_WIDTH + 2000);
        enemy->entity.sprite.position.y = rand_rangef(-2000,
                                                      WINDOW_HEIGHT + 2000);

        bullet_engine_register_entity(&level->bullet_engine, &enemy->entity);
    }
}


void level_event(level_t *level, void *event) {
    player_event(&level->player, event);

    SDL_Event *e = event;
    if (e->type == SDL_EVENT_KEY_DOWN) {
        if (e->key.scancode == SDL_SCANCODE_SPACE) {
            vec2 position = level->player.entity.sprite.position;
            position.x += level->player.entity.sprite.size.x / 2.0f;
            position.y += level->player.entity.sprite.size.y / 2.0f;

            bullet_engine_shoot(&level->bullet_engine,
                                 position,
                                 level->player.entity.sprite.rotation,
                                 10);
        }
    }
}


static inline float sprite_distance(const sprite_t *a, const sprite_t *b) {
    return hypot(a->position.x - b->position.x,
                 a->position.y - b->position.y);
}


static inline void uncollide(sprite_t *a, sprite_t *b, float min_distance) {
    float distance = sprite_distance(a, b);
    if (distance > min_distance) {
        return;
    }

    float angle = atan2(b->position.y - a->position.y,
                        b->position.x - a->position.x);

    a->position.x += cos(angle) * -((min_distance - distance) / 2.0f);
    a->position.y += sin(angle) * -((min_distance - distance) / 2.0f);
    b->position.x += cos(angle) * ((min_distance - distance) / 2.0f);
    b->position.y += sin(angle) * ((min_distance - distance) / 2.0f);
}


void level_update(level_t *level, float deltatime) {
    player_update(&level->player, deltatime);
    bullet_engine_update(&level->bullet_engine, deltatime);

    bool found_alive_enemies = false;
    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        if (!enemy->entity.alive) {
            continue;
        }

        found_alive_enemies = true;

        entity_update(&enemy->entity, deltatime);

        if (!enemy->entity.alive) {
            bullet_engine_unregister_entity(&level->bullet_engine,
                                            &enemy->entity);
        }
        
        vec2 enemy_pos = enemy->entity.sprite.position;
        vec2 player_pos = level->player.entity.sprite.position;
        float distance = hypot(player_pos.x - enemy_pos.x,
                               player_pos.y - enemy_pos.y);

        float dx = (player_pos.x - enemy_pos.x) / distance;
        float dy = (player_pos.y - enemy_pos.y) / distance;
        enemy->entity.sprite.position.x += dx;
        enemy->entity.sprite.position.y += dy;

        enemy->entity.sprite.rotation = atan2(player_pos.y - enemy_pos.y,
                                              player_pos.x - enemy_pos.x) *
                                        (180.0f / M_PI);

        // Handle collisions
        uncollide(&level->player.entity.sprite, &enemy->entity.sprite, 75.0f);
        for (size_t j = 0; j < level->enemy_count; j++) {
            enemy_t *other = &level->enemies[j];
            uncollide(&enemy->entity.sprite, &other->entity.sprite, 100.0f);
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
    SDL_RenderTexture(level->renderer, level->background, 0, 0);

    bullet_engine_render(&level->bullet_engine);
    sprite_render(&level->player.entity.sprite, level->renderer);

    for (size_t i = 0; i < level->enemy_count; i++) {
        enemy_t *enemy = &level->enemies[i];
        if (!enemy->entity.alive) {
            continue;
        }

        sprite_render(&enemy->entity.sprite, level->renderer);
    }
}
