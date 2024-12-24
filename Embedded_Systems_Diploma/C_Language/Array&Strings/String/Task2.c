#include <stdio.h>
#include <stdlib.h>

int main()
{

    int i , c = 0;
    char x[100] ;
    printf("Enter a string : ");
    scanf("%s",&x);
    for (i=0;x[i]!='\0';++i)
    {
            c++;
    }
    printf ("Length of string: %d",c);
    return 0;
}
