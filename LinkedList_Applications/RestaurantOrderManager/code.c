#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct order
{
    char item[50];
    float price;
    int quantity;
    struct order *next;
};

void addOrder(struct order **head, char item[], float price, int quantity);
void displayOrders(struct order *head, FILE *output);
void removeOrder(struct order **head, char item[], FILE *output);
void totalBill(struct order *head, FILE *output);

void totalBill(struct order *head, FILE *output)
{
    float total = 0;
    struct order *cur = head;
    while (cur != NULL)
    {
        total += cur->price * cur->quantity;
        cur = cur->next;
    }
    fprintf(output, "Total bill = Rs. %.2f\n", total);
}

void addOrder(struct order **head, char item[], float price, int quantity)
{
    struct order *newOrder = (struct order *)malloc(sizeof(struct order));
    if (newOrder == NULL)
    {
        perror("Error");
        exit(1);
    }
    newOrder->next = NULL;
    strcpy(newOrder->item, item);
    newOrder->price = price;
    newOrder->quantity = quantity;
    
    if (*head == NULL)
    {
        *head = newOrder;
    }
    else
    {
        struct order *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newOrder;
    }
}

void displayOrders(struct order *head, FILE *output)
{
    struct order *cur = head;
    while (cur != NULL)
    {
        fprintf(output, "Item: %s\n", cur->item);
        fprintf(output, "Price: Rs. %.2f\n", cur->price);
        fprintf(output, "Quantity: %d\n", cur->quantity);
        fprintf(output, "\n");
        cur = cur->next;
    }
}

void removeOrder(struct order **head, char item[], FILE *output)
{
    if (*head == NULL)
    {
        fprintf(output, "Order list is empty.\n");
        return;
    }

    struct order *cur = *head;
    struct order *prev = NULL;

    while (cur != NULL && strcmp(cur->item, item) != 0)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL)
    {
        fprintf(output, "Item not found.\n");
        return;
    }

    if (prev == NULL)
    {
        *head = cur->next;
    }
    else
    {
        prev->next = cur->next;
    }

    fprintf(output, "Order removed:\n");
    fprintf(output, "Item: %s\n", cur->item);
    fprintf(output, "Price: Rs. %.2f\n", cur->price);
    fprintf(output, "Quantity: %d\n", cur->quantity);
    free(cur);
}

int main()
{
    struct order *head = NULL;
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
    int quantity;
    float price;
    char item[50], command[20];
    while (fscanf(input, "%s", command) != EOF)
    {
        if (!strcmp(command, "delete"))
        {
            fscanf(input, "%s", item);
            removeOrder(&head, item, output);
        }
        else if (!strcmp(command, "display"))
        {
            fprintf(output, "Order List:\n");
            displayOrders(head, output);
        }
        else if (!strcmp(command, "add"))
        {
            fscanf(input, "%s %f %d", item, &price, &quantity);
            addOrder(&head, item, price, quantity);
        }
        else if (!strcmp(command, "total"))
        {
            totalBill(head, output);
        }
    }
    fclose(output);
    return 0;
}
