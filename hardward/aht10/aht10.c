#include "aht10.h"

u8 aht10_readdata(uint32_t *data)
{
  u8 hdata[6];
  u32 res = 0;
  aht10_startMeasure();
  delay_ms(80);
  u8 i = 0;
  while ((aht10_startMeasure() & 0x80) == 0x80)
  {
    delay_ms(1);
    i++;
    if (i > 100)
    {
      break;
    }
  }
  I2C_ReadOnlyBytes(AHT10_ADDR, hdata, 6);
  res = (res | hdata[1]) << 8;
  res = (res | hdata[2]) << 8;
  res = (res | hdata[3]);
  res = res >> 4;
  data[0] = res * 1000 / 1024 / 1024;
  res = 0;
  res = (res | hdata[3]) << 8;
  res = (res | hdata[4]) << 8;
  res = (res | hdata[5]);
  res = res & 0xfffff;
  data[1] = res * 2000 / 1024 / 1024 - 500;
  return 0;
}

// 读取状态
u8 aht10_readStatus()
{
  u8 data;
  I2C_ReadOnlyBytes(AHT10_ADDR, &data, 1);
  return data;
}

// 开始测量
u8 aht10_startMeasure()
{
  u8 pdata[] = {0xac, 0x33, 0x00};
  return I2C_WriteBytes(AHT10_ADDR, pdata, 3);
}

// 器件初始化
u8 aht10_init()
{
  u8 pdata[] = {0xe1, 0x08, 0x00};
  return I2C_WriteBytes(AHT10_ADDR, pdata, 3);
}
