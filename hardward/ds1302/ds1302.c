#include "ds1302.h"

void DS1302_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //����GPIOB����ʱ��
	GPIO_InitStructure.GPIO_Pin = DS1302_RST | DS1302_CLK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

void DS1302_write_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = DS1302_DATA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
  GPIO_WriteBit(DS1302_PORT, DS1302_RST, (BitAction)1);
}

void DS1302_read_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DS1302_DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
	GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
  GPIO_WriteBit(DS1302_PORT, DS1302_RST, (BitAction)1);
}

// ��ds1302 дһ���ֽ�����
void ds1302_write_byte(u8 addr, u8 d)
{
	u8 i,m =d/10;
	// BCD ��ת��
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
		// BCD ��ת��
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
		ds1302_write_byte(ds1302_control_add,0x00); //�ر�д����
		ds1302_write_byte(ds1302_sec_add,0x80); //��ͣʱ��
		//ds1302_write_byte(ds1302_charger_add,0xa9); //������
	
		ds1302_write_byte(ds1302_year_add,time_buf[0]); //��
		ds1302_write_byte(ds1302_month_add,time_buf[1]); //��
		ds1302_write_byte(ds1302_date_add,time_buf[2]); //��
		ds1302_write_byte(ds1302_hr_add,time_buf[3]); //ʱ
		ds1302_write_byte(ds1302_min_add,time_buf[4]); //��
		ds1302_write_byte(ds1302_sec_add,time_buf[5]); //��
		ds1302_write_byte(ds1302_day_add,time_buf[6]); //��
		ds1302_write_byte(ds1302_control_add,0x80); //��д����

}

void DS1302_read_time(uint8_t p[])
{
    *p = ds1302_read_byte(ds1302_year_add); //��
  *(p+1) = ds1302_read_byte(ds1302_month_add); //��
	*(p+2) = ds1302_read_byte(ds1302_date_add); //��
	*(p+3) = ds1302_read_byte(ds1302_hr_add); //ʱ
	*(p+4) = ds1302_read_byte(ds1302_min_add); //��
	*(p+5) = ds1302_read_byte(ds1302_sec_add);//��
	*(p+6) = ds1302_read_byte(ds1302_day_add); //��
}
