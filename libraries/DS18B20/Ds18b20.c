/******************* (c) copyright 2016 ���ƺ��Ϲ����� **********************
 * �ļ���       ��DS18B20.c
 ****************************************************************************/
#include "Arduino.h"
#include "PinMap.h"
#include <DS18B20.h>
#include <intrins.h>
#include <math.h>

//�˴��޸����Ŷ���
#define DSPIN P1_0

//��ʼ��ds18b20
//��ds18b20һ����Գ�ʱ��͵�ƽ, Ȼ��һ����Էǳ���ʱ��ߵ�ƽ, ��������
void dsInit()
{
    //����11.0592mhzʱ��, unsigned int�͵�i, ��һ��i++������ʱ�����?us
    unsigned int i;
    digitalWrite(DSPIN, 0);
    i = 100;//����Լ800us, ����Э��Ҫ���480us����
    while(i > 0) i--;
    digitalWrite(DSPIN, 1); //����һ��������, ����ȴ�Ӧ��״̬
    i = 4;
    while(i > 0) i--;
}

void dsWait()
{
    unsigned int i;
    while(digitalRead(DSPIN));
    while(~digitalRead(DSPIN));  //��⵽Ӧ������
    i = 4;
    while(i > 0) i--;
}//��ds18b20��ȡһλ����
//��һλ, ��ds18b20һС���ڵ͵�ƽ, Ȼ����С���ڸߵ�ƽ,
//֮��ds18b20����������һ��ʱ���һλ����

bit dsReadBit()
{
    unsigned int i;
    bit b;
    digitalWrite(DSPIN, 0);
    i++;//��ʱԼ8us, ����Э��Ҫ�����ٱ���1us
    digitalWrite(DSPIN, 1);
    i++;
    i++;  //��ʱԼ16us, ����Э��Ҫ���������ʱ15us����
    b = digitalRead(DSPIN);
    i = 8;
    while(i > 0) i--; //��ʱԼ64us, ���϶�ʱ϶������60usҪ��
    return b;
}

unsigned char dsReadByte()//��ȡһ�ֽ�����, ͨ������dsReadBit()��ʵ��
{
    unsigned int i;
    unsigned char j, dat;
    dat = 0;
    for(i = 0; i < 8; i++)
    {
        j = dsReadBit();
        //���ȶ����������λ����
        dat = (j << 7) | (dat >> 1);
    }
    return dat;
}//��ds18b20д��һ�ֽ�����

void dsWriteByte(unsigned char dat)
{
    unsigned int i;
    unsigned char j;
    bit b;
    for(j = 0; j < 8; j++)
    {
        b = dat & 0x01;
        dat >>= 1;
        //д"1", ��dq����15us��, ��15us~60us�ڽ�dq����, �����д1
        if(b)
        {
            digitalWrite(DSPIN, 0);
            i++;
            i++;  //����Լ16us, ����Ҫ��15~60us��
            digitalWrite(DSPIN, 1);
            i = 8;
            while(i > 0) i--; //��ʱԼ64us, ����дʱ ϶������60usҪ��
        }
        else  //д"0", ��dq����60us~120us
            digitalWrite(DSPIN, 0);
        i = 8;
        while(i > 0) i--; //����Լ64us, ����Ҫ��
        digitalWrite(DSPIN, 1);
        i++;
        i++;  //����д0ʱ϶�����Ѿ�����60us, ����Ͳ�����д1����, ����ʱ64us��

    }
}//��ds18b20�����¶�ת������

void dsSendChangeCMD()
{
    dsInit(); //��ʼ��ds18b20, ����ʲô����, ���ȶ�Ҫ�����ʼ��
    dsWait();//�ȴ�ds18b20Ӧ��
    delay_ms(1); //��ʱ1ms, ��Ϊds18b20������dq 60~240us��ΪӦ���ź�
    dsWriteByte(0xcc); //д���������к������� skip rom
    dsWriteByte(0x44); //д���¶�ת�������� convert t
}//��ds18b20���Ͷ�ȡ��������

void dsSendReadCMDd()
{
    dsInit();
    dsWait();
    delay_ms(1);
    dsWriteByte(0xcc); //д���������к������� skip rom
    dsWriteByte(0xbe); //д���ȡ�������� read scratchpad
}

int dsGetTmpValue() //��ȡ��ǰ�¶�ֵ
{
    unsigned int tmpvalue;
    int value; //����¶���ֵ
    float t;
    unsigned char low, high;
    dsSendReadCMDd();
    //������ȡ�����ֽ�����
    low = dsReadByte();
    high = dsReadByte();
    //���ߵ������ֽںϳ�һ�����α���
    //������ж��ڸ��������ò�������ʾ��
    //���Ǹ�ֵ, ��ȡ��������ֵ���ò����ʾ��, ��ֱ�Ӹ�ֵ��int�͵�value
    tmpvalue = high;
    tmpvalue <<= 8;
    tmpvalue |= low;
    value = tmpvalue;
    //ʹ��ds18b20��Ĭ�Ϸֱ���12λ, ��ȷ��Ϊ0.0625��, ���������ݵ����λ����0.0625��
    t = value * 0.0625;
    //�����Ŵ�100��, ʹ��ʾʱ����ʾС�������λ, ����С������������4��5��
    //��t=11.0625, ���м�����, �õ�value = 1106, ��11.06 ��
    //��t=-11.0625, ���м�����, �õ�value = -1106, ��-11.06 ��
    value = t * 100 + (value > 0 ? 0.5 : -0.5); //����0��0.5, С��0��0.5
    return value;
}
//��ʾ��ǰ�¶�ֵ, ��ȷ��С�����һλ
//����λѡ�ٶ�ѡ, ����io��Ĭ������ߵ�ƽ, ���Ե���λѡ��ʹ����ܳ�������


