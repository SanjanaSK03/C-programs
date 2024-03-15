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
    int rev=0;
    int temp;
    int num=n;
    while(n!=0)
    {
        temp=n%10;
        rev=(rev*10)+temp;
        n=n/10;
    }
    output=fopen("output.txt","w");
    if(num==rev)
        {
            fprintf(output,"Is a Palindrome");
        }
    else
    {
        fprintf(output,"Is not a Palindrome");
    }
    fclose(output);
    return 0;
}