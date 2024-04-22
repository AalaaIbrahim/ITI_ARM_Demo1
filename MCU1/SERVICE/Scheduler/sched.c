/*
 * @file  : sched.c
 * @brief : API implementations for scheduler
 * @author: Alaa Hisham
 * @date  : 15-03-2024
 */

/*===========================================================================================================*/
/*												    Includes		 										 */
/*===========================================================================================================*/
#include "STD_TYPES.h"

#include "NVIC.h"
#include "HSYSTICK.h"
#include "sched.h"
#include "sched_cfg.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef struct
{
	Runnable_t *runnable;
	u32 remainingTimeMs;
}RunnableInfo_t;

/*===========================================================================================================*/
/*										  	   Global Variables											     */
/*===========================================================================================================*/

extern Runnable_t Sched_Runnables[_TotalRunnables];

static RunnableInfo_t RunInfoArr[_TotalRunnables];

static u32 pendingTicks = ZERO;

/*===========================================================================================================*/
/*										  	   Private Functions											     */
/*===========================================================================================================*/

static void tickcb(void)
{
	pendingTicks++;
}

static void sched(void)
{
	u32 idx;
	for(idx = 0; idx < _TotalRunnables; idx++)
	{
		if(RunInfoArr[idx].runnable && (RunInfoArr[idx].runnable)->cb && RunInfoArr[idx].remainingTimeMs == 0)
		{

			RunInfoArr[idx].runnable->cb();

			RunInfoArr[idx].remainingTimeMs = RunInfoArr[idx].runnable->periodicity;
		}

		RunInfoArr[idx].remainingTimeMs -= SCHED_TICK_TIME_MS;

	}
}

/*===========================================================================================================*/
/*										  	   Private Functions											     */
/*===========================================================================================================*/

void sched_init(void)
{
	u32 Priority = 0;
    
    for (Priority = 0; Priority < _TotalRunnables; ++Priority)
    {
        RunInfoArr[Priority].runnable = &Sched_Runnables[Priority];
        RunInfoArr[Priority].remainingTimeMs = Sched_Runnables[Priority].firstDelay;
    }

	//NVIC_EnableIRQ(SysTick_IRQn);
	HSYSTICK_Init();
	HSYSTICK_SetCBF(tickcb);
}

void sched_start(void)
{
	HSYSTICK_DelayMs(SCHED_TICK_TIME_MS, H_Periodic);
	while(1)
	{
		if(pendingTicks)
		{
			pendingTicks--;
			sched();
		}
	}
}

