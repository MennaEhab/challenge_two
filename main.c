/*
 * challenge_two_atmel.c
 *
 * Created: 1/17/2020 1:51:27 PM
 * Author : MENA
 */ 

#include "gpio.h"
#include "led.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "sevenSeg.h"

typedef enum status{
	GO,
	STOP,
	GETREADY
}status;

/**
 * Description: Change the LED_0 state to be on for 1 sec as the BTN_0 is pressed
 *
 */

void req2(void)
{
	Led_Init(LED_0);
	
	pushButtonInit(BTN_0);
	
	//softwareDelayMs(1000);
	
	while(1){
		uint32_t count = 0 ;
		Led_Off(LED_0);
		

		if(pushButtonGetStatus(BTN_0)== Pressed){
			
			count = 5;
		}
		
		
		while (count > 0)
		{
			Led_On(LED_0);
			softwareDelayMs(10);
			
			if(pushButtonGetStatus(BTN_0)== Pressed)
			count +=5;
			
			count --;
		}
		
		Led_Off(LED_0);
		
		
		
	}
}




/**
 * Description: function to count from 00 to 99 and display the count on SEG_0 and SEG_1 
	the digit is on display for 1 sec ;
 *
 */

void req1(void){
	
	sevenSegInit(SEG_0);
	sevenSegInit(SEG_1);
	
	while(1) {
	for(uint8_t counter = 0 ; counter < 100 ; counter ++){
	for(uint8_t Dis1Sec = 0 ; Dis1Sec <90 ; Dis1Sec ++){
	
	sevenSegWrite(SEG_1 , counter/10);
	
	sevenSegEnable(SEG_1);
	softwareDelayMs(2);
	sevenSegDisable(SEG_1);
	sevenSegWrite(SEG_0 ,counter-( (counter/10)*10));
	sevenSegEnable(SEG_0);
	softwareDelayMs(2);
	sevenSegDisable(SEG_0);
	
	}
	}
	//
	}
	
}


/**
 * Description: Change the LED_x state (where x 0, 1, 2 ) to be on as the state change
 *
 */


void req3(void){
Led_Init(LED_0);
Led_Init(LED_1);
Led_Init(LED_2);
status myState = GETREADY ;

while(1){	
	switch (myState){
		
		case GETREADY :
		Led_On(LED_0) ;
		softwareDelayMs(370);
		Led_Off(LED_0);
		myState = GO ;
		break; 
		
		case GO :
		Led_On(LED_2);
		softwareDelayMs(370);
		Led_Off(LED_2) ;
		myState = STOP ;
		break;
		
		case STOP : 
		Led_On(LED_1);
		softwareDelayMs(370);
		Led_Off(LED_1) ;
		myState = GETREADY ;
		break;
	}	
}


}




int main(void)
{
    
	/* call each function of req1 , req2 and req3 to test each one of the applications
	 req1 -> for the 7seg application 
	 req2 -> the push buttons and the led 
	 req3-> the state machine 
	*/
			//req1();
			//req2();
			//req3();
		
}

