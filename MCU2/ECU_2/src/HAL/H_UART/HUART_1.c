

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "H_UART/HUART.h"
#include "MCAL/UART/UART.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define GET_HAMMING_FORMAT(BYTE) (((uint16_t)((BYTE&0x80)<<2))|((uint16_t)((BYTE&0x70)<<1))|((uint16_t)(BYTE&0X0F)))
#define GET_DECODED_FORMAT(HAM)  ((HAM_b7(HAM)<<7)|(HAM_b6(HAM)<<6)|(HAM_b5(HAM)<<5)|(HAM_b4(HAM)<<4)|(HAM_b3(HAM)<<3)|(HAM_b2(HAM)<<2)|(HAM_b1(HAM)<<1)|HAM_b0(HAM))

#define HAM_b7(CODE)    ((CODE>>9)&1)
#define HAM_b6(CODE)    ((CODE>>7)&1)
#define HAM_b5(CODE)    ((CODE>>6)&1)
#define HAM_b4(CODE)    ((CODE>>5)&1)
#define HAM_b3(CODE)    ((CODE>>3)&1)
#define HAM_b2(CODE)    ((CODE>>2)&1)
#define HAM_b1(CODE)    ((CODE>>1)&1)
#define HAM_b0(CODE)    ((CODE>>0)&1)


#define HAM_P1_MASK     0x0800
#define HAM_P2_MASK     0x0400
#define HAM_P4_MASK     0x0100
#define HAM_P8_MASK     0x0010

#define HAM_P1_INDEX    11
#define HAM_P2_INDEX    10
#define HAM_P4_INDEX    8
#define HAM_P8_INDEX    4

#define START_INDEX 0
#define DATA_INDEX 1
#define END_INDEX 2


#define OFFSET_12BIT 12

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/*
//The frame of the protocol over the uart 
uint8_t  Tx_Frame[4];
uint8_t Rx_Frame[4];
//to provid a synchornization  with sending pprocess
 uint8_t Tx_State;
 uint8_t Rx_State;

*/

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


uint16_t   calculateHammingCode(uint8_t data)
{// b3->b7  b5->b6  b6->b5  b7->b4  b9->b3  b10->b2  b11->b1 B12->B0
    uint16_t   hammingCode = GET_HAMMING_FORMAT(data);

    /* Calculate parity bits */ 
    uint16_t   p1 = HAM_b7(hammingCode) ^ HAM_b6(hammingCode) ^ HAM_b4(hammingCode) ^ HAM_b3(hammingCode) ^ HAM_b1(hammingCode);
    uint16_t   p2 = HAM_b7(hammingCode) ^ HAM_b5(hammingCode) ^ HAM_b4(hammingCode) ^ HAM_b2(hammingCode) ^ HAM_b1(hammingCode);
    uint16_t   p4 = HAM_b6(hammingCode) ^ HAM_b5(hammingCode) ^ HAM_b4(hammingCode) ^ HAM_b0(hammingCode);
    uint16_t   p8 = HAM_b3(hammingCode) ^ HAM_b2(hammingCode) ^ HAM_b1(hammingCode) ^ HAM_b0(hammingCode);

    hammingCode |= (p1<<HAM_P1_INDEX) | (p1<<HAM_P2_INDEX) | (p1<<HAM_P4_INDEX) | (p1<<HAM_P8_INDEX);

    return hammingCode;
}


uint8_t HammingDecode(uint16_t   code)
{
    uint8_t wrong_bit_index = 0;
    uint8_t data = 0;

    // Calculate parity bits
    uint16_t   p1 = HAM_b7(code) ^ HAM_b6(code) ^ HAM_b4(code) ^ HAM_b3(code) ^ HAM_b1(code);
    uint16_t   p2 = HAM_b7(code) ^ HAM_b5(code) ^ HAM_b4(code) ^ HAM_b2(code) ^ HAM_b1(code);
    uint16_t   p4 = HAM_b6(code) ^ HAM_b5(code) ^ HAM_b4(code) ^ HAM_b0(code);
    uint16_t   p8 = HAM_b3(code) ^ HAM_b2(code) ^ HAM_b1(code) ^ HAM_b0(code);

    if(p1 != (code&HAM_P1_MASK)>>HAM_P1_INDEX) wrong_bit_index += 1;
    if(p2 != (code&HAM_P2_MASK)>>HAM_P2_INDEX) wrong_bit_index += 2;
    if(p4 != (code&HAM_P4_MASK)>>HAM_P4_INDEX) wrong_bit_index += 4;
    if(p8 != (code&HAM_P8_MASK)>>HAM_P8_INDEX) wrong_bit_index += 8;

    if(wrong_bit_index)
    {
        if(wrong_bit_index <= 12)
        {
            /* Toggle the corrupted bit */
            code ^= (1<<wrong_bit_index);

            data = GET_DECODED_FORMAT(code);
        }
        else
        {
            // multiple bit errors, discard data
        }
    }
    else
    {
        /* Data received correctly */
        data = GET_DECODED_FORMAT(code);
    }
        
    return data;
}


/*
void Tx_Done(void)
{
   Tx_State=1;
}

void Rx_Done(void)
{
   Rx_State=1;
}

void  ALIX_Send (uint8_t Switch_Value)
{
   //Build the frame which will be transmitted through  Uart Protocol
   uint8_t* ptr=NULL;
   Tx_Frame[0]='A';
   Tx_Frame[1]=Switch_Value;
   uint16_t res=calculateHammingCode(Tx_Frame[1]) & 0x0FFF;
   res |=   (0x03)<<12;
   ptr=&res;
   Tx_Frame[2]=*ptr;
   Tx_Frame[3]=*(ptr++);

   //Using UART to Send the Frame
   UART_TxBuffer(UART_1,Tx_Frame,4);
}


void  ALIX_SendAsync (uint8_t Switch_Value)
{
   //Build the frame which will be transmitted through  Uart Protocol
   uint8_t* ptr=NULL;
   Tx_Frame[0]='A';
   Tx_Frame[1]=Switch_Value;
  uint16_t res=calculateHammingCode(Tx_Frame[1]) & 0x0FFF;
   res |=   (0x03)<<12;
   ptr=&res;
   Tx_Frame[2]=*ptr;
   Tx_Frame[3]=*(++ptr);


   Tx_State=0;
   //Using UART to Send the Frame
   UART_TxBufferAsync(UART_1,Tx_Frame,4,Tx_Done);
  
}


HUART_ErrorStatus_t ALIX_RecieveAsync(uint8_t* Switch_Value)

{
   HUART_ErrorStatus_t Ret_ErrorState=HUART_NOK;
   uint8_t* ptr=NULL;
   uint16_t code;
   uint8_t data;



   if(Switch_Value==NULL)
   {
      Ret_ErrorState=HUART_NullPtr;
   }
   else
   {
      Ret_ErrorState=HUART_OK;

      UART_RxBufferAsync(UART_1,Rx_Frame,4,Rx_Done);

      if(Rx_State==1)
      {
         Rx_State=0;
        
         code=((Rx_Frame[4]&0x0f)<<8) | Rx_Frame[3];
         data=HammingDecode(code);
         if( (Rx_Frame[0]=='A') && (Rx_Frame[1]==data) && (((Rx_Frame[3]&0xf0)>>4)==3) )
           {
             *Switch_Value=Rx_Frame[1];
              Rx_State=2;
           }

         else 
            {
               Ret_ErrorState=HUART_CorruptedFrame;
            }
      }
   }

   
   return Ret_ErrorState;

}

*/
