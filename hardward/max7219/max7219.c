#include "max7219.h"
#include "fonts.h"

uint8_t max_len = 1;

const uint8_t t_display[] = {
 // 0 1 2 3 4 5 6 7 8 9 A  B C D E F 无
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00 
};


// 字符串中查找 字符 
int8_t indexOf(char *str, uint8_t ch)
{
	int8_t index = 0;
	
	char tmp = str[index];
	
	while(tmp != '\0') {
		if(tmp == ch) {
			return index;
		}
		index++;
		tmp = str[index];
	}
	
	return -1;
}

/*
 * 初始化 GPIO 端口
 */
void Max7219_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MAX7219_CS_PIN|MAX7219_CLK_PIN|MAX7219_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAX7219PORT, &GPIO_InitStructure);
	// 时钟和数据线拉低
	GPIO_ResetBits(MAX7219PORT,MAX7219_CLK_PIN|MAX7219_DATA_PIN);
	
	GPIO_SetBits(MAX7219PORT,MAX7219_CS_PIN);
}

/*
 * 数码管初始化, 传递一个亮度
 */
void Max7219_Digital_Init(uint8_t intensity, uint8_t len)
{
	Max7219_GPIOInit();
		
	max_len = len;
	
	Max7219_shutdown(NORMAL_MODE);
	Max7219_decode_mode(NO_DECODE_ALL);
	Max7219_intensity(intensity);
  Max7219_scan_limit(0x07);
	// 开始测试
	Max7219_test(0x01);	
	Max7219_test(0x00);

}
/*  
 * 初始化 LED 显示屏  len 为点阵屏个数， intensity 为每个亮度
 */
void Max7219_Led_Init(uint8_t intensity, uint8_t len)
{
	
	Max7219_GPIOInit();	
	max_len = len;
	
	Max7219_decode_mode(NO_DECODE_ALL);
	Max7219_intensity(intensity);
	Max7219_scan_limit(0x07);
	Max7219_shutdown(NORMAL_MODE);
	
	// 开始测试
	Max7219_test(0x01);
	Max7219_test(0x00);

}

void Max7219_WriteByte(uint8_t data)
{
	
	int8_t i;
	uint8_t tmp;

	for (i = 7; i >= 0; i--)
	{
		tmp = (data>>i) & 0x01;
		GPIO_ResetBits(MAX7219PORT,MAX7219_CLK_PIN);
		GPIO_WriteBit(MAX7219PORT, MAX7219_DATA_PIN, (BitAction)tmp);
		GPIO_SetBits(MAX7219PORT,MAX7219_CLK_PIN);
	}
}
/*
 * 向某片单独写数据 
 * addr 写入地址 
 * data 写入的数据 
 * index  写第几片 0 代表全部写入
 */
void Max7219_Send(uint8_t addr, uint8_t data, uint8_t index)
{
	
	GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	for(int8_t j = 0; j < max_len; j++)
	{
		if(index-j == 1) {
			Max7219_WriteByte(addr);
			Max7219_WriteByte(data);
		} else {
			Max7219_WriteByte(0x00);
			Max7219_WriteByte(0x00);
		
		}
	}
	
	GPIO_SetBits(MAX7219PORT,MAX7219_CS_PIN);

}

/*
 * 进入掉电模式
 */
int Max7219_shutdown(uint8_t mode)
{
	
	GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	for(uint8_t i = 0;i < max_len;i++) {
			
		Max7219_WriteByte(SHUT_DOWN);
		
		Max7219_WriteByte(mode);
	}
	
	GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);

	return 0;
}

/*
 * 设译码模式
 *  NO_DECODE_ALL   0x00     都不译码
 *  DECODE_D0_ONLY   0x01    第一个才译码 
 *	DECODE_D0D3_ONLY 0x0f    前四个才译码 
 *  DECODE_ALL      0xff     全都要译码
 *
 */
int Max7219_decode_mode(uint8_t mode)
{
	
	GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	for(uint8_t i = 0;i < max_len;i++) {
			
		Max7219_WriteByte(DECODE_MODE);
		Max7219_WriteByte(mode);
	}
	
	GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	
	return 0;
}

/* 
 * 亮度控制 
 * 0x00-0x0f
 */
int Max7219_intensity(uint8_t mode)
{
	
	GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	for(uint8_t i = 0;i < max_len;i++) {	
		Max7219_WriteByte(INTENSITY);
		Max7219_WriteByte(mode);
	}
	
	GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	return 0;
}

/* 
 * 扫描控制  0 - 7
 * 
 */
int Max7219_scan_limit(uint8_t mode)
{
	
	GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	for(uint8_t i = 0;i < max_len;i++) {
		Max7219_WriteByte(SCAN_LIMIT);
		Max7219_WriteByte(mode);
	}
	GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	
	return 0;
}

/* 
 * 显示检测 0, 1
 * 
 */
int Max7219_test(uint8_t mode)
{
	
	GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	for(uint8_t i = 0;i < max_len;i++) {
		Max7219_WriteByte(DISPLAY_TEST);
		Max7219_WriteByte(mode);
	}
	
	GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);
	
	return 0;
}


/* 数码管显示数字 */
void Max7219_digit(uint8_t digit, uint8_t data)
{
	int tmp = 0;
	
	float t1 = (float)digit / 8;
	
	uint8_t t2 = ceil(t1);
	
	uint8_t dp = data & 0x80;
	
	char *str = "0123456789ABC";
	
	tmp = indexOf(str, data&0x7f);

	if(tmp >= 0) {
		Max7219_Send((digit%8)?(digit%8):8, (uint8_t)(tmp|dp), t2);
	}
}
/* 显示字符 */
void Max7219_display(uint8_t index, char data)
{
	uint8_t i;
	const uint8_t *ptr;
	
	ptr = &Font8.table[(data - 0x20) * 8];
	
	// 逐行扫描
	for(i= 1; i < 9;i++) {
		Max7219_Send(i, *ptr, index);
		ptr++;
	}
	
}
