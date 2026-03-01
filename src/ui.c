#include "ui.h"
#include "level.h"

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>


struct ui_t {
    SDL_Renderer *renderer;
    TTF_TextEngine *engine;
    TTF_Font *font;

    level_t *level;

    struct {
        TTF_Text *text;
    } game;
};


void ui_init(ui_t *ui, level_t *level) {
    ui->renderer = level->renderer;

    if (!TTF_Init()) {
        ui->engine = NULL;
        ui->font = NULL;
        return;
    }

    ui->engine = TTF_CreateRendererTextEngine(ui->renderer);
    ui->font = TTF_OpenFont("res/Geo-Regular.ttf", 48);

    ui->level = level;

    ui->game.text = TTF_CreateText(ui->engine, ui->font, "Score: ", 0);
}


void ui_cleanup(ui_t *ui) {
    TTF_DestroyText(ui->game.text);

    TTF_CloseFont(ui->font);
    TTF_DestroyRendererTextEngine(ui->engine);

    TTF_Quit();
}


void ui_render(ui_t *ui) {
    char str[64];

    snprintf(str, 63, "Wave: %d\n", ui->level->wave);
    TTF_SetTextString(ui->game.text, str, 0);
    TTF_DrawRendererText(ui->game.text, 10, 10);
}
