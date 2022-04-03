#include "dht20.h"
#include <stdio.h>

// 读取DHT20 数据
u8 dht20_read(u8* buffer, u8 length)
{
	// 1. 检查总线状态
 	__IO uint32_t I2CTimeout = LONG_TIMEOUT;
  while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(1);
  }
	
	// 开始读取
  I2C_GenerateSTART(I2C1, ENABLE);
  I2CTimeout = LONG_TIMEOUT;
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if ((I2CTimeout--) == 0)
      return I2C_TIMOUT_UserCallback(2);
  }

  // 选择要通信的从设置地址，并设置传输方向
  I2C_Send7bitAddress(I2C1, DHT20_ADDR, I2C_Direction_Receiver);
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
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
			 *buffer = I2C_ReceiveData(I2C1);
				buffer++;
				length--;
    }
  }

  I2C_AcknowledgeConfig(I2C1, ENABLE);

  return 0;
}

// 读取温度和温度
u8 dht20_readdata(uint32_t *data)
{
	u8 hdata[6];
	u32 res = 0;
	
	dht20_startMeasure();
	delay_ms(80);
	u8 i = 0;
	while( (dht20_readStatus () & 0x80) == 0x80) {
		delay_ms(1);
		i++;
		if(i > 100) {
			break;
		}
	}
	
	dht20_read(hdata, 6);
	res = (res|hdata[1]) << 8;
	res = (res|hdata[2]) << 8;
	res = (res|hdata[3]);
	res = res >> 4;
	data[0] = res * 1000 / 1024 / 1024;
	res = 0;
	res = (res|hdata[3]) << 8;
	res = (res|hdata[4]) << 8;
	res = (res|hdata[5]);
	res = res & 0xfffff;
	data[1] = res * 2000 / 1024 / 1024 - 500;
	return 0;
}

// 读取状态
u8 dht20_readStatus()
{
	u8 data;
	dht20_read(&data, 1);
	return data;
}


// 开始测量
u8 dht20_startMeasure()
{
	u8 pdata[] = {0xac, 0x33, 0x00};
	return I2C_WriteBytes(DHT20_ADDR, pdata, 3);
}
