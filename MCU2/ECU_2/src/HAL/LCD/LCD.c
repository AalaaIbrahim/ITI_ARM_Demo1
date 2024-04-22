/*
 * LCD.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Shirehan
 */


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LCD.h"
#include "GPIO/GPIO.h"

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
/**
 * @brief Structure representing the configuration of pins for LCDs.
 *
 * This structure defines the layout of the pin configuration for LCDs.
 */
extern LCD_PinConig_t LCD_ARRAY[_NUM_OF_LCDs][NUM_OF_PINs_PER_LCD];

/**
 * @brief Function pointer type for callback functions.
 *
 * This type represents function pointers for callback functions used in the LCD module.
 */
typedef void (*CallBackFunc)(void);

/**
 * @brief Enumeration of states for the LCD module.
 *
 * This enumeration lists the possible states for the LCD module.
 */
typedef enum {
    LCD_InitState_State,
    PowerON,
    FunctionalSet,
    RSLow_State,
    RSHigh_State,
    RWLowState,
    EnableHigh_State,
    SendingCommand_State,
    SendingCharacter_State,
    EnableLow_State,
    EndWriteCommanDone_State,
    EndWriteCharacterDone_State,
    Entry_State,
    Display_State,
    END_State,
    LCD_Operational_State,

    // TaskState
    Busy,
    Ready,
    Done,
    // Type of request
    Write,
    Clear,
    SetPosition,
    WriteNumber,
	DisplayCursor
} LCD_States;

/**
 * @brief Structure representing a user request for the LCD module.
 *
 * This structure holds information about a user request for the LCD module.
 */
typedef struct {
    const char *string_buff; /**< Pointer to the string buffer. */
    u8 length; /**< Length of the string. */
    u8 state; /**< Current state of the request. */
    u8 type; /**< Type of the request. */
    struct {
        u8 currentPosition; /**< Current position for writing. */
        CallBackFunc CallBack; /**< Callback function for the request. */
    } Write_Process;
    struct {
        u8 X_Position; /**< X position for cursor movement. */
        u8 Y_Position; /**< Y position for cursor movement. */
    } MoveCursor;
    struct {
        uint16_t Number; /**< Number to write on the LCD. */
    } WriteNumber;
} UserRequest;



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/


/**
 * @brief Size of the buffer used in the LCD module.
 *
 * This macro defines the size of the buffer used for storing data in the LCD module.
 */
#define BUFFER_SIZE 30

/**
 * @brief Command to set the LCD into two lines mode.
 *
 * This macro defines the command to set the LCD into two lines mode.
 */
#define TWO_LINES_SET_FUNCTION  0b00111000

/**
 * @brief Command to enable cursor and display.
 *
 * This macro defines the command to enable cursor and display on the LCD.
 */
//#define CURSOR_DISPLAY_COMMAND  0b00001100
#define CURSOR_DISPLAY_COMMAND  0x0E


/**
 * @brief Command to clear the display.
 *
 * This macro defines the command to clear the display on the LCD.
 */
#define DISPLAY_CLEAR_COMMAND   0b00000001


/**
 * @brief Buffer to hold user requests for the LCD module.
 *
 * This buffer holds user requests for the LCD module.
 */
UserRequest RequestBuffer[BUFFER_SIZE];

/**
 * @brief Counter for the buffer used to hold user requests.
 *
 * This counter tracks the number of requests stored in the buffer.
 */
u8 BufferCounter = 0;

/**
 * @brief Global flag representing the state of the LCD module.
 *
 * This flag represents the state of the LCD module.
 */
u8 LCDState = LCD_InitState_State;

/**
 * @brief Global flag representing the command state for LCD operations.
 *
 * This flag represents the command state for LCD operations.
 */
u8 CommandState = RSLow_State;

/**
 * @brief Global flag representing the character writing state for LCD operations.
 *
 * This flag represents the character writing state for LCD operations.
 */
u8 WriteCharState = RSHigh_State;



static void InitializeTheBufferRquest (void);
static void LCD_initSm (void);
static void LCD_WriteCommand (u8 Command);
static void LCD_WriteCharacter_Process (u8 Data);
static void WriteStringProcess (UserRequest* Request);
static void ClearProcess (UserRequest* Request);
static void SetPositionProcess (UserRequest* Request);
static void LCD_WriteNumber_Process (UserRequest* Request);


