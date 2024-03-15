#include <stdio.h>
int main()
{
    char r[5]={'a','b','c','d','e'};
    printf("%d\n",r);
    printf("%c\n",*r);
    printf("%c\n",*(r+1));
    printf("%d\n",*(r));
    printf("%d\n",*(r+1));
}