/**
 * @file    :   KPD.h
 * @author  :   Alaa Hisham
 * @brief   :   User interface for Keypad module
 * @version :   0.0
 * @date    :   07-04-2024
 */

#ifndef KPD_H_
#define KPD_H_

/*===========================================================================================================*/
/*						                             Macros						                             */
/*===========================================================================================================*/
#define NO_KEY_PRESSED	0xFF

/*===========================================================================================================*/
/* 				                                  Keypad APIs 				                                 */
/*===========================================================================================================*/
/**
 * @brief Initialization for using the keypad module
 * 
 * Must be called before any other API.
 */
void KPD_init(void);

/**
 * @brief gets the pressed key synchronously
 *  
 * @return the value of the pressed key as defined
 *         in the KPD_u8KeyArr in the KPD_config.c file.
 */
u8 KPD_u8GetPressedSync(void);

/**
 * @brief gets the most recent pressed key value
 *  
 * @return the value of the pressed key as defined
 *         in the KPD_u8KeyArr in the KPD_config.c file.
 */
u8 KPD_u8GetKey(void);


#endif /* KPD_H_ */