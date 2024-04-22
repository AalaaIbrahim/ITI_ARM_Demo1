/**
 * @file    :   KPD.c
 * @author  :   Alaa Hisham
 * @brief   :   API Implementations for Keypad module
 * @version :   0.0
 * @date    :   07-04-2024
 */

/*===========================================================================================================*/
/*						                             Includes						                         */
/*===========================================================================================================*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC.h"
#include "GPIO.h"

#include "KPD.h"
#include "KPD_private.h"
#include "KPD_config.h"

/*===========================================================================================================*/
/*						                             Macros						                             */
/*===========================================================================================================*/

#if KPD_INPUT_PINS == KPD_ROW_PINS
    #define NUMBER_OF_INPUT_PINS    KPD_ROWS
    #define NUMBER_OF_OUTPUT_PINS   KPD_COLUMNS
#elif KPD_INPUT_PINS == KPD_COL_PINS
    #define NUMBER_OF_INPUT_PINS    KPD_COLUMNS
    #define NUMBER_OF_OUTPUT_PINS   KPD_ROWS
#else
#error "Invalid Configuration!"
#endif   

#if (KPD_INPUT_PULL_TYPE == INTERNAL_PULLDOWN) || (KPD_INPUT_PULL_TYPE == EXTERNAL_PULLDOWN)
    #define KEY_PRESSED         1
    #define KEY_RELEASED        0
    #define OUT_KEY_ACTIVATED   1
    #define OUT_KEY_DEACTIVATED 0
#elif (KPD_INPUT_PULL_TYPE == INTERNAL_PULLUP) || (KPD_INPUT_PULL_TYPE == EXTERNAL_PULLUP)
    #define KEY_PRESSED         0
    #define KEY_RELEASED        1
    #define OUT_KEY_ACTIVATED   0
    #define OUT_KEY_DEACTIVATED 1
#else
#error "Invalid Configuration!"
#endif

#define KPD_DEBOUNCE_COUNT      6

/*===========================================================================================================*/
/* 				                              Global Variables					                             */
/*===========================================================================================================*/
extern const KPD_stPin_t KPD_strRowPins[KPD_ROWS];
extern const KPD_stPin_t KPD_strColPins[KPD_COLUMNS];
extern const u8 KPD_u8KeyArr[KPD_ROWS][KPD_COLUMNS];
static const KPD_stPin_t* KPD_pstrInputPins = NULL;
static const KPD_stPin_t* KPD_pstrOutputPins = NULL;
static u8 KPD_u8PressedKey = NO_KEY_PRESSED;

/*===========================================================================================================*/
/* 				                             API Implementations 				                             */
/*===========================================================================================================*/
void KPD_init(void)
{
    u8 Loc_u8PinIterator = ZERO;
    GPIO_strPinConfig_t tempPin;
       
    #if KPD_INPUT_PINS == KPD_ROW_PINS
        /* Set the input pin pointer to point to row pins */
        KPD_pstrInputPins = KPD_strRowPins;
        /* Set the output pin pointer to point to column pins */
        KPD_pstrOutputPins = KPD_strColPins;
        
    #elif KPD_INPUT_PINS == KPD_COL_PINS
        /* Set the input pin pointer to point to column pins */
        KPD_pstrInputPins = KPD_strColPins;
        /* Set the output pin pointer to point to row pins */
        KPD_pstrOutputPins = KPD_strRowPins;

    #else
    #error "Invalid Configuration!"
    #endif
    
    /* Initialize the input pins */
    tempPin.mode = INPUT_PIN;
	tempPin.modeCfg.inputCfg.pull = KPD_INPUT_PULL_TYPE;

    for(Loc_u8PinIterator=ZERO; Loc_u8PinIterator<NUMBER_OF_INPUT_PINS; Loc_u8PinIterator++)
    {
        tempPin.port = KPD_pstrInputPins[Loc_u8PinIterator].port;
        tempPin.pin = KPD_pstrInputPins[Loc_u8PinIterator].pin;
        GPIO_enuInitPin(&tempPin);
    }
    
    /* Initialize the output pins */
    tempPin.mode = OUTPUT_PIN;
	tempPin.modeCfg.outputCfg.pull = KPD_INPUT_PULL_TYPE;
	tempPin.modeCfg.outputCfg.speed = OUTPUT_LOW_SPEED;
	tempPin.modeCfg.outputCfg.type = OUTPUT_PUSH_PULL;

    for(Loc_u8PinIterator=ZERO; Loc_u8PinIterator<NUMBER_OF_OUTPUT_PINS; Loc_u8PinIterator++)
    {
        tempPin.port = KPD_pstrOutputPins[Loc_u8PinIterator].port;
        tempPin.pin = KPD_pstrOutputPins[Loc_u8PinIterator].pin;
        GPIO_enuInitPin(&tempPin);
    }
    
}

