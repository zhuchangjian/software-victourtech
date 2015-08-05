#include "PeripProtocol.h"
#include "lib_uart_lpc213x.h"
#include "lib_gpio_lpc213x.h"
#include "lib_vic_lpc213x.h"
#include "lib_e2prom_lpc213x.h"
#include "CRC.h"
#include "LED.h"
/****************************************
* 静态变量
*****************************************/
uint32 WriteAdr = 0x4000;
static BOOL bTransDone = FALSE;
static BOOL FirstTimeWrite = FALSE;

static uint8 PeripRecvData[4200];
static uint16 PeripRecvDataLen = 0;

static uint8 PeripSendData[16];
/****************************************
* 全局变量
*****************************************/
BOOL Header = FALSE;
/****************************************
* 内部函数
*****************************************/
void PeripProtocolISR(void) __irq;
BOOL CompareCRCVal(__in puint8 pData, __in uint16 len);
/************************************************************************
Function: inline void SetModbusSendDir()
Description: 设置modbus为发送状态
Input:  none
Output: none
Return: none
Author:       
Version: V1.0
Others: none
*************************************************************************/
void SetModbusSendDir(void)
{
    GPIO_SET(PORT_0, NUM8);
}

/************************************************************************
Function: inline void SetModbusRecvDir()
Description: 设置modbus为接收状态
Input:  none
Output: none
Return: none
Author:       
Version: V1.0
Others: none
*************************************************************************/
void SetModbusRecvDir(void)
{
    GPIO_CLR(PORT_0, NUM8);
}

void PeripProtocolISR(void) __irq
{
	//判断中断类型
	static uint16 i = 0;
    uint32 intFlag;
	
    intFlag = UART0_GetIntFlag();	
	
    if((intFlag & UART0_INTFLAG_MASK) == UART0_INTFLAG_RDA)  //接收到数据中断
    {
		PeripRecvData[i] = UART0_RecvByte();
				
		if(Header)
		{
			if(i == 2)
			{
				PeripRecvDataLen = PeripRecvData[1];
				PeripRecvDataLen <<= 8;
				PeripRecvDataLen += PeripRecvData[2];
			}
			if(PeripRecvData[i] == 0xff && i == (PeripRecvDataLen - 1))
			{
				bTransDone = TRUE;
				Header = FALSE;
				i = 0;
				LED_Clear(LED[4]);
			}
		}
		else
		{
			if(PeripRecvData[i] == 0xee)
			{
				i = 0;
				PeripRecvData[0] = 0xee;
				Header = TRUE;
			}
		}
		
		i++;
		if(i > 4198)
		{
			i = 0;
		}
    }
    else if((intFlag & UART0_INTFLAG_MASK) == UART0_INTFLAG_CTI)
    {
        //清除标志位
        UART0_RecvByte();
    }
    else  //其他中断
    {
        UART0_GetLineStatus();  //清除中断状态
    }
    
    //清除中断标志位
    VIC_ClearCurVectAddr();
}

