/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "H_UART/HUART.h"
#include "UART/UART.h"
#include "GPIO/GPIO.h"
#include "NVIC/NVIC.h"
#include "RCC/RCC.h"
#include "LED/LED.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

extern volatile uint32_t State ;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
/*The frame of the protocol over the uart */
uint8_t  Tx_Frame[4];
uint8_t Rx_Frame[4];
uint8_t Rx_Frame_Temp[3];
/*to provid a synchornization  with sending pprocess*/
 uint8_t Tx_State=1;
 uint8_t Rx_State=1;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

uint8_t CheckSum(uint8_t* Add_Farme,uint8_t  Copy_uint8_tLength)
{
   uint8_t chk=0;

   for(uint8_t i=0;i<Copy_uint8_tLength;i++)
   {
      chk-=Add_Farme[i];
   }
   return chk;
}

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
void Tx_Done(void)
{
   Tx_State=1;
}

void Rx_Done(void)
{
   Rx_State=1;
   ALIX_RecieveAsync(&State);

}



void  ALIX_Send (uint8_t Switch_Value)
{
   /*Build the frame which will be transmitted through  Uart Protocol*/
   Tx_Frame[0]='A';
   Tx_Frame[1]=Switch_Value;
   Tx_Frame[2]=CheckSum(Tx_Frame,2);
   Tx_Frame[3]='Z';

   /*Using UART to Send the Frame*/
   UART_TxBuffer(UART_1,Tx_Frame,4);
   
}


void  ALIX_SendAsync (uint8_t Switch_Value)
{

   /*Using UART to Send the Frame*/
   if(Tx_State==1)
   {
	   /*Build the frame which will be transmitted through  Uart Protocol*/
	   Tx_State=0;
	   Tx_Frame[0]='A';
	   Tx_Frame[1]=Switch_Value;
	   Tx_Frame[2]=CheckSum(Tx_Frame,2);
	   Tx_Frame[3]='Z';
	   UART_TxBufferAsync(UART_1,Tx_Frame,4,Tx_Done);

   }
  
}


HUART_ErrorStatus_t ALIX_RecieveAsync(uint8_t* Switch_Value)

{
   HUART_ErrorStatus_t Ret_ErrorState=HUART_NOK;
 

   if(Switch_Value==NULL)
   {
      Ret_ErrorState=HUART_NullPtr;

   }
   else
   {
	   uint8_t Temp;
      Ret_ErrorState=HUART_OK;
      uint8_t chk;
      /*UART_RxByte(UART_1,&Temp);
      if(Temp=='A')
      {
    	  UART_RxBufferAsync(UART_1,Rx_Frame_Temp,3,Rx_Done);
      }
*/

      if(Rx_State==1)
      {
										/* Rx_State=0;
										 Rx_Frame[0] = 'A';
										 Rx_Frame[1] = Rx_Frame_Temp[0];
										 Rx_Frame[2] = Rx_Frame_Temp[1];
										 Rx_Frame[3] = Rx_Frame_Temp[2];
										 	 */
    	 Rx_State=0;
    	 UART_RxBufferAsync(UART_1,Rx_Frame,4,Rx_Done);
         chk=CheckSum(Rx_Frame,2);
         if( (Rx_Frame[0]=='A') && (Rx_Frame[2]==chk) && (Rx_Frame[3]=='Z'))
           {
             *Switch_Value=Rx_Frame[1];
              //Rx_State=2;
           }

         else 
            {


               Ret_ErrorState=HUART_CorruptedFrame;
            }
      }
   }

   
   return Ret_ErrorState;

}

void H_UART_init(uint8_t* State)
    {

	    RCC_EnablePeripheral(RCC_USART1);
         UART_Init(UART_1);
         NVIC_EnableIRQ(USART1);
        /*Configure Tx Pin*/
         GPIO_strPin_t PinTx = {
         			.Pin = GPIO_PIN9,
         			.Port = GPIOA,
         			.Mode = AlternateFunction_PushPull,
         			.speed = High_Speed
         		};
         GPIO_initPin(&PinTx);

        /*Configure Rx Pin*/
        GPIO_strPin_t PinRx = {
        				.Pin = GPIO_PIN10,
        				.Port = GPIOA,
        				.Mode = AlternateFunction_PushPull,
        				.speed = High_Speed
        			};
        GPIO_initPin(&PinRx);
        GPIO_SetPinAF(GPIO_PIN9,GPIOA,AF7_USART1_USART2);
        GPIO_SetPinAF(GPIO_PIN10,GPIOA,AF7_USART1_USART2);
        ALIX_RecieveAsync(State);

    }
