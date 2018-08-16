/******************* (c) coPyright 2016 枫云海韵工作室 **********************
 * 文件名       ：keyscan.c
 * 函数         ：void  keyInit(void)         初始化键盘
                  unsigned char keyScan(unsigned char clock)  键盘扫描, clock=1时自锁。
 * 键盘分布     ：
                  0  4  8  c
                  1  5  9  d
                  2  6  a  e
                  3  7  b  f

                  思通未来开发板为全独立键盘，标号为SM1~SM4, KEY1~KEY3
                  HOT51开发板为矩阵键盘，
                  标号为SM1~SM4扫描线，JC1~JC4检测线，独立按键为KEY1,KEY2P,KEY3
 ****************************************************************************/
#include <Arduino.h>
#include <PinMap.h>
#include <keyscan.h>

#define keytype 1 //如果为1则为全独立键盘，为0则为矩阵键盘

#define SM1 P1_4 //扫描线1-4
#define SM2 P1_5
#define SM3 P1_6
#define SM4 P1_7

#define SMPIN P1 //扫描线组

#define JC1 P1_0 //检测线1-4
#define JC2 P1_1
#define JC3 P1_2
#define JC4 P1_3 

#define KEY1 P3_2 //独立按键1-3
#define KEY2 P3_3
#define KEY3 P3_4

void keyInit(void)
{
    SM1 = 1;
    SM2 = 1;
    SM3 = 1;
    SM4 = 1;
    KEY1 = 1;
    KEY2 = 1;
    KEY3 = 1;
}

unsigned char keyScan(unsigned char clock)
#if keytype
{
    unsigned char i;
    if(SM1 == 0)
    {
        delay_ms(20);
        if(SM1 == 0)
            while(SM1 == 0);
        i = 1;
    }
    else if(SM2 == 0)
    {
        delay_ms(20);
        if(SM2 == 0)
            while(SM2 == 0);
        i = 2;
    }
    else if(SM3 == 0)
    {
        delay_ms(20);
        if(SM3 == 0)
            while(SM3 == 0);
        i = 3;
    }
    else if(SM4 == 0)
    {
        delay_ms(20);
        if(SM4 == 0)
            while(SM4 == 0);
        i = 4;
    }
    else if(KEY1 == 0)
    {
        delay_ms(20);
        if(KEY1 == 0)
            while(KEY1 == 0);
        i = 5;
    }
    else if(KEY2 == 0)
    {
        delay_ms(20);
        if(KEY2 == 0)
            while(KEY2 == 0);
        i = 6;
    }
    else if(KEY3 == 0)
    {
        delay_ms(20);
        if(KEY3 == 0)
            while(KEY3 == 0);
        i = 7;
    }
    if(!clock)i = 0;
    return i;
}
#else
{
    unsigned char i, j, temp, a, buffer[4] = {0xef, 0xdf, 0xbf, 0x7f};
    for(j = 0; j < 4; j++)
    {
        SMPIN = buffer[j];
        delay_ms(5);
        temp = 0x01;
        for(i = 0; i < 4; i++)
        {
            if(!(SMPIN & temp))
            {
                a = (i + j * 4);
            }
            temp <<= 1;
        }
    }                                            //矩阵键盘
    if(KEY1 == 0)
    {
        delay_ms(5);    //独立按键1
        if(KEY1 == 0)a = 21;
    }
    else if(KEY2 == 0)
    {
        delay_ms(5);    //独立按键2
        if(KEY2 == 0)a = 22;
    }
    else if(KEY3 == 0)
    {
        delay_ms(5);    //独立按键3
        if(KEY3 == 0)a = 23;
    }

    if(!clock)a = 0;
    return a;
}
#endif
