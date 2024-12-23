#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "data/day13.h"

#define GRID_WIDTH 101
#define GRID_HEIGHT 103
#define SECONDS 100
#define ROWS 500

bool checkblock(int floor[][GRID_HEIGHT], int w, int h);

int main() {
    int x = 0, y = 0, velocity_x = 0, velocity_y = 0, new_x = 0, new_y = 0;
    size_t quadrant_1 = 0, quadrant_2 = 0, quadrant_3 = 0, quadrant_4 = 0, quadrant_height = 0, quadrant_width = 0;

    size_t part_1 = 0;
    size_t seconds = SECONDS;
    int floor[GRID_WIDTH][GRID_HEIGHT] = { 0 };

    quadrant_height = ((GRID_HEIGHT - 1) / 2);
    quadrant_width = ((GRID_WIDTH - 1) / 2);

    while(true) {
        quadrant_1 = 0; quadrant_2 = 0; quadrant_3 = 0; quadrant_4 = 0;
        for (size_t r = 0; r < ROWS; ++r) {
            x = data[r][0];
            y = data[r][1];
            velocity_x = data[r][2];
            velocity_y = data[r][3];
            new_x = (x + (velocity_x * (int)seconds)) % GRID_WIDTH;
            new_y = (y + (velocity_y * (int)seconds)) % GRID_HEIGHT;

            if (new_x < 0) new_x = GRID_WIDTH + new_x;
            if (new_y < 0) new_y = GRID_HEIGHT + new_y;

            floor[new_x][new_y]++;

            if (new_x < quadrant_width && new_y < quadrant_height) quadrant_1++;
            if (new_x < quadrant_width && new_y > quadrant_height) quadrant_2++;
            if (new_x > quadrant_width && new_y < quadrant_height) quadrant_3++;
            if (new_x > quadrant_width && new_y > quadrant_height) quadrant_4++;
        }

        if (seconds == SECONDS) part_1 = quadrant_1 * quadrant_2 * quadrant_3 * quadrant_4;      
        
        //part 2 - for each second, search the grid for 5x5 solid pattern
        size_t robots = 0;
        if (seconds > SECONDS && checkblock(floor, 5, 5)) {
            for (size_t row = 0; row < GRID_HEIGHT; ++row) {
                for (size_t col = 0; col < GRID_WIDTH; ++col) {
                    robots = floor[col][row];
                    if (robots == 0) {
                        printf(".");
                    } else {
                        printf("%zu", robots);
                    }
                }
                puts("");
            }

            printf("Part 1: %zu\nPart 2: %zu\n", part_1, seconds);
            return 0;
        }

        seconds++; 
        if (seconds % 1000 == 0) printf("Seconds: %zu\n", seconds);
        memset(floor, 0, sizeof(floor));
    }

    return 0;
}

bool checkblock(int floor[][GRID_HEIGHT], int w, int h) {
    bool found = true;
    for (size_t x = 0; x < GRID_WIDTH - w; ++x) {
        for (size_t y = 0; y < GRID_HEIGHT - h; ++y) {
            found = true;
            for (size_t rows = 0; rows < h; ++rows) {
                for (size_t cols = 0; cols < w; ++cols) {
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