/*API for user to buffer the request*/
void LCD_Init (void){
	InitializeTheBufferRquest();
	GPIO_strPin_t TempPin;

			 TempPin.Mode = Output_PushPull ;
			 TempPin.speed = High_Speed;
			 for (u8 i =0 ;i <_NUM_OF_LCDs ; i++)
			 {
				 for (u8 j =0 ; j<NUM_OF_PINs_PER_LCD ; j++)
				 {
					 TempPin.Port = LCD_ARRAY[i][j].Port;
					 TempPin.Pin = LCD_ARRAY[i][j].Pin;
					 GPIO_initPin(&TempPin);
				 }
			 }

}

LCD_ErrorState_t LCD_WriteString (u8* StrData, u8 length)
{
	LCD_ErrorState_t LocalErrorState = LCD_NOK;
	//static u8 BufferCounter =0;
	if ( RequestBuffer[BufferCounter].state == Done && BufferCounter<BUFFER_SIZE && StrData != NULL )
	{
		LocalErrorState = LCD_OK;
		RequestBuffer[BufferCounter].string_buff = StrData;
		RequestBuffer[BufferCounter].length = length;
		RequestBuffer[BufferCounter].state = Ready;
		RequestBuffer[BufferCounter].type = Write;
		BufferCounter++;

	}
	else
	{
		//DO Nothing
	}

	if (BufferCounter ==BUFFER_SIZE){BufferCounter =0;}

	return LocalErrorState;

}
LCD_ErrorState_t LCD_ClearScreen (void)
{
	LCD_ErrorState_t LocalErrorState = LCD_NOK;
	if ( RequestBuffer[BufferCounter].state == Done && BufferCounter<BUFFER_SIZE  )
	{
		LocalErrorState = LCD_OK;

				RequestBuffer[BufferCounter].state = Ready;
				RequestBuffer[BufferCounter].type = Clear;
				BufferCounter++;
	}
	else
		{
			//DO Nothing
		}

		if (BufferCounter ==BUFFER_SIZE){BufferCounter =0;}

		return LocalErrorState;



}

LCD_ErrorState_t LCD_SetPosition (uint8_t X , uint8_t Y)
{
	LCD_ErrorState_t LocalErrorState = LCD_NOK;
	if ( RequestBuffer[BufferCounter].state == Done && BufferCounter<BUFFER_SIZE  )
	{
		LocalErrorState = LCD_OK;
		RequestBuffer[BufferCounter].state = Ready;
		RequestBuffer[BufferCounter].type = SetPosition;
		RequestBuffer[BufferCounter].MoveCursor.X_Position = X;
		RequestBuffer[BufferCounter].MoveCursor.Y_Position = Y;
		BufferCounter++;


	}
	else
		{
			//DO Nothing
		}

		if (BufferCounter ==BUFFER_SIZE){BufferCounter =0;}

		return LocalErrorState;

}


LCD_ErrorState_t LCD_WriteNumber (uint16_t Number)
{
	LCD_ErrorState_t LocalErrorState = LCD_NOK;

		if ( RequestBuffer[BufferCounter].state == Done && BufferCounter<BUFFER_SIZE  )
			{
				LocalErrorState = LCD_OK;

						RequestBuffer[BufferCounter].state = Ready;
						RequestBuffer[BufferCounter].type = WriteNumber;
						RequestBuffer[BufferCounter].WriteNumber.Number = Number;
						BufferCounter++;
			}
			else
				{
					//DO Nothing
				}

				if (BufferCounter ==BUFFER_SIZE)
				{BufferCounter =0;}




	return LocalErrorState;


}








//Comes each 2ms
void LCD_TASK (void)
{
	if (LCDState ==  LCD_InitState_State)
	{

		LCD_initSm();
	}
	else if (LCDState == LCD_Operational_State)
	{
		static u8 Servecounter =0;
		if (RequestBuffer[Servecounter].state != Done && Servecounter < BUFFER_SIZE)
		{
			switch (RequestBuffer[Servecounter].type)
			{
			case Write:
			{
				WriteStringProcess(&RequestBuffer[Servecounter]);

			}break;
			case Clear:
			{
				ClearProcess(&RequestBuffer[Servecounter]);
			}break;
			case SetPosition:
			{
				SetPositionProcess(&RequestBuffer[Servecounter]);
			}break;
			case WriteNumber:
			{
				LCD_WriteNumber_Process(&RequestBuffer[Servecounter]);
			}break;


			}

			if (RequestBuffer[Servecounter].state == Done)
			{
				Servecounter++;
				//Circular Buffering
				if (Servecounter ==BUFFER_SIZE)
				{
					Servecounter =0;
				}
			}

		}
		else
		{
			//DoNothing

		}

	}


}




