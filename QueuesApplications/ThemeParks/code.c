#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a visitor
struct Visitor {
    int visitorID;
    char name[50];
    struct Visitor *next;
};

// Structure to represent a queue
struct Queue {
    struct Visitor *front; // Front of the queue
    struct Visitor *rear;  // Rear of the queue
};

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue *queue) {
    return queue->front == NULL;
}

// Function to add a visitor to the queue (enqueue)
void enqueue(struct Queue *queue, int visitorID, const char *name) {
    struct Visitor *newVisitor = (struct Visitor*)malloc(sizeof(struct Visitor));
    if (newVisitor == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newVisitor->visitorID = visitorID;
    strcpy(newVisitor->name, name);
    newVisitor->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newVisitor;
    } else {
        queue->rear->next = newVisitor;
        queue->rear = newVisitor;
    }
}

// Function to remove a visitor from the queue (dequeue)
int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    int visitorID = queue->front->visitorID;
    struct Visitor *temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return visitorID;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    struct Queue *queue = createQueue();
    int visitorID;
    char name[50];
    while (fscanf(inputFile, "%d %s", &visitorID, name) == 2) {
        enqueue(queue, visitorID, name);
        fprintf(outputFile, "Visitor %d (%s) entered the queue for the theme park.\n", visitorID, name);
    }


    while (!isEmpty(queue)) {
        visitorID = dequeue(queue);
        fprintf(outputFile, "Visitor %d (%s) served and entered the theme park.\n", visitorID, name);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
