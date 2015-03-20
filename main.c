#include "snake.h"

int main(void) {
	Screen* screen = create_screen(40, 20);
	set_screen(screen);
	display_screen(screen);
	return 0;
}
