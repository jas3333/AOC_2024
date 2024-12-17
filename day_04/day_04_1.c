#include "lib/utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("Must provide filename arg.\n");
		exit(1);
	}

	char *filename = argv[1];
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File not found.\n");
		exit(1);
	}

	// Place contents from file into buffer without the '\n' char.
	char ch;
	int row_count = 0;
	int col_count = 0;
	int rows = line_count(filename); 
	int cols = get_line_length(filename);
	char buffer[rows][cols + 1];
	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			buffer[row_count][col_count] = '\0';
			col_count = 0;
			row_count++;
		} else {
			buffer[row_count][col_count] = ch;
			col_count++;
		}

	}
	fclose(file);

	int directions[8][2] = {
		{0, 1},			// Right;
		{1, 0},			// Down;
		{0, -1},		// Left;
		{-1, 0},		// Up;
		{1, 1},			// Down-Right
		{-1, 1},		// Up-Right
		{1, -1},		// Down-Left
		{-1, -1},		// Up-Left
	};
	int total = 0;
	for (int i = 0; i < rows; i++) {
		for (int x = 0; x < cols; x++) {
			if (buffer[i][x] == 'X') {
				for (int d = 0; d < 8; d++) {
					if (word_check(buffer, i, x, rows, cols, directions[d][0], directions[d][1])) {
						total++;
					}
				}
			}
		}
	}
	printf("Total: %d\n", total);
}
