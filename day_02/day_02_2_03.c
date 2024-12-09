#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

	while (fgets(buffer, sizeof(buffer), file) != NULL) {

		char *token = strtok(buffer, " ");
		int count = 0;

		int is_decreasing = true;
		int is_increasing = true;
		int is_safe = true;

		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			numbers[count] = atoi(token);
			token = strtok(NULL, " ");
			count++;
		}

		for (int i = 0; i < count - 1; i++) {

			int diff = abs(numbers[i] - numbers[i + 1]);
			if (diff < 1 || diff > 3) {
				is_safe = false;
				break;
			}

			// Check if numbers are increasing or decreasing
			if (numbers[i] > numbers[i + 1]) {
				is_increasing = false;
			}
			else if (numbers[i] < numbers[i + 1]) {
				is_decreasing = false;
			}
			else {
				is_safe = false;
				break;
			}
		}

		if (is_safe && (is_decreasing || is_increasing)) {
			safe_reports++;
		}

		free(numbers);
		numbers = NULL;
	}

	printf("%d\n", safe_reports);

	return 0;
}
