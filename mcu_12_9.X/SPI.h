#ifndef SPI_H
#define	SPI_H

/* FIXME: FIXME it goes wrong */
#define SPICS_DS3234            LATCbits.LATC1
#define SPICS_EE1		LATCbits.LATC2
#define SPICS_EE2		LATCbits.LATC3
//#define SPICS_SC740             LATEbits.LATE1
/********************************************************************/
/*              Header for SPI module library functions             */
/********************************************************************/
void initSPI1(void);
void initSPI2(void);
unsigned char readSPI1Byte(void);
unsigned char readSPI2Byte(void);
void  writeSPI1Byte(unsigned int);
void  writeSPI2Byte(unsigned int);

#define CHIP_SEL_ENABLE         0       // low active
#define CHIP_SEL_DISABLE        1

#define SPI_READ            0x00
#define SPI_WRITE           0x80

#if defined(__dsPIC30F__)
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#endif

/* List of SFRs for SPI */
/* This list contains the SFRs with default (POR) values to be used for configuring SPI */
/* The user can modify this based on the requirement */

#define SPI1STAT_VALUE         0x0000
#define SPI2STAT_VALUE         0x0000
#define SPI1BUF_VALUE          0x0000
#define SPI2BUF_VALUE          0x0000

#if defined(__dsPIC33F__) || defined(__PIC24H__) || \
    defined(__dsPIC30F1010__) || defined(__dsPIC30F2020__) || defined(__dsPIC30F2023__)

#define _SPI_V2

#define SPI1CON1_VALUE          0x0000
#define SPI2CON1_VALUE          0x0000
#define SPI1CON2_VALUE          0x0000
#define SPI2CON2_VALUE          0x0000

#elif defined(__dsPIC30F__)

#define _SPI_V1

#define SPI1CON_VALUE          0x0000
#define SPI2CON_VALUE          0x0000

#endif

#if defined(_SPI_V2)

/* SPIXCON1 REGISTER bits differing from 30F devices*/

#define DISABLE_SCK_PIN         0xffff  /* Internal SPI clock is diabled, pin functions as I/O */
#define ENABLE_SCK_PIN          0xefff  /*Internal SPI clock is enabled */

/* SPIXCON2 REGISTER */

#define  FRAME_ENABLE_ON        0xffff  /* Frame SPI support enable        */
#define  FRAME_ENABLE_OFF       0x7fff  /* Frame SPI support Disable       */

#define  FRAME_SYNC_INPUT       0xffff  /* Frame sync pulse Input (slave)  */
#define  FRAME_SYNC_OUTPUT      0xbfff  /* Frame sync pulse Output (master)*/

#define FRAME_POL_ACTIVE_HIGH   0xffff  /* Frame sync pulse is active-high*/
#define FRAME_POL_ACTIVE_LOW    0xdfff  /* Frame sync pulse is active-low */

#define FRAME_SYNC_EDGE_COINCIDE 0xffff  /* Frame sync pulse coincides with first bit clock */
#define FRAME_SYNC_EDGE_PRECEDE  0xfffd  /* Frame sync pulse precedes first bit clock */

#define FIFO_BUFFER_ENABLE      0xffff  /* FIFO buffer enabled */
#define FIFO_BUFFER_DISABLE     0xfffe  /* FIFO buffer enabled */

#elif defined(_SPI_V1)

/* SPIxCON REGISTER bits in 30F (non-SMPS) devices differing from 33F and 24H devices */

#define  FRAME_ENABLE_ON        0xffff  /* Frame SPI support enable        */
#define  FRAME_ENABLE_OFF       0xbfff  /* Frame SPI support Disable       */

#define  FRAME_SYNC_INPUT       0xffff  /* Frame sync pulse Input (slave)  */
#define  FRAME_SYNC_OUTPUT      0xdfff  /* Frame sync pulse Output (master)*/

#endif

