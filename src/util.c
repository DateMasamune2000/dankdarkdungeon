#include "util.h"

#include <curses.h>
#include <stdlib.h>

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

	int sector_size_rows = (24 / vertical_sectors);
	int sector_size_cols = (80 / horizontal_sectors);

	int max_room_rows = sector_size_rows - 2;
	int max_room_cols = sector_size_cols - 2;

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

			int max_start_row = sector_size_rows - room_rows - 2;
			int max_start_col = sector_size_cols - room_cols - 2;

			int start_row = 1 + (rand() % max_start_row);
			int start_col = 1 + (rand() % max_start_col);

#ifdef _DEBUG
			fprintf(stderr, "room size: %d rows x %d cols\n",
					room_rows, room_cols);
			fprintf(stderr, "room start: (r, c) = (%d, %d)\n",
					start_row, start_col);
#endif

			/* Draw the borders */
			int abs_row_start = sr*sector_size_rows + start_row - 1;
			int abs_col_start = sc*sector_size_cols + start_col - 1;
			for (int c = 0; c <= room_cols; c++) {
				l->data[abs_row_start][abs_col_start + c] = '#';
				l->data[abs_row_start + room_rows + 1][abs_col_start + c] = '#';
			}
			for (int r = 0; r <= room_rows; r++) {
				l->data[abs_row_start + r][abs_col_start] = '#';
				l->data[abs_row_start + r][abs_col_start + room_cols + 1] = '#';
			}

			/* Fill in the room */
			for (int r = 0; r < room_rows; r++) {
				int abs_row_pos = sr*sector_size_rows + start_row + r;

				for (int c = 0; c < room_cols; c++) {
					int abs_col_pos = sc*sector_size_cols + start_col + c;

					l->data[abs_row_pos][abs_col_pos] = '.';
				}
			}
		}
	}
}
