#include <stdio.h>
#include <stdbool.h>

#define MAX 16
// ANSI color codes
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

const char data[MAX][MAX] = {
"###############",
"#.......#....E#",
"#.#.###.#.###.#",
"#.....#.#...#.#",
"#.###.#####.#.#",
"#.#.#.......#.#",
"#.#.#####.###.#",
"#...........#.#",
"###.#.#####.#.#",
"#...#.....#.#.#",
"#.#.#.###.#.#.#",
"#.....#...#.#.#",
"#.###.#.#.#.#.#",
"#S..#.....#...#",
"###############",
};

typedef struct Position Position;
struct Position {
    unsigned row;
    unsigned col;
    bool is_end;
};
#define POS_COMP(a, b) (a.row == b.row && a.col == b.col)

//Position r[100] = { 0 };
bool checked[MAX][MAX] = { false };
bool solution[MAX][MAX] = { false };

const Position start = { .col = 1, .row = 13 };
char v;

void print(Position position) {
    for (size_t row = 0; row < MAX; row++) {
        for (size_t col = 0; col < MAX; col++) {
            v = checked[row][col] ? 'X' : data[row][col];
            if (position.col == col && position.row == row) {
                v = '0';
            }
            printf("%c", v);
        }
        puts("");
    }
    puts("");
}

void print_solution() {
    for (size_t row = 0; row < MAX; row++) {
        for (size_t col = 0; col < MAX; col++) {
            if (solution[row][col]) {
                printf(GREEN "X" RESET);
            } else if (checked[row][col]) {
                printf(RED "X" RESET);
            } else {
                
                printf("%c", data[row][col]);
            }
        }
        puts("");
    }
    puts("");
}

size_t check(Position position, Position previous, Position path[], size_t count) {
    size_t ret = 0;
    if (data[position.row][position.col] == '#') return false;
    if (checked[position.row][position.col]) return false;
    checked[position.row][position.col] = true;
    path[count] = position;
    //print(position);
    if (data[position.row][position.col] == 'E') {
        path[count].is_end = true;
        return count + 1;
    }

    Position new_position = { .row = position.row, .col = position.col };
    int row_inc, col_inc;
    size_t new_count = count + 1;

    if (position.row > 0) {
        new_position.row = position.row - 1;
        new_position.col = position.col;
        if (!POS_COMP(previous, new_position) && check(new_position, position, path, new_count)) return true;
    }
    if (position.row < MAX) {
        new_position.row = position.row + 1;
        new_position.col = position.col;
        if (!POS_COMP(previous, new_position) && check(new_position, position, path, new_count)) return true;
    }
    if (position.col > 0) {
        new_position.row = position.row;
        new_position.col = position.col - 1;
        if (!POS_COMP(previous, new_position) && check(new_position, position, path, new_count)) return true;
    }
    if (position.col < MAX) {
        new_position.row = position.row;
        new_position.col = position.col + 1;
        if (!POS_COMP(previous, new_position) && check(new_position, position, path, new_count)) return true;
    }

    return false;
}

int main() {
    Position a = { .col = 1, .row = 1 };
    Position b = { .col = 12, .row = 1 };  
    Position path[MAX * MAX] = { 0 };
    Position *p = &path[0];
    bool c = check(start, start, path, 0);
    while (p->is_end == false) {
        solution[p->row][p->col] = true;
        p++;
    }
    print_solution();
    printf("%d\n", c);
    puts("end");
}
