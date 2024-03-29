/*
A-Push
P-Pop
D-Display
*/
#include <stdio.h>
#include <stdlib.h>
#define size 10
struct stack
{
    int data;
    struct stack *next;
};
void push(struct stack **top,int d)
{
    struct stack *new;
    new=(struct stack *)malloc(sizeof(struct stack));
    if(new==NULL)
    {
        perror("Error\n");
        return;
    }
    new->data=d;
    new->next=*top;
    *top = new;
}
int pop(struct stack **top)
{
    struct stack *cur=*top;
    int e=cur->data;
    *top=(*top)->next;
    free(cur);
    return e;
}
void displaystack(struct stack *top,FILE *output)
{
    struct stack *cur=top;
    fprintf(output,"Stack: ");
    while(cur)
    {
        fprintf(output,"%d ",cur->data);
        cur=cur->next;
    }
    fprintf(output, "\n");
}
int main()
{
    struct stack *top=NULL;
    FILE *input,*output;
    input=fopen("input.txt","r");
    if(input==NULL)
    {
        perror("Error in opening a file\n");
        return 1;
    }
    int val;
    char ch;
    output=fopen("output.txt","w");
    while((fscanf(input,"%c",&ch))==1)
    {
        switch(ch)
        {
        case 'A':fscanf(input,"%d",&val);
        push(&top,val);
        break;
        case 'P':val=pop(&top);
        fprintf(output,"Popped element=%d\n",val);
        break;
        case 'D':displaystack(top,output);
        break;
        }
    }
    fclose(output);
}