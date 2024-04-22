
#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/* The number of rows in the keypad */
#define	KPD_ROWS                2

/* The number of columns in the keypad */
#define KPD_COLUMNS             4

/*
 * Which keypad pins are used as input pins
 * Options:
 *      KPD_ROW_PINS
 *	    KPD_COL_PINS	
 */
#define KPD_INPUT_PINS          KPD_COL_PINS

/*
 * Options:
 *      EXTERNAL_PULLUP
 *	    INTERNAL_PULLUP	  (if it is supported by the target)
 *	    EXTERNAL_PULLDOWN
 *      INTERNAL_PULLDOWN (if it is supported by the target)
 */
#define KPD_INPUT_PULL_TYPE     INTERNAL_PULLUP


typedef struct
{
    void* port ;
    GPIO_enuPin_t pin;
}KPD_stPin_t;


#endif /* KPD_CONFIG_H_ */