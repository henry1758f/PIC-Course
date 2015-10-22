#include <xc.h>
#include <p33FJ256MC710.h>

/* auto sample, manual covert */
void ADC1_Initial(void)
{
    AD1PCFGL = 0xFFFE;
    AD1PCFGH = 0xFFFF;
    
    AD1CON1 = 0x0000;
    AD1CON1bits.SAMP = 0;           /* ADC Sample Enable */
    AD1CON1bits.ASAM = 1;           /* ADC Sample Auto-Start */
    AD1CON1bits.AD12B = 1;          /* 12-Bit Operation Mode */
    AD1CON1bits.FORM = 0;           /* output format: unsigned int */
    AD1CON1bits.SIMSAM = 0;         /* Simultaneous Sample Select */

    AD1CON2 = 0x0000;
    AD1CON2bits.VCFG = 0x0;         /* Voltage reference is AVdd and AVss*/
    AD1CON2bits.ALTS = 0;           /* Always uses channel input selects for Sample A */

    AD1CON3 = 0x0000;
    AD1CON3bits.ADCS = 0xF;         /* ADC Conversion Clock Select bits, This bit is not used if ADxCON3<15> (ADRC) = 1. */
    AD1CON3bits.ADRC = 0;           /* 1: ADC internal RC clock 0: Clock derived from system clock */
    AD1CON3bits.SAMC = 0x3;         /* Auto-Sample Time bits,This bit is only used if ADxCON1<7:5> (SSRC<2:0>) = 111. */

    AD1CON4 = 0x0000;
    AD1CON4bits.DMABL = 0x0;        /* Allocates 1 word of buffer to each analog input */

    AD1CHS123 = 0x0000;

    AD1CHS0bits.CH0SA= 0x0000;               /* analog input 0 */



    AD1CON1bits.ADON = 1;           /* turn ADC1 module operating */

}


