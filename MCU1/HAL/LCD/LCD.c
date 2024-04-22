/**
 * @file    LCD.c
 * @author  Alaa Hisham
 * @brief   LCD API implementations
 * @version 0.0
 * @date    22-3-2024
 */

/*===============================================================================*/
/*						               Includes	    		    			     */
/*===============================================================================*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC.h"
#include "GPIO.h"

#include "LCD.h"
#include "LCD_cfg.h"

/*===============================================================================*/
/*						                Macros	    		    			     */
/*===============================================================================*/

#define LCD_LINE_ONE 0
#define LCD_LINE_TWO 1

#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE
#define LCD_DATA_PINS 4
#elif LCD_DATA_MODE == LCD_EIGHT_BIT_MODE
#define LCD_DATA_PINS 8
#endif

#define LCD_PINS LCD_DATA_PINS + 3

#define LCD_RS_PIN LCD_stPinArr[LCD_DATA_PINS].port, LCD_stPinArr[LCD_DATA_PINS].pin
#define LCD_RW_PIN LCD_stPinArr[LCD_DATA_PINS + 1].port, LCD_stPinArr[LCD_DATA_PINS + 1].pin
#define LCD_EN_PIN LCD_stPinArr[LCD_DATA_PINS + 2].port, LCD_stPinArr[LCD_DATA_PINS + 2].pin

#define LOW 0
#define HIGH 1

#define LCD_CURSOR_BLINKING_MODE       1
#define LCD_DISPLAY_MODE 1

#define LCD_FONT_MODE                   0
#define LCD_ROWS_MODE  1

#define DISPLAY_ON_OFF_CMD (0b00001000)|(LCD_CURSOR_MODE)|(LCD_DISPLAY_MODE<<2)
#define FUNCTION_SET_CMD  (0b00110000)|(LCD_FONT_MODE<<2)|(LCD_ROWS_MODE<<3)


/**
 * LCD init flag options
 */
#define UNINITIALIZED 0
#define INITIALIZED 1

/**
 * States of LCD initialization
 */
#define INIT_POWER_ON 0
#define INIT_RETURN_HOME 35
#define INIT_FUNCTION_SET 60
#define INIT_DISPLAY_CTRL 62
#define INIT_DISPLAY_ClEAR 64

#define LCD_RUNNABLE_PERIODICITY_MS 2

/*--------------------------------- LCD Commands --------------------------------*/

/*===============================================================================*/
/*						                Types	    		    			     */
/*===============================================================================*/
/**
 * States for LCD runnable
 */
typedef enum
{
	init,
	write_data,
	write_command,
	idle
} LCD_state_t;

/**
 * Steps for any write procedure (data/command)
 */
typedef enum
{
	data_phase,
	enable_phase
} LCD_writeSteps_t;

typedef struct
{
	const char *string;
	u8 len;
	u8 current_pos;
} lcdString_t;

/*===============================================================================*/
/*						          Global Variables			    			     */
/*===============================================================================*/
extern const LCD_stPin_t LCD_stPinArr[LCD_NUMBER_OF_PINS];

static u8 LCD_init_flag = UNINITIALIZED;
static u8 LCD_state = idle;
static u8 LCD_initState = INIT_POWER_ON;
//static u8 LCD_DataReq = ZERO;
static u8 LCD_commandReq = ZERO;
static volatile u8 LCD_currentTime = ZERO;
static u8 LCD_writePhase = data_phase;
static u8 entry_count = ZERO;

#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE
static u8 LCD_currentNibble = HIGH;
static u8 LCD_enableState = LOW;
#endif

lcdString_t LCD_StringInfo = {NULL, ZERO};

/*===============================================================================*/
/*					        	 Private Functions    		    			     */
/*===============================================================================*/
STD_enuErrorStatus_t init_proc(void);
STD_enuErrorStatus_t write_command_proc(u8 command);
void LCD_Runnable(void);

/*===============================================================================*/
/*						         API Implementations   		    			     */
/*===============================================================================*/

/**
 * @brief Initialize all the Configured LCDs in the LCD_config.c file
 *
 * @return void
 */
void LCD_initAsync(void)
{
	LCD_state = init;
}

/**
 * @brief Clears the entire LCD screen
 */
