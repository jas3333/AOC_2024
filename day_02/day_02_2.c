#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lib/utils.h"

bool safe_after_removal(int *array, int count, int index) {
	int *new_numbers = malloc((count - 1) * sizeof(int));
	if (new_numbers == NULL) {
		printf("Unable to allocate memory for safe check.\n");
		exit(1);
	}

	int new_index = 0;
	for (int i = 0; i < count; i++) {
		if (i != index) {
			new_numbers[new_index] = array[i];
			new_index++;
		}
	}

	bool result = safe_check(new_numbers, count - 1);
	free(new_numbers);
	return result;
}

int main() {

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("File not found.\n");
		exit(1);
	}

	char buffer[128];
	int *numbers = NULL;
	int safe_reports = 0;
	int count;
	
	while(fgets(buffer, 128, file) != NULL) {
		count = 0;

		char *token = strtok(buffer, " ");
		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			if (numbers == NULL) {
				printf("Unable to allocate memory.\n");
				exit(1);
			}
			
			numbers[count] = atoi(token);
			token = strtok(NULL, " ");
			count++;
		}

		if (safe_check(numbers, count)) safe_reports++;
		else {
			for (int i = 0; i < count; i++) {
				if (safe_after_removal(numbers, count, i)) {
					safe_reports++;
					break;
				}
			}
		}
		free(numbers);
		numbers = NULL;
	}

	fclose(file);
	printf("Safe Reports: %d\n", safe_reports);
}
