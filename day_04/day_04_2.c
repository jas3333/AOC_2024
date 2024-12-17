#include <stdio.h>
#include <stdlib.h>
#include "lib/utils.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Missing filename arg.\n");
		exit(1);
	}
	char *filename = argv[1];

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File not found.\n");
		exit(1);
	}
}
