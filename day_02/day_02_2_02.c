#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bsort(int *array, int size) {
	int swap = 1;
	while (swap) {
		swap = 0;
		for (int i = 0; i < size - 1; i++) {
			int temp = array[i];
			if (array[i] > array[i + 1]) {
				array[i] = array[i + 1];
				array[i + 1] = temp;
				swap = 1;

			}
		}
	}
}

void display_array(int *array, int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d]\n", array[i]);
		}
		else {
			printf("%d, ", array[i]);
		}
	}
}

int main() {

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Unable to open file.\n");
		exit(1);
	}

	char buffer[128];

	int *numbers = NULL;
	int safe_reports = 0;

	// Place line from file into buffer
	while (fgets(buffer, sizeof(buffer), file) != NULL) {

		// Take the line from the buffer and place the numbers from it into numbers array
		char *token = strtok(buffer, " ");
		int count = 0;

		int is_increasing = 1;
		int is_decreasing = 1;
		int is_safe = 1;


		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			numbers[count] = atoi(token);
			token = strtok(NULL, " ");
			count++;
		}

		for (int i = 0; i < count - 1; i++) {
			int diff = abs(numbers[i] - numbers[i + 1]);
			if (diff < 1 || diff > 3) {
				is_safe = 0;
				break;
			}

			// Check if numbers are increasing or decreasing
			if (numbers[i] > numbers[i + 1]) {
				is_increasing = 0;
			}
			else if (numbers[i] < numbers[i + 1]) {
				is_decreasing = 0;
			}
			else {
				is_safe = 0;
				break;
			}
		}

		if (is_safe && (is_increasing || is_decreasing)) {
			safe_reports++;
		}

		free(numbers);
		numbers = NULL;
	}

	fclose(file);
	printf("%d\n", safe_reports);

	return 0;
}
