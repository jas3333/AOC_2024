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
			token = strtok(NULL, "|");
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

bool is_update_in_order(int update[], int rules[][2], int u_size, int r_size) {
	for (int i = 0; i < r_size; i++) {
		int rule_one_index = -1;
		int rule_two_index = -1;

		for (int x = 0; x < u_size; x++) {
			if (rules[i][0] == update[x]) {
				rule_one_index = x;
			} 
			else if (rules[i][1] == update[x]) {
				rule_two_index = x;
			}
		}

		if (rule_one_index != -1 && rule_two_index != -1) {
			if (rule_one_index >= rule_two_index) {
				return false;
			}
		}
	}

	return true;
}


void fix_update(int update[], int rules[][2], int u_size, int r_size) {
	for (int i = 0; i < r_size; i++) {
		int rule_one_index = -1;
		int rule_two_index = -1;

		for (int x = 0; x < u_size; x++) {
			if (rules[i][0] == update[x]) {
				rule_one_index = x;
			} 
			else if (rules[i][1] == update[x]) {
				rule_two_index = x;
			}
		}
		if (rule_one_index != -1 && rule_two_index != -1) {
			if (rule_one_index >= rule_two_index) {
				int temp = update[rule_two_index];
				update[rule_two_index] = update[rule_one_index];
				update[rule_one_index] = temp;
				fix_update(update, rules, u_size, r_size);
			}
		}
	}

	return;
}

LAB *setup_lab(char *filename) {

    LAB *new_lab = malloc(sizeof(LAB));
    if (new_lab == NULL) {
        fprintf(stderr, "Failed to allocate memory for lab.\n");
        exit(1);
    }
    new_lab->guard.size = 20;
    new_lab->guard.index = 0;
	new_lab->obs_y = 0;
	new_lab->obs_x = 0;
	new_lab->guard.ch = '^';
    new_lab->guard.steps = malloc(sizeof(STEPS) * new_lab->guard.size);
    if (new_lab->guard.steps == NULL) {
        fprintf(stderr, "Failed to allocate memory for guard.\n");
        exit(1);
    }
    new_lab->guard.y = 0;
    new_lab->guard.x = 0;

    new_lab->rows = file_row_count(filename);   // Returns row count of file
    new_lab->cols = file_col_count(filename);   // Returns col count of file

    new_lab->layout = malloc(sizeof(LAB_FLOOR) * new_lab->rows);

    for (int i = 0; i < new_lab->rows; i++) {
        new_lab->layout[i].floor = malloc(sizeof(char) * new_lab->cols);
        if (new_lab->layout->floor == NULL) {
            printf("Unable to setup lab, there was a memory issue...\n");
            exit(1);
        }
    }

    return new_lab;
}

void populate_lab(LAB *lab, char *filename) {

	int rows = file_row_count(filename); 
	int cols = file_col_count(filename);

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Unable to find %s.\n", filename);
		exit(1);
	}
	char ch;
	int row_count = 0;
	int col_count = 0;
	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			lab->layout[row_count].floor[col_count] = '\0';
			row_count++;
			col_count = 0;
		} else {
			lab->layout[row_count].floor[col_count] = ch;
			col_count++;
		}
	}

	locate_guard(lab);
	fclose(file);
}


void locate_guard(LAB *lab) {
    int found = 0;
    for (int y = 0; y < lab->rows; y++) {
        for (int x = 0; x < lab->cols; x++) {
            if (lab->layout[y].floor[x] == lab->guard.ch) {
                lab->guard.y = y;
                lab->guard.x = x;
                found = 1;
                break;
            }
        }
        if (found) break;
    }
}

void cleanup_lab(LAB *lab) {
	for (int i = 0; i < lab->rows; i++) {
		free(lab->layout[i].floor);
	}
	free(lab->layout);
	free(lab->guard.steps);
	free(lab);
}
