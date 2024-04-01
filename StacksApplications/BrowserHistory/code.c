#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 100
#define MAX_STACK_SIZE 10 // Maximum number of URLs in history stack

struct stack {
    char url[MAX_URL_LENGTH];
    struct stack *next;
};
int isFull(struct stack *top) {
    int count = 0;
    struct stack *cur = top;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count >= MAX_STACK_SIZE;
}

int isEmpty(struct stack *top) {
    return top == NULL;
}
void push(struct stack **top, char *url) {
    if (isFull(*top)) {
        fprintf(stderr, "Error: Stack overflow\n");
        return;
    }

    struct stack *new_node = (struct stack *)malloc(sizeof(struct stack));
    if (new_node == NULL) {
        perror("Error\n");
        return;
    }
    strncpy(new_node->url, url, MAX_URL_LENGTH - 1);
    new_node->url[MAX_URL_LENGTH - 1] = '\0'; // Ensure null-termination
    new_node->next = *top;
    *top = new_node;
}

char* pop(struct stack **top) {
    if (isEmpty(*top)) {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    struct stack *cur = *top;
    *top = (*top)->next;
    char* url = malloc(strlen(cur->url) + 1); // Allocate memory for the URL
    if (url == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(url, cur->url); // Copy the URL
    free(cur); // Free the node
    return url;
}


void display_history(struct stack *top, FILE *output) {
    fprintf(output, "Browser History:\n");
    struct stack *cur = top;
    while (cur) {
        fprintf(output, "%s\n", cur->url);
        cur = cur->next;
    }
}



int main() {
    struct stack *history = NULL;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error in opening input file\n");
        return 1;
    }
    char operation, url[MAX_URL_LENGTH];
    output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("Error in opening output file\n");
        fclose(input);
        return 1;
    }
    while (fscanf(input, " %c", &operation) == 1) {
        switch (operation) {
            case 'A':
                fscanf(input, "%s", url);
                push(&history, url);
                break;
            case 'B':
                if (isEmpty(history)) {
                    fprintf(output, "Browser history is empty.\n");
                } else {
                    char* visited_url = pop(&history);
                    fprintf(output, "Navigated back to: %s\n", visited_url);
                    free(visited_url); // Free memory allocated for the URL
                }
                break;
            case 'D':
                display_history(history, output);
                break;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
