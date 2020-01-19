/*
 * sevenSeg_BCD.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Sprints
 */

#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include "gpio.h"
#include "sevenSegConfig.h"


typedef enum En_SevenSegId_t{
	SEG_0,
	SEG_1,
}En_SevenSegId_t;

/**
 * Description: initialize the seg_x pins state to output ( 4 bits for data ,the enable bit ,the decimal bit)
 * @param a_segment_id : The seg to be initialized and it takes
 * 				  one of the enum (En_sevensegd_t) parameters
 */
void sevenSegInit(En_SevenSegId_t a_segment_id);

/**
 * Description: write high on the enable pin of the required  seg
  
 * @param :the seg to be enabled and it takes
 * 				  one of the enum (En_sevensegd_t) parameters
 */
void sevenSegEnable(En_SevenSegId_t en_segment_id);

/**
 * Description: disable the seg
 * @param:the seg to be enabled and it takes
 * 				  one of the enum (En_sevensegd_t) parameters 
 */
void sevenSegDisable(En_SevenSegId_t en_segment_id);

/**
 * Description:  write the required number on the 4 pins connected to seg 
 * @param en_segment_id  : the seg to display on and it takes
 * 				  one of the enum (En_sevensegd_t) parameters
 * @param u8_number : the value of the digit to display on seg
 */
void sevenSegWrite(En_SevenSegId_t en_segment_id, uint8_t u8_number);


#endif /* SEVENSEG_BCD_H_ */
