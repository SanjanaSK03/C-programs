#include <stdio.h>
int bin_to_gray(int n)
{
    
    if(n==0)
    {
        return 0;
    }
    int a=n%10;
    int b=(n/10)%10;
    if(a!=b)
    {
       return 1+10*bin_to_gray(n/10);
    }
    else
    {
       return 10*bin_to_gray(n/10);
    }

    return n;
}

int main()
{
    int b,g;
    printf("Enter b:\n");
    scanf("%d",&b);
    g=bin_to_gray(b);
    printf("Gray number:%d",g);
}