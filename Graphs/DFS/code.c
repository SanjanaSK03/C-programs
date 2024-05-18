#include <stdio.h>
#include <stdlib.h>

#define max 10

int visited[7] = {0, 0, 0, 0, 0, 0, 0};
int a[7][7] = {
        {0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}};

struct Stack {
    int top;
    int arr[max];
};

// Function to initialize the stack
void initialize(struct Stack *stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, int value) {
    if (stack->top == max - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

void DFS(int vertex) 
{
    struct Stack s;
    initialize(&s);

    push(&s, vertex);
    visited[vertex] = 1;

    printf("%d ", vertex);
    int i;
    while (!isEmpty(&s)) 
    {
        int current = pop(&s);
        for (i = 0; i < 7; i++) 
        {
            if (a[current][i] == 1 && visited[i] == 0) 
            {
                push(&s, i);
                visited[i] = 1;
                printf("%d ", i);
            }
        }
    }
}

int main() {
    printf("Depth First Search Traversal: ");
    DFS(0); // Start DFS from vertex 0
    printf("\n");

    return 0;
}
