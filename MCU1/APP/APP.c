

#include "NVIC.h"
#include "GPIO.h"
#include "RCC.h"

#include "HSYSTICK.h"
#include "LED.h"
#include "LCD.h"

#include "sched.h"

/*===========================================================================================================*/
/*						                             Includes						                         */
/*===========================================================================================================*/
#include "STD_TYPES.h"

#include "LCD.h"
#include "KPD.h"

/*===========================================================================================================*/
/*						                             Macros						                             */
/*===========================================================================================================*/

#define DISPLAY_PERIODICITY_MS 50

#define DISPLAY_CLK_PERIODICITY 800
#define EDIT_CLK_PERIODICITY 400

#define RESET_MASK 0xFF00

/*--------- Keypad values ---------*/
#define UP              'U'
#define DOWN            'D'
#define LEFT_PAUSE      'P'
#define RIGHT_STOP      'T'
#define EDIT_START      'S'
#define MODE            'M'
#define OK_RESET        'O'

#define EDIT_TIMEOUT_SEC 10

#define TIME_LENGTH 12
#define DATE_LENGTH 15

#define TIME_SEC_U 7
#define TIME_SEC_T 6

#define TIME_MIN_U 4
#define TIME_MIN_T 3

#define TIME_HOUR_U 1
#define TIME_HOUR_T 0

#define DATE_DAY_U 5
#define DATE_DAY_T 4

#define DATE_MON_U 8
#define DATE_MON_T 7

#define DATE_YEAR_U 13
#define DATE_YEAR_T 12
#define DATE_YEAR_H 11

#define TIME_MODE 0
#define STOPWATCH_MODE 1

#define EDIT_MASK 0x8000

/*===========================================================================================================*/
/*						                             Types						                             */
/*===========================================================================================================*/

typedef enum
{
    edit ,
    display
}APP_enuClockMode_t;

typedef enum
{
    SEC ,
    MIN ,
    HOUR,
    DAY ,
    MON ,
    YEAR
}APP_enuTimeFields_t;

typedef struct 
{
    u16 hr;
    u16 min;
    u16 sec;
    u16 am_pm;
    u16 day;
    u16 mon;
    u16 year;
}APP_strTime_t;

typedef enum
{
    STOPPED ,
    PAUSED  ,
    RUNNING 
}APP_enuStopwatchState_t;

typedef struct 
{
    u8 state;
    u16 hr;
    u16 min;
    u16 sec;
    u16 ms;
}APP_strStopwatch_t;

typedef struct
{
    u8 mode;
    u8 currentLine;
    u16 periodicity;
    APP_strTime_t* time_info; 
}APP_strClock_t;


/*===========================================================================================================*/
/* 				                              Global Variables					                             */
/*===========================================================================================================*/

static u8 APP_displayMode = TIME_MODE;

/* Date Format: MON 01-01-2024 */

static const char* days[7] = {"SAT ", "SUN ", "MON ", "TUE ", "WED ", "THU ", "FRI "};

static u8 days_per_mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static APP_strTime_t time =
{
    .sec = 30,
    .min = 59,
    .hr = 11,
    .am_pm = 'A',
    .day = 1,
    .mon = 1,
    .year = 2024
};

//static APP_strTime_t time_edit;

static APP_strClock_t clock = 
{
    .mode = display,
    .currentLine = 0,
    .periodicity = DISPLAY_CLK_PERIODICITY,
    .time_info = &time
};

static APP_strStopwatch_t stopwatch_info = 
{
    .ms = ZERO ,
    .sec = ZERO,
    .min = ZERO,
    .hr = ZERO
};

/*===========================================================================================================*/
/*						                          Processes						                             */
/*===========================================================================================================*/

u8 get_weekday(u8 d, u8 m, u16 y)
{
    return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
}

static void str_insert_num(u16 num, u8* string, u8 start_index)
{
    u8 count = 2;
    static u8 blink_flag = 1;

    if(num & EDIT_MASK)
    {
        blink_flag ^= 1;
        if(blink_flag)
        {
            while (count--)
            {
                string[start_index--] = ' ';
            } 
        }
        else
        {
            num ^= EDIT_MASK;
            while (count--)
            {
                string[start_index--] = num%10 + '0';
                num /= 10;
            }        
        }
    }
    else
    {
        while (count--)
        {
            string[start_index--] = num%10 + '0';
            num /= 10;
        }        
    }
}

