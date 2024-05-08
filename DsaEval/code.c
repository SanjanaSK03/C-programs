#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct task
{
    char name[50];
    int priority;
    struct task *next;
};

void addTask(struct task **head, char n[], int p);
void displayList(struct task *head, FILE *output);
void DeleteTask(struct task **head, char n[], FILE *output);
void countTask(struct task *head, FILE *output);

void countTask(struct task *head, FILE *output)
{
    int count = 0;
    struct task *cur = head;
    while (cur != NULL)
    {
        count++;
        cur = cur->next;
    }
    fprintf(output, "Total tasks: %d\n\n", count);
}

void addTask(struct task **head, char n[], int p)
{
    struct task *newTask = (struct task *)malloc(sizeof(struct task));
    if (newTask == NULL)
    {
        perror("Error");
        exit(1);
    }
    newTask->next = NULL;
    strcpy(newTask->name, n);
    newTask->priority = p;

    struct task *current = *head;
    struct task *prev = NULL;

    while (current != NULL && current->priority > p)
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        newTask->next = *head;
        *head = newTask;
    }
    else
    {
        prev->next = newTask;
        newTask->next = current;
    }
}

void displayList(struct task *head, FILE *output)
{
    struct task *cur = head;
    while (cur != NULL)
    {
        fprintf(output, "Task name: %s\n", cur->name);
        fprintf(output, "Priority: %d\n", cur->priority);
        fprintf(output, "\n");
        cur = cur->next;
    }
}

void DeleteTask(struct task **head, char n[], FILE *output)
{
    if (*head == NULL)
    {
        fprintf(output, "Task list is empty.\n");
        return;
    }

    struct task *cur = *head;
    struct task *prev = NULL;

    while (cur != NULL && strcmp(cur->name, n) != 0)
    {
        prev = cur;
        cur = cur->next;
    }
    if (prev == NULL)
    {
        *head = cur->next;
    }
    else
    {
        prev->next = cur->next;
    }

    fprintf(output, "Task removed:\n");
    fprintf(output, "Task name: %s\n", cur->name);
    fprintf(output, "Priority: %d\n", cur->priority);
    free(cur);
}

int main()
{
    struct task *head = NULL;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    output = fopen("output.txt", "w");
    if (output == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    int p;
    char n[50];
    char x;
    while (fscanf(input, "%c", x) ==1)
    {
        switch(x)
        {
        case 'D':
            fscanf(input, "%s", n);
            DeleteTask(&head, n, output);
    
        break;
        case 'P':
            fprintf(output, "Task List:\n");
            displayList(head, output);
            break;
        case 'A':
        
            fscanf(input, "%s %d", n, &p);
            addTask(&head, n, p);
        
        break;
        case 'c':
            countTask(head, output);
            break;
}  
    
    fclose(output);
    return 0;
}
