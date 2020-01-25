/*
 * timers.c
 *
 * Created: 1/21/2020 1:52:53 PM
 *  Author: MENA
 */ 

#include "timers.h"
#include <avr/interrupt.h>
#include "led.h"
//#include "interupt.h"



#define F_CPU 16000000.0 

uint16_t  global_prescale ;
uint16_t global_prescale1 ;
uint16_t global_prescale2 ;
volatile int32_t global_input_0 ;
uint16_t prescalerValue =  1;
uint8_t x = 1 ;

void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal,
				 uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
				 {
					 
					 TCCR0 =  0 ;
					 TCCR0 = en_mode | en_OC0 ; 
					 //TCNT0 = u8_initialValue ;
					 timer0Set(u8_initialValue) ;
					 OCR0 = u8_outputCompare ;
					 TIMSK |= en_interruptMask ;
					 
					 global_prescale = en_prescal ;
					 
					/* switch (en_prescal){
						 
						 case t0_prescaler_8 : prescalervalue = 8 ;
						 break;
						 case t0_prescaler_64 : prescalervalue = 64 ;
						 break;
						 case t0_prescaler_256 : prescalervalue = 256 ;
						 break;
						 case t0_prescaler_1024 : prescalervalue = 1024 ;
						 break;
						 	 
					 }
					 timetotalticksms = ((double)(prescalervalue/(f_cpu))*256*1000.0);	 
					 timetotalticksus = ((double)(prescalervalue/(f_cpu))*256*1000.0*1000.0);
					 */
				 }


void timer0Set(uint8_t u8_value) 
		{
			TCNT0 = u8_value ;
		}		
						
uint8_t timer0Read(void){
	
		return TCNT0 ;
	
}
		
void timer0Start(void)
		{
			TCCR0 |= global_prescale ; 
		}

void timer0Stop(void)
		{
			TCCR0 &= T0_NO_CLOCK ;
		}
		
void timer0DelayMs(uint16_t u16_delay_in_ms){
	
	timer0Init(T0_COMP_MODE,T0_OC0_CLEAR,T0_PRESCALER_64, 0 , 250 ,T0_POLLING) ;
	
	TCNT0 = 12;
	// no of ticks for one milli sec 
	
	timer0Start();
	while (u16_delay_in_ms)
	{
		if(TIFR&0x02)
		{
			u16_delay_in_ms -- ;
			TCNT0 = 0 ;	
			TIFR |=0x02 ;
		}
		
	}
	timer0Stop();

}

void timer0DelayMs2(uint16_t u16_delay_in_ms){
	
	global_input_0 = u16_delay_in_ms ;

	timer0Init(T0_COMP_MODE,T0_OC0_SET,T0_PRESCALER_64, 0 , 250 ,T0_INTERRUPT_CMP) ;
	
	sei();
	TCNT0 =10;
	timer0Start();
	
	while(1)
	{
		if (global_input_0<=0)
		{
			timer0Stop();
			break;
		}
		
	}
	
}


	
		
void timer0DelayUs(uint32_t u32_delay_in_us)
		{			
/*
				TCNT0 = 10;
				 no of ticks for one milli sec
				TCNT0 = 1;
				*/
		/*		timer0Start();
							
				while (u32_delay_in_us)
				{
					if(TIFR&0x02)
					{
						u32_delay_in_us -- ;
						TCNT0 = 0 ;
						TIFR |=0x02 ;
					}
					
				}
				timer0Stop();	*/
		global_input_0 = u32_delay_in_us;
		sei();
		timer0Init(T0_COMP_MODE, T0_OC0_CLEAR , T0_NO_CLOCK , 0, 16, T0_INTERRUPT_CMP);
		
		timer0Start();
		
		while(global_input_0);
		
		timer0Stop();
		
		}

ISR(TIMER0_COMP_vect){
	
	global_input_0 -- ;
	

	
	
}

void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, 
				uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,
				uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask){
					
					TCCR1 = 0 ;		
					global_prescale1 = en_prescal ;
					TCCR1 = en_mode | en_OC ;
					timer1Set(u16_initialValue) ;
					OCR1A = u16_outputCompareA ;
					OCR1B = u16_outputCompareB ;
					TIMSK |= en_interruptMask ; 
					
				}
				
				
				
void timer1Set(uint16_t u16_value){
	TCNT1 = u16_value ;
	
}

uint16_t timer1Read(void){
	
	return TCNT1 ;
	
}

void timer1Start(void){
	
	TCCR1 |= global_prescale1 ;
	
}

void timer1Stop(void){
	
	TCCR1 = T1_NO_CLOCK ;
}

void timer1DelayMs(uint16_t u16_delay_in_ms){
	
		timer1Init(T1_COMP_MODE_OCR1A_TOP, T1_OC1A_CLEAR ,T1_PRESCALER_64, 0 , 250 , 0, 0 , T2_POLLING) ;
		// for the time taken by the timer Init function 
		TCNT1 = 29;
		// no of ticks for one milli sec
		timer1Start();
		while (u16_delay_in_ms)
		{
			if(TIFR&0x10)
			{
				u16_delay_in_ms -- ;
				TCNT1 = 0 ;
				TIFR |=0x10 ;
			}	
		}
		timer1Stop();
	
}

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, 
				uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, 
				En_timer2Interrupt_t en_interruptMask){
					
					ASSR &= 0xF0 ;  
					TCCR2 =  0 ;
					TCCR2 = en_mode | en_OC ;
					//TCNT0 = u8_initialValue ;
					timer2Set(u8_initialValue) ;
					OCR2 = u8_outputCompare ;
					TIMSK |= en_interruptMask ;
					
					global_prescale2 = en_prescal ;
					
					}

void timer2Set(uint8_t u8_a_value){
	
	TCNT2 = u8_a_value ;
	
}

uint8_t timer2Read(void){
	
	return TCNT2 ;
	
}

void timer2Start(void){
	
	TCCR2 |= global_prescale2 ;
}

void timer2Stop(void){
	
	TCCR0 &= T0_NO_CLOCK ;
	
}

void timer2DelayMs(uint16_t u16_delay_in_ms){
	
	
	timer2Init(T2_COMP_MODE,T2_OC2_CLEAR,T2_PRESCALER_64, 0 , 250, 0,T2_POLLING) ;

	TCNT2 = 12;
	// no of ticks for one milli sec
	timer2Start();
	while (u16_delay_in_ms)
	{
		if(TIFR&0x80)
		{
			u16_delay_in_ms -- ;
			TCNT2 = 0 ;
			TIFR |=0x80 ;
		}
		
	}
	timer2Stop();
}

