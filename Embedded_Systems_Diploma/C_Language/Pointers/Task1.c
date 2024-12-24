#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m = 29;
    printf("Address of m : 0x%x\n",&m);
    printf("Value of m : %d\n",m);
    int*ab = &m;
    printf("\nNow ab is assigned with the address of m.\n");
    printf("Address of pointer ab :0x%x\n",ab);
    printf("content of pointer ab : %d\n",*ab);
    m = 34;
    printf("\nThe value of assigned to 34 now.\n");
    printf("Address of pointer m :0x%x\n",ab);
    printf("content of pointer m : %d\n",*ab);
    *ab = 7;
    printf("\nThe pointer variable ab is assigned with the value 7 now.\n");
    printf("Address of pointer m :0x%x\n",ab);
    printf("content of pointer m : %d\n",*ab);
    return 0;
}