STD_enuErrorStatus_t LCD_ClearDisplayAsync(void)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;


		if (idle == LCD_state)
		{
			entry_count = ZERO;
			LCD_commandReq = LCD_CLEAR_DISPLAY;
			LCD_state = write_command;
		}
		else
		{
			Local_enuErrorStatus = STD_enuBusyFunction;
		}

	return Local_enuErrorStatus;
}

/**
 * @brief Function to move the cursor to a given location on LCD
 *
 * @param[in] Copy_u8Row : The row of the location on the LCD
 * @param[in] Copy_u8Col : The column of the location on the LCD
 *
 * @return STD_enuErrorStatus_t
 */
STD_enuErrorStatus_t LCD_enuGotoXY(u8 Copy_u8Row, u8 Copy_u8Col)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;
	u8 Local_u8Address = ZERO;


		if (idle == LCD_state)
		{
			entry_count = ZERO;
			if (Copy_u8Row < LCD_LINES)
			{
				if (Copy_u8Row == LCD_LINE_ONE)	Local_u8Address = Copy_u8Col;
				else if (Copy_u8Row == LCD_LINE_TWO) Local_u8Address = Copy_u8Col + 0x40;
				else {}

				LCD_commandReq = Local_u8Address + 128;
				LCD_state = write_command;
			}
			else /* position out of range */
			{
				Local_enuErrorStatus = STD_enuInvalidValue;
			}
		}
		else
		{
			Local_enuErrorStatus = STD_enuBusyFunction;
		}


	return Local_enuErrorStatus;
}

/**
 * @brief Displays a string of characters on the LCD
 *
 * @param[in] Copy_pchString : A pointer to the string
 * @param[in] Copy_u8StrLen  : The length of the string
 *
 * @return STD_enuErrorStatus_t
 */
STD_enuErrorStatus_t LCD_enuWriteStringAsync(const char *Copy_pchString, u8 Copy_u8StrLen)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuOk;

	if (idle == LCD_state)
	{
		entry_count = ZERO;
		//LCD_enuWriteData(' ');

		if (Copy_pchString != NULL)
		{
			LCD_StringInfo.string = Copy_pchString;
			LCD_StringInfo.len = Copy_u8StrLen;
			LCD_StringInfo.current_pos = ZERO;
			LCD_state = write_data;
		}
		else
		{
			Local_enuErrorStatus = STD_enuNullPtr;
		}
	}
	else
	{
		Local_enuErrorStatus = STD_enuBusyFunction;
	}

	return Local_enuErrorStatus;
}


/**
 * @brief Initialize all the Configured 7-segments in the SSD_config.c file
 *
 * @return void
 */
