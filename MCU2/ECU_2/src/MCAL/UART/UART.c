/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "UART/UART.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define SAMPLE_OVER16 16
#define SAMPLE_OVER8   8



/*Mask For Status Reg*/
#define  TXF  0x80
#define  TXCF 0x40
#define  RXF  0x20



/* Mask For CTR1   Register*/
#define UART_EN         0x2000
#define RX_EN           0x0004
#define TX_EN           0x0008
#define IDL_IE          0x0010
#define RX_IE           0x0020
#define TXC_IE          0x0040
#define TX_IE           0x0080
#define PR_IE           0x0100




/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;


}UART_RegDef_t;

typedef void(*CallBack_t)(void);

typedef enum
{
     Ready,
     Busy
}UART_enuState_t;

/*Need to struct because Uart Full Dublex -> transmit and recieve at the same time */

typedef struct 
{
    uint8_t* Data;
    uint16_t Size;
    uint16_t Position;
    CallBack_t CB;
    uint8_t State;
    volatile  UART_RegDef_t* Uart;
        
}UART_strTxReq_t;

typedef struct 
{
    uint8_t* Data;
    uint16_t Size;
    uint16_t Position;
    CallBack_t CB;
    uint8_t State;
    volatile  UART_RegDef_t* Uart;
        
}UART_strRxReq_t;

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
 static UART_strTxReq_t  TxReq;
 static UART_strRxReq_t  RxReq;


/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void UART_Init(void* Copy_UartID)
{ 
    volatile UART_RegDef_t* Uart;
    Uart=(UART_RegDef_t*)Copy_UartID;
     
     uint16_t  Fraction;
     uint16_t Mantesa;
     uint32_t Loc_UartDiv =((uint64_t)SYS_FRQ*1000)/(UART_SAMPLE *UART_BR);
    
      /*to Extract integer value*/
     Mantesa=Loc_UartDiv/1000;
     Fraction=(Loc_UartDiv%1000)*16;
    if(Fraction%1000 >=500)
    {
        Fraction=(Fraction/1000)+1;
    }
    else
    {
        Fraction=Fraction/1000;
    }
    /*This Part to Handel Carry */
    if(Fraction>=0x10)
    {
        Mantesa+= Fraction & (0xF0);
    }


    /*Configur the BoadRate of UART -> we can enhance this feature through applying the equation*/
    Uart->BRR=(Mantesa<<4)|(Fraction& 0x0F);

    /*#if UART_BR == 9600
        Uart->BRR=0x683;
    #elif UART_BR == 115200
        Uart->BRR=0x86;
    #endif
     */
    /*through the CTR1 we can control: 

       01-Data Length;
       02-Party(Enable,Selection,Intrupt);
       03-Sample Rate 
       04-Uart Enable 
       05-Transmiter Enable 
       06-Reciever Enable 
       07-enable Interrupt of (Tx & Rx Flags)

    */

    /*Enable UART*/
    Uart->CR1|=UART_EN;
    /*  Enable Tx  */
     Uart->CR1|=TX_EN;
    /*Enable Rx*/
    Uart->CR1|=RX_EN;

    Uart->SR=0;
   //Keep Default Configuration For Sample(16) and Data Lenth (8)
}


void UART_TxByte(void* Copy_UartID,uint8_t Copy_uint8_tByte)
{
    volatile  UART_RegDef_t* Uart;
    uint16_t Loc_Counter=3000;
    Uart=(UART_RegDef_t*)Copy_UartID;

    Uart->DR=Copy_uint8_tByte;

    /*wait until the Transmit* empty flag raised  or Timeout*/
    while( ((Uart->SR & TXF) ==0) && (Loc_Counter>0))
    {
        Loc_Counter--;
    }


}

void UART_TxBuffer(void* Copy_UartID, uint8_t* Copy_AddTxBuffer, uint16_t Copy_uint16_tLength)
{
    volatile UART_RegDef_t* Uart;
    uint16_t Loc_Counter=7000;
    Uart=(UART_RegDef_t*)Copy_UartID;

   for(uint16_t i=0; i<Copy_uint16_tLength; i++ )
   {
       Uart->DR=Copy_AddTxBuffer[i];
      while( ((Uart->SR & TXCF) ==0 ) && (Loc_Counter>0) )
      {
         Loc_Counter--;
      }
      
      Uart->SR &= ~TXCF;
   }

}

