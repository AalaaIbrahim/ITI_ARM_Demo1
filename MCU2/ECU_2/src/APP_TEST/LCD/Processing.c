/*
 * Processing.c
 *
 *  Created on: Apr 9, 2024
 *      Author: NoteBook
 */
#include "Switch_App.h"
#include "LIB/STD_TYPES.h"
#include "StopWatch.h"
#include "Processing.h"
#include "H_UART/HUART.h"
#include "LED/LED.h"

volatile uint32_t State ;


uint8_t GState =0;
uint8_t STOP_WATCH_LOCAL_State =0;
extern uint8_t  StopWatch_Req_Type;
extern volatile uint8_t MoveCursorState;
extern uint8_t EditState ;

void Processing (void)
{
	//ALIX_RecieveAsync(&State);
	if (State == GLOBAL_STATE )
	{
		static uint8_t counter =0;
		counter++;
		if (counter == 1)
		{

			GState = Stop_Watch;

		}
		else
		{
			counter =0;
			GState = Digital_watch;
		}
		State = 0xff;
	}
   if (State == START_STATE)
	{

	   switch (GState)
	   {
	   case Digital_watch:
		   EditState =True;
		   break;
	   case Stop_Watch:
		   StopWatch_Req_Type = Start;
		   break;
	   }
		State = 0xff;




	}
	else if (State == RESET_STATE)
	{
		 switch (GState)
			   {
			   case Digital_watch:
				   EditState =False;
				   break;
			   case Stop_Watch:
					StopWatch_Req_Type = Reset;
				   break;
			   }
			State = 0xff;

	}
	else if (State == STOP_STATE)
	{
		switch (GState)
		 {
		 case Digital_watch:
			 MoveCursorState = 'R';
			   break;
		 case Stop_Watch:
				StopWatch_Req_Type = Stop;
			   break;
		 }
		State = 0xff;

	}
	else if (State == PAUSE_STATE)
	{
		static uint8_t counter =0;

			switch (GState)
			{
			case Digital_watch:
			{
				MoveCursorState = 'L';
			}
				break;
			case Stop_Watch:
			{
				counter++;
			    if (counter == 1)
			    {
			    	StopWatch_Req_Type = Pause;

			    }
			    else
			    {
			    	counter =0;
			    	StopWatch_Req_Type = Continue;
			    }
			}break;

						}
			State = 0xff;

			}





	else if (State == UP_STATE)
	{
		MoveCursorState = UP_STATE;
		State = 0xff;

	}
	else if (State == DOWN_STATE)
	{
		MoveCursorState = DOWN_STATE;
		State = DEFAULT_VALUE;

	}


}



