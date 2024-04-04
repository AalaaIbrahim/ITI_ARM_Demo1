/**
  ******************************************************************************
  * @file    SYSTICK.c
  * @author  Asmaa Newigy
  * @version V1.0.0
  * @date    12 March 2024
  * @brief   SYSTICK driver.
  *          Source file for the SYSTICK driver.
  ******************************************************************************
**/
/*--------------------------------- Include Libraries ------------------------------*/
#include "Std_Types.h"
#include "SYSTICK.h"

/*------------------------------------ Macros -------------------------------------*/
#define SYSTICK_BASE_ADDRESS                0xE000E010  

#define SYSTICK_TICK_INT                   0x00000002
#define SYSTICK_CLK_SOURCE_AHB_DIV_BY_8    0x00000000
#define SYSTICK_CLK_SOURCE_AHB             0x00000004
#define SYSTICK_ACTIVATE_HANDLER			(1U)
#define SYSTICK_NOT_ACTIVATE_HANDLER		(0U)

#define SYSTICK_ENABLE_MASK                 0x00000001
#define SYSTICK_LOAD_MASK                 	    0x00FFFFFF
#define SYSTICK_MAX_COUNT_MS                	0x00FFFFFF
#define SYSTICK_COUNTFLAG_MASK         	        0x00010000

/*------------------------------------- Types -------------------------------------*/
typedef struct
{
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
    uint32_t CALIB;
}SYSTICKTK_Registers_t;

volatile SYSTICKTK_Registers_t * const SYSTICKTK= (volatile SYSTICKTK_Registers_t*) SYSTICK_BASE_ADDRESS;

static systickcbf_t APP_cbf= NULL;

static uint8_t Periodicity= SYSTICK_PERIODICITY_ONE_TIME;

static uint8_t Counter=SYSTICK_ACTIVATE_HANDLER;
/*--------------------------------- Functions Implementation ------------------------------------*/
/*================================== SYSTICK_Start ==============================*/
/**
  * @brief  Start SysTick timer
  *       
  * @param  Systick_Period: SYSTICK_PERIODICITY_ONE_TIME , SYSTICK_PERIODICITY_INFINITE
  *         
  * @return SYSTICK_ErrorStatus_t 
  */
SYSTICK_ErrorStatus_t SYSTICK_Start(uint32_t Systick_Period)
{
	SYSTICK_ErrorStatus_t RET_ErrorStatus= SYSTICK_Ok;
	
	if(Systick_Period>SYSTICK_PERIODICITY_INFINITE)
	{
		RET_ErrorStatus = SYSTICK_NOK;
	}
	else
	{
		/*Enable Interrupts*/
        SYSTICKTK->CTRL|=SYSTICK_TICK_INT;
		/*Set Systick Clock Source*/
        SYSTICKTK->CTRL=SYSTICK_CLK_SOURCE;
		/*Reset Timer*/
        SYSTICKTK->VAL=0;
        /*Check on Peridicity*/
        Periodicity=Systick_Period;      
        /*Activate Handler*/
        Counter=SYSTICK_ACTIVATE_HANDLER;  
        /*Enable Timer*/
        SYSTICKTK->CTRL|=SYSTICK_ENABLE_MASK;
	}
	return RET_ErrorStatus;

}

/*================================== SYSTICK_Stop ==============================*/
/**
  * @brief  Stop SysTick timer
  *
  * @param  Void
  *         
  * @return Void 
  */
void SYSTICK_Stop(uint32_t Systick_Period)
{
	 SYSTICKTK->CTRL &=~SYSTICK_ENABLE_MASK;
}

/*================================== SYSTICK_SetTimeMS ==============================*/
/**
  * @brief Set Time in MilliSeconds to SysTick Timer 
  *
  * @param  Time in millisec
  *
  * @return SYSTICK_ErrorStatus_t 
  */
SYSTICK_ErrorStatus_t SYSTICK_SetTimeMS(uint32_t Time)
{
	SYSTICK_ErrorStatus_t RET_ErrorStatus= SYSTICK_Ok;
    uint32_t StkClock = ((SYSTICK_CLK_SOURCE ==SYSTICK_CLK_SOURCE_AHB) ? SYSTICK_AHB_FREQUENCY : (SYSTICK_AHB_FREQUENCY /8));
    /*Cast to u64 to Prevent Overflow*/
    uint32_t Counts=((uint32_t)(((uint64_t)StkClock*(uint64_t)Time)/(uint64_t)1000)-(uint32_t)1);
    if(Counts>SYSTICK_MAX_COUNT_MS)
    {
        RET_ErrorStatus=SYSTICK_Nok;
    }
    else
    {  
        /*Clear Counter Value*/
        SYSTICK->VAL=0;
        /*Load Counter Value*/
        uint32_t STK_LOAD=SYSTICK->LOAD;
        STK_LOAD&=~SYSTICK_LOAD_MASK;
        STK_LOAD|= Counts;
        SYSTICK->LOAD=STK_LOAD;
    }
    return RET_ErrorStatus;

}

/*================================== SYSTICK_SetTimeMS ==============================*/
 /**
  * @brief Set callBack Function 
  *
  * @param  cbf : Function Name that takes void and returns void  
  *
  * @return SYSTICK_ErrorStatus_t 
  */
SYSTICK_ErrorStatus_t  SYSTICK_SetCallBack(systickcbf_t cbf)
{
	SYSTICK_ErrorStatus_t RET_ErrorStatus= SYSTICK_Ok;
    if(cbf)
    {
        APP_cbf=cbf;
    }
    else
    {
        RET_ErrorStatus= SYSTICK_NOk;
    }
    return RET_ErrorStatus;
}

/*================================== SYSTICK_Handler ==============================*/
/**
  * @brief  Systick Handler Function Implementation 
  *
  * @param  cbf : Function Name that takes void and returns void  
  *
  * @return SYSTICK_ErrorStatus_t 
  */
void  SYSTICK_Handler(void)
{
	 if(APP_cbf && (Counter==SYSTICK_ACTIVATE_HANDLER))
    {
        APP_cbf();
    }   
    if(Periodicity==SYSTICK_PERIODICITY_ONE_TIME)
    {
        STK_Stop();
        Counter=SYSTICK_NOT_ACTIVATE_HANDLER;
    } 
}


