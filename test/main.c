#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	P1->DIR |= BIT0;//����Ϊ���
	 P1->DIR &= BIT0;//����Ϊ���
	while(1)
   {

    }
}
