/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x ADC模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_adc_lpc213x.h"
#include "lib_map_lpc213x.h"
#include "lib_def_lpc213x.h"

/******************************************************/

typedef struct 
{
	volatile uint32 AD0CR;
	volatile uint32 AD0GDR;
    volatile uint32 ADGSR;
    volatile uint32 AD0INTEN;
    volatile uint32 AD0DR[8];
    volatile uint32 AD0STAT;
    uint32 Reserved1[45043];
    volatile uint32 AD1CR;
    volatile uint32 AD1GDR;
    uint32 Reserved2;
    volatile uint32 AD1INTEN;
    volatile uint32 AD1DR[8];
    volatile uint32 AD1STAT;
    
}ADC_TypeDef;

/* VIC结构体地址初始化 */
ADC_TypeDef *ADC = (ADC_TypeDef *)ADC_BASE;



/**********************************************
*
***********************************************/
#define ADC_MAX_CLOCK  4500000   //4.5MHz


#define ADCR_PIN_MASK   0xff
#define ADCR_CLK_MASK   (0xff << 8)
#define ADCR_CONVERT_CLK_MASK  (0x07 << 17)
#define ADCR_CONVERT_MODE_MASK  (0x07 << 24)
#define ADCR_CONVERT_EDGE_MASK  (0x01 << 27)

/************************************************************************
Function: void ADC_SelectADCPin(__in ADCCHANNEL channel, __in uint8 pinNum)
Description: 选择ADC输入通道
Input: channel:ADC0:通道0
               ADC1:通道1    
       pinNum:引脚号
Output: none
Return: TRUE:选择成功
        FALSE:选择失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_SelectADCChl(__in ADCCHANNEL channel, __in uint8 chlBit)
{
    if(channel == ADC0)
    {
        ADC->AD0CR |= chlBit;
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR |= chlBit;
    }
    else
        return FALSE;
    
    return TRUE;
}


/************************************************************************
Function: void ADC_ClearADCPin(__in ADCCHANNEL channel, __in uint8 pinNum)
Description: 清除ADC引脚
Input: channel:ADC0:通道0
               ADC1:通道1    
       pinNum:引脚号
Output: none
Return: TRUE:选择成功
        FALSE:选择失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_ClearADCChl(__in ADCCHANNEL channel, __in uint8 chlBit)
{
    if(channel == ADC0)
    {
        ADC->AD0CR &= ~(chlBit);
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR &= ~(chlBit);
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: uint8 ADC_GetADCPin(__in ADCCHANNEL channel)
Description: 取得ADC引脚选择状态 
Input: channel:ADC0:通道0
               ADC1:通道1 
Output: none
Return: 引脚选择状态
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 ADC_GetADCPin(__in ADCCHANNEL channel)
{
    if(channel == ADC0)
    {
        return (ADC->AD0CR & ADCR_PIN_MASK);
    }
    else if(channel == ADC1)
    {
        return (ADC->AD1CR & ADCR_PIN_MASK);
    }
    
    return 0;
}

/************************************************************************
Function: BOOL ADC_SetClock(__in ADCCHANNEL channel, __in uint32 clock)
Description: 设置ADC时钟 
Input: channel:ADC0:通道0
               ADC1:通道1 
       clock:时钟频率
Output: none
Return: TRUE:设置成功
        FALSE:设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_SetClock(__in ADCCHANNEL channel, __in uint32 clock)
{
    uint8 nDivVal = 0;
    
    if(clock > ADC_MAX_CLOCK)
        return FALSE;
    
    if((CPU_PCLK % clock) != 0)
        nDivVal = CPU_PCLK / clock + 1;
    else
        nDivVal = CPU_PCLK / clock;
    
    ADC->AD0CR &= ~(ADCR_CLK_MASK);
    
    if(channel == ADC0)
    {
        ADC->AD0CR |= (nDivVal << 8);
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR |= (nDivVal << 8);
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: uint32 ADC_GetClock(__in ADCCHANNEL channel)
Description: 取得ADC时钟
Input: channel:ADC0:通道0
               ADC1:通道1
Output: none
Return: ADC时钟频率
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 ADC_GetClock(__in ADCCHANNEL channel)
{
    uint8 nDivVal = 0;
    
    if(channel == ADC0)
    {
        nDivVal = ((ADC->AD0CR) >> 8) & 0xff;
    }
    else if(channel == ADC1)
    {
        nDivVal = ((ADC->AD1CR) >> 8) & 0xff;
    }
    else
        return (uint32)-1;
    
    
    
    return (CPU_PCLK / nDivVal);
}
/************************************************************************
Function: BOOL ADC_EnableBurstMode(__in ADCCHANNEL channel)
Description: 使能burst模式，硬件自动每个通道转换 
Input: channel:ADC0:通道0
               ADC1:通道1
Output: none
Return: TRUE:使能成功
        FALSE:使能失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_EnableBurstMode(__in ADCCHANNEL channel)
{
    if(channel == ADC0)
    {
        ADC->AD0CR |= (1 << 16);
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR |= (1 << 16);
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: BOOL ADC_DisableBurstMode(__in ADCCHANNEL channel)
Description: 禁止burst模式
Input: channel:ADC0:通道0
               ADC1:通道1
Output: none
Return: TRUE:禁止成功
        FALSE：禁止失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_DisableBurstMode(__in ADCCHANNEL channel)
{
    if(channel == ADC0)
    {
        ADC->AD0CR &= ~(1 << 16);
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR &= ~(1 << 16);
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: BOOL ADC_SetConvertClock(__in ADCCHANNEL channel, __in uint8 clk)
Description: 设置ADC转换周期
Input: channel:ADC0:通道0
               ADC1:通道1
       clk:转换周期
Output: none
Return: TRUE:设置成功
        FALSE:设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_SetConvertClock(__in ADCCHANNEL channel, __in uint8 clk)
{
    
    if(channel == ADC0)
    {
        ADC->AD0CR &= ~ADCR_CONVERT_CLK_MASK;
        ADC->AD0CR |= clk;
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR &= ~ADCR_CONVERT_CLK_MASK;
        ADC->AD1CR |= clk;
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: BOOL ADC_SetADCPowerStatus(__in ADCCHANNEL channel, POWERSTATUS status)
Description: 设置ADC电源状态 
Input: channel:ADC0:通道0
               ADC1:通道1
       status:Running:正常工作
              PowerDown：掉电模式
Output: none
Return: TRUE：设置成功
        FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_SetADCPowerStatus(__in ADCCHANNEL channel, POWERSTATUS status)
{
    if(channel == ADC0)
    {
        if(status == Running)
        {
            ADC->AD0CR |= (1 << 21);
        }
        else
        {
            ADC->AD0CR &= ~(1 << 21);
        }
    }
    else if(channel == ADC1)
    {
        if(status == Running)
        {
            ADC->AD1CR |= (1 << 21);
        }
        else
        {
            ADC->AD1CR &= ~(1 << 21);
        }
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: POWERSTATUS ADC_GetADCPowerStatus(__in ADCCHANNEL channel)
Description: 取得ADC电源状态 
Input: channel:ADC0:通道0
               ADC1:通道1
Output: none
Return: ADC工作状态
Author: 
Version: V1.0
Others: none
*************************************************************************/
POWERSTATUS ADC_GetADCPowerStatus(__in ADCCHANNEL channel)
{
    if(channel == ADC0)
    {
        if((((ADC->AD0CR) >> 21) & 0x01) == 0x01)
            return Running;
        
        return PowerDown;
    }
    else
    {
        if((((ADC->AD1CR) >> 21) & 0x01) == 0x01)
            return Running;
        
        return PowerDown;
    }
}

