#ifndef HAL_H_UART_HUART_H_
#define HAL_H_UART_HUART_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include  "STD_TYPES.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef enum
{
 HUART_OK,
 HUART_NOK,
 HUART_CorruptedFrame,
 HUART_NullPtr
}HUART_ErrorStatus_t;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
void H_UART_init(uint8_t* State);
void  ALIX_Send(uint8_t Switch_Value);
void  ALIX_SendAsync(uint8_t Switch_Value);

HUART_ErrorStatus_t ALIX_RecieveAsync(uint8_t* Switch_Value);





#endif // HAL_H_UART_HUART_H_
