/*
 * File:   keypad.h
 * Author: Felix
 *
 * Created on 2014年6月6日, 下午 8:05
 */

#ifndef _KEYPAD_H
#define	_KEYPAD_H

#define KEY_START           10
#define KEY_ABORT           14
#define KEY_NULL            -1


#define KEYPAD_V1           PORTAbits.RA0
#define KEYPAD_V2           PORTAbits.RA1
#define KEYPAD_V3           PORTAbits.RA2
#define KEYPAD_V4           PORTAbits.RA3
#define KEYPAD_H1           LATGbits.LATG12
#define KEYPAD_H2           LATGbits.LATG13
#define KEYPAD_H3           LATGbits.LATG14
#define KEYPAD_H4           LATGbits.LATG15

typedef enum {
    KEYPAD_0,
    KEYPAD_1,
    KEYPAD_2,
    KEYPAD_3,
    KEYPAD_4,
    KEYPAD_5,
    KEYPAD_6,
    KEYPAD_7,
    KEYPAD_8,
    KEYPAD_9,
    KEYPAD_A,
    KEYPAD_B,
    KEYPAD_C,
    KEYPAD_D,
    KEYPAD_E,
    KEYPAD_F,
} KEYPAD_INDEX;

int keypad_init(void);
unsigned int keypad_Scan(void);
int keypad_GetButton(char target);
int keypad_task(void);

#endif	/* _KEYPAD_H */

