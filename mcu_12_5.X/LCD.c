/*
 * File:   LCD.c
 * Author: henry
 *
 * Created on 2015年10月19日, 下午 9:44
 */
#include <xc.h>
#include  "LCD.h"
#include <stdio.h>
 unsigned char* clear_str = "                    ";

union{
	struct{
		unsigned bit0:1;
		unsigned bit1:1;
		unsigned bit2:1;
		unsigned bit3:1;
		unsigned bit4:1;
		unsigned bit5:1;
		unsigned bit6:1;
		unsigned bit7:1;
	};
	struct{
		unsigned char byte;
	};
}LCD_DATA;

unsigned char	LCD_StatusByte ;
int	Return_Data ;

int	LCDIsBusy(void)
{
	int	BusyLoop ;
	for (BusyLoop = 0 ; BusyLoop < 30 ; BusyLoop++) ;
	LCD_StatusByte = cmdreadLCD() ;
	for (BusyLoop = 0 ; BusyLoop < 30 ; BusyLoop++) ;
	return ((LCD_StatusByte >> 7) & 0x0001) ;
}

void InitializeLCM(void)
{
	LCD_Delay200usX(300) ;		// >= 40ms,Wait for LCD power on delay
	LCD_E = 0 ;
	LCD_E_Delay() ;
  
        LCD_Command_4b(0x20);
        LCD_Delay200usX(10);

	LCD_Command(LCD_SET) ;	//must >=72uS
	LCD_Delay200usX(1);

	LCD_Command(LCD_OFF) ;	//must >= 72uS
	LCD_Delay200usX(10) ;

	LCD_Command(LCD_CLR) ;	//must >=4.6ms
	LCD_Delay200usX(60) ;

	LCD_Command(LCD_ON) ;		//must >=72uS
	LCD_Delay200usX(10) ;

	LCD_Command(LCD_ENTRY) ;	//must >=72uS
	LCD_Delay200usX(10) ;

	LCD_Command(LCD_CUR_HOME) ;		//must >=72uS
	LCD_Delay200usX(10) ;

	//============

	LCD_Delay200usX(250) ;		// >= 40ms,Wait for LCD power on delay

}

void LCD_Cursor_Classic( char Cur_X , char Cur_Y )
{
 		unsigned char	BaseAddr ;
		switch ( Cur_X )               // Cur_X �۷��Y�b�ACur_Y�۷��X
		{
			case	0 :
					BaseAddr = 0x80 ;   //0b10000000
					break ;
			case	1 :
					BaseAddr = 0xc0 ;   //0b10110000
					break ;
			case	2 :
					BaseAddr = 0x94 ;   //0b10011000
					break ;
			case	3 :
					BaseAddr = 0xd4 ;   //0b11010100
					break ;
			default :
					BaseAddr = 0x80 ;
					break ;
		}
			BaseAddr += Cur_Y ;
			//while ( LCDIsBusy()) ;
			LCD_Command(BaseAddr) ;
			//LCD_Delay200usX(10) ;

}

void LCD_Cursor_New( char Cur_X , char Cur_Y )
{
 		unsigned char	BaseAddr ;
		switch ( Cur_X )               // Cur_X �۷��Y�b�ACur_Y�۷��X
		{
			case	0 :
					BaseAddr = 0xC0 ;   //0b10000000
					break ;
			case	1 :
					BaseAddr = 0x80 ;   //0b10110000
					break ;
			case	2 :
					BaseAddr = 0x94 ;   //0b10011000
					break ;
			case	3 :
					BaseAddr = 0xD4 ;   //0b11010100
					break ;
			default :
					BaseAddr = 0x00 ;
					break ;
		}
			BaseAddr += Cur_Y ;
			//while ( LCDIsBusy()) ;
			LCD_Command(BaseAddr) ;
			//LCD_Delay200usX(10) ;

}

void putcLCD( unsigned char DataChar)
{
		LCD_WriteData(DataChar);
}

void putsLCD( unsigned char *DataString )
{
		while ( *DataString != 0x00 )		//not end of line
		{
 			//while ( LCDIsBusy() );
			LCD_WriteData( *DataString++ ) ;
		}
}

void	putrsLCD( const unsigned char *OutString )
{
		while ( *OutString != 0x00 )
		{
 			while ( LCDIsBusy() );
			putcLCD( *OutString++ ) ;
		}
}

void LCD_Delay200usX(int UnitOf200us)
{
		int Loop_200usX ;

		for ( Loop_200usX = 0 ; Loop_200usX < UnitOf200us ; Loop_200usX ++ )
		LCD_Delay200us( ) ;
}


void 	LCD_Delay200us(void)
{
	int		Loop_200us ;

	for ( Loop_200us = 0 ; Loop_200us < CPU_FCY * 40  ; Loop_200us++)	;

}

