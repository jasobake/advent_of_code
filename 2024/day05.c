#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node{
    size_t value;
    Node* next;
};

Node rules[100] = {{0, NULL}};

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
    Node *head = node;
    Node *current = head;
    if (current != NULL) {
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = ret;
        //ret->next = node;
        //node = ret;
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

int comp2(const void *a, const void *b) {
    //return (*(int *)a - *(int *)b);
    bool check1 = false, check2 = false;
    Node *rule_a, *rule_b;
    const int aa = *(const int*)a;
    const int bb = *(const int*)b;

    rule_a = &rules[aa];
    rule_b = &rules[bb];

    if (rule_a->value > 0) {
        while(rule_a != NULL) {
            if (rule_a->value == bb) {
                check1 = true;
            }
            rule_a = rule_a->next;
        }
    } 
    
    if (rule_b->value > 0) {
        while(rule_b != NULL) {
            if (rule_b->value == aa) {
                check2 = true;
            }
            rule_b = rule_b->next;
        }
    }

    if (check1) {
        return -1;
    } else if (check2) {
        return 1;
    } else {
        return 0;
    }

}


int main() {

    FILE *file = fopen("data/advent_day5.txt", "r");

    char line[2024];
    
    int a, b;

    while(fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "|");
        if (token != NULL) {
            a = atoi(token);
            token = strtok(NULL, "|");
            if (token != NULL) {
                b = atoi(token);
            }
            //printf("%d %d\n", a, b);
        }
        
        if (a == 17) {
            //puts("debug");
        }

        Node *t = &rules[a];

        if (t->value == 0) {
            t->value = b;
        } else {
            node_append(t, b);
        }

    }

    fclose(file);
    Node *r = NULL;
    bool proceed = true;
    size_t result = 0;
    size_t result2 = 0;

    file = fopen("data/advent_day5b.txt", "r");
    size_t lc = 1;
    while(fgets(line, sizeof(line), file)) {
        //printf("line: %s\n", line);
        if (lc == 21) {
            //puts("break");
        }
        char *token = strtok(line, ",");
        bool hit[1000] = {false};
        size_t counter = 0;
        size_t mid[100] = {0};
        proceed = true;
        while (token != NULL) {
            a = atoi(token);
            //check rules
            r = &rules[a];
            //proceed = true;
            size_t n = 0;
            //printf("\tchecking %i for rules\n", a);
            while(r != NULL) {
                n = r->value;
                //printf("\t\tchecking %zu is a hit?\n", n);
                if (n && hit[n] == true) {
                    //printf("\t\t\tfailed %d %zu\n", n);
                    proceed = false;
                    break;
                }


                r = r->next;
            }
            mid[counter] = a;
            counter++;
            hit[a] = true;
            //if (!proceed) break;
            token = strtok(NULL, ",");
        }
        size_t g = counter / 2;
        if (proceed) {
            //printf("%zu passed rules\n", lc);
            //size_t g = counter / 2;
            result += mid[g];
            //printf("rules passed\n");
        } else {
            qsort(mid, counter, sizeof(size_t), comp2);
            result2 += mid[g];
        }
        lc++;
    }

    printf("Result: %zu\n", result);
    printf("Result2: %zu\n", result2);

    fclose(file);

    return 0;
}