#ifndef _LIB_TIMER_LPC213X_H_
  #define _LIB_TIMER_LPC213X_H_

#include "SystemDef.h"


//定时器中断标志
#define TIMER_INT_MR0    0x01
#define TIMER_INT_MR1    0x02
#define TIMER_INT_MR2    0x04
#define TIMER_INT_MR3    0x08
#define TIMER_INT_CR0    0x01
#define TIMER_INT_CR1    0x02
#define TIMER_INT_CR2    0x04
#define TIMER_INT_CR3    0x08


//捕捉引脚
#define TIMER_PIN_CAP0   0x00
#define TIMER_PIN_CAP1   0x04
#define TIMER_PIN_CAP2   0x08
#define TIMER_PIN_CAP3   0x0c

//匹配模式
#define TIMER_MATCH0             0x01
#define TIMER_MATCH1             0x02
#define TIMER_MATCH2             0x03
#define TIMER_MATCH3             0x04

#define TIMER_MATCH_INT          0x01
#define TIMER_MATCH_RESET        0x02
#define TIMER_MATCH_STOP         0x04

//捕捉模式
#define TIMER_CAP0             0x01
#define TIMER_CAP1             0x02
#define TIMER_CAP2             0x03
#define TIMER_CAP3             0x04

#define TIMER_CAP_RISE        0x01
#define TIMER_CAP_FALL        0x02
#define TIMER_CAP_INT         0x04



typedef enum
{
	TIMER0,
	TIMER1,
}TIMERCHANNEL;


typedef enum
{
	COUNTER_PCLK,
	COUNTER_RISE,
	COUNTER_FALL,
	COUNTER_BOTH,
}COUNTMODE;

typedef enum
{
    MATCH_NOTHING,
    MATCH_CLEAR,
    MATCH_SET,
    MATCH_TOGGLE,
}MATCHMODE;


//外部接口函数
uint32 TIMER_GetIntStatus(TIMERCHANNEL channel);
BOOL TIMER_ClearIntStatus(TIMERCHANNEL channel, uint32 intType);
void TIMER_EnableCounting(TIMERCHANNEL channel);
void TIMER_DisableCounting(TIMERCHANNEL channel);
void TIMER_ResetCounting(TIMERCHANNEL channel);
void TIMER_SetCountMode(TIMERCHANNEL channel, COUNTMODE mode, uint8 inputPin);
uint32 TIMER_GetCounterVal(TIMERCHANNEL channel);
void TIMER_SetCounterVal(TIMERCHANNEL channel, uint32 val);
uint32 TIMER_GetPrescaleVal(TIMERCHANNEL channel);
void TIMER_SetPrescaleVal(TIMERCHANNEL channel, uint32 val);
uint32 TIMER_GetPrescaleCounterVal(TIMERCHANNEL channel);
void TIMER_SetPrescaleCounterVal(TIMERCHANNEL channel, uint32 val);
void TIMER_SetMatchMode(TIMERCHANNEL channel, uint8 matchChl, uint8 matchMode);
void TIMER_SetMatchVal(TIMERCHANNEL channel, uint8 matchChl, uint32 val);
void TIMER_SetCompareMode(TIMERCHANNEL channel, uint8 capChl, uint8 capMode);
uint32 TIMER_GetCaptureValue(TIMERCHANNEL channel, uint8 capChl);
BOOL TIMER_IsMatchConnected(TIMERCHANNEL channel, uint8 matchChl);
MATCHMODE TIMER_GetMatchMode(TIMERCHANNEL channel, uint8 matchChl);







#endif