//		LCD Data @ RD0 .. RD6 and RD10
unsigned char	datareadLCD(void)				//	Read data from LCD
{
		int	Temp_PORTD ;
		
		TRISD |= 0b0000100001111111 ;			// Make all LCD data pins as INPUT 
		LCD_RS = 1 ;
		LCD_RW = 1 ;
		LCD_E_Delay() ;
		LCD_E = 1 ;
		LCD_E_Delay() ;
		Temp_PORTD = PORTD ;
		LCD_E = 0 ;
		TRISD &= 0b1111011110000000 ;
		Return_Data = Temp_PORTD ;
		if ( Temp_PORTD & 0b0000100000000000 ) 
                  {
                   	Return_Data |= 0b10000000 ;
		}
                   else
                   {
                           Return_Data &= 0b01111111 ;
                   }

		return 	(unsigned char)Return_Data ;
}

unsigned char cmdreadLCD(void)				//	Read data from LCD
{
		unsigned int	Temp_PORTD ;
		unsigned char Return_Data ;

		TRISD |= 0xf000 ;			// Make all LCD data pins b15:b12  as INPUT 
		//read the high nibble 4 bits
		LCD_RS = 0 ;
		LCD_RW = 1 ;
		LCD_E_Delay() ;
		LCD_E = 1 ;
		LCD_E_Delay() ;
		Temp_PORTD = PORTD ;
		LCD_E = 0 ;

		//read the low nibble 4 bits
		LCD_RS = 0 ;
		LCD_RW = 1 ;
		LCD_E_Delay() ;
		LCD_E = 1 ;
		LCD_E_Delay() ;
		//Temp_PORTD = PORTD ;
		LCD_E = 0 ;

		TRISD &= 0x0fff ;			//set the LCD data pins b15-b12 as output

		Return_Data =(Temp_PORTD >>8) & 0x80;

		//if (Temp_PORTD & 0x8000) 
		//Return_Data |= 0b10000000 ;
		//else
		//Return_Data &= 0b01111111 ;

		return	Return_Data ;
}

void LCD_WriteData(unsigned char Data)		// Write data to LCD
{
	unsigned char SendData,SendDataTmp;
		/*
		LATD &= 0b1111011110000000 ;
		if ( wdata & 0b0000000010000000 )
			LATD |=  0b0000100000000000 ;
			wdata &= 0b01111111 ;
		LATD |= wdata ;
		*/
	//high nibble 4 bits
	SendDataTmp=Data;
	SendData=SendDataTmp & 0xf0;
	LCD_DATA.byte=SendData;
	LCD_DATA_BIT4=LCD_DATA.bit4;       //RD12
	LCD_DATA_BIT5=LCD_DATA.bit5;       //RD13
	LCD_DATA_BIT6=LCD_DATA.bit6;       //RD14
	LCD_DATA_BIT7=LCD_DATA.bit7;       //RD15
		
	LCD_RS = 1 ;                                            //RS=1 & RW=0 => write    RS=1 %RW=2 => read
	LCD_RW = 0 ;
	LCD_E_Delay() ;
	LCD_E = 1 ;
	LCD_E_Delay() ;
	LCD_E = 0 ;
	LCD_E_Delay() ;

	//low nibble 4 bits
	SendData=(SendDataTmp << 4) & 0xf0;
	LCD_DATA.byte=SendData;
	LCD_DATA_BIT4=LCD_DATA.bit4;
	LCD_DATA_BIT5=LCD_DATA.bit5;
	LCD_DATA_BIT6=LCD_DATA.bit6;
	LCD_DATA_BIT7=LCD_DATA.bit7;

	LCD_RS = 1 ;
	LCD_RW = 0 ;
	LCD_E_Delay() ;
	LCD_E = 1 ;
	LCD_E_Delay() ;
	LCD_E = 0 ;
	LCD_E_Delay() ;
}

void LCD_Command_4b(unsigned char Command)		// Write Command to LCD
{
	unsigned char SendCommand,SendCommandTmp;
	//high nibble 4 bits
	SendCommandTmp=Command;
	SendCommand=SendCommandTmp & 0xf0;   // �]���@���u�� 4 bits �ҥH��&�ӳB�z
	LCD_DATA.byte=SendCommand;
	LCD_DATA_BIT4=LCD_DATA.bit4;
	LCD_DATA_BIT5=LCD_DATA.bit5;
	LCD_DATA_BIT6=LCD_DATA.bit6;
	LCD_DATA_BIT7=LCD_DATA.bit7;

	LCD_RS = 0 ;
	LCD_RW = 0 ;
	LCD_E_Delay() ;
	LCD_E = 1 ;
	LCD_E_Delay() ;
	LCD_E = 0 ;
	LCD_E_Delay() ;

}

