#include "utils.h"

uint32_t hash(char *key) {
	uint32_t hash = BASIS_32;
	int length = strlen(key);

	for (int i = 0; i < length; i++) {
		hash ^= key[i];
		hash *= PRIME_32;
	}

	return hash;
}

void strip_newline(char *string) {
	int count = 0;
	while (string[count] != '\0' && string[count] != '\n') {
		count++;
	}

	if (string[count] == '\n') {
		string[count] = '\0';
	}
}

void insert(MAP *map, char *key) {
	uint32_t index = hash(key) % map->size;
	// Check for empty slot, and duplicate key
	while (map->entries[index].key != NULL && strcmp(map->entries[index].key, key) != 0) {
		index = (index + 1) % map->size;
	}
	
	if (map->entries[index].key == NULL) {
		map->entries[index].key = strdup(key);
		map->entries[index].value = 1;
	} else {
		map->entries[index].value += 1;
	}
}

int get_value(MAP *map, char *key) {
	uint32_t index = hash(key) % map->size; 
	while (map->entries[index].key != NULL) {
		if (strcmp(map->entries[index].key, key) == 0) {
			return map->entries[index].value;
		}
		index = (index + 1) % map->size;
	}
	return 0;
}

int file_row_count(const char *filename) {
	int count = 0;
	char ch;

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Unable to find file.\n");
		exit(1);
	}

	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			count++;
		}
	}
	fclose(file);
	return count;
}

MAP init_map(int size) {
	MAP map = {0};
	map.size = size;
	map.entries = calloc(map.size, sizeof(ENTRIES));
	if (map.entries == NULL) {
		printf("Unable to allocate memory\n");
		exit(1);
	}

	return map;
}

void cleanup(MAP *map) {
	for (int i = 0; i < map->size; i++) {
		free(map->entries[i].key);
	}
	free(map->entries);
}

void fill_map(MAP *map, char *input_file) {
	char *token;
	char buffer[128];

	FILE *file = fopen(input_file, "r");
	if (file == NULL) {
		printf("Unable to find file.\n");
		exit(1);
	}

	while(fgets(buffer, 128, file) != NULL) {
		token = strtok(buffer, " ");
		token = strtok(NULL, " ");
		if (token != NULL) {
			strip_newline(token);
			insert(map, token);
		}
	}
	fclose(file);
}

void display_array(int *array, int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d]\n", array[i]);
		}
		else {
			printf("%d ", array[i]);
		}

	}
}

bool safe_check(int *array, int count) {
	bool is_decreasing = true;
	bool is_increasing = true;

	for (int i = 0; i < count - 1; i++) {
		if (array[i] < array[i + 1]) {
			is_decreasing = false;
		} 
		else if (array[i] > array[i + 1]){
			is_increasing = false;
		}
		else {
			return false;
		}

		int diff = abs(array[i] - array[i + 1]);
		if (diff < 1 || diff > 3) {
			return false;
		}
	}

	if (is_decreasing || is_increasing) return true;

	return false;
}

int get_filesize(char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File not found.\n");
		exit(1);
	}

	fseek(file, 0L, SEEK_END);
	int filesize = ftell(file);
	fclose(file);

	return filesize;
}

int file_col_count(char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File not found.\n");
		exit(1);
	}

	int count = 0;
	char ch;
	while ((ch = fgetc(file)) != '\n') count++; 
	fclose(file);

	return count;
}

int word_check(char grid[][141], int row_start, int col_start, int rows, int cols, int row_dir, int col_dir) {
	char *word = "XMAS";
	int row = row_start;
	int col = col_start;

	for (int i = 0; i < 4; i++) {
		if (row < 0 || row >= rows || col < 0 || col >= cols) {
			return 0;
		}

		if (grid[row][col] != word[i]) {
			return 0;
		}

		row += row_dir;
		col += col_dir;

	}

	return 1;
}

char **load_file_into_2d_array(char *filename) {
	int rows = file_row_count(filename); 
	int cols = file_col_count(filename);

	char **array = malloc(rows * sizeof(char *));
	if (array == NULL) {
		printf("Unable to allocate memory for rows\n");
		exit(1);
	}

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Unable to find %s.\n", filename);
		exit(1);
	}

	for (int i = 0; i < rows; i++) {
		array[i] = malloc((cols + 1) * sizeof(char));
		if (array[i] == NULL) {
			printf("Unable to allocate memory for row %d\n", i);
			exit(1);
		}
	}

	char ch;
	int row_count = 0;
	int col_count = 0;
	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			array[row_count][col_count] = '\0';
			row_count++;
			col_count = 0;
		} else {
			array[row_count][col_count] = ch;
			col_count++;
		}
	}
	fclose(file);

	return array;
}

void free_2d_array(char **array, int rows) {
	for (int i = 0; i < rows; i++) {
		free(array[i]);
	}
	free(array);
}

// Given an input file, will return the line number a blank line is found.
int find_blank_line_number(char *filename) {
	int count = 0;
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File: %s not found.\n", filename);
		exit(1);
	}

	char buffer[128];
	while (fgets(buffer, 128, file) != NULL) {
		if (strcmp(buffer, "\n") == 0) {
			return count;
		}
		count++;
	}
	fclose(file);
	// Not found
	return 0;
}


// Loads rules into provided 2D array from input file.
void load_rules(char *filename, int array[][2], int array_size) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File: %s not found.\n", filename);
		exit(1);
	}

	char buffer[128];
	for (int i = 0; i < array_size; i++) {
		int count = 0;
		fgets(buffer, 128, file);
		char *token;
		token = strtok(buffer, "|");
		while (token != NULL && count < 2) {
			array[i][count] = atoi(token);
			count++;
		}
	}
	fclose(file);
}
// Fast forward file to stop point. Use when need to process part of a file. 
void fast_forward(FILE *file, int stop, int buffer_size) {
	char buffer[buffer_size];

	for (int i = 0; i < stop + 1; i++) {
		if (fgets(buffer, sizeof(buffer), file) == NULL) {
			printf("Reached end of file.\n");
			return;
		}
	}
}
