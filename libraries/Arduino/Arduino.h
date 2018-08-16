/******************* (C) Copyright 2018 枫云海韵工作室 **********************
 * 文件名       ：Arduino.h
 * 作用         ：让51可以用Arduino的语法编辑，其中.更换为_
 * 备注         ：常用函数
 ****************************************************************************/

#ifndef __ARDUINO_H_
#define __ARDUINO_H_ 1

#include "PinMap.h"

#define uint8_t unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long

#define FOSC 11059200l //系统时钟频率

/*μs延时函数，最大值65535*/
#define delayMicroseconds(us) while(us--)
#define delay_us(us) while(us--)
#define delay(ms) delay_ms(ms)

//汇编组
//#define NOP() systimemil++
#define JMP goto
#define LJMP goto
#define SJMP goto

#define HIGH 1
#define LOW 0

sbit CMP_R=P3^6;
sbit ADC_P=P1^1;

//void analogReference(int type);
/*配置参考电压
DEFAULT：默认值，参考电压为5V
INTERNAL：低电压模式，使用片内基准电压源。
EXTERNAL：扩展模式，通过AREF引脚获取参考电压*/

/*管脚写入√ */
#define digitalWrite(pin, value) pin = value

/*管脚读取√ */
#define digitalRead(pin) pin

uint16_t analogRead(uint8_t pin);
/*analogRead函数用于读取引脚的模拟量电压值，
每读一次需要花100ms的时间。
参数pin表示所要获取模拟量电压值的引脚，
该函数返回值为int型，表示引脚的模拟量电压值，范围在0～1023*/

void analogWrite(uint8_t pin, uint8_t value);
/*通过PWM的方式在P4_2，P4_3，P1_3，P1_4引脚上输出一个模拟量，
PWM的频率大约为490Hz。范围为0~255*/

void setPwmFrequency(uint8_t pin, int freq);
/*控制PWM的频率。单位Hz*/

//void attachInterrupt(uint8_t interrupt, function, mode);
/*函数用于设置外部中断，函数有3个参数：interrupt、function和mode，分别表示中断源、中断处理函数、触发模式。参数中断源可选值0或1，在Arduino中一般对应2号和3号数字引脚；参数中断处理函数用来指定中断的处理函数，参数值为函数的指针，触发模式有4种类型：LOW（低电平触发）、CHANGE（变化时触发）、RISING（低电平变为高电平触发）、FALLING（高电平变为低电平触发）。*/

void Serial_begin(int speed);

uint8_t RL (uint8_t a);
uint8_t RR (uint8_t a);
void SWAPL (uint8_t a, uint8_t b);
uint8_t SWAP (uint8_t a);
/*汇编基础函数*/

void setup();
void loop();
/*Arduino基础函数*/

#ifdef MCUTYPE
/*********************从此行开始兼容ATMEL51单片机*********************/

#define OUTPUT 0 //输出拉低
#define INPUT 1 //输入拉高

/*配置管脚模式√ */
#define pinMode(pin, mode) pin = mode

/*控制PWM的频率。单位Hz*/
#define setPwmFrequency(freq) pwmfreq = freq

//串口
#define Serial_available() RI
#define Serial_read() scanf("%c")
#define Serial_flush() SBUF = 0
#define Serial_end() T1 = 0
#define Serial_write(val) printf ("%", val)
#define Serial_print(val) printf("%c", val) //ASCII码
#define Serial_println(val) printf ("%c \n", val) //ASCII码

void init();
void main();
void delay_ms (uint16_t ms);
uint16_t analogRead(uint8_t pin);
void analogWrite(uint8_t pin, uint8_t value);
void Serial_begin(int speed);

#else
/*********************从此行开始兼容STC15单片机*********************/
//通用延时函数
#include "config.h"
#define delay(a) delay_ms(a)

// Arduino化修改内容
// 重新定义了名称：
// GPIO_Pullup INPUT_PULLUP
// GPIO_HighZ INPUT
// GPIO_OUT_PP OUTPUT
// 版本: V1.0, 2012-10-22

#define INPUT_PULLUP 0 //输入上拉
#define INPUT 1  //输入
#define OUTPUT 3 //输出
#define analogRead(a) Get_ADC10bitResult(a)

//串口
#define Serial_available() RI
#define Serial_read() RX1_Buffer[i]
#define Serial_write(val) PrintString1(val) //字符串
#define Serial_print(val) TX1_write2buff(val) //ASCII码
#define Serial_println(val) TX1_write2buff(val);PrintString1("\n") //ASCII码

void init();
void main();
uint8_t pinMap(uint8_t pin);
uint8_t adcPinMap(uint8_t pin);
void pinMode(uint8_t pin, mode);
void adcInit(uint8_t pin);
void analogWrite(uint8_t pin, uint8_t value);
void Serial_begin(int speed);

#endif





