#include <stdio.h>
#include <stdlib.h>
int power (int b , int p);
int s=1;
int power (int b , int p)
{
    if (p > 0)
    {
       s*=b;
       --p;
       power(b,p);
    }
    return s;
}
int main()
{
    int x,y,l;
    printf("Enter base number : ");
    scanf("%d",&x);
    printf("Enter power number (positive integer): ");
    scanf("%d",&y);
    l= power (x,y);
    printf("%d ^ %d = %d",x,y,l);
    return 0;
}
