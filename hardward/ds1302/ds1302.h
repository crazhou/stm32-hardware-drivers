#ifndef __DS1302_H__
#define __DS1302_H__ 1
#include "sys.h"

/* 接口定义 */
#define DS1302_PORT GPIOA
#define DS1302_CE GPIO_Pin_5
#define DS1302_DATA GPIO_Pin_6
#define DS1302_CLK GPIO_Pin_7

/* 写数据地址，读数据 要+1 */
#define DS1302_SEC_ADD 0x80     //秒数据地址
#define DS1302_MIN_ADD 0x82     //分数据地址
#define DS1302_HR_ADD 0x84      //时数据地址
#define DS1302_DATE_ADD 0x86    //日数据地址
#define DS1302_MONTH_ADD 0x88   //月数据地址
#define DS1302_DAY_ADD 0x8a     //星期数据地址
#define DS1302_YEAR_ADD 0x8c    //年数据地址
#define DS1302_CONTROL_ADD 0x8e //控制数据地址
#define DS1302_CHARGER_ADD 0x90
#define DS1302_CLKBURST_ADD 0xbe // 连续写 BURST 模式

#define DS1302_RAM_FIRST 0xc0
#define DS1302_RAM_LAST 0xfc
#define Ds1302_RAMBURST_ADD 0xfe

/* 初始化函数  */
void DS1302_Init(void);
void DS1302_WriteTime(uint8_t time_buf[]); // 向DS1302写入时钟数据 顺序：年，月份，日期，时，分，秒 星期
void DS1302_ReadTime(uint8_t time_buf[]);  // 从DS1302读取数据  顺序： 秒，分，时，日期，月份，星期，年

void DS1302_WriteRam(uint8_t offset, uint8_t data);
uint8_t DS1302_ReadRam(uint8_t offset);

#endif
