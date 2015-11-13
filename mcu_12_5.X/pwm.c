#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "lcd.h"

int initPWM(void)
{
    TRISE = 0x00;  // make sure PWM pins are set to be outputs
    PORTE = 0x00; // clear the outputs

    /* Configuration register FPOR */
    /* High and Low switches set to active-high state */
//    _FPOR(RST_PWMPIN & PWMxH_ACT_HI & PWMxL_ACT_HI)
    /* PWM time base operates in a Free Running mode */
    P1TCONbits.PTMOD = 0b00;
    /* PWM time base input clock period is TCY(1:1 prescale) */
    /* PWM time base output post scale is 1:1 */
    P1TCONbits.PTCKPS = 0b11;   //設除頻  t除64
    P1TCONbits.PTOPS = 0b00;
    /* Choose PWM time period based on input clock selected */
    /* Refer to Equation 14-1*/
    /* PWM switching frequency is 40 kHz */
    /* FCYis 40 MHz */
    P1TPER =6249;  //設三角波上限  
    P1TMR = 0;

    /* PWM I/O pairs 1 to 3 are in complementary mode */
    /* PWM pins are enabled for PWM output */
    PWM1CON1bits.PMOD1 = 1;
    //PWM1CON1bits.PMOD2 = 1;
    //PWM1CON1bits.PMOD3 = 1;
    PWM1CON1bits.PEN1H = 1;
    //PWM1CON1bits.PEN2H = 1;
    //PWM1CON1bits.PEN3H = 1;
    PWM1CON1bits.PEN1L = 0;
    //PWM1CON1bits.PEN2L = 0;
    //PWM1CON1bits.PEN3L = 0;

    /* Immediate update of PWM enabled */
    PWM1CON2bits.IUE = 1;
    PWM1CON2bits.UDIS = 1;

    /* Initialize duty cycle values for PWM1, PWM2 and PWM3 signals */
    P1DC1 = 6249;   //decide duty_cycle
    //P1DC2 = 500;
    //P1DC3 = 500;
    P1TCONbits.PTEN = 1;
    return 0;
}

int infoPWM(void)
{
    /*
     * PTCKPS=11   =>除頻64
     *f = 40MH/64 = 0.625MHz => T=1.6us
     *一次1.6us 根據需求為100Hz  所以 1.6us*()=1/100  => () = P1TPER = 6250 => T=10ms為總週期  F=100Hz
     */
    char    pwm_str[20];
    int p1tper = P1TPER & 0x7FFF;   //max for PWM triangle wave
    int prescale = 1 << (P1TCONbits.PTCKPS * 2);    //prescale
    int frequency = (Fcy / prescale)/(p1tper + 1);
    int p1dc1 = P1DC1;
    int duty_cycle = ((p1dc1 + 1)/2) / ((p1tper + 1)/100);

    LCD_Cursor(0, 0);
    sprintf(pwm_str, "f: %dHz", frequency);
    putsLCD((unsigned char*)pwm_str);

    LCD_Cursor(2, 0);
    sprintf(pwm_str, "duty cycle: %d%c", duty_cycle, 0x25);
    putsLCD((unsigned char*)pwm_str);
    
    LCD_Cursor(3, 0);
    sprintf(pwm_str, "prescale: %d", prescale);
    putsLCD((unsigned char*)pwm_str);
    
    

    return 0;
}