/*
void LCD_TASK (void)
{
    if (LCDState == LCD_InitState_State)
    {
        LCD_initSm();
    }
    else if (LCDState == LCD_Operational_State)
    {
        static u8 Servecounter = 0;
        u8 nextCounter = (Servecounter + 1) % BUFFER_SIZE; // Calculate the next counter position

        // Check if the request at Servecounter is done and the next counter is not the same as Servecounter
        if (RequestBuffer[Servecounter].state == Done && nextCounter != Servecounter)
        {
            switch (RequestBuffer[Servecounter].type)
            {
                // Process the request based on its type
                case Write:
                    WriteStringProcess(&RequestBuffer[Servecounter]);
                    break;
                case Clear:
                    ClearProcess(&RequestBuffer[Servecounter]);
                    break;
                case SetPosition:
                    SetPositionProcess(&RequestBuffer[Servecounter]);
                    break;
                case WriteNumber:
                    LCD_WriteNumber_Process(&RequestBuffer[Servecounter]);
                    break;
            }

            // Update the state and counter
            RequestBuffer[Servecounter].state = Busy;
            Servecounter = nextCounter;
        }
    }
}


*/

static void LCD_initSm (void)
{
	 static u8 counter =0;
	 static u8 initSm_State = PowerON;
	 switch (initSm_State)
	 {
	 case PowerON:
	 {
		 counter = counter+2;
		 if (counter==BUFFER_SIZE)
		 {
			 counter =0;
			 initSm_State = FunctionalSet;
		 }

	 }break;

	 case FunctionalSet:
	 {
		 LCD_WriteCommand(TWO_LINES_SET_FUNCTION);
		 if(CommandState == EndWriteCommanDone_State)
		 {
			 CommandState = RSLow_State;
			 initSm_State = Entry_State;
		 }

	 }break;
	 case Entry_State:
	 {
		 LCD_WriteCommand(CURSOR_DISPLAY_COMMAND);
		 if(CommandState == EndWriteCommanDone_State)
		 {
		 	CommandState = RSLow_State;
		 	initSm_State = Display_State;
		 }

	 }break;

	 case Display_State:
	 	 {
	 		 LCD_WriteCommand(DISPLAY_CLEAR_COMMAND);
	 		 if(CommandState == EndWriteCommanDone_State)
	 		 {
	 		 	CommandState = RSLow_State;
	 		 	initSm_State = END_State;
	 		 }

	 	 }break;

	 case END_State:
	 	 	 {

	 	 		// CommandState = RSLow_State;
	 	 	    initSm_State = END_State;
	 	 		LCDState = LCD_Operational_State;


	 	 	 }break;

	 }
}

static void InitializeTheBufferRquest (void)
{
	for (u8 indx =0 ; indx <BUFFER_SIZE ; indx++)
	{
		RequestBuffer[indx].state = Done;
	}
}

static void LCD_WriteCommand (u8 Command)
{
	//static CommandState = RSLow_State;
	switch (CommandState)
	{
	case RSLow_State:
	{
		GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_RS].Pin , LCD_ARRAY[LCD_0][LCD_RS].Port , GPIO_LOW  );
		CommandState = RWLowState;
	}break;

	case RWLowState:
		{
			GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_RW].Pin , LCD_ARRAY[LCD_0][LCD_RW].Port , GPIO_LOW  );
			CommandState = EnableHigh_State;
		}break;


	case EnableHigh_State:
		{
			GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_ENABLE].Pin , LCD_ARRAY[LCD_0][LCD_ENABLE].Port , GPIO_HIGH  );
			CommandState = SendingCommand_State;
		}break;
	case SendingCommand_State:
			{
				for (u8 i=0 ; i<8 ; i++)
				{
					GPIO_SetPinValue (LCD_ARRAY[LCD_0][i].Pin , LCD_ARRAY[LCD_0][i].Port , (Command>>i)&0x01  );

				}
				CommandState = EnableLow_State;
			}break;
	case EnableLow_State:
	{
		GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_ENABLE].Pin , LCD_ARRAY[LCD_0][LCD_ENABLE].Port , GPIO_LOW);
		CommandState = EndWriteCommanDone_State;
	}break;


	}
}

