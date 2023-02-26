#ifndef SDL_H
#define SDL_H

#include <stdint.h>

void sdl_setup(void);
void sdl_present_frame(void);
void sdl_clear_frame(void);
void sdl_set_draw_color(uint8_t r, uint8_t g, uint8_t b);
void sdl_get_window_size(int *w, int *h);
void sdl_fill_rect(int x, int y, int w, int h);

#endif
