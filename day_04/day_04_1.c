#include <stdio.h>
#include "lib/utils.h"

int horizontal_check(char *string, int length) {
	int count = 0;
	for (int i = 0; i < length - 3; i++) {
		if (string[i] == 'X' && string[i + 1] == 'M' && string[i + 2] == 'A' && string[i + 3] == 'S') {
			count++;
		}

	}
	return count;
}

int main() {
	int lines = line_count("input.txt");
	int line_length = get_line_length("input.txt") + 1;
	int total = 0;

	char input[lines][line_length];
	FILE *file = fopen("input.txt", "r");
	int count = 0;
	for (int i = 0; i < lines; i++) {
		if (fgets(input[i], lines, file) == NULL) {
			fprintf(stderr, "Error reading line %d\n", i);
			break;
		}
	}
	fclose(file);

	for (int i = 0; i < lines; i++) {
		total += horizontal_check(input[i], lines);
	}

	printf("%d\n", total);
}