static void set_clock_str(APP_strTime_t* time_info, u8* time_str, u8* date_str)
{
    u8 day_index = get_weekday(time_info->day, time_info->mon, time_info->year);

    str_insert_num(time_info->sec, time_str, TIME_SEC_U);
    str_insert_num(time_info->min, time_str, TIME_MIN_U);
    str_insert_num(time_info->hr, time_str, TIME_HOUR_U);

    time_str[9] = time_info->am_pm;

    str_insert_num(time_info->day, date_str, DATE_DAY_U);
    str_insert_num(time_info->mon, date_str, DATE_MON_U);
    str_insert_num(time_info->year,date_str,DATE_YEAR_U);

    date_str[0] = days[day_index][0];
    date_str[1] = days[day_index][1];
    date_str[2] = days[day_index][2];
}

static void set_stopwatch_str(APP_strStopwatch_t* stopwatch, u8* stopwatch_str)
{
    str_insert_num(stopwatch->sec, stopwatch_str, TIME_SEC_U);
    str_insert_num(stopwatch->min, stopwatch_str, TIME_MIN_U);
    str_insert_num(stopwatch->hr,  stopwatch_str, TIME_HOUR_U);
    str_insert_num(stopwatch->ms,  stopwatch_str, DATE_DAY_U);
}

/**
 * @brief a process used by the LCD_app Runnable
 *        to display time and date on the LCD
*/
void display_time_proc(void)
{
    static u8 step = ZERO;
    static u8 loc_time_str[TIME_LENGTH] = "00:00:00 AM";
    static u8 loc_date_str[DATE_LENGTH+1] = "MON 01-01-2024";
    static u8 loc_entry_count = ZERO;
    static u16 loc_current_time = ZERO;

    loc_entry_count++;
    loc_current_time = loc_entry_count*DISPLAY_PERIODICITY_MS;

    if(loc_current_time >= clock.periodicity)
    {
        switch (step)
        {
        case 0: if(STD_enuOk == LCD_ClearDisplay()) {step++;} break;
        case 1: if((clock.time_info->am_pm)&EDIT_MASK) loc_time_str[9]^=((clock.time_info->am_pm)&0xff);
                set_clock_str(clock.time_info, loc_time_str, loc_date_str); 
                if(STD_enuOk == LCD_enuGotoXY(0, 0)) {step++;} break;
        case 2: if(STD_enuOk == LCD_enuWriteStringAsync((const char*)loc_time_str, TIME_LENGTH-1)) step++; break;
        case 3: if(STD_enuOk == LCD_enuGotoXY(1, 0)) step++; break;
        case 4: if(STD_enuOk == LCD_enuWriteStringAsync((const char*)loc_date_str, DATE_LENGTH-1)) {
                loc_entry_count = ZERO; step=1;} break;
        default: break;
        }
    }
    
}

/**
 * @brief a process used by the LCD_app Runnable
 *        to display the stopwatch
*/
void display_stopwatch_proc(void)
{
    static u8 step = ZERO;
    static u8 loc_str[TIME_LENGTH] = "00:00:00.00";

    switch (step)
    {
    case 0: if(STD_enuOk == LCD_ClearDisplay()) {step++;} break;
    case 1: set_str(stopwatch_info, loc_str); 
            if(STD_enuOk == LCD_enuGotoXY(0, 0)) {step++;} break;
    case 2: if(STD_enuOk == LCD_enuWriteStringAsync((const char*)loc_str, TIME_LENGTH-1)) step=1; break;
    default: break;
    }    
}

/*===========================================================================================================*/
/* 				                             API implementations					                         */
/*===========================================================================================================*/
void APP_Init(void)
{
    RCC_enuSetPeripheralClk(RCC_AHB1_GPIOA, RCC_ENABLE);
    RCC_enuSetPeripheralClk(RCC_AHB1_GPIOB, RCC_ENABLE);

    KPD_init();
    LCD_initAsync();
        
    sched_init(); 
}

void APP_Start(void)
{
    sched_start();
}

/*===========================================================================================================*/
/*						                          Runnables						                             */
/*===========================================================================================================*/

void LCD_app(void)
{
    if(TIME_MODE == APP_displayMode) 
    {
        display_time_proc();
    }
    else if(STOPWATCH_MODE == APP_displayMode)
    {
        display_stopwatch_proc();
    }
}

