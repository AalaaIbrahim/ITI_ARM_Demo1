
#include "SWITCH/SW.h"
#include "MCAL/GPIO/GPIO.h"

SW_SwitchConfig_t Switches[_Switch_Num]=
{
   [Switch1]={
                .Port=GPIOB,
                .Pin=GPIO_PIN8,
                .Connect=Input_PullUp
             },
   [Switch2]={
                .Port=GPIOB,
                .Pin=GPIO_PIN9,
                .Connect=Input_PullUp
             },
   [Switch3]={
                .Port=GPIOB,
                .Pin=GPIO_PIN10,
                .Connect=Input_PullUp
             },
	[Switch4]={
			    .Port=GPIOB,
			    .Pin=GPIO_PIN12,
			    .Connect=Input_PullUp
			  },
	[Switch5]={
			      .Port=GPIOB,
				  .Pin=GPIO_PIN13,
			      .Connect=Input_PullUp
			  },
	[Switch6]={
			      .Port=GPIOB,
			      .Pin=GPIO_PIN14,
			      .Connect=Input_PullUp
              },
     [Switch7]={
			       .Port=GPIOB,
			       .Pin=GPIO_PIN15,
			       .Connect=Input_PullUp
	         	}


};

