/**
  ******************************************************************************
  * @file    RCC.c
  * @author  Asmaa Newigy
  * @version V1.0.0
  * @date    12-Feb-2024
  * @brief   RCC module driver.
  *          source file for the RCC module driver.
  ******************************************************************************
**/

/*--------------------------------------- Includes ------------------------------------------*/
#include "RCC.h"

/*--------------------------------------- Defines ------------------------------------------*/
#define RCC_BASE_ADDR   		0x40023800

#define RCC_PLL_M_PRE_MASK		0x0000003F
#define RCC_PLL_N_PRE_MASK		0x00007FC0
#define RCC_PLL_P_PRE_MASK		0x00030000
#define RCC_PLL_Q_PRE_MASK		0x0F000000

#define RCC_SYSCLK_MASK         0x00000003

#define RCC_AHBPRESCAL_MASK     0x000000F0
#define RCC_APB1PRESCAL_MASK  	0x00001C00
#define RCC_APB2PRESCAL_MASK   	0x0000E000

#define RCC_GETSYSCLK_MASK      0x0000000C

#define RCC_PLL_SRC_MASK		0x00400000


/*--------------------------------------- Types ------------------------------------------*/
typedef struct 
{
	uint32_t RCC_CR;
	uint32_t RCC_PLLCFGR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_AHB1RSTR;
	uint32_t RCC_AHB2RSTR;
	uint32_t RCC_Reserved1;
	uint32_t RCC_Reserved2;
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_APB2RSTR;
	uint32_t RCC_Reserved3;
	uint32_t RCC_Reserved4;
	uint32_t RCC_AHB1ENR;
	uint32_t RCC_AHB2ENR;
	uint32_t RCC_Reserved5;
	uint32_t RCC_Reserved6;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_APB2ENR;
	uint32_t RCC_Reserved7;
	uint32_t RCC_Reserved8;
	uint32_t RCC_AHB1LPENR;
	uint32_t RCC_AHB2LPENR;
	uint32_t RCC_Reserved9;
	uint32_t RCC_Reserved10;
	uint32_t RCC_APB1LPENR;
	uint32_t RCC_APB2LPENR;
	uint32_t RCC_Reserved11;
	uint32_t RCC_Reserved12;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
	uint32_t RCC_Reserved13;
	uint32_t RCC_Reserved14;
	uint32_t RCC_SSCGR;
	uint32_t RCC_PLLI2SCFGR;
	uint32_t RCC_Reserved15;
	uint32_t RCC_DCKCFGR;
	
}RCC_Periph_t;

/*--------------------------------------- Variables ------------------------------------------*/
 static volatile RCC_Periph_t* const RCC = (volatile RCC_Periph_t*)(RCC_BASE_ADDR);
 
 
/*--------------------------------- Functions Implementation ------------------------------------*/
/*========================== CONTROL ANY CLOCK IN THE SYSTEM ==============================*/
/*.................................. RCC_EnableClock ....................................*/
/**
  * @brief  Enable any Clock in the System .
  *       
  * @param  RCC_ClOCK: represents one of the clocks in the system
  *         which are(RCC_ClOCK_HSI | RCC_ClOCK_HSE | RCC_ClOCK_PLL).
  *         
  * @note   After Reset the ClOCK_HSI selected as system clock
  *
  * @return RCC_ErrorStatus_t 
  */
RCC_ErrorStatus_t RCC_EnableClock(uint32_t RCC_ClOCK)
{
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
		
	if((RCC_ClOCK!=RCC_ClOCK_HSI)||(RCC_ClOCK!=RCC_ClOCK_HSE)||(RCC_ClOCK!=RCC_ClOCK_PLL))
	{
		Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RCC->RCC_CR |= RCC_ClOCK;
		
	}
	return Ret_ErrorStatus;	
}

/*.................................. RCC_DisableSysClock ....................................*/
/**
  * @brief  Disable any Clock in the System.
  *       
  * @param  RCC_ClOCK: uint32_t that represents one of the system clocks 
  *         which are(RCC_ClOCK_HSI | RCC_ClOCK_HSE | RCC_ClOCK_PLL).
  *         
  * @note  If you want to turn off one of the Clocks, Make sure it`s not selected 
  *         as a system clock.
  *
  * @note  If PLL is selected as system Clock, Don`t turn off its source.
  *
  * @return RCC_ErrorStatus_t 
  */
