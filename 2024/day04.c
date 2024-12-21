#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void read_input(char dest[][140]) {
    char line[142];
    FILE *file = fopen("data/advent_day4.txt", "r");
    size_t row = 0;

    while(fgets(line, sizeof(line), file)) {
        for(size_t col = 0; col < 140; ++col) {
            dest[row][col] = line[col];
        }
        ++row;
    }

    fclose(file);
}

int main() {
    char puzzle[140][140] = {0};
    read_input(puzzle);

    size_t result = 0;
    size_t result2 = 0;

    #define MIN 3
    #define MAX 136

    for (size_t i = 0; i < 140; ++i) {
        for(size_t n = 0; n < 140; ++n) {
            if (puzzle[i][n] == 'X') {
                //horiz
                if (n <= MAX && puzzle[i][n+1] == 'M' && puzzle[i][n+2] == 'A' && puzzle[i][n+3] == 'S') result++;
                if (n >= MIN && puzzle[i][n-1] == 'M' && puzzle[i][n-2] == 'A' && puzzle[i][n-3] == 'S') result++;

                //vertical
                if (i <= MAX && puzzle[i+1][n] == 'M' && puzzle[i+2][n] == 'A' && puzzle[i+3][n] == 'S') result++;
                if (i >= MIN && puzzle[i-1][n] == 'M' && puzzle[i-2][n] == 'A' && puzzle[i-3][n] == 'S') result++;

                //diagonal
                if (i <= MAX && n <= MAX && puzzle[i+1][n+1] == 'M' && puzzle[i+2][n+2] == 'A' && puzzle[i+3][n+3] == 'S') result++;
                if (i <= MAX && n >= MIN && puzzle[i+1][n-1] == 'M' && puzzle[i+2][n-2] == 'A' && puzzle[i+3][n-3] == 'S') result++;
                if (i >= MIN && n <= MAX && puzzle[i-1][n+1] == 'M' && puzzle[i-2][n+2] == 'A' && puzzle[i-3][n+3] == 'S') result++;
                if (i >= MIN && n >= MIN && puzzle[i-1][n-1] == 'M' && puzzle[i-2][n-2] == 'A' && puzzle[i-3][n-3] == 'S') result++;

            } else if (puzzle[i][n] == 'A') {  //part2
                if (i > 0 && i < 139 && n > 0 && n < 139) {
                    uint8_t is_x = 0;
                    // M \ S || S \ M
                    if ((puzzle[i-1][n-1] == 'M' && puzzle[i+1][n+1] == 'S') || (puzzle[i-1][n-1] == 'S' && puzzle[i+1][n+1] == 'M')) is_x++;
                    // M / S || S / M
                    if ((puzzle[i-1][n+1] == 'M' && puzzle[i+1][n-1] == 'S') || (puzzle[i-1][n+1] == 'S' && puzzle[i+1][n-1] == 'M')) is_x++;

                    if (is_x == 2) result2++;
                }
            }
        }
    }

    printf("Part 1: %zu\n", result);
    printf("Part 2: %zu\n", result2);

    return 0;
}