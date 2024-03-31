#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct recipe_node
{
    char title[100];
    char ingredients[200];
    char instructions[500];
    struct recipe_node *prev;
    struct recipe_node *next;
};

void add_recipe(struct recipe_node **head, char title[], char ingredients[], char instructions[]);
void display_recipes(struct recipe_node *head, FILE *output);
void delete_recipe(struct recipe_node **head, char title[], FILE *output);
int count_recipes(struct recipe_node *head);
void clear_recipes(struct recipe_node **head);

void add_recipe(struct recipe_node **head, char title[], char ingredients[], char instructions[])
{
    struct recipe_node *new_recipe = (struct recipe_node *)malloc(sizeof(struct recipe_node));
    if (new_recipe == NULL)
    {
        perror("Error");
        exit(1);
    }
    strcpy(new_recipe->title, title);
    strcpy(new_recipe->ingredients, ingredients);
    strcpy(new_recipe->instructions, instructions);
    new_recipe->prev = NULL;
    new_recipe->next = *head;

    if (*head != NULL)
    {
        (*head)->prev = new_recipe;
    }

    *head = new_recipe;
}

void display_recipes(struct recipe_node *head, FILE *output)
{
    struct recipe_node *current = head;
    while (current != NULL)
    {
        fprintf(output, "Title: %s\n", current->title);
        fprintf(output, "Ingredients: %s\n", current->ingredients);
        fprintf(output, "Instructions: %s\n", current->instructions);
        fprintf(output, "\n");
        current = current->next;
    }
}

void delete_recipe(struct recipe_node **head, char title[], FILE *output)
{
    struct recipe_node *current = *head;

    while (current != NULL && strcmp(current->title, title) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        fprintf(output, "Recipe not found.\n");
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

    fprintf(output, "Recipe removed:\n");
    fprintf(output, "Title: %s\n", current->title);
    fprintf(output, "Ingredients: %s\n", current->ingredients);
    fprintf(output, "Instructions: %s\n", current->instructions);
    free(current);
}

int count_recipes(struct recipe_node *head)
{
    int count = 0;
    struct recipe_node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void clear_recipes(struct recipe_node **head)
{
    struct recipe_node *current = *head;
    struct recipe_node *next;
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
    struct recipe_node *recipe_collection = NULL;
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
    char title[100], ingredients[200], instructions[500], x[20];
    while (fscanf(input, "%s", x) != EOF)
    {
        if (!strcmp(x, "delete"))
        {
            fscanf(input, "%s", title);
            delete_recipe(&recipe_collection, title, output);
        }
        else if (!strcmp(x, "display"))
        {
            fprintf(output, "Recipe Collection:\n");
            display_recipes(recipe_collection, output);
        }
        else if (!strcmp(x, "add"))
        {
            fscanf(input, " %[^,],%[^,],%[^\n]", title,ingredients,instructions);
            add_recipe(&recipe_collection, title, ingredients, instructions);
        }
        else if (!strcmp(x, "count"))
        {
            int count = count_recipes(recipe_collection);
            fprintf(output, "Total recipes in collection: %d\n", count);
        }
        else if (!strcmp(x, "clear"))
        {
            clear_recipes(&recipe_collection);
            fprintf(output, "Recipe collection cleared.\n");
        }
    }
    fclose(output);
    return 0;
}