RCC_ErrorStatus_t RCC_DisableSysClock(uint32_t RCC_ClOCK)
{
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
		
	if((RCC_ClOCK!=RCC_ClOCK_HSI)||(RCC_ClOCK!=RCC_ClOCK_HSE)||(RCC_ClOCK!=RCC_ClOCK_PLL))
	{
		Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RCC->RCC_CR &= ~RCC_ClOCK;
		
	}
	return Ret_ErrorStatus;	
}
 
 /*================================== CONFIGURE PLL  =====================================*/
/*................................. RCC_ConfigurePLL ....................................*/
/**
  * @brief  Configure PLL cLOCK.
  *       
  * @param  RCC_CONFIG_PLLM: Division factor for the main PLL 
  *						 within range ( 2 ≤ PLLM ≤ 63 )- use MACROS -
  *         
  * @param  CONFIG_PLLN: Main PLL (PLL) multiplication factor for VCO
  *						 within range ( 192 ≤ PLLN ≤ 432 )- use MACROS -
  * 
  * @param  CONFIG_PLLP: Main PLL (PLL) division factor for main system clock
  *						 within range ( PLLP = 2, 4, 6, or 8 )- use MACROS - 
  * 
  * @param  CONFIG_PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
  *						 within range ( 2 ≤PLLQ ≤15 )- use MACROS -
  * 
  * @note   You must turn off SYSCLOCK_PLL before configuration
  *
  * @return RCC_ErrorStatus_t 
  */
RCC_ErrorStatus_t RCC_ConfigurePLL(uint32_t RCC_Config_PllM, uint32_t RCC_Config_PllN,uint32_t RCC_Config_PllP,uint32_t RCC_Config_PllQ)
{
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;

	if(RCC_Config_PllM == 0 || RCC_Config_PllM == 1 || RCC_Config_PllM > 63)
	{
		Ret_ErrorStatus = RCC_InvalidPll_M_Config;
	}
	else if(RCC_Config_PllN == 0 || RCC_Config_PllN == 1 || RCC_Config_PllN == 433 || RCC_Config_PllN >= 511)
	{
		Ret_ErrorStatus = RCC_InvalidPll_N_Config;
	}
	else if((RCC_Config_PllP != 2) && (RCC_Config_PllP != 4) && (RCC_Config_PllP != 6) && (RCC_Config_PllP != 8))
	{
		Ret_ErrorStatus = RCC_InvalidPll_P_Config;
	}
	else if(RCC_Config_PllQ == 0 || RCC_Config_PllQ == 1 || RCC_Config_PllQ > 15)
	{
		Ret_ErrorStatus = RCC_InvalidPll_Q_Config;
	}
	else
	{
		uint32_t Temp_PllCFG_Reg = RCC->RCC_PLLCFGR;
		
		Temp_PllCFG_Reg &= ~RCC_PLL_M_PRE_MASK;
        Temp_PllCFG_Reg &= ~RCC_PLL_N_PRE_MASK;
        Temp_PllCFG_Reg &= ~RCC_PLL_P_PRE_MASK;
        Temp_PllCFG_Reg &= ~RCC_PLL_Q_PRESCALE_MASK;
		
        Temp_PllCFG_Reg |= RCC_Config_PllM | RCC_Config_PllN | RCC_Config_PllN |RCC_Config_PllQ);
		
        RCC->RCC_PLLCFGR = Temp_PllCFG_Reg;
	}
	return Ret_ErrorStatus;
}

/*================================ SELECT SYSTEM CLOCK ==================================*/
/*................................ RCC_SelectSysClock ...................................*/
/**
  * @brief  Switch to the desired Clock to be the System clock.
  *       
  * @param  RCC_Sysclock: uint32_t that represents one of the system clocks 
  *         which are(RCC_SYSClOCK_HSI | RCC_SYSClOCK_HSE | RCC_SYSClOCK_PLL).
  *         
  * @note   The selected clock must be on and ready before you  
  *         select it as a system clock.
  *
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_SelectSysClock(uint8_t RCC_Sysclock);
 {
	 RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	 if((RCC_Sysclock!=RCC_SYSClOCK_HSI)||(RCC_Sysclock!=RCC_SYSClOCK_HSE)||(RCC_Sysclock!=RCC_SYSClOCK_PLL))
	 {
		Ret_ErrorStatus=RCC_InvalidParameter;
	 }
	 else
	 {
		 uint32_t Temp_CFGR_Reg = RCC->RCC_CFGR;
		 
		 Temp_CFGR_Reg &=~ RCC_SYSCLK_MASK;
		 Temp_CFGR_Reg |= RCC_Sysclock;
		 
		 RCC->RCC_CFGR=Temp_CFGR_Reg;
		 
	 }
	 return Ret_ErrorStatus;
 }
 
 /*================================ CONTROL PERIPHERAL ==================================*/
