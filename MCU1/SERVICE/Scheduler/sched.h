/*
 * @file  : sched.h
 * @brief : user interface for scheduler
 * @author: Alaa Hisham
 * @date  : 15-03-2024
 */

#ifndef SCHED_H_
#define SCHED_H_

/*===========================================================================================================*/
/*												    Includes	 										     */
/*===========================================================================================================*/
#include "STD_TYPES.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/
typedef void (*RunnableCBF_t) (void);


typedef struct
{
	u32 periodicity;
	u32 firstDelay;
	RunnableCBF_t cb;	
}Runnable_t;

/*===========================================================================================================*/
/*												     Types		 										     */
/*===========================================================================================================*/

/**
 * @brief Initializes the scheduler
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */

/**
 * @Function: calculateSquare
 * -------------------------
 * Calculates the square of a given number.
 *
 * Parameters:
 *     num: The input number for which the square is to be calculated. Must be an integer.
 *
 * @pre Add 
 */
void sched_init(void);

/**
 * @brief Function to enable the given Interrupt Request
 *
 * @param[in] Copy_enuIRQn   	: the Interrupt Request's index
 *
 * @return STD_enuErrorStatus_t : STD_enuOk 			 : Successful Operation
 * 								  STD_enuInvalidValue	 : Invalid IRQ index
 */
void sched_start(void);

#endif