/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x 系统控制模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_scb_lpc213x.h"
#include "lib_map_lpc213x.h"


/***********************************************************
*
************************************************************/
#define OSC_FREQUENCY 12000000
#define MAX_FREQUENCY 60000000
#define MIN_FREQUENCY 10000000

/******************************************************/

typedef struct 
{
	volatile uint32 MEMMAP;
	volatile uint32 Reserved0[15];
	volatile uint32 PLLCON;
	volatile uint32 PLLCFG;
	volatile uint32 PLLSTAT;
	volatile uint32 PLLFEED;
	volatile uint32 Reserved1[12];
	volatile uint32 PCON;
	volatile uint32 PCONP;
	volatile uint32 Reserved2[14];
	volatile uint32 APBDIV;
	volatile uint32 Reserved3[15];
	volatile uint32 EXTINT;
	volatile uint32 INTWAKE;
	volatile uint32 EXTMODE;
	volatile uint32 EXTPOLAR;
	volatile uint32 Reserved4[12];
	volatile uint32 RSID;
	volatile uint32 CSPR;
	volatile uint32 Reserved[6];
	volatile uint32 SCS;
	
}SCB_TypeDef;

/* CRC结构体地址初始化 */
SCB_TypeDef *SCB = (SCB_TypeDef *)SCB_BASE;

//SCB寄存器
#define EXTINT_MASK 0x0f
#define EXTWAKE_MASK 0xc00f
#define EXTMODE_MASK 0x0f
#define EXTPOLAR_MASK 0x0f
#define SCS_MASK 0x03
#define MEMMAP_MASK 0x03

//PLL寄存器
#define PLL_ENABLE (0x01)
#define PLL_CONNECT (0x02)

#define PLL_STS_ENABLE (1 << 8)
#define PLL_STS_CONNECT (1 << 9)
#define PLL_STS_LOCK (1 << 10)
#define PLL_M_MASK (0x1f)
#define FCCO_LOW 156000000
#define FCCO_HIGH 320000000

//power
#define PCON_MASK (0x1f) 
#define PCONP_MASK (0x1817be)
#define RSID_MASK (0x0f)
#define APBDIV_MASK (0x03)

/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  清零外部中断状态寄存器
Input:  bit: SCB_EXTINT_EINT0  外部中断0位
			 SCB_EXTINT_EINT1  外部中断1位
			 SCB_EXTINT_EINT2  外部中断2位
			 SCB_EXTINT_EINT3  外部中断3位
			 SCB_EXTINT_ALL   外部中断0-3位
Output: none
Return: TRUE：清零成功
		FALSE：清零失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_ClearEXTINT(__in uint32 bit)
{	
	
	bit &= EXTINT_MASK;
	SCB->EXTINT |= bit;
	
	return TRUE;
}


