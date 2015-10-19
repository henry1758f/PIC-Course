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
#include <adc.h>

/*Global Variables*/

unsigned int ADresult0[10],ADresult1[10],ADresult2[10],ADresult3[10];

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
int ADconvert(unsigned char channel)
{
    AD1CSSL = 0x0000;
    AD1CSSH = 0x0000;
    switch(channel)
    {
        case 0:
            AD1CSSL = 0x0001;
            
            break;
        case 1:
            AD1CSSL = 0x0002;
            break;
        case 2:
            AD1CSSL = 0x0004;
            break;
        case 3:
            AD1CSSL = 0x0008;
            break;
        case 4:
            AD1CSSL = 0x0010;
            break;
        case 5:
            AD1CSSL = 0x0020;
            break;
        case 6:
            AD1CSSL = 0x0040;
            break;
        case 7:
            AD1CSSL = 0x0080;
            break;
        case 8:
            AD1CSSL = 0x0100;
            break;
        default:
            break;
    } 
    AD1CON1bits.SAMP = 1;           //Start Conversion
    
    
    //ATTENTION PLEASE! PROCESS STOP AT HERE
    //THAT MEANS ADConvert MAYBE NOT OPERATING!
    //PLEASE HELP ME CHECKING THE SETTING OF REGISTER
    //PLEASE.....
    
    while (!AD1CON1bits.DONE);      //wait for A/D convrsion complete
    LATDbits.LATD11 = 0;
    return ADC1BUF0;
}

int main(void) 
{
    unsigned char i;
    unsigned int filter[4];
    
    initPLL();
    initIO();
    InitializeLCM();
    LCD_clear();
    LCD_start();
    init_ADC1();
    delay200usX(2*5000);
    LCD_clear();
    
    while(1)
    {
        
        for(i=0;i<10;i++)
        {
            ADresult0[i] = ADconvert(3);
            ADresult1[i] = ADconvert(4);
            ADresult2[i] = ADconvert(5);
            ADresult3[i] = ADconvert(6);
        }
        for(i=0;i<10;i++)
        {
            filter[0]+=ADresult0[i];
        }
        for(i=0;i<10;i++)
        {
            filter[1]+=ADresult1[i];
        }
        for(i=0;i<10;i++)
        {
            filter[2]+=ADresult2[i];
        }
        for(i=0;i<10;i++)
        {
            filter[3]+=ADresult3[i];
        }
        for(i=0;i<4;i++)
        {
            filter[i]/=10;
            LCD_PrintResult(i,filter[i]);
        }
        delay200usX(2500);
        
    }
    return 0;
}
