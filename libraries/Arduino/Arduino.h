/******************* (C) Copyright 2018 ���ƺ��Ϲ����� **********************
 * �ļ���       ��Arduino.h
 * ����         ����51������Arduino���﷨�༭������.����Ϊ_
 * ��ע         �����ú���
 ****************************************************************************/

#ifndef __ARDUINO_H_
#define __ARDUINO_H_ 1

#include "PinMap.h"

#define uint8_t unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long

#define FOSC 11059200l //ϵͳʱ��Ƶ��

/*��s��ʱ���������ֵ65535*/
#define delayMicroseconds(us) while(us--)
#define delay_us(us) while(us--)
#define delay(ms) delay_ms(ms)

//�����
//#define NOP() systimemil++
#define JMP goto
#define LJMP goto
#define SJMP goto

#define HIGH 1
#define LOW 0

sbit CMP_R=P3^6;
sbit ADC_P=P1^1;

//void analogReference(int type);
/*���òο���ѹ
DEFAULT��Ĭ��ֵ���ο���ѹΪ5V
INTERNAL���͵�ѹģʽ��ʹ��Ƭ�ڻ�׼��ѹԴ��
EXTERNAL����չģʽ��ͨ��AREF���Ż�ȡ�ο���ѹ*/

/*�ܽ�д��� */
#define digitalWrite(pin, value) pin = value

/*�ܽŶ�ȡ�� */
#define digitalRead(pin) pin

uint16_t analogRead(uint8_t pin);
/*analogRead�������ڶ�ȡ���ŵ�ģ������ѹֵ��
ÿ��һ����Ҫ��100ms��ʱ�䡣
����pin��ʾ��Ҫ��ȡģ������ѹֵ�����ţ�
�ú�������ֵΪint�ͣ���ʾ���ŵ�ģ������ѹֵ����Χ��0��1023*/

void analogWrite(uint8_t pin, uint8_t value);
/*ͨ��PWM�ķ�ʽ��P4_2��P4_3��P1_3��P1_4���������һ��ģ������
PWM��Ƶ�ʴ�ԼΪ490Hz����ΧΪ0~255*/

void setPwmFrequency(uint8_t pin, int freq);
/*����PWM��Ƶ�ʡ���λHz*/

//void attachInterrupt(uint8_t interrupt, function, mode);
/*�������������ⲿ�жϣ�������3��������interrupt��function��mode���ֱ��ʾ�ж�Դ���жϴ�����������ģʽ�������ж�Դ��ѡֵ0��1����Arduino��һ���Ӧ2�ź�3���������ţ������жϴ���������ָ���жϵĴ�����������ֵΪ������ָ�룬����ģʽ��4�����ͣ�LOW���͵�ƽ��������CHANGE���仯ʱ��������RISING���͵�ƽ��Ϊ�ߵ�ƽ��������FALLING���ߵ�ƽ��Ϊ�͵�ƽ��������*/

void Serial_begin(int speed);

uint8_t RL (uint8_t a);
uint8_t RR (uint8_t a);
void SWAPL (uint8_t a, uint8_t b);
uint8_t SWAP (uint8_t a);
/*����������*/

void setup();
void loop();
/*Arduino��������*/

#ifdef MCUTYPE
/*********************�Ӵ��п�ʼ����ATMEL51��Ƭ��*********************/

#define OUTPUT 0 //�������
#define INPUT 1 //��������

/*���ùܽ�ģʽ�� */
#define pinMode(pin, mode) pin = mode

/*����PWM��Ƶ�ʡ���λHz*/
#define setPwmFrequency(freq) pwmfreq = freq

//����
#define Serial_available() RI
#define Serial_read() scanf("%c")
#define Serial_flush() SBUF = 0
#define Serial_end() T1 = 0
#define Serial_write(val) printf ("%", val)
#define Serial_print(val) printf("%c", val) //ASCII��
#define Serial_println(val) printf ("%c \n", val) //ASCII��

void init();
void main();
void delay_ms (uint16_t ms);
uint16_t analogRead(uint8_t pin);
void analogWrite(uint8_t pin, uint8_t value);
void Serial_begin(int speed);

#else
/*********************�Ӵ��п�ʼ����STC15��Ƭ��*********************/
//ͨ����ʱ����
#include "config.h"
#define delay(a) delay_ms(a)

// Arduino���޸�����
// ���¶��������ƣ�
// GPIO_Pullup INPUT_PULLUP
// GPIO_HighZ INPUT
// GPIO_OUT_PP OUTPUT
// �汾: V1.0, 2012-10-22

#define INPUT_PULLUP 0 //��������
#define INPUT 1  //����
#define OUTPUT 3 //���
#define analogRead(a) Get_ADC10bitResult(a)

//����
#define Serial_available() RI
#define Serial_read() RX1_Buffer[i]
#define Serial_write(val) PrintString1(val) //�ַ���
#define Serial_print(val) TX1_write2buff(val) //ASCII��
#define Serial_println(val) TX1_write2buff(val);PrintString1("\n") //ASCII��

void init();
void main();
uint8_t pinMap(uint8_t pin);
uint8_t adcPinMap(uint8_t pin);
void pinMode(uint8_t pin, mode);
void adcInit(uint8_t pin);
void analogWrite(uint8_t pin, uint8_t value);
void Serial_begin(int speed);

#endif





