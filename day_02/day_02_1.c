#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Unable to open file.\n");
		exit(1);
	}

	char line[200];
	char *token;

	int *numbers = NULL;
	int count = 0;

	int safe_reports = 0;


	while (fgets(line, sizeof(line), file) != NULL) {
		token = strtok(line, " ");
		count = 0;

		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			if (numbers == NULL) {
				printf("Memory allocation failed.\n");
				exit(1);
			}

			numbers[count] = atoi(token);
			count++;
			token = strtok(NULL, " ");
		}

		bool is_safe = true;
		bool is_decreasing = true;
		bool is_increasing = true;

		for (int i = 0; i < count - 1; i++) {
			int diff = abs(numbers[i] - numbers[i + 1]);

			if (diff < 1 || diff > 3) {
				is_safe = false;
				break;
			}

			if (numbers[i] < numbers[i + 1]) {
				is_decreasing = false;
			} 
			else if (numbers[i] > numbers[i + 1]) {
				is_increasing = false;
			} 
			else {
				is_safe = false;
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
	printf("Safe reports: %d\n", safe_reports);

	return 0;
}
