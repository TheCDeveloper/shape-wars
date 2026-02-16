#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"

typedef struct entity_t {
    sprite_t sprite;
    vec2 velocity;

    struct {
        int value;
        int max;
    } health;

    bool alive;
} entity_t;

void entity_init(entity_t *entity, int health);
void entity_update(entity_t *entity, float deltatime);
void entity_render(entity_t *entity, SDL_Renderer *renderer);

#endif // ENTITY_H
