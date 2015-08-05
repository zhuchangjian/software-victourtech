/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_gpio_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x GPIO模块驱动
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_gpio_lpc213x.h"
#include "lib_scb_lpc213x.h"
#include "lib_map_lpc213x.h"

/******************************************************/


typedef struct 
{
	volatile uint32 PINSEL0;
	volatile uint32 PINSEL1;
	volatile uint32 Reserved[3];
	volatile uint32 PINSEL2;
}PINCONNECT_TypeDef;

typedef struct
{
	volatile uint32 IO0PIN;
	volatile uint32 IO0SET;
	volatile uint32 IO0DIR;
	volatile uint32 IO0CLR;
	volatile uint32 IO1PIN;
	volatile uint32 IO1SET;
	volatile uint32 IO1DIR;
	volatile uint32 IO1CLR;
}GPIOA_Typedef;


typedef struct
{
	volatile uint32 FIO0DIR;
	uint32 Reserved1[3];
	volatile uint32 FIO0MASK;
	volatile uint32 FIO0PIN;
	volatile uint32 FIO0SET;
	volatile uint32 FIO0CLR;
	volatile uint32 FIO1DIR;
	uint32 Reserved2[3];
	volatile uint32 FIO1MASK;
	volatile uint32 FIO1PIN;
	volatile uint32 FIO1SET;
	volatile uint32 FIO1CLR;
}GPIOF_Typedef;


/* CRC结构体地址初始化 */
PINCONNECT_TypeDef *PINCONNECT = (PINCONNECT_TypeDef *)PINCONNECT_BASE;
GPIOA_Typedef *GPIOA = (GPIOA_Typedef *)GPIOA_BASE;
GPIOF_Typedef *GPIOF = (GPIOF_Typedef *)GPIOF_BASE;

//PINSEL寄存器
#define PINSEL_MASK  ((uint32)0x00000003)


