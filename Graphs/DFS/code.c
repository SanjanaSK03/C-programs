#include <stdio.h>
#include <stdlib.h>


int adj_matrix[7][7] = {
        {0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}};
int visited[7];

struct Stack {
    int arr[7];
    int top;
};

void push(struct Stack *s, int value) {
    s->arr[++(s->top)] = value;
}

int pop(struct Stack *s) {
    return s->arr[(s->top)--];
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

void dfs(int start_node, int n) 
{
    struct Stack s;
    s.top = -1;
    push(&s, start_node);

    while (!isEmpty(&s)) {
        int current_node = pop(&s);
        if (!visited[current_node]) {
            printf("%d ", current_node);
            visited[current_node] = 1;

            for (int i = 0; i < n; i++) {
                if (adj_matrix[current_node][i] && !visited[i]) {
                    push(&s, i);
                }
            }
        }
    }
}

int main() {
    int start_node;
    printf("Enter the starting node: ");
    scanf("%d", &start_node);

    // Reset visited array
    for (int i = 0; i < 7; i++) {
        visited[i] = 0;
    }

    printf("DFS Traversal: ");
    dfs(start_node, 7);

    return 0;
}
