/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x 串口模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_uart_lpc213x.h"
#include "lib_map_lpc213x.h"
#include "lib_def_lpc213x.h"
/******************************************************/
#pragma anon_unions
typedef struct 
{
	union
	{
		volatile uint32 U0RBR;
		volatile uint32 U0THR;
		volatile uint32 U0DLL;
	};
	
	union
	{
		volatile uint32 U0DLM;
		volatile uint32 U0IER;	
	};
	
	union
	{
		volatile uint32 U0IIR;
		volatile uint32 U0FCR;	
	};
	
	volatile uint32 U0LCR;
	uint32 Reserved1;
	volatile uint32 U0LSR;
	uint32 Reserved2;
	volatile uint32 U0SCR;
	volatile uint32 U0ACR;
	uint32 Reserved3;
	volatile uint32 U0FDR;
	uint32 Reserved4;
	volatile uint32 U0TER;
    
}UART0_TypeDef;

/* VIC结构体地址初始化 */
UART0_TypeDef *UART0 = (UART0_TypeDef *)UART0_BASE;


/**************************************************************
* UART分频因子表
***************************************************************/
const uint8 DIVSODTTAB[100] = 
{
	0x01, 0x01, 0x01, 0x01, 0x1e, 0x1e, 0x1e, 0x1c,
	0x1b, 0x1a, 0x19, 0x18, 0x17, 0x2d, 0x16, 0x2b,
	0x15, 0x3e, 0x29, 0x14, 0x14, 0x3b, 0x27, 0x3a,
	0x13, 0x13, 0x4b, 0x38, 0x25, 0x5c, 0x37, 0x5b,
	0x12, 0x12, 0x8f, 0x59, 0x47, 0x35, 0x58, 0x9e,
	0x23, 0x57, 0x34, 0x79, 0x45, 0x56, 0x67, 0x89,
	0xcd, 0x11, 0x11, 0xed, 0x98, 0x76, 0x65, 0x54,
	0x97, 0x43, 0x75, 0xd9, 0x32, 0x85, 0x53, 0x74,
	0x95, 0xd7, 0x21, 0x21, 0xb5, 0x94, 0x73, 0x52,
	0x83, 0xb4, 0x31, 0x31, 0xa3, 0x72, 0xb3, 0x41,
	0x41, 0x92, 0xe3, 0x51, 0xb2, 0x61, 0xd2, 0x71,
	0x81, 0x81, 0x91, 0xb1, 0xc1, 0xe1, 0xe1, 0xe1,
	0xe1, 0x10, 0x10, 0x10,
};

/************************************************************************
Function: void UART0_RecvData(__out puint8 buf, __in uint8 readLen, __out puint8 readedLen)
Description: 接受数据
Input: none
Output: none
Return: 串口收到的第一个数据
Author:       
Version: V1.0
Others: none
*************************************************************************/
void UART0_RecvPacket(__out puint8 buf, __in uint8 readLen, __out puint8 readedLen)
{
	uint8 i;
	UART0->U0LCR &= ~(1 << 7);
	*readedLen = 0;
	
	for(i = 0; i < readLen; i++)
	{
		if(UART0->U0LSR & 0x01)
		{
			*buf++ = UART0->U0RBR;
			(*readedLen) += 1;	
		}
		else
			break;
	}
	/*while(UART0->U0LSR & 0x01)
	{
		*buf++ = UART0->U0RBR;
		(*readedLen) += 1;
	}*/
}


/************************************************************************
Function: void UART0_RecvData(__out puint8 buf, __out puint8 readedLen)
Description: 接受数据
Input: none
Output: none
Return: 串口收到的第一个数据
Author:       
Version: V1.0
Others: none
*************************************************************************/
uint8 UART0_RecvByte(void)
{
	UART0->U0LCR &= ~(1 << 7);
	return UART0->U0RBR;
}

