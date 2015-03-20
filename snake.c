#include "snake.h"

/**
	* Create a snake and sets its length and position to the default in the screen coordinates.
	*/
Snake* create_snake(const unsigned int width, const unsigned int height) {
	int i;	
	Snake* new_snake = malloc(sizeof(Snake));
	new_snake->length = DEFAULT_WIDTH;
	new_snake->direction = LEFT;
	new_snake->position = calloc((width - 1) * (height - 1), sizeof(Coordinate *));
	for(i = 0; i < DEFAULT_WIDTH; i++) {
		new_snake->position[i] = malloc(sizeof(Coordinate));
		new_snake->position[i]->x = height / 2; 
		new_snake->position[i]->y = width / 2 + i;
	}
	return new_snake;
}

/**
	* Insert a snake on the screen based on the position of the snake.
	*/
void set_snake_on_screen(Screen * const screen) {
	int i, x, y;
	for(i = 0; i < screen->snake->length; i++) {
		x = screen->snake->position[i]->x;
		y = screen->snake->position[i]->y;		
		screen->cells[x][y] = SNAKE;
	}
}
/**
	* Create a screen based on the width and height sent as arguments. Also sets its snake field with the return of create_snake routine.
	*/
Screen* create_screen(const unsigned int width, const unsigned int height) {
	int i;	
	Screen* new_screen = malloc(sizeof(Screen));
	new_screen->width = width;
	new_screen->height = height;
	new_screen->cells = calloc(height, sizeof(int *));
	new_screen->snake = create_snake(width, height);
	
	for(i = 0; i < height; i++) {
		new_screen->cells[i] = calloc(width, sizeof(int));
	}

	return new_screen;
}

/**
	* Set a screen with default attributes. Sets its boundaries as '#' characters, its empty spaces as ' ', its snake as a collection of '*' and its food as '$' based on ASCII.
	*/
void set_screen(Screen * const screen) {
	int i, j;
	
	for(i = 0; i < screen->height; i++) {
		for(j = 0; j < screen->width; j++) {
			if(i == 0 || j == 0 || i == (screen->height - 1) || j == (screen->width - 1))
				screen->cells[i][j] = BOUNDARY;
			else {
				screen->cells[i][j] = SPACE;
			}
		}
	}

	set_snake_on_screen(screen);
}

void display_screen(const Screen * const screen) {
	int i, j;
	
	for(i = 0; i < screen->height; i++) {
		for(j = 0; j < screen->width; j++) {
			putchar(screen->cells[i][j]);
		}
		putchar('\n');
	}
}

