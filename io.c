#include "io.h"
#include <unistd.h>
#include <termios.h>


unsigned int set_input(char input) {
	int i;
	char directions[] = {'w', 's', 'd', 'a'};
	for(i = 0; i < 4 && input != directions[i]; i++);
	
	return i != 4 ? i : set_input(read_input());
}

int read_input(void) {
	char buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		perror ("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror ("tcsetattr ~ICANON");
	return buf;
}