STD_enuErrorStatus_t init_proc(void)
{
	STD_enuErrorStatus_t loc_initStatus = STD_enuBusyFunction;
	u8 Local_u8Counter = ZERO;

	GPIO_strPinConfig_t tempPin;
	/////////////////////
	

	LCD_currentTime = entry_count*LCD_RUNNABLE_PERIODICITY_MS;

	switch (LCD_initState)
	{
	case INIT_POWER_ON:
		tempPin.mode = OUTPUT_PIN;
		tempPin.modeCfg.outputCfg.pull = PULLDOWN;
		tempPin.modeCfg.outputCfg.speed = OUTPUT_LOW_SPEED;
		tempPin.modeCfg.outputCfg.type = OUTPUT_PUSH_PULL;

		/* Initialize LCD pins */
		for (Local_u8Counter=ZERO; Local_u8Counter < LCD_PINS; Local_u8Counter++)
		{
			tempPin.port = LCD_stPinArr[Local_u8Counter].port;
			tempPin.pin = LCD_stPinArr[Local_u8Counter].pin;

			GPIO_enuInitPin(&tempPin);
		}

		LCD_initState = INIT_FUNCTION_SET;
		break;

	case INIT_RETURN_HOME:
		if (LCD_currentTime >= INIT_RETURN_HOME)
		{
			if (STD_enuOk == write_command_proc(LCD_RETURN_HOME))
			{
				LCD_initState = INIT_FUNCTION_SET;
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{
			/* Do Nothing */
		}
		break;

	case INIT_FUNCTION_SET:
		if (LCD_currentTime >= INIT_FUNCTION_SET)
		{
			//u8 Local_u8FunctionSet = LCD_FUNCTION_SET | LCD_FONT | LCD_LINES | LCD_DATA_MODE;

			/* Configure LCD's data mode, number of lines and font */
			if (STD_enuOk == write_command_proc(FUNCTION_SET_CMD))
			{
				LCD_initState = INIT_DISPLAY_CTRL;
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{
			/* Do Nothing */
		}
		break;

	case INIT_DISPLAY_CTRL:
		if (LCD_currentTime >= INIT_DISPLAY_CTRL)
		{
			if (STD_enuOk == write_command_proc(DISPLAY_ON_OFF_CMD))
			{
				LCD_initState = INIT_DISPLAY_ClEAR;
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{
			/* Do Nothing */
		}
		break;

	case INIT_DISPLAY_ClEAR:
		if (LCD_currentTime >= INIT_DISPLAY_ClEAR)
		{
			if (STD_enuOk == write_command_proc(LCD_CLEAR_DISPLAY))
			{
				loc_initStatus = STD_enuOk;
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{
			/* Do Nothing */
		}
		break;

	default:
		break;
	}

	return loc_initStatus;
}

/**
 * @brief Write a command to the LCD from the specified LCD commands
 *
 * @param[in] Copy_u8Command :
 *
 * @return STD_enuErrorStatus_t
 */
STD_enuErrorStatus_t write_command_proc(u8 command)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuBusyFunction;
	static u8 loc_entry_count = ZERO;

	if (LCD_writePhase == data_phase)
	{
		/* Indicate writing info */
		GPIO_enuSetPin(LCD_RW_PIN, GPIO_PIN_LOW);

		/* Indicate we are writing a command */
		GPIO_enuSetPin(LCD_RS_PIN, GPIO_PIN_LOW);

/* Write the data to the data pins */
#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE

		if (LCD_currentNibble == HIGH)
		{
			/* Write the high nibble of the data */
			//GPIO_enuSetPinArr(LCD_stPinArr, LCD_DATA_PINS, GET_HIGH_NIB(command));
			for(int iterator=ZERO; iterator<LCD_DATA_PINS; iterator++)
			{
				GPIO_enuSetPin(LCD_stPinArr[iterator].port, 
							   LCD_stPinArr[iterator].pin,
							   (command>>(iterator+4))&1);
			}
		}
		else
		{
			/* Write the low nibble of the data */
			//GPIO_enuSetPinArr(LCD_stPinArr, LCD_DATA_PINS, GET_LOW_NIB(command));
			for(int iterator=ZERO; iterator<LCD_DATA_PINS; iterator++)
			{
				GPIO_enuSetPin(LCD_stPinArr[iterator].port, 
							   LCD_stPinArr[iterator].pin,
							   (command>>iterator)&1);
			}
		}

		LCD_currentNibble ^= 1;

#elif LCD_DATA_MODE == LCD_EIGHT_BIT_MODE
		/* Write the data to the data pins */
		//GPIO_enuSetPinArr(LCD_stPinArr, LCD_DATA_PINS, command);
		for(int iterator=ZERO; iterator<LCD_DATA_PINS; iterator++)
			{
				GPIO_enuSetPin(LCD_stPinArr[iterator].port, 
							   LCD_stPinArr[iterator].pin,
							   (command>>iterator)&1);
			}

#else
#error "Invalid LCD Data Mode Configuration"
#endif

		/* Send the enable pulse to latch the info on data and control ports */
		GPIO_enuSetPin(LCD_EN_PIN, GPIO_PIN_HIGH);

		LCD_writePhase = enable_phase;
		loc_entry_count = ZERO;
	}
	else if (LCD_writePhase == enable_phase)
	{
		loc_entry_count++;
		if (loc_entry_count*LCD_RUNNABLE_PERIODICITY_MS >= 2)
		{
			GPIO_enuSetPin(LCD_EN_PIN, GPIO_PIN_LOW);
			LCD_writePhase = data_phase;
			Local_enuErrorStatus = STD_enuOk;

			#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE
			if(LCD_currentNibble == HIGH)
				Local_enuErrorStatus = STD_enuBusyFunction;
			#endif
		}
	}

	return Local_enuErrorStatus;
}

/**
 * @brief Function to write a single character on the LCD
 *
 * @param[in] Copy_u8Data : character to write
 *
 * @return STD_enuErrorStatus_t
 */
STD_enuErrorStatus_t write_data_proc(u8 Copy_u8Data)
{
	STD_enuErrorStatus_t Local_enuErrorStatus = STD_enuBusyFunction;
	static u8 loc_entry_count = ZERO;

	if (LCD_writePhase == data_phase)
	{
		/* Indicate writing info */
		GPIO_enuSetPin(LCD_RW_PIN, GPIO_PIN_LOW);

		/* Indicate we are writing data */
		GPIO_enuSetPin(LCD_RS_PIN, GPIO_PIN_HIGH);

/* Write the data to the data pins */
#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE

		if (LCD_currentNibble == HIGH)
		{
			/* Write the high nibble of the data */
			//GPIO_enuSetPinArr(LCD_stPinArr, LCD_DATA_PINS, GET_HIGH_NIB(Copy_u8Data));
			for(int iterator=ZERO; iterator<LCD_DATA_PINS; iterator++)
			{
				GPIO_enuSetPin(LCD_stPinArr[iterator].port, 
							   LCD_stPinArr[iterator].pin,
							   (Copy_u8Data>>(iterator+4))&1);
			}
		}
		else
		{
			/* Write the low nibble of the data */
			//GPIO_enuSetPinArr(LCD_stPinArr, LCD_DATA_PINS, GET_LOW_NIB(Copy_u8Data));
			for(int iterator=ZERO; iterator<LCD_DATA_PINS; iterator++)
			{
				GPIO_enuSetPin(LCD_stPinArr[iterator].port, 
							   LCD_stPinArr[iterator].pin,
							   (Copy_u8Data>>iterator)&1);
			}
		}

		LCD_currentNibble ^= 1;

#elif LCD_DATA_MODE == LCD_EIGHT_BIT_MODE
		/* Write the data to the data pins */
		//GPIO_enuSetPinArr(LCD_stPinArr, LCD_DATA_PINS, Copy_u8Data);
		for(int iterator=ZERO; iterator<LCD_DATA_PINS; iterator++)
			{
				GPIO_enuSetPin(LCD_stPinArr[iterator].port, 
							   LCD_stPinArr[iterator].pin,
							   (Copy_u8Data>>iterator)&1);
			}

#else
#error "Invalid LCD Data Mode Configuration"
#endif

		/* Send the enable pulse to latch the info on data and control ports */
		GPIO_enuSetPin(LCD_EN_PIN, GPIO_PIN_HIGH);

		LCD_writePhase = enable_phase;
		loc_entry_count = ZERO;
	}
	else if (LCD_writePhase == enable_phase)
	{
		loc_entry_count++;
		if (loc_entry_count*LCD_RUNNABLE_PERIODICITY_MS >= 2)
		{
			GPIO_enuSetPin(LCD_EN_PIN, GPIO_PIN_LOW);
			LCD_writePhase = data_phase;
			Local_enuErrorStatus = STD_enuOk;

#if LCD_DATA_MODE == LCD_FOUR_BIT_MODE
			if (LCD_currentNibble == HIGH)
				Local_enuErrorStatus = STD_enuBusyFunction;
#endif
		}
	}

	return Local_enuErrorStatus;
}


void LCD_Runnable(void)
{
	switch (LCD_state)
	{
	case idle:
		break;
	case init:
		if (STD_enuOk == init_proc())
		{
			LCD_state = idle;
		}
		else
		{
			entry_count++;
		}
		break;

	case write_data:
		if (LCD_StringInfo.current_pos < LCD_StringInfo.len)
		{
			if (STD_enuOk == write_data_proc(LCD_StringInfo.string[LCD_StringInfo.current_pos]))
			{
				LCD_StringInfo.current_pos++;
			}
			else
			{
				entry_count++;
			}
		}
		else
		{
			LCD_StringInfo.current_pos = ZERO;
			LCD_state = idle;
		}
		break;

	case write_command:
		if (STD_enuOk == write_command_proc(LCD_commandReq))
		{
			LCD_state = idle;
		}
		else
		{
			entry_count ++;
		}

		break;

	default:
		break;
	}
}
