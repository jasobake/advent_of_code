#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "data/day9.h"

#define BUFF 1000000
#define DEBUG false

void print(uint16_t buffer[], size_t size) {
    if (!DEBUG) return;
    for (size_t i = 0; i < size; i++) {
        printf("%d", buffer[i]);
    }
    printf("\n");
}

int main() {
    uint16_t *buffer = (uint16_t *)calloc(BUFF, sizeof(uint16_t));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed");
        return 1;
    }

    // load pages
    size_t counter = 0, pagesize = 0, file_id = 0;
    uint16_t value = 0;
    for (size_t i = 0; data[i] != '\0'; i++) {
        pagesize = data[i] - '0';
        value = (i % 2 == 0) ? i / 2 : 0;
        for (size_t n = 0; n < pagesize; n++) {
            buffer[counter] = value;
            counter++;
        }
    }

    // defrag
    size_t temp = 0, left = data[0] - '0', right = counter;
    while (true) {
        while(buffer[left] != 0) left++;
        while(buffer[right] == 0) right--;

        if (left >= right) break;
        temp = buffer[left];
        buffer[left] = buffer[right];
        buffer[right] = temp;
    }

    // get the sum
    uint64_t result = 0;
    for (size_t i = 0; i < left; i++) {
        result += buffer[i] * i;
    }

    free(buffer);
    printf("result: %zu", result);
    return 0;
}