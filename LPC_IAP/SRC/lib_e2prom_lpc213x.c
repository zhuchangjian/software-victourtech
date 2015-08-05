/*****************************************************************
**  Copyright (C), 2013-2014, ZCJ.
**  FileName: Flash.c
**  Author: 
**  Version: V1.0.0 +
**  Date: 2014-5-20
**  Description: flash读写程序
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_e2prom_lpc213x.h"
/*
 *  定义函数指针  
 */
void (*IAP_Entry) (unsigned long ulParam_tab[], unsigned long ulPesult_tab[]) = (void(*)())IAP_ENTER_ADR;

unsigned long   GulParamin[8];                                           /* IAP入口参数缓冲区 */
unsigned long   GulParamout[8];

/*  IAP出口参数缓冲区 */
/*********************************************************************************************************
** Function name:       sectorPrepare
** Descriptions:        IAP操作扇区选择，命令代码50
** input parameters:    ucSec1:           起始扇区
**                      ucSec2:           终止扇区
** output parameters:   GulParamout[0]:   IAP操作状态码,IAP返回值
** Returned value:      GulParamout[0]:   IAP操作状态码,IAP返回值
*********************************************************************************************************/
unsigned long  sectorPrepare (unsigned char  ucSec1, unsigned char  ucSec2)
{  
    GulParamin[0] = IAP_Prepare;                                        /* 设置命令字 */
    GulParamin[1] = ucSec1;                                             /* 设置参数 */
    GulParamin[2] = ucSec2;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* 调用IAP服务程序 */
   
    return (GulParamout[0]);                                            /* 返回状态码 */
}

/*********************************************************************************************************
** Function name:       ramCopy
** Descriptions:        复制RAM的数据到FLASH，命令代码51
** input parameters:    ulDst:             目标地址，即FLASH起始地址。以512字节为分界
**                      ulSrc:             源地址，即RAM地址。地址必须字对齐
**                      ulNo:              复制字节个数，为512/1024/4096/8192
** output parameters:   GulParamout[0]:    IAP操作状态码,IAP返回值
** Returned value:      GulParamout[0]:    IAP操作状态码,IAP返回值
*********************************************************************************************************/
unsigned long  ramCopy (unsigned long  ulDst, unsigned long  ulSrc, unsigned long  ulNo)
{  
    GulParamin[0] = IAP_RAMTOFLASH;                                     /* 设置命令字 */
    GulParamin[1] = ulDst;                                              /* 设置参数 */
    GulParamin[2] = ulSrc;
    GulParamin[3] = ulNo;
    GulParamin[4] = IAP_FCCLK;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* 调用IAP服务程序 */
    
    return (GulParamout[0]);                                            /* 返回状态码 */
}

/*********************************************************************************************************
** Function name:       sectorErase
** Descriptions:        扇区擦除，命令代码52
** input parameters:    ucSec1             起始扇区
**                      ucSec2             终止扇区92
** output parameters:   GulParamout[0]:    IAP操作状态码,IAP返回值
** Returned value:      GulParamout[0]:    IAP操作状态码,IAP返回值
*********************************************************************************************************/
unsigned long  sectorErase (unsigned char ucSec1, unsigned char  ucSec2)
{  
    GulParamin[0] = IAP_ERASESECTOR;                                    /* 设置命令字 */
    GulParamin[1] = ucSec1;                                             /* 设置参数 */
    GulParamin[2] = ucSec2;
    GulParamin[3] = IAP_FCCLK;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* 调用IAP服务程序 */

    return (GulParamout[0]);                                            /* 返回状态码 */
}

/*********************************************************************************************************
** Function name:       blankChk
** Descriptions:        扇区查空，命令代码53
** input parameters:    ucSec1:              起始扇区
**                      ucSec2:              终止扇区92
** output parameters:   GulParamout[0]:    IAP操作状态码,IAP返回值
** Returned value:      GulParamout[0]:    IAP操作状态码,IAP返回值
*********************************************************************************************************/
unsigned long  blankChk (unsigned char  ucSec1, unsigned char  ucSec2)
{  
    GulParamin[0] = IAP_BLANKCHK;                                       /* 设置命令字 */
    GulParamin[1] = ucSec1;                                             /* 设置参数 */
    GulParamin[2] = ucSec2;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* 调用IAP服务程序 */

    return (GulParamout[0]);                                            /* 返回状态码 */
}

/*********************************************************************************************************
** Function name:       parIdRead
** Descriptions:        读器件标识号，命令代码54
** input parameters:    无
** output parameters:   GulParamout[0]:    IAP操作状态码,IAP返回值
** Returned value:      GulParamout[0]:    IAP操作状态码,IAP返回值
*********************************************************************************************************/
unsigned long  parIdRead (void)
{
    GulParamin[0] = IAP_READPARTID;                                     /* 设置命令字 */
    (*IAP_Entry)(GulParamin, GulParamout);                              /* 调用IAP服务程序 */

    return (GulParamout[0]);                                            /* 返回状态码 */
}

