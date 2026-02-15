#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

typedef struct player_t {
    sprite_t sprite;
    vec2 velocity;
    float rvelocity; // rotational velocity
    vec2 input_vec;
} player_t;

player_t *player_create(SDL_Renderer *renderer);
void player_destroy(player_t *player);
void player_event(player_t *player, void *event);
void player_update(player_t *player, float deltatime);

#endif // PLAYER_H
