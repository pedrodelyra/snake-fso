#include <stdlib.h>

#define SPACE 32
#define FOOD 36
#define BOUNDARY 35
#define SNAKE 42
#define DEFAULT_WIDTH 4

typedef struct {
	unsigned int x;
	unsigned int y;
} Coordinate;

typedef struct {
	unsigned int length;
	Coordinate **position;
} Snake;

typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int **cells;
	Snake *snake;
} Screen;

Snake* create_snake(const unsigned int width, const unsigned int height) {
	int i;	
	Snake* new_snake = malloc(sizeof(Snake));
	new_snake->length = DEFAULT_WIDTH;
	new_snake->position = calloc((width - 1) * (height - 1), sizeof(Coordinate *));
	for(i = 0; i < DEFAULT_WIDTH; i++) {
		(new_snake->position)[i] = malloc(sizeof(Coordinate));
		(new_snake->position)[i]->x = height / 2; 
		(new_snake->position)[i]->y = width / 2 + i;
	}
	return new_snake;
}

Screen* create_screen(const unsigned int width, const unsigned int height) {
	int i;	
	Screen* new_screen = malloc(sizeof(Screen));
	new_screen->width = width;
	new_screen->height = height;
	new_screen->cells = calloc(height, sizeof(int *));
	new_screen->snake = malloc(sizeof(Snake));
	
	for(i = 0; i < height; i++) {
		(new_screen->cells)[i] = calloc(width, sizeof(int));
	}
	return new_screen;
}

void set_screen(Screen* screen) {
	int i, j;
	
	for(i = 0; i < screen->height; i++) {
		for(j = 0; j < screen->width; j++) {
			if(i == 0 || j == 0 || i == (screen->height - 1) || j == (screen->height - 1))
				
		}
	}
}


void main() {
	Screen* my_screen = create_screen(20, 20);
	//set_screen(my_screen);
	//display_screen(my_screen);
}
