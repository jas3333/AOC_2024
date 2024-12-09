#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
		} else {
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


	int *numbers = NULL;
	int safe_reports = 0;


	char buffer[100];
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		int count = 0;

		bool increase = true;
		bool decrease = true;
		bool is_safe = true;

		char *token = strtok(buffer, " ");
		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			if (numbers == NULL) {
				printf("Unable to allocate memory.\n");
				exit(1);
			}

			numbers[count] = atoi(token);
			count++;
			token = strtok(NULL, " ");
		}


		for (int i = 0; i < count - 1; i++) {

			// Get an absolute value for the difference.
			int diff = abs(numbers[i] - numbers[i + 1]);
			if (diff < 1 || diff > 3) {
				is_safe = false;
				break;
			}

			// Check if numbers are increasing or decreasing.
			if (numbers[i] > numbers[i + 1]) {
				increase = false;
			} 
			else if (numbers[i] < numbers[i + 1]) {
				decrease = false;
			}
			else {
				is_safe = false;
				break;
			}
		}

		if (is_safe && (increase || decrease)) {
			safe_reports++;
		}

		free(numbers);
		numbers = NULL;
	}

	printf("Safe reports: %d\n", safe_reports);
}
