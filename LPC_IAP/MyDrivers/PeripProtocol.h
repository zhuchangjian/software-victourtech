#ifndef _PERIPPROTOCOL_H_
  #define _PERIPPROTOCOL_H_

#include "SystemDef.h"
#define PERIPPROTOCOL_IRQ       (IRQ_CHANNEL0)
BOOL PeripProtocol_Init(void);
void DataControl(void);
#endif
