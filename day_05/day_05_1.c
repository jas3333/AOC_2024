#include "lib/utils.h"
#include <stdlib.h>
#include <stdio.h>


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
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		printf("%s", buffer);
	}
}
