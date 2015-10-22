#ifndef _MAIN_H
#define	_MAIN_H

#define		CPU_FCY	40 				// for LCD elay referewnce
#ifndef Fcy
#define Fcy     CPU_FCY*1000000
#endif
#define Delay_200uS_Cnt  (Fcy * 0.02) / 1080


typedef struct mytime {
    unsigned short  day;
    unsigned char   hour;
    unsigned char   minute;
    unsigned char   second;
    unsigned short  ms;
} mytime_t;

extern mytime_t        timer1;

void T1_Initial(void);
void ADC1_Initial(void);

#endif	/* _MAIN_H */