/************************************************************************
Function: BOOL ADC_SetConvertMode(__in ADCCHANNEL channel, __in uint8 mode, 
                                  _in uint8 edge)
Description: 
Input: 
Output: none
Return: 
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_SetConvertMode(__in ADCCHANNEL channel, __in uint32 mode, 
                        __in uint32 edge)
{
    if(channel == ADC0)
    {
        ADC->AD0CR &= ~(ADCR_CONVERT_MODE_MASK);
        ADC->AD0CR &= ~(ADCR_CONVERT_EDGE_MASK);

        ADC->AD0CR |= mode;
        ADC->AD0CR |= edge;
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR &= ~(ADCR_CONVERT_MODE_MASK);
        ADC->AD1CR &= ~(ADCR_CONVERT_EDGE_MASK); 
       
        ADC->AD1CR |= mode;
        ADC->AD1CR |= edge;
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: 
Description: 
Input: 
Output: none
Return: 
Author: hy
Version: V1.0
Others: none
*************************************************************************/
uint32 ADC_Soft_GetData_Continue(__in ADCCHANNEL channel, __in uint8 chlNum)
{
    uint8 nTimeCnt = 0;
	  volatile uint32 i = 0;
    if(channel == ADC0)
    {
		ADC->AD0DR[chlNum] &= ~0x80000000;
        ADC->AD0CR &= ~(0xff);
        ADC->AD0CR |= (1 << chlNum);
        ADC->AD0CR |= (1 << 21);  //AD正常工作
        ADC->AD0CR |= (1 << 24); //开始转换
        
        while((ADC->AD0DR[chlNum] & 0x80000000) == 0)  //等待转换完成
        {
            for(i = 0; i < 10; i++);
            nTimeCnt++;
            if(nTimeCnt >= 3)
                break;
        }  
        //ADC->AD0DR[chlNum] |= 0x80000000;
        ADC->AD0CR &= ~(1 << 24); //停止转换
        ADC->AD0CR &= ~(1 << 21);  //AD进入掉电模式
        
        return (((ADC->AD0DR[chlNum]) >> 6) & 0x3ff);
        
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR &= ~(0xff);
        ADC->AD1CR |= (1 << chlNum);
        ADC->AD1CR |= (1 << 21);  //AD正常工作
        ADC->AD1CR |= (1 << 24); //开始转换
        
        while((ADC->AD1DR[chlNum] & (uint32)(1 << chlNum)) == 0)   //等待转换完成
        {
            for(i = 0; i < 500; i++);
            nTimeCnt++;
            if(nTimeCnt >= 3)
                break;
        }  
        //ADC->AD1DR[chlNum] |= 0x80000000;
        ADC->AD1CR &= ~(1 << 24); //停止转换
        ADC->AD1CR &= ~(1 << 21);  //AD进入掉电模式
        
        return (((ADC->AD1DR[chlNum]) >> 6) & 0x3ff);
    }
    else
        return (uint32)-1;
}


