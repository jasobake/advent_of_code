#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "data/day13.h"

#define GRID_WIDTH 101
#define GRID_HEIGHT 103
#define SECONDS 100
#define ROWS 500

bool checkblock(int floor[][GRID_HEIGHT], int w, int h);

int main() {
    int x = 0, y = 0, vx = 0, vy = 0, r1 = 0, r2 = 0, q1 = 0, q2 = 0, q3 = 0, q4 = 0, h_s = 0, w_s = 0;

    size_t sec = 0;

    while(true) {
        int floor[GRID_WIDTH][GRID_HEIGHT] = { 0 };
        q1 = 0; q2 = 0; q3 = 0; q4 = 0;
        for (size_t r = 0; r < ROWS; ++r) {
            x = data[r][0];
            y = data[r][1];
            vx = data[r][2];
            vy = data[r][3];
            r1 = (x + (vx * (int)sec)) % GRID_WIDTH;
            r2 = (y + (vy * (int)sec)) % GRID_HEIGHT;

            if (r1 < 0) r1 = GRID_WIDTH + r1;
            if (r2 < 0) r2 = GRID_HEIGHT + r2;

            floor[r1][r2]++;

            h_s = ((GRID_HEIGHT - 1) / 2);
            w_s = ((GRID_WIDTH - 1) / 2);

            if (r1 < w_s && r2 < h_s) q1++;
            if (r1 < w_s && r2 > h_s) q2++;
            if (r1 > w_s && r2 < h_s) q3++;
            if (r1 > w_s && r2 > h_s) q4++;
        }

        if (sec == SECONDS) {
            printf("Part 1: %d", (q1 * q2 * q3 * q4));
            getchar();         
        }

        //part 2 - for each second, search the grid for 5x5 solid pattern
        if (checkblock(floor, 5, 5)) {
            size_t c = 0;
            for (size_t row = 0; row < GRID_HEIGHT; row++) {
                for (size_t col = 0; col < GRID_WIDTH; col++) {
                    int v = floor[col][row];
                    if (v == 0) {
                        printf(".");
                    } else {
                        printf("%d", v);
                        c++;
                    }
                }
                puts("");
            }
        
            printf("Seconds: %d\n", sec);
            getchar();
        }

        sec++; 
        if (sec % 1000 == 0) printf("Seconds: %d\n", sec);
    }

    return 0;
}

bool checkblock(int floor[][GRID_HEIGHT], int w, int h) {
    bool found = true;
    for (size_t x = 0; x < GRID_WIDTH - w; x++) {
        for (size_t y = 0; y < GRID_HEIGHT - h; y++) {
            found = true;
            for (size_t rows = 0; rows < h; ++rows) {
                for (size_t cols = 0; cols < w; cols++) {
                    if (floor[x+rows][y+cols] == 0) {
                        found = false;
                        break;
                    }
                }
            }
            if (found) return true;
        }
    }
    return false; 
}