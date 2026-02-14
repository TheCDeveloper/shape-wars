#include "game.h"

#include <stdio.h>


int main(int argc, char **argv) {
    game *instance = game_init();
    if (!instance) {
        fprintf(stderr, "Failed to initialize!\n");
        return 1;
    }

    game_run(instance);
    game_destroy(instance);
    return 0;
}
