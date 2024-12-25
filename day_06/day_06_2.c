// Part 2
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int y;
    int x;
    char dir;
} OBSTRUCTIONS;

typedef struct {
    OBSTRUCTIONS *obs;
    int size;
    int index;
} array;

typedef struct {
    char ch;
    int y;
    int x;
    int start_y;
    int start_x;
} GUARD;

typedef struct {
    char *col;
} COLS;

typedef struct {
    COLS *row;
    int rows;
    int cols;
} LAB;

array *create_array(int size) {
    array *new_array = malloc(sizeof(array));
    if (new_array == NULL) {
        printf("Unable to allocate memory to array.\n");
        exit(1);
    }

    new_array->index = 0;
    new_array->size = size;

    new_array->obs = malloc(sizeof(OBSTRUCTIONS) * size);
    return new_array;
}

void destroy_array(array *array) {
    free(array->obs);
    free(array);
}

LAB *setup_lab(char *filename) {
    LAB *lab = malloc(sizeof(LAB));
    if (lab == NULL) {
        printf("Unable to allocate memory to lab.\n");
        exit(1);
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("FILE: %s not found.\n", filename);
        exit(1);
    }

    char ch;
    int cols = 0;
    while ((ch = fgetc(file)) != '\n') {
        cols++;
    }
    rewind(file);
    lab->cols = cols;

    int rows = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') rows++;
    }
    rewind(file);

    lab->rows = rows;
    lab->row = malloc(sizeof(COLS) * rows);
    if (lab->row == NULL) {
        printf("Unable to allocate memory to lab->row\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        lab->row[i].col = malloc(sizeof(char) * cols);
        if (lab->row[i].col == NULL) {
            printf("Unable to allocate memory to row[%d]\n", i);
            exit(1);
        }
    }

    int row_count = 0;
    int col_count = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lab->row[row_count].col[col_count] = '\0';
            col_count = 0;
            row_count++;
        }
        else {
            lab->row[row_count].col[col_count] = ch;
            col_count++;
        }
    }
    fclose(file);

    return lab;
}


void destroy_lab(LAB *lab) {
    for (int i = 0; i < lab->rows; i++) {
        free(lab->row[i].col);
    }
    free(lab->row);
    free(lab);
}

void reset_lab(LAB *lab, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("FILE: %s not found.\n", filename);
        exit(1);
    }

    int row_count = 0;
    int col_count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lab->row[row_count].col[col_count] = '\0';
            col_count = 0;
            row_count++;
        } else {
            lab->row[row_count].col[col_count] = ch;
            col_count++;
        }
    }
    fclose(file);
}

GUARD *setup_guard(LAB *lab) {
    GUARD *guard = malloc(sizeof(GUARD));
    if (guard == NULL) {
        printf("Unable to allocate memory for guard.\n");
        exit(1);
    }

    guard->ch = '^';

    int found = 0;
    for (int y = 0; y < lab->rows; y++) {
        for (int x = 0; x < lab->cols; x++) {
            if (lab->row[y].col[x] == guard->ch) {
                guard->start_y = y;
                guard->start_x = x;
                guard->y = y;
                guard->x = x;
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    return guard;
}

void kill_guard(GUARD *guard) {
    free(guard);
}

int check_repeat(array *array, int y, int x, char dir) {
    if (array->index == 0) return 0; 

    for (int i = 0; i < array->index; i++) {
        if (array->obs[i].y == y && array->obs[i].x == x && array->obs[i].dir == dir) {
            return 1;
        }
    }
    return 0;
}

void clear_array(array *array) {
    for (int i = 0; i < array->size; i++) {
        array->obs[i].x = 0;
        array->obs[i].y = 0;
        array->obs[i].dir = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing filename args.\n");
        exit(1);
    }

    char *filename = argv[1];
    LAB *lab = setup_lab(filename);
    GUARD *guard = setup_guard(lab);
    array *obstructions = create_array(500);
    clear_array(obstructions);

    int loops = 0;
    for (int y = 0; y < lab->rows; y++) {
        for (int x = 0; x < lab->cols; x++) {
            reset_lab(lab, filename);
            guard->y = guard->start_y;
            guard->x = guard->start_x;
            guard->ch = '^';
            obstructions->index = 0;
            clear_array(obstructions);

            if (lab->row[y].col[x] == '.') {
                lab->row[y].col[x] = '#';

                while (1) {
                    if (guard->y == 0 || guard->x == 0 || guard->y == lab->rows - 1 || guard->x == lab->cols - 1 ) break;   // Guard exits lab

                    if (guard->ch == '^') {
                        if (lab->row[guard->y - 1].col[guard->x] == '#') {
                            if (check_repeat(obstructions, guard->y, guard->x, guard->ch)){
                                loops++;
                                break;
                            } 
                            obstructions->obs[obstructions->index].y = guard->y;
                            obstructions->obs[obstructions->index].x = guard->x;
                            obstructions->obs[obstructions->index].dir = guard->ch; 
                            guard->ch = '>';
                            obstructions->index++;
                        } else {
                            guard->y--;
                        }
                    } 
                    else if (guard->ch == '>') {
                        if (lab->row[guard->y].col[guard->x + 1] == '#') {
                            if (check_repeat(obstructions, guard->y, guard->x, guard->ch)){
                                loops++;
                                break;
                            } 
                            obstructions->obs[obstructions->index].y = guard->y;
                            obstructions->obs[obstructions->index].x = guard->x;
                            obstructions->obs[obstructions->index].dir = guard->ch; 
                            guard->ch = 'v';
                            obstructions->index++;
                        } else {
                            guard->x++;
                        }
                    }
                    else if (guard->ch == 'v') {
                        if (lab->row[guard->y + 1].col[guard->x] == '#') {
                            if (check_repeat(obstructions, guard->y, guard->x, guard->ch)){
                                loops++;
                                break;
                            } 
                            obstructions->obs[obstructions->index].y = guard->y;
                            obstructions->obs[obstructions->index].x = guard->x;
                            obstructions->obs[obstructions->index].dir = guard->ch; 
                            guard->ch = '<';
                            obstructions->index++;
                        } else {
                            guard->y++;
                        }
                    }
                    else if (guard->ch == '<') {
                        if (lab->row[guard->y].col[guard->x - 1] == '#') {
                            if (check_repeat(obstructions, guard->y, guard->x, guard->ch)){
                                loops++;
                                break;
                            } 
                            obstructions->obs[obstructions->index].y = guard->y;
                            obstructions->obs[obstructions->index].x = guard->x;
                            obstructions->obs[obstructions->index].dir = guard->ch; 
                            guard->ch = '^';
                            obstructions->index++;
                        } else {
                            guard->x--;
                        }
                    }
                }
            }
        }
    }
    printf("Valid Obstructions: %d\n", loops);

    destroy_lab(lab);
    kill_guard(guard);
    destroy_array(obstructions);
}
