#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "spi.h"
#include "EEPROM.h"

unsigned int SPI2_Int_Data;

void initSPI1(void)
{
    IFS0bits.SPI1IF = 0;  //1 = Interrupt request has occurred
                        //0 = Interrupt request has not occurred
    IPC2bits.SPI1IP = 1;  //111 = Interrupt is priority 7 (highest priority interrupt)
                        //嚙瘟嚙瘟嚙瘟
                        //001 = Interrupt is priority 1
                        //000 = Interrupt source is disabled 
    IEC0bits.SPI1IE = 1;  //1 = Interrupt request enabled, 0 = Interrupt request not enabled
    
    
    SPI1CON1bits.DISSCK = 0;  //1 = Internal SPI clock is disabled; pin functions as I/O
                                //0 = Internal SPI clock is enabled
    SPI1CON1bits.DISSDO = 0;  //1 = SDOx pin is not used by module; pin functions as I/O
                                //0 = SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0;  //1 = Communication is word-wide (16 bits)
                                //0 = Communication is byte-wide (8 bits)
    SPI1CON1bits.SMP = 0;     //1:Sample data at end of time
                                //0:Sample data at middle of time
    SPI1CON1bits.CKE = 1;     //1:Active to Idle
                                //0:Idle to Active  
    SPI1CON1bits.SSEN = 0;        //1 = SSx pin used for Slave mode
                                //0 = SSx pin not used by module. Pin controlled by port function.
    SPI1CON1bits.CKP = 0;     //1:Idle on High Level
                                //0:Idle on Low Level
    SPI1CON1bits.MSTEN = 1;   //1:Master
                                //0:Slave
    SPI1CON1bits.SPRE = 5;    //111 = Secondary prescale 1:1
    //SPI1CON1bits.SPRE = 6;  //111 = Secondary prescale 1:1
                                //110 = Secondary prescale 2:1
                                //101 = Secondary prescale 3:1
                                //100 = Secondary prescale 4:1
                                //011 = Secondary prescale 5:1
                                //010 = Secondary prescale 6:1
                                //001 = Secondary prescale 7:1
                                //000 = Secondary prescale 8:1
    SPI1CON1bits.PPRE = 2;    //11 = Primary prescale 1:1
    //SPI1CON1bits.PPRE = 1;  //11 = Primary prescale 1:1
                                //10 = Primary prescale 4:1
                                //01 = Primary prescale 16:1
                                //00 = Primary prescale 64:1
    SPI1STAT = 0x8000;            //bit15:Enable SPI1 module
    SPI1CON2 = 0x0000;
}

void initSPI2(void)
{
	IFS2bits.SPI2IF = 0;	//1 = Interrupt request has occurred
						//0 = Interrupt request has not occurred
	IPC8bits.SPI2IP = 7;	//111 = Interrupt is priority 7 (highest priority interrupt)
						//嚙瘟嚙瘟嚙瘟
						//001 = Interrupt is priority 1
						//000 = Interrupt source is disabled
	IEC2bits.SPI2IE = 1;	//1 = Interrupt request enabled, 0 = Interrupt request not enabled

	SPI2CON1bits.DISSCK = 0;	//1 = Internal SPI clock is disabled; pin functions as I/O
					//0 = Internal SPI clock is enabled
	SPI2CON1bits.DISSDO = 0;	//1 = SDOx pin is not used by module; pin functions as I/O
					//0 = SDOx pin is controlled by the module
	SPI2CON1bits.MODE16 = 0;	//1 = Communication is word-wide (16 bits)
					//0 = Communication is byte-wide (8 bits)
	SPI2CON1bits.SMP = 0;		//1:Sample data at end of time
					//0:Sample data at middle of time
        /* FIXME! FIXME! fill correct mode */
	SPI2CON1bits.CKE = 1;		//1:Active to Idle
					//0:Idle to Active
        /* FIXME! FIXME! fill correct mode */
	SPI2CON1bits.CKP = 0;		//1:Idle on High Level
					//0:Idle on Low Level
	SPI2CON1bits.SSEN = 0;          //1 = SSx pin used for Slave mode
					//0 = SSx pin not used by module. Pin controlled by port function.
	SPI2CON1bits.MSTEN = 1;         //1:Master
					//0:Slave
        /* FIXME! FIXME! chooce correct clock FIXME! FIXME! */
	SPI2CON1bits.SPRE = 3;
	/* FIXME! FIXME! chooce correct clock FIXME! FIXME! */
    SPI2CON1bits.PPRE = 1;          //11 = Primary prescale 1:1
					//10 = Primary prescale 4:1
					//01 = Primary prescale 16:1
					//00 = Primary prescale 64:1
	SPI2STAT = 0x8000;		//bit15:Enable SPI2 module
	SPI2CON2 = 0x0000;
    SPI2BUF  = 0x00; 
   // TRISCbits.TRISC1 = 0;
}

unsigned char readSPI1Byte(void)
{
    unsigned int SPI_Data;

    SPI_Data = SPI1BUF; // & 0x00ff;
    
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPIRBF = 0;
    
    return (unsigned char)SPI_Data;
}

unsigned char readSPI2Byte(void)
{
    char str2[52];
    unsigned int SPI_Data;
    while(SPI2STATbits.SPIRBF == 0);
    SPI_Data = SPI2BUF; // & 0x00ff;
    /*sprintf(str2,"%d",(unsigned char)SPI_Data);
    LCD_Cursor_New(1, 0);
    putsLCD((unsigned char *)str2);*/
    
    SPI2STATbits.SPIROV = 0;
    SPI2STATbits.SPIRBF = 0;
    return (unsigned char)SPI_Data;
}

void writeSPI1Byte(unsigned int data_out)
{
    while (SPI1STATbits.SPITBF == 1);
    
    if (SPI1CON1bits.MODE16 == 0) {			//8 bits clocks
    	SPI1BUF =(unsigned char)data_out;
    } else {
    	SPI1BUF =(data_out<<8) & 0xff00; 	//16 bits clocks
    }
    
    while (SPI1STATbits.SPITBF == 1);
}

void writeSPI2Byte(unsigned int data_out)
{
    char str2[52];
	while (SPI2STATbits.SPITBF == 1);

	if (SPI2CON1bits.MODE16 == 0) {			//8 bits clocks
		SPI2BUF = data_out & 0xff;
	} else {
		SPI2BUF =(data_out<<8) & 0xff00; 	//16 bits clocks
	}

	while (SPI2STATbits.SPITBF == 1);
    /*sprintf(str2,"%d",data_out & 0xff);
    LCD_Cursor_New(0, 0);
    putsLCD((unsigned char *)str2);*/

}

void __attribute__((interrupt, auto_psv)) _SPI2Interrupt(void)
{
	//unsigned int SPI2_Int_Data;
	SPI2_Int_Data=SPI2BUF; // & 0x00ff;

	SPI2STATbits.SPIROV = 0;
	SPI2STATbits.SPIRBF =0;
	IFS2bits.SPI2IF=0;
}