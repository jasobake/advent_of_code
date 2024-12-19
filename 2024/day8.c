#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
//#include "data/day8.h"
#define SIZE 12
#define MAX_NODE 256

char data[SIZE][SIZE] = {
    "............",
    "........0...",
    ".....0......",
    ".......0....",
    "....0.......",
    "......A.....",
    "............",
    "............",
    "........A...",
    ".........A..",
    "............",
    "............",
}; 

bool checked[SIZE][SIZE] = { false };

typedef struct Node Node;
struct Node {
    size_t row;
    size_t col;
};

typedef struct Antenna Antenna;
struct Antenna {
    size_t count;
    Node nodes[30];
};

int check_bounds(int r1, int c1, int r2, int c2) {
    size_t result = 0;

    int row_diff, col_diff;

    row_diff = abs(r1 - r2);
    col_diff = abs(c1 - c2);

    int new_r1, new_c1, new_r2, new_c2;

    if (r1 < r2) {
        new_r1 = r1 - row_diff;
        new_r2 = r2 + row_diff;
    } else {
        new_r1 = r1 + row_diff;
        new_r2 = r2 - row_diff;
    }


    if (c1 < c2) {
        new_c1 = c1 - col_diff;
        new_c2 = c2 + col_diff;
    } else {
        new_c1 = c1 + col_diff;
        new_c2 = c2 - col_diff;
    }

    if (new_r1 >=0 && new_r1 < SIZE && new_c1 >=0 && new_c1 < SIZE && !checked[new_r1][new_c1]) {
        checked[new_r1][new_c1] = true;
        //printf("result: [%d,%d]\n", new_r1+1, new_c1+1);
        result++;
    }

    if (new_r2 >=0 && new_r2 < SIZE && new_c2 >=0 && new_c2 < SIZE && !checked[new_r2][new_c2]) {
        checked[new_r2][new_c2] = true;
        //printf("result: [%d,%d]\n", new_r2+1, new_c2+1);
        result++;
    }

    return result;
}

int check(int row, int col, int row2, int col2) {
    int ret = 2;

    if (row >= 0 && col >= 0 && row < SIZE && col < SIZE) {
        if (checked[row][col] == true) {
            ret--;
        } else {
            printf("an: %d,%d\n", row+1, col+1);
        }
        checked[row][col] = true;
    } else {
        ret--;
    }

    if (row2 >= 0 && col2 >= 0 && row2 < SIZE && col2 < SIZE) {
        if (checked[row2][col2] == true) {
            ret--;
        } else {
            printf("an: %d,%d\n", row2+1, col2+1);
        }
        checked[row2][col2] = true;
    } else {
        ret--;
    }
    
    return ret;
}

int check_bounds2(int r1, int c1, int r2, int c2) {
    size_t result = 0;

    int row_diff, col_diff;

    row_diff = abs(r1 - r2);
    col_diff = abs(c1 - c2);

    int new_r1 = r1, new_c1 = c1, new_r2 = r2, new_c2 = c2;

    while (
        (new_r1 >= 0 && new_r1 < SIZE) || (new_c1 >=0 && new_c1 < SIZE) ||
        (new_r2 >= 0 && new_r2 < SIZE) || (new_c2 >=0 && new_c2 < SIZE)
        ) 
    {
        if (new_r1 > new_r2) {
            new_r1 = new_r1 + row_diff;
            new_r2 = new_r2 - row_diff;
        } else {
            new_r1 = new_r1 - row_diff;
            new_r2 = new_r2 + row_diff;
        }

        if (new_c1 > new_c2) {
            new_c1 = new_c1 + col_diff;
            new_c2 = new_c2 - col_diff;
        } else {
            new_c1 = new_c1 - col_diff;
            new_c2 = new_c2 + col_diff;
        }

        result += check(new_r1, new_c1, new_r2, new_c2);

    }

    return result;
}

int main() {

    Antenna t[MAX_NODE] = { 0 };
    size_t result = 0;

    for (size_t row = 0; row < SIZE; row++) {
        for (size_t col = 0; col < SIZE; col++) {
            size_t index = data[row][col];

            if (isalnum(data[row][col])) {
                size_t v = data[row][col];
                
                Antenna *n = &t[v];
                printf("found: %c \n", v);
                for (size_t j = 0; j < n->count; j++) {
                    printf("rule %zu \n", j);
                    result += check_bounds2(row, col, n->nodes[j].row, n->nodes[j].col);
                }
                //puts("");
                n->nodes[n->count].col = col;
                n->nodes[n->count].row = row;

                n->count++;

            }

        }
    }
    printf("%d\n", result);
    return 0;
    
}