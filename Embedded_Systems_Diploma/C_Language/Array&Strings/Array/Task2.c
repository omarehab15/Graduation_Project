#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i;
    float a=0;
    printf("Enter the number of data : ");
    scanf ("%d",&n);
    float x[n];
    for (i=0;i<n;i++)
    {
        printf ("Enter number : ");
        scanf("%f",&x[i]);
    }
    for (i=0;i<n;i++)
    {
        a+=x[i];
    }
    a/=n;
    printf("Average = %.2f",a);
    return 0;
}
