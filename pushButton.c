/*
 * pushButton.c
 *
 * Created: 1/17/2020 7:49:54 PM
 *  Author: MENA
 */ 

#include "pushButton.h"
#include "softwareDelay.h"


void pushButtonInit(En_buttonId_t en_butotn_id)
{
	switch (en_butotn_id)
	{
		case BTN_0 :
		gpioPinDirection(BTN_0_GPIO , BTN_0_BIT , INPUT);
		gpioPinWrite(GPIOC , BIT4 ,  HIGH) ;
		//PORTC_DATA = PORTC_DATA |(1<<BTN_0_BIT);
		break;
		case BTN_1 :
		gpioPinDirection(BTN_1_GPIO , BTN_1_BIT , INPUT);
		gpioPinWrite(GPIOB , BIT2 ,  HIGH) ;

		//PORTB_DATA = PORTB_DATA |(1<<BTN_1_BIT);

		break;
		case BTN_2 :
		gpioPinDirection(BTN_2_GPIO , BTN_2_BIT , INPUT);
		gpioPinWrite(GPIOA , BIT2 ,  HIGH) ;

			//PORTA_DATA = PORTA_DATA |(1<<BTN_2_BIT);

		break;
		case BTN_3 :
		gpioPinDirection(BTN_3_GPIO , BTN_3_BIT , INPUT);
		gpioPinWrite(GPIOA , BIT3 ,  HIGH) ;

				//PORTA_DATA = PORTA_DATA |(1<<BTN_3_BIT);

		break;
		

	}
	
	
	
}


En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id)
{
	switch (en_butotn_id)
	{
		case BTN_0 :
			softwareDelayMs(20);
		if (gpioPinRead(BTN_0_GPIO, BTN_0_BIT))
		
			return Released ;
		else 
			return Pressed ;
		break;
		
		case BTN_1 :
		softwareDelayMs(20);
		if (gpioPinRead(BTN_1_GPIO, BTN_1_BIT))
			return Released ;
		else 
			return Pressed ;
		break;
		
		case BTN_2 :
		softwareDelayMs(20);
		if (gpioPinRead(BTN_2_GPIO, BTN_2_BIT))
			return Released ;
		else 
			return Pressed ;
		break;
		
		case BTN_3 :
		softwareDelayMs(20);
		if (gpioPinRead(BTN_3_GPIO, BTN_3_BIT))
			return Released ;
		else 
			return Pressed ;
		break;

	}
}
