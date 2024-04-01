#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 100

struct Stack {
    char data;
    struct Stack* next;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        perror("Error creating stack");
        exit(EXIT_FAILURE);
    }
    stack->next = NULL;
    return stack;
}

void push(struct Stack** stack, char data) {
    struct Stack* newNode = (struct Stack*)malloc(sizeof(struct Stack));
    if (!newNode) {
        perror("Error creating new node");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = *stack;
    *stack = newNode;
}

char pop(struct Stack** stack) {
    if (*stack == NULL) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    struct Stack* temp = *stack;
    char popped = temp->data;
    *stack = temp->next;
    free(temp);
    return popped;
}

char peek(struct Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data;
}

int isEmpty(struct Stack* stack) {
    return stack == NULL;
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

void reverseString(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

// Corrected infixToPrefix function

void infixToPrefix(FILE* inputFile, FILE* outputFile) {
    struct Stack* operatorStack = createStack();
    char infix[MAX_EXPRESSION_LENGTH];
    char prefix[MAX_EXPRESSION_LENGTH];
    int outputIndex = 0;
    char c;

    // Read infix expression character by character from input file
    int i = 0;
    while ((fscanf(inputFile, " %c", &c)) != EOF && c != '\n') {
        infix[i++] = c;
    }
    infix[i] = '\0';

    // Reverse the infix expression
    reverseString(infix);

    int len = strlen(infix);

    for (int i = 0; i < len; i++) {
        if (infix[i] != ' ') {
            if (infix[i] >= '0' && infix[i] <= '9') {
                prefix[outputIndex++] = infix[i];
            } else if (infix[i] == ')') {
                push(&operatorStack, infix[i]);
            } else if (infix[i] == '(') {
                while (!isEmpty(operatorStack) && peek(operatorStack) != ')') {
                    prefix[outputIndex++] = pop(&operatorStack);
                }
                pop(&operatorStack); // Discard the ')'
            } else {
                while (!isEmpty(operatorStack) && precedence(infix[i]) <= precedence(peek(operatorStack))) {
                    prefix[outputIndex++] = pop(&operatorStack);
                }
                push(&operatorStack, infix[i]);
            }
        }
    }

    while (!isEmpty(operatorStack)) {
        prefix[outputIndex++] = pop(&operatorStack);
    }

    prefix[outputIndex-1] = '\0';

    // Reverse the resulting prefix expression to get the final result
    reverseString(prefix);

    // Write prefix expression to output file
    fprintf(outputFile, "Prefix expression: %s\n", prefix);
}


int main() {
    FILE *inputFile, *outputFile;

    // Open input file for reading
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Open output file for writing
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Convert infix to prefix and write to output file
    infixToPrefix(inputFile, outputFile);

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    printf("Prefix expression has been written to output.txt\n");

    return 0;
}
