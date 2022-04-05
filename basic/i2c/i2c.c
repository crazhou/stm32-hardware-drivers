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
    ;
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

  I2C_DeInit(I2C1);

  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2C_HOST_ADDR;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_ClockSpeed = BUS_SPEED;

  I2C_Init(I2C1, &I2C_InitStructure);

  I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE);

  I2C_Cmd(I2C1, ENABLE);
}

u8 I2C_WriteOneByte(uint8_t addr, uint8_t data)
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

  I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(3);
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

// 写一个 byte 的数据
u8 I2C_WriteByte(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t data)
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

// 写多个 byte DMA 模式
u8 I2C_WriteBytes(u8 SlaveAddr, u8 *pData, u8 length)
{
  I2CTimeout = LONG_TIMEOUT;
  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(1);
  }

  // 初始化DMA通道
  I2C_DMA_Config(I2C1_DMA_TX, pData, length);

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

  I2C_DMACmd(I2C1, ENABLE);

  DMA_Cmd(I2C1_DMA_TX_CHANNEL, ENABLE);

  // 等待DMA 传输完成
  I2CTimeout = LONG_TIMEOUT;
  while (!DMA_GetFlagStatus(I2C1_DMA_TX_TCFLAG))
  {
    if ((I2CTimeout--) == 0)
    {
      return I2C_TIMOUT_UserCallback(12);
    }
  }

  /* Wait until BTF Flag is set before generating STOP */
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF))
  {
    if ((I2CTimeout--) == 0)
    {
      return I2C_TIMOUT_UserCallback(13);
    }
  }

  I2C_GenerateSTOP(I2C1, ENABLE);

  /* 关闭通道 */
  DMA_Cmd(I2C1_DMA_TX_CHANNEL, DISABLE);

  /* 关闭 I2C DMA 功能 */
  I2C_DMACmd(I2C1, DISABLE);

  /* 清除传输完成态 */
  DMA_ClearFlag(I2C1_DMA_TX_TCFLAG);

  return 0;
}

// 先写后读一个byte
u8 I2C_ReadByte(u8 SlaveAddr, u8 readAddr)
{
  u8 data;

  I2C_ReadBytes(SlaveAddr, readAddr, &data, 1);

  return data;
}

// 先写后读多个byte
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

// 直接多多个byte
u8 I2C_ReadOnlyBytes(u8 Slave_Addr, u8 *buffer, u8 length)
{
  // 1. 检查总线状态
  __IO uint32_t I2CTimeout = LONG_TIMEOUT;
  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(1);
  }

  if (length > 1)
  {
    // 2. 初始化通道
    I2C_DMA_Config(I2C1_DMA_RX, buffer, length);
    I2C_DMALastTransferCmd(I2C1, ENABLE);
  }
  // 3. 发送开始信号
  I2C_GenerateSTART(I2C1, ENABLE);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(2);
  }

  // 发送读取地址
  I2C_Send7bitAddress(I2C1, Slave_Addr, I2C_Direction_Receiver);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(5);
  }

  if (length > 1)
  {
    // 打开I2CDMA 请求
    I2C_DMACmd(I2C1, ENABLE);

    // 打开 DMA RX 通道
    DMA_Cmd(I2C1_DMA_RX_CHANNEL, ENABLE);

    I2CTimeout = LONG_TIMEOUT;
    while (!DMA_GetFlagStatus(I2C1_DMA_RX_TCFLAG))
    {
      if ((I2CTimeout--) == 0)
      {
        return I2C_TIMOUT_UserCallback(11);
      }
    }

    I2C_GenerateSTOP(I2C1, ENABLE);

    DMA_Cmd(I2C1_DMA_RX_CHANNEL, DISABLE);

    I2C_DMACmd(I2C1, DISABLE);

    DMA_ClearFlag(I2C1_DMA_RX_TCFLAG);
  }
  else
  {

    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);

    I2CTimeout = LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      if ((I2CTimeout--) == 0)
        return I2C_TIMOUT_UserCallback(6);
    }
    *buffer = I2C_ReceiveData(I2C1);
    I2C_AcknowledgeConfig(I2C1, ENABLE);
  }
  return 0;
}

static void I2C_DMA_Config(DMADIR_TypeDef Direction, u8 *buffer, u8 NumData)
{
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHBPeriphClockCmd(I2C1_DMA_CLK, ENABLE);

  // 外设与内存地址
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C1_DR_ADDR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)buffer;

  // 外设与内存增量
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

  // 外设与内存字长
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

  // 模式与优先级
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

  // M2M 关闭
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  if (Direction == I2C1_DMA_RX)
  {
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

    DMA_InitStructure.DMA_BufferSize = NumData;

    DMA_DeInit(I2C1_DMA_RX_CHANNEL);

    DMA_Init(I2C1_DMA_RX_CHANNEL, &DMA_InitStructure);
  }
  else if (Direction == I2C1_DMA_TX)
  {

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;

    DMA_InitStructure.DMA_BufferSize = NumData;

    DMA_DeInit(I2C1_DMA_TX_CHANNEL);

    DMA_Init(I2C1_DMA_TX_CHANNEL, &DMA_InitStructure);
  }
}
