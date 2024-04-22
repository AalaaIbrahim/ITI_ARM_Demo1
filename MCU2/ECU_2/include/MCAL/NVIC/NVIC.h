#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "NVIC_STM32401.h"
#include "LIB/STD_TYPES.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define GROUP_4BIT_SUB_0BIT   0xFA050300   //4 Bits f0r Group - 0 Bit For SubGroup
#define GROUP_3BIT_SUB_1BIT   0xFA050400
#define GROUP_2BIT_SUB_2BIT   0xFA050500
#define GROUP_1BIT_SUB_3BIT   0xFA050600
#define GROUP_0BIT_SUB_4BIT   0xFA050700


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum
{
   NVIC_OK,
   NVIC_NOT_OK,
   NVIC_IRQID_Not_Valid
}NVIC_enuErrorState_t;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

NVIC_enuErrorState_t NVIC_EnableIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index);
NVIC_enuErrorState_t NVIC_DisableIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index);

NVIC_enuErrorState_t NVIC_SetPendingIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index);
NVIC_enuErrorState_t NVIC_ClearPendingIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index);

NVIC_enuErrorState_t NVIC_GetActiveState(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index , uint8_t* Copy_uint8_tState);

void NVIC_SetGroupSubBits (uint32_t Copy_uint32_tGroupSubBits);
NVIC_enuErrorState_t NVIC_SetPriority(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index , uint8_t Copy_uint8_tGroupPriority ,uint8_t Copy_uint8_tSubPriority);

NVIC_enuErrorState_t NVIC_SetSoftwareINT(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index );





#endif // MCAL_NVIC_NVIC_H_
