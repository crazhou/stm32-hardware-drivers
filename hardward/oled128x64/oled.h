#ifndef __OLED_H

#define __OLED_H
#include "sys.h"
#include "delay.h"
#include "i2c.h"

#define OLED_ADD 0x78 // OLED I2C µÿ÷∑ 
#define OLED_COMM  0x00  // √¸¡Óµÿ÷∑ 
#define OLED_DATA  0x40//

void OLED_init(u8 intens);
void OLED_display_off(void);
void OLED_display_clear(u8 fill);
void OLED_dispaly_on(void);
void OLED_set_intens(u8);
void OLED_display_string(u8 row, char *str);
void OLED_display_chs(u8 x, u8 y, u16 w);

#endif
