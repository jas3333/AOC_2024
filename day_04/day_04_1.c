#include <stdio.h>
#include "lib/utils.h"

int check_horizontal(char *string, int size) {
	int total = 0;
	for (int i = 0; i < size - 3; i++) {
		if (string[i] == 'X' && string[i + 1] == 'M' && string[i + 2] == 'A' && string[i + 3] == 'S') {
			total++;
		}
	}
	return total;
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("Missing filename from args.\n");
		exit(1);
	} 

	char *filename = argv[1];

	int lines = line_count(filename);
	int line_length = get_line_length(filename);
	int total = 0;
	int count = 0;
	int line_count = 0;

	char buffer[lines][line_length + 1];
	FILE *file = fopen(filename, "r");

	char ch;
	while ((ch = fgetc(file)) != EOF) {
		// Kick the \n to the curb!
		if (ch == '\n') {
			buffer[line_count][count] = '\0';
			line_count++;
			count = 0;
		} else {
			buffer[line_count][count] = ch;
			count++;
		}
	}
	fclose(file);


	for (int i = 0; i < lines; i++) {
		for (int x = 0; x < line_length - 3; x++) {
			if (buffer[i][x] == 'X' && buffer[i][x + 1] == 'M' && buffer[i][x + 2] == 'A' && buffer[i][x + 3] == 'S') {
				total++;
			}
			if (buffer[i][x] == 'S' && buffer[i][x + 1] == 'A' && buffer[i][x + 2] == 'M' && buffer[i][x + 3] == 'X') {
				total++;
			}
		}
	}

	// Check vertical
	for (int i = 0; i < lines - 3; i++) {
		for (int x = 0; x < line_length; x++) {
			if (buffer[i][x] == 'X' && buffer[i + 1][x] == 'M' && buffer[i + 2][x] == 'A' && buffer[i + 3][x] == 'S') {
				total++;
			}
			if (buffer[i][x] == 'S' && buffer[i + 1][x] == 'A' && buffer[i + 2][x] == 'M' && buffer[i + 3][x] == 'X') {
				total++;
			}
		}
	}

	/*
		x
		 x
		  x
	*/
	for (int i = 0; i < lines - 3; i++) {
		for (int x = 0; x < line_length - 3; x++) {
			if (buffer[i][x] == 'X' && buffer[i + 1][x + 1] == 'M' && buffer[i + 2][x + 2] == 'A' && buffer[i + 3][x + 3] == 'S') {
				total++;
			} 
			if (buffer[i][x] == 'S' && buffer[i + 1][x + 1] == 'A' && buffer[i + 2][x + 2] == 'M' && buffer[i + 3][x + 3] == 'X') {
				total++;
			}
		}
	}

	/*
		 x
		x
	   x
	*/
	for (int i = 0; i < lines - 3; i++) {
		for (int x = 3; x - line_length;  x++) {
			if (buffer[i][x] == 'X' && buffer[i + 1][x - 1] == 'M' && buffer[i + 2][x - 2] == 'A' && buffer[i + 3][x - 3] == 'S') {
				total++;
			}
			if (buffer[i][x] == 'S' && buffer[i + 1][x - 1] == 'A' && buffer[i + 2][x - 2] == 'M' && buffer[i + 3][x - 3] == 'X') {
				total++;
			}
		}
	}

	printf("%d\n", total);
}
