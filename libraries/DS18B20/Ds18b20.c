/******************* (c) copyright 2016 枫云海韵工作室 **********************
 * 文件名       ：DS18B20.c
 ****************************************************************************/
#include "Arduino.h"
#include "PinMap.h"
#include <DS18B20.h>
#include <intrins.h>
#include <math.h>

//此处修改引脚定义
#define DSPIN P1_0

//初始化ds18b20
//让ds18b20一段相对长时间低电平, 然后一段相对非常短时间高电平, 即可启动
void dsInit()
{
    //对于11.0592mhz时钟, unsigned int型的i, 作一个i++操作的时间大于?us
    unsigned int i;
    digitalWrite(DSPIN, 0);
    i = 100;//拉低约800us, 符合协议要求的480us以上
    while(i > 0) i--;
    digitalWrite(DSPIN, 1); //产生一个上升沿, 进入等待应答状态
    i = 4;
    while(i > 0) i--;
}

void dsWait()
{
    unsigned int i;
    while(digitalRead(DSPIN));
    while(~digitalRead(DSPIN));  //检测到应答脉冲
    i = 4;
    while(i > 0) i--;
}//向ds18b20读取一位数据
//读一位, 让ds18b20一小周期低电平, 然后两小周期高电平,
//之后ds18b20则会输出持续一段时间的一位数据

bit dsReadBit()
{
    unsigned int i;
    bit b;
    digitalWrite(DSPIN, 0);
    i++;//延时约8us, 符合协议要求至少保持1us
    digitalWrite(DSPIN, 1);
    i++;
    i++;  //延时约16us, 符合协议要求的至少延时15us以上
    b = digitalRead(DSPIN);
    i = 8;
    while(i > 0) i--; //延时约64us, 符合读时隙不低于60us要求
    return b;
}

unsigned char dsReadByte()//读取一字节数据, 通过调用dsReadBit()来实现
{
    unsigned int i;
    unsigned char j, dat;
    dat = 0;
    for(i = 0; i < 8; i++)
    {
        j = dsReadBit();
        //最先读出的是最低位数据
        dat = (j << 7) | (dat >> 1);
    }
    return dat;
}//向ds18b20写入一字节数据

void dsWriteByte(unsigned char dat)
{
    unsigned int i;
    unsigned char j;
    bit b;
    for(j = 0; j < 8; j++)
    {
        b = dat & 0x01;
        dat >>= 1;
        //写"1", 将dq拉低15us后, 在15us~60us内将dq拉高, 即完成写1
        if(b)
        {
            digitalWrite(DSPIN, 0);
            i++;
            i++;  //拉低约16us, 符号要求15~60us内
            digitalWrite(DSPIN, 1);
            i = 8;
            while(i > 0) i--; //延时约64us, 符合写时 隙不低于60us要求
        }
        else  //写"0", 将dq拉低60us~120us
            digitalWrite(DSPIN, 0);
        i = 8;
        while(i > 0) i--; //拉低约64us, 符号要求
        digitalWrite(DSPIN, 1);
        i++;
        i++;  //整个写0时隙过程已经超过60us, 这里就不用像写1那样, 再延时64us了

    }
}//向ds18b20发送温度转换命令

void dsSendChangeCMD()
{
    dsInit(); //初始化ds18b20, 无论什么命令, 首先都要发起初始化
    dsWait();//等待ds18b20应答
    delay_ms(1); //延时1ms, 因为ds18b20会拉低dq 60~240us作为应答信号
    dsWriteByte(0xcc); //写入跳过序列号命令字 skip rom
    dsWriteByte(0x44); //写入温度转换命令字 convert t
}//向ds18b20发送读取数据命令

void dsSendReadCMDd()
{
    dsInit();
    dsWait();
    delay_ms(1);
    dsWriteByte(0xcc); //写入跳过序列号命令字 skip rom
    dsWriteByte(0xbe); //写入读取数据令字 read scratchpad
}

int dsGetTmpValue() //获取当前温度值
{
    unsigned int tmpvalue;
    int value; //存放温度数值
    float t;
    unsigned char low, high;
    dsSendReadCMDd();
    //连续读取两个字节数据
    low = dsReadByte();
    high = dsReadByte();
    //将高低两个字节合成一个整形变量
    //计算机中对于负数是利用补码来表示的
    //若是负值, 读取出来的数值是用补码表示的, 可直接赋值给int型的value
    tmpvalue = high;
    tmpvalue <<= 8;
    tmpvalue |= low;
    value = tmpvalue;
    //使用ds18b20的默认分辨率12位, 精确度为0.0625度, 即读回数据的最低位代表0.0625度
    t = value * 0.0625;
    //将它放大100倍, 使显示时可显示小数点后两位, 并对小数点后第三进行4舍5入
    //如t=11.0625, 进行计数后, 得到value = 1106, 即11.06 度
    //如t=-11.0625, 进行计数后, 得到value = -1106, 即-11.06 度
    value = t * 100 + (value > 0 ? 0.5 : -0.5); //大于0加0.5, 小于0减0.5
    return value;
}
//显示当前温度值, 精确到小数点后一位
//若先位选再段选, 由于io口默认输出高电平, 所以当先位选会使数码管出现乱码


