/*
 * lifo.c
 *
 *  Created on: Apr 28, 2023
 *      Author: omar
 */

#include "lifo.h"

LIFO_status LIFO_ADD_item (LIFO_Buf_t* lifo_buf , unsigned int item )
{
	//check if lifo is valid
	if (!lifo_buf -> base || !lifo_buf -> head)
		return LIFO_Null;

	//check if lifo is full
//if (lifo_buf -> head >= (lifo_buf -> base + (lifo_buf ->length)))
				if (lifo_buf -> count == lifo_buf -> length)
					return LIFO_full ;

	// add value
	*(lifo_buf -> head ) = item ;
	lifo_buf -> head++ ;
	lifo_buf -> count++ ;

	return LIFO_no_error ;
}
LIFO_status LIFO_get_item(LIFO_Buf_t* lifo_buf , unsigned int* item )
{
	//check if lifo is valid
		if (!lifo_buf -> base || !lifo_buf -> head)
			return LIFO_Null;

	//check if lifo is empty
	//if (lifo_buf -> head >= (lifo_buf -> base + (lifo_buf ->length)))
			if( lifo_buf -> count == 0)
				return LIFO_empty ;

		// add value
		lifo_buf -> head-- ;
		*item = *(lifo_buf-> head)   ;
		lifo_buf -> count-- ;

		return LIFO_no_error ;
}
LIFO_status LIFO_init(LIFO_Buf_t* lifo_buf , unsigned int* buf, unsigned int length )
{
	if (buf == NULL)
		return LIFO_Null ;
	lifo_buf -> base = buf ;
	lifo_buf -> head  = buf ;
	lifo_buf -> length = length ;
	lifo_buf -> count = 0 ;
	return LIFO_no_error ;
}
