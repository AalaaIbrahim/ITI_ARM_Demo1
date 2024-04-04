/**
  ******************************************************************************
  * @file    SYSTICK_Config.h
  * @author  Asmaa Newigy
  * @version V1.0.0
  * @date    12 March 2024
  * @brief   SYSTICK driver.
  *          Header file for the SYSTICK driver Configuration.
  ******************************************************************************
**/

#ifndef SYSTICK_CONFIG_H_
#define SYSTICK_CONFIG_H_

/*Configure AHB Frequency*/
#define STK_AHB_FREQUENCY     16000000

/*
 *Choose SysTick clock source
 * OPTIONS :
 *           SYSTICK_CLK_SOURCE_AHB_DIV_BY_8
 *           SYSTICK_CLK_SOURCE_AHB
 */
#define SYSTICK_CLK_SOURCE  SYSTICK_CLK_SOURCE_AHB


#endif  //SYSTICK_CONFIG_H_