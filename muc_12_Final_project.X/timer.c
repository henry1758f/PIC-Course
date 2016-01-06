
#include <xc.h>
#include "main.h"

unsigned int    t1_counter = 0 ;
unsigned int    time_sec = 0;
mytime_t        timer1;

void T1_Initial(void)
{
    /* this timer 1 setup for interrupt every 10ms, used for system tick */
    PR1 = 100;
    T1CON = 0x00;
    T1CONbits.TCKPS = 0;    /* prescale = 1:8 */
    T1CONbits.TON = 1;      /* enable timer */
    IEC0bits.T1IE = 1;
}
