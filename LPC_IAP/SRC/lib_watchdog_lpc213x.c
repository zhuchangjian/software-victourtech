/*****************************************************************
**  Copyright (C), 2013-2014, ZCJ Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2014-08-18
**  Description: lpc213x 看门狗程序
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_map_lpc213x.h"
#include "lib_watchdog_lpc213x.h"
typedef struct 
{
	volatile uint32 WDMOD;
	volatile uint32 WDTC;
	volatile uint32 WDFEED;
	volatile uint32 WDTV;	
}WD_TypeDef;

/* CRC结构体地址初始化 */
WD_TypeDef *WD = (WD_TypeDef *)WATCHDOG_BASE;

/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  清零外部中断状态寄存器

Output: none
Return: TRUE：清零成功
		FALSE：清零失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
void WD_Feed(void)
{	
	__disable_irq();
	WD->WDFEED = 0xAA;
	
	WD->WDFEED = 0x55;
	__enable_irq();
}
/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  清零外部中断状态寄存器

Output: none
Return: TRUE：清零成功
		FALSE：清零失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
void WD_SetCount(__in uint32 count)
{	
	WD->WDTC = count;
}
/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  清零外部中断状态寄存器

Output: none
Return: TRUE：清零成功
		FALSE：清零失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
void WD_ModeSet(__in WDMODE mode)
{	
	WD->WDMOD |= mode;
}
/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  清零外部中断状态寄存器

Output: none
Return: TRUE：清零成功
		FALSE：清零失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
void WD_ClearFlag(void)
{	
	WD->WDMOD &= 0xFB;
}
/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  清零外部中断状态寄存器

Output: none
Return: TRUE：清零成功
		FALSE：清零失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 WD_GetFlag(__in uint8 bit)
{	
	bit &= 0x0F;
	
	return (WD->WDMOD & bit);
}
/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  清零外部中断状态寄存器

Output: none
Return: TRUE：清零成功
		FALSE：清零失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 WD_GetCount(void)
{		
	return WD->WDTV;
}
