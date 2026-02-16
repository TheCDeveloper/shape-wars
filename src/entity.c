#include "entity.h"


void entity_init(entity_t *entity, int health) {
    entity->sprite.visible = true;
    entity->sprite.alpha = 1.0f;
    entity->sprite.position = (vec2) { 0, 0 };
    entity->sprite.size = (vec2) { 100, 100 };
    entity->sprite.rotation = 0.0;

    entity->alive = true;
    entity->velocity = (vec2) { 0, 0 };
    entity->health.value = health;
    entity->health.max = health;
}


void entity_update(entity_t *entity, float deltatime) {
    if (!entity->alive) {
        return;
    } else if (entity->health.value <= 0) {
        entity->alive = false;
        return;
    }

    entity->sprite.position.x += entity->velocity.x * deltatime;
    entity->sprite.position.y += entity->velocity.y * deltatime;
}


void entity_render(entity_t *entity, SDL_Renderer *renderer) {
    sprite_render(&entity->sprite, renderer);
}
