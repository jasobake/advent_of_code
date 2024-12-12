#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "data/day3.h"

int main() {
  char digits_left[4];
  char digits_right[4];
  bool proceed = true; // tracks if the algorithm should keep going
  bool enabled = true; // tracks if we're in do() or don't()
  size_t i;
  size_t result = 0;
  size_t result2 = 0;
  size_t target_end = 0;
  size_t counter = 0;

  while (*data != '\0') {
    if (strncmp("do()", data, 4) == 0) {
        enabled = true;
    } else if (strncmp("don't()", data, 7) == 0) {
        enabled = false;
    }

    proceed = true;

    if (proceed && (strncmp("mul(", data, 4) != 0)) {
        proceed = false;
    }

    for (i = 4; i < 7; ++i) {
        if (!isdigit(data[i])) {
            if (data[i] != ',') {
            proceed = false;
            }
            digits_left[i-4] = '\0';
            break;
        } else {
            digits_left[i-4] = data[i];
        }
    }

    target_end = ++i + 4;
    counter = 0;
    for (; i < target_end; ++i) {
        if (!isdigit(data[i])) {
            if (data[i] != ')') {
            proceed = false;
            }
            digits_right[counter++] = '\0';
            break;
        } else {
            digits_right[counter++] = data[i];
        }
    }

    if (proceed) {
        size_t n = atoi(digits_left) * atoi(digits_right);
        result += n;
        if (enabled) {
            result2 += n;
        }
    }
    
    data++;
  }

  printf("Part 1: %zu\n", result);
  printf("Part 2: %zu\n", result2);
  return 0;
}