// Day 1 - Part 1
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

int main() {

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Unable to open file.\n");
		exit(1);
	}

	char buffer[128];
	char ch;

	int total = 0;
	int num1 = 0;
	int num2 = 0;
	int lines = 0;
	int counter = 0;

	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			lines++;
		}
	}

	int left[lines];
	int right[lines];

	rewind(file);
	while (fgets(buffer, 128, file) != NULL) {
		sscanf(buffer, "%d %d", &num1, &num2);
		left[counter] = num1;
		right[counter] = num2;
		counter++;
	}

	qsort(left, lines, sizeof(int), compare);
	qsort(right, lines, sizeof(int), compare);

	for (int i = 0; i < lines; i++) {
		total += abs(left[i] - right[i]);
	}

	printf("%d\n", total);

	return 0;
}
