#ifndef _LIB_I2C_LPC213X_H_
  #define _LIB_I2C_LPC213X_H_


#include "SystemDef.h"


/******************************************************/
typedef struct 
{
	volatile uint32 I2C0CONSET;
    volatile uint32 I2C0STAT;
    volatile uint32 I2C0DAT;
    volatile uint32 I2C0ADR;
    volatile uint32 I2C0SCLH;
    volatile uint32 I2C0SCLL;
    volatile uint32 I2C0CONCLR;
    uint32 Reserved[65535];
    volatile uint32 I2C1CONSET;
    volatile uint32 I2C1STAT;
    volatile uint32 I2C1DAT;
    volatile uint32 I2C1ADR;
    volatile uint32 I2C1SCLH;
    volatile uint32 I2C1SCLL;
    volatile uint32 I2C1CONCLR;
}I2C_TypeDef;

extern I2C_TypeDef *I2C;

/******************************************************/


typedef enum
{
    I2C0,
    I2C1,
}I2CPORT;

typedef enum
{
    I2C_SLAVE,
    I2C_MASTER,
}I2CMODE;

typedef struct 
{
    I2CPORT port;
    I2CMODE mode;
    uint32 address;
    uint32 speed;
}I2CINFO, *PI2CINFO;


//½Ó¿Úº¯Êý
#define I2C_GetStatus()  (I2C->I2C0STAT)
#define I2C_SendData(x) (I2C->I2C0DAT = x)
#define I2C_GetData() (I2C->I2C0DAT)
#define I2C_ACK() (I2C->I2C0CONSET = 0x04)
#define I2C_ClearFlag(x) (I2C->I2C0CONCLR = x)
BOOL I2C_Open(__in PI2CINFO info);
void I2C_SetClock(__in I2CPORT port, __in uint32 clock);















#endif

