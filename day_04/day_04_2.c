// Part 2
#include <stdio.h>
#include <stdlib.h>
#include "lib/utils.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Missing filename arg.\n");
		exit(1);
	}
	char *filename = argv[1];

	char **grid = load_file_into_2d_array(filename);
	int rows = file_row_count(filename);
	int cols = file_col_count(filename);

	int total = 0;
	for (int row = 1; row < rows - 1; row++) {
		for (int col = 1; col < cols - 1; col++) {
			if (grid[row][col] == 'A') {
				char ul = grid[row - 1][col - 1];	// Up-Left
				char ur = grid[row - 1][col + 1];	// Up-Right
				char dl = grid[row + 1][col - 1];	// Down-Left
				char dr = grid[row + 1][col + 1];	// Down-Right

				if (( (ul == 'M' && dr == 'S') || (ul == 'S' && dr == 'M') ) &&
					( (ur == 'M' && dl == 'S') || (ur == 'S' && dl == 'M') )) {
					total++;
				}
			}
		}
	}
	printf("Total: %d\n", total);

	free_2d_array(grid, rows);
}
