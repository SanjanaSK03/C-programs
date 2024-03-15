#include <stdio.h>
int add(int,int);

int main()
{
   int r1,r2,i1,i2,r,i;
   printf("Enter complex number:\n");
   scanf("%d%d%*c",&r1,&i1);
   printf("Enter complex number:\n");
   scanf("%d%d%*c",&r2,&i2);
   r=add(r1,r2);
   i=add(i1,i2);
   if(i>0|| i==0)
   {
   printf("Sum=%d+%di",r,i);
   }
   else{
    printf("Sum=%d%di",r,i);
   }
}
int add(int a,int b)
{
    return a+b;
}