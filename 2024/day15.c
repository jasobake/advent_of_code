#include <stdio.h>
#include <stdbool.h>
#include "data/day15.h"

#define GRID_WIDTH 50
#define GRID_HEIGHT 50

unsigned start[2] = { 24, 24 };

typedef struct Pos Pos;
struct Pos {
    unsigned x;
    unsigned y;
};

typedef enum Direction Direction;
enum Direction {
    UP, DOWN, LEFT, RIGHT,
};

void check_direction(Pos *pos, char direction) {

    unsigned *m = NULL;
    unsigned *m_clone = NULL;
    int max = 0;
    int dir = 0;
    Pos pos_clone = { pos->x, pos->y };

    switch (direction) {
        case '^':
            if (pos->y <= 0) return; 
            m = &(pos->y);
            m_clone = &(pos_clone.y);
            max = -1;
            dir = -1;
            pos_clone.y += dir;
            break;
        case 'v':
            if (pos->y >= GRID_HEIGHT - 1) return;
            m = &(pos->y);
            m_clone = &(pos_clone.y);
            max = GRID_HEIGHT;
            dir = 1;
            pos_clone.y += dir;
            break;
        case '<':
            if (pos->x <= 0) return;
            m = &(pos->x);
            m_clone = &(pos_clone.x);
            max = -1;
            dir = -1;
            pos_clone.x += dir;
            break;
        case '>':
            if (pos->x >= GRID_WIDTH - 1) return;
            m = &(pos->x);
            m_clone = &(pos_clone.x);
            max = GRID_WIDTH;
            dir = 1;
            pos_clone.x += dir;
            break;
        default:
            break;
    }

    //m_clone += dir;
    bool box_found = false;
    char *s = &(data[pos->y][pos->x]);
    while (*m_clone != max) {
        char *c = &(data[pos_clone.y][pos_clone.x]);
        if (*c == '.') {
            if (box_found) {
                *c = 'O';
            }
            *s = '.';
            *m += dir;
            return;
        } else if (*c == 'O') {
            box_found = true;
        } else if (*c == '#') {
            return;
        }
        *m_clone += dir;
    }

    return; 
}

void print(Pos *pos, size_t *result) {
    for (size_t row = 0; row < GRID_WIDTH; ++row) {
        for (size_t col = 0; col < GRID_HEIGHT; ++col) {
            char m = data[row][col];
            if (m == 'O') *result += (100 * row) + col;
            if (pos->x == col && pos->y == row) m = '@';
            printf("%c", m);
        }
        puts("");
    }
    puts("");
}

int main() {
    const char *move = moves;
    Pos pos = { start[0], start[1] };

    while (*move != '\0') {
        check_direction(&pos, *move);
        move++;
    }

    size_t result = 0;
    print(&pos, &result);

    printf("Result: %zu", result);
    return 0;
}