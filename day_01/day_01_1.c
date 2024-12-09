#include <stdio.h>
#include <stdlib.h>

int count_lines(char *filename) {
	int count = 0;
	char ch;

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Unable to open file.\n");
		exit(1);
	}

	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			count++;
		}
	}

	fclose(file);

	return count;
}

void bsort(int *array, int size) {

	int swap = 1;

	while (swap) {
		swap = 0;

		for (int i = 0; i < size - 1; i++) {
			if (array[i] > array[i + 1]) {
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				swap = 1;
			}
		}
	}
}

int main() {

	int lines = count_lines("input.txt");
	int list_one[lines];
	int list_two[lines];
	int total_distance = 0;

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		fprintf(stderr, "File not found.\n");
		exit(1);
	}

	int count = 0;
	while (fscanf(file, "%d %d", &list_one[count], &list_two[count]) == 2) {
		count++;
	}

	bsort(list_one, lines);
	bsort(list_two, lines);

	for (int i = 0; i < lines; i++) {
		if (list_one[i] > list_two[i]) {
			total_distance += list_one[i] - list_two[i];
		} else {
			total_distance += list_two[i] - list_one[i];
		}
	}

	printf("%d\n", total_distance);

	return 0;
}
