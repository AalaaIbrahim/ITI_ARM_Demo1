/*
 * LCD_Test.c
 *
 *  Created on: Mar 24, 2024
 *      Author: NoteBook
 */


#include "SCHED/Sched.h"
#include "RCC/RCC.h"
#include "GPIO/GPIO.h"

#include "../../HAL/LCD/LCD.h"
#include "LED/LED.h"
#include "SWITCH/SW.h"
#include "H_UART/HUART.h"

/*
extern uint8_t Hours;
extern uint8_t Minutes ;
extern uint8_t Seconds;
extern uint16_t Mseconds ;
*/
extern volatile uint32_t State ;

int main (void)
{
 volatile uint8_t data = 0;

	//Enable RCC Peripheral
		        RCC_EnableSystemClock(Clock_HSE);
				RCC_SelectSystemClock(Clock_HSE);
				RCC_EnablePeripheral(RCC_GPIOA);
				RCC_EnablePeripheral(RCC_GPIOB);
				LED_init();
				LCD_Init();
				Sched_init();
				LCD_ClearScreen();
				SW_Init();
				H_UART_init(&State);

				Sched_Start();







	return 0;
}
