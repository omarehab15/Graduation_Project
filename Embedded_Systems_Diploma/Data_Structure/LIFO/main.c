/*
 * main.c
 *
 *  Created on: Apr 28, 2023
 *      Author: omar
 */
#include "lifo.h"

unsigned int buffer1[5]; //5*4 = 20 bytes

int main (s)
{
	int i , temp = 0;
	LIFO_Buf_t Uart_lifo , I2C_lifo ;

	//static allocation
	LIFO_init (&Uart_lifo ,buffer1 , 5);

	//dynamic allocation
	unsigned int* buffer2 = (unsigned int*) malloc(5 * sizeof(unsigned int));
	LIFO_init (&I2C_lifo ,buffer2 , 5);

	for (i=0 ;i<5 ;i++)
		{
			if(LIFO_ADD_item(&Uart_lifo,i) == LIFO_no_error)
				printf(" UART_LIFO add : %d \n",i);
		}

	for (i=0 ;i<5 ;i++)
		{
			if (LIFO_get_item(&Uart_lifo,&temp) == LIFO_no_error)
				printf("UART_LIFO get : %d \n",temp);
		}

	return 0 ;
}
