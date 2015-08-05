/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: LEC.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: 外围LED控制
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "LED.h"
#include "lib_gpio_lpc213x.h"


//P1.20-P1.25

/********************************************
* 全局变量
*********************************************/
PINNum LED[6] = {NUM20, NUM21, NUM22, NUM23, NUM24, NUM25};

/************************************************************************
Function: BOOL InitLED(void)
Description:  初始化LED控制
Input:  none
Output: none
Return: TRUE：初始化成功
		FALSE：初始化失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL LED_Init(void)
{
	int i = 0;
	//初始化LED端口
	GPIODef LedGPIO;
	LedGPIO.port = PORT_1;
	LedGPIO.num = LED[0];
	LedGPIO.fuc = FUC_GPIO;
	LedGPIO.dir = DIR_OUT;

	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[1];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[2];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[3];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[4];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[5];
	GPIO_SetFunction(&LedGPIO);
    
    //点亮LED
    /*for(int i = 0; i < 6; i++)
    {
        LED_Set(LED[i]);
        for(volatile int j = 0; j < 200000; j++);
    }*/
        
    
    //关闭LED
    for(i = 0; i < 6; i++)
        LED_Clear(LED[i]);

	return TRUE;
}

/************************************************************************
Function: void SetLED(PINNum led)
Description:  点亮LED
Input:  led:LED编号
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL LED_Set(PINNum led)
{
	return GPIO_SET(PORT_1, led);
}

/************************************************************************
Function: void ClrLED(PINNum led)
Description:  熄灭LED
Input:  led：LED编号
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL LED_Clear(PINNum led)
{
	return GPIO_CLR(PORT_1, led);
}