/************************************************************************
Function: uint32 SCB_GetEXTINT(uint32 bit)
Description:  取得外部中断状态寄存器
Input:  bit: SCB_EXTINT_EINT0  外部中断0位
			 SCB_EXTINT_EINT1  外部中断1位
			 SCB_EXTINT_EINT2  外部中断2位
			 SCB_EXTINT_EINT3  外部中断3位
			 SCB_EXTINT_ALL   外部中断0-3位
Output: none
Return: 状态标志
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetEXTINT(__in uint32 bit)
{
	bit &= EXTINT_MASK;
	
	return (SCB->EXTINT & bit);
}

/************************************************************************
Function: BOOL SCB_IsEXTINTSet(bit)
Description:  取得外部中断状态寄存器特定一位的状态
Input:  bit: SCB_EXTINT_EINT0  外部中断0位
			 SCB_EXTINT_EINT1  外部中断1位
			 SCB_EXTINT_EINT2  外部中断2位
			 SCB_EXTINT_EINT3  外部中断3位
Output: none
Return: 状态标志
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_IsEXTINTSet(__in uint32 bit)
{
	bit &= EXTINT_MASK;
	if(SCB->EXTINT & bit)
	{
		return TRUE;
	}
	
	return FALSE;
}

/************************************************************************
Function: BOOL SCB_ClearWakeUpInt(uint32 intFlag)
Description: 清零中断唤醒
Input:  intFlag:  SCB_EXTWAKE_EINT0 外部中断0唤醒
				  SCB_EXTWAKE_EINT1 外部中断1唤醒
				  SCB_EXTWAKE_EINT2 外部中断2唤醒
				  SCB_EXTWAKE_EINT3 外部中断3唤醒
				  SCB_EXTWAKE_BOD BOD中断唤醒
				  SCB_EXTWAKE_RTC RTC中断唤醒
Output: none
Return: 状态标志
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_ClearWakeUpInt(__in uint32 intFlag)
{
	intFlag &= EXTWAKE_MASK;
	SCB->INTWAKE &= ~intFlag;
	
	return TRUE;
}

/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: 设置中断唤醒
Input:  intFlag:  SCB_EXTWAKE_EINT0 外部中断0唤醒
				  SCB_EXTWAKE_EINT1 外部中断1唤醒
				  SCB_EXTWAKE_EINT2 外部中断2唤醒
				  SCB_EXTWAKE_EINT3 外部中断3唤醒
				  SCB_EXTWAKE_BOD BOD中断唤醒
				  SCB_EXTWAKE_RTC RTC中断唤醒
Output: none
Return: 状态标志
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetWakeUpInt(__in uint32 intFlag)
{
	intFlag &= EXTWAKE_MASK;
	SCB->INTWAKE |= intFlag;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: 取得中断唤醒标志
Input:  none
Output: none
Return: 状态标志
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SCB_GetWakeUpInt(void)
{
	return (SCB->INTWAKE & EXTWAKE_MASK);
}

/************************************************************************
Function: BOOL SCB_SetEXINTMode_Level(uint32 channel)
Description: 设置中断唤醒,电平
Input: channel（中断通道）：
       SCB_EXTMODE_EINT0：外部中断0
	   SCB_EXTMODE_EINT1：外部中断1
	   SCB_EXTMODE_EINT2：外部中断2
	   SCB_EXTMODE_EINT3：外部中断3
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTMode_Level(__in uint32 channel)
{
	channel &= EXTMODE_MASK;
	SCB->EXTMODE &= ~channel;
	
	return TRUE;
}

/************************************************************************
Function: BOOL SCB_SetEXINTMode_Edge(uint32 channel)
Description: 设置中断唤醒，边沿
Input:  channel（中断通道）：
       SCB_EXTMODE_EINT0：外部中断0
	   SCB_EXTMODE_EINT1：外部中断1
	   SCB_EXTMODE_EINT2：外部中断2
	   SCB_EXTMODE_EINT3：外部中断3
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTMode_Edge(__in uint32 channel)
{
	channel &= EXTMODE_MASK;
	SCB->EXTMODE |= channel;
	
	return TRUE;
}


/************************************************************************
Function: uint32 SCB_GetEXINTMode(uint32 channel)
Description: 设置中断唤醒
Input:  channel（中断通道）：
       SCB_EXTMODE_EINT0：外部中断0
	   SCB_EXTMODE_EINT1：外部中断1
	   SCB_EXTMODE_EINT2：外部中断2
	   SCB_EXTMODE_EINT3：外部中断3
Output: none
Return: 状态标志
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetEXINTMode(__in uint32 channel)
{
	channel &= EXTMODE_MASK; 
	return (SCB->EXTMODE & channel);
}


/************************************************************************
Function: BOOL SCB_SetEXINTPolarity_LowOrFall(uint32 channel)
Description: 设置中断极性,低电平或下降沿
Input:  channel（中断通道）：
       SCB_EXTPOLAR_EINT0：外部中断0
	   SCB_EXTPOLAR_EINT1：外部中断1
	   SCB_EXTPOLAR_EINT2：外部中断2
	   SCB_EXTPOLAR_EINT3：外部中断3
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTPolarity_LowOrFall(__in uint32 channel)
{
	channel &= EXTPOLAR_MASK;
	SCB->EXTPOLAR &= ~channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: 设置中断极性,高电平或上升沿
Input:  channel（中断通道）：
       SCB_EXTPOLAR_EINT0：外部中断0
	   SCB_EXTPOLAR_EINT1：外部中断1
	   SCB_EXTPOLAR_EINT2：外部中断2
	   SCB_EXTPOLAR_EINT3：外部中断3
Output: none
Return: TRUE：设置成功
        FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTPolarity_HighOrRise(__in uint32 channel)
{
	channel &= EXTPOLAR_MASK;
	SCB->EXTPOLAR |= channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: 设置中断唤醒
Input:  channel（中断通道）：
       SCB_EXTPOLAR_EINT0：外部中断0
	   SCB_EXTPOLAR_EINT1：外部中断1
	   SCB_EXTPOLAR_EINT2：外部中断2
	   SCB_EXTPOLAR_EINT3：外部中断3
Output: none
Return: 中断极性状态标志
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetEXINTPolarity(__in uint32 channel)
{
	channel &= EXTPOLAR_MASK;
	
	return (SCB->EXTPOLAR & channel);
}


/************************************************************************
Function: BOOL SCB_SetPortMode_APB(uint32 channel)
Description: 设置端口模式
Input: channel： 
      SCB_SCS_GPIO0:GPIO0端口
      SCB_SCS_GPIO1:GPIO1端口
Output: none
Return: TRUE：设置成功
        FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetPortMode_APB(__in uint32 channel)
{
	channel &= SCS_MASK;
	
	SCB->SCS &= ~channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetPortMode_GPIO(uint32 channel)
Description: 设置端口模式
Input: channel： 
      SCB_SCS_GPIO0:GPIO0端口
      SCB_SCS_GPIO1:GPIO1端口
Output: none
Return: TRUE：设置成功
        FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetPortMode_GPIO(__in uint32 channel)
{
	channel &= SCS_MASK;
	
	SCB->SCS |= channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL uint32 SCB_GetPortMode(uint32 channel)
Description: 取得端口设置的模式
Input: channel： 
      SCB_SCS_GPIO0:GPIO0端口
      SCB_SCS_GPIO1:GPIO1端口
Output: none
Return: 端口设置模式
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetPortMode(__in uint32 channel)
{
	channel &= SCS_MASK;
	
	return (SCB->SCS & channel);
}

/************************************************************************
Function: BOOL SCB_SetIntVecMap(uint32 mode)
Description: 设置内存映射模式
Input: mode:
	   SCB_MEMMAP_BOOTLOADER: boot loader模式
	   SCB_MEMMAP_FLASH: 内部flash模式
	   SCB_MEMMAP_RAM: 内部ram模式
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetIntVecMap(__in uint8 mode)
{
	mode &= MEMMAP_MASK;
	
	SCB->MEMMAP &= ~MEMMAP_MASK;
	SCB->MEMMAP |= mode;
	
	return TRUE;
}

/************************************************************************
Function: uint8 SCB_GetIntVecMap(void)
Description: 取得内存映射模式
Input: none
Output: none
Return: 内存映射模式
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SCB_GetIntVecMap(void)
{	
	return (SCB->MEMMAP & MEMMAP_MASK);
}

/************************************************************************
Function: inline void SCB_FeedPLL(void)
Description: 在修改PLLCFG和PLLCON之前必须调用此函数
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void SCB_FeedPLL(void)
{
	SCB->PLLFEED = 0xAA;
	SCB->PLLFEED = 0x55;
}

/************************************************************************
Function: uint32 SCB_GetCurFrequence(void)
Description: 取得当前系统频率
Input: none
Output: none
Return: 返回当前系统频率
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SCB_GetCurFrequency(void)
{
	uint8 M_VAL = 0;
	uint32 curFreq = OSC_FREQUENCY;
	//PLL已经连接
	if(((SCB->PLLSTAT & PLL_STS_ENABLE) == PLL_STS_ENABLE) && ((SCB->PLLSTAT & PLL_STS_CONNECT) == PLL_STS_CONNECT))
	{
		M_VAL = (SCB->PLLCFG & PLL_M_MASK);
		curFreq *= (M_VAL + 1);
	}
	
	
	return curFreq;
}


/************************************************************************
Function: uint32 SCB_SetClockFreequence(uint32 frequence)
Description: 设置系统频率
Input: 系统频率
Output: none
Return: 成功返回之前的频率，失败返回（-1）
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_SetClockFrequency(uint32 frequency)
{
	uint8 M_VAL = 0;
	uint8 P_VAL = 0;
	uint32 Fcco= 0;
	uint32 Old_Freq = 0;
	BOOL bFlag = FALSE;
	
	//取得当前的频率
	Old_Freq = SCB_GetCurFrequency();
	
	if(frequency > MAX_FREQUENCY)  //频率设置过大
	{
		frequency = MAX_FREQUENCY;
	}
	
	if(frequency < MIN_FREQUENCY)  //频率设置过小
	{
		frequency = MIN_FREQUENCY;  
	}
	
	//先判断当前PLL有没有锁定或链接
	if(((SCB->PLLSTAT & PLL_ENABLE) == PLL_ENABLE) || ((SCB->PLLSTAT & PLL_CONNECT) == PLL_CONNECT))
	{
		SCB->PLLCON = 0x00;
		SCB_FeedPLL();
	}
	
	//设置倍频数和分频数
	//倍频系数  M值必须在1-32之间
	M_VAL = frequency / OSC_FREQUENCY;
	if(M_VAL < 1)
	{
		M_VAL = 1;  //不倍频
	}
	else if(M_VAL > 32)
	{
		M_VAL = 32;  //最大倍频
	}
		
	//设置分频系数 Fcco在156MHz和320MHz之间
	//P值为1，2，4，8
	P_VAL = 1;
	Fcco = P_VAL * 2 * M_VAL * OSC_FREQUENCY;
	while(Fcco < FCCO_HIGH)
	{
		if(Fcco > FCCO_LOW)
		{
			bFlag = TRUE;
			break;
		}
		
		P_VAL *= 2;
		Fcco = P_VAL * 2 * M_VAL * OSC_FREQUENCY;
		
		if(P_VAL > 8)
			break;
	}
	
	if(bFlag)  //设置成功
	{
		SCB->PLLCFG = 0x00;
		SCB->PLLCFG |= (((P_VAL - 1) << 5) | (M_VAL - 1));
		SCB_FeedPLL();
		SCB->PLLCON |= PLL_ENABLE;
		SCB_FeedPLL();
		//等待PLL锁定
		while(!(SCB->PLLSTAT & PLL_STS_LOCK));
		SCB->PLLCON |= PLL_CONNECT;  //PLL连接
		SCB_FeedPLL();
		
		return Old_Freq;
	}
	else
	{
		/*
		  可以加入回复之前频率的代码
		*/
		return (-1);
	}
}


