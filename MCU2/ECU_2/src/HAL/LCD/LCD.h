/*
 * LCD.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Shirehan
 */

#ifndef LCD_H_
#define LCD_H_

#include "LIB/STD_TYPES.h"

/**
 * @brief Structure representing the configuration of pins for LCDs.
 *
 * This structure defines the layout of the pin configuration for LCDs.
 */
typedef struct {
    uint32_t *Port; /**< Pointer to the port. */
    uint32_t Pin; /**< Pin number. */
    uint32_t Mode; /**< Pin mode. */
    uint8_t InitState; /**< Initial state of the pin. */
} LCD_PinConig_t;

/**
 * @brief Enumeration representing the number of LCDs.
 *
 * This enumeration represents the number of LCDs in the system.
 */
typedef enum {
    LCD_0,
    _NUM_OF_LCDs
} LCD_NumOfLCDs_t;

/**
 * @brief Enumeration representing the pins of an LCD.
 *
 * This enumeration lists the pins of an LCD.
 */
typedef enum {
    LCD_D0,
    LCD_D1,
    LCD_D2,
    LCD_D3,
    LCD_D4,
    LCD_D5,
    LCD_D6,
    LCD_D7,
    LCD_RS,
    LCD_RW,
    LCD_ENABLE,
    NUM_OF_PINs_PER_LCD
} LCD_PINS;

/**
 * @brief Enumeration representing the error states of the LCD module.
 *
 * This enumeration represents the possible error states of the LCD module.
 */
typedef enum {
    LCD_NOK, /**< Error state: Not OK. */
    LCD_OK /**< Error state: OK. */
} LCD_ErrorState_t;

/**
 * @brief Initializes the LCD module.
 */
void LCD_Init(void);

/**
 * @brief Clears the screen of the LCD.
 *
 * @return Error state.
 */
LCD_ErrorState_t LCD_ClearScreen(void);

/**
 * @brief Sets the position of the cursor on the LCD.
 *
 * @param X X-coordinate of the cursor.
 * @param Y Y-coordinate of the cursor.
 * @return Error state.
 */
LCD_ErrorState_t LCD_SetPosition(uint8_t X, uint8_t Y);

/**
 * @brief Writes a number to the LCD.
 *
 * @param Number The number to be written.
 * @return Error state.
 */
LCD_ErrorState_t LCD_WriteNumber(uint16_t Number);

/**
 * @brief Task function for the LCD module.
 *
 * This function is responsible for executing tasks related to the LCD module.
 */
void LCD_TASK(void);

#endif /* LCD_H_ */
