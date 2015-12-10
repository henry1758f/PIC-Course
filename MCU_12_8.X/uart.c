
#include <xc.h>
#include <stdlib.h>
//#include "main.h"
//#include "time.h"
#include "uart.h"
#define USER_STRING "You said: "

void initUART2(unsigned int baudrate)
{
    /* FIXME: check baudrate range */

    U2MODE = 0x0000;                    /* clear all setting */
    U2MODEbits.RTSMD = 1;               //1 = UxRTS pin in Simplex mode; 0 = UxRTS pin in Flow Control mode
    U2MODEbits.PDSEL = ODD_PARITY_8BITS;   //8-bit data,no parity
    U2MODEbits.STSEL = 0;                //1 = Two Stop bits; 0 = One Stop bit
    //U2MODE = 0x8800 ;			//bit 15 UARTEN: UARTx Enable bit
    //U2MODE = 0x8200 ;                     //1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>
                                            //0 = UARTx is disabled; all UARTx pins are controlled by port latches; UARTx power consumption is minima
					//bit 13 USIDL: Stop in Idle Mode bit
                                            //1 = Discontinue module operation when device enters Idle mode.
                                            //0 = Continue module operation in Idle mode
					//bit 12 IREN: IrDAR Encoder and Decoder Enable bit(2)
                                            //1 = IrDA encoder and decoder enabled
                                            //0 = IrDA encoder and decoder disabled

					//bit 9-8 UEN<1:0>: UARTx Enable bits
                                            //11 = UxTX, UxRX and BCLK pins are enabled and used; UxCTS pin controlled by port latches
                                            //10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
                                            //01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin controlled by port latches
                                            //00 = UxTX and UxRX pins are enabled and used and UxRTS/BCLK pins controlled by port latches
					//bit 7 WAKE: Wake-up on Start bit Detect During Sleep Mode Enable bit
                                            //1 = UARTx will continue to sample the UxRX pin. Interrupt generated on the falling edge; bit cleared
                                            //in hardware on the following rising edge.
					//bit 6 LPBACK: UARTx Loopback Mode Select bit
                                            //1 = Enable Loopback mode
                                            //0 = Loopback mode is disabled
                                            //0 = No wake-up enabled
					//bit 5 ABAUD: Auto-Baud Enable bit
                                            //1 = Enable baud rate measurement on the next character – requires reception of a Sync field (0x55)
                                            //before other data; cleared in hardware upon completion
                                            //0 = Baud rate measurement disabled or completed
					//bit 4 URXINV: Receive Polarity Inversion bit
                                            //1 = UxRX Idle state is ‘0’
                                            //0 = UxRX Idle state is ‘1’
                                        //bit 3 BRGH: High Baud Rate Enable bit
                                            //1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
                                            //0 = BRG generates 16 clocks per bit period (16x baud clock, Standard mode)
					//bit 0 STSEL: Stop Bit Selection bit



    U2STAbits.UTXISEL0 = 0;         // Interrupt generated when any character is transferred to the Transmit Shift register
    U2STAbits.UTXISEL1 = 0;
    U2STAbits.URXISEL = 0;          // Interrupt is set when any character is received and transferred from the UxRSR to the receive
    //U2STA = 0x2400 ;
    //U2STA = 0x6400 ;

    U2BRG = baudrate;

    //Ctrl_U1RX = INPUT ;
    //Ctrl_U1TX = OUTPUT ;
    TRISFbits.TRISF4 = 1;			//U2 RX
    TRISFbits.TRISF5 = 0;			//U2 TX

    IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
    IEC1bits.U2TXIE = 0;	// Disable Transmit Interrupts
    IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
    IEC1bits.U2RXIE = 1;	// enable U2RX interrupt

    U2MODEbits.UARTEN = 1;		// Enable UART
    U2STAbits.UTXEN = 1;		// Enable UART Tx
}

void writeUART2Byte(unsigned char data)
{
    while (U2STAbits.UTXBF); /* wait if the buffer is full */
    U2TXREG = data;
}

void writeUART2String(unsigned char *data, unsigned char length)
{
    int i;
    for (i=0; i<length; i++) {
        writeUART2Byte(data[i]);
    }
}

void  __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void)
{
    IFS1bits.U2TXIF = 0;
}

void  __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void)
{
    //writeUART2String(USER_STRING + U2RXREG,sizeof(USER_STRING + U2RXREG));
    writeUART2Byte(U2RXREG);
    /* clear interrupt flag */
    IFS1bits.U2RXIF = 0;

}


