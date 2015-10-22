#include <xc.h>
#include "keypad.h"
#include "LCD.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/* initial GPIO for keypad purpose */
int keypad_init(void)
{
    PORTA = 0xffff;
    TRISA = 0xffff;     // 0:output   1:input
    LATA = 0xffff;

    PORTG = 0x0000;
    TRISG = 0x0000;     // 0:output   1:input
    LATG = 0xffff;

    //PORTGbits.RG12 = 1;
    return 0;
}

unsigned int keypad_Scan(void)
{
    unsigned int key_status = 0;
    KEYPAD_H1 = 0;
    LCD_Delay200usX(1); /* 1ms */
    /* 0 */
    if (KEYPAD_V1 == 0) {
        key_status |= 0x0001;
    }

    /* 1 */
    if (KEYPAD_V2 == 0) {
        key_status |= 0x0002;
    }

    /* 2 */
    if (KEYPAD_V3 == 0) {
        key_status |= 0x0004;
    }

    /* 3 */
    if (KEYPAD_V4 == 0) {
        key_status |= 0x0008;
    }
    KEYPAD_H1 = 1;

    KEYPAD_H2 = 0;
    LCD_Delay200usX(1); /* 1ms */

    /* 4 */
    if (KEYPAD_V1 == 0) {
        key_status |= 0x0010;
    }

    /* 5 */
    if (KEYPAD_V2 == 0) {
        key_status |= 0x0020;
    }

    /* 6 */
    if (KEYPAD_V3 == 0) {
        key_status |= 0x0040;
    }

    /* 7 */
    if (KEYPAD_V4 == 0) {
        key_status |= 0x0080;
    }
    KEYPAD_H2 = 1;

    /* FIXME: scan 8~F keys */

    return key_status;
}

int keypad_GetButton(char target)
{
    unsigned int    key;

    key = keypad_Scan();
    if (key & (1<<target)) {
        LCD_Delay200usX(250); /* 50ms */
        key = keypad_Scan();
        if (key & (1<<target)) {
            return 1;
        }
    }

    return 0;
}

/* test task for keypad */
int keypad_task(void)
{
    int ii;
    static int cnt = 0;
    char temp[10];
    //keypad_init();

//    while(1) {
        for (ii=0; ii<16; ii++) {
            if (keypad_GetButton(ii)) {
                LCD_Cursor_New(2, 0);
                sprintf(temp, "%X", ii);
                putsLCD((unsigned char *)temp);
                if (++cnt >= 20) {
                    cnt = 0;
                }
            }
        }

//        LCD_Delay200usX(5); /* 1ms */
//    }
    return 0;
}

