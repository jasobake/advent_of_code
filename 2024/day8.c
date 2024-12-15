#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

char d[8][8] = {
        '89010123',
        '78121874',
        '87430965',
        '96549874',
        '45678903',
        '32019012',
        '01329801',
        '10456732',
    };

bool r[8][8] = { false };

bool check(size_t i, size_t n, char t) {
    //top
    if (i > 0 )
    //bottom

    //left

    //right
}

int main() {
    size_t c = 0;
    for (size_t i = 0; i < 8; i++)
        for (size_t n = 0; i < 8; n++) {
            if (d[i][n] == '0') {
                if (check(i, n, '1')) c++;
            }
        }
    return 0;
}