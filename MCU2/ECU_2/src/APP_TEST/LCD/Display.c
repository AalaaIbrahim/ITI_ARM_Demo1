/*
 * Display.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Shirehan Medhat
 */

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "DigitalWatch.h"
#include "../../HAL/LCD/LCD.h"
#include "Display.h"
#include "SWITCH/SW.h"
#include "StopWatch.h"
#include "Switch_App.h"
#include "Processing.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
extern SW_Clock_t Clock;
extern uint8_t GState;
extern DaysAndShifts DigitlWatchShifts;
extern DisplayUnit DigitalWatchData[10];
StopWatchPrevData StopWatchPrev =
{
		.PrevHours = 100,
	    .PrevSeconds = 33,
		.PrevMinutes = 33
};
volatile uint8_t X_CursorPosition=0;
volatile uint8_t Y_CursorPosition=0;
volatile uint8_t MoveCursorState =0xff;
volatile uint8_t EditState =False;
volatile uint32_t DigitalWatchFirst = True;
volatile uint32_t StopWatchFirst = True;
volatile uint8_t EditCurrentCursorFlag =0xff;
volatile uint8_t CursCounter = False;


/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static void HandleLine0Movement(void);
static void HandleLine1Movement(void);
static void HandleTimeEdit(char unit);
static void HandleDayShiftEdit(void);
static void ResetCursorPosition(void);
static void SetCursorPosition (void);
static void initDigitalWatchData (void);
static void initStopWatchData (void);
static void StopWatchDisplay (void);
static void DigitalWatchDisplay (void);
/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void Display(void) {
    switch (GState) {
        case Digital_watch: {
            DigitalWatchDisplay();

            if (EditState == True)
            {
            	CursCounter = False;
                LCD_SetPosition(X_CursorPosition, Y_CursorPosition);
                SetCursorPosition();
                if (Y_CursorPosition >= Column_0 && Y_CursorPosition <= Column_15)
                {
                    switch (X_CursorPosition)
                    {
                        case Line_0:
                            HandleLine0Movement();
                            break;
                        case Line_1:
                            HandleLine1Movement();
                            break;
                    }
                }
                else
                {
                	Y_CursorPosition = Column_0;
                }
            }
            else if (EditState == False)
            {
            	EditCurrentCursorFlag = 0xff;
            	if (CursCounter == False)
            	{
            	   X_CursorPosition =0;
            	   Y_CursorPosition = 0;
            	   CursCounter = True;

            	 }
                ResetCursorPosition();

            }

        }break;
        case Stop_Watch: {
            StopWatchDisplay();
            break;
        }
    }
}




void SetCursorPosition (void)
{

	 switch (MoveCursorState) {
	                    case 'R':
	                        Y_CursorPosition++;
	                        MoveCursorState = 0xff;
	                        break;
	                    case 'L':
	                        Y_CursorPosition--;
	                        MoveCursorState = 0xff;
	                        break;
	                    default:
	                        // Do Nothing
	                        break;
	                }
}
static void HandleLine0Movement(void) {
    switch (Y_CursorPosition) {
        case Column_0:
        case Column_1:
        case Column_2:
            HandleTimeEdit('H');
            break;
        case Column_4:
        case Column_5:
            HandleTimeEdit('M');
            break;
        case Column_7:
        case Column_8:
        	//PreviousData.PrevSeconds = DigitlWatch.Seconds;
            HandleTimeEdit('S');
            break;
        case Column_10:
        case Column_11:
        case Column_12:
        	 HandleTimeEdit('L');
        	 break;
        case Column_14:
        case Column_15:
            HandleDayShiftEdit();
            break;
    }
}

static void HandleLine1Movement(void) {
    switch (Y_CursorPosition) {
        case Column_0:
        case Column_1:
        case Column_2:
        	HandleTimeEdit('W');
            break;
        case Column_4:
        case Column_5:
        	HandleTimeEdit('D');
            break;
        case Column_7:
        case Column_8:
        	HandleTimeEdit('O');
            break;
        case Column_10:
        case Column_11:
        case Column_12:
        case Column_13:
        	HandleTimeEdit('Y');
            break;
    }
}

