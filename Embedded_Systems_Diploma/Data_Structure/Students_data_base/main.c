/*
 * main.c
 *
 *  Created on: May 17, 2023
 *      Author: omar
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"



// students data
struct Sdata
{
	int ID ;
	char name[40] ;
	float height ;
};

// linked list mode
struct SStudent
{
	struct Sdata Student;
	struct SStudent* PNextstudent ;
};

struct SStudent* gpFirstStudent= NULL ;

void fill_the_record (struct SStudent* new_student)
{
	char temp_text [40];

	// enter student ID
	printf ("\n Enter the ID : ");
	gets (temp_text);
	new_student -> Student.ID = atoi (temp_text);

	// enter student name
	printf (" Enter the student Full name  : ");
	gets (new_student -> Student.name);

	// enter student height
	printf (" Enter the student heigt  : ");
	gets (temp_text);
	new_student -> Student.height = atof (temp_text);

}

void Add_student ()
{

	struct SStudent* plast_student ;
	struct SStudent* pnew_student ;

	if (gpFirstStudent == NULL) // if the list is empty
	{
		// create the first record
		pnew_student = (struct SStudent*) malloc (sizeof(struct SStudent)) ;
		//AAssign the gpFirstStudent to it
		gpFirstStudent = pnew_student ;

	}
	else //if the list contains records
	{
		//navigate until reach to the last record
		plast_student = gpFirstStudent ;
		while (plast_student -> PNextstudent)
			plast_student = plast_student -> PNextstudent ;

		//create new record and assign pnext to it
		pnew_student = (struct SStudent*) malloc (sizeof(struct SStudent)) ;
		plast_student -> PNextstudent  = pnew_student ;

	}

	//fill the new record
	fill_the_record(pnew_student);

	//set the record to NULL
	pnew_student ->PNextstudent = NULL ;
}

int delete_student ()
{
	char temp_text[40] ;
	int selected_id;

	//get selected recorded ID from user
	printf("\n Enter student ID to be deleted : ");
	gets(temp_text);
	selected_id = atoi(temp_text);

	if (gpFirstStudent)//there are records
	{
		struct SStudent* pPreviousStudent = NULL ;
		struct SStudent* pSelectedStudent = gpFirstStudent ;

		//loop on all records
		while (pSelectedStudent)
		{

			//compare the record ID with the selected ID
			if (pSelectedStudent->Student.ID == selected_id)
			{
				if (pPreviousStudent)
				{
					pPreviousStudent-> PNextstudent = pSelectedStudent ->PNextstudent;
				}
				else
				{
					gpFirstStudent = pSelectedStudent->PNextstudent;
				}
				free(pSelectedStudent);
				return 1; //find it
			}
			// store previous record pointer
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->PNextstudent;


		}
	}
	printf("\n cannot find student ID : ");
	return 0 ; //can't find it
}


void view_students ()
{
	int count = 0 ;
	struct SStudent* pCurrentStudent = gpFirstStudent ;
	if (gpFirstStudent == NULL)
		printf("\n Empty list ");

	while (pCurrentStudent)
	{
		printf("\n Record Number %d ", count+1);
		printf("\n ID : %d " ,pCurrentStudent->Student.ID );
		printf("\n Name : %s " , pCurrentStudent->Student.name );
		printf("\n Height : %f " , pCurrentStudent->Student.height);
		pCurrentStudent = pCurrentStudent->PNextstudent ;
		count++ ;
	}
}

void DeleteAll ()
{
	struct SStudent* pCurrentStudent = gpFirstStudent ;
	if (gpFirstStudent)
		printf("\n Empty list ");
	while (pCurrentStudent)
	{
		struct SStudent* pTempStudent = pCurrentStudent ;
		pCurrentStudent = pCurrentStudent->PNextstudent ;
		free (pTempStudent);

	}
	gpFirstStudent = NULL ;
}


int main ()
{
	char temp_text[40];

	while(1)
	{
		printf("\n ============================");
		printf("\n Choose one of the following options \n ");
		printf("\n 1 : AddStudent  ");
		printf("\n 2 : Delete_Student  ");
		printf("\n 3 : view_students ");
		printf("\n 4 : DeleteAll  ");
		printf("\n Enter Option Number : ");

		gets(temp_text);
		printf("\n ============================");
		switch (atoi (temp_text))
		{
		case 1:
			Add_student ();
			break;
		case 2 :
			delete_student ();
			break ;
		case 3 :
			view_students ();
			break ;
		case 4 :
			DeleteAll ();
			break ;
		default :
			printf("\n wrong option ");
			break ;
		}

	}

	return 0 ;
}
