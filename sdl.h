#ifndef SDL_H
#define SDL_H

#include <stdint.h>

void sdl_setup(void);
void sdl_present_frame(void);
void sdl_clear_frame(void);
void sdl_set_draw_color(uint8_t r, uint8_t g, uint8_t b);

#endif
