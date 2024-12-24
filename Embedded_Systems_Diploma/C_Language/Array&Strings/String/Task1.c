#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i , c=0;
    char y ;
    char x[100] ;
    printf("Enter a string : ");
    gets (x);
    printf("Enter a character to find frequency : ");
    scanf("%c",&y);
    for (i=0;x[i]!='\0';++i)
    {
        if (x[i]==y)
        {
            c++;
        }
    }
    printf ("Frequency of %c = %d",y,c);
    return 0;
}
