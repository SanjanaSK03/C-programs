#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a customer
struct Customer {
    int customerID;
    char name[50];
    struct Customer *next;
};

// Structure to represent a queue
struct Queue {
    struct Customer *front; // Front of the queue
    struct Customer *rear;  // Rear of the queue
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

// Function to add a customer to the queue (enqueue)
void enqueue(struct Queue *queue, int customerID, const char *name) {
    struct Customer *newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
    if (newCustomer == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newCustomer->customerID = customerID;
    strcpy(newCustomer->name, name);
    newCustomer->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newCustomer;
    } else {
        queue->rear->next = newCustomer;
        queue->rear = newCustomer;
    }
}

// Function to remove a customer from the queue (dequeue)
int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    int customerID = queue->front->customerID;
    struct Customer *temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return customerID;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    struct Queue *queue = createQueue();
    int customerID;
    char name[50];
    while (fscanf(inputFile, "%d %s", &customerID, name) == 2) {
        enqueue(queue, customerID, name);
        fprintf(outputFile, "Customer %d (%s) entered the queue.\n", customerID, name);
    }


    while (!isEmpty(queue)) {
        customerID = dequeue(queue);
        fprintf(outputFile, "Customer %d served and left the supermarket.\n", customerID);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
