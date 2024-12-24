#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x , i;
    printf("Input the number of elements to store in the array (max 15): ");
    scanf("%d",&x);
    int arr[x];
    int *ptr = arr ;
    printf("Input %d number of elements in the array : \n",x);
    for (i=0; i < x ;i++)
    {
        printf("element-%d : ",i+1);
        scanf("%d",ptr);
        ptr++;
    }
    ptr--;
    printf("The elements of array in reverse order are : \n");
    for (i = x ; i > 0 ; i--)
    {
        printf("element-%d : %d\n",i,*ptr);
        ptr--;
    }
    return 0;
}
