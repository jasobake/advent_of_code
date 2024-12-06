#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 1000

int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {

    FILE * fp;

    fp = fopen("data/advent_day1.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[20];
    int list1[SIZE];
    int list2[SIZE];

    const char *delim = " ";
    size_t counter = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, delim);

        list1[counter] = atoi(token);
        token = strtok(NULL, delim);
        list2[counter] = atoi(token);
        ++counter;
        
    }

    fclose(fp);

    qsort(list1, SIZE, sizeof(int), comp);
    qsort(list2, SIZE, sizeof(int), comp);

    size_t result = 0;

    for (size_t i = 0; i < SIZE; ++i) {
        result += abs(list2[i] - list1[i]);
    }

    printf("Part 1 Result: %d\n", result);

    return 0;
}