/*............................... RCC_EnableAHB1Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to AHB1 Bus.
  *       
  * @param  RCC_AHB1Periph: RCC_AHB1PERIPH_DMA1 |  RCC_AHB1PERIPH_DMA2 | RCC_AHB1PERIPH_CRC | 
  *         RCC_AHB1PERIPH_GPIOH | RCC_AHB1PERIPH_GPIOE | RCC_AHB1PERIPH_GPIOD | RCC_AHB1PERIPH_GPIOC
  *         | RCC_AHB1PERIPH_GPIOB | RCC_AHB1PERIPH_GPIOA
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAHB1Periphs(uint32_t RCC_AHB1Periph)
 {
	 RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	 if((RCC_AHB1Periph!=RCC_AHB1PERIPH_DMA1)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_DMA2)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_CRC)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOH)||
	 (RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOE)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOD)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOC)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOB)||
	 (RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOA))
	 {
		 Ret_ErrorStatus=RCC_InvalidParameter;
	 }
	 else
	 {
			RCC->RCC_AHB1ENR |= RCC_AHB1Periph;
	 }
 	return Ret_ErrorStatus;

 }

/*............................... RCC_EnableAHB2Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to AHB2 Bus.
  *       
  * @param  RCC_AHB2Periph: RCC_AHB2PERIPH_OTGFS
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAHB2Periphs(uint32_t RCC_AHB2Periph)
 {
	 RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	 if(RCC_AHB1Periph!=RCC_AHB2PERIPH_OTGFS)
	 {
		 Ret_ErrorStatus=RCC_InvalidParameter;
	 }
	 else
	 {
			RCC->RCC_AHB2ENR |= RCC_AHB2Periph;
	 }
 	return Ret_ErrorStatus;
 }

/*............................... RCC_EnableAPB1Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to APB1 Bus.
  *       
  * @param  RCC_APB1Periph: RCC_APB1PERIPH_PWR |  RCC_APB1PERIPH_I2C3 | RCC_APB1PERIPH_I2C2 | RCC_APB1PERIPH_I2C1
  *         RCC_APB1PERIPH_USART2 | RCC_APB1PERIPH_SPI3 | RCC_APB1PERIPH_SPI2 | RCC_APB1PERIPH_WWDG
  *			RCC_APB1PERIPH_TIM5 | RCC_APB1PERIPH_TIM4 | RCC_APB1PERIPH_TIM3 | RCC_APB1PERIPH_TIM2
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAPB1Periphs(uint32_t RCC_APB1Periph);
 {
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	if((RCC_APB1Periph!=RCC_APB1PERIPH_PWR)||(RCC_APB1Periph!=RCC_APB1PERIPH_I2C3)||(RCC_APB1Periph!=RCC_APB1PERIPH_I2C2)||(RCC_APB1Periph!=RCC_APB1PERIPH_I2C1)||
	(RCC_APB1Periph!=RCC_APB1PERIPH_USART2)||(RCC_APB1Periph!=RCC_APB1PERIPH_SPI3)||(RCC_APB1Periph!=RCC_APB1PERIPH_SPI2)||(RCC_APB1Periph!=RCC_APB1PERIPH_WWDG)||
	(RCC_APB1Periph!=RCC_APB1PERIPH_TIM5)(RCC_APB1Periph!=RCC_APB1PERIPH_TIM4)||(RCC_APB1Periph!=RCC_APB1PERIPH_TIM3)||(RCC_APB1Periph!=RCC_APB1PERIPH_TIM2))
	{
		 Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RCC->RCC_APB1ENR |= RCC_APB1Periph;
	}
 	return Ret_ErrorStatus;
 }
 
 /*............................... RCC_EnableAPB2Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to APB2 Bus.
  *       
  * @param  RCC_APB2Periph: RCC_APB2PERIPH_TIM11 |  RCC_APB2PERIPH_TIM10 | RCC_APB2PERIPH_TIM9 | RCC_APB2PERIPH_SYSCFG
  *         RCC_APB2PERIPH_SPI4 | RCC_APB2PERIPH_SPI1 | RCC_APB2PERIPH_SDIO |RCC_APB2PERIPH_ADC1
  *			RCC_APB2PERIPH_USART6 | RCC_APB2PERIPH_USART1 |  RCC_APB2PERIPH_TIM1
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAPB2Periphs(uint32_t RCC_APB2Periph)
 {
	 RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	if((RCC_APB2Periph!=RCC_APB2PERIPH_TIM11)||(RCC_APB2Periph!=RCC_APB2PERIPH_TIM10)||(RCC_APB2Periph!=RCC_APB2PERIPH_TIM9)||(RCC_APB2Periph!=RCC_APB2PERIPH_SYSCFG)||
	(RCC_APB2Periph!=RCC_APB2PERIPH_SPI4)||(RCC_APB2Periph!=RCC_APB2PERIPH_SPI1)||(RCC_APB2Periph!=RCC_APB2PERIPH_SDIO)||(RCC_APB2Periph!=RCC_APB2PERIPH_ADC1)||
	(RCC_APB2Periph!=RCC_APB2PERIPH_USART6)||(RCC_APB2Periph!=RCC_APB2PERIPH_USART1)||(RCC_APB2Periph!=RCC_APB2PERIPH_TIM1))
	{
		 Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RCC->RCC_APB2ENR |= RCC_APB2Periph;
	}
 	return Ret_ErrorStatus;
 }
 
/*............................... RCC_DisableAHB1Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to AHB1 Bus as you select.
  *       
  * @param  RCC_AHB1Periph: RCC_AHB1PERIPH_DMA1 |  RCC_AHB1PERIPH_DMA2 | RCC_AHB1PERIPH_CRC | 
  *         RCC_AHB1PERIPH_GPIOH | RCC_AHB1PERIPH_GPIOE | RCC_AHB1PERIPH_GPIOD | RCC_AHB1PERIPH_GPIOC
  *         | RCC_AHB1PERIPH_GPIOB | RCC_AHB1PERIPH_GPIOA
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAHB1Periphs(uint32_t RCC_AHB1Periph)
 {
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	if((RCC_AHB1Periph!=RCC_AHB1PERIPH_DMA1)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_DMA2)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_CRC)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOH)||
	(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOE)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOD)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOC)||(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOB)||
	(RCC_AHB1Periph!=RCC_AHB1PERIPH_GPIOA))
	{
		Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RCC->RCC_AHB1ENR &=~ RCC_AHB1Periph;
	}
 	return Ret_ErrorStatus;
 }

/*............................... RCC_DisableAHB2Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to AHB2 Bus.
  *       
  * @param  RCC_AHB2Periph: RCC_AHB2PERIPH_OTGFS
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAHB2Periphs(uint32_t RCC_AHB2Periph)
 {
	 RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	 if(RCC_AHB1Periph!=RCC_AHB2PERIPH_OTGFS)
	 {
		 Ret_ErrorStatus=RCC_InvalidParameter;
	 }
	 else
	 {
			RCC->RCC_AHB2ENR &=~ RCC_AHB2Periph;
	 }
 	return Ret_ErrorStatus;
 }

/*............................... RCC_DisableAPB1Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to APB1 Bus.
  *       
  * @param  RCC_APB1Periph: RCC_APB1PERIPH_PWR |  RCC_APB1PERIPH_I2C3 | RCC_APB1PERIPH_I2C2 | RCC_APB1PERIPH_I2C1
  *         RCC_APB1PERIPH_USART2 | RCC_APB1PERIPH_SPI3 | RCC_APB1PERIPH_SPI2 | RCC_APB1PERIPH_WWDG
  *			RCC_APB1PERIPH_TIM5 | RCC_APB1PERIPH_TIM4 | RCC_APB1PERIPH_TIM3 | RCC_APB1PERIPH_TIM2
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAPB1Periphs(uint32_t RCC_APB1Periph)
 {
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	if((RCC_APB1Periph!=RCC_APB1PERIPH_PWR)||(RCC_APB1Periph!=RCC_APB1PERIPH_I2C3)||(RCC_APB1Periph!=RCC_APB1PERIPH_I2C2)||(RCC_APB1Periph!=RCC_APB1PERIPH_I2C1)||
	(RCC_APB1Periph!=RCC_APB1PERIPH_USART2)||(RCC_APB1Periph!=RCC_APB1PERIPH_SPI3)||(RCC_APB1Periph!=RCC_APB1PERIPH_SPI2)||(RCC_APB1Periph!=RCC_APB1PERIPH_WWDG)||
	(RCC_APB1Periph!=RCC_APB1PERIPH_TIM5)(RCC_APB1Periph!=RCC_APB1PERIPH_TIM4)||(RCC_APB1Periph!=RCC_APB1PERIPH_TIM3)||(RCC_APB1Periph!=RCC_APB1PERIPH_TIM2))
	{
		 Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RCC->RCC_APB1ENR &=~ RCC_APB1Periph;
	}
 	return Ret_ErrorStatus;
 }
 
 
 /*............................... RCC_DisableAPB2Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to APB2 Bus.
  *       
  * @param  RCC_APB2Periph: RCC_APB2PERIPH_TIM11 | RCC_APB2PERIPH_TIM10 | RCC_APB2PERIPH_TIM9 | RCC_APB2PERIPH_SYSCFG
  *         RCC_APB2PERIPH_SPI4 | RCC_APB2PERIPH_SPI1 | RCC_APB2PERIPH_SDIO | RCC_APB2PERIPH_ADC1
  *			RCC_APB2PERIPH_USART6 | RCC_APB2PERIPH_USART1 | RCC_APB2PERIPH_TIM1
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAPB2Periphs(uint32_t RCC_APB2Periph)
 {
	 RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	 
	if((RCC_APB2Periph!=RCC_APB2PERIPH_TIM11)||(RCC_APB2Periph!=RCC_APB2PERIPH_TIM10)||(RCC_APB2Periph!=RCC_APB2PERIPH_TIM9)||(RCC_APB2Periph!=RCC_APB2PERIPH_SYSCFG)||
	(RCC_APB2Periph!=RCC_APB2PERIPH_SPI4)||(RCC_APB2Periph!=RCC_APB2PERIPH_SPI1)||(RCC_APB2Periph!=RCC_APB2PERIPH_SDIO)||(RCC_APB2Periph!=RCC_APB2PERIPH_ADC1)||
	(RCC_APB2Periph!=RCC_APB2PERIPH_USART6)||(RCC_APB2Periph!=RCC_APB2PERIPH_USART1)||(RCC_APB2Periph!=RCC_APB2PERIPH_TIM1))
	{
		 Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		RCC->RCC_APB2ENR &=~ RCC_APB2Periph;
	}
 	return Ret_ErrorStatus;
 }
 
 /*==================== CONFIGURE PRESCALERS FOR AHB, APB1 AND APB2 ========================*/
