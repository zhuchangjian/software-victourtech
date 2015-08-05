#ifndef _LIB_SPI_LPC213X_H_
  #define _LIB_SPI_LPC213X_H_

#include "SystemDef.h"


/******************************************************/
#include "lib_map_lpc213x.h"
typedef struct 
{
	volatile uint32 S0SPCR;
	volatile uint32 S0SPSR;
    volatile uint32 S0SPDR;
    volatile uint32 S0SPCCR;
    uint32 Reserved[3];
    volatile uint32 S0SPINT;
}SPI_TypeDef;

extern SPI_TypeDef *SPI;



//SPI数据位
#define SPI_DATABITS_8                 (8 << 8)
#define SPI_DATABITS_9                 (9 << 8)
#define SPI_DATABITS_10                (10 << 8)
#define SPI_DATABITS_11                (11 << 8)
#define SPI_DATABITS_12                (12 << 8)
#define SPI_DATABITS_13                (13 << 8)
#define SPI_DATABITS_14                (14 << 8)
#define SPI_DATABITS_15                (15 << 8)
#define SPI_DATABITS_16                (0x00)

//SPI模式
#define SPI_SLAVE                      (0x00)
#define SPI_MASTER                     (1 << 5)

//CPHA极性
#define SPI_CPHA_FIRST                 (0x00)
#define SPI_CPHA_SECOND                (1 << 3)


//CPOL极性
#define SPI_CPOL_HIGH                  (0x00)
#define SPI_CPOL_LOW                   (1 << 4)

//发送顺序
#define SPI_MSB                        (0x00)
#define SPI_LSB                        (1 << 6)

typedef struct 
{
    uint32 bits;
    uint32 cpha;
    uint32 cpol;
    uint32 mstr;
    uint32 lsbf;
}SPIINFO, *PSPIINFO;






void SPI_Open(PSPIINFO info);
uint32 SPI_SetClock(uint32 clock);


#define SPI_GetClock() (CPU_PCLK / (SPI->S0SPCCR))
#define SPI_EnableInt() (SPI->S0SPCR |= (1 << 7))
#define SPI_DisableInt() (SPI->S0SPCR &= ~(1 << 7))
#define SPI_GetStatus() (SPI->S0SPSR)
#define SPI_GetIntFlag() (SPI->S0SPINT & 0x01)
#define SPI_ClearIntFlag() (SPI->S0SPINT = 0x01)
#define SPI_GetData() (SPI->S0SPDR)
#define SPI_WriteData(data) (SPI->S0SPDR = data)








#endif

