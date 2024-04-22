
#include "LIB/STD_TYPES.h"
#include "SWITCH/SW.h"
#include "LED/LED.h"
#include "NVIC/NVIC.h"
#include "StopWatch.h"
#include "Switch_App.h"
#include "H_UART/HUART.h"
#define DIGITAL_CLOCK	0
#define STOP_WATCH	1
//uint32_t State = 0;

void Switch_APP(void)
{
    uint8_t state[7] = {0};
  
	static uint8_t counter =0;

    

  
    SW_GetSwitchState( Switch1,&state[0]); //Mode	8
    SW_GetSwitchState( Switch2,&state[1]);	//Start	 or edit 9
    SW_GetSwitchState( Switch3,&state[2]);	//Reset	or ok   10
    SW_GetSwitchState( Switch4,&state[3]);	//STOP	or right12
    SW_GetSwitchState( Switch5,&state[4]);	//Pause	or left 13
    SW_GetSwitchState( Switch6,&state[5]);	//UP	14
    SW_GetSwitchState( Switch7,&state[6]);	//Down	15


//Will be Optmised by for loop
    if(state[0] == SW_STATE_PRESSED)
    {

    		//State	= GLOBAL_STATE;
    	ALIX_SendAsync(GLOBAL_STATE);
    }
    else if (state[1] == SW_STATE_PRESSED)
    {
    	//State	= START_STATE;
    	ALIX_SendAsync(START_STATE);

    }
    else if (state[2] == SW_STATE_PRESSED)
    {
    	//State	= RESET_STATE;
    	ALIX_SendAsync(RESET_STATE);


    }
    else if (state[3] == SW_STATE_PRESSED)
        {
        	//State	= STOP_STATE;
    	ALIX_SendAsync(STOP_STATE);


        }
    else if (state[4] == SW_STATE_PRESSED)
           {
           	//State	= PAUSE_STATE;
    	ALIX_SendAsync(PAUSE_STATE);


           }

    else if (state[5] == SW_STATE_PRESSED)
               {
               	//State	= UP_STATE;
    	ALIX_SendAsync(UP_STATE);


               }
    else if (state[6] == SW_STATE_PRESSED)
                   {
                   	//State	= DOWN_STATE;
    	ALIX_SendAsync(DOWN_STATE);


                   }
    else
    {
		//LED_SetStatus(LED_GREEN,LED_STATUS_OFF);

    }


    






   
}