/************************************************************************
Function: BOOL GPIO_SetFunction(GPIODef fuc)
Description:  设置GPIO引脚功能
Input:  fuc:引脚设置
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL GPIO_SetFunction(__in PGPIODef pFuc)
{
	switch(pFuc->port)
	{
	case PORT_0:
		if((pFuc->num) > NUM15)
		{
			PINCONNECT->PINSEL1 &= ~(PINSEL_MASK << ((pFuc->num - 16) * 2));
			PINCONNECT->PINSEL1 |= ((pFuc->fuc) << ((pFuc->num - 16) * 2));
		}
		else
		{
			PINCONNECT->PINSEL0 &= ~(PINSEL_MASK << (pFuc->num * 2));
			PINCONNECT->PINSEL0 |= ((pFuc->fuc) << (pFuc->num * 2));
		}
		
		if(SCB_GetPortMode(SCB_SCS_GPIO0) == SCB_SCS_GPIO0)  
		{
			//高速GPIO
			if(pFuc->dir == DIR_IN)
			{
				GPIOF->FIO0DIR &= ~(1 << pFuc->num);
			}
			else
			{
				GPIOF->FIO0DIR |= (1 << pFuc->num);
			}
			
		}
		else
		{
			//低速GPIO
			if(pFuc->dir == DIR_IN)
			{
				GPIOA->IO0DIR &= ~(1 << pFuc->num);
			}
			else
			{
				GPIOA->IO0DIR |= (1 << pFuc->num);
			}
		}
		break;
	case PORT_1:
        if((pFuc->num) < NUM26)  //为TRACE引脚
        {
            PINCONNECT->PINSEL2 &= ~(1 << 3);
            PINCONNECT->PINSEL2 |= ((pFuc->fuc) << 3);
        }
        else if((pFuc->num) > NUM25)  //为debug引脚
        {
            PINCONNECT->PINSEL2 &= ~(1 << 2);
            PINCONNECT->PINSEL2 |= ((pFuc->fuc) << 2);
        }
		
		if(SCB_GetPortMode(SCB_SCS_GPIO1) == SCB_SCS_GPIO1)  
		{
			//高速GPIO
			if(pFuc->dir == DIR_IN)
			{
				GPIOF->FIO1DIR &= ~(1 << pFuc->num);
			}
			else
			{
				GPIOF->FIO1DIR |= (1 << pFuc->num);
			}
			
		}
		else
		{
			//低速GPIO
			if(pFuc->dir == DIR_IN)
			{
				GPIOA->IO1DIR &= ~(1 << pFuc->num);
			}
			else
			{
				GPIOA->IO1DIR |= (1 << pFuc->num);
			}
		}
		break;
	default:
		return FALSE;
		break;
	}
	

	return TRUE;
}


/************************************************************************
Function: BOOL GPIO_GetFunction(__inout PGPIODef pFuc)
Description:  取得引脚功能
Input:  pFuc：引脚功能
Output: none
Return: TRUE：取得成功
		FALSE：取得失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL GPIO_GetFunction(__inout PGPIODef pFuc)
{
	switch(pFuc->num)
	{
	case PORT_0:
		if((pFuc->num) > NUM15)
		{
			pFuc->fuc = (PINFuc)(((PINCONNECT->PINSEL1) >> ((pFuc->num - 16) * 2)) & PINSEL_MASK);
		}
		else
		{
			pFuc->fuc = (PINFuc)(((PINCONNECT->PINSEL0) >> (pFuc->num * 2)) & PINSEL_MASK);
		}
		
		if(SCB_GetPortMode(SCB_SCS_GPIO0) == SCB_SCS_GPIO0)  
		{
			//高速GPIO
			pFuc->dir = (PINDir)(((GPIOF->FIO0DIR) >> pFuc->num) & 0x01);
		}
		else
		{
			//低速GPIO
			pFuc->dir = (PINDir)(((GPIOA->IO0DIR) >> pFuc->num) & 0x01);
		}
		break;
	case PORT_1:
		pFuc->fuc = (PINFuc)(((PINCONNECT->PINSEL2) >> pFuc->num) & 0x01);
		if(SCB_GetPortMode(SCB_SCS_GPIO1) == SCB_SCS_GPIO1)  
		{
			//高速GPIO
			pFuc->dir = (PINDir)(((GPIOF->FIO1DIR) >> pFuc->num) & 0x01);
		}
		else
		{
			//低速GPIO
			pFuc->dir = (PINDir)(((GPIOA->IO1DIR) >> pFuc->num) & 0x01);
		}
		break;
	default:
		return FALSE;
		break;
	}
	

	return TRUE;
}


/************************************************************************
Function: BOOL GPIO_SetAccess(__in PINPort port, __in PINNum num, __in PINMask mask)
Description:  设置引脚访问权限
Input:  port：端口
        num：引脚号
        mask： MASK     屏蔽引脚访问权限
               UNMASK   使能引脚访问权限
Output: none
Return: TRUE：设置成功
		FALSE：设置失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL GPIO_SetAccess(__in PINPort port, __in PINNum num, __in PINMask mask)
{
	if(port == PORT_0)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO0) == SCB_SCS_GPIO0)  
		{
			//高速GPIO
			if(mask == MASK)
			{
				GPIOF->FIO0MASK |= 1 << num;
			}
			else
			{
				GPIOF->FIO0MASK &= ~(1 << num);
			}
			
			return TRUE;
		}

		return FALSE;
	}
	else if(port == PORT_1)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO1) == SCB_SCS_GPIO1)  
		{
			//高速GPIO
			if(mask == MASK)
			{
				GPIOF->FIO1MASK |= 1 << num;
			}
			else
			{
				GPIOF->FIO1MASK &= ~(1 << num);
			}
			
			return TRUE;
		}

		return FALSE;
	}
	else
		return FALSE;
}


/************************************************************************
Function: PINMask GPIO_GetAccess(__in PINPort port, __in PINNum num)
Description:  取得引脚访问权限
Input:  port：端口号
        num：引脚号
Output: none
Return: MASK  引脚不允许访问
        UNMASK  引脚可以自由访问
Author: 
Version: V1.0
Others: none
*************************************************************************/
PINMask GPIO_GetAccess(__in PINPort port, __in PINNum num)
{
	if(port == PORT_0)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO0) == SCB_SCS_GPIO0)  
		{
			//高速GPIO
			return (PINMask)((GPIOF->FIO0MASK >> num) & 0x01);
		}

		return MASK_ERR;
	}
	else if(port == PORT_1)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO1) == SCB_SCS_GPIO1)  
		{
			//高速GPIO
			return (PINMask)((GPIOF->FIO1MASK >> num) & 0x01);
		}

		return MASK_ERR;
	}
	else
		return MASK_ERR;
}


