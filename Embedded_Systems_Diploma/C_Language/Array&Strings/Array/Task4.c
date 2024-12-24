#include <stdio.h>
#include <stdlib.h>

int main()
{
    int e , i , l ,n ;
    int y [30];
    printf ("Enter the no. of elements : ");
    scanf ("%d",&n);
    printf ("Enter elements : \n");
    for (i=0;i<n;i++)
    {
        scanf("%d",&y[i]);
    }
    printf ("Enter the element to be inserted : ");
    scanf ("%d",&e);
    printf ("Enter the location : ");
    scanf ("%d",&l);
    for ( i = n ; i >= l; i--)
    {
        y[i] = y[i-1];
    }
    n++;
    y[l-1]=e;
    for (i=0;i<n;i++)
    {
        printf (" %d ",y[i]);
    }
    return 0;
}
