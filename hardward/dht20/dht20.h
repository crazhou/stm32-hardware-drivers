#ifndef __DHT20_H
#define __DHT20_H
#include "sys.h"
#include "i2c.h"
#include "delay.h"

#define DHT20_ADDR 0x70 // …Ë±∏µÿ÷∑

u8 dht20_readStatus(void);
u8 dht20_read(u8* buffer, u8 length);
u8 dht20_readdata(uint32_t *ct);
u8 dht20_init(void);
u8 dht20_startMeasure(void);

#endif