static void HandleTimeEdit(char unit) {
    uint16_t* target = NULL;
	EditCurrentCursorFlag = unit;
    switch (unit) {
        case 'H':
        	EditCurrentCursorFlag = hours;
            target = &DigitalWatchData[hours].PreviousValue;
            break;
        case 'M':
        	EditCurrentCursorFlag = minutes;
        	//PreviousData.PrevMinutes = DigitlWatch.Minutes;
            target = &DigitalWatchData[minutes].PreviousValue;
            break;
        case 'S':
        	EditCurrentCursorFlag = seconds;
            target = &(DigitalWatchData[seconds].PreviousValue);
            break;
      case 'L':
    	      EditCurrentCursorFlag = milli;
              if (MoveCursorState == 'U') DigitalWatchData[milli].PreviousValue +=100;
              else if (MoveCursorState == 'D') DigitalWatchData[milli].PreviousValue -=100;
              MoveCursorState = 0xff;

                break;
        case 'W':
        	 EditCurrentCursorFlag = WeekDay;
        	 target = &DigitalWatchData[WeekDay].PreviousValue;
        	 break;
        case 'D':
        	 EditCurrentCursorFlag = CurrentDay;
        	target = &DigitalWatchData[CurrentDay].PreviousValue;
        	break;
        case 'O':
        	 EditCurrentCursorFlag = CurrentMonth;
        	target = &DigitalWatchData[CurrentMonth].PreviousValue;
        	break;
        case 'Y':
        	 EditCurrentCursorFlag = CurrentYear;
        	target = &DigitalWatchData[CurrentYear].PreviousValue;
        	break;
    }
    if (unit != 'L')
    {
    if (MoveCursorState == 'U') {

        (*target)++;
    } else if (MoveCursorState == 'D') {
        (*target)--;
    }
    MoveCursorState = DEFAULT_VALUE;
    }
}

static void HandleDayShiftEdit(void) {
    if (MoveCursorState == 'U' || MoveCursorState == 'D') {
    	DigitalWatchData[DayShift].Value ^= 1;
    }
    MoveCursorState = DEFAULT_VALUE;
}



static void ResetCursorPosition(void) {
    if (MoveCursorState == 'U') {
        X_CursorPosition = Line_0;
    } else if (MoveCursorState == 'D') {
        X_CursorPosition = Line_1;
    }
    MoveCursorState = DEFAULT_VALUE;
}




static void StopWatchDisplay (void)
{
	if (StopWatchFirst == 1) {

		initStopWatchData();
		LCD_ClearScreen();
	}
	if (StopWatchPrev.PrevHours != Clock.hr) {

		LCD_SetPosition(Line_0, Column_1);
		LCD_WriteNumber(Clock.hr);
		LCD_WriteString(":", 1);
		StopWatchPrev.PrevHours = Clock.hr;
	}

	if (StopWatchPrev.PrevMinutes != Clock.min) {
		LCD_SetPosition(Line_0, Column_4);
		LCD_WriteNumber(Clock.min);
		LCD_WriteString(":", 1);
		StopWatchPrev.PrevMinutes = Clock.min;

	}
	if (StopWatchPrev.PrevSeconds != Clock.sec) {
		LCD_SetPosition(Line_0, Column_7);
		LCD_WriteNumber(Clock.sec);
		LCD_WriteString(":", 1);
		StopWatchPrev.PrevSeconds = Clock.sec;

	}
	if (StopWatchPrev.PrevMSeconds != Clock.msec) {
		LCD_SetPosition(Line_0, Column_10);
		LCD_WriteNumber(Clock.msec);
		StopWatchPrev.PrevMSeconds = Clock.msec;

	}

}


