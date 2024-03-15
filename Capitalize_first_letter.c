#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i;
    char s[100];
    printf("Enter string:");
    scanf("%[^\n]s", s);
    printf("%s\n",s);
    for(i=0;s[i]!='\0';i++)
    {
     
          if(s[i-1]==' '|| i==0)
          {
               s[i]=s[i]-32;
          }
         
    }
   printf("%s\n",s);
}