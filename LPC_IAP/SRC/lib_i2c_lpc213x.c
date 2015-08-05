/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x I2C模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_def_lpc213x.h"
#include "lib_map_lpc213x.h"
#include "lib_i2c_lpc213x.h"

/**************************************************/
/* VIC结构体地址初始化 */
I2C_TypeDef *I2C = (I2C_TypeDef *)I2C_BASE;

/******************************************************
*  静态变量
*******************************************************/


/************************************************************************
Function: BOOL I2C_Open(__in PI2CINFO info)
Description: 打开I2C端口
Input: info:端口配置
Output: none
Return: TRUE:打开成功
        FALSE:打开失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL I2C_Open(__in PI2CINFO info)
{
    if(info->port == I2C0)
    {
        I2C_SetClock(I2C0, info->speed);
        if(info->mode == I2C_MASTER)
        {
            I2C->I2C0CONCLR = 0x2c;
            I2C->I2C0CONSET = 0x40;
        }
        else if(info->mode == I2C_SLAVE)
        {
            I2C->I2C0ADR = (info->address) & 0xfe;
            I2C->I2C0CONCLR = 0x2c;
            I2C->I2C0CONSET = 0x44;
        }
        else
            return FALSE;
    }
    else if(info->port == I2C1)
    {
        I2C_SetClock(I2C1, info->speed);
        if(info->mode == I2C_MASTER)
        {
            I2C->I2C1CONCLR = 0x2c;
            I2C->I2C1CONSET = 0x40;
        }
        else if(info->mode == I2C_SLAVE)
        {
            I2C->I2C1ADR = (info->address) & 0xfe;
            I2C->I2C1CONCLR = 0x2c;
            I2C->I2C1CONSET = 0x44;
        }
        else
            return FALSE;
    }
    else
        return FALSE;
    
    return TRUE;
}


/************************************************************************
Function: 
Description: 
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void I2C_SetClock(__in I2CPORT port, __in uint32 clock)
{
    uint16 divVal = 0;
    if(clock > 400000)
        clock = 400000;
    
    divVal = CPU_PCLK / clock;
    if(port == I2C0)
	{
		I2C->I2C0SCLH = (divVal + 1) / 2;
		I2C->I2C0SCLL = divVal / 2;
	}   
    else if(port == I2C1)
	{
		I2C->I2C1SCLH = (divVal + 1) / 2;
		I2C->I2C1SCLL = divVal / 2;
	}
}

/************************************************************************
Function: 
Description: 
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/

/************************************************************************
Function: 
Description: 
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
