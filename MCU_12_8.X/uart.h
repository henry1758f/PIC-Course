#ifndef _UART_H
#define _UART_H

#include <xc.h>

#define UART_RX_BUFFER_SIZE             512
#define UART_TX_BUFFER_SIZE             512

#ifndef FCY
#define FCY 40000000
#endif

#define UART_LOW_SPEED_MODE         0
#if (UART_LOW_SPEED_MODE==1)
#define BAUDRATE_DIV            4
#else
#define BAUDRATE_DIV            16
#endif

#define BRGVAL_9600             ((FCY/9600)/BAUDRATE_DIV)-1         /* 259 */
#define BRGVAL_19200            ((FCY/19200)/BAUDRATE_DIV)-1
#define BRGVAL_38400            ((FCY/38400)/BAUDRATE_DIV)-1
#define BRGVAL_57600            ((FCY/57600)/BAUDRATE_DIV)-1
#define BRGVAL_115200           ((FCY/115200)/BAUDRATE_DIV)-1
#define SPECIAL_BAUDRATE        14400               /* if not on the list */
#define BRGVAL_SPECIAL          ((FCY/SPECIAL_BAUDRATE)/BAUDRATE_DIV)-1

/* UxMode PDSEL */
enum {
    NONE_PARITY_8BITS = 0,
    EVEN_PARITY_8BITS,
    ODD_PARITY_8BITS,
    NONE_PARITY_9BITS
};


/* function prototype */
void initUART1(unsigned int baudrate);
void initUART2(unsigned int baudrate);
void writeUART1Byte(unsigned char data);
void writeUART1String(unsigned char *data, unsigned char length) __attribute__ ((section (".libperi")));
void writeUART2Byte(unsigned char data);
void writeUART2String(unsigned char *data, unsigned char length) __attribute__ ((section (".libperi")));

#endif /*_UART_H */