BOOL PeripProtocol_Init(void)
{
    //使能串口0引脚
    //串口0用作485通讯 
    GPIODef UART1GPIO = {PORT_0, NUM0, FUC_FIRST, DIR_OUT};
	GPIO_SetFunction(&UART1GPIO);
    UART1GPIO.num = NUM1;
    UART1GPIO.dir = DIR_IN;
	GPIO_SetFunction(&UART1GPIO);
    
    //设置485方向IO
	{
		GPIODef DIRGPIO = {PORT_0, NUM8, FUC_GPIO, DIR_OUT};
		GPIO_SetFunction(&DIRGPIO);
	}

    //设置打开串口0
	{
		COMINFO nComInfo = {BAUD_9600, DATABITS_8, STOPBITS_10, PARITY_ODD, TRIGGER_1};
		UART0_Open(&nComInfo);
	}
 
    //设置串口中断为IRQ
    VIC_IntSelect(VIC_INTBIT_UART0, IRQ);
	//绑定ADC中断为向量中断
    VIC_VectIRQBind(PERIPPROTOCOL_IRQ, VIC_INTNUM_UART0, (uint32)PeripProtocolISR);
    //使能外部中断
    VIC_EnableInt(VIC_INTBIT_UART0);
	
    return TRUE;
}
/************************************************************************
Function: BOOL PeripDetect_Init(void)
Description: 初始化外设检测ADC引脚
Input:  none
Output: none
Return: TRUE：初始化成功
		FALSE：初始化失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
void DataControl(void)
{
	int i = 0;
	uint16 crcVal;
	uint16 command;
	uint16 length;
	static uint16 packageSize;
	
	if(bTransDone)
	{
		if(CompareCRCVal(PeripRecvData, PeripRecvDataLen))
		{
			if(PeripRecvData[3] == 1)
			{
				command = PeripRecvData[4];
				command <<= 8;
				command += PeripRecvData[5];	
				
				if(command == 0x65)
				{
					if(PeripRecvData[7] == 1)
					{
						//复位地址
						WriteAdr = 0x4000;
						//置位扇区擦除标志
						FirstTimeWrite = TRUE;
						
						//返回结果
						PeripSendData[0] = 0xEE;
						PeripSendData[1] = 0x0;
						PeripSendData[2] = 0xC;
						PeripSendData[3] = 0x1;
						PeripSendData[4] = 0x0;
						PeripSendData[5] = 0x64;
						PeripSendData[6] = 0x0;
						PeripSendData[7] = 0x1;	
						PeripSendData[8] = 0x0;							
			
						crcVal = CalCRC16(PeripSendData, 9);
							
						PeripSendData[9] = (uint8)(crcVal >> 8);
						PeripSendData[10] = (uint8)(crcVal & 0xff);
						PeripSendData[11] = 0XFF;
							
						SetModbusSendDir();
						UART0_SendData(PeripSendData, 12);
						SetModbusRecvDir();
						
					}
				}
			}
			else if(PeripRecvData[3] == 2)
			{
				command = PeripRecvData[4];
				command <<= 8;
				command += PeripRecvData[5];
				
				if(command == 0xcb)
				{
					packageSize = PeripRecvData[8];
					packageSize <<= 8;
					packageSize += PeripRecvData[9];
					
					
					//返回结果
					PeripSendData[0] = 0xEE;
					PeripSendData[1] = 0x0;
					PeripSendData[2] = 0xC;
					PeripSendData[3] = 0x2;
					PeripSendData[4] = 0x0;
					PeripSendData[5] = 0xc9;
					PeripSendData[6] = 0x0;	
					PeripSendData[7] = 0x1;
					if(packageSize > 0xC000)
					{
						PeripSendData[8] = 2;
					}
					else
					{
						PeripSendData[8] = 1;
					}
		
					crcVal = CalCRC16(PeripSendData, 9);
						
					PeripSendData[9] = (uint8)(crcVal >> 8);
					PeripSendData[10] = (uint8)(crcVal & 0xff);
					PeripSendData[11] = 0XFF;
					
					SetModbusSendDir();
					UART0_SendData(PeripSendData, 12);
					SetModbusRecvDir();
					
				}
				else if(command == 0xcc)
				{
					length = PeripRecvData[6];
					length <<= 8;
					length += PeripRecvData[7];
					
					//擦除用户ROM
					if(FirstTimeWrite)
					{
						eepromErase(SECTOR4, SECTOR8);
						FirstTimeWrite = FALSE;
					}
					if(length == 4096)
					{
						eepromWrite(WriteAdr, &PeripRecvData[8], MODE3);
						WriteAdr += 4096;
						//提示一次写入完成
						LED_Set(LED[4]);
						//返回结果
						PeripSendData[0] = 0xEE;
						PeripSendData[1] = 0x0;
						PeripSendData[2] = 0xC;
						PeripSendData[3] = 0x2;
						PeripSendData[4] = 0x0;
						PeripSendData[5] = 0xc8;
						PeripSendData[6] = 0x0;
						PeripSendData[7] = 0x1;
						PeripSendData[8] = 0x0;	
								
						crcVal = CalCRC16(PeripSendData, 9);
								
						PeripSendData[9] = (uint8)(crcVal >> 8);
						PeripSendData[10] = (uint8)(crcVal & 0xff);
						PeripSendData[11] = 0XFF;
								
						SetModbusSendDir();
						UART0_SendData(PeripSendData, 12);
						SetModbusRecvDir();
					}
					
				}
				else if(command == 0xca)
				{
					WriteAdr = 0x4000;
					packageSize = 0;
					//写入升级成功标记
					PeripRecvData[0] = 1;
					for(i = 1; i < 256; i++)
					{
						PeripRecvData[i] = 0xff;
					}
					eepromWrite(0xFF00, &PeripRecvData[0], MODE0);
				}
			}
		}
		else
		{
			command = PeripRecvData[4];
			command <<= 8;
			command += PeripRecvData[5];
			
			if(command == 1)
			{
				//返回结果
				PeripSendData[0] = 0xEE;
				PeripSendData[1] = 0x0;
				PeripSendData[2] = 0xC;
				PeripSendData[3] = 0x1;
				PeripSendData[4] = 0x0;
				PeripSendData[5] = 0x64;
				PeripSendData[6] = 0x0;
				PeripSendData[7] = 0x1;
				PeripSendData[8] = 0x1;	
	
				crcVal = CalCRC16(PeripSendData, 9);
					
				PeripSendData[9] = (uint8)(crcVal >> 8);
				PeripSendData[10] = (uint8)(crcVal & 0xff);
				PeripSendData[11] = 0XFF;
					
				SetModbusSendDir();
				UART0_SendData(PeripSendData, 12);
				SetModbusRecvDir();
				
			}
			else if(command == 2)
			{
				//返回结果
				PeripSendData[0] = 0xEE;
				PeripSendData[1] = 0x0;
				PeripSendData[2] = 0xC;
				PeripSendData[3] = 0x2;
				PeripSendData[4] = 0x0;
				PeripSendData[5] = 0xc8;
				PeripSendData[6] = 0x0;
				PeripSendData[7] = 0x1;
				PeripSendData[8] = 0x1;	
	
				crcVal = CalCRC16(PeripSendData, 9);
					
				PeripSendData[9] = (uint8)(crcVal >> 8);
				PeripSendData[10] = (uint8)(crcVal & 0xff);
				PeripSendData[11] = 0XFF;
					
				SetModbusSendDir();
				UART0_SendData(PeripSendData, 12);
				SetModbusRecvDir();
							
			}
		}
		
		if((WriteAdr - 0X4000) > packageSize)
		{
			WriteAdr = 0x4000;
			packageSize = 0;
			//写入升级成功标记
			PeripRecvData[0] = 1;
			for(i = 1; i < 256; i++)
			{
				PeripRecvData[i] = 0xff;
			}
			eepromWrite(0xFF00, &PeripRecvData[0], MODE0);			
		}
		
		bTransDone = FALSE;
	}
}


/************************************************************************
Function: BOOL PeripDetect_Init(void)
Description: 初始化外设检测ADC引脚
Input:  none
Output: none
Return: TRUE：初始化成功
		FALSE：初始化失败
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL CompareCRCVal(__in puint8 pData, __in uint16 len)
{
	uint16 crcVal = 0;
	uint16 recvCrcVal = 0;
	crcVal = CalCRC16(pData, len - 3);
	recvCrcVal = (pData[len - 3] << 8) | (pData[len - 2]);
	if(crcVal == recvCrcVal)
		return TRUE;
	
	return FALSE;
}