/************************************************************************
Function: BOOL SCB_EnterPowerDownMode(uint32 mode)
Description: 进入低功耗模式
Input: mode
Output: none
Return: TRUE:设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_EnterPowerDownMode(uint32 mode)
{
	mode &= PCON_MASK;
	SCB->PCON |= PCON_MASK;
	
	return FALSE;
}

/************************************************************************
Function: BOOL SCB_EnablePerpPower(uint32 perp)
Description: 使能外设模块的电源
Input: perp
Output: none
Return: TRUE:设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_EnablePerpPower(uint32 perp)
{
	perp &= PCONP_MASK;
	
	SCB->PCONP |= perp;
	
	return TRUE;
	
}


/************************************************************************
Function: BOOL SCB_DisablePerpPower(uint32 perp)
Description: 断开外设电源
Input: perp
Output: none
Return: TRUE:设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_DisablePerpPower(uint32 perp)
{
	perp &= PCONP_MASK;
	
	SCB->PCONP &= ~perp;
	
	return TRUE;
}

/************************************************************************
Function: uint32 SCB_GetPerpPower(void)
Description: 取得外设电源
Input: perp
Output: none
Return: TRUE:设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SCB_GetPerpPower(void)
{
	return (SCB->PCONP & PCONP_MASK);
}

/************************************************************************
Function: uint8 SCB_GetResetSource(void)
Description: 取得复位源
Input: none
Output: none
Return: 复位源
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SCB_GetResetSource(void)
{
	return (SCB->RSID & RSID_MASK);
}

/************************************************************************
Function: BOOL SCB_ClearResetSource(uint8 src)
Description: 复位复位源
Input: src:复位源
Output: none
Return: TRUE:复位成功
		FALSE：复位失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_ClearResetSource(uint8 src)
{
	src &= RSID_MASK;
	
	SCB->RSID |= src;
	
	return TRUE;
}

/************************************************************************
Function: BOOL SCB_SetAPBClock(uint8 src)
Description: 设置APB总线时钟分频
Input: src:复位源
Output: none
Return: TRUE:复位成功
		FALSE：复位失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetAPBClock(uint8 divd)
{
	divd &= APBDIV_MASK;
	
	SCB->APBDIV |= divd;
	
	return TRUE;
}

/************************************************************************
Function: uint8 SCB_GetAPBClock(void)
Description: 取得APB总线时钟分频
Input: none
Output: none
Return: APB总线分频系数
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SCB_GetAPBClock(void)
{
	return (SCB->APBDIV & APBDIV_MASK);
}
