/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "NVIC/NVIC.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define  NVIC_BASE_ADD  0xE000E100 

/*  Interrupt set-enable registers */
#define  NVIC_ISER  ((volatile uint32_t*) (NVIC_BASE_ADD))

/*  Interrupt clear-enable registers */
#define  NVIC_ICER  ((volatile uint32_t*) (NVIC_BASE_ADD+0x80))


/*  Interrupt set-pending registers */
#define  NVIC_ISPR  ((volatile uint32_t*) (NVIC_BASE_ADD+0x100))

/*  Interrupt clear-pending registers */
#define  NVIC_ICPR  ((volatile uint32_t*) (NVIC_BASE_ADD+0x180))


/*  Interrupt Active-Bit registers */
#define  NVIC_IABR   ((volatile uint32_t*) (NVIC_BASE_ADD+0x200))


/*  Interrupt priority registers */
#define NVIC_IPR      ((volatile uint8_t*) (NVIC_BASE_ADD+0x300))

/*Software trigger interrupt register*/
#define NVIC_STIR    *((volatile uint32_t*) (NVIC_BASE_ADD+0xE00))

  
#define OFFSET_4BIT  4

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

static uint32_t  GroupSubBits ;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

NVIC_enuErrorState_t NVIC_EnableIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index)
{

   uint8_t Reg_Num;
  uint8_t Bit_Num;
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 

   if(Copy_uint8_tIRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_uint8_tIRQ_Index/32;
     Bit_Num=Copy_uint8_tIRQ_Index%32;
     NVIC_ISER[Reg_Num]= (1<<Bit_Num);   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

NVIC_enuErrorState_t NVIC_DisableIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index)
{

   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
   uint8_t Reg_Num;
   uint8_t Bit_Num;
   
   if(Copy_uint8_tIRQ_Index<85)
   {
      Ret_ErrorState=NVIC_OK;
      Reg_Num=Copy_uint8_tIRQ_Index/32;
      Bit_Num=Copy_uint8_tIRQ_Index%32;
      NVIC_ICER[Reg_Num]= (1<<Bit_Num) ;
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

NVIC_enuErrorState_t NVIC_SetPendingIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index)
{
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
   uint8_t Reg_Num;
   uint8_t Bit_Num;

   if(Copy_uint8_tIRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_uint8_tIRQ_Index/32;
     Bit_Num=Copy_uint8_tIRQ_Index%32;
     NVIC_ISPR[Reg_Num]=(1<<Bit_Num);   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }
   return Ret_ErrorState;
};


NVIC_enuErrorState_t NVIC_ClearPendingIRQ(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index)

{
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
   uint8_t Reg_Num;
   uint8_t Bit_Num;
   if(Copy_uint8_tIRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_uint8_tIRQ_Index/32;
     Bit_Num=Copy_uint8_tIRQ_Index%32;
     NVIC_ICPR[Reg_Num]= (1<<Bit_Num);   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

NVIC_enuErrorState_t NVIC_GetActiveState(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index , uint8_t* Copy_uint8_tState)
{
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK;
   uint32_t LocReg;
   uint8_t Reg_Num;
   uint8_t Bit_Num;
   if(Copy_uint8_tIRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_uint8_tIRQ_Index/32;
     Bit_Num=Copy_uint8_tIRQ_Index%32;
     LocReg=NVIC_IABR[Reg_Num];
     *Copy_uint8_tState = (LocReg>>Bit_Num) & 1 ;
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

void NVIC_SetGroupSubBits(uint32_t Copy_uint32_tGroupSubBits)
{
    #define SCB_AIRCR   *((volatile uint32_t*)(0xE000ED0C))

    GroupSubBits= Copy_uint32_tGroupSubBits;
    SCB_AIRCR=Copy_uint32_tGroupSubBits;
};

NVIC_enuErrorState_t NVIC_SetPriority(NVIC_IRQ_ID_t  Copy_uint8_tIRQ_Index , uint8_t Copy_uint8_tGroupPriority ,uint8_t Copy_uint8_tSubPriority)
{
    NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
    uint8_t Local_Priority=0;

   if(Copy_uint8_tIRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Local_Priority= Copy_uint8_tSubPriority|(Copy_uint8_tGroupPriority <<((GroupSubBits-0xFA050300)/256));
     NVIC_IPR[Copy_uint8_tIRQ_Index]= Local_Priority<<OFFSET_4BIT;
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};
