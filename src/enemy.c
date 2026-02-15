#include "enemy.h"


void enemy_initialize(enemy_t *enemy,
                      SDL_Renderer *renderer,
                      int health,
                      int damage) {
    enemy->sprite.texture = util_load_texture(renderer, "res/enemy.png");
    enemy->sprite.visible = true;
    enemy->sprite.alpha = 1.0f;

    enemy->sprite.position = (vec2) { 0, 0 };
    enemy->sprite.size = (vec2) { 75, 75 };

    enemy->sprite.rotation = 0.0;
}
