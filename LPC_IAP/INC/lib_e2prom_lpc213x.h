#ifndef _LIB_E2PROM_LPC213X_H_
  #define _LIB_E2PROM_LPC213X_H_


#include "SystemDef.h"
#include "lib_def_lpc213x.h"

#define IAP_ENTER_ADR   0x7FFFFFF1  // IAP入口地址定义

/*
 *  定义IAP命令字
 */
#define IAP_Prepare             50                                      /*  选择扇区                    */
                                                                        /*  【起始扇区号、结束扇区号】  */
#define IAP_RAMTOFLASH          51                                      /*  拷贝数据 FLASH目标地址      */
                                                                        /*  RAM源地址    【、写入字节数 */
                                                                        /*  系统时钟频率】              */
#define IAP_ERASESECTOR         52                                      /*  擦除扇区    【起始扇区号    */
                                                                        /*  结束扇区号、系统时钟频率】  */
#define IAP_BLANKCHK            53                                      /*  查空扇区    【起始扇区号、  */
                                                                        /*  结束扇区号】                */
#define IAP_READPARTID          54                                      /*  读器件ID    【无】          */
#define IAP_BOOTCODEID          55                                      /*  读Boot版本号【无】          */
#define IAP_COMPARE             56                                      /*  比较命令    【Flash起始地址 */
                                                                        /*  RAM起始地址、需要比较的     */
                                                                        /*  字节数】                    */
/*
 *  定义IAP返回状态字
 */
#define CMD_SUCCESS                                0
#define INVALID_COMMAND                            1
#define SRC_ADDR_ERROR                             2
#define DST_ADDR_ERROR                             3
#define SRC_ADDR_NOT_MAPPED                        4
#define DST_ADDR_NOT_MAPPED                        5
#define COUNT_ERROR                                6
#define INVALID_SECTOR                             7
#define SECTOR_NOT_BLANK                           8
#define SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION    9
#define COMPARE_ERROR                              10
#define BUSY                                       11

/* 
 *  定义CCLK值大小，单位为KHz 
 */
#define IAP_FCCLK            (60000)                                    /* 此频率值必须同主频相同 */

#define EEPROM_STARTSEC            4                                    /* 定义作为EEPROM的Falsh */                                                                    /* 起始扇区和结束扇区 */
#define EEPROM_ENDSEC              8

#define EE_SUUCEESS                0                                    /* EEPROM写操作成功完成 */
#define IAP_ERROR                  1                                    /* 内部IAP函数调用出错 */
#define PARA_BANK_ERROR            2                                    /* 操作的板块错误 */
#define PARA_SRCADDR_ERROR         3                                    /* 写数据时的源地址错误(z字对齐) */
#define PARA_OVERFLOW_ERROR        4                                    /* 写入溢出 */


//IAP写入字节数
typedef enum
{
    MODE0 = 256,
    MODE1 = 512,
	MODE2 = 1024,
    MODE3 = 4096,
}IAPWRITEMODE;

//IAP写入字节数
typedef enum
{
    SECTOR0,
    SECTOR1,
	SECTOR2,
    SECTOR3,
	SECTOR4,
    SECTOR5,
	SECTOR6,
    SECTOR7,
	SECTOR8,
}IAPCHANNEL;
/*********************************************************************************************************
**   注意：调用该函数将会使定义为EEPROM的Flash全部擦除，既会使前面写的所有数据丢失
*********************************************************************************************************/
uint8 eepromWrite(uint32 WriteAddr, uint8 *pBuffer, IAPWRITEMODE mode);
uint8 eepromErase(IAPCHANNEL StartSec, IAPCHANNEL EndSec);
/*********************************************************************************************************
** src_addr表示偏移量
*********************************************************************************************************/
void eepromRead(uint32 ReadAddr, uint8 *pBuffer, uint16 NumToRead);
#endif


