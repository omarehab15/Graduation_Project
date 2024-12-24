#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x[50];
    printf("Input a string : ");
    scanf ("%s",x);
    char*y ;
    int i = strlen(x)-1;
    y = &x[i];
    printf ("Reverse of the string is : ");
    for (i; i >= 0;i--)
    {
        printf("%c",*y);
        y--;
    }
    return 0;
}
