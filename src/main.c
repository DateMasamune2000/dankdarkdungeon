#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>

#define _DEBUG

struct level {
	char data[24][80];
	bool seen[24][80];
};

void generate(struct level *l);
void display(const struct level *l);

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

void display(const struct level *l)
{
	for (int r = 0; r < 24; r++) {
		for (int c = 0; c < 80; c++) {
			mvaddch(r, c, l->data[r][c]);
		}
	}
}

void generate(struct level *l)
{
	for (int r = 0; r < 24; r++) {
		for (int c = 0; c < 80; c++) {
			l->data[r][c] = ' ';
			l->seen[r][c] = false;
		}
	}

	int vertical_sectors = (rand() % 4) + 1;
	int horizontal_sectors = (rand() % 4) + 1;

	int max_room_rows = 24 / vertical_sectors;
	int max_room_cols = 80 / horizontal_sectors;

#ifdef _DEBUG
	fprintf(stderr, "%d x %d sectors\n",
			vertical_sectors, horizontal_sectors);
	fprintf(stderr, "sector size: %d rows x %d cols\n",
			max_room_rows, max_room_cols);
#endif

	const int min_room_rows = 3, min_room_cols = 3;

	for (int sr = 0; sr < vertical_sectors; sr++) {
		for (int sc = 0; sc < horizontal_sectors; sc++) {
			int room_rows = min_room_rows
				+ (rand() % (max_room_rows - min_room_rows));
			int room_cols = min_room_cols
				+ (rand() % (max_room_cols - min_room_cols));

			int max_start_row = (24/vertical_sectors) - room_rows;
			int max_start_col = (80/horizontal_sectors) - room_cols;

			int start_row = rand() % max_start_row;
			int start_col = rand() % max_start_col;

#ifdef _DEBUG
			fprintf(stderr, "room size: %d rows x %d cols\n",
					room_rows, room_cols);
			fprintf(stderr, "room start: (r, c) = (%d, %d)\n",
					start_row, start_col);
#endif

			for (int r = 0; r < room_rows; r++) {
				for (int c = 0; c < room_cols; c++) {
					int abs_row_pos = sr*max_room_rows + start_row + r;
					int abs_col_pos = sc*max_room_cols + start_col + c;

					l->data[abs_row_pos][abs_col_pos] = '.';
				}
			}
		}
	}
}
