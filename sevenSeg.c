/*
 * sevenSeg.c
 *
 * Created: 1/18/2020 5:07:51 PM
 *  Author: MENA
 */ 
#include "sevenSeg.h"

void sevenSegInit(En_SevenSegId_t a_segment_id);
void sevenSegEnable(En_SevenSegId_t en_segment_id);
void sevenSegDisable(En_SevenSegId_t en_segment_id);
void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number);



void sevenSegInit(En_SevenSegId_t a_segment_id)
{
	gpioPinDirection(SEG_BCD_GPIO , SEG_BCD_DP_BIT , OUTPUT);
	gpioPinDirection(SEG_BCD_DP_GPIO , SEG_BCD_DP_BIT , OUTPUT);
	
	switch (a_segment_id) 
	{
		
		case SEG_0 : 
		
		gpioPinDirection(SEG_EN1_GPIO , SEG_EN1_BIT , OUTPUT);
		gpioPinWrite(SEG_EN1_GPIO , SEG_EN1_BIT , LOW);
		break;
		
		
		
		case SEG_1 :
		
		gpioPinDirection(SEG_EN2_GPIO , SEG_EN2_BIT , OUTPUT);
		gpioPinWrite(SEG_EN1_GPIO , SEG_EN2_BIT , LOW);
		break;

		
	}
	
}


void sevenSegEnable(En_SevenSegId_t en_segment_id)
{
	
	
	switch (en_segment_id)
	{
		
		case SEG_0 :
		
		gpioPinWrite(SEG_EN1_GPIO , SEG_EN1_BIT, HIGH);
		break;
		
		case SEG_1 :
		
		gpioPinWrite(SEG_EN2_GPIO , SEG_EN2_BIT, HIGH);
		break;
		
	}
	
}


void sevenSegDisable( En_SevenSegId_t en_segment_id)
{
	switch (en_segment_id)
	{
		
		case SEG_0 :
		
		gpioPinWrite(SEG_EN1_GPIO , SEG_EN1_BIT, LOW);
		break;
		
		case SEG_1 :
		
		gpioPinWrite(SEG_EN2_GPIO , SEG_EN2_BIT, LOW);
		break;
		
	}
}


void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number)
{
	switch (en_segment_id)
	{
		
		case SEG_0 :
		
		gpioPinWrite(SEG_BCD_GPIO , SEG_BCD_BITS, u8_number);
		break;
		
		case SEG_1 :
		
		gpioPinWrite(SEG_BCD_GPIO , SEG_BCD_BITS, u8_number);
		break;
		
	}
}
