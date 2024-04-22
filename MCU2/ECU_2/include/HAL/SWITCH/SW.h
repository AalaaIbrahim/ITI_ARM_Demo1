#ifndef HAL_SW_SW_H_
#define HAL_SW_SW_H_

#include "LIB/STD_TYPES.h"
#include "SW_config.h"

#define SW_STATE_PRESSED      1
#define SW_STATE_NOT_PRESSED  0
   

typedef struct
{
    void* Port;
    uint32_t    Pin;
    uint32_t    Connect;

}SW_SwitchConfig_t;


void SW_Init(void);
void SW_GetSwitchState(uint8_t SwitchName ,uint8_t* state);

#endif // HAL_SW_SW_H_
