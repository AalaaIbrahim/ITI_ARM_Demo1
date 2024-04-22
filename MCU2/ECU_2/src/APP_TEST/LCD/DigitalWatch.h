/*
 * DigitalWatch.h
 *
 *  Created on: Apr 5, 2024
 *      Author: Shirehan Medhat
 */

#ifndef APP_TEST_LCD_DIGITALWATCH_H_
#define APP_TEST_LCD_DIGITALWATCH_H_

/********************************************************************************************************/
/********************************************** Includes *************************************************/
/********************************************************************************************************/

#include "LIB/STD_TYPES.h"

/********************************************************************************************************/
/*********************************************** Types ***************************************************/
/********************************************************************************************************/

// Enumeration defining the days of the week
typedef enum
{
    Saturday,
    Sunday,
    Monday,
    Tuesday,
    Wendesday,
    Thursday,
    Friday
} WeekDays;

// Structure to hold day periods and days of the week
typedef struct {
    char* DayPeriods[2];
    char* StrDays[7];
} DaysAndShifts;

// Structure representing a display unit
typedef struct
{
    uint16_t Value;         // Current value
    uint16_t PreviousValue; // Previous value
    uint8_t Line;           // Line on LCD
    uint8_t Col;            // Column on LCD
} DisplayUnit;

// Enumeration defining LCD lines
typedef enum
{
    Line_0,
    Line_1
} Lines;

// Enumeration defining LCD columns
typedef enum
{
    Column_0, Column_1, Column_2, Column_3, Column_4, Column_5, Column_6, Column_7,
    Column_8, Column_9, Column_10, Column_11, Column_12, Column_13, Column_14, Column_15
} Columns;

/********************************************************************************************************/
/*********************************************** Defines *************************************************/
/********************************************************************************************************/

#define DummyNumber	1000
#define hours	0
#define minutes	1
#define seconds 2
#define milli   3
#define DayShift 4
#define WeekDay 5
#define CurrentDay 6
#define CurrentMonth 7
#define CurrentYear 8

/********************************************************************************************************/
/************************************* Defines For User *************************************************/
/********************************************************************************************************/

// Default values for digital watch
#define USER_HOURS          12
#define USER_MINUTES        59
#define USER_SECONDS        53
#define USER_MILLI          0
#define USER_DAY_SHIFT      1
#define USER_WEEKDAY        Saturday
#define USER_CURRENTDAY     30
#define USER_MONTH          12
#define USER_YEAR           2024

/********************************************************************************************************/
/************************************************* APIs **************************************************/
/********************************************************************************************************/

// Function to check and correct boundary values

// Function to calculate digital watch time
void DigitalWatchCalc(void);

#endif /* APP_TEST_LCD_DIGITALWATCH_H_ */
