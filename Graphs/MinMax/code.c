#include <stdio.h>
#include <limits.h>

#define SIZE 10

struct queue {
    int front;
    int rear;
    int a[SIZE];
};

void initQueue(struct queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct queue *q) {
    return q->front == -1;
}

int isFull(struct queue *q) {
    return q->rear == SIZE - 1;
}

void enQueue(struct queue *q, int d) {
    if (isFull(q)) {
        printf("Queue is FULL\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = q->rear + 1;
    }
    q->a[q->rear] = d;
}

int deQueue(struct queue *q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }
    int d = q->a[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = q->front + 1;
    }
    return d;
}

void BFS(int a[7][7], int visited[7], int start) {
    struct queue q;
    initQueue(&q);

    int min_weight = INT_MAX;
    int max_weight = INT_MIN;
    int min_node = -1;
    int max_node = -1;

    enQueue(&q, start);
    visited[start] = 1;

    while (!isEmpty(&q)) {
        int node = deQueue(&q);
        for (int j = 0; j < 7; j++) {
            if (a[node][j] != 0 && !visited[j]) {
                visited[j] = 1;
                enQueue(&q, j);
                // Check weights to find min and max weighted edges
                if (a[node][j] < min_weight) {
                    min_weight = a[node][j];
                    min_node = j;
                }
                if (a[node][j] > max_weight) {
                    max_weight = a[node][j];
                    max_node = j;
                }
            }
        }
    }

    printf("\nMinimum weight edge ends at node: %d with weight %d\n", min_node, min_weight);
    printf("Maximum weight edge ends at node: %d with weight %d\n", max_node, max_weight);
}

int main() {
    // BFS Implementation with Weighted Graph
    int visited[7] = {0, 0, 0, 0, 0, 0, 0};
    int a[7][7] = {
        {0, 2, 3, 1, 0, 0, 0},
        {2, 0, 2, 0, 0, 0, 0},
        {3, 2, 0, 4, 5, 0, 0},
        {1, 0, 4, 0, 2, 0, 0},
        {0, 0, 5, 2, 0, 3, 1},
        {0, 0, 0, 0, 3, 0, 2},
        {0, 0, 0, 0, 1, 2, 0}
    };

    int start_node = 0;
    printf("BFS traversal starting from node %d:\n", start_node);
    BFS(a, visited, start_node);

    return 0;
}
