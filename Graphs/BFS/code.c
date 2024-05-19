#include <stdio.h>

#define size 10

struct queue
{
    int front;
    int rear;
    int a[size];
};

void initQueue(struct queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct queue *q)
{
    return q->front == -1;
}

int isFull(struct queue *q)
{
    return q->rear == size - 1;
}

void enQueue(struct queue *q, int d)
{
    if (isFull(q))
    {
        printf("Queue is FULL\n");
        return;
    }
    if (isEmpty(q))
    {
        q->front = q->rear = 0;
    }
    else
    {
        q->rear = q->rear + 1;
    }
    q->a[q->rear] = d;
}

int deQueue(struct queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is Empty\n");
        return -1;
    }
    int d = q->a[q->front];
    if (q->front == q->rear)
    {
        q->front = q->rear = -1;
    }
    else
    {
        q->front = q->front + 1;
    }
    return d;
}

int main()
{
    // Initializing Queue (Array Implementation)
    struct queue q;
    initQueue(&q);

    // BFS Implementation
    int node;
    int i = 4;
    int visited[7] = {0, 0, 0, 0, 0, 0, 0};
    int a[7][7] = {
        {0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}};

    printf("%d ", i);
    visited[i] = 1;
    enQueue(&q, i); // Enqueue i for exploration
    while (!isEmpty(&q))
    {
        int node = deQueue(&q);
        for (int j = 0; j < 7; j++)
        {
            if (a[node][j] == 1 && visited[j] == 0)
            {
                printf("%d ", j);
                visited[j] = 1;
                enQueue(&q, j);
            }
        }
    }
    return 0;
}
