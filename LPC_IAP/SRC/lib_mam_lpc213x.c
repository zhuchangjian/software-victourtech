/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_mam_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x MAM模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_mam_lpc213x.h"
#include "lib_map_lpc213x.h"

/******************************************************/


typedef struct 
{
	volatile uint32 MAMCR;
	volatile uint32 MAMTIM;
}MAM_TypeDef;

/* CRC结构体地址初始化 */
MAM_TypeDef *MAM = (MAM_TypeDef *)MAM_BASE;

//MAM寄存器
#define MAMCR_MASK  0x03
#define MAMTIM_MASK  0x07

/************************************************************************
Function: BOOL MAM_SetMode(uint32 mode)
Description:  设置MAM模块控制模式
Input:  mode:  MAM_CONTROL_DISABLE:关闭MAM模块
               MAM_CONTROL_PARTICAL：部分使能
               MAM_CONTROL_FULL：全部使能
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL MAM_SetMode(uint32 mode)
{

	MAM->MAMCR &= ~MAMCR_MASK;
	MAM->MAMCR |= mode;

	return TRUE;
}


/************************************************************************
Function: uint32 MAM_GetMode(void)
Description: 取得MAM控制模块模式
Input:  none
Output: MAM控制模块模式
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 MAM_GetMode(void)
{
	return (MAM->MAMCR & MAMCR_MASK);
}


/************************************************************************
Function: BOOL MAM_SetFetchCycle(uint32 cycle)
Description:  设置MAM模块访问延时时间
Input:  cycle:  MAM_FETCH_1:延时1个时钟周期
                MAM_FETCH_2:延时2个时钟周期
                MAM_FETCH_3:延时3个时钟周期
				MAM_FETCH_4:延时4个时钟周期
				MAM_FETCH_5:延时5个时钟周期
				MAM_FETCH_6:延时6个时钟周期
				MAM_FETCH_7:延时7个时钟周期
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL MAM_SetFetchCycle(uint32 cycle)
{

	MAM->MAMCR &= ~MAMTIM_MASK;
	MAM->MAMCR |= cycle;

	return TRUE;
}


/************************************************************************
Function: uint32 MAM_GetFetchCycle(void)
Description: 取得MAM模块访问延时时间
Input:  none
Output: MAM模块访问延时时间
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 MAM_GetFetchCycle(void)
{
	return (MAM->MAMTIM & MAMTIM_MASK);
}
