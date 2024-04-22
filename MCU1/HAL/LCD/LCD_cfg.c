/**
 * @file    LCD_config.c
 * @author  Alaa Hisham
 * @brief   Contains post-compile configurations for the system's LCDs
 * @version 0.0
 * @date    22-3-2024
 */ 

/*===============================================================================*/
/*						                Macros	    		    			     */
/*===============================================================================*/
#include "STD_TYPES.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_cfg.h"



#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE

const LCD_stPin_t LCD_stPinArr[LCD_NUMBER_OF_PINS] =
{
/* Data pin 4 */ {.port=GPIOA,.pin=GPIO_enuPin0},
/* Data pin 5 */ {.port=GPIOA,.pin=GPIO_enuPin1},
/* Data pin 6 */ {.port=GPIOA,.pin=GPIO_enuPin2},
/* Data pin 7 */ {.port=GPIOA,.pin=GPIO_enuPin3},
/*   RS pin   */ {.port=GPIOA,.pin=GPIO_enuPin5},
/*   RW pin   */ {.port=GPIOA,.pin=GPIO_enuPin6},
/*   En pin   */ {.port=GPIOA,.pin=GPIO_enuPin7}
};

#elif LCD_DATA_MODE == LCD_EIGHT_BIT_MODE


const LCD_stPin_t LCD_stPinArr[LCD_NUMBER_OF_PINS] =
{
/* Data pin 0 */ {.port=GPIOA,.pin=GPIO_enuPin0},
/* Data pin 1 */ {.port=GPIOA,.pin=GPIO_enuPin1},
/* Data pin 2 */ {.port=GPIOA,.pin=GPIO_enuPin2},
/* Data pin 3 */ {.port=GPIOA,.pin=GPIO_enuPin3},
/* Data pin 4 */ {.port=GPIOA,.pin=GPIO_enuPin4},
/* Data pin 5 */ {.port=GPIOA,.pin=GPIO_enuPin5},
/* Data pin 6 */ {.port=GPIOA,.pin=GPIO_enuPin6},
/* Data pin 7 */ {.port=GPIOA,.pin=GPIO_enuPin7},
/*   RS pin   */ {.port=GPIOB,.pin=GPIO_enuPin12},
/*   RW pin   */ {.port=GPIOB,.pin=GPIO_enuPin13},
/*   En pin   */ {.port=GPIOB,.pin=GPIO_enuPin14}
};

#endif
 