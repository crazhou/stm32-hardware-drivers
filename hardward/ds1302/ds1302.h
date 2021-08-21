#ifndef __DS1302_H__
#define __DS1302_H__ 1
#include "sys.h"

#define DS1302_PORT GPIOA
#define DS1302_RST GPIO_Pin_4
#define DS1302_DATA GPIO_Pin_5
#define DS1302_CLK GPIO_Pin_6

// д���ݵ�ַ�������� Ҫ+1
#define ds1302_sec_add 0x80 //�����ݵ�ַ
#define ds1302_min_add 0x82 //�����ݵ�ַ
#define ds1302_hr_add 0x84 //ʱ���ݵ�ַ
#define ds1302_date_add 0x86 //�����ݵ�ַ
#define ds1302_month_add 0x88 //�����ݵ�ַ
#define ds1302_day_add 0x8a //�������ݵ�ַ
#define ds1302_year_add 0x8c //�����ݵ�ַ
#define ds1302_control_add 0x8e //�������ݵ�ַ
#define ds1302_charger_add 0x90
#define ds1302_clkburst_add 0xbe

// ���庯�� 
void DS1302_Init(void);
void DS1302_write_time(uint8_t time_buf[]);//��DS1302д��ʱ������
void DS1302_read_time(uint8_t time_buf[]); // ��DS1302��ȡ����  
#endif
