/* A: Add a node to the beginning of the list.
B: Add a node to the end of the list.
C: Add a node at a specific position in the list.
D: Delete the first node from the list.
E: Delete the last node from the list.
F: Delete a node at a specific position in the list.
P: Print the entire list.
S: Search for an element in the list.*/
#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
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
    if(*head==NULL)
    {
        *head=newNode;
    }
    else
    {
        struct node* cur=*head;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=newNode;
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
    newNode->next=*head;
    *head=newNode;
    
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
    if(pos<=0 ||*head==NULL)
    {
        newNode->next=*head;
        *head=newNode;
        return;
    }
    struct node *cur=*head;
    struct node *prev=NULL;
    for(int i=0;i<pos;i++)
    {
        prev=cur;
        cur=cur->next;
    }
    prev->next=newNode;
    newNode->next=cur;

}
int deleteAtPos(struct node **head,int pos)
{
    struct node *cur=*head;
    struct node *prev=NULL;
    int val;
    if(pos<=0 || (*head)->next==NULL)
    {
        *head=(*head)->next;
        val=cur->data;
        free(cur);
        return val;
    }
    for(int i=0;i<pos && cur->next!=NULL;i++)
    {
        prev=cur;
        cur=cur->next;
    }
    val=cur->data;
    prev->next=cur->next;
    free(cur);
    return val;
}
int deleteNodeBeg(struct node **head)
{
    struct node *cur=*head;
    *head=(*head)->next;
    int val=cur->data;
    free(cur);
    return val;
}
int deleteNodeEnd(struct node **head)
{
    struct node *cur=*head;
    struct node *prev;
    while(cur->next!=NULL)
    {
        prev=cur;
        cur=cur->next;
    }
    int val=cur->data;
    if(prev!=NULL)
    {
        prev->next=NULL;
    }
    else
    {
        *head=NULL;
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
int Search(struct node *head,int d)
{
    struct node *cur=head;
    while(cur)
    {
        if((cur->data)==d)
            return 1;
            cur=cur->next;
        
    }
    return 0;
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
            case 'S':
                fscanf(input, "%d", &val);
                c = Search(head, val);
                if (c == 1) {
                    fprintf(output, "Element found\n");
                } else {
                    fprintf(output, "Element not found\n");
                }
                break;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}
