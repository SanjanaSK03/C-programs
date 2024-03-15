#include <stdio.h>
void readMatrix(int[][10],int,int);
void Matrix(int[][10],int,int);
void printMatrix(int[][10],int,int);
void MultiplyMatrix(int[][10],int[][10],int[][10],int,int,int,int);

int main()
{
    int a[10][10],b[10][10],c[10][10];
    int n,m,x,y; //let m,n be the order of matrices
    printf("Enter order of matrices:");
    scanf("%d%d",&m,&n);
    printf("Enter order of matrices:");
    scanf("%d%d",&x,&y);
    readMatrix(a,m,n);
    readMatrix(b,m,n);
    Matrix(c,m,y);
    printf("Matrix a=\n");
    printMatrix(a,m,n);
    printf("Matrix b=\n");
    printMatrix(b,x,y);
    MultiplyMatrix(c,a,b,m,n,x,y);
    printf("Product=\n");
    printMatrix(c,m,n);
    
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
void Matrix(int a[][10],int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=0;
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
void MultiplyMatrix(int c[][10],int a[][10],int b[][10],int m,int n,int x,int y)
{
    int i,j,k;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<m;k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }

        }
    }

}
