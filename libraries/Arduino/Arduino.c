/******************* (C) Copyright 2018 枫云海韵工作室 **********************
 * 文件名       ：Arduino.c
 * 作用         ：让51内核单片机可以用Arduino的语法编辑，兼容AT89X5X，AT89X4051其中.更换为_
 * 备注         ：如果是ATMEL公司单片机，则
                    Timer0 用为任意管脚的PWM功能
                    Timer1 用为波特率发生器、滴答计数器和ADC采集计数器
                    Timer2 空
                  如果是STC15，则
                    Timer0 空
                    Timer1 空
                    Timer2 空
 ****************************************************************************/
#include <Arduino.h>
#include <PinMap.h>
#include <stdio.h> //一个串口用这么多库简直浪费
#include <stdarg.h> //一个串口用这么多库简直浪费

#define PWM_OUT P1_0

uint8_t TH0HIGH = 0;
uint8_t TL0HIGH = 0;
uint8_t TH0LOW = 0;
uint8_t TL0LOW = 0;

uint32_t systime = 0; //系统时间ms
uint32_t systimemil = 0; //系统时间μs
uint8_t timebit = 1; //时间比率

uint8_t uartmsg = 0; //串口缓存
uint16_t baud = 0; //串口波特率

uint16_t pwmfreq = 490; //初始PWM频率
uint16_t valuebak = 0; //PWM频率缓存

uint16_t advalue = 0; //ADC相关
bit timeroverflow; //ADC相关

uint8_t RL (uint8_t a)
{
    if(a & 0x80)a = (a << 1) | 0x01;
    else a = a << 1;
    return a;
}

uint8_t RR (uint8_t a)
{
    if(a & 0x01)a = (a >> 1) | 0x80;
    else a = a >> 1;
    return a;
}

void SWAPL (uint8_t c, uint8_t d)
{
    uint8_t i;
    uint8_t *a;
    uint8_t *b;
    a = &c;
    b = &d;
    i = *a;
    *a = *b;
    *b = i;
}

uint8_t SWAP (uint8_t a)
{
    uint8_t i = a / 16, j = a % 16;
    return a = 16 * j + i;
}

#if MCUTYPE
/*********************从此行开始兼容ATMEL51单片机*********************/

//基础函数组
void init()
{
    ;
}

void main()
{
    init();
    setup();
    for(;;)loop();
}

void delay_ms (uint16_t ms)
{
    uint8_t a, b;
    for(; ms > 0; ms--)
        for(b = 142; b > 0; b--)
            for(a = 2; a > 0; a--);
}

//中断组
void pwmInterrupt() interrupt 1 using 1 //定时器0中断
{
    if(PWM_OUT == 0)
    {
        TH0 = TH0HIGH;
        TL0 = TL0HIGH;
    }
    else
    {
        TH0 = TH0LOW;
        TL0 = TL0LOW;
    }
    TR0 = 0;
    TR0 = 1;
    PWM_OUT = ~PWM_OUT;
}

void adcInterrupt() interrupt 5 using 2 //定时器2中断
{
    TR1 = 0;
    timeroverflow = 1;
    TH1 = 0xFF;
    TL1 = 0xFF;
}

//这个ADC需要研究一下
uint16_t analogRead(uint8_t pin)
{
   pin = 0;
   TR1 = 0;
   TMOD &= 0x0F; //清空定时器1相关寄存器
   TMOD |= 0x10; //设定定时器1为16位计数器
   ET1 = 1;
   EA = 1;
   advalue = 0;
   TL1 = 0x00;
   TH1 = 0x00;
   TR1 = 1;
   ADC_P = 1; //充电
   while(CMP_R&&(!timeroverflow));
   timeroverflow = 0;
   TR1 = 0;
   ADC_P = 0;
   ((unsigned char *)&advalue)[0]=TH1;
   ((unsigned char *)&advalue)[1]=TL1;
   advalue=advalue+1000;
   
   Serial_begin(baud); //还原波特率
  
   return advalue;
}

void analogWrite(uint8_t pin, uint8_t value)
{
    pin = 0;
    if (value != valuebak) //避免重复运算浪费时间
    {
        uint16_t pwmfreq = valuebak = value;
        uint32_t PWM_OVER = 1000000 / pwmfreq; //总溢出量
        uint32_t THIGH = 0xff - PWM_OVER * value / 0xff; //高电平计数值
        uint32_t TLOW = 0xff - PWM_OVER * (0xff - value) / 0xff; //低电平计数值
        TH0HIGH = THIGH / 0xff;
        TL0HIGH = THIGH % 0xff;
        TH0LOW = TLOW / 0xff;
        TL0LOW = TLOW % 0xff;

        TMOD &= 0xF0;		//设置定时器模式
        TMOD |= 0x02;		//设置定时器模式
        TH0 = TH0HIGH;
        TL0 = TL0HIGH;
        EA = 1;
        ET0 = 1;
        TR0 = 1;
    }
}

void Serial_begin(int speed)
{
    baud = speed;
    switch (speed)
    {
    case 2400:
        TL1 = 0xF4;
        TH1 = 0xF4;
        break;
    case 4800:
        TL1 = 0xFA;
        TH1 = 0xFA;
        break;
    case 9600:
        TL1 = 0xFD;
        TH1 = 0xFD;
        break;
    case 19200:
        TL1 = 0xFE;
        TH1 = 0xFE;
        break;
    }
    TMOD &= 0x0F;   //清空定时器1相关寄存器
    TMOD |= 0x20;		//设定定时器1为8位自动重装方式
    SCON = 0x50;		//8位数据,可变波特率
    ET1 = 1;
    TR1 = 1;
    TI = 1;
}

