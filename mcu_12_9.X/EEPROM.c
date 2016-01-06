#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "LCD.h"
#include "spi.h"
#include "EEPROM.h"

void EEPROM_init(void)
{
    SPICS_EE2_IO = 0;
    SPICS_EE2 = CHIP_SEL_DISABLE;
    SCK_IO = 0;
    SCK = 0;
    SDO_IO = 0;
    SDO = 0;
    SDI_IO = 1;
    SDI = 1;
            
}

void EEPROM_WREN(void)
{
    SPICS_EE2 = CHIP_SEL_ENABLE;
    writeSPI2Byte(WREN);
    SPICS_EE2 = CHIP_SEL_DISABLE;
}

void EEPROM_WRDI(void)
{
    SPICS_EE2 = CHIP_SEL_ENABLE;
    writeSPI2Byte(WRDI);
    SPICS_EE2 = CHIP_SEL_DISABLE;
}

unsigned char EEPROM_RDSR(void)
{
    unsigned char s;
    SPICS_EE2 = CHIP_SEL_ENABLE;
    writeSPI2Byte(RDSR);
    s = readSPI2Byte();
    SPICS_EE2 = CHIP_SEL_DISABLE;
    return s;
}


void EEPROM_Write_Byte(unsigned long addr, unsigned int data_out)
{
    EEPROM_WREN();
    
    SPICS_EE2 = CHIP_SEL_ENABLE;
    writeSPI2Byte(Write);
    writeSPI2Byte(addr >> 16);
    writeSPI2Byte(addr >> 8);
    writeSPI2Byte(addr);
    writeSPI2Byte(data_out);
    SPICS_EE2 = CHIP_SEL_DISABLE;
}

unsigned char EEPROM_Read_Byte(unsigned long addr)
{
    //    int i;
    unsigned char data;
    //EEPROM_WRDI();
    
    SPICS_EE2 = CHIP_SEL_ENABLE;
    writeSPI2Byte(Read);
    writeSPI2Byte(addr >> 16);
    writeSPI2Byte(addr >> 8);
    writeSPI2Byte(addr);
    data = readSPI2Byte();
    SPICS_EE2 = CHIP_SEL_DISABLE;
    
    return data;
    }

void EEPROM_Write_Page(unsigned long addr, unsigned int data_out[] ,unsigned int nbytes)
{
    int     i;
    EEPROM_WREN();
    
    SPICS_EE2 = CHIP_SEL_ENABLE;
    writeSPI2Byte(Write);
    writeSPI2Byte(addr >> 16);
    writeSPI2Byte(addr >> 8);
    writeSPI2Byte((unsigned char)addr);
    for(i = 0;i <= nbytes;i++)
    {
    writeSPI2Byte(data_out[i]);
    }
    SPICS_EE2 = CHIP_SEL_DISABLE;
}

void EEPROM_Read_Page(unsigned long addr, unsigned long nbytes, unsigned char data[])
{
    int     i = 0;
    EEPROM_WRDI();
    
    SPICS_EE2 = CHIP_SEL_ENABLE;
    writeSPI2Byte(Read);
    writeSPI2Byte(addr >> 16);
    writeSPI2Byte(addr >> 8);
    writeSPI2Byte((unsigned char)addr);
    for(i = 0;i < nbytes;i++)
    {
        data[i] = readSPI2Byte();
    }
    SPICS_EE2 = CHIP_SEL_DISABLE;
}

/*void byteout(unsigned char byte, int i)
{
    SCK = 0;
    for (i = 0; i < 8; i++)
    {
        if (byte & 0x80)
        {
            SDO = 1;
        }
        else
        {
            SDO = 0;
        }
        SCK = 1;
        Nop();
        SCK = 0;
        byte = byte << 1; 
    }
    
}*/