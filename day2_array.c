#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

bool check_safety(const int* d, const size_t arrsize) {
    bool rising = (d[0] < d[1]);

    for (size_t i = 1; i < arrsize; ++i) {
        if ((d[i-1] == d[i] || abs(d[i] - d[i-1]) > 3) || 
            (rising && d[i-1] > d[i]) ||
            (!rising && d[i-1] < d[i])) 
        {
            return false;
        }

    }

    return true;
}

int main() {
    size_t safe_count = 0;
    char line[50];
    
    FILE* file = fopen("data/advent_day2.txt", "r");

    while(fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " ");
        int holder[50];
        size_t counter = 0;
        while (token != NULL) {
            holder[counter] = atoi(token);
            token = strtok(NULL, " ");
            ++counter;
        }

        if (check_safety(holder, counter)) {
            ++safe_count;
        }
    }

    printf("safe: %zu", safe_count);
    return 0;
}