#include "oled.h"
#include "ASCII_8x16.h"
#include "CHS_16x16.h"

// 128 x 64 显示屏 1.3 英寸
void OLED_init(u8 intens)
{
	OLED_display_off();
	OLED_display_clear(0x00);
	OLED_dispaly_on();
	OLED_set_intens(intens);
}

void OLED_display_off (void)
{
	
	u8 buf[] = {
		OLED_COMM,
		0xae, //0xae:关显示，0xaf:开显示
		0x8d,
		0x10, //VCC电源
	};
	I2C_WriteBytes(OLED_ADD, buf, 4);
}

void OLED_dispaly_on (void)
{
	
	u8 buf[] = {
		OLED_COMM,
		0xae,//0xae:关显示，0xaf:开显示
		0x00,0x10,//开始地址（双字节）       
		0xd5,0x80,//显示时钟频率？
		0xa8,0x3f,//复用率？
		0xd3,0x00,//显示偏移？
		0XB0,//写入页位置（0xB0~7）
		0x40,//显示开始线
		0x8d,0x14,//VCC电源
		0xa1,//设置段重新映射？
		0xc8,//COM输出方式
		0xda,0x12,//COM输出方式？
		0x81,0xff,//对比度，指令：0x81，数据：0~255（255最高）
		0xd9,0xf1,//充电周期？
		0xdb,0x30,//VCC电压输出
		0x20,0x00,//水平寻址设置
		0xa4,//0xa4:正常显示，0xa5:整体点亮
		0xa6,//0xa6:正常显示，0xa7:反色显示
		0xaf//0xae:关显示，0xaf:开显示
	};
	
	I2C_WriteBytes(OLED_ADD, buf, 29);
}

//OLED屏亮度设置（0~255）
void OLED_set_intens (u8 x)
{

	I2C_WriteByte(OLED_ADD, OLED_COMM, 0x81);
	I2C_WriteByte(OLED_ADD, OLED_COMM, x);

}

void OLED_display_clear(u8 x)
{
	for(u8 t=0; t<8;t++) {
		I2C_WriteByte(OLED_ADD, OLED_COMM, 0xb0 + t);
		I2C_WriteByte(OLED_ADD, OLED_COMM, 0x02);
		I2C_WriteByte(OLED_ADD, OLED_COMM, 0x10);
		for(u8 j = 0; j < 128; j++) {
			I2C_WriteByte(OLED_ADD, OLED_DATA, x);
		}
	}
}

//显示英文与数字8*16的ASCII码
void OLED_DISPLAY_8x16(u8 x, u8 y, u16 w)
{
	u8 c=0;
	for(u8 t=0; t<2; t++){
		I2C_WriteByte(OLED_ADD,OLED_COMM,0xb0+x);    //页地址（从0xB0到0xB7）
		I2C_WriteByte(OLED_ADD,OLED_COMM,y/16+0x10); //起始列地址的高4位
		I2C_WriteByte(OLED_ADD,OLED_COMM,y%16+0x02); //起始列地址的低4位
		for(u8 j=0;j<8;j++){ //整页内容填充
 			I2C_WriteByte(OLED_ADD, OLED_DATA, ASCII_8x16[(w*16)+c-512]);//为了和ASII表对应要减512
			c++;
		}
		x++; //页地址加1
	}
}
//向LCM发送一个字符串,长度64字符之内。
void OLED_display_string(u8 row, char *str)
{
	u8 r = 0;
	while(*str != '\0') {
		OLED_DISPLAY_8x16(row, r*8, *str++);
		r++;
	}	
}

//显示汉字16*16
//取模大小为16*16，取模方式为“从左到右从上到下”“纵向8点下高位”
void OLED_display_chs(u8 x, u8 y, u16 w)
{
	u8 j,t,c=0;
	for(t=0;t<2;t++) {
		I2C_WriteByte(OLED_ADD, OLED_COMM, 0xb0 + x); //页地址（从0xB0到0xB7）
		I2C_WriteByte(OLED_ADD, OLED_COMM, y/16 + 0x10); //起始列地址的高4位
		I2C_WriteByte(OLED_ADD, OLED_COMM, y%16 + 0x02);	//起始列地址的低4位
		for(j=0;j < 16;j++){ //整页内容填充
 			I2C_WriteByte(OLED_ADD, OLED_DATA, GB_16[(w*32)+c]);
			c++;
		}
		x++; //页地址加1
	}
}
