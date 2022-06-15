#ifndef __MAX7219_H

#define __MAX7219_H
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "sys.h"
#include "delay.h"

/* 引脚定义 */
#define MAX7219PORT GPIOA
#define MAX7219_CLK_PIN GPIO_Pin_2
#define MAX7219_CS_PIN GPIO_Pin_3
#define MAX7219_DATA_PIN GPIO_Pin_4


/*  地址定义 */
#define  DECODE_MODE  0x09   // 选择显示模式
#define  INTENSITY  0x0a   // 控制亮度
#define  SCAN_LIMIT  0x0b   // 扫描限制 
#define  SHUT_DOWN  0x0c   // 进入低功耗
#define  DISPLAY_TEST  0x0f   // 显示测试

/* 模式定义 */
#define NORMAL_MODE      1
#define SHUTDOWN_MODE    0

/* 译码模式定义 */
#define NO_DECODE_ALL   0x00
#define DECODE_D0_ONLY   0x01
#define DECODE_D0D3_ONLY 0x0f
#define DECODE_ALL      0xff

#define Segment_Line_DP (1<<7)

// 初始化数码管显示 
void Max7219_Digital_Init(uint8_t intensity, uint8_t len);
// 数码管显示
void Max7219_digit(uint8_t digit, uint8_t data);

void Max7219_Led_Init(uint8_t intensity, uint8_t len);
void Max7219_display(uint8_t x, char data);


// 设置验译码方式 
int Max7219_decode_mode(uint8_t mode);
// 设置亮度
int Max7219_intensity(uint8_t mode);
// 设置扫描个数 
int Max7219_scan_limit(uint8_t mode);
// 省电模式
int Max7219_shutdown(uint8_t mode);
// 屏幕测试
int Max7219_test(uint8_t mode);


#endif