void UART_RxByte(void* Copy_UartID, uint8_t* Copy_AddRxByte)
{
    volatile UART_RegDef_t* Uart;
    uint16_t Loc_Counter=3000;

    Uart=(UART_RegDef_t*)Copy_UartID;
   
   /*Polling till the Recieve Flage Raised  Or TimeOut  */
   while ( ((Uart->SR&RXF)==0 ) && (Loc_Counter>0) )
   {
      Loc_Counter--;
   };

   *Copy_AddRxByte= (Uart->DR) & 0xFF;
    
}
void UART_RxBuffer(void* Copy_UartID, uint8_t* Copy_AddRxBuffer,uint16_t Copy_uint16_tLength)
{
    volatile UART_RegDef_t* Uart;
    uint16_t Loc_Counter=7000;

    Uart=(UART_RegDef_t*)Copy_UartID;

    for(uint16_t i=0; i<Copy_uint16_tLength; i++)
    {
        /*Polling till the Recieve Flage Raised  or TimeOut Happen*/
         while ( ((Uart->SR&RXF)==0) && (Loc_Counter>0) )
         {
            Loc_Counter--;
         }
         Copy_AddRxBuffer[i]= (Uart->DR) & 0xFF;
     
    }
}


void UART_TxBufferAsync(void* Copy_UartID, uint8_t* Copy_AddTxBuffer , uint16_t Copy_uint16_tLength,void(*fptr)(void))
{
   if (TxReq.State==Ready)
   {
    /*Buffer the request*/
     TxReq.State=Busy;
     TxReq.Data=Copy_AddTxBuffer;
     TxReq.Size=Copy_uint16_tLength;
     TxReq.Position=0;
     TxReq.CB=fptr;
     TxReq.Uart=(UART_RegDef_t*)Copy_UartID;

   
     /*Enable the interrupt*/
    TxReq.Uart->CR1 |= TX_IE;

    /*Send the first Byte Here to fire the intrrrupt */
    TxReq.Uart->DR=TxReq.Data[TxReq.Position];
    //TxReq.Position++;

   
   }
   

}


void UART_RxBufferAsync(void* Copy_UartID, uint8_t* Copy_AddRxBuffer, uint16_t Copy_uint16_tLength,void(*fptr)(void))
{
    if (RxReq.State==Ready)
   {
    /*Buffer the request*/
     RxReq.State=Busy;
     RxReq.Data=Copy_AddRxBuffer;
     RxReq.Size=Copy_uint16_tLength;
     RxReq.Position=0;
     RxReq.CB=fptr;
     RxReq.Uart=(UART_RegDef_t*)Copy_UartID;

    /*Enable the interrupt*/
     RxReq.Uart->CR1 |= RX_IE;
  
   }
}



void  USART1_IRQHandler (void)
{
   if(TxReq.Uart->SR&TXF)
   {
      if(TxReq.Position< (TxReq.Size-1))
      {
         TxReq.Position++;
        TxReq.Uart->DR=TxReq.Data[TxReq.Position];
       
      }

      else
      {
         TxReq.Uart->CR1 &= ~TX_IE;
         TxReq.State=Ready;
         if(TxReq.CB!=NULL)
          {
                TxReq.CB();
          }
      }
       
   }



 if(RxReq.Uart->SR&RXF)
    {
      if(RxReq.Position<RxReq.Size)
       { 
        RxReq.Data[RxReq.Position]= (RxReq.Uart->DR)&0xFF;
        RxReq.Position++;
       }

      if(RxReq.Position==RxReq.Size)
       {
         RxReq.Uart->CR1 &= ~RX_IE;
         RxReq.State=Ready;
          if(RxReq.CB)
          {
            RxReq.CB();
          }  
       }  
   }
}


