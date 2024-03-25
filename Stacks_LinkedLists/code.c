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
void displaystack(struct stack *top)
{
    struct stack *cur=top;
    while(cur)
    {
        printf("%d\n",cur->data);
        cur=cur->next;
    }
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
    int i=0;
    int a[size];
    while((fscanf(input,"%d",&a[i]))==1)
    {
        i++;
    }
    int j=0;
    for(j=0;j<i;j++)
    {
        push(&top,a[j]);
    }
    displaystack(top);
    int val;
    val=pop(&top);
    printf("Popped element=%d\n",val);
    printf("After popping:\n");
    displaystack(top);
    val=pop(&top);
    printf("Popped element=%d\n",val);
    printf("After popping:\n");
    displaystack(top);
    val=pop(&top);
    printf("Popped element=%d\n",val);
    printf("After popping:\n");
    displaystack(top);
}