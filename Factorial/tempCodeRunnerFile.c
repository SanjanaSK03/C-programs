#include <stdio.h>
int main()
{
    int num;
    FILE *input,*output;
    int fact=1;
    input=fopen("input.txt","r");
    if(input==NULL)
    {
        perror("\nError in opening the file\n");
        return 1;
    }
    fscanf(input,"%d",&num);
    for (int i = 1; i <= num; i++) 
    {
    fact=fact*i;
    }

    output=fopen("output.txt","w");
    fprintf(output,"%d",fact);
    return 0;
}