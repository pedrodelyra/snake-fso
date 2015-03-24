#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "snake.h"
#include "io.h"

// function that will be executed as a thread to read user's input
void *read_user_data(void *screen) {
	GAME_STATUS = PLAYING;
	char user_input;	
	while(GAME_STATUS != GAME_OVER) {
		user_input = set_input(read_input());
		move_snake((Screen *) screen, user_input);
	}
	pthread_exit("Exit successfully");
}

int main(void) {
	GAME_STATUS = PLAYING;
	Screen * const screen = create_screen(30, 12);
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, read_user_data, screen);
	while(GAME_STATUS != GAME_OVER) {
		set_screen(screen);
		display_screen(screen);
		move_snake(screen, screen->snake->direction);
		wait_for(0.1);
		system("clear");
	}
	//free_resources(screen);
	printf("\n\n\n***** GAME OVER *****\n\n\n");
	printf("SCORE: %d POINTS\n\n\n", screen->score);	
	return 0;
}
