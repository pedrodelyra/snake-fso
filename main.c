#include <stdio.h>
#include <time.h>
#include "snake.h"
#include "io.h"

int main(void) {
	GAME_STATUS = PLAYING;
	Screen* screen = create_screen(40, 20);
	char user_input;	
	while(GAME_STATUS != GAME_OVER) {
		set_screen(screen);
		display_screen(screen);
		//user_input = set_input(read_input());
		move_snake(screen, screen->snake->direction);
		wait_for(0.2);
	}
	printf("\n\n\nGAME OVER\n\n\n");
	return 0;
}
