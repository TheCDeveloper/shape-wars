#include "bullet.h"
#include "sprite.h"
#include "constants.h"

#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL_render.h>


static void resize_bullets(bullet_manager_t *manager, size_t size) {
    bullet_t *bullets = calloc(size, sizeof(bullet_t));
    size_t target_size = size > manager->size ? manager->size : size;
    memcpy(bullets, manager->bullets, target_size);
    free(manager->bullets);

    manager->bullets = bullets;
    manager->size = size;
}


void bullet_manager_init(bullet_manager_t *manager, SDL_Renderer *renderer) {
    manager->count = 0;
    manager->size = 512;
    manager->bullets = calloc(manager->size, sizeof(bullet_t));

    manager->renderer = renderer;
    manager->texture = util_load_texture(renderer, "res/bullet.png");
}


void bullet_manager_cleanup(bullet_manager_t *manager) {
    free(manager->bullets);
    manager->bullets = NULL;
    SDL_DestroyTexture(manager->texture);
}


void bullet_manager_shoot(bullet_manager_t *manager,
                          vec2 position,
                          double rotation,
                          int damage) {
    bullet_t *bullet = NULL;

    for (size_t i = 0; i < manager->count; i++) {
        if (!manager->bullets[i].active) {
            bullet = &manager->bullets[i];
            break;
        }
    }

    if (!bullet) {
        if (manager->count > manager->size) {
            resize_bullets(manager, manager->size + 8);
        }

        bullet = &manager->bullets[manager->count++];
    }

    bullet->active = true;
    bullet->sprite.texture = manager->texture;
    bullet->sprite.visible = true;
    bullet->sprite.alpha = 1.0f;
    bullet->sprite.position = (vec2) {
        position.x + 25.0f,
        position.y + 25.0f 
    };
    bullet->sprite.size = (vec2) { 50.0f, 50.0f };
    bullet->sprite.rotation = rotation;

    bullet->velocity.x = cos(rotation * (M_PI / 180.0f)) * 200.0f;
    bullet->velocity.y = sin(rotation * (M_PI / 180.0f)) * 200.0f;
    bullet->damage = damage;
}


static inline void remove_bullet(bullet_manager_t *manager, size_t id) {
    manager->bullets[id].active = false;
}


static inline void update_bullet(bullet_manager_t *manager, size_t id) {
    vec2 position = manager->bullets[id].sprite.position;

    if ((position.x < -100 || position.x > WINDOW_WIDTH + 100) ||
        (position.y < -100 || position.y > WINDOW_HEIGHT + 100)) {
        remove_bullet(manager, id);
    }
}


void bullet_manager_update(bullet_manager_t *manager, float deltatime) {
    for (size_t i = 0; i < manager->count; i++) {
        bullet_t *bullet = &manager->bullets[i];
        bullet->sprite.position.x += bullet->velocity.x * deltatime;
        bullet->sprite.position.y += bullet->velocity.y * deltatime;
        update_bullet(manager, i);
    }
}


void bullet_manager_render(bullet_manager_t *manager) {
    for (size_t i = 0; i < manager->count; i++) {
        bullet_t *bullet = &manager->bullets[i];
        sprite_render(&bullet->sprite, manager->renderer);
    }
}
