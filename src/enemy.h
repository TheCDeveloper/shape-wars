#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

typedef struct player_t player_t;

typedef struct enemy_t {
    sprite_t sprite;
    
    struct {
        int value;
        int max;
    } health;

    int damage;
    bool alive;
} enemy_t;

void enemy_initialize(enemy_t *enemy,
                      SDL_Renderer *renderer,
                      int health,
                      int damage);

#endif // ENEMY_H
