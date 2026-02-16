#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

typedef struct player_t player_t;

typedef struct enemy_t {
    entity_t entity;
    
    int damage;
} enemy_t;

void enemy_init(enemy_t *enemy,
                      SDL_Renderer *renderer,
                      int health,
                      int damage);

#endif // ENEMY_H
