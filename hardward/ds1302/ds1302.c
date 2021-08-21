#include "ds1302.h"

void DS1302_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //开启GPIOB外设时钟
	GPIO_InitStructure.GPIO_Pin = DS1302_RST | DS1302_CLK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

void DS1302_write_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = DS1302_DATA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
  GPIO_WriteBit(DS1302_PORT, DS1302_RST, (BitAction)1);
}

void DS1302_read_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DS1302_DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
  GPIO_WriteBit(DS1302_PORT, DS1302_RST, (BitAction)1);
}

// 向ds1302 写一个字节数据
void ds1302_write_byte(u8 addr, u8 d)
{
	u8 i,m =d/10;
	// BCD 码转换
	d = (m<<4) + d%10;
	DS1302_write_init();
	
	for (i = 0; i <8; i++)
	{
		GPIO_WriteBit(DS1302_PORT, DS1302_DATA, (BitAction)(addr & 0x01));
		GPIO_SetBits(DS1302_PORT,DS1302_CLK);
		GPIO_ResetBits(DS1302_PORT,DS1302_CLK);
		addr>>= 1;
	}
	
	for (i = 0; i <8; i++)
	{
		GPIO_WriteBit(DS1302_PORT, DS1302_DATA, (BitAction)(d & 0x01));
		GPIO_SetBits(DS1302_PORT,DS1302_CLK);
		GPIO_ResetBits(DS1302_PORT,DS1302_CLK);
		d>>= 1;
	}
	GPIO_WriteBit(DS1302_PORT, DS1302_RST, (BitAction)0);
}

u8 ds1302_read_byte(u8 addr)
{
	 uint8_t i,temp,k;
	 DS1302_write_init();
	 addr+=1;
	 for(i = 0; i< 8;i++) {
	 	GPIO_WriteBit(DS1302_PORT, DS1302_DATA, (BitAction)(addr & 0x01));	
		GPIO_SetBits(DS1302_PORT,DS1302_CLK);
		GPIO_ResetBits(DS1302_PORT,DS1302_CLK);
		addr >>= 1;
	 }
	 DS1302_read_init();

	 temp = 0;
	 k = 1;
	 for (i = 0; i < 8; i ++) {
		if (GPIO_ReadInputDataBit(DS1302_PORT, DS1302_DATA)) {
		// BCD 码转换
			if(i < 4) {
			  temp += k;
			} else {
			  temp += (k>>4)*10;
			}
		}
		k<<=1;
		GPIO_SetBits(DS1302_PORT,DS1302_CLK);
		GPIO_ResetBits(DS1302_PORT,DS1302_CLK);
	 }
	 GPIO_WriteBit(DS1302_PORT, DS1302_RST, (BitAction)0);
	 return temp;
}

void DS1302_write_time(uint8_t time_buf[])
{
		ds1302_write_byte(ds1302_control_add,0x00); //关闭写保护
		ds1302_write_byte(ds1302_sec_add,0x80); //暂停时钟
		//ds1302_write_byte(ds1302_charger_add,0xa9); //涓流充电
	
		ds1302_write_byte(ds1302_year_add,time_buf[0]); //年
		ds1302_write_byte(ds1302_month_add,time_buf[1]); //月
		ds1302_write_byte(ds1302_date_add,time_buf[2]); //日
		ds1302_write_byte(ds1302_hr_add,time_buf[3]); //时
		ds1302_write_byte(ds1302_min_add,time_buf[4]); //分
		ds1302_write_byte(ds1302_sec_add,time_buf[5]); //秒
		ds1302_write_byte(ds1302_day_add,time_buf[6]); //周
		ds1302_write_byte(ds1302_control_add,0x80); //打开写保护

}

void DS1302_read_time(uint8_t p[])
{
    *p = ds1302_read_byte(ds1302_year_add); //年
  *(p+1) = ds1302_read_byte(ds1302_month_add); //月
	*(p+2) = ds1302_read_byte(ds1302_date_add); //日
	*(p+3) = ds1302_read_byte(ds1302_hr_add); //时
	*(p+4) = ds1302_read_byte(ds1302_min_add); //分
	*(p+5) = ds1302_read_byte(ds1302_sec_add);//秒
	*(p+6) = ds1302_read_byte(ds1302_day_add); //周
}
