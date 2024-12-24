#include <stdio.h>
#include <stdlib.h>
struct student
{
    char name[50];
    int roll ;
    float marks ;
}gx[10];
int main()
{
    int i ;
    printf("Enter information of student:\n");
    for (i=0;i<10;i++)
    {
        gx[i].roll = i+1;
        printf("For roll number %d\n",gx[i].roll);
        printf("Enter name : ");
        scanf("%s",&gx[i].name);
        printf("Enter marks : ");
        scanf("%f",&gx[i].marks);
        printf("\n");
    }
    printf("Displaying information of students : \n");
     for (i=0;i<10;i++)
    {
        printf("Information for roll number %d\n",gx[i].roll);
        printf("Name : %s\n",gx[i].name);
        printf("Enter marks : %.1f\n",gx[i].marks);
        printf("\n");
    }
    return 0;
}
