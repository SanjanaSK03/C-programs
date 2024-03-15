#include <stdio.h>
int main()
{
    FILE *input,*output;
    input=fopen("input.txt","r");
    if(input==NULL)
    {
        perror("Error in opening file");
        return 1;
    }
    int a,b;
    char c;
    while(!feof(input))
    {
        fscanf(input,"%d%c%d",&a,&c,&b);
    }
    int res;

    switch(c)
    {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
        res=a/b;
        break;
        case '%':
        res=a%b;
        break;
    }
    output=fopen("output.txt","w");
    fprintf(output,"%d",res);
    fclose(output);
    return 0;
}
