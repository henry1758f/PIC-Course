#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "keypad.h"
#include "LCD.h"

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

    PORTB = 0xffff;
    TRISB = 0x0000;
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
}

int main(void)
{
    char            str[32];
    int             temp_ms, temp_sec;
    RCONbits.SWDTEN = 0;			//disable Watch dog timer
    initPLL();

    while (OSCCONbits.CF == 1);			//check clock failed
    while (OSCCONbits.COSC != 0b011);           // Wait for Clock switch to occur
    while (OSCCONbits.LOCK == 0);		//check PLL locked
    T1_Initial();
    PORTS_Test_Initial();
    keypad_init();
    ADC1_Initial();
    initPWM();
    InitializeLCM();
    LATDbits.LATD11 = 1;                        /* turn the LCM back light */
    
    int a;
    LCD_clear();
    LCD_start();
    delay200usX(2*5000);
    LCD_clear();
    while (1) {
        
        /* PWM */
        infoPWM();
        a = keypad_task();
        /*
        LCD_Cursor_New(0, 12);
        sprintf(str, "%d",a);
        putsLCD((unsigned char*)str); 
        *//*
        if(a==1){P1DC1 = 749; }
        if(a==2){P1DC1 = 3124; }
        if(a==3){P1DC1 = 4999; }
        if(a==4){P1DC1 = 6249; }
        */
        if(a==1){P1DC1 = 1499; }
        if(a==2){P1DC1 = 6249; }
        if(a==3){P1DC1 = 9999; }
        if(a==4){P1DC1 = 12499; }
        
    }
}


