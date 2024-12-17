#include <stdio.h>
#include "lib/utils.h"

int main() {


	int lines = line_count("input.txt");
	int line_length = get_line_length("input.txt");
	int total = 0;

	char buffer[lines][line_length];

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("File not found.\n");
		exit(1);
	}

	char ch;
	int index = 0;
	int count = 0;
	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			buffer[count][index] = '\0';
			index = 0;;
			count++;
		} else {
			buffer[count][index] = ch;
			index++;
		}
	}
	for (int i = 0; i < lines - 1; i++) {
		for (int x = 0; x < line_length - 1; x++) {
			if (
				(buffer[i][x] == 'M' || buffer[i][x] == 'S') &&
				buffer[i + 1][x + 1] == 'A' &&
				(buffer[i + 2][x + 2] == 'S' || buffer[i + 2][x + 2] == 'M') &&
				(buffer[i][x + 2] == 'M' || buffer[i][x + 2] == 'S') &&
				(buffer[i + 2][x] == 'S' || buffer[i + 2][x] == 'M')
			)
			{
				total++;
			}
		}
	}
	printf("%d\n", total);
	
}