/*********************************************************************************************************
** Function name:       codeIdBoot
** Descriptions:        读Boot代码版本号，命令代码55
** input parameters:    无
** output parameters:   GulParamout[0]:    IAP操作状态码,IAP返回值
** Returned value:      GulParamout[0]:    IAP操作状态码,IAP返回值
*********************************************************************************************************/
unsigned long  codeIdBoot (void)
{
    GulParamin[0] = IAP_BOOTCODEID;                                     /* 设置命令字 */
    (*IAP_Entry)(GulParamin, GulParamout);                              /* 调用IAP服务程序 */

    return (GulParamout[0]);                                            /* 返回状态码 */
}

/*********************************************************************************************************
** Function name:       dataCompare
** Descriptions:        校验数据，命令代码56
** input parameters:    ulDst:             目标地址，即RAM/FLASH起始地址。地址必须字对齐
**                      ulSrc:             源地址，即FLASH/RAM地址。地址必须字对齐
**                      ulNo:              待比较的字节数。计数值应当为4的倍数字
** output parameters:   GulParamout[0]:    IAP操作状态码,IAP返回值
** Returned value:      GulParamout[0]:    IAP操作状态码,IAP返回值
*********************************************************************************************************/
unsigned long  dataCompare (unsigned long  ulDst, unsigned long  ulSrc, unsigned long  ulNo)
{  
    GulParamin[0] = IAP_COMPARE;                                        /* 设置命令字 */
    GulParamin[1] = ulDst;                                              /* 设置参数 */
    GulParamin[2] = ulSrc;
    GulParamin[3] = ulNo;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* 调用IAP服务程序 */

    return (GulParamout[0]);                                            /* 返回状态码 */
}

/********************************************************************************************************
** 用户接口层
********************************************************************************************************/
/*********************************************************************************************************
** Function name:       eepromWrite
** Descriptions:        调用该函数可以模拟写EEPROM操作，最大写数据256字节
** input parameters:    bank:从EEPROM空间开始的存储器bank编号,一个bank 256字节
**                      src_addr:存储数据的源地址
** output parameters:   状态信息
** Returned value:      无
**                      一次写入的数据为256字节
注意：调用该函数将会使定义为EEPROM的Flash全部擦除，即会使前面写的所有数据丢失
*********************************************************************************************************/
uint8 eepromWrite(uint32 WriteAddr, uint8 *pBuffer, IAPWRITEMODE mode)
{
    uint8 ucErr = 0;
	
	__disable_irq();

    if (WriteAddr >  64 * 1024)
    { 
		__enable_irq();
        return PARA_BANK_ERROR;
    }  
    
    if ((((unsigned long)pBuffer) % 4) != 0 ) 
    {
		__enable_irq();
       return PARA_SRCADDR_ERROR;  
    }
	
	ucErr = sectorPrepare(EEPROM_STARTSEC, EEPROM_ENDSEC);
	ucErr = ramCopy(WriteAddr, (unsigned long)pBuffer, mode);
	ucErr = dataCompare(WriteAddr, (unsigned long)pBuffer, mode);		
	  
	if (ucErr != CMD_SUCCESS) 
	{                       /*  IAP函数调用出错 */
		__enable_irq();  
		return IAP_ERROR;
    }
	
	__enable_irq();
    return EE_SUUCEESS;
}
/*********************************************************************************************************
** Function name:       eepromWrite
** Descriptions:        调用该函数可以模拟写EEPROM操作，最大写数据256字节
** input parameters:    bank:从EEPROM空间开始的存储器bank编号,一个bank 256字节
**                      src_addr:存储数据的源地址
** output parameters:   状态信息
** Returned value:      无
**                      一次写入的数据为256字节
注意：调用该函数将会使定义为EEPROM的Flash全部擦除，即会使前面写的所有数据丢失
*********************************************************************************************************/
uint8 eepromErase(IAPCHANNEL StartSec, IAPCHANNEL EndSec)
{
    uint8 ucErr = 0;
	
	__disable_irq();
 
	ucErr = sectorPrepare(StartSec, EndSec);
	ucErr = sectorErase(StartSec, EndSec);
	ucErr = blankChk(StartSec, EndSec);
	  
	if(ucErr != CMD_SUCCESS)
	{                       /*  IAP函数调用出错 */
		__enable_irq();  
		return IAP_ERROR;
    }
	
	__enable_irq();
    return EE_SUUCEESS;
}
/*********************************************************************************************************
** Function name:       eepromRead
** Descriptions:        调用该函数可以读从EEPROM_STARTSEC(EEPROM起始扇区开始的数据)
** input parameters:    src_addr:当做EEPROM存储空间的偏移量地址
**                      dst_addr:接收读取数据的源地址
**                      num:读取的字节数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
/*void eepromRead(uint32 src_addr, uint8 *dst_addr, uint32 num)
{
    uint32 i;
  
    for (i = 0; num != 0; num--, i++) 
    {    
        *(dst_addr + i) = *(((uint8 * )(EEPROM_STARTSEC * 1024 * 4 + src_addr)) + i);
    }
}*/
void eepromRead(uint32 ReadAddr, uint8 *pBuffer, uint16 NumToRead)
{
    uint16 i;
  
    for (i = 0; i < NumToRead; i++)
    {    
        pBuffer[i] = *(uint8 * )ReadAddr;
        ReadAddr += 1;
    }
}

