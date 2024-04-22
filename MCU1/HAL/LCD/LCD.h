/**
 * @file    LCD.h
 * @author  Alaa Hisham
 * @brief   Provides user interface with LCD Module
 * @version 0.0
 * @date    22-3-2024
 */ 


#ifndef LCD_H_
#define LCD_H_

/*===============================================================================*/
/*						               Includes	    		    			     */
/*===============================================================================*/
#include "STD_TYPES.h"
#include "GPIO.h"

/*===============================================================================*/
/*						                Macros	    		    			     */
/*===============================================================================*/

#define	LCD_CLEAR_DISPLAY	    0x01
#define	LCD_CURSOR_INCREMENT	0x06
#define	LCD_RETURN_HOME		    0x02
#define	LCD_CURSOR_BLINK	    0x0e
#define	LCD_CURSOR_SHIFT_LEFT	0x10
#define	LCD_CURSOR_SHIFT_RIGHT	0x14
#define	LCD_CURSOR_LINE1_START	0x80
#define	LCD_CURSOR_LINE2_START	0xc0

#define LCD_FOUR_BIT_MODE	0
#define LCD_EIGHT_BIT_MODE	0x10

#define NOT_DISPLAYED		0
#define DISPLAY_NO_BLINKING	2
#define DISPLAY_BLINKING	3

#define LCD_ONE_LINE	    0
#define LCD_TWO_LINE	    8

#define LCD_5_BY_7	    0
#define LCD_5_BY_10	    4

/*===============================================================================*/
/*	    		    			        Types	    		    			     */
/*===============================================================================*/

typedef enum
{
    CGRAM_BLOCK_0 ,
    CGRAM_BLOCK_1 ,
    CGRAM_BLOCK_2 ,
    CGRAM_BLOCK_3 ,
    CGRAM_BLOCK_4 ,
    CGRAM_BLOCK_5 ,
    CGRAM_BLOCK_6 ,
    CGRAM_BLOCK_7
}LCD_enuCGRAMblock_t;

/*===============================================================================*/
/*	    		    			     LCD APIs	    		    			     */
/*===============================================================================*/

/**
 * @brief Initialize all the Configured LCDs in the LCD_config.c file
 *
 * @return void
 */
void LCD_initAsync(void);

/**
 * @brief Clears the entire LCD screen
 */
STD_enuErrorStatus_t LCD_ClearDisplayAsync(void);

/**
 * @brief Function to move the cursor to a given location on LCD
 * 
 * @param[in] Copy_u8Row : The row of the location on the LCD
 * @param[in] Copy_u8Col : The column of the location on the LCD
 * 
 * @return LCD_enuErrorStatus
 */
STD_enuErrorStatus_t LCD_enuGotoXY(u8 Copy_u8Row, u8 Copy_u8Col);


/**
 * @brief Displays a string of characters on the LCD
 *
 * @param[in] Copy_pchString : A pointer to the string
 * @param[in] Copy_u8StrLen  : The length of the string
 *
 * @return STD_enuErrorStatus_t
 */
STD_enuErrorStatus_t LCD_enuWriteStringAsync(const char *Copy_pchString, u8 Copy_u8StrLen);

/**
 * @brief Write a command to the LCD from the specified LCD commands
 * 
 * @param[in] Copy_u8Command : 
 * 
 * @return STD_enuErrorStatus_t
 */
STD_enuErrorStatus_t LCD_enuWriteCommandAsync(u8 Copy_u8Command);


#endif /* LCD_H_ */