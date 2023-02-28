#include "sdl.h"
#include "log.h"

#include <SDL2/SDL.h>

#define SDL_INIT_FLAG (SDL_INIT_VIDEO | SDL_INIT_AUDIO)
#define SDL_DISPLAY_INDEX 0

static struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} sdl_ctx;

static struct {
	SDL_DisplayMode *modes;
	int num_modes;
} display;

#ifndef DEBUG_MODE
static void get_display_modes(void)
{
	display.num_modes = SDL_GetNumDisplayModes(SDL_DISPLAY_INDEX);
	/* TODO: Read modes from all screens connected. */
	if (!display.num_modes) {
		LOG_ERROR("Failed to read display modes. %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	display.modes = malloc(sizeof(SDL_DisplayMode)
		* (size_t) display.num_modes);
	for (int i = 0; i < display.num_modes; ++i) {
		SDL_GetDisplayMode(SDL_DISPLAY_INDEX, i, &display.modes[i]);
	}
}
#endif

void sdl_setup(void)
{
	if ((SDL_WasInit(SDL_INIT_FLAG) & SDL_INIT_FLAG)
			|| (sdl_ctx.window && sdl_ctx.renderer)) {
		LOG_DEBUG("Attempted to setup SDL contexts again.");
		return;
	}
	if (SDL_Init(SDL_INIT_FLAG) != 0) {
		LOG_ERROR("Failed to initialize SDL. %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
#if DEBUG_MODE
	sdl_ctx.window = SDL_CreateWindow("Warcraft", 0, 0, 1024, 768, 0);
	if (!sdl_ctx.window) {
		LOG_ERROR("Failed to create SDL window. %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
#else
	/* TODO: Tidy this code up, store current display mode in variable. */
	get_display_modes();
	sdl_ctx.window = SDL_CreateWindow("Warcraft: Orcs & Humans", 0, 0,
		display.modes[display.num_modes - 1].w,
		display.modes[display.num_modes - 1].h,
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_GRABBED);
	if (!sdl_ctx.window) {
		LOG_ERROR("Failed to create SDL window. %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
#endif
	sdl_ctx.renderer = SDL_CreateRenderer(sdl_ctx.window, -1, 0);
	if (!sdl_ctx.renderer) {
		LOG_ERROR("Failed to create SDL renderer. %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void sdl_shutdown(void)
{
	free(display.modes);
	SDL_DestroyRenderer(sdl_ctx.renderer);
	SDL_DestroyWindow(sdl_ctx.window);
	SDL_Quit();
}

void sdl_poll_events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			sdl_shutdown();
			exit(EXIT_SUCCESS);
		}
	}
}

void sdl_present_frame(void)
{
	SDL_RenderPresent(sdl_ctx.renderer);
}

void sdl_clear_frame(void)
{
	SDL_RenderClear(sdl_ctx.renderer);
}

void sdl_set_draw_color(uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetRenderDrawColor(sdl_ctx.renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void sdl_fill_rect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };

	SDL_RenderFillRect(sdl_ctx.renderer, &rect);
}

void sdl_get_window_size(int *w, int *h)
{
	SDL_GetWindowSize(sdl_ctx.window, w, h);
}