#define  DISABLE_SDO_PIN        0xffff  /* SDO pin is not used by module   */
#define  ENABLE_SDO_PIN         0xf7ff  /* SDO pin is  used by module      */

#define  SPI_MODE16_ON          0xffff  /* Communication is word wide      */
#define  SPI_MODE16_OFF         0xfbff  /* Communication is byte wide      */

#define  SPI_SMP_ON             0xffff  /* Input data sampled at end of data output time */
#define  SPI_SMP_OFF            0xfdff  /* Input data sampled at middle of data output time */

#define  SPI_CKE_ON             0xffff  /* Transmit happens from active clock
                                           state to idle clock state*/
#define  SPI_CKE_OFF            0xfeff  /* Transmit happens on transition from
                                           idle clock state to active clock state */

#define  SLAVE_ENABLE_ON        0xffff  /* Slave Select enbale               */
#define  SLAVE_ENABLE_OFF       0xff7f  /* Slave Select not used by module   */

#define  CLK_POL_ACTIVE_LOW     0xffff  /* Idle state for clock is high, active is low */
#define  CLK_POL_ACTIVE_HIGH    0xffbf  /* Idle state for clock is low, active is high */

#define  MASTER_ENABLE_ON       0xffff  /* Master Mode              */
#define  MASTER_ENABLE_OFF      0xffdf  /* Slave Mode               */

#define  SEC_PRESCAL_1_1        0xffff  /* Secondary Prescale 1:1   */
#define  SEC_PRESCAL_2_1        0xfffb  /* Secondary Prescale 2:1   */
#define  SEC_PRESCAL_3_1        0xfff7  /* Secondary Prescale 3:1   */
#define  SEC_PRESCAL_4_1        0xfff3  /* Secondary Prescale 4:1   */
#define  SEC_PRESCAL_5_1        0xffef  /* Secondary Prescale 5:1   */
#define  SEC_PRESCAL_6_1        0xffeb  /* Secondary Prescale 6:1   */
#define  SEC_PRESCAL_7_1        0xffe7  /* Secondary Prescale 7:1   */
#define  SEC_PRESCAL_8_1        0xffe3  /* Secondary Prescale 8:1   */

#define  PRI_PRESCAL_1_1        0xffff  /* Primary Prescale 1:1     */
#define  PRI_PRESCAL_4_1        0xfffe  /* Primary Prescale 4:1     */
#define  PRI_PRESCAL_16_1       0xfffd  /* Primary Prescale 16:1    */
#define  PRI_PRESCAL_64_1       0xfffc  /* Primary Prescale 64:1    */

/* SPIxSTAT REGISTER */

#define  SPI_ENABLE             0xffff  /* Enable module */
#define  SPI_DISABLE            0x7fff  /* Disable module */

#define  SPI_IDLE_CON           0xdfff  /* Continue module operation in idle mode */
#define  SPI_IDLE_STOP          0xffff  /* Discontinue module operation in idle mode */

#define  SPI_RX_OVFLOW_CLR     0xffbf   /* Clear receive overflow bit.*/

/* SPI Interrupt defines */

#define  SPI_INT_EN             0xffff  /* SPI Interrupt Enable     */
#define  SPI_INT_DIS            0xfff7  /* SPI Interrupt Disable    */

#define  SPI_INT_PRI_0          0xfff8  /* SPI Interrupt Prior Level_0 */
#define  SPI_INT_PRI_1          0xfff9  /* SPI Interrupt Prior Level_1 */
#define  SPI_INT_PRI_2          0xfffa  /* SPI Interrupt Prior Level_2 */
#define  SPI_INT_PRI_3          0xfffb  /* SPI Interrupt Prior Level_3 */
#define  SPI_INT_PRI_4          0xfffc  /* SPI Interrupt Prior Level_4 */
#define  SPI_INT_PRI_5          0xfffd  /* SPI Interrupt Prior Level_5 */
#define  SPI_INT_PRI_6          0xfffe  /* SPI Interrupt Prior Level_6 */
#define  SPI_INT_PRI_7          0xffff  /* SPI Interrupt Prior Level_7 */

