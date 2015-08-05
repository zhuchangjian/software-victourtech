#ifndef _LIB_SCB_LPC213X_H_
  #define _LIB_SCB_LPC213X_H_


#include "SystemDef.h"


//外部中断状态位 
#define SCB_EXTINT_EINT0    (0x01)
#define SCB_EXTINT_EINT1    (0x02)
#define SCB_EXTINT_EINT2    (0x04)
#define SCB_EXTINT_EINT3    (0x08)
#define SCB_EXTINT_ALL      (0x0f)

#define IS_SCB_EXTINT_PARAM(param)  ((param <= SCB_EXTINT_ALL))



//外部中断唤醒
#define SCB_EXTWAKE_EINT0     (0x01)
#define SCB_EXTWAKE_EINT1     (0x02)
#define SCB_EXTWAKE_EINT2     (0x04)
#define SCB_EXTWAKE_EINT3     (0x08)
#define SCB_EXTWAKE_BOD       (1 << 14)
#define SCB_EXTWAKE_RTC       (1 << 15)
#define SCB_EXTWAKE_ALL       (0xc00f)

#define IS_SCB_EXTWAKE_PARAM(param)  ((param <= (1 << 15)))


//外部中断极性
#define SCB_EXTPOLAR_EXINT0   (0x01)
#define SCB_EXTPOLAR_EXINT1   (0x02)
#define SCB_EXTPOLAR_EXINT2   (0x04)
#define SCB_EXTPOLAR_EXINT3   (0x08)

#define IS_SCB_EXTPOLAR_PARAM(param) ((param <= 0x0f))


//IO口模式设置
#define SCB_SCS_GPIO0   (0x01)
#define SCB_SCS_GPIO1   (0x02)

#define IS_SCB_SCS_PARAM(param) ((param <= 0x03))

//中断向量映射模式
#define SCB_MEMMAP_BOOTLOADER   (0x00)
#define SCB_MEMMAP_FLASH        (0x01)
#define SCB_MEMMAP_RAM          (0x02)

#define IS_SCB_MEMMAP_PARAM(param) ((param == SCB_MEMMAP_BOOTLOADER) || (param == SCB_MEMMAP_FLASH) || \
	                                (param == SCB_MEMMAP_RAM))

//低功耗模式
#define SCB_PCON_IDL       (0x01)
#define SCB_PCON_PD        (0x02)
#define SCB_PCON_BODPDM    (0x04)
#define SCB_PCON_BOGD      (0x08)
#define SCB_PCON_BORD      (0x10)

#define IS_SCB_PCON_PARAM(param) ((param <= 0x1f))

//外设电源控制
#define SCB_PCONP_PCTIM0        (1 << 1)
#define SCB_PCONP_PCTIM1        (1 << 2)
#define SCB_PCONP_PCUART0       (1 << 3)
#define SCB_PCONP_PCUART1       (1 << 4)
#define SCB_PCONP_PCPWM0        (1 << 5)
#define SCB_PCONP_PCI2C0        (1 << 7)
#define SCB_PCONP_PCSPI0        (1 << 8)
#define SCB_PCONP_PCRTC         (1 << 9)
#define SCB_PCONP_PCSPI1        (1 << 10)
#define SCB_PCONP_PCAD0         (1 << 12)
#define SCB_PCONP_PCI2C1        (1 << 19)
#define SCB_PCONP_PCAD1         (1 << 20)

#define IS_SCB_PCONP_PARAM(param) ((param <= (1 << 20)))


//复位源
#define SCB_RSIR_POR    (0x01)
#define SCB_RSIR_EXTR   (0x02)
#define SCB_RSIR_WDTR   (0x04)
#define SCB_RSIR_BODR   (0x08)

#define IS_SCB_RSID_PARAM(param) ((param <= 0x0f))

//APB时钟
#define SCB_APBDIV_4  (0x00)
#define SCB_APBDIV_1  (0x01)
#define SCB_APBDIV_2  (0x02)

#define IS_SCB_APBDIV_PARAM(param) ((param == SCB_APBDIV_1) || (param == SCB_APBDIV_2) || \
                             (param == SCB_APBDIV_4))

//接口函数
BOOL SCB_ClearEXTINT(__in uint32 bit);
int32 SCB_GetEXTINT(__in uint32 bit);
BOOL SCB_IsEXTINTSet(__in uint32 bit);
BOOL SCB_ClearWakeUpInt(__in uint32 intFlag);
BOOL SCB_SetWakeUpInt(__in uint32 intFlag);
uint32 SCB_GetWakeUpInt(void);
BOOL SCB_SetEXINTMode_Level(__in uint32 channel);
BOOL SCB_SetEXINTMode_Edge(__in uint32 channel);
int32 SCB_GetEXINTMode(__in uint32 channel);
BOOL SCB_SetEXINTPolarity_LowOrFall(__in uint32 channel);
BOOL SCB_SetEXINTPolarity_HighOrRise(__in uint32 channel);
int32 SCB_GetEXINTPolarity(__in uint32 channel);
BOOL SCB_SetPortMode_APB(__in uint32 channel);
BOOL SCB_SetPortMode_GPIO(__in uint32 channel);
int32 SCB_GetPortMode(__in uint32 channel);
BOOL SCB_SetIntVecMap(__in uint8 mode);
uint8 SCB_GetIntVecMap(void);
void SCB_FeedPLL(void);
uint32 SCB_GetCurFrequency(void);
int32 SCB_SetClockFrequency(uint32 frequency);
BOOL SCB_EnterPowerDownMode(uint32 mode);
BOOL SCB_EnablePerpPower(uint32 perp);
BOOL SCB_DisablePerpPower(uint32 perp);
uint32 SCB_GetPerpPower(void);
uint8 SCB_GetResetSource(void);
BOOL SCB_ClearResetSource(uint8 src);
BOOL SCB_SetAPBClock(uint8 divd);
uint8 SCB_GetAPBClock(void);





#endif
















