#ifndef __AHT10_H
#define __AHT10_H
#include "sys.h"
#include "i2c.h"
#include "delay.h"

#define AHT10_ADDR 0x70

// 读取状态位
u8 aht10_readStatus(void);

u8 aht10_readdata(uint32_t *ct);

// 开始测量
u8 aht10_startMeasure(void);
u8 aht10_init(void);

#endif