/************************************************************************
Function: inline void UART0_SendData(uint8 data) 
Description: 发送数据
Input: data:需要发送的数据
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_SendData(__in puint8 buf, __in uint8 len)
{
	UART0->U0LCR &= ~(1 << 7);
	
	while(len--)
	{
		UART0->U0THR = *buf++;
		while(!((UART0->U0LSR) & (1 << 6)));
	}
    
    
    UART0->U0LCR |= (1 << 7);
}

/************************************************************************
Function: uint32 UART0_GetBaud(void)
Description: 取得当前波特率
Input: none
Output: none
Return: 当前波特率
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 UART0_GetBaud(void)
{
	uint8 DlmVal,DllVal,MulVal,DivVal;
    UART0->U0LCR |= (1 << 7);
	DlmVal = UART0->U0DLM;
	DllVal = UART0->U0DLL;
	MulVal = ((UART0->U0FDR) >> 4) & 0x0f;
	DivVal = (UART0->U0FDR) & 0x0f;
	
	return (CPU_PCLK * MulVal) / (16*(256*DlmVal + DllVal)*(MulVal+DivVal));
}

/************************************************************************
Function: uint32 UART0_SetBaud(uint32 baud)
Description: 设置波特率
Input: baud:需要设置的波特率
Output: none
Return: 当前波特率
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 UART0_SetBaud(uint32 baud)
{
	uint8 DlmVal = 0;
	uint8 DllVal = 0;
	uint8 DivVal;
	uint32 tempVal;
	uint64 calClk;
	
	tempVal = CPU_PCLK / (baud * 16);
	
	DlmVal = tempVal / 256;
	DllVal = tempVal % 256;
	
	calClk = 16 * (256 * DlmVal + DllVal) * baud;
	DivVal = ((calClk * 100) / CPU_PCLK) % 100;
	UART0->U0LCR |= (1 << 7);
	if(calClk == CPU_PCLK)
	{
		UART0->U0DLL = DllVal;
		UART0->U0DLM = DlmVal;
		UART0->U0FDR = 0x10;
	}
	else
	{
		UART0->U0DLL = DllVal;
		UART0->U0DLM = DlmVal;
        UART0->U0FDR = DIVSODTTAB[DivVal];
	}

	return UART0_GetBaud();
	
}

/************************************************************************
Function: void UART0_EnableInt(uint32 intFlag)
Description: 使能串口中断
Input: intFlag:需要使能的中断位
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_EnableInt(uint32 intFlag)
{
    UART0->U0LCR &= ~(1 << 7);
    UART0->U0IER |= intFlag;
}

/************************************************************************
Function: void UART0_DisableInt(uint32 intFlag)
Description: 禁止串口中断
Input: intFlag：需要禁止的中断位
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_DisableInt(uint32 intFlag)
{
    UART0->U0LCR &= ~(1 << 7);
    UART0->U0IER &= ~(intFlag);
}


/************************************************************************
Function: BOOL UART0_IsIntPending(void)
Description: 检测是否有中断产生
Input: none
Output: none
Return: TRUE：有中断产生
        FALSE：没有中断产生
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL UART0_IsIntPending(void)
{
    if((UART0->U0IIR & 0x01) == 0x01)
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: uint32 UART0_GetIntStatus(void)
Description: 取得中断状态
Input: none
Output: none
Return: 中断状态
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 UART0_GetIntFlag(void)
{
    return UART0->U0IIR;
}


/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_EnableFIFO(void)
{
    UART0->U0FCR |= 0x01;
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_DisableFIFO(void)
{
    UART0->U0FCR &= ~0x01;
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_ResetRXFIFO(void)
{
    UART0->U0FCR |= (1 << 1);
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_ResetTXFIFO(void)
{
    UART0->U0FCR |= (1 << 2);
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_SetRXTrigger(uint8 trigger)
{
    UART0->U0FCR &= ~(0x03 << 6);
    UART0->U0FCR |= trigger;
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_SetLineControl(uint8 len, uint8 stopbit, uint8 parity)
{
    UART0->U0LCR &= ~0x03;
    UART0->U0LCR |= len;
    
    UART0->U0LCR &= ~(1 << 2);
    UART0->U0LCR |= stopbit;
    
    if(parity == PARITY_NONE)
    {
        UART0->U0LCR &= ~(1 << 3);
    }
    else
    {
        UART0->U0LCR |= 1 << 3;
        UART0->U0LCR &= ~(0x03 << 4);
        UART0->U0LCR |= parity;
    }
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_EnableBreakTransmission(void)
{
    UART0->U0LCR |= (1 << 6);
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_DisableBreakTransmission(void)
{
    UART0->U0LCR &= ~(1 << 6);
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 UART0_GetLineStatus(void)
{
    return UART0->U0LSR;
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_EnableSendData(void)
{
    UART0->U0TER |= (1 << 7);
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_DisableSendData(void)
{
    UART0->U0TER &= ~(1 << 7);
}

/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void UART0_Open(PCOMINFO pComInfo)
{
    //设置波特率
    UART0_SetBaud(pComInfo->baud);
    //设置线状态
    UART0_SetLineControl(pComInfo->wordlen, pComInfo->stopbit, pComInfo->patity);
    //使能接收和发送FIFO
    //UART0->U0FCR = 0x00;
    //UART0->U0FCR = 0x07;
    //UART0->U0FCR |= pComInfo->trigger;
    //使能接收，发送和线状态中断
    UART0->U0LCR &= ~(1 << 7);
    UART0->U0IER = 0x01;
    //使能发送
    UART0->U0TER |= 1 << 7;
}