#else
/*********************从此行开始兼容STC15单片机*********************/

#include "config.h"
//基础函数组
void init()
{
    ;
}

void main()
{
    init();
    setup();
    for(;;)loop();
}

/*配置管脚模式√ */
//把引脚改成数字
uint8_t pinMap(uint8_t pin)
{
  switch(pin)
  {
    case 0:return 30;break;
    case 1:return 31;break;
    case 2:return 32;break;
    case 3:return 33;break;
    case 4:return 34;break;
    case 5:return 35;break;
    case 6:return 36;break;
    case 7:return 37;break;
    case 8:return 26;break;
    case 9:return 25;break;
    case 10:return 24;break;
    case 11:return 23;break;
    case 12:return 22;break;
    case 13:return 21;break;
	default: return 0;break;
  }
}

uint8_t adcPinMap(uint8_t pin)
{
  switch(pin)
  {
    case 0:return 0x01;break;
    case 1:return 0x02;break;
    case 2:return 0x04;break;
    case 3:return 0x08;break;
    case 4:return 0x10;break;
    case 5:return 0x20;break;
    case 6:return 0x40;break;
    case 7:return 0x80;break;
	default: return 0;break;
  }
}

void pinMode(uint8_t pin, mode)
{
  uint8_t GPIO_TEMP = pinMap(pin) / 10;
  uint8_t GPIO_PIN_TEMP = 0x01 << (pinMap(pin) % 10);
  
  GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_PIN_TEMP;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = mode;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_TEMP,&GPIO_InitStructure);	//初始化
}

//ADC初始化
void adcInit(uint8_t pin)
{
  uint8_t ADC_PIN_TEMP = adcPinMap(pin);
  
  ADC_InitTypeDef		ADC_InitStructure;				//结构定义
	ADC_InitStructure.ADC_Px        = ADC_PIN_TEMP;	//设置要做ADC的IO,	ADC_P10 ~ ADC_P17(或操作),ADC_P1_All
	ADC_InitStructure.ADC_Speed     = ADC_360T;			//ADC速度			ADC_90T,ADC_180T,ADC_360T,ADC_540T
	ADC_InitStructure.ADC_Power     = ENABLE;			//ADC功率允许/关闭	ENABLE,DISABLE
	ADC_InitStructure.ADC_AdjResult = ADC_RES_H8L2;		//ADC结果调整,	ADC_RES_H2L8,ADC_RES_H8L2
	ADC_InitStructure.ADC_Polity    = PolityLow;		//优先级设置	PolityHigh,PolityLow
	ADC_InitStructure.ADC_Interrupt = DISABLE;			//中断允许		ENABLE,DISABLE
	ADC_Inilize(&ADC_InitStructure);					//初始化
	ADC_PowerControl(ENABLE);							//单独的ADC电源操作函数, ENABLE或DISABLE
}

void analogWrite(uint8_t pin, uint8_t value)
{
    PCA_InitTypeDef		PCA_InitStructure;
    
    u8 PWM_PIN_TEMP;
    u8 PWM_IO_USE;
    switch(pin)
    {
      case 5: PWM_PIN_TEMP = PCA0;PWM_IO_USE = PCA_P34_P35_P36_P37;break;
      case 6: PWM_PIN_TEMP = PCA1;PWM_IO_USE = PCA_P34_P35_P36_P37;break;
      case 7: PWM_PIN_TEMP = PCA2;PWM_IO_USE = PCA_P34_P35_P36_P37;break;
      case 10: PWM_PIN_TEMP = PCA0;PWM_IO_USE = PCA_P24_P25_P26_P27;break;
      case 9: PWM_PIN_TEMP = PCA1;PWM_IO_USE = PCA_P24_P25_P26_P27;break;
    }
    
    PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
    PCA_InitStructure.PCA_IoUse    = PWM_IO_USE;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
    PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//ENABLE, DISABLE
    PCA_InitStructure.PCA_Polity   = PolityLow;			//优先级设置	PolityHigh,PolityLow
    //PCA_InitStructure.PCA_RUN      = DISABLE;			//ENABLE, DISABLE
    PCA_Init(PCA_Counter,&PCA_InitStructure);

    PCA_InitStructure.PCA_Mode     = PCA_Mode_PWM;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
    PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_8bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
    PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
    PCA_InitStructure.PCA_Value    = 128 << 8;			//对于PWM,高8位为PWM占空比
    PCA_Init(PWM_PIN_TEMP,&PCA_InitStructure);
    
    CR = 1;

	UpdatePwm(PWM_PIN_TEMP, value);
}

//串口相关
void Serial_begin(int speed)
{
    COMx_InitDefine		COMx_InitStructure;					//结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//使用波特率,   BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = speed;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    COMx_InitStructure.UART_Interrupt = ENABLE;				//中断允许,   ENABLE或DISABLE
    COMx_InitStructure.UART_Polity    = PolityLow;			//中断优先级, PolityLow,PolityHigh
    COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
    COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
    USART_Configuration(USART1, &COMx_InitStructure);		//初始化串口1 USART1,USART2
}

#endif

