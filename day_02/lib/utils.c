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
	while (string[count] != '\n') {
		count++;
	}

	string[count] = '\0';
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

int line_count(const char *filename) {
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
