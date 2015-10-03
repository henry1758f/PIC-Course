
#include <xc.h>
#include "main.h"

unsigned int    t1_counter = 0 ;
unsigned int    time_sec = 0;
mytime_t        timer1;

void T1_Initial(void)
{
    /* this timer 1 setup for interrupt every 10ms, used for system tick */
    PR1 = 50000;
    T1CON = 0x00;
    T1CONbits.TCKPS = 1;    /* prescale = 1:8 */
    T1CONbits.TON = 1;      /* enable timer */
    IEC0bits.T1IE = 1;
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;                  // clear Timer1 interrupt flag

    /* should enter every 10ms */
    timer1.ms += 10;

   /* if (timer1.ms >= 1000) {
        timer1.ms = 0;
        if (++timer1.second >= 60) {
            timer1.second = 0;
            if (++timer1.minute >= 60) {
                timer1.minute = 0;
                if (++timer1.hour >= 24) {
                    timer1.hour = 0;
                    ++timer1.day;
                }
            }
        }
    }*/

}
