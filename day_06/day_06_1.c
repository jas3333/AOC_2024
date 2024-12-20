#include "lib/utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing arg filename.\n");
        exit(1);
    }

    char *filename = argv[1];

    int rows = file_row_count(filename); 
    int cols = file_col_count(filename);
    char **lab = load_file_into_2d_array(filename);

    int guard_y = 0; // Rows
    int guard_x = 0; // Cols
    char guard = '^';

    // Find guard's initial position
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (lab[y][x] == '^') {
                guard_y = y;
                guard_x = x;
            }
        }
    }

    int steps = 0;
    while (1) {
        lab[guard_y][guard_x] = 'X';
        if (guard_y == 0 || guard_x == 0 || guard_x == cols - 1 || guard_y == rows - 1) break;

        if (guard == '^') {
            if (lab[guard_y - 1][guard_x] == '#') {
                guard = '>';
            } else {
                guard_y--;
            }
        }
        else if (guard == '>') {
            if (lab[guard_y][guard_x + 1] == '#') {
                guard = 'v';
            } else {
                guard_x++;
            }
        }
        else if (guard == 'v') {
            if (lab[guard_y + 1][guard_x] == '#') {
                guard = '<';
            } else {
                guard_y++;
            }
        }
        else if (guard == '<') {
            if (lab[guard_y][guard_x - 1] == '#') {
                guard = '^';
            } else {
                guard_x--;
            } 
        }

    }

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (lab[y][x] == 'X') {
                steps++;
            }
        }
    }

    printf("%d\n", steps);
}