static void LCD_WriteCharacter_Process (u8 Data)
{
	if ((Data>0) && (Data <255))
	{
		switch (WriteCharState)
		{
		case RSHigh_State:
		{
			GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_RS].Pin , LCD_ARRAY[LCD_0][LCD_RS].Port , GPIO_HIGH  );
			WriteCharState = RWLowState;

		}break;
		case RWLowState:
		{
			GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_RW].Pin , LCD_ARRAY[LCD_0][LCD_RW].Port , GPIO_LOW  );
			WriteCharState = EnableHigh_State;
		}break;

		case EnableHigh_State:
				{
					GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_ENABLE].Pin , LCD_ARRAY[LCD_0][LCD_ENABLE].Port , GPIO_HIGH  );
					WriteCharState = SendingCharacter_State;
				}break;

		case SendingCharacter_State:
					{
						for (u8 i=0 ; i<8 ; i++)
						{
							GPIO_SetPinValue (LCD_ARRAY[LCD_0][i].Pin , LCD_ARRAY[LCD_0][i].Port , (Data>>i)&0x01  );

						}
						WriteCharState = EnableLow_State;
					}break;
		case EnableLow_State:
			{
				GPIO_SetPinValue (LCD_ARRAY[LCD_0][LCD_ENABLE].Pin , LCD_ARRAY[LCD_0][LCD_ENABLE].Port , GPIO_LOW);
				WriteCharState = EndWriteCharacterDone_State;
				//WriteCharState = RSHigh_State;

			}break;

		}

	}
}

static void WriteStringProcess (UserRequest* Request)
{

	if (Request != NULL)
	{
		static u8 indx =0;
		Request->state = Busy;

			LCD_WriteCharacter_Process(Request->string_buff[indx]);
			if (WriteCharState == EndWriteCharacterDone_State)
			{
				indx++;
				WriteCharState = RSHigh_State;


			}
			else
			{
				//DoNothing
			}

		if (indx == Request->length )
		{
			indx =0;
			Request->state = Done;

		}

	}


}

static void ClearProcess (UserRequest* Request)
{

	if (Request != NULL)
	{
		Request->state = Busy;
		LCD_WriteCommand(DISPLAY_CLEAR_COMMAND);
		if(CommandState == EndWriteCommanDone_State)
		{
			CommandState = RSLow_State;
			Request->state = Done;
		}





	}


}

static void SetPositionProcess (UserRequest* Request)
{
	u8 LCD_Local_LcdAdressCounter = 0;
	if (Request != NULL && Request->MoveCursor.X_Position<2)
		{
			Request->state = Busy;
			switch (Request->MoveCursor.X_Position)
			{
			case 0:
				LCD_Local_LcdAdressCounter = Request->MoveCursor.Y_Position;
				break;
			case 1:
				LCD_Local_LcdAdressCounter = Request->MoveCursor.Y_Position + 0x40;
				break;
			}

			LCD_WriteCommand(LCD_Local_LcdAdressCounter+128);
			if(CommandState == EndWriteCommanDone_State)
					{
						CommandState = RSLow_State;
						Request->state = Done;
					}


		}


}

static void LCD_WriteNumber_Process (UserRequest* Request)
{
	static u8 Flag =0;
    static u8 indx = 0;
    static  char Buffer[4];
	 if (Request != NULL)
	    {
		 if (Flag ==0)
		 {
			 u8 i=0;
	        Request->state = Busy;

	        // Convert number to string
	        for (i = 0; i < 4; i++) { // Change loop condition to 4
	            Buffer[i] = (((Request->WriteNumber).Number) % 10) + '0';
	            ((Request->WriteNumber).Number) = ((Request->WriteNumber).Number) / 10;
	        }

	        Buffer[i] = '\0'; // Assign null terminator

	        // Reverse the string to get correct order
	        for (u8 i = 0, j = 3; i < j; i++, j--) { // Change loop condition to j = 3
	            char temp = Buffer[i];
	            Buffer[i] = Buffer[j];
	            Buffer[j] = temp;
	        }
	        Flag++;
		 }
	        //Write the Number
		 	 if (((indx == 0) && (Buffer[0] == '0'))|| (indx == 1 && Buffer[0] == '0' && Buffer[1] == '0' ))
		 	 {
		 		indx++;
		 	 }
		 	 else
		 	 {
		 		 LCD_WriteCharacter_Process(Buffer[indx]);
		 	 }
	        if (WriteCharState == EndWriteCharacterDone_State)
	        {
	            indx++;
	            WriteCharState = RSHigh_State;
	        }
	        else
	        {
	            //DoNothing
	        }

	        if (indx == 4 || Buffer[indx] == '\0' )
	        {
	            indx = 0;
	            Flag =0;
	            Request->state = Done;
	        }
	    }



}
