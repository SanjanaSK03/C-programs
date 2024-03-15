#include <stdio.h>
void readMatrix(int[][10],int,int);
void printMatrix(int[][10],int,int);
void addMatrix(int[][10],int[][10],int[][10],int,int);
void subtractMatrix(int[][10],int[][10],int[][10],int,int);
int main()
{
    int a[10][10],b[10][10],c[10][10],d[10][10];
    int n,m; //let m,n be the order of matrices
    printf("Enter order of matrices:");
    scanf("%d%d",&m,&n);
    readMatrix(a,m,n);
    readMatrix(b,m,n);
    printf("Matrix a=\n");
    printMatrix(a,m,n);
    printf("Matrix b=\n");
    printMatrix(b,m,n);
    addMatrix(c,a,b,m,n);
    subtractMatrix(d,a,b,m,n);
    printf("Sum=\n");
    printMatrix(c,m,n);
    printf("Difference=\n");
    printMatrix(d,m,n);
}
void readMatrix(int a[][10],int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
}
void printMatrix(int a[][10],int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}
void addMatrix(int c[][10],int a[][10],int b[][10],int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            c[i][j]=a[i][j]+b[i][j];
        }
    }

}
void subtractMatrix(int c[][10],int a[][10],int b[][10],int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            c[i][j]=a[i][j]-b[i][j];
        }
    }

}