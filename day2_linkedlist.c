#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

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

bool check_safety(Node *head, bool allow_one_skip) {

    if (head == NULL || head->next == NULL) {
        return false;
    }

    bool skipped_one = !allow_one_skip;

    Node *current = head;

    if (!skipped_one && current->value == current->next->value) {
        current = current->next;
        skipped_one = true;
    }

    bool rising = (current->value < current->next->value);

    while(current->next != NULL) {
        size_t next_value = current->next->value;
        size_t current_value = current->value;
        if ((current_value == next_value || abs(next_value - current_value) > 3) ||
            (rising && current_value > next_value) ||
            (!rising && current_value < next_value)) 
        {
            if (skipped_one) {
                return false;
            }
            skipped_one = true;
        }

        current = current->next;
        
    }

    return true;
}

int main() {
    size_t safe_count_part1 = 0;
    size_t safe_count_part2 = 0;

    char line[50];
    FILE* file = fopen("data/advent_day2.txt", "r");

    if (file == NULL) {
        perror("Error opening file\n");
        return -1;
    }

    size_t counter = 0;

    while(fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " ");
        Node *head = NULL;
        Node *current = NULL;
        while (token != NULL) {
            current = node_append(current, atoi(token));
            if (head == NULL) {
                head = current;
            }
            token = strtok(NULL, " ");
        }
        ++counter;
        if (check_safety(head, false)) {
            ++safe_count_part1;
        } else if (check_safety(head, true)) {
            ++safe_count_part2;
        }
        

        free_list(head);
    }

    printf("safe part1: %zu\n", safe_count_part1);
    printf("safe part2: %zu\n", safe_count_part1 + safe_count_part2);

    return 0;
}