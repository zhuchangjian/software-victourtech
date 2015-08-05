/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author:
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x 定时器模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_timer_lpc213x.h"
#include "lib_map_lpc213x.h"

/******************************************************/

typedef struct 
{
	volatile uint32 T0IR;
	volatile uint32 T0TCR;
	volatile uint32 T0TC;
	volatile uint32 T0PR;
	volatile uint32 T0PC;
	volatile uint32 T0MCR;
	volatile uint32 T0MR0;
	volatile uint32 T0MR1;
	volatile uint32 T0MR2;
    volatile uint32 T0MR3;
    volatile uint32 T0CCR;
    volatile uint32 T0CR0;
    volatile uint32 T0CR1;
    volatile uint32 T0CR2;
    volatile uint32 T0CR3;
    volatile uint32 T0EMR;
	uint32 Reserved1[12];
    volatile uint32 T0CTCR;
	uint32 Reserved2[4067];
	volatile uint32 T1IR;
	volatile uint32 T1TCR;
	volatile uint32 T1TC;
	volatile uint32 T1PR;
	volatile uint32 T1PC;
	volatile uint32 T1MCR;
	volatile uint32 T1MR0;
	volatile uint32 T1MR1;
	volatile uint32 T1MR2;
    volatile uint32 T1MR3;
    volatile uint32 T1CCR;
    volatile uint32 T1CR0;
    volatile uint32 T1CR1;
    volatile uint32 T1CR2;
    volatile uint32 T1CR3;
    volatile uint32 T1EMR;
	uint32 Reserved3[12];
    volatile uint32 T1CTCR;
}TIMER_TypeDef;

/* VIC结构体地址初始化 */
TIMER_TypeDef *TIMER = (TIMER_TypeDef *)TIMER_BASE;

/******************************************************
*
******************************************************/
#define TCR_ENABLE       0x01
#define TCR_RESET        0x02
#define CTCR_MASK        0x0f
#define MCR_MASK         0x07
#define CCR_MASK         0x07

