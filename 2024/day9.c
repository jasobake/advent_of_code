#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "data/day9.h" // char data[] = "31928309190908...."

#define DEBUG false

typedef struct Page Page;
struct Page {
    size_t size;
    size_t file[10];
};

typedef struct GetBack GetBack;
struct GetBack {
    size_t page;
    size_t index;
};

GetBack getback(GetBack start, Page *data) {
    size_t i = 0, n = 0;
    Page *active;
    active = &data[start.page];
    for(i = start.page; i >= 0; i--) {
        for (n = start.index; n >= 0; n--) {
            if (data[i].file[n] != 0) {
                GetBack t = {i, n};
                return t;
            }
        }
    }

    return start;
}

void printit(size_t max, Page *data) {
    if (!DEBUG) return;
    for(size_t i = 0; i < max; i++) {
        //printf("[f%zu,s%zu]", data[i].file, data[i].size);
        for (size_t n = 0; n < data[i].size; n++) {
            if (i % 2 != 0 && data[i].file[n] == 0) {
                printf(".|");
            } else {
                printf("%zu|", data[i].file[n]);
            }
        }
    }
    printf("\n");
    for(size_t i = 0; i < max; i++) {
        //printf("[f%zu,s%zu]", data[i].file, data[i].size);
        for (size_t n = 0; n < data[i].size; n++) {
            printf("%zu|", i);
        }
    }
    printf("\n------------------------------\n");
}

int main() {

    // get input length so we can allocate an array
    size_t d_len = strlen(data);
    uint8_t test = 0;
    size_t s = 0;
    size_t t = 0;
    Page *p = malloc(d_len * sizeof(Page));
    Page *p_head = p;

    // build list of Pages
    size_t page_counter = 0;
    for (size_t i = 0; i < d_len; i++) {
        s = data[i] - '0';
        if (i % 2 == 0) {
            t = page_counter++;
        } else {
            t = 0;
        }
        size_t n = 0;
        for (n = 0; n < s; n++) {
            p->file[n] = t;
        }
        p->file[n] = '\0';

        p->size = s;
        p++;
    }

    // defrag
    size_t left = 1;
    size_t right = d_len - 1;
    GetBack g;
    p = p_head;
    Page *active;

    size_t c = 0;
    g.page = right;
    g.index = p[right].size;

    printit(d_len, p);
    while (left < g.page) {
        // loop until left is a 0
        if (p[left].file[0] == 0) {
            active = &p[left];
            size_t ps;
            for (size_t i = 0; i < p[left].size; i++) {
                g = getback(g, p);
                p[left].file[i] = p[g.page].file[g.index];
                p[g.page].file[g.index] = 0;
                if (g.index == 0) {
                    g.page -= 2;
                    if (g.page <= left) {
                        break;
                    }
                    g.index = p[g.page].size;
                } else {
                    g.index--;
                }
            }

        }
        printit(d_len, p);
        left += 2;
        c += 2;
    }

    // sum up
    size_t counter = 0;
    size_t result = 0;
    for (size_t i = 0; i < d_len; i++) {
        if (p[i].file != 0) {
            for (size_t n = 0; n < p[i].size; n++) {
                result += counter * p[i].file[n];
                counter++;
            }
        }
    }

    printf("%zu", result);
    
    free(p_head);

    return 0;

}