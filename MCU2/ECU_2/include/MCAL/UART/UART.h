#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "LIB/STD_TYPES.h"
#include "UART_config.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define UART_1   (void*)0x40011000 //--->Both 1&6 on the APB2
#define UART_6   (void*)0x40011400
#define UART_2   (void*)0x40004400


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

void UART_Init(void* Copy_UartID);

void UART_TxByte(void* Copy_UartID,uint8_t Copy_uint8_tByte);
void UART_TxBuffer(void* Copy_UartID, uint8_t* Copy_AddTxBuffer, uint16_t Copy_uint16_tLength);
void UART_TxByteAsync(void* Copy_UartID, uint8_t Copy_uint8_tByte,void(*fptr)(void));
void UART_TxBufferAsync (void* Copy_UartID, uint8_t* Copy_AddTxBuffer , uint16_t Copy_uint16_tLength,void(*fptr)(void));

void UART_RxByte(void* Copy_UartID, uint8_t* Copy_AddRxByte);
void UART_RxBuffer(void* Copy_UartID, uint8_t* Copy_AddRxBuffer,uint16_t Copy_uint16_tLength);
void UARt_RxByteAsync(void* Copy_UartID, uint8_t* Copy_AddRxByte);
void UART_RxBufferAsync(void* Copy_UartID, uint8_t* Copy_AddRxBuffer, uint16_t Copy_uint16_tLength,void(*fptr)(void));


#endif // MCAL_UART_UART_H_
