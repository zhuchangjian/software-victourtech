#ifndef _SYSTEMDEF_H_
  #define _SYSTEMDEF_H_


#define MCUTYPE 32


#if MDUTYPE == 8

#elif MCUTYPE == 16

#elif MCUTYPE == 32
/*****************************************
	int define
******************************************/
typedef unsigned char uint8; 
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long long uint64;
typedef signed long long int64;

/*****************************************
	float define 
******************************************/



/*****************************************
	pointer define 
******************************************/
typedef	unsigned char* puint8;
typedef signed char* pint8;
typedef unsigned short* puint16;
typedef signed short* pint16;
typedef unsigned int* puint32;
typedef signed int* pint32;
typedef unsigned long* puint64;
typedef signed long* pint64;

#else

#endif


/********************************************
* inline定义
*********************************************/
#ifndef inline
#define inline inline
#endif

/********************************************
*  输入输出标记
*********************************************/
#define __in
#define __out
#define __inout


//取数组长度宏
#define GET_ARRAYLEN(x) (sizeof(x)/sizeof(x[0]))

#ifndef NULL
  #define NULL ((void *)0)
#endif


//布尔量
typedef enum 
{
	FALSE = 0, TRUE = !FALSE,
}BOOL;


typedef enum
{
	DISABLE = 0, ENABLE = !DISABLE,
}FunctionStatus;

typedef enum
{
	RESET = 0, SET = !RESET,
}FlagStatus;

typedef enum
{
	ERROR = 0, SUCCESS = !ERROR,
}ErrorStatus;

typedef enum
{
    WRITE = 0, READ,
}OptionStatus;















#endif

