#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "snake.h"
#include "io.h"

Screen* screen;

void *read_user_data(void *arg) {
	GAME_STATUS = PLAYING;	
	char user_input;	
	while(GAME_STATUS != GAME_OVER) {
		set_screen(screen);
		display_screen(screen);
		user_input = set_input(read_input());
		move_snake(screen, user_input);
		system("clear");
	}

}

int main(void) {
	GAME_STATUS = PLAYING;
	screen = create_screen(40, 20);
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &read_user_data, NULL);
	while(GAME_STATUS != GAME_OVER) {
		set_screen(screen);
		display_screen(screen);
		move_snake(screen, screen->snake->direction);
		wait_for(0.1);
		system("clear");
	}
	printf("\n\n\n***** GAME OVER *****\n\n\n");
	printf("SCORE: %d POINTS\n", screen->score);	
	return 0;
}
