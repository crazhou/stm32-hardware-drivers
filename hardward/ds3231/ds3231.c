#include "ds3231.h"

u8 Bcd2dec(u8 data)
{
  return (data>>4&0x0f)*10 + (data&0x0f);
}

u8 Dec2bcd(u8 data)
{
	return ((data/10)<<4) + (data%10);
}

u8 DS3231_Get_Status(void)
{
		return I2C_ReadByte(DS3231_ADDR, 0x0f);
}


void DS3231_GetTime(u8 *time)
{
	// Ê±¼ä¼Ä´æÆ÷µØÖ·
	u8 addrs[] = {0x02, 0x01, 0x00};
	
	u8 temp = 0;
	
	for(u8 i = 0; i < 3; i++){
		
		temp = I2C_ReadByte(DS3231_ADDR, addrs[i]);
		
		*(time+i) = Bcd2dec(temp);
	}
	
}

void DS3231_GetDate(u8 *date)
{
	u8 addrs[] = {0x06, 0x05, 0x04, 0x03};
	
	u8 temp = 0; 
	
	for(u8 i = 0; i < 4; i++){
		
		temp = I2C_ReadByte(DS3231_ADDR, addrs[i]);
		
		*(date+i) = Bcd2dec(temp);
	}
	
}

void DS3231_SetDate(u8 *date)
{
	u8 addrs[] = {0x06, 0x05, 0x04};
	
	for(u8 i = 0; i < 3; i++){
		I2C_WriteByte(DS3231_ADDR, addrs[i], Dec2bcd(date[i]));
	}
}

void DS3231_setweek(u8 week)
{
	u8 addr = 0x03;
	I2C_WriteByte(DS3231_ADDR,addr, Dec2bcd(week));
}

void DS3231_SetTime(u8 *time)
{
	
	u8 addrs[] = {0x02, 0x01, 0x00};
	
	for(u8 i = 0; i < 3; i++){
		I2C_WriteByte(DS3231_ADDR, addrs[i], Dec2bcd(time[i]));
	}

}

void DS3231_GetTemp(u8 *temp)
{
		u8 t = I2C_ReadByte(DS3231_ADDR, 0x11);
		
	  *temp = t;
}
