/**
  ******************************************************************************
  * @file    Font8.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text Font8 for STM32xx-EVAL's LCD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fonts.h"

// 
//  Font data for Courier New 12pt
// 

const uint8_t Font8_Table[] = 
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // - -

	0x00,0x10,0x10,0x10,0x10,0x10,0x00,0x10, // -!-

	0x00,0x28,0x28,0x28,0x00,0x00,0x00,0x00, // -"-

	0x00,0x28,0x28,0x7C,0x28,0x7C,0x28,0x28, // -#-

	0x00,0x10,0x3C,0x60,0x38,0x14,0x78,0x10, // -$-

	0x00,0x60,0x64,0x08,0x10,0x20,0x4C,0x0C, // -%-

	0x00,0x20,0x50,0x50,0x20,0x54,0x48,0x34, // -&-

	0x00,0x18,0x10,0x20,0x00,0x00,0x00,0x00, // -'-

	0x00,0x08,0x10,0x20,0x20,0x20,0x10,0x08, // -(-

	0x00,0x20,0x10,0x08,0x08,0x08,0x10,0x20, // -)-

	0x00,0x10,0x54,0x38,0x10,0x38,0x54,0x10, // -*-

	0x00,0x10,0x10,0x10,0x7C,0x10,0x10,0x10, // -+-

	0x00,0x00,0x00,0x00,0x00,0x30,0x20,0x40, // -,-

	0x00,0x00,0x00,0x00,0x7C,0x00,0x00,0x00, // ---

	0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30, // -.-

	0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x00, // -/-

	0x0F,0x09,0x09,0x09,0x09,0x09,0x0F,0x00, // -0-

	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00, // -1-

	0x0F,0x01,0x01,0x0F,0x08,0x08,0x0F,0x00, // -2-

	0x0F,0x01,0x01,0x0F,0x01,0x01,0x0F,0x00, // -3-

	0x09,0x09,0x09,0x0F,0x01,0x01,0x01,0x00, // -4-

	0x0F,0x08,0x08,0x0F,0x01,0x01,0x0F,0x00, // -5-

	0x0F,0x08,0x08,0x0F,0x09,0x09,0x0F,0x00, // -6-

	0x0F,0x01,0x01,0x01,0x01,0x01,0x01,0x00, // -7-

	0x0F,0x09,0x09,0x0F,0x09,0x09,0x0F,0x00, // -8-

	0x0F,0x09,0x09,0x0F,0x01,0x01,0x0F,0x00, // -9-

	0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x00, // -:-

	0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x40, // -;-

	0x00,0x08,0x10,0x20,0x40,0x20,0x10,0x08, // -<-

	0x00,0x00,0x00,0x7C,0x00,0x7C,0x00,0x00, // -=-

	0x00,0x20,0x10,0x08,0x04,0x08,0x10,0x20, // ->-

	0x00,0x38,0x44,0x08,0x10,0x10,0x00,0x10, // -?-

	0x00,0x38,0x44,0x5C,0x54,0x5C,0x40,0x3C, // -@-

	0x00,0x10,0x28,0x44,0x44,0x7C,0x44,0x44, // -A-

	0x00,0x78,0x44,0x44,0x78,0x44,0x44,0x78, // -B-

	0x00,0x38,0x44,0x40,0x40,0x40,0x44,0x38, // -C-

	0x00,0x78,0x44,0x44,0x44,0x44,0x44,0x78, // -D-

	0x00,0x7C,0x40,0x40,0x78,0x40,0x40,0x7C, // -E-

	0x00,0x7C,0x40,0x40,0x78,0x40,0x40,0x40, // -F-

	0x00,0x38,0x44,0x40,0x40,0x5C,0x44,0x3C, // -G-

	0x00,0x44,0x44,0x44,0x7C,0x44,0x44,0x44, // -H-

	0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x38, // -I-

	0x00,0x1C,0x08,0x08,0x08,0x08,0x48,0x30, // -J-

	0x00,0x44,0x48,0x50,0x60,0x50,0x48,0x44, // -K-

	0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7C, // -L-

	0x00,0x44,0x6C,0x54,0x54,0x44,0x44,0x44, // -M-

	0x00,0x44,0x44,0x64,0x54,0x4C,0x44,0x44, // -N-

	0x00,0x38,0x44,0x44,0x44,0x44,0x44,0x38, // -O-

	0x00,0x78,0x44,0x44,0x78,0x40,0x40,0x40, // -P-

	0x00,0x38,0x44,0x44,0x44,0x54,0x48,0x34, // -Q-

	0x00,0x78,0x44,0x44,0x78,0x50,0x48,0x44, // -R-

	0x00,0x38,0x44,0x40,0x38,0x04,0x44,0x38, // -S-

	0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10, // -T-

	0x00,0x44,0x44,0x44,0x44,0x44,0x44,0x38, // -U-

	0x00,0x44,0x44,0x44,0x44,0x44,0x28,0x10, // -V-

	0x00,0x44,0x44,0x44,0x54,0x54,0x6C,0x44, // -W-

	0x00,0x44,0x44,0x28,0x10,0x28,0x44,0x44, // -X-

	0x00,0x44,0x44,0x28,0x10,0x10,0x10,0x10, // -Y-

	0x00,0x7C,0x04,0x08,0x10,0x20,0x40,0x7C, // -Z-

	0x00,0x78,0x60,0x60,0x60,0x60,0x60,0x78, // -[-

	0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x00, // -\-

	0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C, // -]-

	0x00,0x10,0x38,0x54,0x10,0x10,0x10,0x10, // -^-

	0x00,0x00,0x10,0x20,0x7C,0x20,0x10,0x00, // -_-

	0x00,0x10,0x08,0x04,0x00,0x00,0x00,0x00, // -`-

	0x00,0x00,0x00,0x70,0x08,0x38,0x48,0x34, // -a-

	0x00,0x40,0x40,0x58,0x64,0x44,0x64,0x58, // -b-

	0x00,0x00,0x00,0x38,0x44,0x40,0x40,0x38, // -c-

	0x00,0x04,0x04,0x34,0x4C,0x44,0x4C,0x34, // -d-

	0x00,0x00,0x00,0x38,0x44,0x78,0x40,0x38, // -e-

	0x00,0x18,0x24,0x20,0x78,0x20,0x20,0x20, // -f-

	0x00,0x00,0x00,0x38,0x44,0x44,0x3C,0x04, // -g-

	0x00,0x40,0x40,0x58,0x64,0x44,0x44,0x44, // -h-

	0x00,0x10,0x00,0x00,0x10,0x10,0x10,0x10, // -i-

	0x00,0x08,0x00,0x00,0x18,0x08,0x08,0x08, // -j-

	0x00,0x40,0x40,0x48,0x50,0x60,0x50,0x4C, // -k-

	0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x38, // -l-

	0x00,0x00,0x00,0x28,0x54,0x54,0x54,0x54, // -m-

	0x00,0x00,0x00,0x58,0x24,0x24,0x24,0x24, // -n-

	0x00,0x00,0x00,0x38,0x44,0x44,0x44,0x38, // -o-

	0x00,0x00,0x00,0x78,0x44,0x44,0x78,0x40, // -p-

	0x00,0x00,0x00,0x3C,0x44,0x44,0x3C,0x04, // -q-

	0x00,0x00,0x00,0x58,0x24,0x20,0x20,0x20, // -r-

	0x00,0x00,0x00,0x3C,0x40,0x38,0x04,0x78, // -s-

	0x00,0x20,0x20,0x7C,0x20,0x20,0x24,0x18, // -t-

	0x00,0x00,0x00,0x48,0x48,0x48,0x48,0x34, // -u-

	0x00,0x00,0x00,0x44,0x44,0x44,0x28,0x10, // -v-

	0x00,0x00,0x00,0x54,0x54,0x54,0x54,0x28, // -w-

	0x00,0x00,0x00,0x44,0x28,0x10,0x28,0x44, // -x-

	0x00,0x00,0x00,0x44,0x44,0x4C,0x34,0x04, // -y-

	0x00,0x00,0x00,0x7C,0x08,0x10,0x20,0x7C, // -z-

	0x00,0x10,0x20,0x20,0x40,0x20,0x20,0x10, // -{-

	0x00,0x10,0x10,0x10,0x00,0x10,0x10,0x10, // -|-

	0x00,0x10,0x08,0x08,0x04,0x08,0x08,0x10, // -}-

	0x00,0x00,0x00,0x20,0x54,0x08,0x00,0x00 // -~-

};

sFONT Font8 = {
  Font8_Table,
  8, /* Width */
  8, /* Height */
};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/