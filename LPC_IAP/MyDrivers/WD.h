#ifndef _WD_H_
  #define _WD_H_

#include "SystemDef.h"

#define WD_IRQ       (IRQ_CHANNEL2)

void WDInit(uint32 count);
//void ClearUserRom(void);

#endif
