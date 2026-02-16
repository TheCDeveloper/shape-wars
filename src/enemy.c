#include "enemy.h"


void enemy_init(enemy_t *enemy,
                      SDL_Renderer *renderer,
                      int health,
                      int damage) {
    entity_init(&enemy->entity, health);
    enemy->entity.sprite.texture = util_load_texture(renderer, "res/enemy.png");
    enemy->damage = damage;
}
