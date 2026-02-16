#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>


void player_init(player_t *player, SDL_Renderer *renderer) {
    entity_init(&player->entity, 100);
    player->entity.sprite.texture = util_load_texture(renderer, "res/player.png");
    player->input_vec = (vec2) { 0, 0 };
}


void player_cleanup(player_t *player) {
    SDL_DestroyTexture(player->entity.sprite.texture);
}


void player_destroy(player_t *player) {
    if (!player) {
        return;
    }

    SDL_DestroyTexture(player->entity.sprite.texture);
    free(player);
}


static void handle_key_events(player_t *player, SDL_KeyboardEvent *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->scancode) {
            case SDL_SCANCODE_W:
                player->input_vec.y = 1;
                break;
            case SDL_SCANCODE_S:
                player->input_vec.y = -1;
                break;
            case SDL_SCANCODE_A:
                player->input_vec.x = -1;
                break;
            case SDL_SCANCODE_D:
                player->input_vec.x = 1;
                break;

            default:
                break;
        }
    } else if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                player->input_vec.y = 0;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                player->input_vec.x = 0;
                break;

            default:
                break;
        }
    }
}


void player_event(player_t *player, void *e) {
#ifndef NDEBUG
    if (!player || !e) {
        fprintf(stderr, "player_event, player.c: player or event is NULL\n");
        return;
    }
#endif

    SDL_Event *event = (SDL_Event *) e;
    switch (event->type) {
        case SDL_EVENT_KEY_UP:
        case SDL_EVENT_KEY_DOWN:
            handle_key_events(player, &event->key);
            break;

        default:
            break;
    }
}


void player_update(player_t *player, float deltatime) {
#ifndef NDEBUG
    if (!player) {
        fprintf(stderr, "player_update, player.c: player is NULL\n");
        return;
    }
#endif

    player->entity.velocity.x += cos(player->entity.sprite.rotation * (M_PI / 180.0f)) *
                         player->input_vec.y * 100.0f * deltatime;
    player->entity.velocity.y += sin(player->entity.sprite.rotation * (M_PI / 180.0f)) *
                         player->input_vec.y * 100.0f * deltatime;
    player->rvelocity += player->input_vec.x * 45.0f * deltatime;

    entity_update(&player->entity, deltatime);
    player->entity.sprite.rotation += player->rvelocity * deltatime;

    player->entity.velocity.x -= player->entity.velocity.x * 1.0f * deltatime;
    player->entity.velocity.y -= player->entity.velocity.y * 1.0f * deltatime;
    player->rvelocity -= player->rvelocity * 1.0f * deltatime;
}
