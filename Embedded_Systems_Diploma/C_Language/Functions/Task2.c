#include <stdio.h>
#include <stdlib.h>
int factorial (int x);
int factorial (int x)
{
    if (x!=1)
    {
      return x * factorial(x-1);
    }
}
int main()
{
    int y ,fact;
    printf ("Enter an positive integer : ");
    scanf("%d",&y);
    fact = factorial(y);
    printf("\nFactorial of %d = %d\n",y,fact);
    return 0;
}
