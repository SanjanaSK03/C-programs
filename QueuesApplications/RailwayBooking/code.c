#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a passenger
struct Passenger {
    int passengerID;
    char name[50];
    struct Passenger *next;
};

// Structure to represent a queue
struct Queue {
    struct Passenger *front; // Front of the queue
    struct Passenger *rear;  // Rear of the queue
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

// Function to add a passenger to the queue (enqueue)
void enqueue(struct Queue *queue, int passengerID, const char *name) {
    struct Passenger *newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));
    if (newPassenger == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newPassenger->passengerID = passengerID;
    strcpy(newPassenger->name, name);
    newPassenger->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newPassenger;
    } else {
        queue->rear->next = newPassenger;
        queue->rear = newPassenger;
    }
}

// Function to remove a passenger from the queue (dequeue)
int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    int passengerID = queue->front->passengerID;
    struct Passenger *temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return passengerID;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    struct Queue *queue = createQueue();
    int passengerID;
    char name[50];
    while (fscanf(inputFile, "%d %s", &passengerID, name) == 2) {
        enqueue(queue, passengerID, name);
        fprintf(outputFile, "Passenger %d (%s) entered the railway booking queue.\n", passengerID, name);
    }

    while (!isEmpty(queue)) {
        passengerID = dequeue(queue);
        fprintf(outputFile, "Passenger %d (%s) booked the ticket and left the queue.\n", passengerID, name);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
