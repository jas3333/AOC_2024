// Part 2
#include "lib/utils.h"
#include <stdio.h>
#include <stdlib.h>

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
	fast_forward(file, rule_size, 128);

	char buffer[128];
	int total = 0;
	int fixed = 0;
	while (fgets(buffer, 128, file) != NULL) {
		int *numbers = NULL;
		int count = 0;

		char *token;
		token = strtok(buffer, ",");
		while (token != NULL) {
			numbers = realloc(numbers, (count + 1) * sizeof(int));
			if (numbers == NULL) {
				printf("Unable to reallocate to numbers.\n");
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
		} else {
			fix_update(numbers, rules, count, rule_size);
			int middle_index = count / 2;
			int middle_page = (count % 2 == 0) ? numbers[middle_index - 1] : numbers[middle_index];
			fixed += middle_page;
		}
		free(numbers);
	}

	printf("Total: %d\n", fixed);
}
