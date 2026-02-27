#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

#include <stddef.h>

typedef struct bullet_t {
    bool active;
    sprite_t sprite;

    vec2 velocity;
    int damage;
} bullet_t;

typedef struct bullet_engine_t {
    size_t bullets_count;
    size_t bullets_size;
    bullet_t *bullets;

    size_t entities_count;
    size_t entities_size;
    entity_t **entities;

    SDL_Renderer *renderer;
    SDL_Texture *texture;
} bullet_engine_t;

void bullet_engine_init(bullet_engine_t *be, SDL_Renderer *renderer);
void bullet_engine_cleanup(bullet_engine_t *be);
void bullet_engine_register_entity(bullet_engine_t *be, entity_t *entity);
void bullet_engine_unregister_entity(bullet_engine_t *be, entity_t *entity);
void bullet_engine_shoot(bullet_engine_t *be,
                         vec2 position,
                         double rotation,
                         int damage);
void bullet_engine_update(bullet_engine_t *be, float deltatime);
void bullet_engine_render(bullet_engine_t *be);

#endif // BULLET_H
