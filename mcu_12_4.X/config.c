/*
 * File:   config.c
 * Author: henry
 *
 * Created on 2015年10月18日, 下午 7:35
 */

// DSPIC33FJ256MC710 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure Segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = PRIPLL           // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
#pragma config IESO = ON                // Two-speed Oscillator Start-Up Enable (Start up with FRC, then switch)

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS128          // Watchdog Timer Postscaler (1:128)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config LPOL = ON                // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD2               // Comm Channel Select (Communicate on PGC2/EMUC2 and PGD2/EMUD2)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)



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
    
    TRISB = 0x0000;
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
    AD1CON1 = 0x0000;
    AD1CON1bits.SAMP = 0;           /* ADC Sample Keep */
    AD1CON1bits.ASAM = 0;           /* ADC Sample Start by program */
    AD1CON1bits.AD12B = 0;          /* 10-Bit 4ch Operation Mode */
    AD1CON1bits.FORM = 0;           /* output format: unsigned int */
    AD1CON1bits.SIMSAM = 1;         /* Simultaneous Sample Select */

    AD1CON2 = 0x0000;
    AD1CON2bits.VCFG = 0x0;         /* Vref+: AVDD,  Vref-:Avss */
    AD1CON2bits.ALTS = 0;           /* Always uses channel input selects for Sample A */

    AD1CON3 = 0x0000;
    AD1CON3bits.ADCS = 0xF;         /* ADC Conversion Clock Select bits, This bit is not used if ADxCON3<15> (ADRC) = 1. */
    AD1CON3bits.ADRC = 0;           /* 1: ADC internal RC clock 0: Clock derived from system clock */
    AD1CON3bits.SAMC = 0x3;         /* Auto-Sample Time bits,This bit is only used if ADxCON1<7:5> (SSRC<2:0>) = 111. */

    AD1CON4 = 0x0000;
    AD1CON4bits.DMABL = 0x0;        /* Allocates 1 word of buffer to each analog input */

    AD1CHS123 = 0x0000;

    AD1CHS0 = 0x0000;               /* analog input 0 */

    AD1PCFGL = 0xFFFE;
    AD1PCFGH = 0xFFFF;

    AD1CON1bits.ADON = 1;           /* turn ADC1 module operating */
}
