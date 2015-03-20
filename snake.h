#include <stdlib.h>

#define SPACE 32
#define FOOD 36
#define BOUNDARY 35
#define SNAKE 42
#define DEFAULT_WIDTH 5

enum {
	GAME_OVER, PLAYING
} GAME_STATUS;

typedef enum {
	UP, DOWN, RIGHT, LEFT
} Direction;

typedef struct {
	unsigned int x;
	unsigned int y;
} Coordinate;

typedef struct {
	unsigned int length;
	Direction direction;
	Coordinate **position;
} Snake;

typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int **cells;
	Snake *snake;
	int score;
} Screen;

Snake* create_snake(const unsigned int width, const unsigned int height);

void set_snake_on_screen(Screen * const screen);

Screen* create_screen(const unsigned int width, const unsigned int height);

void set_screen(Screen * const screen);

void display_screen(const Screen * const screen);

int validate_movement(Direction current_direction, Direction next_direction);

void move_snake(Screen * const screen, Direction direction);