// Function to update date and time string
void updateDateTime(void) 
{   
    time.sec ++; 
    
    if((time.sec & ~EDIT_MASK) >= 60)
    {
    	time.sec &= RESET_MASK;
    	time.min ++;
    	
    	if((time.min & ~EDIT_MASK) >= 60)
    	{
    	    time.min &= RESET_MASK;
    	    time.hr ++;
    	    
            if((time.hr & ~EDIT_MASK) == 12) time.am_pm = time.am_pm == 'A'? 'P':'A';
    	    else if((time.hr & ~EDIT_MASK) > 12)
    	    {
    	    	time.hr = (time.hr & RESET_MASK) +1;
    	    	time.day ++;
    	    	
    	    	if((time.day & ~EDIT_MASK) > days_per_mon[time.mon-1])
    	    	{
    	    	    // check for leap years
    	    	    time.day = (time.day & RESET_MASK) +1;

    	    	    time.mon ++;
    	    	    
    	    	    if((time.mon & ~EDIT_MASK) > 12)
    	    	    {
    	    	    	time.mon = (time.mon & RESET_MASK) +1;
    	    	    	time.year ++;
    	    	    }
    	    	}
    	    }    	    
    	}    	
    }     
}

void StopWatch(void)
{
    if (RUNNING == stopwatch_info.state)
    {
        stopwatch_info.sec++;

        if (stopwatch_info.sec >= 60)
        {
            stopwatch_info.sec &= RESET_MASK;
            stopwatch_info.min++;

            if (stopwatch_info.min >= 60)
            {
                stopwatch_info.min &= RESET_MASK;
                stopwatch_info.hr++;

                if (stopwatch_info.hr > 99)
                {
                    stopwatch_info.hr &= RESET_MASK;
                }
            }
        }
    }
}

u8 APP_RxByte;

