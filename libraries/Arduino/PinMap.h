/******************* (C) Copyright 2018 枫云海韵工作室 **********************
 * 文件名       ：PinMap.h
 * 作用         ：4051，STC15引脚库 51Arduino UNO
 * 备注         ：集成了reg51.h，使用了官方库
--------------------------------------------------------------------------*/

#ifndef __PINMAP_H_
#define __PINMAP_H_ 1

//此处检验单片机类型
//1为AT51可以兼容STC89系列
//0为STC15可以兼容STC12系列
#define MCUTYPE 1

#ifdef MCUTYPE

  #define D0 P3_0
  #define D1 P3_1
  #define D2 P3_2
  #define D3 P3_3
  #define D4 P3_4
  #define D5 P3_5
  #define D6 P3_6
  #define D7 P3_7

  #define A0 P1_0
  #define A1 P1_1

  #define D8 P1_2
  #define D9 P1_3
  #define D10 P1_4
  #define D11 P1_5
  #define D12 P1_6
  #define D13 P1_7

  /*------------------------------------------------
  P0 Bit Registers
  ------------------------------------------------*/
  sbit P0_0 = 0x80;
  sbit P0_1 = 0x81;
  sbit P0_2 = 0x82;
  sbit P0_3 = 0x83;
  sbit P0_4 = 0x84;
  sbit P0_5 = 0x85;
  sbit P0_6 = 0x86;
  sbit P0_7 = 0x87;

  /*------------------------------------------------
  P1 Bit Registers
  ------------------------------------------------*/
  sbit P1_0 = 0x90;
  sbit P1_1 = 0x91;
  sbit P1_2 = 0x92;
  sbit P1_3 = 0x93;
  sbit P1_4 = 0x94;
  sbit P1_5 = 0x95;
  sbit P1_6 = 0x96;
  sbit P1_7 = 0x97;

  /*------------------------------------------------
  P2 Bit Registers
  ------------------------------------------------*/
  sbit P2_0 = 0xA0;
  sbit P2_1 = 0xA1;
  sbit P2_2 = 0xA2;
  sbit P2_3 = 0xA3;
  sbit P2_4 = 0xA4;
  sbit P2_5 = 0xA5;
  sbit P2_6 = 0xA6;
  sbit P2_7 = 0xA7;

  /*------------------------------------------------
  P3 Bit Registers (Mnemonics & Ports)
  ------------------------------------------------*/
  sbit P3_0 = 0xB0;
  sbit P3_1 = 0xB1;
  sbit P3_2 = 0xB2;
  sbit P3_3 = 0xB3;
  sbit P3_4 = 0xB4;
  sbit P3_5 = 0xB5;
  sbit P3_6 = 0xB6;
  sbit P3_7 = 0xB7;

  /*  BYTE Register  */
  sfr P0   = 0x80;
  sfr P1   = 0x90;
  sfr P2   = 0xA0;
  sfr P3   = 0xB0;
  sfr PSW  = 0xD0;
  sfr ACC  = 0xE0;
  sfr B    = 0xF0;
  sfr SP   = 0x81;
  sfr DPL  = 0x82;
  sfr DPH  = 0x83;
  sfr PCON = 0x87;
  sfr TCON = 0x88;
  sfr TMOD = 0x89;
  sfr TL0  = 0x8A;
  sfr TL1  = 0x8B;
  sfr TH0  = 0x8C;
  sfr TH1  = 0x8D;
  sfr IE   = 0xA8;
  sfr IP   = 0xB8;
  sfr SCON = 0x98;
  sfr SBUF = 0x99;


  /*  BIT Register  */
  /*  PSW   */
  sbit CY   = 0xD7;
  sbit AC   = 0xD6;
  sbit F0   = 0xD5;
  sbit RS1  = 0xD4;
  sbit RS0  = 0xD3;
  sbit OV   = 0xD2;
  sbit P    = 0xD0;

  /*  TCON  */
  sbit TF1  = 0x8F;
  sbit TR1  = 0x8E;
  sbit TF0  = 0x8D;
  sbit TR0  = 0x8C;
  sbit IE1  = 0x8B;
  sbit IT1  = 0x8A;
  sbit IE0  = 0x89;
  sbit IT0  = 0x88;

  /*  IE   */
  sbit EA   = 0xAF;
  sbit ES   = 0xAC;
  sbit ET1  = 0xAB;
  sbit EX1  = 0xAA;
  sbit ET0  = 0xA9;
  sbit EX0  = 0xA8;

  /*  IP   */
  sbit PS   = 0xBC;
  sbit PT1  = 0xBB;
  sbit PX1  = 0xBA;
  sbit PT0  = 0xB9;
  sbit PX0  = 0xB8;

  /*  P3  */
  sbit RD   = 0xB7;
  sbit WR   = 0xB6;
  sbit T1   = 0xB5;
  sbit T0   = 0xB4;
  sbit INT1 = 0xB3;
  sbit INT0 = 0xB2;
  sbit TXD  = 0xB1;
  sbit RXD  = 0xB0;

  /*  SCON  */
  sbit SM0  = 0x9F;
  sbit SM1  = 0x9E;
  sbit SM2  = 0x9D;
  sbit REN  = 0x9C;
  sbit TB8  = 0x9B;
  sbit RB8  = 0x9A;
  sbit TI   = 0x99;
  sbit RI   = 0x98;

