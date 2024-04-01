#include <stdio.h>
#include <stdlib.h>

#define size 10

struct stack {
    int data;
    struct stack *next;
};

void push(struct stack **top, int d) {
    struct stack *new;
    new = (struct stack *)malloc(sizeof(struct stack));
    if (new == NULL) {
        perror("Error\n");
        return;
    }
    new->data = d;
    new->next = *top;
    *top = new;
}

int pop(struct stack **top) {
    if (*top == NULL) {
        perror("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    struct stack *cur = *top;
    int e = cur->data;
    *top = (*top)->next;
    free(cur);
    return e;
}

void displaystack(struct stack *top, FILE *output) {
    struct stack *cur = top;
    fprintf(output, "Stack: ");
    while (cur) {
        fprintf(output, "%d ", cur->data);
        cur = cur->next;
    }
    fprintf(output, "\n");
}

int main() {
    struct stack *top = NULL, *undo_stack = NULL;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error in opening input file\n");
        return 1;
    }
    int val;
    char ch;
    output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("Error in opening output file\n");
        fclose(input);
        return 1;
    }
    while ((fscanf(input, "%c", &ch)) == 1) {
        switch (ch) {
            case 'A':
                fscanf(input, "%d", &val);
                push(&top, val);
                break;
            case 'P':
                if (top == NULL) {
                    fprintf(output, "No elements to pop.\n");
                } else {
                    val = pop(&top);
                    fprintf(output, "Popped element = %d\n", val);
                    // Push the popped element to the undo stack
                    push(&undo_stack, val);
                }
                break;
            case 'U':
                if (undo_stack == NULL) {
                    fprintf(output, "No undo available.\n");
                } else {
                    // Pop the top element from the undo stack
                    val = pop(&undo_stack);
                    // Push the element back to the main stack
                    push(&top, val);
                    fprintf(output, "Undo performed. Element = %d\n", val);
                }
                break;
            case 'D':
                displaystack(top, output);
                break;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
