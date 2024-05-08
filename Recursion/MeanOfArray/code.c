#include <stdio.h>
#define max 7

int mean(int a[],int n)
{
    if(n==0)
    {
        return 0;
    }
    else
    {
        return a[n-1]+mean(a,n-1);
    }
}

int main()
{
    int arr[max]={1,2,3,4,5,6,7};
    float m=mean(arr,max);
    printf("Mean of array=%.2f",m/max);
}