/**
 * @file    :   KPD.c
 * @author  :   Alaa Hisham
 * @brief   :   Configurations for Keypad module
 * @version :   0.0
 * @date    :   07-4-2024
 */

/*===========================================================================================================*/
/*						                            Includes						                         */
/*===========================================================================================================*/
#include "GPIO.h"

#include "KPD_config.h"

/*===========================================================================================================*/
/*						                             Macros						                             */
/*===========================================================================================================*/


/*===========================================================================================================*/
/*						                       Keypad Configurations			                             */
/*===========================================================================================================*/

/**
 * Pin configurations for keypad rows 
 * (Add/remove pins according to the value of KPD_ROWS)
 */
KPD_stPin_t KPD_strRowPins[KPD_ROWS] =
{
    {.port = GPIOB, .pin = GPIO_enuPin9},
    {.port = GPIOB, .pin = GPIO_enuPin10}
    //{.port = GPIOB, .pin = GPIO_enuPin6},
    //{.port = GPIOB, .pin = GPIO_enuPin7}
};

/**
 * Pin configurations for keypad columns 
 * (Add/remove pins according to the value of KPD_COLUMNS)
 */
const KPD_stPin_t KPD_strColPins[KPD_COLUMNS] =
{
    {.port = GPIOB, .pin = GPIO_enuPin5},
    {.port = GPIOB, .pin = GPIO_enuPin6},
    {.port = GPIOB, .pin = GPIO_enuPin7},
    {.port = GPIOB, .pin = GPIO_enuPin8}
};

/**
 * Key values of the keypad
 * (Add/remove rows/columns according to the value of KPD_ROWS & KPD_COLUMNS)
 */
const u8 KPD_u8KeyArr[KPD_ROWS][KPD_COLUMNS] =
{                   /* Col 1 */ /* Col 2 */ /* Col 3 */ /* Col 4 */
    /* Row 1 */    {    'S'     ,    'D'   , 'P' ,'T'},
    /* Row 2 */    {'U' ,    'M'   ,    'O'     ,    0    }
    /* Row 3 */    //{    '1'    ,    '2'    ,    '3'    ,    '-'    },
    /* Row 4 */    //{    'C'    ,    '0'    ,    '='    ,    '+'    }
};
