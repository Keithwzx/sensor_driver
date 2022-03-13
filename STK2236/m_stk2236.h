#ifndef _STK_MOD_H_
#define _STK_MOD_H_
#include "drv_stk2236.h"


uint8_t Stk2236SensorInit(void);
uint8_t Stk2236ReadData(uint16_t *als_value, uint16_t * ir_value);

#endif //_STK_MOD_H_
