# 说明

## 这里不会放详细的数据手册 ,会写一些我平时踩的坑!

1. max7219 驱动 8 个数码管的 驱动 请看 Max7219_Digital_Init 和 Max7219_digit 两个函数
2. max7219 驱动 4 个 8x8 的 led 点阵，请看
   Max7219_Led_Init 和 Max7219_display 两个函数

# 关于器件

- Max7219 是 8 位数码管或 8x8 点阵屏专用的驱动芯片，和 SPI 协议是不兼容的，引脚看着有点像 SPI，实际上不是！
- Max7221 和 他的功能类似，抗干扰能力更强，支持 SPI 通信
- 两者都支持级联
