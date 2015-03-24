#include <stdio.h>
#include "snake.h"

/**
 * Create a snake and sets its length and position to the default in the screen coordinates.
 */
Snake* create_snake(const unsigned int width, const unsigned int height) {
	int i;	
	Snake* new_snake = malloc(sizeof(Snake));
	new_snake->length = DEFAULT_SIZE;
	new_snake->direction = LEFT;
	new_snake->position = calloc((width - 1) * (height - 1), sizeof(Coordinate *));
	for(i = 0; i < (width - 1) * (height - 1); i++) {
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
	printf("\n\n\t%s\n\n%s: %d\n\n", "SNAKE", "Score", screen->score);
	for(i = 0; i < screen->snake->length; i++) {
		x = screen->snake->position[i]->x;
		y = screen->snake->position[i]->y;
		screen->cells[x][y] = SNAKE;
	}
}

/**
 * Set a randomly cell of the screen with a food value to be displayed later
 */
void set_food_on_screen(Screen * const screen) {
	int i, j, contains_food = 0;
	for(i = 0; i < screen->height; i++) {
		for(j = 0; j < screen->width; j++) {
			if(screen->cells[i][j] == FOOD)
				contains_food++;
		}
	}

	if(!contains_food) {
		int random_x;
		int random_y;
		int valid_position = 0;
		srand(time(NULL));
		do {
			random_x = 1 + rand() % (screen->height - 3);
			random_y = 1 + rand() % (screen->width - 3);
			if(screen->cells[random_x][random_y] != SNAKE) {
				screen->cells[random_x][random_y] = FOOD;
				valid_position = 1;
			}
		} while(!valid_position);
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
	new_screen->score = 0;
	
	for(i = 0; i < height; i++) {
		new_screen->cells[i] = calloc(width, sizeof(int));
	}

	return new_screen;
}

/**
 * Set a screen with default attributes. Sets its boundaries as '#' characters, its empty spaces as ' ', its snake as a collection of '*' and its 
 * food as '$' based on ASCII.
 */
void set_screen(Screen * const screen) {
	int i, j;
	
	for(i = 0; i < screen->height; i++) {
		for(j = 0; j < screen->width; j++) {
			if(screen->cells[i][j] != FOOD) {
				if(i == 0 || j == 0 || i == (screen->height - 1) || j == (screen->width - 1))
					screen->cells[i][j] = BOUNDARY;
				else {
					screen->cells[i][j] = SPACE;
				}
			}
		}
	}

	set_snake_on_screen(screen);

	set_food_on_screen(screen);

	screen->score = (screen->snake->length - DEFAULT_SIZE) * 10;	
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

/**
 * Checks if a movement trying to be made is valid. Snake can't move backwards: it only keeps its direction or move to the left or right (in her 
 * sense of view)
 */
int validate_movement(Direction current_direction, Direction next_direction) {
	if(current_direction == UP)
		return next_direction != DOWN;
	else if(current_direction == RIGHT)
		return next_direction != LEFT;
	else if(current_direction == DOWN)
		return next_direction != UP;
	else if(current_direction == LEFT)
		return next_direction != RIGHT;
}

/**
 * This function moves the snake based on her direction. An input can change its direction.
 */
void move_snake(Screen * const screen, Direction next_direction) {
	if(validate_movement(screen->snake->direction, next_direction)) {
		int i, x, y, old_x, old_y;
		screen->snake->direction = next_direction;
		old_x = x = screen->snake->position[screen->snake->length - 1]->x; // last position's x coordinate
		old_y = y = screen->snake->position[screen->snake->length - 1]->y; // last position's y coordinate
		
		// set each cell of the snake to the next cell's position (except for the head)
		for(i = screen->snake->length - 1; i > 0; i--) {
			screen->snake->position[i]->x = screen->snake->position[i - 1]->x;
			screen->snake->position[i]->y = screen->snake->position[i - 1]->y;
		}

		// Actually moves snake based on its direction
		if(screen->snake->direction == UP) {
			screen->snake->position[i]->x -= 1;
		} else if(screen->snake->direction == DOWN) {
			screen->snake->position[i]->x += 1;
		}	else if(screen->snake->direction == RIGHT) {
			screen->snake->position[i]->y += 1;
		} else if(screen->snake->direction == LEFT) {
			screen->snake->position[i]->y -= 1;	
		}

		// Stores snake's head's position to check if it's in a food or wall later
		x = screen->snake->position[0]->x; // head's x coordinate
		y = screen->snake->position[0]->y; // head's y coordinate

		// Check if snake hitted itself and ends the game if so
		for(i = 3; i < screen->snake->length; i++) {
			if(x == screen->snake->position[i]->x && y == screen->snake->position[i]->y)
				GAME_STATUS = GAME_OVER;
		}

		
		//  Makes snake appear in the opposite side of the wall it entered.
		if(screen->cells[x][y] == BOUNDARY) {
			if(x == 0) {
				screen->snake->position[0]->x = screen->height - 2;
			} else if(x == screen->height - 1) {
				screen->snake->position[0]->x = 1;
			} else if(y == 0) {
				screen->snake->position[0]->y = screen->width - 2;
			} else if(y == screen->width - 1) {
				screen->snake->position[0]->y = 1;
			}
		}

		
		// Increases snake's size if it moved into a cell with food
		if(screen->cells[x][y] == FOOD) {
			screen->snake->position[screen->snake->length]->x = old_x;
			screen->snake->position[screen->snake->length]->y = old_y;
			(screen->snake->length)++;
			screen->cells[x][y] = SPACE;
		}
	}

}

