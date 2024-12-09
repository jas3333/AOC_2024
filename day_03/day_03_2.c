#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main() {

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Error opening file, make sure file exists.\n");
		exit(1);
	}

	fseek(file, 0L, SEEK_END);
	int filesize = ftell(file);
	rewind(file);

	char input[filesize + 1];
	fread(input, 1, filesize, file);
	fclose(file);

	int count = 0;
	int start;
	int end;

	int total = 0;
	int num1 = 0;
	int num2 = 0;

	bool is_enabled = true;

	char *temp_string = NULL;

	while (input[count] != '\0') {
		if (strncmp(&input[count], "do(", 3) == 0) {
			is_enabled = true;
			count += 3;
			while (input[count] != ')') count++;
		}
		else if (strncmp(&input[count], "don't(", 6) == 0) {
			is_enabled = false;
			count += 6;
			while (input[count] != ')') count++;
		}

		if (input[count] == 'm' && input[count + 1] == 'u' && input[count + 2] == 'l' && input[count +3] == '(' && is_enabled) {
			start = count + 4;
			end = start;

			while (input[end] != ')' && (end - start) < 9)  {
				end++;
			}

			if (isdigit(input[end - 1]) && (end - start) < 9) {
				temp_string = realloc(temp_string, (end - start + 1) * sizeof(char));
				if (temp_string == NULL) {
					printf("Unable to allocate memory.\n");
					exit(1);
				}

				for (int i = 0; i < (end - start); i++) {
					temp_string[i] = input[start + i];
				}
				temp_string[end - start] = '\0';

				sscanf(temp_string, "%d,%d", &num1, &num2);
				total += num1 * num2;

				free(temp_string);
				temp_string = NULL;
			}
		}
		count++;
	}

	printf("%d\n", total);
	return 0;
}
