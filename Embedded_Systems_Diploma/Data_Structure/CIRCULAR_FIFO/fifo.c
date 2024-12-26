/*
 * fifo.c
 *
 *  Created on: May 15, 2023
 *      Author: omar
 */

#include "fifo.h"


#define width 5
element_type buff1[width] ;

int main()
{
   FIFO_Buf_t FIFO_UART ;
   element_type i , temp = 0 ;

   if ( FIFO_init( &FIFO_UART , buff1 , 5 ) == FIFO_no_error )
        printf("fifo init-----------Done \n");
   for (i=0 ; i < 7 ; i++ )
   {
       printf (" fifo enqueue (%x) \n ", i );
       if (FIFO_enqueue(&FIFO_UART , i ) == FIFO_no_error)
            printf("\n fifo enqueue ------------- Done \n");
       else
            printf("\n fifo enqueue ------------- Failed \n");

   }

     FIFO_Print(&FIFO_UART);
     if (FIFO_dequeue(&FIFO_UART , &temp) == FIFO_no_error)
        printf("\n fifo dequeue %x ------------- Done \n" , temp );
     if (FIFO_dequeue(&FIFO_UART , &temp) == FIFO_no_error)
        printf("\n fifo dequeue %x ------------- Done \n" , temp );
    FIFO_Print(&FIFO_UART);

    return 0;
}

//APIs
FIFO_Buf_status FIFO_init (FIFO_Buf_t* fifo , element_type* buf , uint32_t buf_length )
{
    if (buf == NULL )
        return FIFO_null ;

    fifo->base = buf ;
    fifo->head = buf ;
    fifo->tail = buf ;
    fifo->length = buf_length ;
    fifo->count = 0 ;

    return FIFO_no_error ;
}
FIFO_Buf_status FIFO_enqueue (FIFO_Buf_t* fifo , element_type item )
{
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_null ;
    if (FIFO_IS_Full(fifo) == FIFO_Full)
        return FIFO_Full ;
    *(fifo->head) = item ;
    fifo->count++ ;
    //circular fifo
    if (fifo->head == (fifo->base + (fifo->length * sizeof(element_type))))
        fifo->head = fifo->base ;
    else
        fifo->head++ ;

    return FIFO_no_error ;
}
FIFO_Buf_status FIFO_dequeue (FIFO_Buf_t* fifo , element_type* item )
{
  if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_null ;
    // check if FIFO is empty
    if (fifo->count == 0)
        return FIFO_empty ;
    *item = *(fifo->tail) ;
     fifo->count-- ;
     // circular FIFO
     if (fifo->tail == (fifo->base + (fifo->length * sizeof(element_type))))
        fifo->tail = fifo->base ;
     else
        fifo->tail++ ;

     return FIFO_no_error ;
}
FIFO_Buf_status FIFO_IS_Full (FIFO_Buf_t* fifo )
{
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_null ;

    if (fifo->count == fifo->length)
        return FIFO_Full ;

    return FIFO_no_error ;
}
void FIFO_Print (FIFO_Buf_t* fifo)
{
    element_type* temp ;
    int i ;
    if (fifo->count == 0)
    {
        printf("FIFO is Empty \n");
    }
    else
    {
        temp = fifo->tail ;
        printf("\n =========== FIFO print ==========\n");
        for (i=0 ; i< fifo->count ; i++ )

        {
            printf("\n %x \n",*temp);
            temp++ ;
        }
        printf("==========================");

    }

}

