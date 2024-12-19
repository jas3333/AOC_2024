// Part 1
#include "lib/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Missing filename arg.\n");
		exit(1);
	}
	char *filename = argv[1];

	int rule_size = find_blank_line_number(filename);
	int rules[rule_size][2];
	load_rules(filename, rules, rule_size);

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File: %s not found.\n", filename);
		exit(1);
	}
	char buffer[128];
	fast_forward(file, rule_size, 128);

	int total = 0;
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		int *numbers = NULL;
		int count = 0;
		char *token;
		token = strtok(buffer, ",");
		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			if (numbers == NULL) {
				printf("Unable to reallocate memory.\n");
				exit(1);
			}
			numbers[count] = atoi(token);
			token = strtok(NULL, ",");
			count++;
		}

		if (is_update_in_order(numbers, rules, count, rule_size)) {
			int middle_index = count / 2;
			int middle_page = (count % 2 == 0) ? numbers[middle_index - 1] : numbers[middle_index];
			total += middle_page;
		}
		free(numbers);
	}

	printf("Total: %d\n", total);
}
