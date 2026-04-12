#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

int main(int argc, char *argv[])
{
	if (argc == 2) {
		srand(atoi(argv[1]));
	}

	initscr();
	cbreak();
	noecho();

	struct level lv_zero;
	generate(&lv_zero);
	display(&lv_zero);

	getch();
	endwin();

	return 0;
}

