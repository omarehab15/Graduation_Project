#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x ;
    char* y = &x;
    printf("The Alphabets are : \n");
    for (x = 'A';x<='Z';x++)
    {
        printf("  %c  ",*y);
    }
    return 0;
}
