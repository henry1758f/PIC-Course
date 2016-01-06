#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "keypad.h"
#include "LCD.h"
#define times 10000
/****************** CRITICAL SETUP, MODIFY THEM CAREFULLY *******************/
//F80000 0x00CF
//F80002 0x00CF
//F80004
_FGS(0x0007);
//F80006
_FOSCSEL(0x00A3);
//F80008
_FOSC(0x00E6);
//F8000A
_FWDT(0x77);
//F8000C
_FPOR(0x00E7);
//F8000E
_FICD(0xC2);
unsigned int ser1,ser2,ser3,ser4,ser5,ser6;

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;                  // clear Timer1 interrupt flag

    /* should enter every 10ms */
    timer1.count += 1;
    if (timer1.count == ser1) {LATAbits.LATA0=0;}
    if (timer1.count == ser2) {LATAbits.LATA1=0;}
    if (timer1.count == ser3) {LATAbits.LATA2=0;}
    if (timer1.count == ser4) {LATAbits.LATA3=0;}
    if (timer1.count == ser5) {LATGbits.LATG12=0;}
    if (timer1.count == ser6) {LATGbits.LATG13=0;}
    
    if (timer1.count == 9000) {timer1.count = 0;LATA=0xffff;LATG=0xffff;}

}
void delay(unsigned long delay_count)
{
    unsigned long       temp;
    for (temp=delay_count; temp>0; temp--);

}

void delay200usX(unsigned long delay_count)
{
    unsigned long       temp;

    for (temp=delay_count; temp>0; temp--)
        delay(Delay_200uS_Cnt);
}

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


void PORTS_Test_Initial(void)
{
    PORTA = 0xffff;
    TRISA = 0x0000;
    PORTA = 0xffff;
    LATA=0xffffff;
    
    PORTB = 0xffff;
    TRISB = 0xffff;
    PORTB = 0xffff;

    PORTC = 0xffff;
    TRISC = 0x0000;
    PORTC = 0xffff;

    PORTD = 0xffff;
    TRISD = 0x0000;
    PORTD = 0xffff;

    PORTE = 0xffff;
    TRISE = 0x0000;
    PORTE = 0xffff;

    PORTF = 0xffff;
    TRISF = 0x0000;
    PORTF = 0xffff;

    PORTG = 0xffff;
    TRISG = 0x0000;
    PORTG = 0xffff;
    LATG=0xffffff;
}

int main(void)
{
    char            str[32];
    long int             ad_val_12,ad_val_13,ad_val_14,ad_val_15;
    unsigned int ad[4][10],i;
    RCONbits.SWDTEN = 0;			//disable Watch dog timer
    initPLL();

    while (OSCCONbits.CF == 1);			//check clock failed
    while (OSCCONbits.COSC != 0b011);           // Wait for Clock switch to occur
    while (OSCCONbits.LOCK == 0);		//check PLL locked
    
    T1_Initial();
    PORTS_Test_Initial();
    ADC1_Initial();
    InitializeLCM();
    LATDbits.LATD11 = 1;                        /* turn the LCM back light */
    ser1=100;
    ser2=100;
    ser3=100;
    ser4=100;
    ser5=100;
    ser6=100;
    while (1) 
    {

        LCD_Cursor_New(0, 0);
        sprintf(str, "timer1.count: %d",timer1.count);
        putsLCD((unsigned char*)str);

    }
}


