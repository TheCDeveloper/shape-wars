#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

typedef struct player_t {
    entity_t entity;

    float rvelocity; // rotational velocity
    vec2 input_vec;
} player_t;

void player_init(player_t *player, SDL_Renderer *renderer);
void player_cleanup(player_t *player);
void player_event(player_t *player, void *event);
void player_update(player_t *player, float deltatime);

#endif // PLAYER_H
