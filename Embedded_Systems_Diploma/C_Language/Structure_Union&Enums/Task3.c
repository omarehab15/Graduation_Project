#include <stdio.h>
#include <stdlib.h>

struct comp
{
    float real;
    float imag;
}num1,num2,sum;
struct comp add(struct comp x1 ,struct comp x2 )
{
    struct comp s;
    s.real = x1.real + x2.real;
    s.imag = x1.imag + x2.imag;
    return s ;
}
int main()
{
    printf("For 1st complex number.\n");
    printf("Enter real and imaginary respectively : ");
    scanf("%f %f",&num1.real,&num1.imag);
    printf("For 2nd complex number.\n");
    printf("Enter real and imaginary respectively : ");
    scanf("%f %f",&num2.real,&num2.imag);
    sum = add(num1,num2);
    printf("Sum = %.1f + %.1fi\n",sum.real,sum.imag);
    return 0;
}
