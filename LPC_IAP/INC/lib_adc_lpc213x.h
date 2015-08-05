#ifndef _LIB_ADC_LPC213X_H_
  #define _LIB_ADC_LPC213X_H_


#include "SystemDef.h"
#include "lib_def_lpc213x.h"
//ADC通道
typedef enum
{
    ADC0,
    ADC1,
}ADCCHANNEL;

//ADC输入通道
#define ADC_CHL_BIT0       0x01
#define ADC_CHL_BIT1       0x02
#define ADC_CHL_BIT2       0x04
#define ADC_CHL_BIT3       0x08
#define ADC_CHL_BIT4       0x10
#define ADC_CHL_BIT5       0x20
#define ADC_CHL_BIT6       0x40
#define ADC_CHL_BIT7       0x80
#define ADC_CHL_GLB        0x100
#define ADC_CHL_BIT_ALL    0xFF
#define ADC_CHL_BIT_GLBALL 0x1FF

#define ADC_CHL_NUM0       0x00
#define ADC_CHL_NUM1       0x01
#define ADC_CHL_NUM2       0x02
#define ADC_CHL_NUM3       0x03
#define ADC_CHL_NUM4       0x04
#define ADC_CHL_NUM5       0x05
#define ADC_CHL_NUM6       0x06
#define ADC_CHL_NUM7       0x07


//转换周期 
#define ADC_CLK_CONVERT_4        (0x07 << 17)
#define ADC_CLK_CONVERT_5        (0x06 << 17)
#define ADC_CLK_CONVERT_6        (0x05 << 17)
#define ADC_CLK_CONVERT_7        (0x04 << 17)
#define ADC_CLK_CONVERT_8        (0x03 << 17)
#define ADC_CLK_CONVERT_9        (0x02 << 17)
#define ADC_CLK_CONVERT_10       (0x01 << 17)
#define ADC_CLK_CONVERT_11       (0x00 << 17)


//转换模式
#define ADC_CONVERT_STOP      (0x00 << 24)
#define ADC_CONVERT_NOW       (0x01 << 24)
#define ADC_CONVERT_NUM16     (0x02 << 24)
#define ADC_CONVERT_NUM22     (0x03 << 24)
#define ADC_CONVERT_MAT01     (0x04 << 24)
#define ADC_CONVERT_MAT03     (0x05 << 24)
#define ADC_CONVERT_MAT10     (0x06 << 24)
#define ADC_CONVERT_MAT11     (0x07 << 24)
    
#define ADC_CONVERT_RISE      (0x00 << 27)
#define ADC_CONVERT_FALL      (0x01 << 27)



//接口函数
BOOL ADC_SelectADCChl(__in ADCCHANNEL channel, __in uint8 chlBit);
BOOL ADC_ClearADCChl(__in ADCCHANNEL channel, __in uint8 chlBit);
uint8 ADC_GetADCPin(__in ADCCHANNEL channel);
BOOL ADC_SetClock(__in ADCCHANNEL channel, __in uint32 clock);
uint32 ADC_GetClock(__in ADCCHANNEL channel);
BOOL ADC_EnableBurstMode(__in ADCCHANNEL channel);
BOOL ADC_DisableBurstMode(__in ADCCHANNEL channel);
BOOL ADC_SetConvertClock(__in ADCCHANNEL channel, __in uint8 clk);
BOOL ADC_SetADCPowerStatus(__in ADCCHANNEL channel, POWERSTATUS status);
POWERSTATUS ADC_GetADCPowerStatus(__in ADCCHANNEL channel);
BOOL ADC_SetConvertMode(__in ADCCHANNEL channel, __in uint32 mode, 
                        __in uint32 edge);
uint32 ADC_Soft_GetData_OneTime(__in ADCCHANNEL channel, __in uint8 chlNum);
uint32 ADC_Soft_GetData_Continue(__in ADCCHANNEL channel, __in uint8 chlNum);
BOOL ADC_EnableInt(__in ADCCHANNEL channel, __in uint16 chlBit);
BOOL ADC_DisableInt(__in ADCCHANNEL channel, __in uint16 chlBit);
uint8 ADC_GetDoneFlag(__in ADCCHANNEL channel, __in uint8 chlNum);









#endif

