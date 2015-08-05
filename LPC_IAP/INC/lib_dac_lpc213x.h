#ifndef _LIB_DAC_LPC213X_H_
#define _LIB_DAC_LPC213X_H_


#include "SystemDef.h"

#define DAC_BIAS_700    1
#define DAC_BIAS_350    2



//½Ó¿Úº¯Êý
void DAC_SetOutputVal(uint16 val);
void DAC_OutputVoltage(uint16 val);
BOOL DAC_SetBIAS(__in uint8 bias);
















#endif