static void DigitalWatchDisplay (void)
{
	if (DigitalWatchFirst == True)
		{
		   initDigitalWatchData();
			LCD_ClearScreen();
			X_CursorPosition=Line_0;
			Y_CursorPosition=Column_0;


		}
	for (uint8_t i =0 ; i<9 ; i++)
	{
		if ((DigitalWatchData[i].PreviousValue != DigitalWatchData[i].Value ) && EditCurrentCursorFlag != i )
			{
					LCD_SetPosition(DigitalWatchData[i].Line,DigitalWatchData[i].Col);
					switch (i)
					{
					case milli:
						LCD_WriteNumber(DigitalWatchData[i].Value/10);
					    LCD_SetPosition(X_CursorPosition,Y_CursorPosition);
					    break;
					case hours:
					case minutes:
						LCD_WriteNumber(DigitalWatchData[i].Value);
						LCD_WriteString(":",1);
						break;
					case seconds:
						LCD_WriteNumber(DigitalWatchData[i].Value);
						LCD_WriteString(".",1);
						break;
					case DayShift:
						LCD_WriteString(DigitlWatchShifts.DayPeriods[DigitalWatchData[DayShift].Value],2);
						break;
					case WeekDay:
						LCD_WriteString(DigitlWatchShifts.StrDays[DigitalWatchData[WeekDay].Value],3);
						LCD_SetPosition(0,12);
						LCD_WriteString("0",1);
						LCD_SetPosition(0,3);
						break;
					case CurrentDay:
					case CurrentMonth:
						LCD_WriteNumber(DigitalWatchData[i].Value);
						LCD_WriteString("-",1);
					    break;
					case CurrentYear:
						LCD_WriteNumber(DigitalWatchData[i].Value);
						break;


					}
					DigitalWatchData[i].PreviousValue = DigitalWatchData[i].Value;
			}
		else if ( EditCurrentCursorFlag ==i)
		{
			LCD_SetPosition(DigitalWatchData[i].Line,DigitalWatchData[i].Col);

			switch (i)
		{


		       case hours:
		       case minutes:
		          	LCD_WriteNumber(DigitalWatchData[i].PreviousValue);
		       	    LCD_WriteString(":",1);
		       	    break;
		       case seconds:
		    	   LCD_WriteNumber(DigitalWatchData[i].PreviousValue);
		    	   LCD_WriteString(".",1);
		    	   break;
		       case DayShift:
		    	   LCD_WriteString(DigitlWatchShifts.DayPeriods[DigitalWatchData[DayShift].PreviousValue],2);
		    	   break;
		       case WeekDay:
		    	   LCD_WriteString(DigitlWatchShifts.StrDays[DigitalWatchData[WeekDay].PreviousValue],3);
		    	   LCD_SetPosition(0,12);
		    	   LCD_WriteString("0",1);
		    	   LCD_SetPosition(0,3);
		    	   break;
		       case CurrentDay:
		       case CurrentMonth:
		    	   LCD_WriteNumber(DigitalWatchData[i].PreviousValue);
		    	   LCD_WriteString("-",1);
		           break;
		       case CurrentYear:
		    	   LCD_WriteNumber(DigitalWatchData[i].PreviousValue);
		    	   break;
		       case milli:
		       	     LCD_WriteNumber(DigitalWatchData[i].Value/10);
		       	     LCD_SetPosition(X_CursorPosition,Y_CursorPosition);
		       	     DigitalWatchData[i].PreviousValue = DigitalWatchData[i].Value;
		       	     break;


		}

			DigitalWatchData[i].Value = DigitalWatchData[i].PreviousValue;
			EditCurrentCursorFlag = DEFAULT_VALUE;
		}


	}

}

static void initDigitalWatchData (void)
{
	            DigitalWatchData[hours].PreviousValue 			= DEFAULT_VALUE;
				DigitalWatchData[seconds].PreviousValue 		= DEFAULT_VALUE;
				DigitalWatchData[CurrentDay].PreviousValue 		= DEFAULT_VALUE;
				DigitalWatchData[CurrentMonth].PreviousValue 	= DEFAULT_VALUE;
				DigitalWatchData[CurrentYear].PreviousValue 	= DEFAULT_VALUE;
				DigitalWatchData[DayShift].PreviousValue 		= DEFAULT_VALUE;
				DigitalWatchData[minutes].PreviousValue 		= DEFAULT_VALUE;
				DigitalWatchData[WeekDay].PreviousValue 		= DEFAULT_VALUE;
				DigitalWatchData[CurrentDay].PreviousValue	    = DEFAULT_VALUE;
				DigitalWatchData[CurrentMonth].PreviousValue	= DEFAULT_VALUE;
				DigitalWatchData[CurrentYear].PreviousValue 	= DEFAULT_VALUE;
				DigitalWatchFirst = False;
				StopWatchFirst = True;

}

static void initStopWatchData (void)
{
	        StopWatchPrev.PrevHours 	= 100;
			StopWatchPrev.PrevMSeconds 	= 2000;
			StopWatchPrev.PrevMinutes 	= 100;
			StopWatchPrev.PrevSeconds 	= 100;
			DigitalWatchFirst 			= 1;
			StopWatchFirst 				= 0;
}

