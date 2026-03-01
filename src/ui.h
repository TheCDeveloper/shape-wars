#ifndef UI_H
#define UI_H

#include <stdbool.h>

typedef struct SDL_Renderer SDL_Renderer;
typedef union SDL_Event SDL_Event;

typedef struct level_t level_t;

typedef struct ui_t ui_t;

ui_t *ui_init(level_t *level);
void ui_cleanup(ui_t *ui);
void ui_update(ui_t *ui, const SDL_Event *event);
void ui_render(ui_t *ui);

#endif // UI_H
