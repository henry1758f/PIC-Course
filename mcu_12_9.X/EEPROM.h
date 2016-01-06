#ifndef EEPROM_H
#define	EEPROM_H

#define PAGE_SIZE 256

#define Write 0x02
#define Read  0x03
#define WREN  0x06
#define WRDI  0x04
#define RDSR  0x05
#define WRSR  0x01
#define PE    0x42
#define SE    0xd8
#define CE    0xc7
#define RDID  0xab
#define DPD   0xb9
#define SCK   LATGbits.LATG6
#define SDO   LATGbits.LATG7
#define SDI   LATGbits.LATG8
#define SCK_IO   TRISGbits.TRISG6
#define SDO_IO   TRISGbits.TRISG7
#define SDI_IO   TRISGbits.TRISG8
#define SPICS_EE2_IO TRISCbits.TRISC3

void EEPROM_init(void);
void EEPROM_WREN(void);
void EEPROM_WRDI(void);
unsigned char EEPROM_RDSR(void);
void EEPROM_Write_Byte(unsigned long addr, unsigned int data_out);
unsigned char EEPROM_Read_Byte(unsigned long addr);
void EEPROM_Write_Page(unsigned long addr, unsigned int data_out[] ,unsigned int nbytes);
void EEPROM_Read_Page(unsigned long addr, unsigned long nbytes, unsigned char data[]);

#endif	/* EEPROM_H */
