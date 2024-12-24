#include <stdio.h>
#include <stdlib.h>
#include "string.h"
int main()
{
    char x [100];
    char y [100];
    int i,j,l;
    printf("Enter the string : ");
    scanf("%s",x);
    j=strlen(x);
    l=j-1;
    for (i=0;i<j;i++)
    {
       y[i]=x[l] ;
       l--;
    }
    printf ("Reverse string is : %s\n",y);
    return 0;
}
