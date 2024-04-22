/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "StopWatch.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define Periodicity_ms 200;

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


/*typedef struct 
{
  u8 type;
}User_Req_t;
*/


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

/*GLobal Shared Variable*/
SW_Clock_t Clock;

uint8_t  StopWatch_Req_Type =1;


/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

 static void Clock_Process(void)
 {
     Clock.msec += Periodicity_ms;
     if(Clock.msec==1000)
     { 
        Clock.msec=0;
        Clock.sec +=1;
      
     }

   if(Clock.sec==60)
     { 
        Clock.sec=0;
        Clock.min +=1;
       
     }

     if(Clock.min==60)
     { 
        Clock.min=0;
        Clock.hr +=1;
      
     }

     if(Clock.hr==24)
     { 
        Clock.hr =0;
     }
 }

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void StopWatch_Process(void)
{
    if(StopWatch_Req_Type==Reset)
    {
        Clock.hr=0;
        Clock.min=0;
        Clock.sec=0;
        Clock.msec=0;
    }

    if( (StopWatch_Req_Type==Start) || (StopWatch_Req_Type==Continue) )
    {
        Clock_Process();
    }

    if ((StopWatch_Req_Type==Pause)||(StopWatch_Req_Type==Stop))
    {

    };


}
