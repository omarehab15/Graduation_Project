#include <stdio.h>
#include <stdlib.h>

int prime(int a);
int prime(int a)
{
    int i , j=0;
        for(i=2;i<=a/2;i++)
        {
            if (a%i==0)
            {
                j=1;
                break;
            }
        }
        return j ;
}
int main()
{
    int x,y,z,l;
    printf ("Enter two numbers (intervals):");
    scanf("%d %d",&x,&y);
    printf ("prime numbers between %d and %d are :",x,y);
    for (l=x;l<y;l++)
    {
         z = prime(l);
         if (z==0)
         printf ("%d ",l);
    }
    return 0;
}
