#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,s;
    int y[30];
    printf("Enter no of elements : ");
    scanf("%d",&n);
    printf ("Enter the elements \n");
    for (i = 0 ; i<n ; i++)
    {
        scanf ("%d",&y[i]);
    }
    printf ("Enter the elements to be searched : ");
    scanf ("%d",&s);
     for (i = 0 ; i<n ; i++)
    {
        if (y[i] == s)
        {
            printf ("Number found at the location = %d",i+1);
            break;
        }
    }
    return 0;
}
