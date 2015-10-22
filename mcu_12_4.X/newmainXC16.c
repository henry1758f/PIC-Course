/*
 * File:   newmainXC16.c
 * Author: TEAM 12
 * A/D Converter Homework / MCU-Course HW4 / KUAS 
 * Created on 2015年10月16日, 下午 7:43
 */
#define		CPU_FCY	40 				
#ifndef Fcy
#define Fcy     CPU_FCY*1000000
#endif
#define Delay_200uS_Cnt  (Fcy * 0.02) / 1080


/*Header files to include*/
#include "xc.h"
#include "LCD.h"
#include "config.h"
#include <adc.h>

/*Global Variables*/

unsigned int ADresult[10][4];

/*Definiation*/

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
unsigned int ADconvert()
{
    unsigned int result;
        AD1CON1bits.SAMP = 0;           //Start Conversion
        while (!AD1CON1bits.DONE);      //wait for A/D convrsion complete
        //LATDbits.LATD11 = 0;                        /* turn the LCM back light */
        result = ADC1BUF0;

    return result;
    
}

int main(void) 
{
    unsigned char i=0;
    unsigned int filter[4];
    unsigned char strvalue[24];
    
    RCONbits.SWDTEN = 0;			//disable Watch dog timer
    initPLL();

    while (OSCCONbits.CF == 1);			//check clock failed
    while (OSCCONbits.COSC != 0b011);           // Wait for Clock switch to occur
    while (OSCCONbits.LOCK == 0);		//check PLL locked

    initIO();
    InitializeLCM();
    LCD_clear();
    LCD_start();
    //init_ADC1();
    init_ADC1();
    delay200usX(2*5000);
    LCD_clear();
    
    while(1)
    {
        AD1CON1bits.SAMP = 1;           //Start C
        delay200usX(200);
        AD1CON1bits.SAMP = 0;           //Start Conversion
        for(i=0;i<4;i++)
        {
            
            while (!AD1CON1bits.DONE);
            filter[i] = ADC1BUF0;
            
//            filter[0] = ADconvert();
//            filter[1] = ADconvert();  
//            filter[2] = ADconvert();  LATDbits.LATD11 = 0;                        /* turn the LCM back light */
//            filter[3] = ADconvert();
            
        }
        /*for(i=0;i<4;i++)
        {
            for(j=0;j<10;j++)
            {
                filter[i] += ADresult[i][j];
            }
            filter[i]/=10;
        }*/
        for(i=0;i<4;i++)
        {
            LCD_PrintResult(i,filter[i]);
        }
        
    }
    
    return 0;
}