/************************************************************************
Function: uint32 TIMER_GetIntStatus(TIMERCHANNEL channel)
Description: 取得定时器中断状态
Input:  channel:TIMER0:通道0
                TIMER1:通道1
Output: none
Return: 定时器中断状态
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 TIMER_GetIntStatus(TIMERCHANNEL channel)
{
	if(channel == TIMER0)
	{
		return TIMER->T0IR;
	}
	else if(channel == TIMER1)
	{
		return TIMER->T1IR;
	}
	else
		return (uint32)-1;
}


/************************************************************************
Function: BOOL TIMER_ClearIntStatus(TIMERCHANNEL channel, uint32 intType)
Description: 清除定时器中断状态
Input:  channel:TIMER0:通道0
                TIMER1:通道1
        intType:终端类型
Output: none
Return: TRUE：清除成功
        FALSE：清除失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL TIMER_ClearIntStatus(TIMERCHANNEL channel, uint32 intType)
{
	if(channel == TIMER0)
	{
		TIMER->T0IR |= intType;
	}
	else if(channel == TIMER1)
	{
		TIMER->T1IR |= intType;
	}
	else
		return FALSE;
	
	return TRUE;
}

/************************************************************************
Function: void TIMER_EnableCounting(TIMERCHANNEL channel)
Description: 使能定时器计数
Input:  channel：定时器通道
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_EnableCounting(TIMERCHANNEL channel)
{
	if(channel == TIMER0)
	{
		TIMER->T0TCR |= TCR_ENABLE;
	}
	else if(channel == TIMER1)
	{
		TIMER->T1TCR |= TCR_ENABLE;
	}
}

/************************************************************************
Function: void TIMER_DisableCounting(TIMERCHANNEL channel)
Description: 停止定时器技术
Input:  channel：定时器通道
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_DisableCounting(TIMERCHANNEL channel)
{
	if(channel == TIMER0)
	{
		TIMER->T0TCR &= ~TCR_ENABLE;
	}
	else if(channel == TIMER1)
	{
		TIMER->T1TCR &= ~TCR_ENABLE;
	}
}

/************************************************************************
Function: void TIMER_ResetCounting(TIMERCHANNEL channel)
Description: 复位定时器计数器
Input:  channel:定时器通道
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_ResetCounting(TIMERCHANNEL channel)
{
	if(channel == TIMER0)
	{
		TIMER->T0TCR |= TCR_RESET;
	}
	else if(channel == TIMER1)
	{
		TIMER->T1TCR |= TCR_RESET;
	}
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_SetCountMode(TIMERCHANNEL channel, COUNTMODE mode, uint8 inputPin)
{
    if(channel == TIMER0)
    {
        TIMER->T0CTCR &= ~CTCR_MASK;
        TIMER->T0CTCR |= mode;
        TIMER->T0CTCR |= inputPin;
    }
    else if(channel == TIMER1)
    {
        TIMER->T1CTCR &= ~CTCR_MASK;
        TIMER->T1CTCR |= mode;
        TIMER->T1CTCR |= inputPin;
    }
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 TIMER_GetCounterVal(TIMERCHANNEL channel)
{
    if(channel == TIMER0)
    {
        return TIMER->T0TC;
    }
    else
    {
        return TIMER->T1TC;
    }
}


/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_SetCounterVal(TIMERCHANNEL channel, uint32 val)
{
    if(channel == TIMER0)
    {
        TIMER->T0TC = val;
    }
    else
    {
        TIMER->T1TC = val;
    }
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 TIMER_GetPrescaleVal(TIMERCHANNEL channel)
{
    if(channel == TIMER0)
    {
        return TIMER->T0PR;
    }
    else
    {
        return TIMER->T1PR;
    }
}


/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_SetPrescaleVal(TIMERCHANNEL channel, uint32 val)
{
    if(channel == TIMER0)
    {
        TIMER->T0PR = val;
    }
    else
    {
        TIMER->T1PR = val;
    }
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 TIMER_GetPrescaleCounterVal(TIMERCHANNEL channel)
{
    if(channel == TIMER0)
    {
        return TIMER->T0PC;
    }
    else
    {
        return TIMER->T1PC;
    }
}


/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_SetPrescaleCounterVal(TIMERCHANNEL channel, uint32 val)
{
    if(channel == TIMER0)
    {
        TIMER->T0PC = val;
    }
    else
    {
        TIMER->T1PC = val;
    }
}


/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_SetMatchMode(TIMERCHANNEL channel, uint8 matchChl, uint8 matchMode)
{
    if(channel == TIMER0)
    {
        switch(matchChl)
        {
        case TIMER_MATCH0:
            TIMER->T0MCR &= ~MCR_MASK;
            TIMER->T0MCR |= matchMode;
            break;
        case TIMER_MATCH1:
            TIMER->T0MCR &= ~(MCR_MASK << 3);
            TIMER->T0MCR |= (matchMode << 3);
            break;
        case TIMER_MATCH2:
            TIMER->T0MCR &= ~(MCR_MASK << 6);
            TIMER->T0MCR |= (matchMode << 6);
            break;
        case TIMER_MATCH3:
            TIMER->T0MCR &= ~(MCR_MASK << 9);
            TIMER->T0MCR |= (matchMode << 9);
            break;
        default:
            break;
        }
    }
    else
    {
        switch(matchChl)
        {
        case TIMER_MATCH0:
            TIMER->T1MCR &= ~MCR_MASK;
            TIMER->T1MCR |= matchMode;
            break;
        case TIMER_MATCH1:
            TIMER->T1MCR &= ~(MCR_MASK << 3);
            TIMER->T1MCR |= (matchMode << 3);
            break;
        case TIMER_MATCH2:
            TIMER->T1MCR &= ~(MCR_MASK << 6);
            TIMER->T1MCR |= (matchMode << 6);
            break;
        case TIMER_MATCH3:
            TIMER->T1MCR &= ~(MCR_MASK << 9);
            TIMER->T1MCR |= (matchMode << 9);
            break;
        default:
            break;
        }
    }
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_SetMatchVal(TIMERCHANNEL channel, uint8 matchChl, uint32 val)
{
    if(channel == TIMER0)
    {
        switch(matchChl)
        {
        case TIMER_MATCH0:
            TIMER->T0MR0 = val;
            break;
        case TIMER_MATCH1:
            TIMER->T0MR1 = val;
            break;
        case TIMER_MATCH2:
            TIMER->T0MR2 = val;
            break;
        case TIMER_MATCH3:
            TIMER->T0MR3 = val;
            break;
        default:
            break;
        }
    }
    else
    {
        switch(matchChl)
        {
        case TIMER_MATCH0:
            TIMER->T1MR0 = val;
            break;
        case TIMER_MATCH1:
            TIMER->T1MR1 = val;
            break;
        case TIMER_MATCH2:
            TIMER->T1MR2 = val;
            break;
        case TIMER_MATCH3:
            TIMER->T1MR3 = val;
            break;
        default:
            break;
        }
    }
}


/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void TIMER_SetCompareMode(TIMERCHANNEL channel, uint8 capChl, uint8 capMode)
{
    if(channel == TIMER0)
    {
        switch(capChl)
        {
        case TIMER_CAP0:
            TIMER->T0CCR &= ~CCR_MASK;
            TIMER->T0CCR |= capMode;
            break;
        case TIMER_CAP1:
            TIMER->T0CCR &= ~(CCR_MASK << 3);
            TIMER->T0CCR |= (capMode << 3);
            break;
        case TIMER_CAP2:
            TIMER->T0CCR &= ~(CCR_MASK << 6);
            TIMER->T0CCR |= (capMode << 6);
            break;
        case TIMER_CAP3:
            TIMER->T0CCR &= ~(CCR_MASK << 9);
            TIMER->T0CCR |= (capMode << 9);
            break;
        default:
            break;
        }
    }
    else
    {
        switch(capChl)
        {
        case TIMER_CAP0:
            TIMER->T1CCR &= ~CCR_MASK;
            TIMER->T1CCR |= capMode;
            break;
        case TIMER_CAP1:
            TIMER->T1CCR &= ~(CCR_MASK << 3);
            TIMER->T1CCR |= (capMode << 3);
            break;
        case TIMER_CAP2:
            TIMER->T1CCR &= ~(CCR_MASK << 6);
            TIMER->T1CCR |= (capMode << 6);
            break;
        case TIMER_CAP3:
            TIMER->T1CCR &= ~(CCR_MASK << 9);
            TIMER->T1CCR |= (capMode << 9);
            break;
        default:
            break;
        }
    }
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 TIMER_GetCaptureValue(TIMERCHANNEL channel, uint8 capChl)
{
    uint32 retVal = 0;
    if(channel == TIMER0)
    {
        switch(capChl)
        {
        case TIMER_CAP0:
            retVal = TIMER->T0CR0;
            break;
        case TIMER_CAP1:
            retVal = TIMER->T0CR1;
            break;
        case TIMER_CAP2:
            retVal = TIMER->T0CR2;
            break;
        case TIMER_CAP3:
            retVal = TIMER->T0CR3;
            break;
        default:
            break;
        }
    }
    else
    {
        switch(capChl)
        {
        case TIMER_CAP0:
            retVal = TIMER->T1CR0;
            break;
        case TIMER_CAP1:
            retVal = TIMER->T1CR1;
            break;
        case TIMER_CAP2:
            retVal = TIMER->T1CR2;
            break;
        case TIMER_CAP3:
            retVal = TIMER->T1CR3;
            break;
        default:
            break;
        }
    }
    
    return retVal;
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL TIMER_IsMatchConnected(TIMERCHANNEL channel, uint8 matchChl)
{
    BOOL bRetVal = FALSE;
    if(channel == TIMER0)
    {
        switch(matchChl)
        {
        case TIMER_MATCH0:
            if(TIMER->T0EMR & 0x01)
                bRetVal = TRUE;
            break;
        case TIMER_MATCH1:
            if(TIMER->T0EMR & 0x02)
                bRetVal = TRUE;
            break;
        case TIMER_MATCH2:
            if(TIMER->T0EMR & 0x04)
                bRetVal = TRUE;
            break;
        case TIMER_MATCH3:
            if(TIMER->T0EMR & 0x08)
                bRetVal = TRUE;
            break;
        default:
            break;
        }
    }
    else
    {
        switch(matchChl)
        {
        case TIMER_MATCH0:
            if(TIMER->T1EMR & 0x01)
                bRetVal = TRUE;
            break;
        case TIMER_MATCH1:
            if(TIMER->T1EMR & 0x02)
                bRetVal = TRUE;
            break;
        case TIMER_MATCH2:
            if(TIMER->T1EMR & 0x04)
                bRetVal = TRUE;
            break;
        case TIMER_MATCH3:
            if(TIMER->T1EMR & 0x08)
                bRetVal = TRUE;
            break;
        default:
            break;
        }
    }
    
    return bRetVal;
}

/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
MATCHMODE TIMER_GetMatchMode(TIMERCHANNEL channel, uint8 matchChl)
{
    MATCHMODE nMode = MATCH_NOTHING;
    
    if(channel == TIMER0)
    {
        switch(matchChl)
        {
        case TIMER_MATCH0:
            nMode = (MATCHMODE)((TIMER->T0EMR >> 5) & 0x03);
            break;
        case TIMER_MATCH1:
            nMode = (MATCHMODE)((TIMER->T0EMR >> 7) & 0x03);
            break;
        case TIMER_MATCH2:
            nMode = (MATCHMODE)((TIMER->T0EMR >> 9) & 0x03);
            break;
        case TIMER_MATCH3:
            nMode = (MATCHMODE)((TIMER->T0EMR >> 11) & 0x03);
            break;
        default:
            break;
        }
    }
    else
    {
        switch(matchChl)
        {
         case TIMER_MATCH0:
            nMode = (MATCHMODE)((TIMER->T1EMR >> 5) & 0x03);
            break;
        case TIMER_MATCH1:
            nMode = (MATCHMODE)((TIMER->T1EMR >> 7) & 0x03);
            break;
        case TIMER_MATCH2:
            nMode = (MATCHMODE)((TIMER->T1EMR >> 9) & 0x03);
            break;
        case TIMER_MATCH3:
            nMode = (MATCHMODE)((TIMER->T1EMR >> 11) & 0x03);
            break;
        default:
            break;
        }
    }
    
    return nMode;
}
