#include "Arduino.h"
#include "PinMap.h"
#include "EM1190B.h"

#define EMCLK P1_0
#define EMDIN P1_1

unsigned char code em1190bnum[10] = {0x11, 0xDD, 0x83, 0x89, 0x4d, 0x29, 0x21, 0x9d, 0x01, 0x09, }; //0~1
unsigned char code em1190bpoint[2] = {0xff, 0x00}; //_ :

void emSetChar(unsigned char i)
{
    unsigned char j, k;
    for (j = 1; j < 9; j++)
    {
        digitalWrite(EMCLK, 1);
        k++;//延时
        k++;//延时
        digitalWrite(EMDIN, i & 0x80);
        i = i << 1;
        k++;//延时
        k++;//延时
        k++;//延时
        k++;//延时
        digitalWrite(EMCLK, 0);
        k++;//延时
        k++;//延时
    }
}

void emSetBit(void)
{
    unsigned char k;
    digitalWrite(EMCLK, 1);
    k++;
    k++;
    digitalWrite(EMDIN, 1);
    k++;
    k++;
    k++;
    k++;
    digitalWrite(EMCLK, 0);
    k++;
    k++;
}

void emDelay(void)
{
    unsigned char a, b, c;
    for(c = 167; c > 0; c--)
        for(b = 171; b > 0; b--)
            for(a = 16; a > 0; a--);
    //  a++;
}

void emDisplay(unsigned char m1, m2, s1, s2, p) //显示时间,p取0或1
{
    digitalWrite(EMCLK, 0);
    digitalWrite(EMDIN, 0);
    emDelay();
    emSetChar(em1190bpoint[p]);
    emSetChar(em1190bnum[m1]);
    emSetChar(em1190bnum[m2]);
    emSetChar(em1190bnum[s1]);
    emSetChar(em1190bnum[s2]);
    emSetBit();
    emDelay();
}