#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product
{
    char name[20];
    float price;
    int quantity;
    struct product *next;
};
void addToCart(struct product **head, char n[], float p, int q);
void displayCart(struct product *head,FILE *output);
void removeFromCart(struct product **head,char n[],FILE *output);
void totalPrice(struct product *head,FILE *output);
void totalPrice(struct product *head,FILE *output)
{
    int sum=0;
    struct product *cur = head;
    while (cur != NULL)
    {
        sum=sum+(cur->price*cur->quantity);
        cur=cur->next;
    }
    fprintf(output,"Cart total = Rs.%d\n", sum);
}
void addToCart(struct product **head, char n[], float p, int q)
{
    struct product *newProduct = (struct product *)malloc(sizeof(struct product));
    if (newProduct == NULL)
    {
        perror("Error");
        exit(1);
    }
    newProduct->next = NULL;
    strcpy(newProduct->name, n);
    newProduct->price = p;
    newProduct->quantity = q;
    newProduct->next = *head;
    *head = newProduct;
}

void displayCart(struct product *head,FILE *output)
{
    struct product *cur = head;
    while (cur != NULL)
    {
        fprintf(output,"Product name = %s\n", cur->name);
        fprintf(output,"Price = Rs. %.2f\n", cur->price);
        fprintf(output,"Quantity = %d\n", cur->quantity);
        fprintf(output,"\n");
        cur = cur->next;
    }
}
void removeFromCart(struct product **head,char n[],FILE *output)
{
    if (*head == NULL) 
    {
        printf("Cart is empty.\n");
        return;
    }
    struct product* cur = *head;
    struct product* prev = NULL;
    while((cur->next!=NULL) && (strcmp(cur->name,n)!=0))
    {
        prev=cur;
        cur=cur->next;
    }
    if(prev!=NULL)
    {
        prev->next=cur->next;
    }
    else
    {
        *head=cur->next;
    }
    fprintf(output, "Product removed:\n");
    displayCart(cur,output);
    free(cur);
}
int main()
{
    struct product *head = NULL;
    FILE *input,*output;
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
    int q;
    float p;
    char n[20],x[20];
    while (fscanf(input,"%s", x) != EOF)
    {
        if(!strcmp(x,"delete"))
        {
            fscanf(input,"%s",n);
            removeFromCart(&head,n,output);
        }
        else if(!strcmp(x,"display"))
        {
            fprintf(output,"Shopping Cart:\n");
            displayCart(head,output);
        }
        else if(!strcmp(x,"add"))
        {
            fscanf(input,"%s %f %d",n,&p,&q);
            addToCart(&head, n, p, q);
        }
        else if(!strcmp(x,"total"))
        {
            totalPrice(head,output);
        }
    }
    fclose(output);
    return 0;
}
