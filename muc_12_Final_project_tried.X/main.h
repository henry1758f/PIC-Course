#ifndef _MAIN_H
#define	_MAIN_H

#define		CPU_FCY	40 				// for LCD elay referewnce
#ifndef Fcy
#define Fcy     CPU_FCY*1000000
#endif
#define Delay_200uS_Cnt  (Fcy * 0.02) / 1080


typedef struct mytime {
    unsigned int  count;
} mytime_t;

extern mytime_t        timer1;

void T1_Initial(void);
void ADC1_Initial(void);
void PORTS_Test_Initial(void);
void initPLL(void);
void delay200usX(unsigned long);
void delay(unsigned long);

int ADC_read(unsigned char,unsigned char);

#endif	/* _MAIN_H */
