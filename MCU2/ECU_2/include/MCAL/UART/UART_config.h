#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_


/*
   01-Enter the Required Boad rate :

*/
#define UART_BR 9600

/*
    U Can Select:
    01-SAMPLE_OVER8
    02-SAMPLE_OVER16
*/

#define UART_SAMPLE SAMPLE_OVER16

/*
    Enter The System frequence in  HZ
*/

#define SYS_FRQ   16000000

#endif // MCAL_UART_UART_CONFIG_H_