/************************************************************************
Function: uint8 GPIO_GetVal(__in PINPort port, __in PINNum num)
Description:  取得引脚电平
Input:  port：端口号
        num：引脚号
Output: none
Return: 0 低电平
        1 高电平
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 GPIO_GetVal(__in PINPort port, __in PINNum num)
{
	if(port == PORT_0)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO0) == SCB_SCS_GPIO0)  
		{
			//高速GPIO
			if(GPIO_GetAccess(port, num) == MASK)  //屏蔽访问
				return (uint8)-1;
			
			return (uint8)((GPIOF->FIO0PIN >> num) & 0x01);
		}
		else
		{
			//低速IO
			return (uint8)((GPIOA->IO0PIN >> num) & 0x01);
		}
	}
	else if(port == PORT_1)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO1) == SCB_SCS_GPIO1)  
		{
			//高速GPIO
			if(GPIO_GetAccess(port, num) == MASK)  //屏蔽访问
				return (uint8)-1;
			
			return (uint8)((GPIOF->FIO1PIN >> num) & 0x01);
		}
		else
		{
			//低速IO
			return (uint8)((GPIOA->IO1PIN >> num) & 0x01);
		}
	}
	else
		return (uint8)-1;
}

/************************************************************************
Function: BOOL GPIO_GetFunction(__inout PGPIODef pFuc)
Description:  取得引脚功能
Input:  pFuc：引脚功能
Output: none
Return: TRUE：取得成功
		FALSE：取得失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL GPIO_SET(__in PINPort port, __in PINNum num)
{
	if(port == PORT_0)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO0) == SCB_SCS_GPIO0)  
		{
			//高速GPIO
			if(GPIO_GetAccess(port, num) == MASK)  //屏蔽访问
				return FALSE;
			
			GPIOF->FIO0SET |= (1 << num); 
			
			return TRUE;
		}
		else
		{
			//低速IO
			GPIOA->IO0SET |= (1 << num);
			
			return TRUE;
		}
	}
	else if(port == PORT_1)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO1) == SCB_SCS_GPIO1)  
		{
			//高速GPIO
			if(GPIO_GetAccess(port, num) == MASK)  //屏蔽访问
				return FALSE;
			
			GPIOF->FIO1SET |= (1 << num); 
			
			return TRUE;
		}
		else
		{
			//低速IO
			GPIOA->IO1SET |= (1 << num);
			
			return TRUE;
		}
	}
	else
		return FALSE;
}

/************************************************************************
Function: BOOL GPIO_GetFunction(__inout PGPIODef pFuc)
Description:  取得引脚功能
Input:  pFuc：引脚功能
Output: none
Return: TRUE：取得成功
		FALSE：取得失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL GPIO_CLR(__in PINPort port, __in PINNum num)
{
	if(port == PORT_0)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO0) == SCB_SCS_GPIO0)  
		{
			//高速GPIO
			if(GPIO_GetAccess(port, num) == MASK)  //屏蔽访问
				return FALSE;
			
			GPIOF->FIO0CLR |= (1 << num); 
			
			return TRUE;
		}
		else
		{
			//低速IO
			GPIOA->IO0CLR |= (1 << num);
			
			return TRUE;
		}
	}
	else if(port == PORT_1)
	{
		if(SCB_GetPortMode(SCB_SCS_GPIO1) == SCB_SCS_GPIO1)  
		{
			//高速GPIO
			if(GPIO_GetAccess(port, num) == MASK)  //屏蔽访问
				return FALSE;
			
			GPIOF->FIO1CLR |= (1 << num); 
			
			return TRUE;
		}
		else
		{
			//低速IO
			GPIOA->IO1CLR |= (1 << num);
			
			return TRUE;
		}
	}
	else
		return FALSE;
}
