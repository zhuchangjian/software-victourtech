#ifndef _LIB_MAM_LPC213X_H_
  #define _LIB_MAM_LPC213X_H_


#include "SystemDef.h"


//MAM control 
#define MAM_CONTROL_DISABLE             (0x00)
#define MAM_CONTROL_PARTIALLY           (0x01)
#define MAM_CONTROL_FULL                (0x02)

#define IS_MAM_CONTROL_PARAM(param)  ((param == MAM_CONTROL_DISABLE) || (param == MAM_CONTROL_PARTIALLY) || \
                                      (param == MAM_CONTROL_FULL))


//MAM fetch
#define MAM_FETCH_1             (0x01)
#define MAM_FETCH_2             (0x02)
#define MAM_FETCH_3             (0x03)
#define MAM_FETCH_4             (0x04)
#define MAM_FETCH_5             (0x05)
#define MAM_FETCH_6             (0x06)
#define MAM_FETCH_7             (0x07)


#define IS_MAM_FETCH_PARAM(param)  ((param == MAM_FETCH_1) || (param == MAM_FETCH_2) || \
                                    (param == MAM_FETCH_3) || (param == MAM_FETCH_4) || \
								    (param == MAM_FETCH_5) || (param == MAM_FETCH_6) || \
									(param == MAM_FETCH_7))







//½Ó¿Úº¯Êý
BOOL MAM_SetMode(uint32 mode);
uint32 MAM_GetMode(void);
BOOL MAM_SetFetchCycle(uint32 cycle);
uint32 MAM_GetFetchCycle(void);








#endif

