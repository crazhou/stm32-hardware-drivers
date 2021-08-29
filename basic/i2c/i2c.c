#include "i2c.h"
#include "sys.h"

__IO uint32_t I2CTimeout = LONG_TIMEOUT;

/*
 *  i2c 通信超时回调
 */
u8 I2C_TIMOUT_UserCallback(u8 errcode)
{
  printf("Communication Timeout Error Code: %d!\r\n", errcode);

  while (1)
  {
  }
}

// I2C引脚初始化
void I2C_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // GPIOB 时钟开启
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // 复用开漏
  GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(I2C1PORT, &GPIO_InitStructure);
}

void I2C_Configuration(void)
{
  I2C_InitTypeDef I2C_InitStructure;

  // I2C1 时钟开启
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  I2C_GPIO_Init();

  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2C_HOST_ADDR;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_ClockSpeed = BUS_SPEED;

  I2C_Init(I2C1, &I2C_InitStructure);

  I2C_Cmd(I2C1, ENABLE);
}

// 发送一个byte 的数据
u8 I2C_WirteByte(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t data)
{
  I2CTimeout = LONG_TIMEOUT;
  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(1);
  }

  I2C_GenerateSTART(I2C1, ENABLE);

  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(2);
  }

  I2C_Send7bitAddress(I2C1, SlaveAddr, I2C_Direction_Transmitter);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(3);
  }

  I2C_SendData(I2C1, WriteAddr);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(4);
  }

  I2C_SendData(I2C1, data);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(4);
  }

  I2C_GenerateSTOP(I2C1, ENABLE);

  return 0;
}

u8 I2C_ReadBytes(uint8_t SlaveAddr, uint8_t readAddr, uint8_t *buffer, uint8_t length)
{
  // 1. 检查总线状态
  I2CTimeout = LONG_TIMEOUT;
  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(1);
  }

  // 2. 发送开始信号
  I2C_GenerateSTART(I2C1, ENABLE);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(2);
  }

  // 3. 发送7位的地址，选中要通信的子设备
  I2C_Send7bitAddress(I2C1, SlaveAddr, I2C_Direction_Transmitter);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(3);
  }

  // 4. 发送数据
  I2C_SendData(I2C1, readAddr);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(4);
  }

  I2C_GenerateSTART(I2C1, ENABLE);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(2);
  }

  // 选择要通信的从设置地址，并设置传输方向
  I2C_Send7bitAddress(I2C1, SlaveAddr, I2C_Direction_Receiver);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(5);
  }

  while (length)
  {
    if (length == 1)
    {
      // 将 ack 反馈关闭，并发送停止信号
      I2C_AcknowledgeConfig(I2C1, DISABLE);
      I2C_GenerateSTOP(I2C1, ENABLE);
    }

    I2CTimeout = LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      if ((I2CTimeout--) == 0)
        return I2C_TIMOUT_UserCallback(6);
    }
    *buffer = I2C_ReceiveData(I2C1);
    buffer++;
    length--;
  }

  I2C_AcknowledgeConfig(I2C1, ENABLE);

  return 0;
}

u8 I2C_ReadByte(u8 SlaveAddr, u8 readAddr)
{
  u8 data;

  I2C_ReadBytes(SlaveAddr, readAddr, &data, 1);

  return data;
}
