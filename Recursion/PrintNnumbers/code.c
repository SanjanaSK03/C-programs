#include <stdio.h>
void ReverseprintNumbers(int n)
{
    if(n>0)
    {
        printf("%d ",n);
        ReverseprintNumbers(n-1);
    }
}
void printNumbers(int n)
{
    if(n>0)
    {
        printNumbers(n-1);
        printf("%d ",n);
    }
}
int main()
{
    int n;
    printf("Enter n:\n");
    scanf("%d",&n);
    printNumbers(n);
    printf("\n");
    ReverseprintNumbers(n);
}