#include "sdl.h"

#define UNUSED(x) (void)(x)

int main(int argc, char **argv)
{
	int ww, wh;

	UNUSED(argc);
	UNUSED(argv);
	sdl_setup();
	sdl_get_window_size(&ww, &wh);
	while (1) {
		sdl_set_draw_color(0, 0, 0);
		sdl_clear_frame();
		sdl_present_frame();
	}
	return 0;
}
