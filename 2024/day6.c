#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 130

typedef enum Direction Direction;
enum Direction {
    UP, DOWN, LEFT, RIGHT,
};

void read_input(char dest[][130], int guard[2]) {
    char line[142];
    FILE *file = fopen("data/advent_day6.txt", "r");
    size_t row = 0;

    while(fgets(line, sizeof(line), file)) {
        for(size_t col = 0; col < SIZE; ++col) {
            dest[col][row] = line[col];
            if (line[col] == '^') {
                guard[0] = col;
                guard[1] = row;
            }
        }
        ++row;
    }

    fclose(file);
}

int main() {
    char d[SIZE][SIZE] = {0};
    bool r[SIZE][SIZE] = {false};
    int guard[2];
    Direction direction = UP;
    Direction new_direction = UP;
    
    read_input(d, guard);
    int guard_x = guard[0];
    int guard_y = guard[1];

    d[guard_x][guard_y] = 'V';

    size_t counter = 0;
    while(guard_x >= 0 && guard_y >= 0 && guard_x < SIZE && guard_y < SIZE) {
        switch (direction)
        {
        case UP:
            --guard_y;
            if (guard_y > 0 && d[guard_x][(guard_y-1)] == '#'){
                new_direction = RIGHT;
            } 
            break;
        case DOWN:
            ++guard_y;
            if (guard_y < SIZE && d[guard_x][(guard_y+1)] == '#'){
                new_direction = LEFT;
            }
            break;
        case LEFT:
            --guard_x;
            if (guard_x > 0 && d[guard_x-1][(guard_y)] == '#') {
                new_direction = UP;
            }
            break;
        case RIGHT:
            ++guard_x;
            if (guard_x < SIZE && d[guard_x+1][(guard_y)] == '#'){
                new_direction = DOWN;
            }
            break;
        default:
            break;
        }


        direction = new_direction;    
        r[guard_x][guard_y] = true;

        counter++;
    } 

    size_t result = 0;
    for (size_t row = 0; row < SIZE; ++row) {
        for (size_t col = 0; col < SIZE; ++col) {
            if (r[row][col]) ++result;
        }
    }

    printf("%zu\n", result);

    return 0;
}