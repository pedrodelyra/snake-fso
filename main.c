#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "snake.h"
#include "io.h"

static Screen *screen;

// function that will be executed as a thread to read user's input
void *read_user_data(void *arg) {
	GAME_STATUS = PLAYING;	
	char user_input;	
	while(GAME_STATUS != GAME_OVER) {
		user_input = set_input(read_input());
		move_snake(screen, user_input);
	}

}

int main(void) {
	GAME_STATUS = PLAYING;
	screen = create_screen(30, 12);
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
	printf("SCORE: %d POINTS\n\n\n", screen->score);	
	return 0;
}
