#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char d[140][140] = {0};
    read_input(d);

    size_t result = 0;
    size_t result2 = 0;

    #define AMIN 3
    #define AMAX 136

    for (size_t i = 0; i < 140; ++i) {
        for(size_t n = 0; n < 140; ++n) {
            if (d[i][n] == 'X') {
                //horiz
                if (n <= AMAX && d[i][n+1] == 'M' && d[i][n+2] == 'A' && d[i][n+3] == 'S') ++result;
                if (n >= AMIN && d[i][n-1] == 'M' && d[i][n-2] == 'A' && d[i][n-3] == 'S') ++result;

                //vertical
                if (i <= AMAX && d[i+1][n] == 'M' && d[i+2][n] == 'A' && d[i+3][n] == 'S') ++result;
                if (i >= AMIN && d[i-1][n] == 'M' && d[i-2][n] == 'A' && d[i-3][n] == 'S') ++result;

                //diagonal
                if (i <= AMAX && n <= AMAX && d[i+1][n+1] == 'M' && d[i+2][n+2] == 'A' && d[i+3][n+3] == 'S') ++result;
                if (i <= AMAX && n >= AMIN && d[i+1][n-1] == 'M' && d[i+2][n-2] == 'A' && d[i+3][n-3] == 'S') ++result;
                if (i >= AMIN && n <= AMAX && d[i-1][n+1] == 'M' && d[i-2][n+2] == 'A' && d[i-3][n+3] == 'S') ++result;
                if (i >= AMIN && n >= AMIN && d[i-1][n-1] == 'M' && d[i-2][n-2] == 'A' && d[i-3][n-3] == 'S') ++result;

            } else if (d[i][n] == 'A') {  //part2
                if (i > 0 && i < 139 && n > 0 && n < 139) {
                    size_t isx = 0;
                    // M \ S || S \ M
                    if ((d[i-1][n-1] == 'M' && d[i+1][n+1] == 'S') || (d[i-1][n-1] == 'S' && d[i+1][n+1] == 'M')) isx++;
                    // M / S || S / M
                    if ((d[i-1][n+1] == 'M' && d[i+1][n-1] == 'S') || (d[i-1][n+1] == 'S' && d[i+1][n-1] == 'M')) isx++;

                    if (isx == 2) ++result2;
                }
            }
            
        }
    }

    printf("Part 1: %zu\nPart 2: %zu\n", result, result2);

    return 0;
}