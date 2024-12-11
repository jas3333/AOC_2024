#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

	char *token;
	char buffer[128];
	int *numbers = NULL;
	int count;


	int safe_reports = 0;

	FILE *file = fopen("input.txt", "r");
	while (fgets(buffer, 128, file) != NULL) {
		count = 0;

		int increasing = 1;
		int decreasing = 1;
		int is_safe = 1;

		token = strtok(buffer, " ");
		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			numbers[count] = atoi(token);
			token = strtok(NULL, " ");
			count++;
		}

		for (int i = 0; i < count - 1; i++) {
			if (numbers[i] < numbers[i + 1]) {
				decreasing = 0;
			}
			else if (numbers[i] > numbers[i + 1]) {
				increasing = 0;
			}
			else {
				is_safe = 0;
				break;
			}
			int diff = abs(numbers[i] - numbers[i + 1]);
			if (diff < 1 || diff > 3) {
				is_safe = 0;
				break;
			}
		}

		if (is_safe && (decreasing || increasing)) {
			safe_reports++;
		}

		numbers = NULL;
		free(numbers);
	}

	fclose(file);

	printf("Safe Reports: %d\n", safe_reports);
}
