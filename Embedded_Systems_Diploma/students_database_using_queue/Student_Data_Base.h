/*
 * Student_Data_Base.h
 *
 *  Created on: Sep 27, 2024
 *      Author: omar Ehab
 */

#ifndef STUDENT_DATA_BASE_H_
#define STUDENT_DATA_BASE_H_

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include"stdio.h"
#include "stdlib.h"
#include "string.h"


/******************************************************************************
 *                                 MACROs			                          *
 *******************************************************************************/
#define DPRINTF(...)      {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}

/******************************************************************************
 *                               Structure			                          *
 *******************************************************************************/
typedef struct{
	char F_Name[50];
	char L_Name[50];
	int roll_NUM ;
	float GPA ;
	int Course_ID [10];

}St;

St students[55] ;

/**********************************************/
typedef struct {
	St *head ;
	St *tail ;
	St *base ;
	St *counter ;
	St *length ;
}Qeue;

typedef enum {
	fifo_no_error ,
	fifo_full ,
	fifo_empty ,
	fifo_null ,
	fifo_error ,
}fifo_State;
/******************************************************************************
 *                                 APIs				                          *
 *******************************************************************************/
int roll_num_check(Qeue* fifo , int x);								//to check if the roll number is exist
fifo_State fifo_init(Qeue* fifo, St* buffer , int length); 			//to initialize FIFO buffer
fifo_State add_student_by_file(Qeue* fifo); 									//to add student for other file
fifo_State add_Student_Manually(Qeue* fifo);									//to add student Manually
fifo_State find_Student_by_Roll_NUM(Qeue* fifo);								//to find student using roll number
fifo_State find_Student_by_First_Name(Qeue* fifo);							//to find student using First name
fifo_State find_Student_Course(Qeue* fifo);
fifo_State Total_Student_NUM(Qeue* fifo);
fifo_State Delete_Student(Qeue* fifo);
fifo_State Update_Student_Info(Qeue* fifo);
fifo_State Show_All_Student(Qeue* fifo);
fifo_State buffer_shift(int index , Qeue* fifo);

#endif /* STUDENT_DATA_BASE_H_ */
