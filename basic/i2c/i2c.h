#ifndef __I2C_H
#define __I2C_H
#include <stdint.h>
#include <stdio.h>
#include "sys.h"

/* I2C1 的端口 */
#define I2C1PORT GPIOB
#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7

/* I2C1 DMA 相关 */
#define I2C1_DR_ADDR ((uint32_t)0x40005410)
#define I2C1_DMA_CLK RCC_AHBPeriph_DMA1
#define I2C1_DMA_TX_CHANNEL DMA1_Channel6
#define I2C1_DMA_RX_CHANNEL DMA1_Channel7
#define I2C1_DMA_TX_TCFLAG DMA1_FLAG_TC6
#define I2C1_DMA_RX_TCFLAG DMA1_FLAG_TC7

// 定义传输方向
typedef enum
{
  I2C1_DMA_TX = 0,
  I2C1_DMA_RX = 1
} DMADIR_TypeDef;

#define FLAG_TIMEOUT ((uint32_t)0x1000)
#define LONG_TIMEOUT ((uint32_t)(10 * FLAG_TIMEOUT))

/* 定义主地址和传输速度  */
#define I2C_HOST_ADDR 0xc0
#define BUS_SPEED 400000

void I2C_Configuration(void);

u8 I2C_TIMOUT_UserCallback(u8 errcode);

// 写数据
u8 I2C_WriteOneByte(u8 SlaveAddr, u8 data);
u8 I2C_WriteByte(u8 SlaveAddr, u8 WriteAddr, u8 data);
u8 I2C_WriteBytes(u8 SlaveAddr, u8 *pData, u8 length);

// 读数据
u8 I2C_ReadByte(u8 SlaveAddr, u8 readAddr);
u8 I2C_ReadBytes(u8 SlaveAddr, u8 readAddr, u8 *buffer, u8 length);
u8 I2C_ReadOnlyBytes(u8 Slave_Addr, u8 *buffer, u8 length);

// DMA 通道配置
static void I2C_DMA_Config(DMADIR_TypeDef Direction, u8 *buffer, u8 NumData);

#endif
