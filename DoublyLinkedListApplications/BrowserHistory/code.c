#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node
{
    char url[200];
    char timestamp[50];
    struct node *prev;
    struct node *next;
};

void add_url(struct node **head, char url[], char timestamp[]);
void display_history(struct node *head, FILE *output);
void delete_url(struct node **head, char url[], FILE *output);
int count_urls(struct node *head);
void clear_history(struct node **head);

void add_url(struct node **head, char url[], char timestamp[])
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        perror("Error");
        exit(1);
    }
    strcpy(new_node->url, url);
    strcpy(new_node->timestamp, timestamp);
    new_node->prev = NULL;
    new_node->next = *head;

    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }

    *head = new_node;
}

void display_history(struct node *head, FILE *output)
{
    struct node *current = head;
    while (current != NULL)
    {
        fprintf(output, "URL: %s, Timestamp: %s\n", current->url, current->timestamp);
        current = current->next;
    }
}

void delete_url(struct node **head, char url[], FILE *output)
{
    struct node *current = *head;

    while (current != NULL && strcmp(current->url, url) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        fprintf(output, "URL not found.\n");
        return;
    }

    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else
    {
        *head = current->next;
    }

    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }

    fprintf(output, "URL removed: %s, Timestamp: %s\n", current->url, current->timestamp);
    free(current);
}

int count_urls(struct node *head)
{
    int count = 0;
    struct node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void clear_history(struct node **head)
{
    struct node *current = *head;
    struct node *n;
    while (current != NULL)
    {
        n = current->next;
        free(current);
        current = n;
    }
    *head = NULL;
}

int main()
{
    struct node *history = NULL;
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
    char url[200], timestamp[50], x[20];
    while (fscanf(input, "%s", x) != EOF)
    {
        if (!strcmp(x, "delete"))
        {
            fscanf(input, "%s", url);
            delete_url(&history, url, output);
        }
        else if (!strcmp(x, "display"))
        {
            fprintf(output, "Browser History:\n");
            display_history(history, output);
        }
        else if (!strcmp(x, "add"))
        {
            fscanf(input, "%s", url);
            fscanf(input, "%s", timestamp);
            add_url(&history, url, timestamp);
        }
        else if (!strcmp(x, "count"))
        {
            int count = count_urls(history);
            fprintf(output, "Total URLs in history: %d\n", count);
        }
        else if (!strcmp(x, "clear"))
        {
            clear_history(&history);
            fprintf(output, "History cleared.\n");
        }
    }
    fclose(output);
    return 0;
}