u8 KPD_u8GetPressedSync(void)
{
    u8 Local_u8PressedKey = NO_KEY_PRESSED;

    u8 Local_u8InputIterator = ZERO;
    u8 Local_u8OutputIterator = ZERO;
    
    u8 Local_u8InputValue = ZERO;

    for(Local_u8OutputIterator = ZERO; Local_u8OutputIterator<NUMBER_OF_OUTPUT_PINS; Local_u8OutputIterator++)
    {
        /* Activate the output pin (Row/Col) */
        GPIO_enuSetPin(KPD_pstrOutputPins[Local_u8OutputIterator].port, KPD_pstrOutputPins[Local_u8OutputIterator].pin, OUT_KEY_ACTIVATED);

        for(Local_u8InputIterator = ZERO; Local_u8InputIterator<NUMBER_OF_INPUT_PINS; Local_u8InputIterator++)
        {
            /* Read the current input pin (Col/Row) */
            GPIO_enuGetPin(KPD_pstrInputPins[Local_u8InputIterator].port, KPD_pstrInputPins[Local_u8InputIterator].pin, &Local_u8InputValue);
            
            if(Local_u8InputValue == KEY_PRESSED)
            {
                /* Get the Value of the pressed key */
                #if KPD_INPUT_PINS == KPD_ROW_PINS
                Local_u8PressedKey = KPD_u8KeyArr[Local_u8InputIterator][Local_u8OutputIterator];
                #elif KPD_INPUT_PINS == KPD_COL_PINS
                Local_u8PressedKey = KPD_u8KeyArr[Local_u8OutputIterator][Local_u8InputIterator];
                #else
                #error "Invalid Configuration!"
                #endif

                /* Wait until the key is released */
                while(Local_u8InputValue == KEY_PRESSED)
                {
                    GPIO_enuGetPin(KPD_pstrInputPins[Local_u8InputIterator].port, KPD_pstrInputPins[Local_u8InputIterator].pin, &Local_u8InputValue);
                }

                return Local_u8PressedKey;
            }
        }
        /* Deactivate the output pin (Row/Col) */
        GPIO_enuSetPin(KPD_pstrOutputPins[Local_u8OutputIterator].port, KPD_pstrOutputPins[Local_u8OutputIterator].pin, OUT_KEY_DEACTIVATED);
    }
    return Local_u8PressedKey;
}

u8 KPD_u8GetKey(void)
{
	return KPD_u8PressedKey;	
}

void KPD_Runnable(void)
{
	u8 loc_u8PressedKey = NO_KEY_PRESSED;

    u8 loc_u8InputIterator = ZERO;
    u8 loc_u8OutputIterator = ZERO;
    
    u8 loc_u8InputValue = ZERO;

    static u8 loc_u8KeyCount = ZERO;

    for(loc_u8OutputIterator = ZERO; loc_u8OutputIterator<NUMBER_OF_OUTPUT_PINS; loc_u8OutputIterator++)
    {
        /* Activate the output pin (Row/Col) */
        GPIO_enuSetPin(KPD_pstrOutputPins[loc_u8OutputIterator].port, KPD_pstrOutputPins[loc_u8OutputIterator].pin, OUT_KEY_ACTIVATED);

        for(loc_u8InputIterator = ZERO; loc_u8InputIterator<NUMBER_OF_INPUT_PINS; loc_u8InputIterator++)
        {
            /* Read the current input pin (Col/Row) */
            GPIO_enuGetPin(KPD_pstrInputPins[loc_u8InputIterator].port, KPD_pstrInputPins[loc_u8InputIterator].pin, &loc_u8InputValue);
            
            if(loc_u8InputValue == KEY_PRESSED)
            {
                /* Get the Value of the pressed key */
                #if KPD_INPUT_PINS == KPD_ROW_PINS
                loc_u8PressedKey = KPD_u8KeyArr[loc_u8InputIterator][loc_u8OutputIterator];
                #elif KPD_INPUT_PINS == KPD_COL_PINS
                loc_u8PressedKey = KPD_u8KeyArr[loc_u8OutputIterator][loc_u8InputIterator];
                #else
                #error "Invalid Configuration!"
                #endif
            }
        }

        /* Deactivate the output pin (Row/Col) */
        GPIO_enuSetPin(KPD_pstrOutputPins[loc_u8OutputIterator].port, KPD_pstrOutputPins[loc_u8OutputIterator].pin, OUT_KEY_DEACTIVATED);
    }

    if(loc_u8PressedKey != KPD_u8PressedKey) loc_u8KeyCount ++;
	else loc_u8KeyCount = ZERO;

	if(loc_u8KeyCount == KPD_DEBOUNCE_COUNT)
	{
		KPD_u8PressedKey = loc_u8PressedKey;
		loc_u8KeyCount = ZERO;
	}
	else
	{
		/* Do Nothing */
	}
}