void LCD_Command(unsigned char Command)		// Write Command to LCD 
{
	unsigned char SendCommand,SendCommandTmp;
	//high nibble 4 bits
	SendCommandTmp=Command;
	SendCommand=SendCommandTmp & 0xf0;   // �]���@���u�� 4 bits �ҥH��&�ӳB�z 
	LCD_DATA.byte=SendCommand;
	LCD_DATA_BIT4=LCD_DATA.bit4;
	LCD_DATA_BIT5=LCD_DATA.bit5;
	LCD_DATA_BIT6=LCD_DATA.bit6;
	LCD_DATA_BIT7=LCD_DATA.bit7;

	LCD_RS = 0 ;
	LCD_RW = 0 ;
	LCD_E_Delay() ;
	LCD_E = 1 ;
	LCD_E_Delay() ;
	LCD_E = 0 ;
	LCD_E_Delay() ;

			
	//low nibble 4 bits
	SendCommand=(SendCommandTmp << 4) & 0xf0;
	LCD_DATA.byte=SendCommand;
	LCD_DATA_BIT4=LCD_DATA.bit4;
	LCD_DATA_BIT5=LCD_DATA.bit5;
	LCD_DATA_BIT6=LCD_DATA.bit6;
	LCD_DATA_BIT7=LCD_DATA.bit7;

	LCD_RS = 0 ;
	LCD_RW = 0 ;
	LCD_E_Delay() ;
	LCD_E = 1 ;
	LCD_E_Delay() ;
	LCD_E = 0 ;
	LCD_E_Delay() ;

	//LCD_Delay200usX(10) ;
}

void	LCD_E_Delay(void)
{
		int	E_Loop ;
		for ( E_Loop = 0 ; E_Loop < CPU_FCY * 5 ; E_Loop ++ ) ;
}

unsigned char num2char(unsigned char value)
{
    switch(value)
    {
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 3:
            return '3';
            break;
        case 4:
            return '4';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '6';
            break;
        case 7:
            return '7';
            break;
        case 8:
            return '8';
            break;
        case 9:
            return '9';
            break;
        case 10:
            return 'A';
            break;
        case 11:
            return 'B';
            break;
        case 12:
            return 'C';
            break;
        case 13:
            return 'D';
            break;
        case 14:
            return 'E';
            break;
        case 15:
            return 'F';
            break;
        default:
            return 'X';
            break;
    }
    return 'X';
}

void LCD_start()
{
    unsigned char str1[21]="   = MCU Course =   ",
                  str2[21]="       TEAM 12      ",
                  str3[21]="     2015/11/06     ";
    LCD_Cursor_New(0, 0);
    putsLCD((unsigned char*)str1);
    LCD_Cursor_New(1, 0);
    putsLCD((unsigned char*)str2);
    LCD_Cursor_New(2, 0);
    putsLCD((unsigned char*)clear_str);
    LCD_Cursor_New(3, 0);
    putsLCD((unsigned char*)str3);
    
}

void LCD_clear()
{
    LCD_Cursor_New(0, 0);
    putsLCD((unsigned char*)clear_str);
    LCD_Cursor_New(1, 0);
    putsLCD((unsigned char*)clear_str);
    LCD_Cursor_New(2, 0);
    putsLCD((unsigned char*)clear_str);
    LCD_Cursor_New(3, 0);
    putsLCD((unsigned char*)clear_str);
}

void LCD_clearAline(unsigned char posY)
{
    switch (posY)
    {
        case 0:
            LCD_Cursor_New(0, 0);
            putsLCD((unsigned char*)clear_str);
            break;
        case 1:
            LCD_Cursor_New(1, 0);
            putsLCD((unsigned char*)clear_str);
            break;
        case 2:
            LCD_Cursor_New(2, 0);
            putsLCD((unsigned char*)clear_str);
            break;
        case 3:
            LCD_Cursor_New(3, 0);
            putsLCD((unsigned char*)clear_str);
            break;
        default:
            break;
    }
}

void LCD_PrintResult(unsigned char posY,unsigned int value)
{
    //unsigned char* str1 = "AN",str2 = " value: ",
    unsigned char strvalue[32];
    switch(posY)
    {
        case 0:
            LCD_Cursor_New(0, 0);
            LCD_clearAline(posY);
            LCD_Cursor_New(0, 0);
            break;
        case 1:
            LCD_Cursor_New(1, 0);
            LCD_clearAline(posY);
            LCD_Cursor_New(1, 0);
            break;
        case 2:
            LCD_Cursor_New(2, 0);
            LCD_clearAline(posY);
            LCD_Cursor_New(2, 0);
            break;
        case 3:
            LCD_Cursor_New(3, 0);
            LCD_clearAline(posY);
            LCD_Cursor_New(3, 0);
            break;
        default:
            LCD_Cursor_New(0, 0);
            LCD_clearAline(posY);
            LCD_Cursor_New(0, 0);
            break;
    }
    //putsLCD(*str1);
    //putcLCD(num2char(posY));
    //putsLCD(*str2);
    sprintf(strvalue, "AD%d: %04d", posY,value);
    
    putsLCD(strvalue);
    
}