void ProcessRxData(void)
{
    static u16* loc_edit_field;
    APP_RxByte = KPD_u8GetKey();

    switch (APP_RxByte)
    {
    case UP:
        if (TIME_MODE == APP_displayMode)
        {
            if (clock.mode == display)
            {
                clock.currentLine ^= 1;
            }
            else if (clock.mode == edit)
            {
                if(loc_edit_field==&(clock.time_info->day)) 
                {
                    if((((*loc_edit_field)^EDIT_MASK) < days_per_mon[clock.time_info->mon])) (*loc_edit_field)++;
                    else *loc_edit_field = EDIT_MASK+1;
                }
                else if((loc_edit_field==&(clock.time_info->mon))
                    || (loc_edit_field==&(clock.time_info->hr)))
                {
                    if((((*loc_edit_field)^EDIT_MASK) < 12)) (*loc_edit_field)++;
                    else *loc_edit_field = EDIT_MASK+1;
                }
                else if((loc_edit_field==&(clock.time_info->sec)) 
                     || (loc_edit_field==&(clock.time_info->min)))
                {
                    if((((*loc_edit_field)^EDIT_MASK) < 60)) (*loc_edit_field)++;
                    else *loc_edit_field = EDIT_MASK;
                } 
                else if((loc_edit_field==&(clock.time_info->year)) 
                     && (((*loc_edit_field)^EDIT_MASK) < 2099))
                {
                   (*loc_edit_field)++;
                }
                else if(loc_edit_field==&(clock.time_info->am_pm)) 
                {
                    *loc_edit_field = ((*loc_edit_field)^EDIT_MASK) == 'A'?
                                      'P' ^ EDIT_MASK : 'A' ^ EDIT_MASK; 
                }
            }
        }
        else
        {
            /* Ignore */
        }        
        break;

    case DOWN:
        if (TIME_MODE == APP_displayMode)
        {
            if (clock.mode == display)
            {
                clock.currentLine ^= 1;
            }
            else if (clock.mode == edit)
            {
                if((loc_edit_field==&(clock.time_info->day)) 
                 || (loc_edit_field==&(clock.time_info->mon))
                 || (loc_edit_field==&(clock.time_info->hr)))
                {
                    if((((*loc_edit_field)^EDIT_MASK) > 1)) (*loc_edit_field)--;
                }
                else if((loc_edit_field==&(clock.time_info->sec)) 
                     || (loc_edit_field==&(clock.time_info->min)))
                {
                    if((((*loc_edit_field)^EDIT_MASK) > 0)) (*loc_edit_field)--;
                } 
                else if((loc_edit_field==&(clock.time_info->year)) 
                     && (((*loc_edit_field)^EDIT_MASK) > 2000))
                {
                   (*loc_edit_field)--;
                }
                else if(loc_edit_field==&(clock.time_info->am_pm)) 
                {
                    *loc_edit_field = ((*loc_edit_field)^EDIT_MASK) == 'A'?
                                      'P' ^ EDIT_MASK : 'A' ^ EDIT_MASK; 
                }
            }
        }
        else 
        {
            /* Ignore */
        }        
        break;

    case LEFT_PAUSE:
        if (TIME_MODE == APP_displayMode)
        {
            if (clock.mode == display)
            {
                /* Ignore */
            }
            else if (clock.mode == edit)
            {
                if(clock.currentLine)
                {
                    if(loc_edit_field == &(clock.time_info->day)){/* Ignore */}
                    else 
                    {
                        *loc_edit_field ^= EDIT_MASK;
                        loc_edit_field--;
                        *loc_edit_field ^= EDIT_MASK;
                    }
                }
                else
                {
                    if(loc_edit_field == &(clock.time_info->hr)){/* Ignore */}
                    else
                    {
                        *loc_edit_field ^= EDIT_MASK;
                        loc_edit_field--;
                        *loc_edit_field ^= EDIT_MASK;
                    }
                }  
            }
        }
        else if(STOPWATCH_MODE == APP_displayMode)
        {
            if(stopwatch_info.state == PAUSED) stopwatch_info.state = RUNNING;
            else if(stopwatch_info.state == RUNNING) stopwatch_info.state = PAUSED;
            else {/* Do Nothing */}
        }
        break;

    case RIGHT_STOP:
        if (TIME_MODE == APP_displayMode)
        {
            if (clock.mode == display)
            {
                /* Ignore */
            }
            else if (clock.mode == edit)
            {
                if(clock.currentLine)
                {
                    if(loc_edit_field == &(clock.time_info->year)){/* Ignore */}
                    else 
                    {
                        *loc_edit_field ^= EDIT_MASK;
                        loc_edit_field++;
                        *loc_edit_field ^= EDIT_MASK;
                    }
                }
                else
                {
                    if(loc_edit_field == &(clock.time_info->am_pm)){/* Ignore */}
                    else 
                    {
                        *loc_edit_field ^= EDIT_MASK;
                        loc_edit_field++;
                        *loc_edit_field ^= EDIT_MASK;
                    }
                }  
            }
        }
        else if(STOPWATCH_MODE == APP_displayMode)
        {
            stopwatch_info.state = STOPPED;
        }
        break;

    case EDIT_START:
        if (TIME_MODE == APP_displayMode)
        {
            if (clock.mode == display)
            {
                //time_edit = time;
                clock.mode = edit;
                clock.periodicity = EDIT_CLK_PERIODICITY;
                //clock.time_info = &time_edit;            

                /**
                 * In edit mode
                 *  - if the first line is selected (edit time mode), the cursor position is 0
                 *  - if the second line is selected (edit date mode), the cursor position is 4
                */
                if(clock.currentLine) loc_edit_field = &(clock.time_info->day);
                else loc_edit_field = &(clock.time_info->hr);

                *loc_edit_field ^= EDIT_MASK;
            }
            else if (clock.mode == edit)
            {
                /* Ignore */
            }
        }
        else if(STOPWATCH_MODE == APP_displayMode)
        {
            stopwatch_info.state = RUNNING;
        }
        break;

    case MODE:
        APP_displayMode ^= 1;
        
        break;

    case OK_RESET:
        if (TIME_MODE == APP_displayMode)
        {
            if(edit == clock.mode)
            {
                *loc_edit_field ^= EDIT_MASK;
                //time = time_edit;
                clock.mode = display;
                clock.periodicity = DISPLAY_CLK_PERIODICITY;
                //clock.time_info = &time;
            }
            else
            {
                /* Ignore */
            }
        }
        else if(STOPWATCH_MODE == APP_displayMode)
        {
            stopwatch_info.ms = ZERO;
            stopwatch_info.sec = ZERO;
            stopwatch_info.min = ZERO;
            stopwatch_info.hr = ZERO;
        }
        break;
    
    default:
        break;
    }
}
