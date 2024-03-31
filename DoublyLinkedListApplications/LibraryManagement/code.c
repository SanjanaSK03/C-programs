#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book_node
{
    char title[100];
    char author[100];
    char genre[100];
    struct book_node *prev;
    struct book_node *next;
};

void add_book(struct book_node **head, char title[], char author[], char genre[]);
void display_books(struct book_node *head, FILE *output);
void delete_book(struct book_node **head, char title[], FILE *output);
int count_books(struct book_node *head);
void clear_books(struct book_node **head);

void add_book(struct book_node **head, char title[], char author[], char genre[])
{
    struct book_node *new_book = (struct book_node *)malloc(sizeof(struct book_node));
    if (new_book == NULL)
    {
        perror("Error");
        exit(1);
    }
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    strcpy(new_book->genre, genre);
    new_book->prev = NULL;
    new_book->next = *head;

    if (*head != NULL)
    {
        (*head)->prev = new_book;
    }

    *head = new_book;
}

void display_books(struct book_node *head, FILE *output)
{
    struct book_node *current = head;
    while (current != NULL)
    {
        fprintf(output, "Title: %s\n", current->title);
        fprintf(output, "Author: %s\n", current->author);
        fprintf(output, "Genre: %s\n", current->genre);
        fprintf(output, "\n");
        current = current->next;
    }
}

void delete_book(struct book_node **head, char title[], FILE *output)
{
    struct book_node *current = *head;

    while (current != NULL && strcmp(current->title, title) != 0)
    {
        printf("%s",current->title);
        current = current->next;
    }

    if (current == NULL)
    {
        fprintf(output, "Book not found.\n");
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

    fprintf(output, "Book removed:\n");
    fprintf(output, "Title: %s\n", current->title);
    fprintf(output, "Author: %s\n", current->author);
    fprintf(output, "Genre: %s\n", current->genre);
    free(current);
}

int count_books(struct book_node *head)
{
    int count = 0;
    struct book_node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void clear_books(struct book_node **head)
{
    struct book_node *current = *head;
    struct book_node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main()
{
    struct book_node *library = NULL;
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
    char title[100], author[100], genre[100], x[20];
    while (fscanf(input, "%s", x) != EOF)
    {
        if (!strcmp(x, "delete"))
        {
            fscanf(input," %[^\n]", title);
            printf("title:%s",title);
            delete_book(&library, title, output);
        }
        else if (!strcmp(x, "display"))
        {
            fprintf(output, "Library:\n");
            display_books(library, output);
        }
        else if (!strcmp(x, "add"))
{
    fscanf(input, " %[^,],%[^,],%[^\n]", title, author, genre);
    add_book(&library, title, author, genre);
}

        else if (!strcmp(x, "count"))
        {
            int count = count_books(library);
            fprintf(output, "Total books in library: %d\n", count);
        }
        else if (!strcmp(x, "clear"))
        {
            clear_books(&library);
            fprintf(output, "Library cleared.\n");
        }
    }
    fclose(output);
    return 0;
}