#else

  #include "STC15Fxxxx.H"

  #define D0 P3_0
  #define D1 P3_1
  #define D2 P3_2
  #define D3 P3_3
  #define D4 P3_4
  #define D5 P3_5
  #define D6 P3_6
  #define D7 P3_7

  #define D8 P2_6
  #define D9 P2_5
  #define D10 P2_4
  #define D11 P2_3
  #define D12 P2_2
  #define D13 P2_1

  #define A0 P1_0
  #define A1 P1_1
  #define A2 P1_2
  #define A3 P1_3
  #define A4 P1_4
  #define A5 P1_5
  #define A6 P1_6
  #define A7 P1_7
  
  /*------------------------------------------------
  P0 Bit Registers
  ------------------------------------------------*/
  sbit P0_0 = 0x80;
  sbit P0_1 = 0x81;
  sbit P0_2 = 0x82;
  sbit P0_3 = 0x83;
  sbit P0_4 = 0x84;
  sbit P0_5 = 0x85;
  sbit P0_6 = 0x86;
  sbit P0_7 = 0x87;

  /*------------------------------------------------
  P1 Bit Registers
  ------------------------------------------------*/
  sbit P1_0 = 0x90;
  sbit P1_1 = 0x91;
  sbit P1_2 = 0x92;
  sbit P1_3 = 0x93;
  sbit P1_4 = 0x94;
  sbit P1_5 = 0x95;
  sbit P1_6 = 0x96;
  sbit P1_7 = 0x97;

  /*------------------------------------------------
  P2 Bit Registers
  ------------------------------------------------*/
  sbit P2_0 = 0xA0;
  sbit P2_1 = 0xA1;
  sbit P2_2 = 0xA2;
  sbit P2_3 = 0xA3;
  sbit P2_4 = 0xA4;
  sbit P2_5 = 0xA5;
  sbit P2_6 = 0xA6;
  sbit P2_7 = 0xA7;

  /*------------------------------------------------
  P3 Bit Registers (Mnemonics & Ports)
  ------------------------------------------------*/
  sbit P3_0 = 0xB0;
  sbit P3_1 = 0xB1;
  sbit P3_2 = 0xB2;
  sbit P3_3 = 0xB3;
  sbit P3_4 = 0xB4;
  sbit P3_5 = 0xB5;
  sbit P3_6 = 0xB6;
  sbit P3_7 = 0xB7;


#endif

#endif
