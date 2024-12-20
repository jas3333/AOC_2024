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

    int rows = file_row_count(filename);
    int cols = file_col_count(filename);
    char **lab = load_file_into_2d_array(filename);

    // Find guards start position
    int guard_y = 0;        // Rows
    int guard_x = 0;        // Cols
    int found = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (lab[y][x] == '^') {
                guard_y = y;
                guard_x = x;
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    char guard = '^';
    int steps = 0;
    while (1) {
        lab[guard_y][guard_x] = 'X';
        if (guard_y == 0 || guard_x == 0 || guard_y == rows - 1 || guard_x == cols - 1) break;
        switch (guard) {
            case '^': lab[guard_y - 1][guard_x] == '#' ? guard = '>' : guard_y--; break;
            case '>': lab[guard_y][guard_x + 1] == '#' ? guard = 'v': guard_x++; break;
            case 'v': lab[guard_y + 1][guard_x] == '#' ? guard = '<': guard_y++; break;
            case '<': lab[guard_y][guard_x - 1] == '#' ? guard = '^':guard_x--; break;
        }
    }

    for (int y = 0; y < rows; y++) {
        for (int x  = 0; x < cols; x++) {
            if (lab[y][x] == 'X') steps++;
        }
    }

    printf("Steps: %d\n", steps);
    free_2d_array(lab, rows);
}
