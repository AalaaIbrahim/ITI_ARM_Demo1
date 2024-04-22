/*
 * @file  : sched_cfg.c
 * @brief : API implementations for scheduler
 * @author: Alaa Hisham
 * @date  : 15-03-2024
 */

/*===========================================================================================================*/
/*												    Includes	 										     */
/*===========================================================================================================*/
#include "sched.h"
#include "sched_cfg.h"


const Runnable_t Sched_Runnables[_TotalRunnables] = 
{
	//[LED1] = {.periodicity = 500, .firstDelay = 0, .cb=led1},
    //[LED2] = {.periodicity = 1000, .firstDelay = 0, .cb=led2},
    [LCD] = {.periodicity = 2, .firstDelay = 5, .cb=LCD_Runnable},
    [LCD_APP] = {.periodicity = 50, .firstDelay = 100, .cb = LCD_app},
    [DateTime] = {.periodicity = 1000, .firstDelay = 1100, .cb = updateDateTime},
    [KPD] = {.periodicity = 5, .firstDelay = 300, .cb = KPD_Runnable},
    [RX] = {.periodicity = 100, .firstDelay = 501, .cb = ProcessRxData},
    [SW] = {.periodicity = 100, .firstDelay = 1110, .cb = StopWatch},
    [SEND] = {.periodicity = 200, .firstDelay = 502, .cb = SendCommand}
};