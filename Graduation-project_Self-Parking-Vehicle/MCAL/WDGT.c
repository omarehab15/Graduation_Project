/*
 * WDGT.c
 *
 *  Created on: Nov 25, 2023
 *      Author: Kareem Abelkader
 */



/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include "WDGT.h"


/******************************************************************************
*                           APIS IMPLEMENTATION			                  *
*******************************************************************************/

void IWDG_set(void)
{
	IWDG->KR &=~ (0xFFFF << 0) ;
	IWDG->KR = 0xCCCC  ;
}

void IWDG_RESET(void)
{
	IWDG->KR &=~ (0xFFFF << 0) ;
	IWDG->KR = 0xAAAA ;
}

void IWDG_time_set(uint32_t pr, uint32_t time)
{

	IWDG->KR &=~ (0xFFFF << 0) ;
	IWDG->KR |= 0x5555 ;

	/*
	 *pr:
	 * 	000: divider /4
		001: divider /8
		010: divider /16
		011: divider /32
		100: divider /64
		101: divider /128
		110: divider /256
	 */

	switch(pr)
	{
	case 0 :
	{
		(IWDG->PR |= (0x000  << 0)) ;
		break;
	}
	case 1 :
	{
		(IWDG->PR |= (0x001 << 0)) ;
		break;
	}
	case 2 :
	{
		(IWDG->PR |= (0x010 << 0)) ;
		break;
	}
	case 3 :
	{
		(IWDG->PR |= (0x011 << 0)) ;
		break;
	}
	case 4 :
	{
		(IWDG->PR |= (0x100 << 0)) ;
		break;
	}
	case 5 :
	{
		(IWDG->PR |= (0x101 << 0)) ;
		break;
	}
	case 6 :
	{
		(IWDG->PR |= (0x110 << 0)) ;
		break;
	}
	}

	uint32_t rlr ;

	switch(pr)
	{
	case 0 :
	{
		 rlr = ((time / 0.1)-1);
		 break;
	}
	case 1 :
	{
		 rlr = ((time / 0.2)-1);
		 break;
	}
	case 2 :
	{
		rlr = ((time / 0.4)-1);
		break;
	}
	case 3 :
	{
		rlr = ((time / 0.8)-1);
		 break;
	}
	case 4 :
	{
		rlr = ((time / 1.6)-1);
		break;
	}
	case 5 :
	{
		rlr = ((time / 3.2)-1);
		break;
	}
	case 6 :
	{
		rlr = ((time / 6.4)-1);
		break;
	}

	}

	IWDG->RLR = rlr ;

}
