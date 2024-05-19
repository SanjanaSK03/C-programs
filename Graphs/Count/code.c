#include <stdio.h>

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

    int vertex_count = 0; // Counter for visited vertices

    enQueue(&q, start);
    visited[start] = 1;
    vertex_count++; // Increment for the start node

    while (!isEmpty(&q)) {
        int node = deQueue(&q);
        for (int j = 0; j < 7; j++) {
            if (a[node][j] == 1 && !visited[j]) {
                visited[j] = 1;
                enQueue(&q, j);
                vertex_count++; // Increment for each newly visited node
            }
        }
    }

    printf("Number of visited vertices: %d\n", vertex_count); // Print the count of visited vertices
}

int main() {
    // BFS Implementation with Unweighted Graph
    int visited[7] = {0, 0, 0, 0, 0, 0, 0};
    int a[7][7] = {
        {0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}
    };

    int start_node = 0;
    printf("BFS traversal starting from node %d:\n", start_node);
    BFS(a, visited, start_node);

    return 0;
}
