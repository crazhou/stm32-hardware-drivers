#ifndef __DS1302_H__
#define __DS1302_H__ 1
#include "sys.h"

#define DS1302_PORT GPIOA
#define DS1302_RST GPIO_Pin_4
#define DS1302_DATA GPIO_Pin_5
#define DS1302_CLK GPIO_Pin_6

// 写数据地址，读数据 要+1
#define ds1302_sec_add 0x80 //秒数据地址
#define ds1302_min_add 0x82 //分数据地址
#define ds1302_hr_add 0x84 //时数据地址
#define ds1302_date_add 0x86 //日数据地址
#define ds1302_month_add 0x88 //月数据地址
#define ds1302_day_add 0x8a //星期数据地址
#define ds1302_year_add 0x8c //年数据地址
#define ds1302_control_add 0x8e //控制数据地址
#define ds1302_charger_add 0x90
#define ds1302_clkburst_add 0xbe

// 定义函数 
void DS1302_Init(void);
void DS1302_write_time(uint8_t time_buf[]);//向DS1302写入时钟数据
void DS1302_read_time(uint8_t time_buf[]); // 从DS1302读取数据  
#endif
