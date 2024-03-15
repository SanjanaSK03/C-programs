#include <stdio.h>
#define max 10
int main()
{
    int num;
    FILE *input,*output;
    input=fopen("input.txt","r");
    if(input==NULL)
    {
        perror("\nError in opening the file\n");
        return 1;
    }
    fscanf(input,"%d",&num);
    int a=-1;
    int b=1;
    int x[max];
    int j=0,c;
    for (int i = 0; i <num; i++) 
    {
        c=a+b;
        a=b;
        b=c;
        x[j]=c;
        j++;
    }

    output=fopen("output.txt","w");
    for(int i=0;i<j;i++)
    {
        fprintf(output,"%d ",x[i]);
    }
    return 0;
}