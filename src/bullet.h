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

typedef struct bullet_manager_t {
    size_t count;
    size_t size;
    bullet_t *bullets;

    SDL_Renderer *renderer;
    SDL_Texture *texture;
} bullet_manager_t;

void bullet_manager_init(bullet_manager_t *manager, SDL_Renderer *renderer);
void bullet_manager_cleanup(bullet_manager_t *manager);
void bullet_manager_shoot(bullet_manager_t *manager,
                          vec2 position,
                          double rotation,
                          int damage);
void bullet_manager_update(bullet_manager_t *manager, float deltatime);
void bullet_manager_render(bullet_manager_t *manager);

#endif // BULLET_H
