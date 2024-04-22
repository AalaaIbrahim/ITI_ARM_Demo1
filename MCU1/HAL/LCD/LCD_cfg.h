/**
 * @file    LCD_config.h
 * @author  Alaa Hisham
 * @brief   Contains data types and pre-compile configurations 
 *	        for the system's LCDs
 * @version 0.0
 * @date    22-3-2024
 */ 

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "GPIO.h"
/*===============================================================================*/
/*						                Macros	    		    			     */
/*===============================================================================*/

/*
 * Options:
 *	    LCD_5_BY_7
 *	    LCD_5_BY_10
 */
#define LCD_FONT		LCD_5_BY_7
#define LCD_LINES		LCD_TWO_LINE
#define LCD_COLUMNS		16

/*
 * Options:
 *	    LCD_FOUR_BIT_MODE
 *	    LCD_EIGHT_BIT_MODE
 */
#define LCD_DATA_MODE		LCD_EIGHT_BIT_MODE

/*
 * Options:
 *	    NOT_DISPLAYED
 *	    DISPLAY_NO_BLINKING
 *	    DISPLAY_BLINKING	
 */
#define LCD_CURSOR_MODE		NOT_DISPLAYED


#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE
#define LCD_NUMBER_OF_PINS		    7
#elif LCD_DATA_MODE == LCD_EIGHT_BIT_MODE
#define LCD_NUMBER_OF_PINS		    11
#endif

/*===============================================================================*/
/*	    		    			        Types	    		    			     */
/*===============================================================================*/
typedef struct
{
	void*         port;
	GPIO_enuPin_t pin ;
}LCD_stPin_t;


#endif /* LCD_CONFIG_H_ */