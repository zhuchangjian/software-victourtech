#ifndef _LED_H_
  #define _LED_H_

#include "SystemDef.h"
#include "lib_gpio_lpc213x.h"

extern PINNum LED[6];


BOOL LED_Init(void);

BOOL LED_Set(PINNum led);
BOOL LED_Clear(PINNum led);






#endif