/*............................... RCC_CofigureAHBPrescaler .................................*/
 /**
  * @brief  Configure AHB Bus Prescaler.
  *       
  * @param  RCC_AHBPrescal: RCC_AHBPRESCAL_NOPRE |  RCC_AHBPRESCAL_2 | RCC_AHBPRESCAL_4 |RCC_AHBPRESCAL_8
  *         RCC_AHBPRESCAL_16 | RCC_AHBPRESCAL_64 | RCC_AHBPRESCAL_128 | RCC_AHBPRESCAL_256
  *			RCC_AHBPRESCAL_512
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CofigureAHBPrescaler(uint32_t RCC_AHBPrescal)
 {
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;

	if(((RCC_AHBPrescal < RCC_AHBPRESCAL_NOPRE)||(RCC_AHBPrescal > RCC_AHBPRESCAL_512)) &&((RCC_AHBPrescal&(RCC_AHBPrescal-1))==0))
	{
		Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		 uint32_t Temp_CFGR_Reg = RCC->RCC_CFGR;
		 
		 Temp_CFGR_Reg &=~ RCC_AHBPRESCAL_MASK;
		 Temp_CFGR_Reg |= RCC_AHBPrescal;
		 
		 RCC->RCC_CFGR=Temp_CFGR_Reg;
	}
	return Ret_ErrorStatus;
 }

/*............................... RCC_CofigureAPB1Prescaler .................................*/
 /**
  * @brief  Configure  APB Low speed prescaler (APB1).
  *       
  * @param  RCC_APB1Prescal: RCC_APB1PRESCAL_NOPRE |  RCC_APB1PRESCAL_2 | RCC_APB1PRESCAL_4 | RCC_APB1PRESCAL_8
  *         RCC_APB1PRESCAL_16 
  *
  * @note   The software has to set these bits correctly not to exceed 42 MHz on this domain
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CofigureAPB1Prescaler(uint32_t RCC_APB1Prescal);
 {
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;

	if(((RCC_APB1Prescal < RCC_APB1PRESCAL_NOPRE)||(RCC_APB1Prescal > RCC_APB1PRESCAL_16))&&((RCC_APB1Prescal&(RCC_APB1Prescal-1))==0) )
	{
		Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		 uint32_t Temp_CFGR_Reg = RCC->RCC_CFGR;
		 
		 Temp_CFGR_Reg &=~ RCC_APB1PRESCAL_MASK;
		 Temp_CFGR_Reg |= RCC_APB1Prescal;
		 
		 RCC->RCC_CFGR=Temp_CFGR_Reg;
	}
	return Ret_ErrorStatus;
 }
/*............................... RCC_CofigureAPB2Prescaler .................................*/
 /**
  * @brief  Configure : APB high-speed prescaler (APB2).
  *       
  * @param  RCC_APB2Prescal:RCC_APB2PRESCAL_NOPRE |  RCC_APB2PRESCAL_2 | RCC_APB2PRESCAL_4 | RCC_APB2PRESCAL_8
  *         RCC_APB2PRESCAL_16 
  *
  * @note   The software has to set these bits correctly not to exceed 84 MHz on this domain. 
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CofigureAPB2Prescaler(uint32_t RCC_APB2Prescal)
 {
	 RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;

	if(((RCC_APB2Prescal < RCC_APB2PRESCAL_NOPRE)||(RCC_APB2Prescal > RCC_APB2PRESCAL_16))&&((RCC_APB2Prescal&(RCC_APB2Prescal-1))==0) )
	{
		Ret_ErrorStatus=RCC_InvalidParameter;
	}
	else
	{
		 uint32_t Temp_CFGR_Reg = RCC->RCC_CFGR;
		 
		 Temp_CFGR_Reg &=~ RCC_APB2PRESCAL_MASK;
		 Temp_CFGR_Reg |= RCC_APB2Prescal;
		 
		 RCC->RCC_CFGR=Temp_CFGR_Reg;
	}
	return Ret_ErrorStatus;
 }

/*==================================== Get SYSTEM CLOCK ====================================*/
/*.................................... RCC_GetSysClock .....................................*/
/**
  * @brief  Return the runing system clock.
  *       
  * @param  SysClock: stores the runing system clock.
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_GetSysClock(uint32_t* SysClock)
 {
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;

	if(SysClock==NULL)
	{
		Ret_ErrorStatus=RCC_NullPointer;
	}
	else
	{
		SysClock = RCC->RCC_CFGR & RCC_GETSYSCLK_MASK
	}
	return Ret_ErrorStatus;
 }
 
 /*================================= SELECT PLL CLOCK SOURCE ================================*/
 /*.................................. RCC_SetPllSourceHSI ...................................*/
 /**
  * @brief  Select Pll Source with HSI clock.
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_SetPllSourceHSI()
 {
	 RCC->RCC_PLLCFGR &=~ RCC_PLL_SRC_MASK;
 }
 
 /*.................................. RCC_SetPllSourceHSE ...................................*/
 /**
  * @brief  Select Pll Source with HSE clock.
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_SetPllSourceHSE()
 {
	 RCC->RCC_PLLCFGR |= RCC_PLL_SRC_MASK;

 }
 
 /*================================== CHECK READY FLAG STATUS =================================*/
 /*.................................... RCC_CheckRdyStatus ....................................*/
 /**
  * @brief  ChecK ready flag status for each clock
  *       
  * @param  RCC_CLock_RDY_Status: RCC_CLOCK_RDY_STATUS_HSI | RCC_CLOCK_RDY_STATUS_HSE | RCC_CLOCK_RDY_STATUS_PLL
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CheckRdyStatus(uint32_t RCC_CLock_RDY_Status)
 {
	RCC_ErrorStatus_t Ret_ErrorStatus=RCC_OK;
	uint16_t Timeout=1000;

	if(CLockRDYStatus!=)
	{
	}
	else
	{
		while(!(RCC->RCC_CR & RCC_CLock_RDY_Status) && Timeout)
		{
			Timeout--;
		}

		if(Timeout)
		{
			Ret_ErrorStatus=RCC_ClockReady;
		}
		else
		{
			Ret_ErrorStatus=RCC_ClockNotReady;
		}
	}
	return Ret_ErrorStatus;
 }
 


 
