#include "ds1302.h"

void DS1302_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //开启GPIOB外设时钟

  GPIO_InitStructure.GPIO_Pin = DS1302_CE | DS1302_CLK;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

// 开始写数据
void DS1302_write_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = DS1302_DATA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);

  GPIO_SetBits(DS1302_PORT, DS1302_CE);
}

// 开始读数据
void DS1302_read_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = DS1302_DATA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入

  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);

  GPIO_SetBits(DS1302_PORT, DS1302_CE);
}

// 向ds1302 写一个字节数据
void ds1302_write_byte(u8 addr, u8 data)
{
  u8 i, m = data / 10;

  // BCD 码转换
  data = (m << data) + data % 10;

  DS1302_write_init();

  for (i = 0; i < 8; i++)
  {
    GPIO_WriteBit(DS1302_PORT, DS1302_DATA, (BitAction)(addr & 0x01));
    GPIO_SetBits(DS1302_PORT, DS1302_CLK);
    GPIO_ResetBits(DS1302_PORT, DS1302_CLK);
    addr >>= 1;
  }

  for (i = 0; i < 8; i++)
  {
    GPIO_WriteBit(DS1302_PORT, DS1302_DATA, (BitAction)(data & 0x01));
    GPIO_SetBits(DS1302_PORT, DS1302_CLK);
    GPIO_ResetBits(DS1302_PORT, DS1302_CLK);
    data >>= 1;
  }
  GPIO_ResetBits(DS1302_PORT, DS1302_CE);
}

/* 读取一个字节的数据 */
u8 ds1302_read_byte(u8 addr)
{
  uint8_t i, temp, k;
  DS1302_write_init();
  addr += 1;
  for (i = 0; i < 8; i++)
  {
    GPIO_WriteBit(DS1302_PORT, DS1302_DATA, (BitAction)(addr & 0x01));
    GPIO_SetBits(DS1302_PORT, DS1302_CLK);
    GPIO_ResetBits(DS1302_PORT, DS1302_CLK);
    addr >>= 1;
  }

  DS1302_read_init();

  temp = 0;
  k = 1;
  for (i = 0; i < 8; i++)
  {
    if (GPIO_ReadInputDataBit(DS1302_PORT, DS1302_DATA))
    {
      // BCD 码转换
      if (i < 4)
        temp += k;
      else
        temp += (k >> 4) * 10;
    }
    k <<= 1;
    GPIO_SetBits(DS1302_PORT, DS1302_CLK);
    GPIO_ResetBits(DS1302_PORT, DS1302_CLK);
  }
  GPIO_ResetBits(DS1302_PORT, DS1302_CE);
  return temp;
}

/*
 * 使用burst 模式读取数据 
 */
void ds1302_read_burst(u8 addr, uint8_t *time_buf)
{
  DS1302_write_init();

  addr++; // +1 变成读地址
  for (uint8_t i = 0; i < 8; i++)
  {
    GPIO_WriteBit(DS1302_PORT, DS1302_DATA, (BitAction)(addr & 0x01));
    GPIO_SetBits(DS1302_PORT, DS1302_CLK);
    GPIO_ResetBits(DS1302_PORT, DS1302_CLK);
    addr >>= 1;
  }

  DS1302_read_init();

  // 读取8 个 字节
  for (uint8_t i = 0; i < 8; i++)
  {

    uint8_t temp = 0, k = 1, j;
    for (j = 0; j < 8; j++)
    {
      if (GPIO_ReadInputDataBit(DS1302_PORT, DS1302_DATA))
      {
        // BCD 码转换
        if (j < 4)
        {
          temp += k;
        }
        else
        {
          temp += (k >> 4) * 10;
        }
      }
      k <<= 1;
      GPIO_SetBits(DS1302_PORT, DS1302_CLK);
      GPIO_ResetBits(DS1302_PORT, DS1302_CLK);
    }
    *(time_buf + i) = temp;
  }

  GPIO_ResetBits(DS1302_PORT, DS1302_CE);
}

// 写入时间
void DS1302_WriteTime(uint8_t time_buf[])
{
  ds1302_write_byte(DS1302_CONTROL_ADD, 0x00); //关闭写保护

  ds1302_write_byte(DS1302_SEC_ADD, 0x80); //暂停时钟

  //ds1302_write_byte(ds1302_charger_add,0xa9); //涓流充电

  ds1302_write_byte(DS1302_YEAR_ADD, time_buf[0]);  //年
  ds1302_write_byte(DS1302_MONTH_ADD, time_buf[1]); //月
  ds1302_write_byte(DS1302_DATE_ADD, time_buf[2]);  //日
  ds1302_write_byte(DS1302_HR_ADD, time_buf[3]);    //时
  ds1302_write_byte(DS1302_MIN_ADD, time_buf[4]);   //分
  ds1302_write_byte(DS1302_SEC_ADD, time_buf[5]);   //秒
  ds1302_write_byte(DS1302_DAY_ADD, time_buf[6]);   //周

  ds1302_write_byte(DS1302_CONTROL_ADD, 0x80); //打开写保护
}

// 读取时间 顺序： 秒，分，时，日期，月份，星期，年
void DS1302_ReadTime(uint8_t p[])
{
  ds1302_read_burst(DS1302_CLKBURST_ADD, p);
}
