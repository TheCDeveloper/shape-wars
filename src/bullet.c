#include "bullet.h"
#include "sprite.h"
#include "constants.h"

#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL_render.h>


static void resize_bullets_array(bullet_engine_t *be, size_t new_size) {
    bullet_t *bullets = calloc(new_size, sizeof(bullet_t));
    size_t size = new_size < be->bullets_count ? new_size : be->bullets_count;
    memmove(bullets, be->bullets, size * sizeof(bullet_t));
    free(be->bullets);

    be->bullets_size = new_size;
    be->bullets = bullets;
}


static void resize_entities_array(bullet_engine_t *be, size_t new_size) {
    entity_t **entities = calloc(new_size, sizeof(entity_t *));
    size_t size = new_size < be->entities_count ? new_size : be->entities_count;
    memmove(entities, be->entities, size * sizeof(entity_t *));
free(be->entities);

    be->entities_size = new_size;
    be->entities = entities;
}


void bullet_engine_init(bullet_engine_t *be, SDL_Renderer *renderer) {
    be->bullets_count = 0;
    be->bullets_size = 1024;
    be->bullets = calloc(be->bullets_size, sizeof(bullet_t));

    be->entities_count = 0;
    be->entities_size = 64;
    be->entities = calloc(be->entities_size, sizeof(entity_t *));

    be->renderer = renderer;
    be->texture = util_load_texture(renderer, "res/bullet.png");
}


void bullet_engine_cleanup(bullet_engine_t *be) {
    free(be->bullets);
    free(be->entities);

    SDL_DestroyTexture(be->texture);
}


void bullet_engine_register_entity(bullet_engine_t *be, entity_t *entity) {

    size_t index = SIZE_MAX;
    for (size_t i = 0; i < be->entities_count; i++) {
        if (be->entities[i] == NULL) {
            index = i;
            break;
        }
    }

    if (index == SIZE_MAX) {
        if (be->entities_size <= be->entities_count + 1) {
            resize_entities_array(be, be->entities_size * 2);
        }

        index = be->entities_count++;
    }

    be->entities[index] = entity;
}


void bullet_engine_unregister_entity(bullet_engine_t *be, entity_t *entity) {
    size_t index = SIZE_MAX;
    for (size_t i = 0; i < be->entities_count; i++) {
        if (be->entities[i] == entity) {
            index = i;
            break;
        }
    }

    if (index == SIZE_MAX) {
        return;
    }

    be->entities[index] = NULL;

    if (index + 1 == be->entities_count) {
        be->entities_count--;
    }
}


void bullet_engine_shoot(bullet_engine_t *be,
                          vec2 position,
                          double rotation,
                          int damage) {

    size_t index = SIZE_MAX;
    for (size_t i = 0; i < be->bullets_count; i++) {
        if (!be->bullets[i].active) {
            index = i;
            break;
        }
    }

    if (index == SIZE_MAX) {
        if (be->bullets_count >= be->bullets_size) {
            resize_bullets_array(be, be->bullets_size * 2);
        }

        index = be->bullets_count++;
    }

    position = (vec2) { position.x - 25.0f, position.y - 25.0f };

    bullet_t *bullet = &be->bullets[index];
    bullet->active = true;

    bullet->sprite = (sprite_t) {
        be->texture,
        true,
        1.0f,
        position,
        (vec2) { 50.0f, 50.0f },
        rotation
    };

    bullet->velocity.x = cos(rotation * (M_PI / 180.0f)) * 50.0f;
    bullet->velocity.y = sin(rotation * (M_PI / 180.0f)) * 50.0f;
    bullet->damage = damage;
}


static void remove_bullet(bullet_engine_t *be, size_t index) {
    be->bullets[index].active = false;

    if (index + 1 == be->bullets_count) {
        be->bullets_count--;
    }
}


static bool is_bullet_valid(bullet_engine_t *be, bullet_t *bullet) {
    vec2 pos = bullet->sprite.position;
    if ((pos.x < -500 || pos.x > WINDOW_WIDTH + 500) &&
        (pos.y < -500 || pos.y > WINDOW_HEIGHT + 500)) {
        return false;
    }

    SDL_FRect a = {
        bullet->sprite.position.x, bullet->sprite.position.y,
        bullet->sprite.size.x, bullet->sprite.size.y
    };

    for (size_t i = 0; i < be->entities_count; i++) {
        entity_t *entity = be->entities[i];
        SDL_FRect b = {
            entity->sprite.position.x, entity->sprite.position.y,
            entity->sprite.size.x, entity->sprite.size.y
        };

        if (SDL_HasRectIntersectionFloat(&a, &b)) {
            return false;
        }
    }

    return true;
}


void bullet_engine_update(bullet_engine_t *be, float deltatime) {
    for (size_t i = 0; i < be->bullets_count; i++) {
        bullet_t *bullet = &be->bullets[i];
        if (!bullet->active) {
            continue;
        }

        bullet->sprite.position.x += bullet->velocity.x * deltatime;
        bullet->sprite.position.y += bullet->velocity.y * deltatime;

        if (!is_bullet_valid(be, bullet)) {
            remove_bullet(be, i);
        }
    }
}


void bullet_engine_render(bullet_engine_t *be) {
    for (size_t i = 0; i < be->bullets_count; i++) {
        bullet_t *bullet = &be->bullets[i];
        if (!bullet->active) {
            continue;
        }

        sprite_render(&bullet->sprite, be->renderer);
    }
}
