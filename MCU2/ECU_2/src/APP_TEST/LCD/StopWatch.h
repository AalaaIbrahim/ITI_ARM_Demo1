#ifndef APP_STOPWATCH_H_
#define APP_STOPWATCH_H_
#include "LIB/STD_TYPES.h"


typedef struct 
{
   uint8_t  hr;
   uint8_t  min;
   uint8_t  sec;
   uint16_t msec;

}SW_Clock_t;

typedef enum
{
    Reset,
    Start,
    Pause,
    Continue,
    Stop
}SW_State_t;


#endif // APP_STOPWATCH_H_
