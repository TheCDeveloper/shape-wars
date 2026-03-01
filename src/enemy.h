#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

typedef struct player_t player_t;

typedef struct enemy_t {
    entity_t entity;
    
    int damage;
} enemy_t;

#endif // ENEMY_H
