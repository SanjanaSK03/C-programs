#include <stdio.h>
#include <stdlib.h>

#define size 10

struct stack {
    char data;
    struct stack *next;
};

void push(struct stack **top, char d) {
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

char pop(struct stack **top) {
    if (*top == NULL) {
        perror("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    struct stack *cur = *top;
    char e = cur->data;
    *top = (*top)->next;
    free(cur);
    return e;
}

void displaystack(struct stack *top, FILE *output) {
    struct stack *cur = top;
    fprintf(output, "Stack: ");
    while (cur) {
        fprintf(output, "%c ", cur->data);
        cur = cur->next;
    }
    fprintf(output, "\n");
}

int isBalanced(FILE *input, FILE *output) {
    struct stack *top = NULL;
    char ch;
    while ((fscanf(input, "%c", &ch)) == 1) {
        switch (ch) {
            case '(':
            case '[':
            case '{':
                push(&top, ch);
                break;
            case ')':
                if (top == NULL || pop(&top) != '(') {
                    fprintf(output, "Unbalanced Parentheses\n");
                    return 0;
                }
                break;
            case ']':
                if (top == NULL || pop(&top) != '[') {
                    fprintf(output, "Unbalanced Parentheses\n");
                    return 0;
                }
                break;
            case '}':
                if (top == NULL || pop(&top) != '{') {
                    fprintf(output, "Unbalanced Parentheses\n");
                    return 0;
                }
                break;
        }
    }
    if (top == NULL) {
        fprintf(output, "Balanced Parentheses\n");
        return 1;
    } else {
        fprintf(output, "Unbalanced Parentheses\n");
        return 0;
    }
}

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error in opening input file\n");
        return 1;
    }
    output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("Error in opening output file\n");
        return 1;
    }
    isBalanced(input, output);
    fclose(input);
    fclose(output);
    return 0;
}
