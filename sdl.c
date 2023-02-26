#include "sdl.h"
#include "log.h"

#include <SDL2/SDL.h>

#define SDL_INIT_FLAG (SDL_INIT_VIDEO | SDL_INIT_AUDIO)

static struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} sdl_ctx;

void sdl_setup()
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
	sdl_ctx.window = SDL_CreateWindow("Warcraft", 0, 0, 1024, 720, 0);
	if (!sdl_ctx.window) {
		LOG_ERROR("Failed to create SDL window. %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	sdl_ctx.renderer = SDL_CreateRenderer(sdl_ctx.window, -1, 0);
	if (!sdl_ctx.renderer) {
		LOG_ERROR("Failed to create SDL renderer. %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void sdl_present_frame()
{
	SDL_RenderPresent(sdl_ctx.renderer);
}

void sdl_clear_frame()
{
	SDL_RenderClear(sdl_ctx.renderer);
}

void sdl_set_draw_color(uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetRenderDrawColor(sdl_ctx.renderer, r, g, b, SDL_ALPHA_OPAQUE);
}
