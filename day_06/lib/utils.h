#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>
#include <stdbool.h>

#define PRIME_32 16777691
#define BASIS_32 2166136261

typedef struct {
	char *key;
	int value;
} ENTRIES;

typedef struct {
	ENTRIES *entries;
	int size;
} MAP;

MAP init_map(int size);
int get_value(MAP *map, char *key);

int file_row_count(const char *filename); 
int file_col_count(char *filename); 
int get_filesize(char *filename); 

uint32_t hash(char *key);

void strip_newline(char *string); 
void insert(MAP *map, char *key); 
void cleanup(MAP *map); 
void fill_map(MAP *map, char *input_file); 
void display_array(int *array, int size);

bool safe_check(int *array, int count);
int word_check(char grid[][141], int row_start, int col_start, int cols, int rows, int row_dir, int col_dir); 

char **load_file_into_2d_array(char *filename); 
void free_2d_array(char **array, int rows); 

int find_blank_line_number(char *filename);
void load_rules(char *filename, int array[][2], int array_size); 
void fast_forward(FILE *file, int stop, int buffer_size); 
bool is_update_in_order(int update[], int rules[][2], int u_size, int r_size);
void fix_update(int update[], int rules[][2], int u_size, int r_size); 

#endif
