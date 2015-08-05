/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x 中断向量模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_vic_lpc213x.h"
#include "lib_map_lpc213x.h"

/*****************************************************/
/* VIC结构体地址初始化 */
VIC_TypeDef *VIC = (VIC_TypeDef *)VIC_BASE;


/************************************************************************
Function: void VIC_ProduceSoftInt(uint32 intNum)
Description: 产生各个外设的软件中断
Input:  intNum:中断号
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_ProduceSoftInt(uint32 intBit)
{
	VIC->VICSoftInt |= intBit;
}

/************************************************************************
Function: void VIC_ClearSoftInt(uint32 intNum)
Description: 清楚各个外设的软件中断位
Input:  intNum:中断号
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_ClearSoftInt(uint32 intBit)
{
	VIC->VICSoftIntClear |= intBit;
}

/************************************************************************
Function: uint32 VIC_GetIntStatus(void)
Description: 取得中断原始状态，不管中断有没有使能
Input:  none
Output: none
Return: 中断状态
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetRawIntStatus(void)
{
	return VIC->VICRawIntr;
}


/************************************************************************
Function: void VIC_EnableInt(uint32 intNum)
Description: 中断使能
Input:  intNum：中断号
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_EnableInt(uint32 intBit)
{
	VIC->VICIntEnable |= intBit;
}


/************************************************************************
Function: uint32 VIC_GetEnabledInt(void)
Description: 取得使能的中断号
Input:  none
Output: none
Return: 使能的中断号
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetEnabledInt(void)
{
	return VIC->VICIntEnable;
}


/************************************************************************
Function: void VIC_DisableInt(uint32 intNum)
Description: 关闭中断
Input:  intNum:中断号
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_DisableInt(uint32 intBit)
{
	VIC->VICIntEnClr |= intBit;
}


/************************************************************************
Function: BOOL VIC_IntSelect(uint32 intBit, INTTYPE type)
Description: 中断通道选择
Input:  intNum:通道号
        type：IRQ：绑定到IRQ中断   FIQ：绑定到FIQ中断
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL VIC_IntSelect(uint32 intBit, INTTYPE type)
{
	if(type == IRQ)
	{
		VIC->VICIntSelect &= ~(intBit);
	}
	else if(type == FIQ)
	{
		VIC->VICIntSelect |= intBit;
	}
	else
		return FALSE;
	
	return TRUE;
}


/************************************************************************
Function: uint32 VIC_GetIRQIntStatus(void)
Description: 取得使能的IRQ中断的状态
Input:  none
Output: none
Return: 中断状态
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetIRQIntStatus(void)
{
	return VIC->VICIRQStatus;
}


/************************************************************************
Function: uint32 VIC_GetFIQIntStatus(void)
Description: 取得使能的FIQ中断的状态
Input:  none
Output: none
Return: 中断状态
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetFIQIntStatus(void)
{
	return VIC->VICFIQStatus;
}


/************************************************************************
Function: void VIC_IRQBind(uint8 irqChannel, uint8 intNum, void *intAddr)
Description: 向量IRQ通道和地址绑定
Input:  irqChannel:irq通道号
		intNum:中断号
        intAddr:中断地址
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_VectIRQBind(uint8 irqChannel, uint32 intNum, uint32 intAddr)
{
	VIC->VICVectAddr[irqChannel] = intAddr;
    VIC->VICVectCntl[irqChannel] = 0x20 | intNum;
}

/************************************************************************
Function: void VIC_NonVectIRQBind(uint8 irqChannel, uint8 intNum, void *intAddr)
Description: 非向量IRQ通道和地址绑定
Input:  irqChannel:irq通道号
		intNum:中断号
        intAddr:中断地址
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_NonVectIRQBind(uint32 intAddr)
{
	if(VIC->VICDefVectAddr == 0x00)  //第一次设置非向量中断ISR地址
		VIC->VICDefVectAddr = intAddr;
}

/************************************************************************
Function: uint32 VIC_GetCurVectAddr(void)
Description: 取得当前优先级最高的向量IRQ或者非向量IRQ的ISR的地址
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
//uint32 VIC_GetCurVectAddr(void)
//{
//	return VIC->VICCurVectAddr;
//}

/************************************************************************
Function: void VIC_ClearCurVectAddr(void)
Description: 清楚当前中断ISR地址，为下一次中断最准备
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
//void VIC_ClearCurVectAddr(void)
//{
//	VIC->VICCurVectAddr = 0;
//}


/************************************************************************
Function: none
Description: none
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_SetVICAcceccMode(VICACCESSMODE mode)
{
	if(mode == USER)
	{
		VIC->VICProtection = 0x00;
	}
	else if(mode == PRIVILEGE)
	{
		VIC->VICProtection = 0x01;
	}
}
















