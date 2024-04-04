/**
  ******************************************************************************
  * @file    SYSTICK.h
  * @author  Asmaa Newigy
  * @version V1.0.0
  * @date    12 March 2024
  * @brief   SYSTICK Driver
  *          Hewader file for SYSTICK core peripheral.
  ******************************************************************************
**/
#ifndef SYSTICK_H_
#define SYSTICK_H_

/*--------------------------------- Include Libraries ------------------------------*/
#include "SYSTICK_Config.h"

/*------------------------------------ Macros -------------------------------------*/
#define SYSTICK_PERIODICITY_ONE_TIME    (0U)
#define SYSTICK_PERIODICITY_INFINITE    (1U)

/*------------------------------------- Types -------------------------------------*/
typedef enum
{
    SYSTICK_OK,
    SYSTICK_NOK,
    SYSTICK_NULL_PTR,

}SYSTICK_ErrorStatus_t;

/*SysTick Call-Back Function Type*/
typedef void (*systickcbf_t) (void); 

/*--------------------------------- Function Prototypes ------------------------------*/
/*================================== SYSTICK_Start ==============================*/
/**
  * @brief  Start SysTick timer
  *       
  * @param  Systick_Period: SYSTICK_PERIODICITY_ONE_TIME , SYSTICK_PERIODICITY_INFINITE
  *         
  * @return SYSTICK_ErrorStatus_t 
  */
SYSTICK_ErrorStatus_t SYSTICK_Start(uint32_t Systick_Period);

/*================================== SYSTICK_Stop ==============================*/
/**
  * @brief  Stop SysTick timer
  *
  * @param  Void
  *         
  * @return Void 
  */
void SYSTICK_Stop(uint32_t Systick_Period);

/*================================== SYSTICK_SetTimeMS ==============================*/
/**
  * @brief Set Time in MilliSeconds to SysTick Timer 
  *
  * @param  Time in millisec
  *
  * @return SYSTICK_ErrorStatus_t 
  */
SYSTICK_ErrorStatus_t SYSTICK_SetTimeMS(uint32_t32 Time);

/*================================== SYSTICK_SetTimeMS ==============================*/
 /**
  * @brief Set callBack Function 
  *
  * @param  cbf : Function Name that takes void and returns void  
  *
  * @return SYSTICK_ErrorStatus_t 
  */
SYSTICK_ErrorStatus_t  SYSTICK_SetCallBack(systickcbf_t cbf);

/*================================== SYSTICK_Handler ==============================*/
/**
  * @brief  Systick Handler Function Implementation 
  *
  * @param  cbf : Function Name that takes void and returns void  
  *
  * @return SYSTICK_ErrorStatus_t 
  */
void  SYSTICK_Handler(void);

#endif //SYSTICK_H_ 