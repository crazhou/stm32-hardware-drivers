#ifndef __DS3231_H
#define __DS3231_H
#include "sys.h"
#include "i2c.h"


#define DS3231_ADDR 0xd0

u8 DS3231_Get_Status(void);

void DS3231_GetTime(u8 *time);

void DS3231_GetDate(u8 *date);

void DS3231_SetTime(u8 *time); // ʱ�� �֣� ��

void DS3231_SetDate(u8 *date); // �꣬ �£� ��

void DS3231_GetTemp(u8 *temp); // ��ȡ�¶�

void DS3231_setweek(u8 week);


#endif
