#include "max7219.h"

/*
 * �����ֲ��е����ݣ�max7219 �ǲ�֧�� SPI �ģ� �� Max7212 ��֧��SPI
 */
void Max7219_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = MAX7219_CS_PIN | MAX7219_CLK_PIN | MAX7219_DATA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MAX7219PORT, &GPIO_InitStructure);

  // ʱ�Ӻ�����������
  GPIO_ResetBits(MAX7219PORT, MAX7219_CLK_PIN | MAX7219_DATA_PIN);

  // Ƭѡ�ӿ�����
  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);

  Max7219_decode_mode(DECODE_ALL);
  Max7219_intensity(0x04);
  Max7219_scan_limit(0x07);
  Max7219_shutdown(NORMAL_MODE);

  // ��ʼ����
  Max7219_test(0x01);
  delay_ms(1000);
  Max7219_test(0x00);
}

void Max7219_Send(uint8_t addr, uint8_t data)
{
  int8_t i;
  uint8_t tmp;

  GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);

  for (i = 7; i >= 0; i--)
  {
    tmp = (addr >> i) & 0x01;
    GPIO_WriteBit(MAX7219PORT, MAX7219_DATA_PIN, (BitAction)tmp);
    GPIO_SetBits(MAX7219PORT, MAX7219_CLK_PIN);
    GPIO_ResetBits(MAX7219PORT, MAX7219_CLK_PIN);
  }

  for (i = 7; i >= 0; i--)
  {
    tmp = (data >> i) & 0x01;
    GPIO_WriteBit(MAX7219PORT, MAX7219_DATA_PIN, (BitAction)tmp);
    GPIO_SetBits(MAX7219PORT, MAX7219_CLK_PIN);
    GPIO_ResetBits(MAX7219PORT, MAX7219_CLK_PIN);
  }

  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);
}

/*
 * �������ģʽ
 */
int Max7219_shutdown(uint8_t mode)
{
  Max7219_Send(SHUT_DOWN, mode);

  return 0;
}

/*
 * ������ģʽ
 *  NO_DECODE_ALL   0x00     ��������
 *  DECODE_D0_ONLY   0x01    ��һ�������� 
 *	DECODE_D0D3_ONLY 0x0f    ǰ�ĸ������� 
 *  DECODE_ALL      0xff     ȫ��Ҫ����
 *
 */
int Max7219_decode_mode(uint8_t mode)
{

  Max7219_Send(DECODE_MODE, mode);

  return 0;
}

/* 
 * ���ȿ��� 
 * 0x00-0x0f
 */
int Max7219_intensity(uint8_t mode)
{

  Max7219_Send(INTENSITY, mode);

  return 0;
}

/* 
 * ɨ�����  0 - 7
 * 
 */
int Max7219_scan_limit(uint8_t mode)
{

  Max7219_Send(SCAN_LIMIT, mode);

  return 0;
}

/* 
 * ��ʾ��� 0, 1
 * 
 */
int Max7219_test(uint8_t mode)
{

  Max7219_Send(DISPLAY_TEST, mode);

  return 0;
}

int8_t indexOf(char *str, uint8_t ch)
{
  int8_t index = 0;

  char tmp = str[index];

  while (tmp != '\0')
  {

    if (tmp == ch)
    {
      return index;
    }
    index++;
    tmp = str[index];
  }

  return -1;
}

int Max7219_digit(uint8_t digit, uint8_t data)
{
  int8_t tmp = 0;

  char str[] = "0123456789-EHLP ";

  tmp = indexOf(str, data);

  if (tmp >= 0)
  {

    Max7219_Send(digit, (uint8_t)tmp);
  }
  return 0;
}
