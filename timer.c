#include <time.h>
#include "timer.h"

void wait_for(double seconds) {
	clock_t begin;

	begin = clock();
	
	while((double) (clock() - begin) / CLOCKS_PER_SEC < seconds);
}
