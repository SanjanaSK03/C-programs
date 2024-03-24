/* A: Add a node to the beginning of the list.
B: Add a node to the end of the list.
C: Add a node at a specific position in the list.
D: Delete the first node from the list.
E: Delete the last node from the list.
F: Delete a node at a specific position in the list.
P: Print the entire list.*/
#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
void addNodeEnd(struct node **head, int d);
void addNodeBeg(struct node **head, int d);
void addAtPos(struct node **head, int d, int pos);
int deleteAtPos(struct node **head, int pos);
int deleteNodeBeg(struct node **head);
int deleteNodeEnd(struct node **head);
void displayList(struct node *head, FILE *output);
int Search(struct node *head, int d);

void addNodeEnd(struct node **head,int d)
{
    struct node *newNode=(struct node *)malloc(sizeof(struct node));
    if(newNode==NULL)
    {
        perror("Error");
        exit(0);
    }
    newNode->data=d;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(*head==NULL)
    {
        *head=newNode;
    }
    else
    {
        struct node *q=*head;
        while(q->next!=NULL)
        {
            q=q->next;
        }
        newNode->prev=q;
        q->next=newNode;
    }
}
void addNodeBeg(struct node **head,int d)
{
    struct node *newNode=(struct node *)malloc(sizeof(struct node));
    if(newNode==NULL)
    {
        perror("Error");
        exit(0);
    }
    newNode->data=d;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(*head==NULL)
    {
        *head=newNode;
    }
    else
    {
        newNode->next=*head;
        (*head)->prev=newNode;
        *head=newNode;
    }
    
}
void addAtPos(struct node **head,int d,int pos)
{
    struct node *newNode=(struct node *)malloc(sizeof(struct node));
    if(newNode==NULL)
    {
        perror("Error");
        exit(0);
    }
    newNode->data=d;
    newNode->next=NULL;
    newNode->prev=NULL;
    if(*head==NULL)
    {
        *head=newNode;
        return;
    }
    if(pos<=0)
    {
        newNode->next=*head;
        (*head)->prev=newNode;
        *head=newNode;
        return;
    }
    struct node *cur=*head;
    struct node *follow;
    for(int i=0;i<pos && cur!=NULL;i++)
    {
        follow=cur;
        cur=cur->next;
    }
    newNode->next=cur;
    newNode->prev=follow;
    follow->next=newNode;
    if(cur!=NULL)
    {
        cur->prev=newNode;
    }

}
int deleteAtPos(struct node **head,int pos)
{
    struct node *cur=*head;
    struct node *follow=NULL;
    int val;
    if(cur->next==NULL)
    {
        val=cur->data;
        *head=NULL;
        free(cur);
        return val;
    }
    if(pos<0)
    {
        *head=(*head)->next;
        val=cur->data;
        (*head)->prev=NULL;
        free(cur);
        return val;
    }
    for(int i=0;i<pos && cur->next!=NULL;i++)
    {
        follow=cur;
        cur=cur->next;
    }
    val=cur->data;
    if(cur->next!=NULL)
    {
        (cur->next)->prev=follow;
    }
    follow->next=cur->next;
    free(cur);
    return val;

}
int deleteNodeBeg(struct node **head)
{
    struct node *cur=*head;
    *head=(*head)->next;
    if((*head)!=NULL)
    {
        (*head)->prev=NULL;
    }
    int val=cur->data;
    free(cur);
    return val;
}
int deleteNodeEnd(struct node **head)
{
    struct node *cur=*head;
    struct node *follow;
    while(cur->next!=NULL)
    {
        cur=cur->next;
    }
    int val=cur->data;
    follow=cur->prev;
    if(follow!=NULL)
    {
        follow->next=NULL;
    }
    
    free(cur);
    return val;
}
void displayList(struct node *head, FILE *output)
{
    struct node *current = head;
    fprintf(output, "List= ");
    while (current != NULL)
    {
        printf("%d\n", current->data);
        fprintf(output, "%d ", current->data); // Add newline character
        current = current->next;
    }
    fprintf(output, "\n");
}

int main() {
    struct node* head = NULL;
    FILE *input, *output;
    int val, pos, c;
    char operation;

    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("\nError in opening input file\n");
        return 1;
    }

    output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("\nError in opening output file\n");
        fclose(input);
        return 1;
    }

    while (fscanf(input, " %c", &operation)==1) {
        switch (operation) {
            case 'A':
                fscanf(input, "%d", &val);
                addNodeBeg(&head, val);
                break;
            case 'B':
                fscanf(input, "%d", &val);
                addNodeEnd(&head, val);
                break;
            case 'C':
                fscanf(input, "%d %d", &val, &pos);
                addAtPos(&head, val, pos);
                break;
            case 'D':
                val = deleteNodeBeg(&head);
                printf("deleted node at beginning=%d\n", val);
                break;
            case 'E':
                val = deleteNodeEnd(&head);
                printf("deleted node at end=%d\n", val);
                break;
            case 'F':
                fscanf(input, "%d", &pos);
                val = deleteAtPos(&head, pos);
                printf("deleted node at pos %d=%d\n", pos, val);
                break;
            case 'P':
                displayList(head, output);
                break;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}
