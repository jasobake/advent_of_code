#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "data/day11.h"

typedef struct Node Node;
struct Node{
    size_t value;
    Node* next;
};

Node *node_get(const size_t value) {
    Node *ret = malloc(sizeof(Node));

    if (ret == NULL) {
        perror("Error getting new node\n");
        return NULL;
    }

    ret->value = value;
    ret->next = NULL;

    return ret;
}

Node *node_append(Node *node, size_t value) {
    Node *ret = node_get(value);

    if (node != NULL) {
        node->next = ret;
    }
    
    return ret;
}

void free_list(Node *head) {
    Node *current = head;

    while(current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

bool is_even(uint64_t n) {
    return ((int)log10(n) + 1) % 2 == 0;
}

void split(uint64_t n, uint64_t *a, uint64_t *b) {
    int divisor = (int)pow(10, ((int)log10(n) + 1) / 2);

    *a = n / divisor;
    *b = n % divisor;
}

int main() {
    size_t arr_len = sizeof(data) / sizeof(data[0]);

    Node *head = NULL;
    Node *current = NULL;

    for (size_t i = 0; i < arr_len; i++) {
        current = node_append(current, data[i]);
        if (head == NULL) {
            head = current;
        }
    }

    size_t blinks = 75;
    uint64_t a, b;

    current = head;
    for (size_t i = 0; i < blinks; i++) {
        while(current) {
            //printf("%zu| ", current->value);
            if (current->value == 0) {
                current->value = 1;
            } else if (is_even(current->value)) {
                split(current->value, &a, &b);
                current->value = a;
                Node *n = node_get(b);
                n->next = current->next;
                current->next = n;
                current = n;
            } else {
                current->value *= 2024;
            }

            current = current->next;

        }
        current = head;
    }

    size_t result = 0;

    while(current) {
        result++;
        current = current->next;
    }

    printf("%zu", result);

    return 0;

}