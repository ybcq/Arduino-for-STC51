/******************* (c) copyright 2016 ���ƺ��Ϲ����� **********************
 * �ļ���       ��led.c
 * ����         ��ledInit(void)                                     ��ʼ����Ļ
                  ledDisplay(uint16_t i, uint16_t j, uint8_t point, uint8_t digit)
                  ��Ļɨ��(ǰ4λ����4λ�����Ҳ���С����λ�ã�λ��)
                  ledDisplayEnglish(uint8_t digit, uint8_t letter)         ��ʾӢ�ľɰ�
                  ledDisplayNew(uint8_t letter[8])                       ��ʾӢ���°�
 * ��ע         ��ʹ�õ���DISSMɨ���ߣ�DISXS��ʾ��
                  ˼ͨδ���������ǹ�������HOT51������ʹ�õ��ǹ�����
 ****************************************************************************/

#include <Arduino.h>
#include <PinMap.h>
#include <leddisplay.h>

#define ledtype 1 //����Ϊ1λ��������0Ϊ������

#define DISSM P2 //ɨ����
#define DISXS P0 //��ʾ��

extern uint8_t code ascii[128] =
{
    0xc0, 	0xf9, 	0xa4, 	0xb0, 	0x99, 	0x92, 	0x82, 	0xf8, 	0x80, 	0x90,
    0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00,   0x00,
    0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00, 	0x00,
    0x00, 	0x00, 	0x00, 	0x86, 	0x22, 	0x00, 	0x00, 	0x00, 	0x00, 	0x20,
    0x39, 	0x0f, 	0x00, 	0x00, 	0x80, 	0x40, 	0x80, 	0x52, 	0x3f, 	0x06,
    0x5b, 	0x4f, 	0x66, 	0x6d, 	0x7d, 	0x07, 	0x7f, 	0x6f, 	0x00,   0x00,
    0x00, 	0x48, 	0x00, 	0x53, 	0x5f, 	0x77, 	0x7c, 	0x39, 	0x5e, 	0x79,
    0x71, 	0x3d, 	0x76, 	0x30, 	0x0e, 	0x00, 	0x38, 	0x00, 	0x37, 	0x3f,
    0x73, 	0x67, 	0x50, 	0x6d, 	0x78, 	0x3e, 	0x3e, 	0x00, 	0x00, 	0x6e,
    0x5b, 	0x39, 	0x64, 	0x0f, 	0x23, 	0x08, 	0x01, 	0x5f, 	0x7c, 	0x58,
    0x5e, 	0x7b, 	0x71, 	0x6f, 	0x74, 	0x10, 	0x0e, 	0x00, 	0x30, 	0x00,
    0x54, 	0x5c, 	0x73, 	0x67, 	0x50, 	0x6d, 	0x78, 	0x1c, 	0x00, 	0x00,
    0x00, 	0x6e, 	0x5b, 	0x39, 	0x30, 	0x0f, 	0x01, 	0x00
};

#if ledtype       //*******************˼ͨδ��������**********************
void ledInit(void)
{
  DISSM = 0xff;
  DISXS = 0xff;
}

void ledDisplay(uint16_t i, uint16_t j, uint8_t point, uint8_t digit)
{
    uint8_t pdigit = 0;
    uint8_t pa = 0;
    uint8_t data1[] = {0, 0, 0, 0, 0, 0, 0, 0};
    data1[7] = i / 1000;
    data1[6] = i % 1000 / 100;
    data1[5] = i % 100 / 10;
    data1[4] = i % 10;
    data1[3] = j / 1000;
    data1[2] = j % 1000 / 100;
    data1[1] = j % 100 / 10;
    data1[0] = j % 10;
    DISSM = 0xfe;
    while(digit)
    {
        DISXS = ascii[data1[pdigit]];
        if(point == (pdigit + 1))DISXS = DISXS & 0x7f;
        delay_ms(5);
        pdigit++;
        digit--;
        DISXS = 0xff;
        pa = ~DISSM;
        pa = pa << 1;
        DISSM = ~pa;
    }
}

void ledDisplayEnglish(uint8_t digit, uint8_t letter)
{
    uint8_t pdigit = 1;							// pow(2,digit-1)
    uint8_t n = digit - 1;						// pow(2,digit-1)
    uint8_t i;								// pow(2,digit-1)
    for(i = 1; i <= n; i++)
    {
        pdigit *= 2;   // pow(2,digit-1)
    }
    DISSM = ~pdigit;
    DISXS = ~ascii[letter];
    delay_ms(10);
    DISSM = 0xff;
}

void ledDisplayNew(uint8_t letter[8])
{
    uint8_t pa;
    uint8_t digit = 8;
    while(digit)
    {
        DISXS = ascii[letter[digit - 1]];
        delay_ms(5);
        digit--;
        DISXS = 0xff;
        pa = ~DISSM;
        pa = pa << 1;
        DISSM = ~pa;
    }
}

#else                  //*******************hot51������**********************
void ledInit(void)
{
DISSM = 0x07; //ɨ��
DISXS = 0x00; //����  
}

void ledDisplay(uint16_t i, uint16_t j, uint8_t point, uint8_t digit)
{
    uint8_t pdigit = 0;					   //С����ɨ�����
    // uint8_t pa = 0;
    uint8_t data1[] = {0, 0, 0, 0, 0, 0, 0, 0};
    data1[7] = i / 1000;
    data1[6] = i % 1000 / 100;
    data1[5] = i % 100 / 10;
    data1[4] = i % 10;
    data1[3] = j / 1000;
    data1[2] = j % 1000 / 100;
    data1[1] = j % 100 / 10;
    data1[0] = j % 10;
    DISSM = 0x07;
    while(digit)
    {
        DISXS = ~ascii[data1[pdigit]];
        if(point == (pdigit + 1))DISXS = DISXS | ~0x7f;
        delay_ms(5);
        pdigit++;
        digit--;
        DISXS = 0x00;
        if(DISSM != 0)DISSM--;
        else DISSM = 7;
    }
}

void ledDisplayEnglish(uint8_t digit, uint8_t letter)
{
    DISSM = 8 - digit;
    DISXS = ascii[letter];
    delay_ms(10);
    DISSM = 0x07;  								// ��ԭ����
}

void ledDisplayNew(uint8_t letter[8])
{
    uint8_t digit = 8;
    while(digit)
    {
        DISXS = ascii[letter[digit - 1]];
        delay_ms(5);
        digit--;
        DISXS = 0x00;
        if(DISSM != 0)DISSM--;
        else DISSM = 7;
    }
}
#endif

/***************************�ɰ汾��table*********************************
 extern uint8_t code table[]=
 {
 	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90
 };
 extern uint8_t code tableenglish[]=
 {
	0x77, 0x5f, 0x7c, 0x39, 0x58, 0x5e, 0x79, 0x7b, 0x71, 0x3d, // a 	 a 	 b 	 c 	 c 	 d 	 e 	 e 	 f 	 g
	0x76, 0x74, 0x0e, 0x38, 0x37, 0x54, 0x5c, 0x73, 0x67, 0x50, // h 	 h   j   l   n   n   o   p   q   r
	0x78, 0x3e, 0x1c, 0x6e, 0x40, 0x08                          // t 	 u   u   y   -   _
 };
****************************************************************************/

