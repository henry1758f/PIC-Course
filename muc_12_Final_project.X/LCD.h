#define		CPU_FCY	40 				// for LCD elay referewnce

#define		LCD_RS		LATGbits.LATG1		// RS = 1 >> Data , =0 >> Command
#define		LCD_RW		LATGbits.LATG0		//  RW = 0 >> Write , = 1 >> Read
#define		LCD_E		LATDbits.LATD10
#define   	LCD_BACKLIGHT 	LATDbits.LATD11

#define		LCD_DATA_BIT4	LATDbits.LATD12
#define		LCD_DATA_BIT5	LATDbits.LATD13
#define		LCD_DATA_BIT6	LATDbits.LATD14
#define		LCD_DATA_BIT7	LATDbits.LATD15

#define LCD_OFF 	0x08  		//turn off lcd
//#define LCD_SET 	0x38	//bit5 always 1, bit4 8/4 bits data length
							//bit3 x, bit2 normal/extend instruction
							//bit1 x, bit0 x, 8 bits 2 lines 5*7 
#define LCD_SET 	0x28		// 4 bits 2 lines 5*7 
#define LCD_CLR 	0x01		//clear LCD
//#define LCD_ON  	0x0f
#define LCD_ON  	0x0C			//bit3 always 1,bit2:on/off, bit1:cursor on/off, bit0:cursor blink on/off
#define LCD_ENTRY 	0x06	//set entry
#define LCD_CUR_HOME    0x80 	//cursor home position

#define LCD_Cursor              LCD_Cursor_Classic
void	LCD_Delay200us(void) ;
void	LCD_Delay200usX(int) ;
void    OpenLCD(void);
void	InitializeLCM(void) ;
void	LCD_PutChar(unsigned char) ;
void	LCD_Cursor_Classic(char,char);
void	LCD_Cursor_New(char,char);
void	putcLCD(unsigned char) ;
void	putsLCD( unsigned char * ) ;
void	putrsLCD( const unsigned char * ) ;
void	LCD_E_Delay(void) ;
void	LCD_WriteData(unsigned char) ;
void    LCD_Command_4b(unsigned char Command);
void	LCD_Command(unsigned char) ;
unsigned char 	datareadLCD(void) ;
unsigned char	cmdreadLCD(void) ;



/*
#pragma .userconstants
const  unsigned char DEMAND_TITLE1[6]={"Solar"};
const  unsigned char DEMAND_TITLE2[8]={"Control"};
const  unsigned char DEMAND_TITLE3[7]={"System"};
const  unsigned char DEMAND_TITLE4[10]={"Ver. 2.06"};
#pragma 
*/
