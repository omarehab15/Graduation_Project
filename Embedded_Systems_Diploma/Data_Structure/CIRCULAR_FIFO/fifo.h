/*
 * fifo.h
 *
 *  Created on: May 15, 2023
 *      Author: omar
 */

#ifndef FIFO_H_
#define FIFO_H_


#include "stdio.h"
#include "stdint.h"

//user cofiguration
//select the element type (uint8_t , uint16_t , uint32_t)
#define element_type uint8_t
// FIFO data types

typedef struct {
    unsigned int length ;
    unsigned int count ;
    element_type* base ;
    element_type* head ;
    element_type* tail ;
}FIFO_Buf_t;

typedef enum {
    FIFO_no_error ,
    FIFO_Full ,
    FIFO_empty ,
    FIFO_null ,
}FIFO_Buf_status ;

//APIs
FIFO_Buf_status FIFO_init (FIFO_Buf_t* fifo , element_type* buf , uint32_t buf_length );
FIFO_Buf_status FIFO_enqueue (FIFO_Buf_t* fifo , element_type item );
FIFO_Buf_status FIFO_dequeue (FIFO_Buf_t* fifo , element_type* item );
FIFO_Buf_status FIFO_IS_Full (FIFO_Buf_t* fifo );
void FIFO_Print (FIFO_Buf_t* fifo);



#endif /* TEST_H_ */
