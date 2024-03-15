#include <stdio.h>
#include <string.h>
#define pi 3.14
int main()
{
    FILE *input,*output;
    input=fopen("input.txt","r");
    int a,b;
    char shape[10];
    if(input==NULL)
    {
        perror("Error in opening file");
        return 1;
    }
    fscanf(input,"%s%d%d",shape,&a,&b);
    float area;
    if(strcmp(shape,"circle")==0)
    {
        area=pi*a*a;
    }
    else if(strcmp(shape,"square")==0)
    {
        area=a*a;
    }
    else if(strcmp(shape,"rectangle")==0)
    {
        area=a*b;
    }
    else if(strcmp(shape,"triangle")==0)
    {
        area=0.5*a*b;
    }
    output=fopen("output.txt","w");
    fprintf(output,"Area=%.2f",area);
    fclose(output);
    return 0;
}