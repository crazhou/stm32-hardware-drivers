#include "max7219.h"
#include "fonts.h"

// �ַ����в��� �ַ�
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

/*
 * ��ʼ�� GPIO �˿�
 * �ҵ�GPIO ʵʱ �Ѿ� Ĭ�ϳ�ʼ���ˣ����û�У���ſ��� 32 ��ע�� 
 */
void Max7219_GPIOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = MAX7219_CS_PIN | MAX7219_CLK_PIN | MAX7219_DATA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MAX7219PORT, &GPIO_InitStructure);

  // ʱ�Ӻ�����������
  GPIO_ResetBits(MAX7219PORT, MAX7219_CLK_PIN | MAX7219_DATA_PIN);

  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);
}

/*
 * ����ܳ�ʼ��, ����һ������
 */
void Max7219_Digital_Init(uint8_t intensity)
{
  Max7219_GPIOInit();

  // �ȴ�������ʼ��
  delay_ms(50);

  Max7219_decode_mode(DECODE_ALL);
  Max7219_intensity(intensity);
  Max7219_scan_limit(0x07);
  Max7219_shutdown(NORMAL_MODE);

  // ��ʼ����
  Max7219_test(0x01);
  Max7219_test(0x00);
}
/*  
 * ��ʼ�� LED ��ʾ�� intensity Ϊÿ������ 0x01 ~ 0x0f
 */
void Max7219_Led_Init(uint8_t intensity)
{

  Max7219_GPIOInit();

  // �ȴ�������ʼ��
  delay_ms(50);

  Max7219_decode_mode(NO_DECODE_ALL);

  Max7219_intensity(intensity);

  Max7219_scan_limit(0x07);

  Max7219_shutdown(NORMAL_MODE);

  // ��ʼ��Ļ����
  Max7219_test(0x01);
  delay_ms(1000);
  Max7219_test(0x00);
}

void Max7219_WriteByte(uint8_t data)
{
  int8_t i;
  uint8_t tmp;

  for (i = 7; i >= 0; i--)
  {
    tmp = (data >> i) & 0x01;
    GPIO_ResetBits(MAX7219PORT, MAX7219_CLK_PIN);
    GPIO_WriteBit(MAX7219PORT, MAX7219_DATA_PIN, (BitAction)tmp);
    GPIO_SetBits(MAX7219PORT, MAX7219_CLK_PIN);
  }
}
/*
 * ��ĳƬ����д���� 
 * addr д���ַ 
 * data д������� 
 * index  д�ڼ�Ƭ
 */
void Max7219_Send(uint8_t addr, uint8_t data, uint8_t index)
{

  GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);

  for (int8_t j = 0; j < LED_LEN; j++)
  {
    if (index - j == 1)
    {
      Max7219_WriteByte(addr);
      Max7219_WriteByte(data);
    }
    else
    {
      Max7219_WriteByte(0x00);
      Max7219_WriteByte(0x00);
    }
  }

  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);
}

/*
 * �������ģʽ
 */
int Max7219_shutdown(uint8_t mode)
{

  GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);

  for (uint8_t i = 0; i < LED_LEN; i++)
  {

    Max7219_WriteByte(SHUT_DOWN);

    Max7219_WriteByte(mode);
  }

  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);

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

  GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);

  for (uint8_t i = 0; i < LED_LEN; i++)
  {

    Max7219_WriteByte(DECODE_MODE);
    Max7219_WriteByte(mode);
  }

  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);

  return 0;
}

/* 
 * ���ȿ��� 
 * 0x00-0x0f
 */
int Max7219_intensity(uint8_t mode)
{

  GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);

  for (uint8_t i = 0; i < LED_LEN; i++)
  {

    Max7219_WriteByte(INTENSITY);
    Max7219_WriteByte(mode);
  }

  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);

  return 0;
}

/* 
 * ɨ�����  0 - 7
 * 
 */
int Max7219_scan_limit(uint8_t mode)
{

  GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);

  for (uint8_t i = 0; i < LED_LEN; i++)
  {

    Max7219_WriteByte(SCAN_LIMIT);
    Max7219_WriteByte(mode);
  }
  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);

  return 0;
}

/* 
 * ��ʾ��� 0, 1
 * 
 */
int Max7219_test(uint8_t mode)
{

  GPIO_ResetBits(MAX7219PORT, MAX7219_CS_PIN);

  for (uint8_t i = 0; i < LED_LEN; i++)
  {

    Max7219_WriteByte(DISPLAY_TEST);
    Max7219_WriteByte(mode);
  }

  GPIO_SetBits(MAX7219PORT, MAX7219_CS_PIN);

  return 0;
}

/* ��ʾ���� */
void Max7219_digit(uint8_t digit, uint8_t data)
{
  int tmp = 0;

  uint8_t dp = data & 0x80;

  char str[] = "0123456789-EHLP ";

  tmp = indexOf(str, data & 0x7f);

  if (tmp >= 0)
  {

    Max7219_Send(digit, (uint8_t)(tmp | dp), 1);
  }
}
/* ��ʾ�ַ� */
void Max7219_display(uint8_t index, char data)
{

  uint8_t i;
  const uint8_t *ptr;

  ptr = &Font8.table[(data - 0x20) * 8];

  // ����ɨ��
  for (i = 1; i < 9; i++)
  {
    Max7219_Send(i, *ptr, index);
    ptr++;
  }
}
