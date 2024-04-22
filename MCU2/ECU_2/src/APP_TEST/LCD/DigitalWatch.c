/*
 * DigitalWatch.c
 *
 *  Created on: Apr 3, 2024
 *      Author: Shirehan Medhat
 */





/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "DigitalWatch.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/




/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/




/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
/*To Verify the user edit in the editMode*/
extern volatile uint8_t EditState;
/* Structure to hold day periods and days of the week*/
DaysAndShifts DigitlWatchShifts = {
    .DayPeriods = {"AM", "PM"},
    .StrDays = {"Sat", "Sun", "Mon", "Tues", "Wen", "Thu", "Fri"}
};

// Array of display units for digital watch data
DisplayUnit DigitalWatchData[10] =
    {
        [hours] 		= {.Value = USER_HOURS		, .PreviousValue = DummyNumber	, .Line = Line_0, .Col = Column_1},
        [minutes] 		= {.Value = USER_MINUTES	, .PreviousValue = DummyNumber	, .Line = Line_0, .Col = Column_4},
        [seconds] 		= {.Value = USER_SECONDS	, .PreviousValue = DummyNumber	, .Line = Line_0, .Col = Column_7},
        [milli] 		= {.Value = USER_MILLI		, .PreviousValue = DummyNumber	, .Line = Line_0, .Col = Column_10},
        [DayShift] 		= {.Value = USER_DAY_SHIFT	, .PreviousValue = DummyNumber	, .Line = Line_0, .Col = Column_14},
        [WeekDay] 		= {.Value = USER_WEEKDAY	, .PreviousValue = DummyNumber	, .Line = Line_1, .Col = Column_0},
        [CurrentDay] 	= {.Value = USER_CURRENTDAY	, .PreviousValue = DummyNumber	, .Line = Line_1, .Col = Column_4},
        [CurrentMonth] 	= {.Value = USER_MONTH		, .PreviousValue = DummyNumber	, .Line = Line_1, .Col = Column_7},
        [CurrentYear] 	= {.Value = USER_YEAR		, .PreviousValue = DummyNumber	, .Line = Line_1, .Col = Column_10},
};

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static void BoundariesChecking(void);

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

// Function to calculate digital watch time
void DigitalWatchCalc(void)
{
    static uint64_t Counter = 0;
    BoundariesChecking(); // Check boundaries of data

    // Update time counters
    if (Counter == 0 || EditState == 1)
    {
        Counter = DigitalWatchData[milli].Value + ((DigitalWatchData[seconds].Value) * 1000) + ((DigitalWatchData[minutes].Value) * 60000);
    }
    Counter = Counter + 100;

    // Update milliseconds
    if (Counter % 100 == 0)
    {
        DigitalWatchData[milli].Value += 100;
        if (DigitalWatchData[milli].Value >= 1000)
        {
            DigitalWatchData[milli].Value = 0;
        }
    }

    // Update seconds
    if (Counter % 1000 == 0)
    {
        DigitalWatchData[seconds].Value++;
        if (DigitalWatchData[seconds].Value >= 60)
        {
            DigitalWatchData[seconds].Value = 0;
        }
    }

    // Update minutes
    if (Counter % 60000 == 0)
    {
        DigitalWatchData[minutes].Value++;
        if (DigitalWatchData[minutes].Value >= 60)
        {
            DigitalWatchData[minutes].Value = 0;
        }
    }

    // Update hours and date
    if (Counter % 3600000 == 0)
    {
        DigitalWatchData[hours].Value++;
        if (DigitalWatchData[hours].Value >= 13)
        {
            // Reset hours to 1 if it exceeds 12 and toggle day shift
            DigitalWatchData[hours].Value = 1;
            DigitalWatchData[DayShift].Value = (DigitalWatchData[DayShift].Value) ^ 1;
            // If it's AM, update weekday and current day
            if (DigitlWatchShifts.DayPeriods[DigitalWatchData[DayShift].Value] == "AM")
            {
                DigitalWatchData[WeekDay].Value++;
                // Reset weekday if it exceeds 6 (Saturday)
                if (DigitalWatchData[WeekDay].Value > 6)
                {
                    DigitalWatchData[WeekDay].Value = 0;
                }
                DigitalWatchData[CurrentDay].Value++;
                // Reset current day and update current month/year if needed
                if (DigitalWatchData[CurrentDay].Value > 30)
                {
                    DigitalWatchData[CurrentMonth].Value++;
                    DigitalWatchData[CurrentDay].Value = 1;
                    if (DigitalWatchData[CurrentMonth].Value >= 13)
                    {
                        DigitalWatchData[CurrentYear].Value++;
                        DigitalWatchData[CurrentMonth].Value = 1;
                    }
                }
            }
        }
    }
}

// Function to check and correct boundary values
static void BoundariesChecking(void)
{
    // Check and correct minutes, seconds, and milliseconds
    if (DigitalWatchData[minutes].PreviousValue > 59)
        DigitalWatchData[minutes].PreviousValue = 0;
    if (DigitalWatchData[seconds].PreviousValue > 59)
        DigitalWatchData[seconds].PreviousValue = 0;
    if (DigitalWatchData[milli].PreviousValue > 1000)
        DigitalWatchData[seconds].PreviousValue = 0;

    // Check and correct hours
    if (DigitalWatchData[hours].PreviousValue > 12 || DigitalWatchData[hours].PreviousValue < 1)
        DigitalWatchData[hours].PreviousValue = 1;

    // Check and correct current day
    if (DigitalWatchData[CurrentDay].PreviousValue > 30 || DigitalWatchData[CurrentDay].PreviousValue < 1)
        DigitalWatchData[CurrentDay].PreviousValue = 1;

    // Check and correct current month
    if (DigitalWatchData[CurrentMonth].PreviousValue > 12 || DigitalWatchData[CurrentMonth].PreviousValue < 1)
        DigitalWatchData[CurrentMonth].PreviousValue = 1;

    // Check and correct week day
    if (DigitalWatchData[WeekDay].PreviousValue > 6)
    {
        DigitalWatchData[WeekDay].PreviousValue = 0;
    }
}