/* Macros to  Enable/Disable interrupts and set Interrupt priority of SPI1 in 33F*/
#define EnableIntSPI1                    _SPI1IE = 1
#define DisableIntSPI1                   _SPI1IE = 0
#define SetPriorityIntSPI1(priority)     _SPI1IP = priority

/* CloseSPI. Disables SPI module */
void  CloseSPI1() __attribute__ ((section (".libperi")));

/* ConfigINtSPI1. Configure Interrupt enable and priorities */
void ConfigIntSPI1(unsigned int config)  __attribute__ ((section(".libperi")));

/* DataRdySPI */

char DataRdySPI1() __attribute__ ((section (".libperi")));

/* getcSPI. Read byte from SPIBUF register */
#define  getcSPI1    ReadSPI1

/* getsSPI.Write string to SPIBUF */
unsigned int getsSPI1(unsigned int length, unsigned int *rdptr, unsigned int spi_data_wait)
__attribute__ ((section (".libperi")));

/* OpenSPI1 */
#if defined(_SPI_V2)
void OpenSPI1(unsigned int config1,unsigned int config2, unsigned int config3 )__attribute__ ((section(".libperi")));
#elif defined(_SPI_V1)
void OpenSPI1(unsigned int config1,unsigned int config2 ) __attribute__ ((section (".libperi")));
#endif

/* putcSPI.Write byte/word to SPIBUF register */
#define  putcSPI1    WriteSPI1

/* putsSPI Read string from SPIBUF */
void putsSPI1(unsigned int length, unsigned int *wrptr)__attribute__ ((section (".libperi")));

/* ReadSPI.Read byte/word from SPIBUF register */
unsigned int ReadSPI1() __attribute__ ((section (".libperi")));

/* WriteSPI. Write byte/word to SPIBUF register */
void WriteSPI1(unsigned int data_out) __attribute__ ((section (".libperi")));

#ifdef _SPI2IF

/* Macros to  Enable/Disable interrupts and set Interrupt priority of SPI2 */
#define EnableIntSPI2                    _SPI2IE = 1
#define DisableIntSPI2                   _SPI2IE = 0
#define SetPriorityIntSPI2(priority)     _SPI2IP = priority

/* CloseSPI2.Disables SPI module */
void  CloseSPI2()  __attribute__ ((section (".libperi")));

/* ConfigINtSPI2. Configures Interrupt enable and priorities */
void ConfigIntSPI2(unsigned int config)  __attribute__ ((section(".libperi")));

/* OpenSPI2 */
#if defined(_SPI_V2)
void OpenSPI2(unsigned int config1,unsigned int config2, unsigned int config3 )__attribute__ ((section(".libperi")));
#elif defined(_SPI_V1)
void OpenSPI2(unsigned int config1,unsigned int config2 ) __attribute__ ((section (".libperi")));
#endif

/* DataRdySPI2. Test if SPIBUF register is full */
char DataRdySPI2()  __attribute__ ((section (".libperi")));

/* getcSPI2.Read byte from SPIBUF register */
#define  getcSPI2    ReadSPI2

/* getsSPI2.Write string to SPIBUF */
unsigned int getsSPI2(unsigned int length, unsigned int *rdptr, unsigned int spi_data_wait)
 __attribute__ ((section(".libperi")));

/* putcSPI2.Write byte/word to SPIBUF register */
#define  putcSPI2    WriteSPI2

/* putsSPI2. Read string from SPIBUF */
void putsSPI2(unsigned int length, unsigned int *wrptr)__attribute__ ((section(".libperi")));

/* ReadSPI2.Read byte/word from SPIBUF register */
unsigned int ReadSPI2() __attribute__ ((section (".libperi")));

/* WriteSPI2. Write byte/word to SPIBUF register */
void WriteSPI2( unsigned int data_out) __attribute__ ((section(".libperi")));

#endif



#endif	/* SPI_H */
