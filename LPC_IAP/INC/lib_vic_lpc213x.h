#ifndef _LIB_VIC_LPC213X_H_
  #define _LIB_VIC_LPC213X_H_

#include "SystemDef.h"


/******************************************************/

typedef struct 
{
	volatile uint32 VICIRQStatus;
	volatile uint32 VICFIQStatus;
	volatile uint32 VICRawIntr;
	volatile uint32 VICIntSelect;
	volatile uint32 VICIntEnable;
	volatile uint32 VICIntEnClr;
	volatile uint32 VICSoftInt;
	volatile uint32 VICSoftIntClear;
	volatile uint32 VICProtection;
	uint32 Reserved1[3];
	volatile uint32 VICCurVectAddr;
	volatile uint32 VICDefVectAddr;
	uint32 Reserved2[50];
	volatile uint32 VICVectAddr[16];
	uint32 Reserved3[48];
	volatile uint32 VICVectCntl[16];
}VIC_TypeDef;

extern VIC_TypeDef *VIC;


//中断位
#define VIC_INTBIT_WDT              (0x01)
#define VIC_INTBIT_ARMCORE0         (0x04)
#define VIC_INTBIT_ARMCORE1         (0x08)
#define VIC_INTBIT_TIMER0           (1 << 4)
#define VIC_INTBIT_TIMER1           (1 << 5)
#define VIC_INTBIT_UART0            (1 << 6)
#define VIC_INTBIT_UART1            (1 << 7)
#define VIC_INTBIT_PWM0             (1 << 8)
#define VIC_INTBIT_I2C0             (1 << 9)
#define VIC_INTBIT_SPI0             (1 << 10)
#define VIC_INTBIT_SPI1             (1 << 11)
#define VIC_INTBIT_PLL              (1 << 12)
#define VIC_INTBIT_RTC              (1 << 13)
#define VIC_INTBIT_EINT0            (1 << 14)
#define VIC_INTBIT_EINT1            (1 << 15)
#define VIC_INTBIT_EINT2            (1 << 16)
#define VIC_INTBIT_EINT3            (1 << 17)
#define VIC_INTBIT_AD0              (1 << 18)
#define VIC_INTBIT_I2C1             (1 << 19)
#define VIC_INTBIT_BOD              (1 << 20)
#define VIC_INTBIT_AD1              (1 << 21)


//中断号
#define VIC_INTNUM_WDT              0
#define VIC_INTNUM_ARMCORE0         2
#define VIC_INTNUM_ARMCORE1         3
#define VIC_INTNUM_TIMER0           4
#define VIC_INTNUM_TIMER1           5
#define VIC_INTNUM_UART0            6
#define VIC_INTNUM_UART1            7
#define VIC_INTNUM_PWM0             8
#define VIC_INTNUM_I2C0             9
#define VIC_INTNUM_SPI0             10
#define VIC_INTNUM_SPI1             11
#define VIC_INTNUM_PLL              12
#define VIC_INTNUM_RTC              13
#define VIC_INTNUM_EINT0            14
#define VIC_INTNUM_EINT1            15
#define VIC_INTNUM_EINT2            16
#define VIC_INTNUM_EINT3            17
#define VIC_INTNUM_AD0              18
#define VIC_INTNUM_I2C1             19
#define VIC_INTNUM_BOD              20
#define VIC_INTNUM_AD1              21

//IRQ通道
#define IRQ_CHANNEL0             0
#define IRQ_CHANNEL1             1
#define IRQ_CHANNEL2             2
#define IRQ_CHANNEL3             3
#define IRQ_CHANNEL4             4
#define IRQ_CHANNEL5             5
#define IRQ_CHANNEL6             6
#define IRQ_CHANNEL7             7
#define IRQ_CHANNEL8             8
#define IRQ_CHANNEL9             9
#define IRQ_CHANNEL10            10
#define IRQ_CHANNEL11            11
#define IRQ_CHANNEL12            12
#define IRQ_CHANNEL13            13
#define IRQ_CHANNEL14            14
#define IRQ_CHANNEL15            15


//中断通道
typedef enum
{
	IRQ,
	FIQ,
}INTTYPE;


//中断访问权限
typedef enum
{
	USER,
	PRIVILEGE,
}VICACCESSMODE;




	
//外部接口函数
void VIC_ProduceSoftInt(uint32 intBit);
void VIC_ClearSoftInt(uint32 intBit);
uint32 VIC_GetRawIntStatus(void);
void VIC_EnableInt(uint32 intBit);
uint32 VIC_GetEnabledInt(void);
void VIC_DisableInt(uint32 intBit);
BOOL VIC_IntSelect(uint32 intBit, INTTYPE type);
uint32 VIC_GetIRQIntStatus(void);
uint32 VIC_GetFIQIntStatus(void);
void VIC_VectIRQBind(uint8 irqChannel, uint32 intNum, uint32 intAddr);
void VIC_NonVectIRQBind(uint32 intAddr);
//uint32 VIC_GetCurVectAddr(void);
//void VIC_ClearCurVectAddr(void);
void VIC_SetVICAcceccMode(VICACCESSMODE mode);

#define VIC_GetCurVectAddr() (VIC->VICCurVectAddr)
#define VIC_ClearCurVectAddr() (VIC->VICCurVectAddr = 0)













#endif

