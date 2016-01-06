/*
 * File:   newmainXC16.c
 * Author: henry
 *
 * Created on 2015年12月18日, 下午 1:39
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

void PORTS_Test_Initial(void) {
    PORTA = 0xffff;
    TRISA = 0x0000;
    PORTA = 0xffff;

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
    TRISF = 0x0010;
    PORTF = 0xffff;

    PORTG = 0xffff;
    TRISG = 0x0000;
    PORTG = 0xffff;
}
int main(void) 
{
    PORTS_Test_Initial();
    InitializeLCM();
    EEPROM_init();
    initSPI2();
    LCD_clear();
    LCD_start();
    LCD_Delay200usX(5000);
    LCD_clear();
    
    
    while(1);
    
    return 0;
}
