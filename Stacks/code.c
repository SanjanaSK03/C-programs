#include <stdio.h>
#define size 10
struct stack
{
    int e[size];
    int top;
};
int isfull(struct stack *s)
{
    return (s->top == size - 1);

}
int isempty(struct stack *s)
{
    return (s->top == (-1));

}
void push(struct stack *s,int d,FILE *output)
{
    if(isfull(s))
    {
        fprintf(output,"Stack overflow");
        return;
    }
    s->top++;
    s->e[s->top]=d;
    return;
}
int pop(struct stack *s,FILE *output)
{
    if(isempty(s))
    {
        fprintf(output,"Stack underflowflow");
        return 0;
    }  
    int d=s->e[s->top];
    s->top--;
    return d;

}
int peek(struct stack *s)
{
    return s->e[s->top];
}
void display(struct stack *s,FILE *output)
{
    fprintf(output,"Elements in the stack: ");
    for (int i = 0; i <= s->top; i++) {
        fprintf(output,"%d ", s->e[i]);
    }
    fprintf(output,"\n");
}
int sizeOfStack(struct stack *s)
{
    return s->top + 1; 
}


int main()
{
    struct stack s;
    s.top=-1;
    FILE *input,*output;
    input=fopen("input.txt","r");
    int n;
    char c;
    output=fopen("output.txt","w");
    while ((fscanf(input,"%c",&c))==1)
    {
        switch(c)
        {
            case 'A':fscanf(input,"%d",&n);
            push(&s,n,output);
            break;
            case 'B':n=pop(&s,output);
            fprintf(output,"Popped element=%d\n",n);
            break;
            case 'C':n=peek(&s);
            fprintf(output,"Peak element=%d\n",n);
            break;
            case 'D':display(&s,output);
            break;
            case 'S':n=sizeOfStack(&s);
            fprintf(output,"Size=%d\n",n);
            break;
        }
    }
    fclose(input);
    fclose(output);
}