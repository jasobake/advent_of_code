#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_DT Point
#define MAX_QUEUE 2

typedef struct Point Point;
struct Point {
    unsigned row, col;
};

typedef struct Queue Queue;
struct Queue {
    QUEUE_DT points[100];
    int left, right;
};

void queue_init(Queue *queue) {
    queue->left = queue->right = -1;
}

void queue_enqueue(Queue *queue, QUEUE_DT p) {
    if (queue->right == MAX_QUEUE - 1) {
        perror("Queue size maxed out");
        exit(EXIT_FAILURE);
    }
    if (queue->left == -1) queue->left = 0;
    queue->right++;
    queue->points[queue->right] = p;
}

QUEUE_DT queue_dequeue(Queue *queue) {
    if (queue->left == -1) {
        perror("Queue out of bounds");
        exit(EXIT_FAILURE);
    }
    QUEUE_DT p = queue->points[queue->left];
    if (queue->left == queue->right) {
        queue->left = queue->right = -1;
    } else {
        queue->left++;
    }
    return p;
}

bool queue_isempty(Queue *queue) {
    return (queue->left == -1);
}

int main() {
    Queue q;
    queue_init(&q);

    queue_enqueue(&q, (Point){1, 2});
    queue_enqueue(&q, (Point){2, 3});
    queue_enqueue(&q, (Point){3, 4});

    while(!queue_isempty(&q)) {
        QUEUE_DT c = queue_dequeue(&q);
        printf("%d, %d\n", c.row, c.col);
    }

    return 0;
}