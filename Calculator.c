#include <stdio.h>
int main()
{
    int a,b,y;
    char c;
    printf("Enter 2 numbers=\n");
    scanf("%d%d",&a,&b);
    printf("Enter operator=\n");
    scanf("%*c%c",&c);
    switch (c)
    {
    case '+':y=a+b;
        break;
    case '-':y=a-b;
        break;
    case '*':y=a*b;
        break;
    case '/':y=a/b;
        break;
    case '%':y=a%b;
        break;
        
    }
    printf("y=%d",y);
    }