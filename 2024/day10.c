#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "data/day10.h"

#define SIZE 41

bool checked[SIZE][SIZE] = { false };

size_t check(size_t i, size_t n, char t, size_t p) {
    if (checked[i][n]) return 0;
    checked[i][n] = true;

    size_t total = p;
    char new_target = t + 1;
    if (new_target == '9' + 1) {
        return 1;
    }
    //top
    if (i > 0 && data[i-1][n] == new_target) {
        total += (check(i-1, n, new_target, p));
    }
    //bottom
    if (i < (SIZE - 1) && data[i+1][n] == new_target) {
        total += (check(i+1, n, new_target, p));
    }
    //left
    if (n > 0 && data[i][n-1] == new_target) {
        total += (check(i, n-1, new_target, p));
    }
    //right
    if (n < (SIZE - 1) && data[i][n+1] == new_target) {
        total += (check(i, n+1, new_target, p));
    }

    return total;
}

int main() {
    size_t c = 0;
    for (size_t i = 0; i < SIZE; i++)
        for (size_t n = 0; n < SIZE; n++) {
            if (data[i][n] == '0') {
                size_t score = check(i, n, '0', 0);
                c += score;
                memset(checked, 0, sizeof(checked));
            }
        }
    
    printf("%zu", c);
    return 0;
}