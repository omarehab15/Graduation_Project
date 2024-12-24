#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a[2][2];
    float b[2][2];
    float x[2][2];
    int i , j ;
    printf ("Enter the elements of 1st matrix:\n");
    for (i=0;i<2;i++)
    {
        for (j=0;j<2;j++)
        {
            printf ("Enter a%d%d:",i+1,j+1);
            scanf("%f",&a[i][j]);
        }
    }
    printf ("Enter the elements of 2nd matrix:\n");
    for (i=0;i<2;i++)
    {
        for (j=0;j<2;j++)
        {
            printf ("Enter b%d%d:",i+1,j+1);
            scanf("%f",&b[i][j]);
        }
    }
    printf ("Sum of Matrix :\n");
    for (i=0;i<2;i++)
    {
        for (j=0;j<2;j++)
        {
            x[i][j]=a[i][j]+b[i][j];
            printf ("%.1f  ",x[i][j]);
        }
        printf ("\n");
    }
    return 0;
}
