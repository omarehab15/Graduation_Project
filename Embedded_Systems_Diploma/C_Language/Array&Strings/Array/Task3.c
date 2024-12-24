#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n ,l,i,j;
    printf ("Enter rows and column of matrix : ");
    scanf ("%d %d",&n,&l);
    float x[n][l];
    float y[l][n];
    for (i=0;i<n;i++)
    {
        for (j=0;j<l;j++)
        {
            printf ("Enter elements a%d%d: ",i,j);
            scanf("%f",&x[i][j]);
        }
    }
    printf ("Entered Matrix : \n");
     for (i=0;i<n;i++)
    {
        for (j=0;j<l;j++)
        {
            printf ("%0.1f  ",x[i][j]);
        }
        printf ("\n");
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<l;j++)
        {
           y[j][i]=x[i][j];
        }
    }
     printf ("Transposed Matrix : \n");
     for (i=0;i<l;i++)
    {
        for (j=0;j<n;j++)
        {
            printf ("%0.1f  ",y[i][j]);
        }
        printf ("\n");
    }

    return 0;
}
