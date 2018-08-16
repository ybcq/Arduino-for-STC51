/******************* (c) coPyright 2016 枫云海韵工作室 **********************
 * 文件名       ：74ls164.c
 * 作用         ：共阴数码管74hc164串行驱动
 ****************************************************************************/
#include "Arduino.h"
#include "PinMap.h"
#include <74LS164.h>

//此处修改引脚定义
#define LS164_CLK P1_1
#define LS164_DAT P1_2

unsigned char code lsnum[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xff, 0xf6}; //0-9,-,全灭

void lssendbyte(unsigned char byte)
{
    uint8_t num, c;
    num = lsnum[byte];
    //num = num | 0x01;
    for(c = 0; c < 8; c++)
    {
        digitalWrite(LS164_CLK, 0);
        digitalWrite(LS164_DAT, num & 0x01;);
        digitalWrite(LS164_CLK, 1);
        num >>= 1;
    }
}

void lsDisplay(unsigned char number)
{
    unsigned char numberh = number / 10;
    unsigned char numberl = number % 10;
    lssendbyte (numberh);
    delay_ms(10);
    lssendbyte (numberl);
    delay_ms(10);
}
