#include "snake.h"

int main(void) {
	Screen* screen = create_screen(40, 20);
	char option;	
	while(1) {
		set_screen(screen);
		display_screen(screen);
		option = getchar();
		getchar();
		move_snake(screen, option);
	}
	return 0;
}
