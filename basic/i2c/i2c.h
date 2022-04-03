#ifndef __I2C_H
#define __I2C_H
#include <stdint.h>
#include <stdio.h>
#include "sys.h"

/* I2C1 �Ķ˿� */
#define I2C1PORT GPIOB
#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7

#define FLAG_TIMEOUT ((uint32_t)0x1000)
#define LONG_TIMEOUT ((uint32_t)(10 * FLAG_TIMEOUT))

/* ��������ַ�ʹ����ٶ�  */
#define I2C_HOST_ADDR 0xc0
#define BUS_SPEED 400000

void I2C_Configuration(void);

u8 I2C_TIMOUT_UserCallback(u8 errcode);

u8 I2C_WriteOneByte(u8 SlaveAddr, u8 data);
u8 I2C_WriteByte(u8 SlaveAddr, u8 WriteAddr, u8 data);
u8 I2C_WriteBytes(u8 SlaveAddr, u8* pData, u8 length);


u8 I2C_ReadByte(u8 SlaveAddr, u8 readAddr);
u8 I2C_ReadBytes(u8 SlaveAddr, u8 readAddr, u8 *buffer, u8 length);

#endif
