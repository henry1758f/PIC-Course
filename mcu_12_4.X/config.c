/*
 * File:   config.c
 * Author: henry
 *
 * Created on 2015年10月18日, 下午 7:35
 */

// DSPIC33FJ256MC710 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
//#include "config.h"



void initPLL(void)
{
    int i,j;

    CLKDIVbits.ROI = 0;
    CLKDIVbits.DOZEN = 0;
    CLKDIVbits.DOZE = 0;

    CLKDIVbits.PLLPRE = 18;       // N1 = PLLPRE + 2 = 18+2 =20
    PLLFBD = 158;               // M = 158+2=160
    CLKDIVbits.PLLPOST = 0;       // N2 = 2           sum: Fosc= {OSC*M/(N1*N2)}=20M*160/(20*2)=80MHz
                                    // Tcy=1/80M*4=50nS
    SRbits.IPL = 0 ;

    //wait for Fosc stablize
    for (i=1000; i>0; i--)
        for (j=1000; j>0; j--);

}

void initIO()
{
    TRISA = 0x0000;
    PORTA = 0xFFFF;
    
    TRISB = 0xFFFF;
    PORTB = 0xFFFF;
    
    TRISC = 0x0000;
    PORTC = 0xFFFF;
    
    TRISD = 0x0000;
    PORTD = 0xFFFF;
    
    TRISE = 0x0000;
    PORTE = 0xFFFF;
    
    TRISF = 0x0000;
    PORTF = 0xFFFF;
    
    TRISG = 0x0000;
    PORTG = 0xFFFF;
}

void init_ADC1(void)    //ADC1
{
    AD1PCFGL = 0xFFFE;
    AD1PCFGH = 0xFFFF;
    
    AD1CON1bits.AD12B = 0; // Select 10-bit mode
    AD1CON2bits.CHPS = 3; // Select 4-channel mode
    AD1CON1bits.SIMSAM = 0; // Enable Sequential Sampling
    AD1CON2bits.ALTS = 0; // Enable Alternate Input Selection
    AD1CON2bits.CSCNA = 1; // Enable Channel Scanning
    AD1CON2bits.SMPI = 0; // Select 8 conversion between interrupt
    AD1CON1bits.ASAM = 0; // DISable Automatic Sampling
    // Initialize Channel Scan Selection
    AD1CSSLbits.CSS3 = 1; // Enable AN3 for scan
    AD1CSSLbits.CSS4 = 1; // Enable AN4 for scan
    AD1CSSLbits.CSS5 = 1; // Enable AN5 for scan
    AD1CSSLbits.CSS6 = 1; // Enable AN6 for scan
    // Initialize MUXA Input Selection
    AD1CHS123bits.CH123SA = 1; // CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5
    AD1CHS123bits.CH123NA = 0; // CH1, CH2, CH3 negative input is VREFbit
    // Initialize MUXB Input Selection
    AD1CHS0bits.CH0SB = 6; // Select AN6 for CH0 +ve input
    AD1CHS0bits.CH0NB = 0; // Select VREF- for CH0 -ve inputs
    AD1CHS123bits.CH123SB = 1; // CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5
    AD1CHS123bits.CH123NB = 0; // Select VREF- for CH1 -ve inputs

    AD1CHS0bits.CH0SA= 0x0006;               /* analog input AN6 */



    AD1CON1bits.ADON = 1;           /* turn ADC1 module operating */

}