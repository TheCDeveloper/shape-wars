#include "ui.h"
#include "level.h"

#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>


struct ui_t {
    level_t *level;

    TTF_TextEngine *engine;
    TTF_Font *font;

    TTF_Text *text;
};


ui_t *ui_init(level_t *level) {
    if (!level) {
        return NULL;
    }

    ui_t *ui = malloc(sizeof(ui_t));
    if (!ui) {
        return NULL;
    }

    ui->level = level;

    if (!TTF_Init()) {
        fprintf(stderr, "Failed to initialize TTF: %s\n", SDL_GetError());
        return NULL;
    }

    ui->engine = TTF_CreateRendererTextEngine(level->renderer);
    if (!ui->engine) {
        fprintf(stderr, "Failed to create engine: %s\n", SDL_GetError());
        return NULL;
    }

    ui->font = TTF_OpenFont("res/Geo-Regular.ttf", 48);
    if (!ui->font) {
        fprintf(stderr, "Failed to load font: %s\n", SDL_GetError());
        return NULL;
    }

    ui->text = TTF_CreateText(ui->engine, ui->font, "Hello", 0);

    return ui;
}


void ui_cleanup(ui_t *ui) {
    if (!ui) {
        return;
    }

    if (ui->font) {
        TTF_CloseFont(ui->font);
        ui->font = NULL;
    }

    if (ui->engine)  {
        TTF_DestroyRendererTextEngine(ui->engine);
        ui->engine = NULL;
    }

    if (TTF_WasInit()) {
        TTF_Quit();
    }

    free(ui);
}


void ui_update(ui_t *ui, const SDL_Event *event) {

}


void ui_render(ui_t *ui) {
    char str[64];
    snprintf(str, 63, "Wave: %d\n", ui->level->wave);
    TTF_SetTextString(ui->text, str, 0);

    TTF_DrawRendererText(ui->text, 10, 10);
}
