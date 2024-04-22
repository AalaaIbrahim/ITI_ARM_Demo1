/*
 * Sched_Config.c
 *
 *  Created on: Mar 17, 2024
 *      Author: NoteBook
 */

#include "SCHED/Sched.h"


//extern void TrafficLights(void);
//extern void App1_Runnable (void);
extern void LCD_TASK (void);
extern void DigitalWatchCalc(void);
extern void Display (void);
extern void StopWatch_Process(void);
extern void Switch_APP(void);
extern  void SW_GetState(void);
extern void Processing (void);
volatile Runnable_t Runnables_Arr[_Max_RUNNABLE_NUM] =
{
    [Runnable_1] = {
    				.name = "LCD",
					.PeriodicityMs = 2,
					.Priority = 0,
					.CallBack = LCD_TASK,
					.DelayMs = 0
    },

	[Runnable_2] = {
					.name = "SW_GetState",
					.PeriodicityMs = 5,
					.Priority = 1,
					.CallBack = SW_GetState,
					.DelayMs = 0
		    },

	[Runnable_4] = {
					.name = "Switch_APP",
					.PeriodicityMs = 200,
					.Priority = 2,
					.CallBack = Switch_APP,
					.DelayMs = 1},

	[Runnable_3] = {
				    .name = "Processing",
				    .PeriodicityMs = 100,
				    .Priority = 3,
				    .CallBack = Processing,
				    .DelayMs = 2},


	 [Runnable_5] = {
				   .name = "Display",
				   .PeriodicityMs = 200,
				   .Priority = 4,
				   .CallBack = Display,
				   .DelayMs = 1
					 		},

	[Runnable_6] = {
	        		.name = "DigitalWatchCalc",
					.PeriodicityMs = 100,
					.Priority = 5,
					.CallBack = DigitalWatchCalc,
					.DelayMs = 1
    							},

	 [Runnable_7] = {
				     .name = "StopWatch_Process",
					 .PeriodicityMs = 200,
					 .Priority = 6,
					 .CallBack = StopWatch_Process,
					 .DelayMs = 1
							    }







};
