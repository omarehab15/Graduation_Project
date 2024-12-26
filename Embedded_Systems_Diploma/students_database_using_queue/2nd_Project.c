/*
 ============================================================================
1 Name        : 2nd_Project.c
 Author      : Omar Ehab
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Student_Data_Base.h"

int main(void)
{
	int x ;
	Qeue buffer ;
	fifo_init(&buffer , students , 55);
	DPRINTF("Welcome to the student Management System \n");

	while(1)
	{
		DPRINTF("--------------------------------------------\n");
		DPRINTF("Choose The Task that you want to perform\n");
		DPRINTF("1. Add the Student Details Manually\n");
		DPRINTF("2. Add the Student Details From Text File\n");
		DPRINTF("3. Find the Student Details by Roll Number\n");
		DPRINTF("4. Find the Student Details by First Name\n");
		DPRINTF("5. Find the Student Details by Course ID\n");
		DPRINTF("6. Find the Total number of Students\n");
		DPRINTF("7. Delete the Student Details by Roll Number \n");
		DPRINTF("8. Update the Student Details by Roll Number \n");
		DPRINTF("9. Show all information\n");
		DPRINTF(" Enter your choice to perform the task\n");
		scanf("%d",&x);
		switch(x)
		{
		case 1 :
		{
			add_Student_Manually(&buffer);
			break;
		}
		case 2 :
		{
			add_student_by_file(&buffer);
			break;
		}
		case 3 :
		{
			find_Student_by_Roll_NUM(&buffer);
			break;
		}
		case 4 :
		{
			find_Student_by_First_Name(&buffer);
			break;
		}
		case 5 :
		{
			find_Student_Course(&buffer);
			break;
		}
		case 6 :
		{
			Total_Student_NUM(&buffer);
			break;
		}
		case 7 :
		{
			Delete_Student(&buffer);
			break;
		}
		case 8 :
		{
			Update_Student_Info(&buffer);
			break;
		}
		case 9 :
		{
			Show_All_Student(&buffer);
			break;
		}
		default :
		{
			DPRINTF("Wrong choice\n");

		}
		}

	}

	return 0 ;
}
