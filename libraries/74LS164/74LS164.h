/******************* (c) copyright 2016 枫云海韵工作室 **********************
 * 文件名       ：74ls164.h
 * 作用         ：共阴数码管74hc164串行驱动
 * 函数         ：ls164_sendbyte(uchar byte)           发送一个字节的i2c
                  ls164_display(uchar number)          74ls164显示
 * 转载         ：http://www.baiheee.com/documents/100816/100816210758.htm
 ****************************************************************************/

#ifndef __74LS164_H_
#define __74LS164_H_ 1

void lssendByte(unsigned char byte);
void lsDisplay(unsigned char number);

#endif
