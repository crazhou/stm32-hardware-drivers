#ifndef __I2C_H
#define __I2C_H
#include <stdint.h>
#include <stdio.h>
#include "sys.h"

/* I2C1 的端口 */
#define I2C1PORT GPIOB
#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7

#define FLAG_TIMEOUT ((uint32_t)0x1000)
#define LONG_TIMEOUT ((uint32_t)(10 * FLAG_TIMEOUT))

/* 定义主地址和传输速度  */
#define I2C_HOST_ADDR 0xc0
#define BUS_SPEED 300000

void I2C_Configuration(void);

u8 I2C_WirteByte(u8 SlaveAddr, u8 WriteAddr, u8 data);
u8 I2C_ReadByte(u8 SlaveAddr, u8 readAddr);
u8 I2C_ReadBytes(u8 SlaveAddr, u8 readAddr, u8 *buffer, u8 length);

#endif
