#include <stdio.h>
int main()
{
    int n;
    FILE *input,*output;
    input=fopen("input.txt","r");
    if (input==NULL)
    {
        perror("Error in opening the file");
        return 1;
    }
    while(!feof(input))
    {
        fscanf(input,"%d",&n);
    }
    int sum=0;
    int temp;
    while(n!=0)
    {
        temp=n%10;
        sum=sum+temp;
        n=n/10;
    }
    output=fopen("output.txt","w");
    fprintf(output,"%d",sum);
    fclose(output);
    return 0;
}