/************************************************************************
Function: 
Description: 
Input: 
Output: none
Return: 
Author: hy
Version: V1.0
Others: none
*************************************************************************/
uint32 ADC_Soft_GetData_OneTime(__in ADCCHANNEL channel, __in uint8 chlNum)
{
    if(channel == ADC0)
    {
		ADC->AD0CR &= ~(1 << 24); //停止转换
        ADC->AD0CR &= ~(0xff);
        ADC->AD0CR |= (1 << chlNum);
        ADC->AD0CR &= ~(1 << 16);  //设定为软件触发
        ADC->AD0CR &= ~(0x07 << 17); //设定为11个时钟周期
        ADC->AD0CR &= ~(0x07 << 24);
		ADC->AD0CR |= (1 << 21); //AD正常工作
        ADC->AD0CR |= (1 << 24); //开始转换
        
        while((ADC->AD0DR[chlNum] & (uint32)(1 << 31)) == 0);  //等待转换完成
        ADC->AD0CR &= ~(1 << 24); //停止转换
        ADC->AD0CR &= ~(1 << 21); //AD掉电模式
        
        return (((ADC->AD0DR[chlNum]) >> 6) & 0x3ff);
        
    }
    else if(channel == ADC1)
    {
        ADC->AD1CR &= ~(1 << 24); //停止转换
        ADC->AD1CR &= ~(0xff);
        ADC->AD1CR |= (1 << chlNum);
        ADC->AD1CR &= ~(1 << 16);  //设定为软件触发
        ADC->AD1CR &= ~(0x07 << 17); //设定为11个时钟周期
        ADC->AD1CR &= ~(0x07 << 24);
        ADC->AD1CR |= (1 << 21); //AD正常工作
        ADC->AD1CR |= (1 << 24); //开始转换
        
        while((ADC->AD1DR[chlNum] & (uint32)(1 << chlNum)) == 0);  //等待转换完成
        ADC->AD1CR &= ~(1 << 24); //停止转换
        ADC->AD1CR &= ~(1 << 21); //AD掉电模式
        
        return (((ADC->AD1DR[chlNum]) >> 6) & 0x3ff);
    }
    else
        return (uint32)-1;
}


/************************************************************************
Function: 
Description: 
Input: 
Output: none
Return: 
Author: hy
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_EnableInt(__in ADCCHANNEL channel, __in uint16 chlBit)
{
    if(channel == ADC0)
    {
        ADC->AD0INTEN |= chlBit;
    }
    else if(channel == ADC1)
    {
        ADC->AD1INTEN |= chlBit;
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: 
Description: 
Input: 
Output: none
Return: 
Author: hy
Version: V1.0
Others: none
*************************************************************************/
BOOL ADC_DisableInt(__in ADCCHANNEL channel, __in uint16 chlBit)
{
    if(channel == ADC0)
    {
        ADC->AD0INTEN &= ~(chlBit);
    }
    else if(channel == ADC1)
    {
        ADC->AD1INTEN &= ~(chlBit);
    }
    else
        return FALSE;
    
    return TRUE;
}

/************************************************************************
Function: 
Description: 
Input: 
Output: none
Return: 
Author: hy
Version: V1.0
Others: none
*************************************************************************/
uint8 ADC_GetDoneFlag(__in ADCCHANNEL channel, __in uint8 chlNum)
{
     if(channel == ADC0)
    {
        return (ADC->AD0DR[chlNum] >> 31);
    }
    else if(channel == ADC1)
    {
        return (ADC->AD1DR[chlNum] >> 31);
    }
    else
        return (uint8)-1;
}


