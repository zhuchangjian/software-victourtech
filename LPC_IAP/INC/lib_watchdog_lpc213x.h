#ifndef _LIB_WATCHDOG_LPC213X_H_
  #define _LIB_WATCHDOG_LPC213X_H_


#include "SystemDef.h"
#include "lib_def_lpc213x.h"

//WDMode
typedef enum
{
    MODE_0 = 0,
    MODE_1 = 1,
	MODE_2 = 3,
}WDMODE;


void WD_Feed(void);

void WD_SetCount(uint32 count);

void WD_ModeSet(WDMODE mode);

void WD_ClearFlag(void);

uint8 WD_GetFlag(__in uint8 bit);

uint32 WD_GetCount(void);
#endif

