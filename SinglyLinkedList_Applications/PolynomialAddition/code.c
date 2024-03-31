#include <stdio.h>
#include <stdlib.h>
struct node
{
    int c;
    int e;
    struct node *next;
};
void addPolynomial(struct node **head1, struct node **head2, struct node **head3)
{
    struct node *cur1 = *head1;
    struct node *cur2 = *head2;
    struct node *c3 = NULL;

    while (cur1 != NULL && cur2 != NULL)
    {
        struct node *cur3 = (struct node *)malloc(sizeof(struct node));
        if (cur3 == NULL)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        if (cur1->e == cur2->e)
        {
            cur3->c = cur1->c + cur2->c;
            cur3->e = cur1->e;
            cur2 = cur2->next;
            cur1 = cur1->next;
        }
        else if (cur1->e > cur2->e)
        {
            cur3->c = cur1->c;
            cur3->e = cur1->e;
            cur1 = cur1->next;
        }
        else
        {
            cur3->c = cur2->c;
            cur3->e = cur2->e;
            cur2 = cur2->next;
        }
        cur3->next = NULL;
        if (*head3 == NULL)
        {
            *head3 = cur3;
        }
        else
        {
            c3->next = cur3;
        }
        c3 = cur3;
    }

    // Handle remaining terms in either polynomial
    while (cur1 != NULL)
    {
        struct node *cur3 = (struct node *)malloc(sizeof(struct node));
        if (cur3 == NULL)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        cur3->c = cur1->c;
        cur3->e = cur1->e;
        cur3->next = NULL;
        if (*head3 == NULL)
        {
            *head3 = cur3;
        }
        else
        {
            c3->next = cur3;
        }
        c3 = cur3;
        cur1 = cur1->next;
    }

    while (cur2 != NULL)
    {
        struct node *cur3 = (struct node *)malloc(sizeof(struct node));
        if (cur3 == NULL)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        cur3->c = cur2->c;
        cur3->e = cur2->e;
        cur3->next = NULL;
        if (*head3 == NULL)
        {
            *head3 = cur3;
        }
        else
        {
            c3->next = cur3;
        }
        c3 = cur3;
        cur2 = cur2->next;
    }
}

void displayPolynomial(struct node *head,FILE *output) 
{
    struct node *current = head;
    while (current != NULL) {
        fprintf(output,"%dx^%d", current->c, current->e);
        current = current->next;
        if (current != NULL) {
            fprintf(output," + ");
        }
    }
    fprintf(output,"\n");
}

void addNode(struct node **head,int coeff,int exp)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if(new==NULL)
    {
        perror("Error");
        exit(0);
    }
    new->c=coeff;
    new->e=exp;
    new->next=NULL;

    if(*head==NULL || exp > (*head)->e)
    {
        new->next=*head;
        *head=new;
        return;
    }
    struct node *prev=NULL;
    struct node *cur=*head;
    
    while(cur!=NULL && exp< cur->e)
    {
        prev=cur;
        cur=cur->next;
    }
    prev->next=new;
    new->next=cur;
}
int main()
{
    struct node *head1=NULL;
    struct node *head2=NULL;
    struct node *head3=NULL;
    FILE *input1,*input2,*output;
    input1=fopen("input1.txt","r");
    input2=fopen("input2.txt","r");
    if(input1==NULL || input2==NULL)
    {
        perror("Error in opening the file");
        return 1;
    }

    output=fopen("output.txt","w");
    if(output==NULL)
    {
        perror("Errorn in opening the file");
        return 1;
    }
    int coeff,exp;
    while(fscanf(input1,"%d%d",&coeff,&exp)!=EOF)
    {
        addNode(&head1,coeff,exp);
    }
    while(fscanf(input2,"%d%d",&coeff,&exp)!=EOF)
    {
        addNode(&head2,coeff,exp);
    }
    fprintf(output,"First polynomial: ");
    displayPolynomial(head1,output);

    fprintf(output,"Second polynomial: ");
    displayPolynomial(head2,output);

    addPolynomial(&head1,&head2,&head3);
    fprintf(output,"Sum of polynomials: ");
    displayPolynomial(head3,output);
    fclose(output);
}
