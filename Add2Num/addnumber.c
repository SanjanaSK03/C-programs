#include <stdio.h>
#define max 25
int main()
{
    int a[max];
    FILE *input,*output;
    input=fopen("input.txt","r");
    if(input==NULL)
    {
        perror("\nError in opening a file\n");
        return 1;
    }
    int i=0;
    int j=0;
    int sum=0;
    while(!feof(input))
    {
        fscanf(input,"%d",&a[i]);
        i++;
    }
    for(j=0;j<i;j++)
    {
        sum=sum+a[j];
    }

    output=fopen("output.txt","w");
    
        fprintf(output,"%d",sum);
    fclose(output);
    return 0;
}