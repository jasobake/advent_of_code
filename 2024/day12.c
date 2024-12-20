#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "data/day12.h"

#define SIZE 140

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

typedef struct Region Region;
struct Region {
    size_t perimiter;
    size_t area;
    size_t faces;
};

typedef struct Fence Fence;
struct Fence {
    bool top;
    bool bottom;
    bool left;
    bool right;
};

bool checked[SIZE][SIZE] = { false };
Region region[1024] = { 0 };
     
bool check(size_t row, size_t col, char current_plot, size_t count, Fence fences[SIZE][SIZE]) {

    char plot = data[row][col];
    if (plot != current_plot) return false;

    if (checked[row][col]) {
        return false;
    }
    checked[row][col] = true;

    region[count].area++;

    if (row == 0 || data[row-1][col] != plot) {
        fences[row][col].top = true;
        region[count].perimiter++;
    }
    if (col == 0 || data[row][col-1] != plot) {
        fences[row][col].left = true;
        region[count].perimiter++;
    }
    if (row == SIZE - 1 || data[row+1][col] != plot) {
        fences[row][col].bottom = true;
        region[count].perimiter++;
    }   
    if (col == SIZE - 1 || data[row][col+1] != plot) {
        fences[row][col].right = true;
        region[count].perimiter++;
    } 

    size_t faces = 0;
    // if it's a corner, it's a face  _
    // check for corners             |
    if (fences[row][col].top && fences[row][col].left) faces++;
    if (fences[row][col].top && fences[row][col].right) faces++;
    if (fences[row][col].bottom && fences[row][col].left) faces++;
    if (fences[row][col].bottom && fences[row][col].right) faces++;

    // check for corners _|
    if (row > 0 && col > 0 && data[row-1][col-1] != plot && !fences[row][col].left && !fences[row][col].top) faces++;
    if (row > 0 && col < SIZE - 1 && data[row-1][col+1] != plot && !fences[row][col].right && !fences[row][col].top) faces++;
    if (row < SIZE - 1 && col > 0 && data[row+1][col-1] != plot && !fences[row][col].left && !fences[row][col].bottom) faces++;
    if (row < SIZE - 1 && col < SIZE - 1 && data[row+1][col+1] != plot && !fences[row][col].right && !fences[row][col].bottom) faces++;

    region[count].faces += faces;

    if (row > 0) check(row-1, col, plot, count, fences);
    if (row < SIZE - 1) check(row+1, col, plot, count, fences);
    if (col > 0) check(row, col-1, plot, count, fences);
    if (col < SIZE - 1) check(row, col+1, plot, count, fences);

    return true;
}

int main() {
    size_t count = 0;
    size_t result = 0;
    size_t result2 = 0;
    Fence fences[SIZE][SIZE] = { 0 };

    for (size_t row = 0; row < SIZE; row++) {
        for(size_t col = 0; col < SIZE; col++) {
            if (check(row, col, data[row][col], count, fences)) {
                result += (region[count].perimiter * region[count].area);
                result2 += (region[count].faces * region[count].area);
                count++;
            }
        }
    }

    printf("Part 1: %zu\nPart 2: %zu\n", result, result2);

    return 0;
}