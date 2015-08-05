#ifndef _LIB_GPIO_LPC213X_H_
  #define _LIB_GPIO_LPC213X_H_

#include "SystemDef.h"


//端口定义
typedef enum
{
	PORT_0 = 0,
	PORT_1,
}PINPort;

typedef enum
{
	FUC_GPIO = 0,
	FUC_FIRST,
	FUC_SECOND,
	FUC_THIRD,
}PINFuc;

typedef enum
{
	DIR_IN = 0,
	DIR_OUT,
}PINDir;

typedef enum
{
	NUM0 = 0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM10, NUM11, NUM12, NUM13, NUM14, NUM15,
	NUM16, NUM17, NUM18, NUM19, NUM20, NUM21, NUM22, NUM23, NUM24, NUM25, NUM26, NUM27, NUM28, NUM29, NUM30, NUM31,
}PINNum;


typedef enum
{
	MASK,
	UNMASK,
	MASK_ERR,
}PINMask;

typedef struct tagGPIODef
{
	PINPort port;  //端口号
	PINNum num; //引脚号
	PINFuc fuc;  //引脚功能
	PINDir dir;  //引脚方向
}GPIODef, *PGPIODef;



BOOL GPIO_SetFunction(__in PGPIODef pFuc);
BOOL GPIO_GetFunction(__inout PGPIODef pFuc);

BOOL GPIO_SetAccess(__in PINPort port, __in PINNum num, __in PINMask mask);
PINMask GPIO_GetAccess(__in PINPort port, __in PINNum num);

uint8 GPIO_GetVal(__in PINPort port, __in PINNum num);
BOOL GPIO_SET(__in PINPort port, __in PINNum num);
BOOL GPIO_CLR(__in PINPort port, __in PINNum num);










#endif

