#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUMBERS 50 // Maximum number of integers after the colon

uint64_t combine_uint64(uint64_t a, uint64_t b);
int parse_string(const char *input, size_t *first_num, size_t *numbers, size_t *count);

bool check(size_t *d, size_t current_value, size_t start, size_t target, size_t len) {
    if (current_value == target && start == len - 1) {
        return true;
    } else if (current_value > target || start >=  len - 1) {
        return false;
    }

    uint64_t next_value = d[start + 1];

    bool add = check(d, current_value + next_value, start + 1, target, len);
    if (add) return true;

    bool mul = check(d, current_value * next_value, start + 1, target, len);
    if (mul) return true;

    // part 2
    bool cat = check(d, combine_uint64(current_value, next_value), start + 1, target, len);
    if (cat) return true;
}

int main() {
    FILE *f = fopen("data/day7.txt", "r");

    char line[150];
    size_t target = 0;
    size_t count = 0;
    size_t result = 0;
    size_t numbers[50];

    while(fgets(line, sizeof(line), f)) {
        parse_string(line, &target, numbers, &count);
        if (check(numbers, numbers[0], 0, target, count)) {
            result += target;
        }

    }

    fclose(f);
    printf("%zu", result);
}

int parse_string(const char *input, size_t *first_num, size_t *numbers, size_t *count) {
    char *endptr;
    const char* str = input;

    *first_num = strtoull(str, &endptr, 10);

    str = endptr + 1;
    while (*str == ' ') {
        str++;
    }

    *count = 0;
    while (*str && *count < MAX_NUMBERS) {
        errno = 0;  // Reset errno for each number
        numbers[*count] = strtoull(str, &endptr, 10);

        if (endptr == str) {
            break;  // No more valid numbers
        }
        (*count)++;
        str = endptr;
        while (*str == ' ') {
            str++;
        }
    }

    return 1; // Successful parsing
}

uint64_t combine_uint64(uint64_t a, uint64_t b) {
    if (b == 0) return a * 10;  // Special case when b is 0

    uint64_t b_copy = b;
    uint64_t multiplier = 1;

    while (b_copy > 0) {
        b_copy /= 10;
        multiplier *= 10;
    }

    return a * multiplier + b;
}