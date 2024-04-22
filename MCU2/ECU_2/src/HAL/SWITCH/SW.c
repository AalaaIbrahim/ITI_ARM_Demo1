#include "SWITCH/SW.h"
#include "MCAL/GPIO/GPIO.h"

#define Sw_4BIT_OFFSET 2

static  uint8_t Sw_StableState [_Switch_Num]={0,0,0};

//static  u8 G_SwitchName;

extern SW_SwitchConfig_t Switches[_Switch_Num];

void SW_Init(void)
{

	GPIO_strPin_t pin;

     pin.speed =Medium_Speed;
     for (uint8_t index=0 ;index < _Switch_Num ; index++)
     {
        pin.Port=Switches[index].Port;
        pin.Pin=Switches[index].Pin;
        pin.Mode=Switches[index].Connect;
        GPIO_initPin(&pin);
     }


}

/*it gonna be runneble which is run each 5 ms*/
 void SW_GetState(void)
{
   static uint8_t Counter[_Switch_Num]={0};
   static uint8_t prev_state[_Switch_Num]={0};
   uint8_t cur_state;

   uint32_t PinValue;
   //u8 SwitchName=G_SwitchName;
    for(uint8_t i=0 ; i <_Switch_Num ;i++)
    {
        GPIO_GetPinValue(Switches[i].Pin,Switches[i].Port,&PinValue);
        cur_state=  (PinValue) ^ (Switches[i].Connect >> Sw_4BIT_OFFSET);

        if(cur_state==prev_state[i])
        {
            Counter[i]++;
        }
        else
        {
             Counter[i]=0;
        }

        if(Counter[i]==5)
        {
            Sw_StableState[i]=cur_state;
            Counter[i]=0  ;
        }

         prev_state[i]=cur_state;

    }



}


void SW_GetSwitchState(uint8_t SwitchName ,uint8_t*  state)
{

   //G_SwitchName=SwitchName ;
   *state=Sw_StableState[SwitchName];

}

/*
void SW_GetSwitchState(u8 SwitchName ,u8*  state)
{
     u8 PinValue;
     GPIO_GetPinValue(Switches[SwitchName].Port,Switches[SwitchName ].Pin,&PinValue);
     *state=  (PinValue) ^ (Switches[SwitchName ].Connect >> Sw_4BIT_OFFSET);
}
*/
