#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a patient
struct Patient {
    int patientID;
    char name[50];
    struct Patient *next;
};

// Structure to represent a queue
struct Queue {
    struct Patient *front; // Front of the queue
    struct Patient *rear;  // Rear of the queue
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

// Function to add a patient to the queue (enqueue)
void enqueue(struct Queue *queue, int patientID, const char *name) {
    struct Patient *newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    if (newPatient == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newPatient->patientID = patientID;
    strcpy(newPatient->name, name);
    newPatient->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newPatient;
    } else {
        queue->rear->next = newPatient;
        queue->rear = newPatient;
    }
}

// Function to remove a patient from the queue (dequeue)
int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    int patientID = queue->front->patientID;
    struct Patient *temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return patientID;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    struct Queue *queue = createQueue();
    int patientID;
    char name[50];
    while (fscanf(inputFile, "%d %s", &patientID, name) == 2) {
        enqueue(queue, patientID, name);
        fprintf(outputFile, "Patient %d (%s) entered the emergency services queue.\n", patientID, name);
    }

    while (!isEmpty(queue)) {
        patientID = dequeue(queue);
        fprintf(outputFile, "Patient %d (%s) served and left the emergency services.\n", patientID, name);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
