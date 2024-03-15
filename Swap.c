#include <stdio.h>
int main()
{
    int a,b;
    printf("Enter 2 numbers=\n");
    scanf("%d%d",&a,&b);
    a=a+b;
    b=a-b;
    a=a-b;
    printf("a=%d\n",a);
    printf("b=%d",b);
}